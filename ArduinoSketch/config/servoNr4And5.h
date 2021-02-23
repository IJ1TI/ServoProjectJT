#ifndef CONFIG_HOLDER_H
#define CONFIG_HOLDER_H

#include "../defaultConfigHolder.h"
#include "../ResistiveEncoderHandler.h"
#include "../DCServo.h"

// replace with gear ratio from motor to output
constexpr float mainEncoderGearRatio{105.0 / 27968.0};

// replace with generated output from systemIdent.py
// vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
// config setps
// x 1) disconnect motor from gearbox
// x 2) compile and transfer to servo nr x
// x 3) open MasterCommunication folder in terminal
// x 4) run 'make'
// x 5) run './executable --servoNr x --recOpticalEncoder --output=opticalEncoderData.txt'
// x 6) run './systemIdent.py --opticalEncoderDataFile=opticalEncoderData.txt'
// x 7) copy past new generated ConfigHolder class, from terminal, over old class
// x 8) compile and transfer to servo nr x with new ConfigHolder class
// x 9) run './executable --servoNr x --recSystemIdentData --output=systemIdentData.txt'
// x 10) run './systemIdent.py --opticalEncoderDataFile=opticalEncoderData.txt --systemIdentDataFile=systemIdentData.txt'
// x 11) copy past new generated ConfigHolder class, from terminal, over old class
// x 12) connect motor to gearbox again
// x 13) compile and transfer to servo nr x with new ConfigHolder class
class SetupConfigHolder : public DefaultConfigHolder
{
public:
    static std::unique_ptr<OpticalEncoderHandler> createMainEncoderHandler()
    {
        std::array<uint16_t, 512> aVec = {2552, 2550, 2546, 2540, 2533, 2523, 2519, 2515, 2511, 2506, 2500, 2494, 2491, 2485, 2479, 2472, 2466, 2461, 2456, 2450, 2448, 2447, 2444, 2441, 2437, 2434, 2431, 2426, 2422, 2419, 2416, 2414, 2413, 2411, 2411, 2407, 2406, 2402, 2400, 2396, 2394, 2391, 2391, 2390, 2386, 2384, 2382, 2380, 2379, 2378, 2376, 2376, 2374, 2373, 2371, 2368, 2368, 2368, 2367, 2366, 2365, 2367, 2366, 2364, 2363, 2364, 2362, 2362, 2362, 2362, 2360, 2360, 2362, 2363, 2362, 2362, 2364, 2364, 2367, 2367, 2367, 2370, 2369, 2368, 2372, 2371, 2374, 2376, 2377, 2378, 2380, 2383, 2386, 2390, 2393, 2394, 2396, 2399, 2401, 2405, 2410, 2412, 2414, 2417, 2420, 2424, 2426, 2430, 2434, 2439, 2445, 2452, 2456, 2460, 2463, 2468, 2474, 2481, 2489, 2494, 2503, 2507, 2512, 2518, 2524, 2530, 2533, 2538, 2544, 2550, 2558, 2563, 2568, 2573, 2583, 2588, 2590, 2594, 2598, 2605, 2607, 2612, 2617, 2625, 2635, 2641, 2644, 2649, 2657, 2662, 2673, 2682, 2688, 2691, 2694, 2701, 2706, 2711, 2718, 2722, 2729, 2733, 2739, 2743, 2747, 2754, 2762, 2767, 2773, 2781, 2786, 2790, 2794, 2799, 2805, 2811, 2823, 2828, 2832, 2841, 2847, 2853, 2859, 2866, 2874, 2881, 2890, 2898, 2903, 2907, 2913, 2919, 2922, 2924, 2927, 2929, 2931, 2937, 2940, 2943, 2947, 2952, 2956, 2960, 2964, 2967, 2974, 2980, 2987, 2992, 2997, 3000, 3005, 3007, 3012, 3018, 3022, 3026, 3029, 3035, 3038, 3042, 3045, 3049, 3054, 3057, 3062, 3067, 3070, 3072, 3076, 3082, 3086, 3090, 3094, 3097, 3102, 3104, 3106, 3108, 3110, 3113, 3116, 3119, 3123, 3125, 3129, 3132, 3132, 3135, 3141, 3144, 3149, 3152, 3154, 3159, 3163, 3167, 3169, 3172, 3178, 3180, 3182, 3184, 3184, 3187, 3190, 3192, 3194, 3197, 3196, 3199, 3200, 3201, 3203, 3205, 3207, 3212, 3212, 3214, 3218, 3220, 3222, 3224, 3226, 3226, 3229, 3229, 3231, 3233, 3235, 3236, 3237, 3239, 3241, 3243, 3243, 3244, 3246, 3248, 3250, 3250, 3251, 3253, 3254, 3255, 3257, 3257, 3258, 3259, 3260, 3261, 3262, 3260, 3262, 3264, 3263, 3264, 3265, 3266, 3266, 3266, 3267, 3268, 3268, 3267, 3268, 3268, 3268, 3268, 3268, 3269, 3268, 3268, 3268, 3268, 3268, 3268, 3267, 3267, 3266, 3265, 3266, 3265, 3264, 3263, 3262, 3261, 3260, 3258, 3257, 3257, 3255, 3255, 3256, 3252, 3251, 3249, 3248, 3246, 3245, 3245, 3243, 3241, 3239, 3238, 3236, 3235, 3234, 3232, 3229, 3227, 3226, 3224, 3221, 3218, 3215, 3213, 3212, 3211, 3207, 3205, 3202, 3199, 3197, 3196, 3195, 3193, 3190, 3187, 3184, 3180, 3176, 3174, 3171, 3165, 3163, 3161, 3159, 3155, 3152, 3147, 3143, 3139, 3136, 3132, 3129, 3126, 3121, 3117, 3115, 3111, 3108, 3104, 3098, 3095, 3092, 3087, 3083, 3076, 3074, 3071, 3062, 3058, 3052, 3047, 3043, 3039, 3035, 3033, 3029, 3025, 3022, 3020, 3016, 3012, 3003, 2997, 2992, 2989, 2985, 2982, 2975, 2969, 2963, 2956, 2950, 2942, 2934, 2930, 2925, 2920, 2917, 2910, 2905, 2900, 2896, 2892, 2886, 2880, 2875, 2870, 2862, 2856, 2842, 2834, 2826, 2821, 2812, 2805, 2800, 2789, 2778, 2772, 2766, 2760, 2755, 2750, 2745, 2739, 2734, 2729, 2724, 2721, 2716, 2711, 2706, 2704, 2700, 2695, 2686, 2680, 2669, 2662, 2658, 2652, 2647, 2645, 2640, 2636, 2632, 2625, 2623, 2615, 2609, 2602, 2596, 2592, 2588, 2580, 2573, 2565};
        std::array<uint16_t, 512> bVec = {2771, 2771, 2768, 2765, 2761, 2754, 2751, 2748, 2745, 2742, 2735, 2732, 2729, 2723, 2718, 2712, 2706, 2702, 2698, 2692, 2689, 2689, 2686, 2682, 2678, 2676, 2671, 2665, 2661, 2656, 2652, 2649, 2648, 2647, 2644, 2642, 2638, 2631, 2628, 2622, 2618, 2615, 2612, 2609, 2601, 2596, 2592, 2586, 2583, 2581, 2578, 2573, 2566, 2562, 2559, 2554, 2546, 2538, 2535, 2532, 2527, 2524, 2516, 2512, 2506, 2499, 2493, 2489, 2484, 2480, 2475, 2470, 2469, 2461, 2457, 2455, 2451, 2444, 2438, 2432, 2428, 2425, 2425, 2419, 2418, 2412, 2405, 2400, 2396, 2391, 2389, 2380, 2374, 2366, 2359, 2356, 2352, 2348, 2345, 2338, 2332, 2329, 2324, 2322, 2318, 2312, 2310, 2306, 2301, 2297, 2289, 2283, 2279, 2276, 2273, 2270, 2265, 2259, 2254, 2251, 2246, 2244, 2241, 2238, 2234, 2232, 2232, 2230, 2228, 2225, 2223, 2221, 2220, 2219, 2216, 2215, 2215, 2213, 2213, 2212, 2212, 2211, 2210, 2210, 2209, 2209, 2209, 2208, 2210, 2210, 2211, 2212, 2213, 2212, 2214, 2214, 2215, 2217, 2218, 2219, 2221, 2221, 2222, 2223, 2225, 2226, 2229, 2230, 2231, 2235, 2237, 2237, 2240, 2242, 2245, 2246, 2252, 2253, 2255, 2258, 2262, 2266, 2269, 2272, 2277, 2283, 2290, 2296, 2299, 2302, 2306, 2311, 2313, 2315, 2316, 2319, 2321, 2326, 2328, 2330, 2334, 2338, 2342, 2346, 2349, 2351, 2360, 2367, 2375, 2382, 2388, 2392, 2398, 2401, 2407, 2416, 2422, 2428, 2433, 2442, 2447, 2452, 2456, 2464, 2472, 2477, 2485, 2495, 2501, 2505, 2512, 2524, 2531, 2538, 2547, 2556, 2562, 2567, 2571, 2575, 2580, 2586, 2590, 2597, 2606, 2612, 2618, 2625, 2628, 2634, 2647, 2654, 2664, 2671, 2679, 2690, 2698, 2709, 2717, 2724, 2738, 2746, 2749, 2755, 2760, 2766, 2773, 2779, 2784, 2788, 2792, 2798, 2800, 2803, 2808, 2815, 2822, 2831, 2836, 2843, 2852, 2856, 2863, 2869, 2874, 2878, 2880, 2884, 2890, 2896, 2900, 2903, 2909, 2916, 2919, 2925, 2928, 2933, 2936, 2942, 2949, 2951, 2954, 2959, 2963, 2967, 2973, 2976, 2977, 2980, 2984, 2985, 2988, 2988, 2990, 2994, 2996, 2998, 3000, 3002, 3004, 3006, 3009, 3012, 3014, 3016, 3018, 3020, 3022, 3024, 3026, 3028, 3030, 3031, 3033, 3035, 3037, 3038, 3040, 3041, 3041, 3043, 3044, 3045, 3046, 3048, 3049, 3050, 3052, 3052, 3054, 3055, 3054, 3053, 3052, 3056, 3056, 3056, 3058, 3057, 3056, 3058, 3058, 3057, 3058, 3057, 3058, 3056, 3056, 3056, 3056, 3055, 3054, 3056, 3054, 3053, 3052, 3052, 3052, 3052, 3049, 3050, 3049, 3049, 3047, 3047, 3046, 3046, 3046, 3044, 3044, 3042, 3042, 3041, 3040, 3039, 3039, 3038, 3038, 3037, 3036, 3035, 3034, 3032, 3033, 3032, 3032, 3030, 3029, 3028, 3028, 3025, 3026, 3024, 3024, 3022, 3022, 3021, 3019, 3018, 3017, 3017, 3014, 3012, 3010, 3009, 3007, 3007, 3005, 3004, 3004, 3002, 3000, 3000, 2999, 2998, 2994, 2992, 2990, 2989, 2988, 2986, 2984, 2982, 2980, 2978, 2974, 2971, 2969, 2966, 2965, 2963, 2961, 2958, 2957, 2955, 2954, 2952, 2950, 2947, 2946, 2942, 2940, 2938, 2932, 2928, 2924, 2923, 2919, 2916, 2914, 2909, 2904, 2900, 2898, 2895, 2892, 2889, 2887, 2885, 2881, 2879, 2876, 2874, 2872, 2869, 2866, 2864, 2862, 2860, 2854, 2852, 2845, 2840, 2839, 2836, 2833, 2831, 2828, 2826, 2824, 2820, 2817, 2813, 2809, 2804, 2801, 2798, 2795, 2791, 2786, 2782};
        return std::make_unique<OpticalEncoderHandler>(aVec, bVec, A1, A2, 4096.0 * mainEncoderGearRatio);
    }

