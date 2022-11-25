#include"RewardMatrix.h"


RewardMatrix::RewardMatrix() {
	// 构造函数初始化, 将所有值置为 -1
	(*this)(Fastor::all, Fastor::all, Fastor::all) = -1;
}

void RewardMatrix::initReward(Router& route, std::vector<Barrier>& vecBarr) {

	// 对地图边界部分的奖励矩阵设置 -10 的惩罚
	(*this)(Fastor::all, Fastor::fseq<0, 7>(), 3) = -10;
	(*this)(Fastor::all, Fastor::fseq<42, 49>(), 2) = -10;
	for (int i = 0; i < constants::num_states; ++i) {
		if (i % 7 == 0)
			(*this)(Fastor::all, i, 1) = -10;
		if (i % 7 == 6)
			(*this)(Fastor::all, i, 0) = -10;
	}
	// 对无人机飞行高度范围外的奖励矩阵设置 -5 的惩罚
	(*this)(0, Fastor::all, 5) = -5;
	(*this)(2, Fastor::all, 4) = -5;

	// 根据无人机在路由器附近的位置设置不同的奖励
	for (int i = 0; i < constants::num_altitudes; ++i) {
		int goal = route.getPosition();
		double xPos = route.getxPos();
		double yPos = route.getyPos();
		if (!isFowardBound(goal))
			(*this)(i, goal + 1, 1) = calculateReward(i, goal, xPos, yPos);
		if (!isLeftBound(goal))
			(*this)(i, goal - 7, 2) = calculateReward(i, goal, xPos, yPos);
		if (!isRightBound(goal))
			(*this)(i, goal + 7, 3) = calculateReward(i, goal, xPos, yPos);
		if (!isBackBound(goal))
			(*this)(i, goal - 1, 0) = calculateReward(i, goal, xPos, yPos);
		(*this)(1, goal, 5) = calculateReward(0, goal, xPos, yPos);
		(*this)(2, goal, 5) = 0.6 * calculateReward(1, goal, xPos, yPos);
		(*this)(0, goal, 4) = 0.6 * calculateReward(1, goal, xPos, yPos);
		(*this)(1, goal, 4) = 0.3 * calculateReward(2, goal, xPos, yPos);
	}
	
	// 对地图边界部分的障碍物设置 -10 的惩罚
	for (auto& barr : vecBarr) {
		int barrier = barr.getPosition();
		int height = barr.getHeight();
		if (!isFowardBound(barrier))
			(*this)(Fastor::seq(0, height + 1), barrier + 1, 1) = -10;
		if (!isLeftBound(barrier))
			(*this)(Fastor::seq(0, height + 1), barrier - 7, 2) = -10;
		if (!isRightBound(barrier))
			(*this)(Fastor::seq(0, height + 1), barrier + 7, 3) = -10;
		if (!isBackBound(barrier))
			(*this)(Fastor::seq(0, height + 1), barrier - 1, 0) = -10;
		// 地面上障碍物边界部分置为0
		(*this)(Fastor::seq(0, height + 1), barrier, Fastor::all) = 0;
	}
}



double RewardMatrix::calculateReward(int altitude, int goalState, double xPos, double yPos) {
	auto pair = calcualteTheta(altitude, goalState, xPos, yPos);
	double theta = pair.first;
	double opposite = pair.second;
	double hypotenuse = 0.0;
	// 计算无人机到路由器的空间直线距离
	if (!theta)
		hypotenuse = opposite;
	else
		hypotenuse = opposite / sin(theta);
	double prob_los = 1 / (1 + constants::a * exp(-constants::b * ((180 / constants::pi) * theta - constants::a)));
	double path_loss = 20 * log10(((4 * constants::pi * constants::carrier_freq * hypotenuse) / constants::c)) + prob_los * constants::n_los + (1 - prob_los) * constants::n_nlos;

	path_loss = pow(10, constants::noise / 10);
	double newNoise = pow(10, constants::noise / 10);
	// 计算平均信号功率
	double received_p = constants::transmit_p - path_loss;
	double data_rate = constants::bandwidth * log2(1 + received_p / newNoise);
	data_rate = data_rate / 1000;
	return data_rate;
}


std::pair<double, double> RewardMatrix::calcualteTheta(int altitude, int goalState, double xPos, double yPos) {
	int droneXPos = (goalState % 7) * 10;
	int droneYPos = (goalState / 7) * 10;
	double opposite = 0.0;
	if (altitude == 0)
		opposite = 5;
	else if (altitude == 1)
		opposite = 12.5;
	else if (altitude == 2)
		opposite = 20;
	// 利用解析几何公式计算出无人机在平面上的投影到路由器的距离
	double adjacent = sqrt(pow(((abs(droneXPos - xPos)) * 10), 2) + pow(((abs(droneYPos - yPos)) * 10), 2));
	double theta = 0.0;
	// 计算路由器对无人机的仰角
	if (adjacent)
		theta = atan(opposite / adjacent);
	return { theta, opposite };
}