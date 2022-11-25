#ifndef CONSTANTS_H
#define CONSTANTS_H

/*
    创建了一个名为 constants 的命名空间用以存储所有用到的常量.
*/


// define your own namespace to hold constants
namespace constants
{
    // 高度最大的障碍物个数
    inline constexpr int num_high = 2;
    // 高度中等的障碍物个数
    inline constexpr int num_medium = 8;
    // 高度最小的障碍物个数
    inline constexpr int num_low = 2;
    // 路由器的个数
    inline constexpr int num_router = 5;

    // ε-greedy 策略的常数
    inline constexpr double epsilon_max = 1.0;
    inline constexpr double epsilon_min = 0.01;
    inline constexpr double epsilon_decay_rate = 0.9993;

    // Q-learning 算法的常数
    inline constexpr double gamma = 0.9;  
    inline constexpr double alpha = 0.01;

    // 地图格子的总数, 也即无人机平面位置坐标的总数
    inline constexpr int num_states = 49;
    // 无人机可以采取的 6 种飞行动作
    inline constexpr int num_actions = 6;
    // 无人机可以采取的 3 种飞行高度
    inline constexpr int num_altitudes = 3;

    // 无人机的燃料总量, 也即单次训练时无人机可以进行的最多的步数
    inline constexpr int num_steps_in_episode = 100;
    // 对于每个路由器训练无人机的轮数 
    inline constexpr int num_episodes = 2000;

    inline constexpr double min_number = -1e5;
    inline constexpr double pi = 3.14159;
    // 光速
    inline constexpr int c = 299792458;
    // 衰减比率计算常数
    inline constexpr double n_los = 1.0, n_nlos = 20.0;
    inline const double a = 9.61, b = 0.16;
    // 载波频段
    inline constexpr int carrier_freq = 2412000000;  // Hz
    // 初始传输功率
    inline constexpr int transmit_p = 5; // W
    // 信道带宽
    inline constexpr int bandwidth = 2000000; // Hz
    // 平均噪声功率
    inline constexpr int noise = -90; // dBm
}
#endif