    static std::unique_ptr<EncoderHandlerInterface> createOutputEncoderHandler()
    {
        std::array<int16_t, 32> compVec = {79, 97, 93, 94, 92, 88, 84, 82, 75, 76, 65, 58, 52, 39, 26, 14, -5, -20, -35, -51, -66, -77, -90, -96, -96, -96, -95, -94, -83, -71, -71, -71};
        return std::make_unique<ResistiveEncoderHandler>(A0, 4096.0 * 200.0 / 360.0, compVec);
    }

    static std::unique_ptr<CurrentController> createCurrentController()
    {
        constexpr float pwmToStallCurrent{1.0};
        constexpr float backEmfCurrent{-1.6693232382199313e-05 * 2};

        return std::make_unique<CurrentControlModel>(pwmToStallCurrent, backEmfCurrent, std::make_unique<HBridge2WirePwm>(11, 12));
    }

    class ControlParameters : public SetupConfigHolder::DefaultControlParameters
    {
      public:
        //kalman filter observer vector
        static Eigen::Vector3f getKVector()
        {
            Eigen::Vector3f K;
            K << 2.011661941066074,
                493.0937878670418,
                103.38332707332667 * 2;

            return K;
        }

        //system model A matrix
        static Eigen::Matrix3f getAMatrix()
        {
            Eigen::Matrix3f A;
            A << 1.0, 0.0024, 0.0014842527435006162 / 2,
                0.0, 0.9819417628930723, 1.2368772862505137 / 2,
                0.0, 0.0, 1.0;

            return A;
        }

