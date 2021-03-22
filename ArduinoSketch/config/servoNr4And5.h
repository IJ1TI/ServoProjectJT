#ifndef CONFIG_HOLDER_H
#define CONFIG_HOLDER_H

#include "../defaultConfigHolder.h"
#include "../ResistiveEncoderHandler.h"
#include "../DCServo.h"

// replace with gear ratio from motor to output
constexpr float mainEncoderGearRatio{10.0 / 48.0 * 10.0 / 38.0 * 10.0 / 38.0 * 10.0 / 38.0};

std::array<uint16_t, 512> pwmHighFrqCompLookup = {0, 129, 161, 209, 241, 265, 289, 313, 337, 353, 377, 393, 409, 425, 441, 457, 473, 489, 505, 513, 529, 545, 553, 569, 581, 593, 601, 617, 625, 637, 649, 657, 669, 679, 679, 679, 683, 683, 683, 683, 683, 683, 687, 687, 687, 687, 687, 689, 691, 691, 691, 691, 691, 693, 695, 695, 695, 695, 695, 699, 699, 699, 699, 699, 699, 703, 703, 703, 703, 703, 705, 707, 707, 707, 707, 707, 711, 711, 711, 711, 711, 711, 715, 715, 715, 715, 715, 717, 719, 719, 719, 719, 719, 721, 723, 723, 723, 723, 723, 727, 727, 727, 727, 727, 729, 731, 731, 731, 731, 731, 733, 735, 735, 735, 735, 735, 739, 739, 739, 739, 739, 741, 743, 743, 743, 743, 743, 745, 747, 747, 747, 747, 747, 751, 751, 751, 751, 751, 753, 755, 755, 755, 755, 755, 757, 759, 759, 759, 759, 759, 763, 763, 763, 763, 763, 765, 767, 767, 767, 767, 767, 771, 771, 771, 771, 771, 771, 775, 775, 775, 775, 775, 777, 779, 779, 779, 779, 779, 783, 783, 783, 783, 783, 785, 787, 787, 787, 787, 787, 789, 791, 791, 791, 791, 791, 795, 795, 795, 795, 795, 797, 799, 799, 799, 799, 799, 803, 803, 803, 803, 803, 805, 807, 807, 807, 807, 807, 809, 811, 811, 811, 811, 811, 815, 815, 815, 815, 815, 817, 819, 819, 819, 819, 819, 823, 823, 823, 823, 823, 825, 827, 827, 827, 827, 827, 831, 831, 831, 831, 831, 833, 835, 835, 835, 835, 835, 837, 839, 839, 839, 839, 839, 843, 843, 843, 843, 843, 845, 847, 847, 847, 847, 847, 851, 851, 851, 851, 851, 853, 855, 855, 855, 855, 855, 859, 859, 859, 859, 859, 861, 863, 863, 863, 863, 863, 867, 867, 867, 867, 867, 869, 871, 871, 871, 871, 871, 875, 875, 875, 875, 875, 877, 879, 879, 879, 879, 879, 883, 883, 883, 883, 883, 885, 887, 887, 887, 887, 887, 891, 891, 891, 891, 891, 893, 895, 895, 895, 895, 895, 899, 899, 899, 899, 899, 901, 903, 903, 903, 903, 903, 907, 907, 907, 907, 907, 909, 911, 911, 911, 911, 911, 915, 915, 915, 915, 915, 917, 919, 919, 919, 919, 919, 923, 923, 923, 923, 923, 925, 927, 927, 927, 927, 927, 931, 931, 931, 931, 931, 933, 935, 935, 935, 935, 935, 939, 939, 939, 939, 939, 943, 943, 943, 943, 943, 945, 947, 947, 947, 947, 947, 951, 951, 951, 951, 951, 953, 955, 955, 955, 955, 955, 959, 959, 959, 959, 959, 961, 963, 963, 963, 963, 963, 967, 967, 967, 967, 967, 971, 971, 971, 971, 971, 973, 975, 975, 975, 975, 975, 979, 979, 979, 979, 979, 981, 983, 983, 983, 983, 983, 987, 987, 987, 987, 987, 991, 991, 991, 991, 991, 993, 995, 995, 995, 995, 995, 999, 999, 999, 999, 999, 1001, 1003, 1003, 1003, 1003, 1005, 1007, 1007, 1007, 1007, 1007, 1011, 1011, 1011, 1011, 1011, 1013, 1015, 1015, 1015, 1015, 1015, 1019, 1019, 1019, 1019, 1019, 1023, 1023, 1023, 1023, 1023};

