#ifndef CONSTANTS_H
#define CONSTANTS_H

/*
    ������һ����Ϊ constants �������ռ����Դ洢�����õ��ĳ���.
*/


// define your own namespace to hold constants
namespace constants
{
    // �߶������ϰ������
    inline constexpr int num_high = 2;
    // �߶��еȵ��ϰ������
    inline constexpr int num_medium = 8;
    // �߶���С���ϰ������
    inline constexpr int num_low = 2;
    // ·�����ĸ���
    inline constexpr int num_router = 5;

    // ��-greedy ���Եĳ���
    inline constexpr double epsilon_max = 1.0;
    inline constexpr double epsilon_min = 0.01;
    inline constexpr double epsilon_decay_rate = 0.9993;

    // Q-learning �㷨�ĳ���
    inline constexpr double gamma = 0.9;  
    inline constexpr double alpha = 0.01;

    // ��ͼ���ӵ�����, Ҳ�����˻�ƽ��λ�����������
    inline constexpr int num_states = 49;
    // ���˻����Բ�ȡ�� 6 �ַ��ж���
    inline constexpr int num_actions = 6;
    // ���˻����Բ�ȡ�� 3 �ַ��и߶�
    inline constexpr int num_altitudes = 3;

    // ���˻���ȼ������, Ҳ������ѵ��ʱ���˻����Խ��е����Ĳ���
    inline constexpr int num_steps_in_episode = 100;
    // ����ÿ��·����ѵ�����˻������� 
    inline constexpr int num_episodes = 2000;

    inline constexpr double min_number = -1e5;
    inline constexpr double pi = 3.14159;
    // ����
    inline constexpr int c = 299792458;
    // ˥�����ʼ��㳣��
    inline constexpr double n_los = 1.0, n_nlos = 20.0;
    inline const double a = 9.61, b = 0.16;
    // �ز�Ƶ��
    inline constexpr int carrier_freq = 2412000000;  // Hz
    // ��ʼ���书��
    inline constexpr int transmit_p = 5; // W
    // �ŵ�����
    inline constexpr int bandwidth = 2000000; // Hz
    // ƽ����������
    inline constexpr int noise = -90; // dBm
}
#endif