        //system model invers A matrix
        static Eigen::Matrix3f getAInvMatrix()
        {
            Eigen::Matrix3f AInv;
            AInv << 1.0, -0.0024441368018903024, 0.0015388445512464705 / 2,
                0.0, 1.0183903341209595, -1.2596238728112863 / 2,
                0.0, 0.0, 1.0;

            return AInv;
        }

        //system model B matrix
        static Eigen::Vector3f getBVector()
        {
            Eigen::Vector3f B;
            B << 0.0014842527435006162 / 2,
                1.2368772862505137 / 2,
                0.0;

            return B;
        }

        //system model friction comp value
        static float getFrictionComp()
        {
            return 62.79863496418996;
        }
    };
};
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

class SetupConfigHolder2 : public DefaultConfigHolder
{
public:
    static std::unique_ptr<OpticalEncoderHandler> createMainEncoderHandler()
    {
        std::array<uint16_t, 512> aVec = {3390, 3391, 3390, 3390, 3389, 3390, 3390, 3390, 3389, 3389, 3388, 3388, 3389, 3388, 3388, 3388, 3387, 3386, 3386, 3385, 3385, 3384, 3384, 3383, 3383, 3382, 3381, 3380, 3381, 3379, 3379, 3378, 3377, 3376, 3375, 3374, 3373, 3372, 3371, 3369, 3368, 3368, 3366, 3364, 3363, 3362, 3360, 3358, 3356, 3355, 3354, 3352, 3351, 3350, 3348, 3346, 3344, 3343, 3342, 3339, 3337, 3335, 3332, 3331, 3329, 3327, 3326, 3324, 3323, 3322, 3320, 3318, 3315, 3314, 3314, 3311, 3310, 3307, 3305, 3302, 3301, 3300, 3298, 3296, 3295, 3292, 3291, 3290, 3288, 3287, 3284, 3282, 3279, 3277, 3274, 3272, 3271, 3269, 3266, 3265, 3262, 3260, 3258, 3256, 3254, 3252, 3251, 3248, 3246, 3245, 3243, 3241, 3237, 3234, 3234, 3231, 3229, 3228, 3226, 3225, 3221, 3218, 3216, 3214, 3211, 3210, 3208, 3206, 3203, 3202, 3202, 3199, 3197, 3196, 3193, 3190, 3188, 3186, 3185, 3183, 3181, 3179, 3177, 3176, 3173, 3171, 3168, 3166, 3164, 3162, 3160, 3158, 3156, 3155, 3153, 3150, 3148, 3146, 3144, 3141, 3139, 3137, 3136, 3134, 3133, 3131, 3129, 3127, 3123, 3122, 3120, 3118, 3117, 3116, 3112, 3113, 3112, 3111, 3108, 3105, 3102, 3101, 3100, 3098, 3098, 3097, 3096, 3094, 3093, 3092, 3091, 3089, 3088, 3088, 3086, 3086, 3085, 3083, 3082, 3081, 3081, 3080, 3078, 3078, 3076, 3075, 3075, 3074, 3073, 3071, 3071, 3070, 3069, 3069, 3068, 3068, 3065, 3065, 3064, 3063, 3063, 3062, 3062, 3060, 3060, 3058, 3058, 3058, 3058, 3057, 3056, 3055, 3054, 3054, 3052, 3052, 3052, 3051, 3051, 3050, 3050, 3049, 3049, 3050, 3048, 3048, 3048, 3047, 3047, 3047, 3046, 3046, 3045, 3046, 3046, 3045, 3046, 3045, 3046, 3045, 3046, 3046, 3045, 3045, 3045, 3046, 3046, 3046, 3046, 3046, 3046, 3047, 3047, 3047, 3047, 3048, 3048, 3048, 3048, 3048, 3049, 3049, 3049, 3050, 3051, 3052, 3052, 3051, 3052, 3053, 3054, 3053, 3055, 3055, 3056, 3057, 3058, 3058, 3059, 3060, 3060, 3061, 3061, 3063, 3064, 3065, 3065, 3067, 3067, 3068, 3070, 3071, 3072, 3073, 3074, 3076, 3078, 3078, 3078, 3082, 3084, 3086, 3086, 3084, 3082, 3088, 3090, 3092, 3093, 3095, 3096, 3098, 3099, 3101, 3102, 3104, 3106, 3108, 3110, 3111, 3113, 3114, 3116, 3117, 3119, 3122, 3124, 3125, 3127, 3129, 3131, 3132, 3135, 3137, 3138, 3141, 3143, 3145, 3147, 3150, 3152, 3155, 3157, 3158, 3162, 3165, 3166, 3169, 3171, 3174, 3174, 3177, 3180, 3181, 3183, 3185, 3188, 3192, 3195, 3196, 3198, 3202, 3204, 3207, 3210, 3213, 3216, 3218, 3219, 3221, 3224, 3225, 3228, 3230, 3232, 3235, 3238, 3240, 3241, 3243, 3246, 3248, 3250, 3252, 3255, 3257, 3259, 3262, 3263, 3265, 3268, 3271, 3275, 3277, 3277, 3280, 3283, 3286, 3289, 3291, 3293, 3296, 3297, 3299, 3301, 3303, 3304, 3306, 3309, 3311, 3313, 3315, 3316, 3319, 3321, 3321, 3323, 3324, 3327, 3329, 3330, 3333, 3334, 3336, 3338, 3339, 3340, 3341, 3343, 3345, 3346, 3347, 3347, 3349, 3350, 3352, 3354, 3356, 3355, 3357, 3358, 3360, 3362, 3362, 3363, 3364, 3365, 3367, 3368, 3369, 3369, 3371, 3372, 3373, 3374, 3375, 3376, 3378, 3378, 3379, 3379, 3380, 3380, 3382, 3382, 3384, 3384, 3385, 3386, 3386, 3386, 3387, 3387, 3387, 3388, 3388, 3389, 3390, 3389, 3390, 3390, 3389, 3390, 3391, 3390, 3391, 3391, 3390, 3390, 3391, 3391, 3390};
        std::array<uint16_t, 512> bVec = {1683, 1687, 1696, 1703, 1708, 1712, 1718, 1724, 1727, 1730, 1735, 1740, 1745, 1751, 1755, 1760, 1764, 1770, 1773, 1776, 1778, 1781, 1784, 1789, 1793, 1796, 1798, 1801, 1802, 1806, 1809, 1811, 1813, 1816, 1818, 1819, 1822, 1824, 1826, 1827, 1829, 1831, 1831, 1833, 1834, 1835, 1836, 1836, 1837, 1837, 1837, 1837, 1837, 1836, 1836, 1834, 1835, 1836, 1835, 1834, 1832, 1831, 1832, 1830, 1829, 1829, 1827, 1826, 1824, 1823, 1823, 1820, 1819, 1817, 1816, 1814, 1812, 1811, 1809, 1807, 1805, 1804, 1802, 1799, 1796, 1795, 1794, 1791, 1789, 1786, 1783, 1780, 1778, 1775, 1771, 1767, 1766, 1764, 1759, 1756, 1754, 1751, 1748, 1745, 1742, 1739, 1735, 1733, 1729, 1726, 1723, 1721, 1714, 1710, 1708, 1706, 1703, 1700, 1698, 1696, 1689, 1686, 1681, 1677, 1674, 1670, 1670, 1666, 1662, 1660, 1659, 1654, 1650, 1647, 1645, 1639, 1636, 1634, 1631, 1628, 1625, 1623, 1618, 1615, 1611, 1607, 1601, 1597, 1591, 1588, 1584, 1580, 1577, 1573, 1568, 1562, 1558, 1553, 1548, 1541, 1537, 1533, 1530, 1527, 1521, 1517, 1512, 1504, 1496, 1491, 1487, 1481, 1477, 1473, 1466, 1464, 1459, 1455, 1444, 1432, 1427, 1420, 1413, 1409, 1405, 1400, 1396, 1390, 1385, 1380, 1372, 1364, 1359, 1354, 1348, 1344, 1340, 1331, 1326, 1317, 1309, 1304, 1299, 1291, 1284, 1279, 1272, 1268, 1260, 1252, 1246, 1238, 1232, 1224, 1218, 1213, 1200, 1193, 1188, 1181, 1173, 1167, 1161, 1152, 1140, 1132, 1126, 1120, 1112, 1107, 1101, 1093, 1085, 1079, 1072, 1064, 1058, 1054, 1048, 1040, 1035, 1033, 1030, 1024, 1019, 1014, 1004, 999, 994, 988, 982, 977, 970, 962, 958, 951, 946, 941, 936, 931, 927, 922, 918, 913, 909, 898, 892, 887, 882, 877, 868, 864, 861, 857, 852, 849, 846, 840, 836, 832, 827, 823, 815, 812, 808, 804, 800, 797, 793, 789, 786, 782, 777, 774, 770, 766, 764, 759, 757, 755, 754, 752, 750, 746, 743, 742, 740, 738, 737, 735, 734, 732, 729, 728, 726, 726, 725, 723, 723, 722, 721, 721, 719, 719, 720, 719, 718, 716, 717, 715, 715, 716, 716, 715, 716, 716, 715, 716, 716, 715, 715, 716, 716, 717, 716, 718, 720, 720, 720, 722, 722, 722, 725, 726, 728, 731, 732, 734, 736, 738, 740, 742, 744, 745, 748, 750, 753, 755, 756, 758, 760, 762, 766, 768, 769, 772, 776, 780, 784, 784, 788, 794, 798, 803, 808, 812, 818, 821, 827, 830, 837, 839, 842, 849, 855, 861, 868, 873, 877, 882, 891, 896, 900, 906, 914, 920, 927, 933, 940, 946, 954, 962, 977, 982, 987, 996, 1007, 1016, 1029, 1036, 1047, 1057, 1062, 1072, 1079, 1086, 1094, 1101, 1110, 1116, 1122, 1131, 1141, 1153, 1160, 1165, 1170, 1176, 1190, 1199, 1211, 1220, 1230, 1238, 1246, 1251, 1261, 1271, 1277, 1285, 1291, 1296, 1301, 1306, 1313, 1323, 1331, 1336, 1342, 1347, 1355, 1364, 1370, 1376, 1384, 1391, 1397, 1403, 1410, 1415, 1421, 1430, 1435, 1443, 1450, 1458, 1466, 1474, 1479, 1484, 1488, 1495, 1502, 1509, 1520, 1527, 1537, 1542, 1548, 1555, 1558, 1564, 1566, 1571, 1576, 1582, 1587, 1593, 1599, 1606, 1616, 1619, 1622, 1627, 1629, 1634, 1641, 1646, 1652, 1660, 1664, 1669};
        return std::make_unique<OpticalEncoderHandler>(aVec, bVec, A4, A5, 4096.0 * mainEncoderGearRatio);
    }