uint16_t pwmHighFrqComp(uint16_t in)
{
    return pwmHighFrqCompLookup[in / 2];
}

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
        std::array<uint16_t, 512> aVec = {3254, 3254, 3256, 3258, 3259, 3261, 3262, 3263, 3264, 3265, 3266, 3267, 3268, 3269, 3270, 3271, 3272, 3272, 3273, 3274, 3275, 3275, 3276, 3277, 3277, 3277, 3278, 3278, 3278, 3279, 3279, 3279, 3279, 3280, 3280, 3279, 3279, 3279, 3279, 3279, 3279, 3279, 3279, 3278, 3278, 3277, 3276, 3276, 3275, 3275, 3274, 3274, 3273, 3272, 3271, 3271, 3270, 3269, 3268, 3267, 3266, 3265, 3264, 3262, 3261, 3260, 3258, 3257, 3256, 3255, 3253, 3251, 3250, 3248, 3247, 3245, 3244, 3242, 3240, 3238, 3237, 3236, 3234, 3233, 3231, 3229, 3226, 3225, 3223, 3220, 3218, 3216, 3214, 3212, 3210, 3207, 3205, 3202, 3200, 3197, 3194, 3191, 3188, 3185, 3182, 3179, 3176, 3174, 3170, 3167, 3164, 3159, 3156, 3152, 3149, 3144, 3141, 3137, 3133, 3130, 3126, 3122, 3118, 3114, 3109, 3104, 3100, 3095, 3091, 3086, 3082, 3078, 3074, 3070, 3065, 3060, 3055, 3050, 3045, 3041, 3036, 3032, 3027, 3022, 3016, 3011, 3006, 3001, 2996, 2992, 2986, 2981, 2975, 2970, 2965, 2959, 2953, 2948, 2943, 2938, 2933, 2927, 2921, 2914, 2908, 2903, 2897, 2891, 2885, 2880, 2875, 2869, 2863, 2856, 2850, 2846, 2840, 2833, 2828, 2822, 2817, 2810, 2804, 2799, 2792, 2786, 2780, 2775, 2770, 2763, 2757, 2751, 2746, 2741, 2736, 2729, 2723, 2719, 2713, 2707, 2702, 2696, 2692, 2687, 2681, 2675, 2671, 2665, 2659, 2654, 2650, 2645, 2639, 2633, 2627, 2622, 2616, 2611, 2606, 2601, 2595, 2589, 2584, 2578, 2572, 2566, 2561, 2556, 2552, 2546, 2540, 2535, 2531, 2524, 2518, 2512, 2507, 2503, 2498, 2495, 2490, 2486, 2481, 2477, 2473, 2468, 2464, 2460, 2457, 2453, 2449, 2446, 2443, 2440, 2437, 2433, 2429, 2427, 2423, 2421, 2418, 2416, 2413, 2412, 2410, 2408, 2405, 2403, 2402, 2400, 2398, 2397, 2395, 2394, 2393, 2392, 2390, 2389, 2388, 2387, 2386, 2386, 2385, 2384, 2384, 2383, 2383, 2382, 2382, 2381, 2381, 2381, 2380, 2380, 2380, 2380, 2380, 2380, 2381, 2381, 2382, 2382, 2383, 2384, 2385, 2386, 2387, 2388, 2390, 2392, 2393, 2395, 2396, 2398, 2400, 2401, 2403, 2406, 2408, 2411, 2414, 2417, 2419, 2422, 2425, 2428, 2432, 2435, 2438, 2443, 2446, 2451, 2455, 2459, 2463, 2467, 2471, 2475, 2479, 2485, 2490, 2496, 2500, 2504, 2509, 2514, 2520, 2525, 2530, 2535, 2542, 2548, 2553, 2559, 2565, 2571, 2577, 2582, 2587, 2591, 2598, 2605, 2611, 2618, 2625, 2631, 2638, 2644, 2649, 2653, 2660, 2667, 2673, 2681, 2686, 2692, 2699, 2705, 2711, 2716, 2723, 2728, 2736, 2742, 2747, 2754, 2760, 2765, 2772, 2777, 2785, 2791, 2795, 2800, 2807, 2812, 2819, 2823, 2830, 2837, 2843, 2848, 2853, 2858, 2864, 2868, 2876, 2883, 2889, 2894, 2899, 2905, 2911, 2916, 2921, 2927, 2932, 2938, 2943, 2949, 2954, 2959, 2964, 2968, 2974, 2980, 2985, 2990, 2995, 3000, 3005, 3009, 3013, 3017, 3023, 3028, 3032, 3037, 3041, 3046, 3050, 3054, 3058, 3062, 3066, 3069, 3071, 3076, 3081, 3085, 3089, 3093, 3097, 3100, 3103, 3106, 3111, 3114, 3118, 3122, 3126, 3130, 3134, 3137, 3140, 3143, 3146, 3149, 3154, 3158, 3161, 3164, 3167, 3170, 3173, 3176, 3178, 3182, 3184, 3187, 3191, 3192, 3196, 3198, 3200, 3204, 3206, 3208, 3210, 3212, 3214, 3216, 3218, 3221, 3223, 3225, 3226, 3228, 3230, 3233, 3234, 3236, 3238, 3239, 3241, 3242, 3244, 3245, 3247, 3248, 3249, 3251};
        std::array<uint16_t, 512> bVec = {2942, 2945, 2951, 2957, 2962, 2966, 2970, 2974, 2977, 2981, 2985, 2988, 2992, 2995, 2998, 3001, 3004, 3006, 3008, 3011, 3014, 3017, 3020, 3022, 3024, 3026, 3028, 3030, 3032, 3034, 3036, 3037, 3039, 3041, 3043, 3045, 3046, 3048, 3049, 3051, 3052, 3054, 3055, 3057, 3058, 3060, 3061, 3062, 3064, 3065, 3066, 3067, 3067, 3068, 3069, 3070, 3071, 3072, 3072, 3073, 3073, 3074, 3074, 3074, 3075, 3075, 3075, 3075, 3075, 3075, 3075, 3075, 3075, 3075, 3075, 3075, 3074, 3074, 3074, 3073, 3073, 3073, 3072, 3072, 3071, 3071, 3071, 3070, 3070, 3069, 3068, 3068, 3067, 3066, 3066, 3065, 3065, 3064, 3063, 3063, 3061, 3061, 3060, 3059, 3058, 3058, 3057, 3057, 3056, 3055, 3055, 3054, 3053, 3052, 3051, 3050, 3049, 3048, 3047, 3047, 3046, 3045, 3044, 3042, 3042, 3040, 3039, 3038, 3037, 3035, 3034, 3033, 3032, 3030, 3029, 3027, 3026, 3024, 3023, 3021, 3020, 3018, 3017, 3015, 3013, 3011, 3009, 3007, 3006, 3004, 3002, 3000, 2997, 2995, 2993, 2991, 2988, 2987, 2985, 2983, 2981, 2978, 2976, 2973, 2971, 2969, 2967, 2964, 2962, 2960, 2957, 2955, 2952, 2949, 2947, 2945, 2943, 2939, 2937, 2934, 2932, 2929, 2926, 2924, 2921, 2918, 2915, 2912, 2910, 2906, 2903, 2900, 2897, 2895, 2892, 2888, 2885, 2882, 2880, 2876, 2873, 2870, 2868, 2864, 2861, 2858, 2855, 2852, 2849, 2846, 2843, 2840, 2837, 2833, 2830, 2826, 2823, 2819, 2816, 2813, 2809, 2805, 2801, 2798, 2794, 2790, 2786, 2783, 2780, 2776, 2772, 2769, 2765, 2760, 2756, 2751, 2747, 2743, 2739, 2736, 2732, 2729, 2725, 2721, 2716, 2712, 2708, 2704, 2700, 2696, 2692, 2688, 2685, 2681, 2678, 2672, 2667, 2663, 2659, 2655, 2651, 2647, 2643, 2639, 2637, 2633, 2628, 2623, 2619, 2615, 2611, 2606, 2602, 2599, 2595, 2590, 2586, 2581, 2577, 2572, 2567, 2563, 2559, 2554, 2549, 2545, 2540, 2535, 2531, 2525, 2520, 2515, 2511, 2507, 2502, 2497, 2493, 2489, 2484, 2479, 2474, 2469, 2464, 2459, 2454, 2450, 2446, 2441, 2435, 2430, 2426, 2420, 2416, 2412, 2408, 2404, 2399, 2394, 2389, 2383, 2378, 2374, 2369, 2365, 2360, 2356, 2351, 2346, 2342, 2336, 2332, 2327, 2323, 2318, 2314, 2311, 2307, 2303, 2300, 2295, 2290, 2286, 2283, 2280, 2277, 2274, 2270, 2267, 2265, 2262, 2260, 2258, 2256, 2253, 2251, 2249, 2247, 2246, 2245, 2244, 2242, 2241, 2240, 2239, 2237, 2237, 2236, 2236, 2235, 2235, 2235, 2235, 2236, 2236, 2237, 2237, 2238, 2239, 2240, 2241, 2242, 2243, 2244, 2246, 2247, 2249, 2250, 2252, 2253, 2255, 2257, 2259, 2261, 2262, 2265, 2267, 2269, 2271, 2273, 2277, 2279, 2282, 2285, 2288, 2291, 2293, 2297, 2302, 2305, 2308, 2312, 2316, 2319, 2323, 2327, 2331, 2335, 2339, 2343, 2348, 2352, 2357, 2361, 2365, 2371, 2376, 2382, 2387, 2392, 2399, 2405, 2409, 2415, 2420, 2428, 2435, 2441, 2447, 2453, 2461, 2468, 2473, 2480, 2487, 2493, 2499, 2503, 2512, 2521, 2528, 2536, 2543, 2551, 2557, 2564, 2570, 2578, 2585, 2594, 2601, 2610, 2619, 2625, 2632, 2639, 2646, 2654, 2660, 2671, 2679, 2687, 2695, 2702, 2710, 2718, 2724, 2729, 2739, 2745, 2755, 2762, 2768, 2776, 2783, 2788, 2797, 2803, 2810, 2815, 2822, 2829, 2834, 2840, 2847, 2852, 2858, 2863, 2869, 2875, 2880, 2884, 2889, 2894, 2898, 2903, 2907, 2912, 2916, 2921, 2925, 2930, 2935};
        return std::make_unique<OpticalEncoderHandler>(aVec, bVec, A1, A2, 4096.0 * mainEncoderGearRatio1);
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
        std::array<uint16_t, 512> aVec = {2896, 2897, 2898, 2899, 2900, 2901, 2902, 2903, 2904, 2905, 2906, 2907, 2909, 2910, 2911, 2912, 2913, 2915, 2916, 2917, 2918, 2919, 2921, 2922, 2924, 2925, 2927, 2929, 2930, 2931, 2933, 2934, 2936, 2938, 2939, 2941, 2942, 2944, 2946, 2948, 2950, 2952, 2953, 2956, 2957, 2959, 2960, 2962, 2964, 2966, 2968, 2970, 2973, 2975, 2978, 2980, 2982, 2985, 2987, 2989, 2991, 2993, 2996, 2998, 3000, 3002, 3004, 3007, 3010, 3012, 3014, 3017, 3019, 3021, 3023, 3026, 3029, 3032, 3034, 3036, 3038, 3041, 3043, 3045, 3048, 3050, 3053, 3055, 3058, 3060, 3062, 3064, 3067, 3069, 3071, 3074, 3076, 3078, 3081, 3084, 3086, 3088, 3091, 3093, 3096, 3098, 3100, 3102, 3104, 3107, 3110, 3113, 3115, 3118, 3120, 3123, 3126, 3128, 3130, 3132, 3133, 3136, 3138, 3140, 3143, 3145, 3147, 3149, 3151, 3153, 3155, 3157, 3160, 3161, 3163, 3165, 3167, 3170, 3171, 3173, 3175, 3177, 3180, 3182, 3184, 3187, 3189, 3191, 3194, 3196, 3198, 3199, 3202, 3204, 3205, 3207, 3209, 3211, 3212, 3214, 3216, 3218, 3220, 3221, 3223, 3224, 3226, 3227, 3229, 3231, 3232, 3234, 3236, 3238, 3239, 3241, 3243, 3244, 3246, 3247, 3248, 3249, 3251, 3252, 3253, 3254, 3256, 3257, 3258, 3260, 3261, 3262, 3263, 3263, 3264, 3266, 3267, 3268, 3269, 3269, 3270, 3271, 3272, 3272, 3273, 3274, 3274, 3275, 3276, 3277, 3277, 3277, 3278, 3278, 3279, 3279, 3280, 3280, 3280, 3281, 3281, 3281, 3282, 3282, 3283, 3283, 3283, 3283, 3283, 3283, 3284, 3284, 3284, 3284, 3284, 3283, 3283, 3284, 3283, 3283, 3283, 3283, 3283, 3283, 3282, 3282, 3282, 3281, 3281, 3281, 3280, 3280, 3279, 3279, 3278, 3278, 3277, 3277, 3276, 3275, 3275, 3274, 3273, 3272, 3271, 3270, 3269, 3268, 3267, 3266, 3265, 3264, 3263, 3262, 3261, 3260, 3259, 3258, 3256, 3255, 3254, 3253, 3251, 3249, 3248, 3247, 3246, 3244, 3242, 3241, 3239, 3238, 3237, 3235, 3234, 3232, 3230, 3228, 3227, 3225, 3223, 3222, 3220, 3219, 3217, 3215, 3213, 3212, 3210, 3208, 3206, 3205, 3203, 3201, 3199, 3196, 3194, 3193, 3190, 3188, 3187, 3185, 3182, 3180, 3178, 3175, 3173, 3171, 3169, 3166, 3164, 3162, 3160, 3157, 3155, 3153, 3151, 3148, 3146, 3143, 3140, 3138, 3135, 3133, 3130, 3127, 3125, 3123, 3120, 3116, 3113, 3111, 3108, 3105, 3102, 3099, 3096, 3093, 3090, 3088, 3086, 3083, 3081, 3079, 3076, 3073, 3071, 3068, 3065, 3063, 3060, 3057, 3054, 3051, 3049, 3046, 3044, 3042, 3039, 3037, 3035, 3033, 3030, 3028, 3025, 3023, 3020, 3017, 3014, 3012, 3009, 3007, 3004, 3001, 2999, 2997, 2995, 2993, 2990, 2988, 2986, 2984, 2982, 2979, 2976, 2974, 2972, 2969, 2967, 2964, 2963, 2960, 2958, 2956, 2955, 2953, 2951, 2948, 2947, 2945, 2943, 2941, 2939, 2937, 2936, 2934, 2933, 2931, 2929, 2928, 2926, 2925, 2924, 2922, 2920, 2919, 2918, 2917, 2915, 2914, 2912, 2911, 2909, 2908, 2906, 2905, 2904, 2902, 2902, 2901, 2899, 2898, 2897, 2896, 2895, 2894, 2893, 2892, 2891, 2891, 2890, 2890, 2889, 2888, 2888, 2887, 2887, 2886, 2886, 2886, 2885, 2885, 2884, 2884, 2883, 2883, 2884, 2883, 2883, 2883, 2883, 2882, 2883, 2882, 2882, 2883, 2883, 2883, 2883, 2884, 2884, 2884, 2884, 2885, 2885, 2886, 2886, 2886, 2886, 2887, 2888, 2888, 2889, 2890, 2890, 2891, 2892, 2892, 2893, 2894, 2895, 2896};
        std::array<uint16_t, 512> bVec = {2669, 2671, 2675, 2678, 2681, 2684, 2688, 2691, 2695, 2699, 2703, 2707, 2711, 2715, 2718, 2721, 2724, 2728, 2731, 2735, 2738, 2741, 2744, 2748, 2752, 2756, 2760, 2765, 2768, 2771, 2774, 2778, 2782, 2786, 2789, 2793, 2796, 2800, 2805, 2809, 2812, 2816, 2819, 2822, 2826, 2829, 2833, 2836, 2839, 2842, 2845, 2849, 2852, 2856, 2860, 2863, 2867, 2870, 2873, 2876, 2879, 2883, 2886, 2889, 2891, 2894, 2897, 2900, 2903, 2905, 2908, 2910, 2913, 2915, 2918, 2921, 2923, 2926, 2928, 2930, 2932, 2934, 2936, 2938, 2941, 2943, 2945, 2947, 2949, 2951, 2953, 2955, 2957, 2959, 2961, 2963, 2965, 2966, 2968, 2971, 2973, 2975, 2977, 2979, 2981, 2982, 2984, 2986, 2988, 2990, 2992, 2994, 2996, 2998, 3000, 3002, 3004, 3006, 3007, 3009, 3010, 3012, 3014, 3016, 3017, 3019, 3021, 3022, 3023, 3025, 3027, 3028, 3030, 3031, 3032, 3034, 3035, 3037, 3038, 3039, 3040, 3041, 3043, 3044, 3045, 3046, 3048, 3049, 3050, 3051, 3052, 3053, 3054, 3055, 3056, 3057, 3057, 3058, 3059, 3059, 3060, 3060, 3061, 3061, 3061, 3062, 3062, 3062, 3063, 3063, 3063, 3063, 3063, 3064, 3063, 3064, 3064, 3064, 3064, 3064, 3063, 3063, 3064, 3063, 3063, 3063, 3062, 3062, 3061, 3061, 3060, 3059, 3059, 3058, 3057, 3056, 3055, 3054, 3053, 3052, 3051, 3049, 3048, 3047, 3046, 3045, 3043, 3042, 3040, 3039, 3037, 3035, 3033, 3032, 3030, 3029, 3027, 3025, 3023, 3021, 3019, 3017, 3016, 3013, 3011, 3009, 3006, 3005, 3003, 3001, 2998, 2996, 2994, 2991, 2989, 2987, 2985, 2982, 2980, 2978, 2975, 2973, 2970, 2968, 2965, 2963, 2960, 2957, 2954, 2952, 2949, 2947, 2944, 2942, 2939, 2937, 2934, 2932, 2930, 2927, 2924, 2921, 2917, 2914, 2912, 2909, 2906, 2903, 2900, 2897, 2894, 2891, 2888, 2885, 2882, 2878, 2875, 2871, 2868, 2864, 2861, 2858, 2855, 2850, 2848, 2845, 2842, 2838, 2834, 2830, 2827, 2824, 2820, 2816, 2812, 2808, 2804, 2800, 2796, 2793, 2789, 2786, 2782, 2779, 2775, 2771, 2768, 2764, 2761, 2758, 2755, 2751, 2747, 2744, 2739, 2735, 2732, 2728, 2724, 2720, 2717, 2714, 2710, 2706, 2702, 2698, 2695, 2691, 2686, 2683, 2679, 2676, 2673, 2668, 2665, 2662, 2659, 2655, 2651, 2647, 2643, 2640, 2637, 2633, 2629, 2626, 2623, 2620, 2617, 2613, 2609, 2605, 2602, 2599, 2595, 2592, 2588, 2585, 2582, 2580, 2577, 2574, 2572, 2569, 2567, 2564, 2561, 2559, 2556, 2553, 2552, 2549, 2546, 2544, 2542, 2540, 2538, 2536, 2534, 2533, 2531, 2529, 2528, 2526, 2525, 2523, 2522, 2520, 2518, 2517, 2516, 2515, 2514, 2513, 2512, 2511, 2510, 2509, 2508, 2507, 2507, 2506, 2505, 2504, 2504, 2503, 2503, 2502, 2502, 2501, 2501, 2501, 2500, 2500, 2500, 2499, 2500, 2499, 2499, 2499, 2499, 2499, 2499, 2499, 2500, 2500, 2500, 2501, 2501, 2501, 2502, 2503, 2504, 2502, 2504, 2503, 2504, 2504, 2504, 2504, 2505, 2505, 2505, 2505, 2506, 2507, 2507, 2508, 2509, 2510, 2511, 2512, 2514, 2515, 2517, 2518, 2520, 2522, 2524, 2526, 2528, 2530, 2532, 2533, 2536, 2538, 2541, 2543, 2545, 2547, 2549, 2551, 2553, 2556, 2558, 2560, 2562, 2564, 2567, 2569, 2572, 2576, 2578, 2581, 2583, 2586, 2588, 2592, 2595, 2599, 2602, 2604, 2607, 2609, 2612, 2615, 2618, 2621, 2624, 2627, 2631, 2634, 2637, 2640, 2643, 2647, 2649, 2652, 2655, 2659, 2662, 2663};
        return std::make_unique<OpticalEncoderHandler>(aVec, bVec, A4, A5, -4096.0 * mainEncoderGearRatio2);
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
