from ServoProjectModules.CalibrationAnalyzers.Helper import *

class SystemIdentificationObject:
    def __init__(self, data, a=None, b=None, c=None, f=None, dt=None):
        if len(data) == 0:
            self.dt = dt
            self.velData = np.array([[0], [0]])
            self.pwmData = np.array([[0], [0]])

            self.servoModelParameters = np.array([[a], [b], [f], [c]])
            self.identifyCurrentSystemModel()
            return

        self.dt = data[1, 0] - data[0, 0]

        derivativeTimeSteps = 2
        tempVelData = 0 * data[:, 1]
        for i, d in enumerate(zip(data[derivativeTimeSteps:,1], data[0:-derivativeTimeSteps,1])):
            tempVelData[i + 1] = 0.75 * tempVelData[i] + 0.25 * (d[0] - d[1]) / (derivativeTimeSteps * self.dt)

        def minDiff(vec, v):
            min = vec[0]
            for d in vec:
                if abs(v - min) > abs(v - d):
                    min = d
            return min

        lastVel = None
        for i, d in enumerate(tempVelData[1:-1]):
            i += 1
            if lastVel == None:
                lastVel = d
            if abs(d - lastVel) < 300000:
                data[i, 1] = d
                lastVel = d
            else:
                data[i, 1] = lastVel
                lastVel = minDiff(tempVelData[i - 5:i], lastVel)

        data = data[1:-1]

        velData = data[:, 1]
        pwmData = data[:, 2]

        velData = np.array(velData)
        velData.shape = (len(velData),1)
        pwmData = np.array(pwmData)
        pwmData.shape = (len(pwmData),1)

        velData -= np.mean(velData)

        self.velData = velData
        self.pwmData = pwmData

        self.identifyServoSystemModel()
        self.identifyCurrentSystemModel()

    def getServoSystemModelParameters(self, outputDt):
        contineusEqiv = -math.log(self.servoModelParameters[0]) / self.dt
        scaledPoleA = math.exp(outputDt * -contineusEqiv)
        scaledB = self.servoModelParameters[1, 0] / self.dt
        return np.array([scaledPoleA, scaledB])

    def identifyCurrentSystemModel(self):
        self.currentModelParams = np.array([1.0, self.servoModelParameters[3,0]])
        return self.currentModelParams

    def identifyServoSystemModel(self):
        covDef = False
        cov = None#np.matrix([[0.0, 0.0, 0.0, 0.0],
            #[0.0, 0.0, 0.0, 0.0],
            #[0.0, 0.0, 0.0, 0.0],
            #[0.0, 0.0, 0.0, 0.0]])
        covYDef = False
        covY = None#np.matrix([[0.0],[0.0],[0.0],[0.0]])

        velData = np.abs(self.velData)
        pwmData = np.abs(self.pwmData)

        for d in zip(velData[1+5:-5], velData[0+5:-1-5], pwmData[0+5:-1-5], pwmData[0:-1-5-5], pwmData[0+5+5:-1]):
            if d[4][0] == d[3][0]:
                phi = np.matrix([[d[1][0]], [d[2][0]], [1.0], [d[1][0] * d[2][0]]])
                y = d[0][0]

                temp = phi * np.transpose(phi)
                if covDef == False:
                    covDef = True
                    cov = temp
                else:
                    cov += temp
                if covYDef == False:
                    covYDef = True
                    covY = y * phi
                else:
                    covY += y * phi

        self.servoModelParameters = np.linalg.solve(cov, covY)
        self.servoModelParameters[2,0] = -self.servoModelParameters[2,0] / self.servoModelParameters[1,0]
        self.servoModelParameters[3,0] = self.servoModelParameters[3,0] / self.servoModelParameters[1,0]
        return self.servoModelParameters

    def plotServoSystemModel(self, box):
        simVel = 0 * self.velData
        lastSimVel = None
        for i, d in enumerate(zip(self.velData[1:], self.velData[0:-1], self.pwmData[0:-1])):
            if lastSimVel == None:
                lastSimVel = d[1][0]
            if True:
                pwm = d[2][0]
                friction = 0
                if pwm > 0:
                    friction = -self.servoModelParameters[2,0]
                elif pwm < 0:
                    friction = self.servoModelParameters[2,0]
                simVel[i] = (self.servoModelParameters[0] * lastSimVel +
                    self.servoModelParameters[1] * (pwm + friction + self.servoModelParameters[3] * lastSimVel * abs(pwm)))
            else:
                simVel[i] = d[0][0]

            lastSimVel = simVel[i]

        fig = Figure(figsize=(5, 4), dpi=100)
        ax = fig.add_subplot()

        t = np.arange(len(simVel)) * self.dt
        ax.plot(t, self.velData, 'b')
        ax.plot(t, simVel, 'k')

        canvas = FigureCanvas(fig)
        canvas.set_size_request(600, 400)
        box.add(canvas)

        label = Gtk.Label(label='Blue curve is real system and black is model. A good result\nis indicated by the black curve resembling the blue.')
        label.set_use_markup(True)
        label.set_margin_start(30)
        label.set_margin_end(50)
        label.set_margin_top(8)
        label.set_margin_bottom(10)
        label.set_xalign(0.0)
        box.add(label)

        box.show_all()

