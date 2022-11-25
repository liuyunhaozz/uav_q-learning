#include"uavQLearning.h"


void getBarrList(std::vector<Barrier>& vecBarr, msr::airlib::MultirotorRpcLibClient& client) {
	for (int i = 0; i < constants::num_low; ++i) {
		Barrier barrier("low_barrier_" + std::to_string(i), 0, client);
		vecBarr.push_back(barrier);
	}
	for (int i = 0; i < constants::num_medium; ++i) {
		Barrier barrier("medium_barrier_" + std::to_string(i), 1, client);
		vecBarr.push_back(barrier);
	}
	for (int i = 0; i < constants::num_high; ++i) {
		Barrier barrier("high_barrier_" + std::to_string(i), 2, client);
		vecBarr.push_back(barrier);
	}
}

void getRouterList(std::vector<Router>& vecRouter, msr::airlib::MultirotorRpcLibClient& client) {
	for (int i = 0; i < constants::num_router; ++i) {
		Router router("route_" + std::to_string(i), client);
		vecRouter.push_back(router);
	}
}

void getRewardMatrixList(std::vector<RewardMatrix>& vecRewardMatrix, std::vector<Router>& vecRouter, std::vector<Barrier>& vecBarr) {
	int lenRouter = vecRouter.size();
	for (int i = 0; i < lenRouter; ++i) {
		RewardMatrix rewardMat;
		rewardMat.initReward(vecRouter[i], vecBarr);
		vecRewardMatrix.push_back(rewardMat);
	}
}


void getQMatrixList(std::vector<QMatrix>& vecQMatrix, int lenRouter) {
	for (int i = 0; i < lenRouter; ++i) {
		QMatrix qMat;
		vecQMatrix.push_back(qMat);
	}
}


void train(std::vector<Barrier>& vecBarr, std::vector<Router>& vecRouter,
	std::vector<RewardMatrix>& vecRewardMatrix, std::vector<QMatrix>& vecQMatrix, Drone& drone, msr::airlib::MultirotorRpcLibClient& client) {
	getBarrList(vecBarr, client);
	getRouterList(vecRouter, client);
	int lenRoute = vecRouter.size();
	getRewardMatrixList(vecRewardMatrix, vecRouter, vecBarr);
	getQMatrixList(vecQMatrix, lenRoute);

	// �� lenRoute ��·�����ֱ�ѵ����Ӧ�� Q-Table
	for (int i = 0; i < lenRoute; ++i) {
		double epsilon = constants::epsilon_max;
		Router route = vecRouter[i];
		// ����һ��ȷ����·����, ѵ�� num_episodes ��, ���˻�ÿ�ζ���������
		for (int episode = 0; episode < constants::num_episodes; ++episode) {
			drone.setStatus(0, 0, -1);
			// ������˻�ȼ��û�кľ�, ������һ������
			while (drone.getFuel()) {
				if (drone.getState() == route.getPosition()) {
					std::cout << "GOAL reached" << std::endl;
					break;
				}
				int currentState = drone.getState();
				int currentAltitude = drone.getAltitude();
				drone.chooseAction(vecQMatrix[i], epsilon);
				drone.updateState();
				drone.updateAltitude();
				drone.decreaseFuel();
				vecQMatrix[i].updateQMatrix(vecRewardMatrix[i], currentState, drone.getState(), currentAltitude, drone.getAltitude(), drone.getAction());
			}
			std::cout << "Episode " << episode + 1 << " " << "is done." << std::endl;
			if (epsilon >= constants::epsilon_min)
				epsilon = epsilon * constants::epsilon_decay_rate;
		}
		std::cout << "-------------------------------------------------------------" << std::endl;
		std::cout << "Route " << i + 1 << " " << "is done." << std::endl;
		// option to save qMatrix
	}
}

int getOptimalRoute(QMatrix& qMatrix, Drone& drone, Router& router, int startState, int startAltitude, msr::airlib::MultirotorRpcLibClient& client) {
	// ����ÿ��·����, ��ʼ�����˻���λ��
	drone.setStatus(startAltitude, startState, -1);
	if (drone.getAltitude() == 0)
		client.moveToZAsync(-5, 3)->waitOnLastTask();
	else if (drone.getAltitude() == 1)
		client.moveToZAsync(-12.5, 3)->waitOnLastTask();
	else if (drone.getAltitude() == 2)
		client.moveToZAsync(-20, 3)->waitOnLastTask();
	while (drone.getFuel()) {
		if (drone.getState() == router.getPosition()) {
			std::cout << "GOAL reached" << std::endl;
			break;
		}
		else
			drone.chooseAction(qMatrix);
		drone.takeAction(client);
		drone.updateState();
		drone.updateAltitude();
		drone.decreaseFuel();
	}
	// �ڵ�����ĳһ�����˻���, �������˻��ĵ�ǰ�߶�, ��Ϊ��һ�γ�ʼ�����˻�����ʼ�߶�
	return drone.getAltitude();
}



void validate(std::vector<QMatrix>& vecQMatrix, std::vector<Router> vecRouter, Drone& drone, msr::airlib::MultirotorRpcLibClient& client) {

	// ͨ�� Airsim API ʵ�����˻������.
	client.takeoffAsync()->waitOnLastTask();
	int lenRouter = vecRouter.size();
	std::vector<int> startStateList;
	// �������˻������, ���˻������Ϊλ�� 0 �� �� n - 1 ��·����
	startStateList.push_back(0);
	for (int i = 0; i < lenRouter - 1; ++i)
		startStateList.push_back(vecRouter[i].getPosition());
	int startAltitude = 0;
	for (int i = 0; i < lenRouter; ++i) {
		startAltitude = getOptimalRoute(vecQMatrix[i], drone, vecRouter[i], startStateList[i], startAltitude, client);
	}
	// ͨ�� Airsim API ʵ�����˻��Ľ���.
	client.landAsync()->waitOnLastTask();
}

