#include<random>
#include"Drone.h"

// 两个浮点数相等的近似判断
bool isDoubleEqual(double x, double y) {
	if (abs(x - y) <= 1e-5)
		return true;
	else
		return false;
}

void Drone::setStatus(int altitude, int state, int act) {
	currentAltitude = altitude;
	currentState = state;
	action = act;
	fuel = constants::num_steps_in_episode;
}

int Drone::getState() {
	return currentState;
}

int Drone::getAltitude() {
	return currentAltitude;
}

int Drone::getAction() {
	return action;
}

void Drone::decreaseFuel() {
	fuel--;
}

int Drone::getFuel() {
	return fuel;
}

void Drone::chooseAction(QMatrix& qMatrix, double epsilon) {

	std::random_device rd;
	std::mt19937 gen(rd());
	// 利用 random 库初始化一个服从 (0, 1) 之间均匀分布的随机数 
	std::uniform_real_distribution<> uniReal(0, 1.0);

	double exploreExploitN = uniReal(gen);
	// 采取 ε-greedy 策略, 如果 exploreExploitN > epsilon, 选取使 Q-Table 最大的动作; 否则随机选取一个动作
	if (exploreExploitN > epsilon) {
		vector<int> maxQAction;
		double maxQValue = QMatrix::maxQValue(qMatrix, currentAltitude, currentState);
		
		for (int i = 0; i < 6; ++i) {
			if (isDoubleEqual(maxQValue, qMatrix(currentAltitude, currentState, i))) {
				maxQAction.push_back(i);
			}
		}
		std::cout << std::endl;
		// 如果有多个重复的最大值, 随机选取一个
		if (maxQAction.size() > 1) {
			// 利用 random 库, 在 maxQAction 数组中随机选取一个数
			std::uniform_int_distribution<> uniInt(0, maxQAction.size() - 1);
			action = maxQAction[uniInt(gen)];
		}
		else
			action = maxQAction[0];
			
	}
	else {
		std::uniform_int_distribution<> ramdomAction(0, 5);
		action = ramdomAction(gen);
	}

}

void Drone::chooseAction(QMatrix& qMatrix) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> uniReal(0, 1.0);
	double exploreExploitN = uniReal(gen);
	// 采取普通策略, 选取使 Q-Table 最大的动作
	vector<int> maxQAction;
	double maxQValue = QMatrix::maxQValue(qMatrix, currentAltitude, currentState);
	for (int i = 0; i < 6; ++i) {
		if (isDoubleEqual(maxQValue, qMatrix(currentAltitude, currentState, i)))
			maxQAction.push_back(i);
	}
	// 如果有多个重复的最大值, 随机选取一个
	if (maxQAction.size() > 1) {
		std::uniform_int_distribution<> uniInt(0, maxQAction.size() - 1);
		action = maxQAction[uniInt(gen)];
	}
	else
		action = maxQAction[0];

}

void Drone::updateState() {
	// 如果即将执行的动作为前且当前的环境不在地图的前边界, 无人机向前移动
	if (action == 0 && !isFowardBound(currentState))
		currentState += 1;
	// 如果即将执行的动作为后且当前的环境不在地图的后边界, 无人机向后移动
	else if (action == 1 && !isBackBound(currentState))
		currentState -= 1;
	// 如果即将执行的动作为右且当前的环境不在地图的右边界, 无人机向右移动
	else if (action == 2 && !isRightBound(currentState))
		currentState += 7;
	// 如果即将执行的动作为左且当前的环境不在地图的左边界, 无人机向左移动
	else if (action == 3 && !isLeftBound(currentState))
		currentState -= 7;
}


void Drone::updateAltitude() {
	// 如果即将执行的动作为上且当前无人机的高度小于最大飞行高度, 无人机向上移动
	if (action == 4) {
		if (currentAltitude < 2)
			currentAltitude += 1;
	}
	// 如果即将执行的动作为下且当前无人机的高度大于最小飞行高度, 无人机向下移动
	else if (action == 5) {
		if (currentAltitude > 0)
			currentAltitude -= 1;
	}
}


void Drone::takeAction(msr::airlib::MultirotorRpcLibClient& client) {
	// 调用 Airsim API 获取无人机在地图中坐标
	auto pos = client.simGetVehiclePose().position;
	double xPos = pos.x();
	double yPos = pos.y();
	double zPos = pos.z();

	// 调用 Airsim API 使无人机向前移动
	if (action == 0) {
		client.moveToPositionAsync(xPos + 10, yPos, zPos, speed)->waitOnLastTask();
		client.hoverAsync()->waitOnLastTask();
	}
	// 调用 Airsim API 使无人机向后移动
	else if (action == 1) {
		client.moveToPositionAsync(xPos - 10, yPos, zPos, speed)->waitOnLastTask();
		client.hoverAsync()->waitOnLastTask();
	}
	// 调用 Airsim API 使无人机向右移动
	else if (action == 2) {
		client.moveToPositionAsync(xPos, yPos + 10, zPos, speed)->waitOnLastTask();
		client.hoverAsync()->waitOnLastTask();
	}
	// 调用 Airsim API 使无人机向左移动
	else if (action == 3) {
		client.moveToPositionAsync(xPos, yPos - 10, zPos, speed)->waitOnLastTask();
		client.hoverAsync()->waitOnLastTask();
	}
	// 调用 Airsim API 使无人机向上移动
	else if (action == 4 && currentAltitude >= 0 && currentAltitude <= 1) {
		client.moveToPositionAsync(xPos, yPos, zPos - 7.5, speed)->waitOnLastTask();
		client.hoverAsync()->waitOnLastTask();
	}
	// 调用 Airsim API 使无人机向下移动
	else if (action == 5 && currentAltitude >= 1 && currentAltitude <= 2) {
		client.moveToPositionAsync(xPos, yPos, zPos + 7.5, speed)->waitOnLastTask();
		client.hoverAsync()->waitOnLastTask();
	}
}

