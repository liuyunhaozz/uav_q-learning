#include<random>
#include"Drone.h"

// ������������ȵĽ����ж�
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
	// ���� random ���ʼ��һ������ (0, 1) ֮����ȷֲ�������� 
	std::uniform_real_distribution<> uniReal(0, 1.0);

	double exploreExploitN = uniReal(gen);
	// ��ȡ ��-greedy ����, ��� exploreExploitN > epsilon, ѡȡʹ Q-Table ���Ķ���; �������ѡȡһ������
	if (exploreExploitN > epsilon) {
		vector<int> maxQAction;
		double maxQValue = QMatrix::maxQValue(qMatrix, currentAltitude, currentState);
		
		for (int i = 0; i < 6; ++i) {
			if (isDoubleEqual(maxQValue, qMatrix(currentAltitude, currentState, i))) {
				maxQAction.push_back(i);
			}
		}
		std::cout << std::endl;
		// ����ж���ظ������ֵ, ���ѡȡһ��
		if (maxQAction.size() > 1) {
			// ���� random ��, �� maxQAction ���������ѡȡһ����
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
	// ��ȡ��ͨ����, ѡȡʹ Q-Table ���Ķ���
	vector<int> maxQAction;
	double maxQValue = QMatrix::maxQValue(qMatrix, currentAltitude, currentState);
	for (int i = 0; i < 6; ++i) {
		if (isDoubleEqual(maxQValue, qMatrix(currentAltitude, currentState, i)))
			maxQAction.push_back(i);
	}
	// ����ж���ظ������ֵ, ���ѡȡһ��
	if (maxQAction.size() > 1) {
		std::uniform_int_distribution<> uniInt(0, maxQAction.size() - 1);
		action = maxQAction[uniInt(gen)];
	}
	else
		action = maxQAction[0];

}

void Drone::updateState() {
	// �������ִ�еĶ���Ϊǰ�ҵ�ǰ�Ļ������ڵ�ͼ��ǰ�߽�, ���˻���ǰ�ƶ�
	if (action == 0 && !isFowardBound(currentState))
		currentState += 1;
	// �������ִ�еĶ���Ϊ���ҵ�ǰ�Ļ������ڵ�ͼ�ĺ�߽�, ���˻�����ƶ�
	else if (action == 1 && !isBackBound(currentState))
		currentState -= 1;
	// �������ִ�еĶ���Ϊ���ҵ�ǰ�Ļ������ڵ�ͼ���ұ߽�, ���˻������ƶ�
	else if (action == 2 && !isRightBound(currentState))
		currentState += 7;
	// �������ִ�еĶ���Ϊ���ҵ�ǰ�Ļ������ڵ�ͼ����߽�, ���˻������ƶ�
	else if (action == 3 && !isLeftBound(currentState))
		currentState -= 7;
}


void Drone::updateAltitude() {
	// �������ִ�еĶ���Ϊ���ҵ�ǰ���˻��ĸ߶�С�������и߶�, ���˻������ƶ�
	if (action == 4) {
		if (currentAltitude < 2)
			currentAltitude += 1;
	}
	// �������ִ�еĶ���Ϊ���ҵ�ǰ���˻��ĸ߶ȴ�����С���и߶�, ���˻������ƶ�
	else if (action == 5) {
		if (currentAltitude > 0)
			currentAltitude -= 1;
	}
}


void Drone::takeAction(msr::airlib::MultirotorRpcLibClient& client) {
	// ���� Airsim API ��ȡ���˻��ڵ�ͼ������
	auto pos = client.simGetVehiclePose().position;
	double xPos = pos.x();
	double yPos = pos.y();
	double zPos = pos.z();

	// ���� Airsim API ʹ���˻���ǰ�ƶ�
	if (action == 0) {
		client.moveToPositionAsync(xPos + 10, yPos, zPos, speed)->waitOnLastTask();
		client.hoverAsync()->waitOnLastTask();
	}
	// ���� Airsim API ʹ���˻�����ƶ�
	else if (action == 1) {
		client.moveToPositionAsync(xPos - 10, yPos, zPos, speed)->waitOnLastTask();
		client.hoverAsync()->waitOnLastTask();
	}
	// ���� Airsim API ʹ���˻������ƶ�
	else if (action == 2) {
		client.moveToPositionAsync(xPos, yPos + 10, zPos, speed)->waitOnLastTask();
		client.hoverAsync()->waitOnLastTask();
	}
	// ���� Airsim API ʹ���˻������ƶ�
	else if (action == 3) {
		client.moveToPositionAsync(xPos, yPos - 10, zPos, speed)->waitOnLastTask();
		client.hoverAsync()->waitOnLastTask();
	}
	// ���� Airsim API ʹ���˻������ƶ�
	else if (action == 4 && currentAltitude >= 0 && currentAltitude <= 1) {
		client.moveToPositionAsync(xPos, yPos, zPos - 7.5, speed)->waitOnLastTask();
		client.hoverAsync()->waitOnLastTask();
	}
	// ���� Airsim API ʹ���˻������ƶ�
	else if (action == 5 && currentAltitude >= 1 && currentAltitude <= 2) {
		client.moveToPositionAsync(xPos, yPos, zPos + 7.5, speed)->waitOnLastTask();
		client.hoverAsync()->waitOnLastTask();
	}
}

