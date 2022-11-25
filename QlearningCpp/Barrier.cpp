#include<math.h>
#include"Barrier.h"



Barrier::Barrier(std::string nam, int h, msr::airlib::MultirotorRpcLibClient& client) {
	name = nam;
	height = h;
	// ���� Airsim API ����Ŀ�����������
	auto pose = client.simGetObjectPose(nam).position;
	if (!isnan(pose.x())) {
		// ��ʵ���������ת��Ϊһά�����е�λ������
		position = approPosition(pose.x(), pose.y());
	}
	else
		position = -1;
}

std::string Barrier::getName() {
	return name; 
}

int Barrier::getHeight() {
	return height; 
}

int Barrier::getPosition() { 
	return position;
}