    static std::unique_ptr<EncoderHandlerInterface> createOutputEncoderHandler()
    {
        std::array<int16_t, 32> compVec = {71, 71, 71, 70, 76, 79, 74, 66, 67, 64, 55, 50, 36, 22, 16, 13, 0, -13, -22, -39, -58, -69, -78, -77, -78, -80, -83, -81, -74, -63, -49, -36};
        return std::make_unique<ResistiveEncoderHandler>(A3, 4096.0 * 200.0 / 360.0, compVec);
    }

    static std::unique_ptr<CurrentController> createCurrentController()
    {
        constexpr float pwmToStallCurrent{1.0};
        constexpr float backEmfCurrent{0.0001538331760438727};

        return std::make_unique<CurrentControlModel>(pwmToStallCurrent, backEmfCurrent, std::make_unique<HBridge2WirePwm>(3, 4));
    }

    class ControlParameters : public SetupConfigHolder::DefaultControlParameters
    {
      public:
        //kalman filter observer vector
        static Eigen::Vector3f getKVector()
        {
            Eigen::Vector3f K;
            K << 2.0040734732795924,
                487.05380054424984,
                331.65594286687923;

            return K;
        }

        //system model A matrix
        static Eigen::Matrix3f getAMatrix()
        {
            Eigen::Matrix3f A;
            A << 1.0, 0.0024, 0.00046093594172144956,
                0.0, 0.9743532960026547, 0.38411328476787465,
                0.0, 0.0, 1.0;

            return A;
        }

        //system model invers A matrix
        static Eigen::Matrix3f getAInvMatrix()
        {
            Eigen::Matrix3f AInv;
            AInv << 1.0, -0.0024631722495794387, 0.0004852012420135838,
                0.0, 1.0263217706580996, -0.3942238265562639,
                0.0, 0.0, 1.0;

            return AInv;
        }

        //system model B matrix
        static Eigen::Vector3f getBVector()
        {
            Eigen::Vector3f B;
            B << 0.00046093594172144956,
                0.38411328476787465,
                0.0;

            return B;
        }

        //system model friction comp value
        static float getFrictionComp()
        {
            return 72.96369247808231;
        }
    };
};
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

class ConfigHolder
{
public:
    static std::unique_ptr<Communication> getCommunicationHandler()
    {
        auto com = std::make_unique<Communication>(&Serial1, 115200);
        com->addCommunicationNode(
                std::make_unique<DCServoCommunicationHandler>(4, createDCServo<SetupConfigHolder>()));
        com->addCommunicationNode(
                std::make_unique<DCServoCommunicationHandler>(5, createDCServo<SetupConfigHolder2>()));

        return com;
    }
};

#endif