class KalmanFilter(object):
    """docstring for KalmanFilter"""
    def __init__(self, dt, A, B, C):
        super(KalmanFilter, self).__init__()

        Aex = np.hstack((A, B))
        Aex = np.vstack((Aex, np.array([[0, 0, 1]])))

        Bex = np.vstack((B, np.array([[0]])))
        Cex = np.hstack((C, np.array([[0]])))

        xhatex = np.zeros(np.shape(Bex))

        self.A = Aex
        self.AInv = np.linalg.inv(Aex)
        self.B = Bex
        self.C = Cex

        AT = np.transpose(Aex)
        CT = np.transpose(Cex)

        x = range(1 * 4 * 20, 100 * 4 * 20, 4 * 20)
        vec1 = []
        vec2 = []
        vec3 = []
        for v in x:
            kalmanFilterSpeed = v
            poles = np.exp(dt * np.array([-1.0, -0.98, -0.96]) * kalmanFilterSpeed)
            plaseResult = scipy.signal.place_poles(AT,  CT, poles)

            vec1.append(plaseResult.gain_matrix[0, 0])
            vec2.append(plaseResult.gain_matrix[0, 1])
            vec3.append(plaseResult.gain_matrix[0, 2])

        p1 = np.polyfit(x, vec1, 6)
        p2 = np.polyfit(x, vec2, 6)
        p3 = np.polyfit(x, vec3, 6)


        self.polyK = np.vstack((p1, p2, p3))

def getModelDtFromConfigFileString(configFileAsString, configClassName):
    configClassString = getConfigClassString(configFileAsString, configClassName)

    dtPattern = re.compile(r'Eigen::Matrix3f\s+A;[\n\s]+A\s*<<\s*[^,]*,\s*([^,]*)')
    temp = dtPattern.search(configClassString)
    if temp != None:
        dtStr = temp.group(1)
        dtStr = re.sub(r'f', '', dtStr)
        return float(dtStr)
    else:
        raise Exception('Could not find model dt')

