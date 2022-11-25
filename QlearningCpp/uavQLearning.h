#include"Drone.h"

/*
	功能函数文件, 定义了使用 Q-learning 算法对无人机进行训练和验证的方法.
*/


// 获取地图中所有障碍物存入 vector 数组中
void getBarrList(std::vector<Barrier>& vecBarr, msr::airlib::MultirotorRpcLibClient& client);

// 获取地图中所有路由器存入 vector 数组中
void getRouterList(std::vector<Router>& vecRouter, msr::airlib::MultirotorRpcLibClient& client);

// 对于每个路由器, 建立一个关于它的奖励矩阵, 存入 vector 数组中
void getRewardMatrixList(std::vector<RewardMatrix>& vecRewardMatrix, std::vector<Router>& vecRoute, std::vector<Barrier>& vecBarr);

// 对于每个路由器, 建立一个关于它的 Q-Table, 存入 vector 数组中
void getQMatrixList(std::vector<QMatrix>& vecQMatrix, int lenRouter);

// 传入地图中的所有障碍物和路由器, 以及它们对应的奖励矩阵和 Q-Table, 以及无人机, 进行训练
void train(std::vector<Barrier>& vecBarr, std::vector<Router>& vecRouter,
	std::vector<RewardMatrix>& vecRewardMatrix, std::vector<QMatrix>& vecQMatrix, Drone& drone, msr::airlib::MultirotorRpcLibClient& client);

// 无人机根据 Q-Table 选择最佳的路径
int getOptimalRoute(QMatrix& qMatrix, Drone& drone, Router& router, int startState, int startAltitude, msr::airlib::MultirotorRpcLibClient& client);

// 传入地图中的所有路由器, 以及它们对应的 Q-Table, 以及无人机, 进行验证, 结果通过 Airsim API 在 UE4 引擎中展示
void validate(std::vector<QMatrix>& vecQMatrix, std::vector<Router> vecRouter, Drone& drone, msr::airlib::MultirotorRpcLibClient& client);