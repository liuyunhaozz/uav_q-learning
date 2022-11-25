#include"QMatrix.h"

QMatrix::QMatrix() {
	(*this)(Fastor::all, Fastor::all, Fastor::all) = 0;
}

void QMatrix::updateQMatrix(RewardMatrix& rewardMat, int currentState, int nextState, int currentAltitude, int nextAltitude, int action) {
	// 根据无人机当前的状态和下一个状态，以及无人机在状态转变中所选择的动作，更新Q-Table
	double reward = rewardMat(currentAltitude, currentState, action);
	double currentQ = (*this)(currentAltitude, currentState, action);
	// Q-learning 算法核心: Bellman 方程
	(*this)(currentAltitude, currentState, action) = currentQ + constants::alpha * (reward + constants::gamma * maxQValue(*this, nextAltitude, nextState) - currentQ);
}

double QMatrix::maxQValue(QMatrix& qMatrix, int currentAltitude, int currentState) {
	double max = constants::min_number;
	for (int i = 0; i < constants::num_actions; ++i) {
		if (qMatrix(currentAltitude, currentState, i) > max)
			max = qMatrix(currentAltitude, currentState, i);
	}
	return max;
}