class ServoModel(object):
    """docstring for ServoModel"""
    def __init__(self, dt, systemModel):
            super(ServoModel, self).__init__()
            self.dt = dt
            self.systemModel = systemModel

            dtp = self.dt
            dt2p = self.dt**2
            temp = self.systemModel.getServoSystemModelParameters(self.dt)
            a = temp[0]
            b = temp[1]

            self.A = np.array([[1, dtp], [0, a]])
            self.B = np.array([[dt2p / 2], [dtp]]) * b
            self.C = np.array([[1, 0]])

            self.kalmanFilter = KalmanFilter(dt, self.A, self.B, self.C)

    def  getControlParametersClassContentStr(self, indent):
        out = ''
        out += indent + '  public:\n'
        out += indent + '    //kalman filter observer vector\n'
        out += indent + '    static Eigen::Matrix<float, 3, 7> getKVector()\n'
        out += indent + '    {\n'
        out += indent + '        Eigen::Matrix<float, 3, 7> K;\n'
        out += indent + '        K << ' + printAsEigenInit(self.kalmanFilter.polyK, indent + '            ')
        out += '\n'
        out += indent + '        return K;\n'
        out += indent + '    }\n'
        out += '\n'
        out += indent + '    //system model A matrix\n'
        out += indent + '    static Eigen::Matrix3f getAMatrix()\n'
        out += indent + '    {\n'
        out += indent + '        Eigen::Matrix3f A;\n'
        out += indent + '        A << ' + printAsEigenInit(self.kalmanFilter.A, indent + '            ')
        out += '\n'
        out += indent + '        return A;\n'
        out += indent + '    }\n'
        out += '\n'
        out += indent + '    //system model invers A matrix\n'
        out += indent + '    static Eigen::Matrix3f getAInvMatrix()\n'
        out += indent + '    {\n'
        out += indent + '        Eigen::Matrix3f AInv;\n'
        out += indent + '        AInv << ' + printAsEigenInit(self.kalmanFilter.AInv, indent + '            ')
        out += '\n'
        out += indent + '        return AInv;\n'
        out += indent + '    }\n'
        out += '\n'
        out += indent + '    //system model B matrix\n'
        out += indent + '    static Eigen::Vector3f getBVector()\n'
        out += indent + '    {\n'
        out += indent + '        Eigen::Vector3f B;\n'
        out += indent + '        B << ' + printAsEigenInit(self.kalmanFilter.B, indent + '            ')
        out += '\n'
        out += indent + '        return B;\n'
        out += indent + '    }\n'
        out += '\n'
        out += indent + '    //system model friction comp value\n'
        out += indent + '    static float getFrictionComp()\n'
        out += indent + '    {\n'
        out += indent + '        return ' + str(self.systemModel.servoModelParameters[2,0]) + 'f;\n'
        out += indent + '    }\n'
        out += indent + '};'
        return out

    def writeModelToConfigFileString(self, configFileAsString, configClassName):
        configClassString = getConfigClassString(configFileAsString, configClassName)            

        pwmToStallCurrentPattern = re.compile(r'((\s*)constexpr\s+float\s+pwmToStallCurrent\s*)\{[^\}]*\};')
        backEmfCurrentPattern = re.compile(r'((\s*)constexpr\s+float\s+backEmfCurrent\s*)\{[^\}]*\};')
        controlParametersPattern = re.compile(r'((\s*)class\s+ControlParameters\s+:.*\n\2\{)(.*\n)*?\2\};')
        
        temp = True
        temp = pwmToStallCurrentPattern.search(configClassString) != None and temp
        temp = backEmfCurrentPattern.search(configClassString) != None and temp
        temp = controlParametersPattern.search(configClassString) != None and temp
        if temp:
            out = r'\1{' + str(self.systemModel.currentModelParams[0]) + r'f};'
            configClassString = re.sub(pwmToStallCurrentPattern, out, configClassString)

            out = r'\1{' + str(self.systemModel.currentModelParams[1]) + r'f};'
            configClassString = re.sub(backEmfCurrentPattern, out, configClassString)

            out = r'\1\n'
            out += self.getControlParametersClassContentStr(r'\2')
            configClassString = re.sub(controlParametersPattern, out, configClassString)

            configFileAsString = setConfigClassString(configFileAsString, configClassName, configClassString)

            return configFileAsString

        return ''

    def getGeneratedModel(self):
        out = ''
        out += '--------------------------------------------------------------------------------\n'
        out += '\n'
        out += '        constexpr float pwmToStallCurrent{' + str(self.systemModel.currentModelParams[0]) + 'f};\n'
        out += '        constexpr float backEmfCurrent{' + str(self.systemModel.currentModelParams[1]) + 'f};\n'
        out += '\n'
        out += '--------------------------------------------------------------------------------\n'
        out += '\n'
        out += '    class ControlParameters : public SetupConfigHolder::DefaultControlParameters\n'
        out += '    {\n'
        out += self.getControlParametersClassContentStr('    ') + '\n'
        out += '\n'
        out += '--------------------------------------------------------------------------------\n'

        return out

