#include"Drone.h"

/*
	���ܺ����ļ�, ������ʹ�� Q-learning �㷨�����˻�����ѵ������֤�ķ���.
*/


// ��ȡ��ͼ�������ϰ������ vector ������
void getBarrList(std::vector<Barrier>& vecBarr, msr::airlib::MultirotorRpcLibClient& client);

// ��ȡ��ͼ������·�������� vector ������
void getRouterList(std::vector<Router>& vecRouter, msr::airlib::MultirotorRpcLibClient& client);

// ����ÿ��·����, ����һ���������Ľ�������, ���� vector ������
void getRewardMatrixList(std::vector<RewardMatrix>& vecRewardMatrix, std::vector<Router>& vecRoute, std::vector<Barrier>& vecBarr);

// ����ÿ��·����, ����һ���������� Q-Table, ���� vector ������
void getQMatrixList(std::vector<QMatrix>& vecQMatrix, int lenRouter);

// �����ͼ�е������ϰ����·����, �Լ����Ƕ�Ӧ�Ľ�������� Q-Table, �Լ����˻�, ����ѵ��
void train(std::vector<Barrier>& vecBarr, std::vector<Router>& vecRouter,
	std::vector<RewardMatrix>& vecRewardMatrix, std::vector<QMatrix>& vecQMatrix, Drone& drone, msr::airlib::MultirotorRpcLibClient& client);

// ���˻����� Q-Table ѡ����ѵ�·��
int getOptimalRoute(QMatrix& qMatrix, Drone& drone, Router& router, int startState, int startAltitude, msr::airlib::MultirotorRpcLibClient& client);

// �����ͼ�е�����·����, �Լ����Ƕ�Ӧ�� Q-Table, �Լ����˻�, ������֤, ���ͨ�� Airsim API �� UE4 ������չʾ
void validate(std::vector<QMatrix>& vecQMatrix, std::vector<Router> vecRouter, Drone& drone, msr::airlib::MultirotorRpcLibClient& client);