def createGuiBox(parent, nodeNr, getPortFun, configFilePath, configClassName):
    calibrationBox = Gtk.Box(orientation=Gtk.Orientation.VERTICAL)
    calibrationBox.set_margin_start(40)

    limitMovementButton = GuiFunctions.createToggleButton('Lock', getLowLev=True)
    limitMovementButton = GuiFunctions.addTopLabelTo('<b>Limit movement</b>\n Only move around locked position to avoid end limits', limitMovementButton[0]), limitMovementButton[1]
    calibrationBox.pack_start(limitMovementButton[0], False, False, 0)

    startPos = None

    def onLockPosition(widget):
        nonlocal startPos
        if widget.get_active():
            with createRobot(nodeNr, getPortFun()) as r:
                startPos = r.servoArray[0].getPosition(True)
        else:
            startPos = None

    limitMovementButton[1].connect('toggled', onLockPosition)

    outputModelDt = 0.0012
    motorSettleTime = 2
    minPwmValue = 10
    maxPwmValue = 100

    try:
        with open(configFilePath, "r") as configFile:
            configFileAsString = configFile.read()
            outputModelDt = getModelDtFromConfigFileString(configFileAsString, configClassName)
    except Exception as e:
        pass


    motorSettleTimeScale = GuiFunctions.creatHScale(motorSettleTime, 1, 10, 1, getLowLev=True)
    motorSettleTimeScale = GuiFunctions.addTopLabelTo('<b>Motor settle time</b>', motorSettleTimeScale[0]), motorSettleTimeScale[1]
    calibrationBox.pack_start(motorSettleTimeScale[0], False, False, 0)

    minPwmScale = GuiFunctions.creatHScale(minPwmValue, 0, 1023, 1, getLowLev=True)
    minPwmScale = GuiFunctions.addTopLabelTo('<b>Min motor pwm value</b>', minPwmScale[0]), minPwmScale[1]
    calibrationBox.pack_start(minPwmScale[0], False, False, 0)

    maxPwmScale = GuiFunctions.creatHScale(maxPwmValue, 0, 1023, 1, getLowLev=True)
    maxPwmScale = GuiFunctions.addTopLabelTo('<b>Max motor pwm value</b>', maxPwmScale[0]), maxPwmScale[1]
    calibrationBox.pack_start(maxPwmScale[0], False, False, 0)

    testButton = GuiFunctions.createButton('Test pwm value', getLowLev=True)

    dtSpinButton = GuiFunctions.creatSpinButton(outputModelDt * 1000, 0.6, 2.4, 0.2, getLowLev=True)
    dtSpinButton[1].set_margin_end(6)
    label = GuiFunctions.createLabel('ms')
    label.set_margin_start(6)
    dtSpinButton[0].pack_start(label, False, False, 0)
    dtSpinButton = GuiFunctions.addTopLabelTo('<b>System model cycle time</b>', dtSpinButton[0]), dtSpinButton[1]


    startButton = GuiFunctions.createButton('Start calibration', getLowLev=True)

    recordingProgressBar = GuiFunctions.creatProgressBar(label='Recording', getLowLev=True)

    testPwmValue = minPwmValue

    threadMutex = threading.Lock()

    def motorSettleTimeChanged(widget):
        nonlocal motorSettleTime
        nonlocal threadMutex

        with threadMutex:
            motorSettleTime = widget.get_value()

    def minPwmValueChanged(widget):
        nonlocal maxPwmScale
        nonlocal minPwmValue
        nonlocal testPwmValue
        nonlocal threadMutex

        with threadMutex:
            minPwmValue = widget.get_value()
            testPwmValue = minPwmValue

        if minPwmValue > maxPwmScale[1].get_value():
            maxPwmScale[1].set_value(minPwmValue)

    def maxPwmValueChanged(widget):
        nonlocal minPwmScale
        nonlocal maxPwmValue
        nonlocal testPwmValue
        nonlocal threadMutex

        with threadMutex:
            maxPwmValue = widget.get_value()
            testPwmValue = maxPwmValue

        if maxPwmValue < minPwmScale[1].get_value():
            minPwmScale[1].set_value(maxPwmValue)

    motorSettleTimeScale[1].connect('value-changed', motorSettleTimeChanged)
    minPwmScale[1].connect('value-changed', minPwmValueChanged)
    maxPwmScale[1].connect('value-changed', maxPwmValueChanged)

    def resetGuiAfterCalibration():
        nonlocal startButton
        nonlocal testButton
        nonlocal calibrationBox
        nonlocal recordingProgressBar
        nonlocal minPwmScale
        nonlocal maxPwmScale

        testButton[1].set_label('Test pwm value')
        testButton[1].set_sensitive(True)
        dtSpinButton[1].set_sensitive(True)
        startButton[1].set_label('Start calibration')
        startButton[1].set_sensitive(True)
        calibrationBox.remove(recordingProgressBar[0])
        motorSettleTimeScale[1].set_sensitive(True)
        minPwmScale[1].set_sensitive(True)
        maxPwmScale[1].set_sensitive(True)
        limitMovementButton[1].set_sensitive(True)

    runThread = False
    def testPwmRun(nodeNr, port):
        nonlocal runThread
        nonlocal threadMutex

        with createRobot(nodeNr, port) as robot:
            t = 0.0
            doneRunning = False
            pwmDir = 1
            moveDir = 0

            def sendCommandHandlerFunction(dt, robot):
                nonlocal t
                nonlocal threadMutex
                nonlocal pwmDir
                nonlocal moveDir

                servo = robot.servoArray[0]

                pos = servo.getPosition(True)

                if startPos != None:
                    if pos - startPos < -1 and moveDir != -1:
                        moveDir = -1
                        pwmDir *= -1
                    elif pos - startPos > 1 and moveDir != 1:
                        moveDir = 1
                        pwmDir *= -1

                servo.setOpenLoopControlSignal(testPwmValue * pwmDir, True)

            out = []

            def readResultHandlerFunction(dt, robot):
                nonlocal t
                nonlocal runThread
                nonlocal doneRunning

                t += dt
                servo = robot.servoArray[0]
                out.append([t, servo.getVelocity()])

                stop = False
                with threadMutex:
                    if runThread == False:
                        stop = True

                if stop or parent.isClosed:
                    robot.removeHandlerFunctions()
                    doneRunning = True

            robot.setHandlerFunctions(sendCommandHandlerFunction, readResultHandlerFunction);

            while not doneRunning:
                if not robot.isAlive():
                    break
                time.sleep(0.1)

            robot.shutdown()

            data = np.array(out)

            def plotData(data):
                dialog = Gtk.MessageDialog(
                        transient_for=parent,
                        flags=0,
                        message_type=Gtk.MessageType.INFO,
                        buttons=Gtk.ButtonsType.YES_NO,
                        text='Pwm test done!',
                )
                dialog.format_secondary_text(
                    "Do you want to plot the recorded data?"
                )
                response = dialog.run()
                dialog.destroy()

                if response == Gtk.ResponseType.YES:
                    plt.figure(1)
                    plt.plot(data[:, 0], data[:, 1], 'r')
                    plt.show()

            GLib.idle_add(plotData, data)

        GLib.idle_add(resetGuiAfterCalibration)

    testThread = None

    def onTestPwm(widget):
        nonlocal calibrationBox
        nonlocal startButton

        nonlocal testThread
        nonlocal runThread
        nonlocal threadMutex

        if widget.get_label() == 'Test pwm value':
            dtSpinButton[1].set_sensitive(False)
            startButton[1].set_sensitive(False)
            limitMovementButton[1].set_sensitive(False)
            widget.set_label('Stop pwm test')
            with threadMutex:
                runThread = True
            testThread = threading.Thread(target=testPwmRun, args=(nodeNr, getPortFun(),))
            testThread.start()
        else:
            with threadMutex:
                runThread = False
            testThread.join()

    def onDtSpinButtonChange(widget):
        outputModelDt = widget.get_value()

    def updateRecordingProgressBar(fraction):
        nonlocal recordingProgressBar

        recordingProgressBar[1].set_fraction(fraction)

    def handleResults(data):
        systemIdentifier = SystemIdentificationObject(data)

        dialog = Gtk.MessageDialog(
                transient_for=parent,
                flags=0,
                message_type=Gtk.MessageType.INFO,
                buttons=Gtk.ButtonsType.YES_NO,
                text='System identification done!',
        )
        dialog.format_secondary_text(
            "Should the configuration be updated with the new model?"
        )
        systemIdentifier.plotServoSystemModel(dialog.get_message_area())
        dialog.get_widget_for_response(Gtk.ResponseType.YES).grab_focus()
        response = dialog.run()
        dialog.destroy()

        if response == Gtk.ResponseType.YES:
            with open(configFilePath, "r") as configFile:
                configFileAsString = configFile.read()

                servoModel = ServoModel(outputModelDt, systemIdentifier)

                configFileAsString = servoModel.writeModelToConfigFileString(configFileAsString, configClassName)

                if configFileAsString != '':
                    with open(configFilePath, "w") as configFile:
                        configFile.write(configFileAsString)
                        GuiFunctions.transferToTargetMessage(parent)

                        return

            dialog = Gtk.MessageDialog(
                    transient_for=parent,
                    flags=0,
                    message_type=Gtk.MessageType.ERROR,
                    buttons=Gtk.ButtonsType.OK,
                    text='Configuration format error!',
            )
            dialog.format_secondary_text(
                "Please past in the new model manually"
            )
            box = dialog.get_message_area()
            funEntry = Gtk.Entry()
            funEntry.set_text(ServoModel(dt, systemIdentifier).getGeneratedModel())
            box.add(funEntry)
            box.show_all()
            response = dialog.run()
            dialog.destroy()

    def startCalibrationRun(nodeNr, port):
        nonlocal runThread
        nonlocal threadMutex
        nonlocal minPwmValue
        nonlocal maxPwmValue
        nonlocal motorSettleTime

        with createRobot(nodeNr, port, 0.018) as robot:
            pwmSampleValues = []
            nr = 10
            for i in range(0, nr):
                pwmSampleValues.append(i * (minPwmValue - maxPwmValue) / nr + maxPwmValue)
                pwmSampleValues.append(minPwmValue)
                pwmSampleValues.append(-(i * (minPwmValue - maxPwmValue) / nr + maxPwmValue))
                pwmSampleValues.append(-minPwmValue)

            def sendCommandHandlerFunction(dt, robot):
                return

            t = 0.0
            if startPos != None:
                t = -float(motorSettleTime)

            doneRunning = False
            i = 0
            pwm = None
            pwmDir = -1
            outEncDir = 1

            out = []

            def readResultHandlerFunction(dt, robot):
                nonlocal t
                nonlocal runThread
                nonlocal doneRunning
                nonlocal pwm
                nonlocal i
                nonlocal pwmDir
                nonlocal startPos
                nonlocal outEncDir

                stop = False

                servo = robot.servoArray[0]

                d = [t, servo.getPosition(False) / servo.getScaling(),
                        pwm]
                if pwm != None:
                    out.append(d)

                pos = servo.getPosition(True)

                if t < 0:
                    if pwmDir == -1:
                        if abs(pos - startPos) > 1.0:
                            pwmDir = 1
                            if pos - startPos >= 0.0:
                                outEncDir = -1
                        t = -motorSettleTime
                    elif abs(pos - startPos) > 1.0:
                        t = -motorSettleTime
                    else:
                        pwmDir = 0

                    servo.setOpenLoopControlSignal(maxPwmValue * pwmDir, True)

                    pwm = None
                else:
                    i = int(t / motorSettleTime)
                    if i < len(pwmSampleValues):
                        pwm = pwmSampleValues[i]

                        if startPos != None:
                            if outEncDir * pwm < 0 and pos - startPos > 1.0:
                                t -= dt
                            if outEncDir * pwm > 0 and pos - startPos < -1.0:
                                t -= dt
                    else:
                        pwm = 0
                        stop = True

                    servo.setOpenLoopControlSignal(pwm, True)

                GLib.idle_add(updateRecordingProgressBar, t / (motorSettleTime * len(pwmSampleValues)))

                with threadMutex:
                    if runThread == False:
                        stop = True

                if stop or parent.isClosed:
                    robot.removeHandlerFunctions()
                    doneRunning = True
                    return

                t += dt

            robot.setHandlerFunctions(sendCommandHandlerFunction, readResultHandlerFunction);

            while not doneRunning:
                if not robot.isAlive():
                    runThread = False
                    break
                time.sleep(0.1)

            robot.shutdown()

            if runThread == True:
                data = np.array(out)
                GLib.idle_add(handleResults, data)

        GLib.idle_add(resetGuiAfterCalibration)

    def onStartCalibration(widget):
        nonlocal testThread
        nonlocal threadMutex
        nonlocal runThread

        nonlocal calibrationBox
        nonlocal motorSettleTimeScale
        nonlocal minPwmScale
        nonlocal maxPwmScale
        nonlocal recordingProgressBar
        nonlocal testButton

        if widget.get_label() == 'Start calibration':
            widget.set_label('Abort calibration')

            recordingProgressBar[1].set_fraction(0.0)
            testButton[1].set_sensitive(False)
            dtSpinButton[1].set_sensitive(False)
            calibrationBox.pack_start(recordingProgressBar[0], False, False, 0)
            motorSettleTimeScale[1].set_sensitive(False)
            minPwmScale[1].set_sensitive(False)
            maxPwmScale[1].set_sensitive(False)
            limitMovementButton[1].set_sensitive(False)

            calibrationBox.show_all()

            with threadMutex:
                runThread = True
            testThread = threading.Thread(target=startCalibrationRun, args=(nodeNr, getPortFun(),))
            testThread.start()                                    
        else:
            with threadMutex:
                runThread = False
            testThread.join()

    testButton[1].connect('clicked', onTestPwm)
    dtSpinButton[1].connect('changed', onDtSpinButtonChange)
    startButton[1].connect('clicked', onStartCalibration)
    calibrationBox.pack_start(testButton[0], False, False, 0)
    calibrationBox.pack_start(dtSpinButton[0], False, False, 0)
    calibrationBox.pack_start(startButton[0], False, False, 0)
    calibrationBox.show_all()

    return calibrationBox
