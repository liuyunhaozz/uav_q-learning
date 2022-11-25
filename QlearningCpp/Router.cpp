#include<math.h>
#include"Router.h"



Router::Router(std::string nam, msr::airlib::MultirotorRpcLibClient& client) {
	name = nam;
	// ���� Airsim API ����·����������
	auto pose = client.simGetObjectPose(nam).position;
	x_pos = pose.x();
	y_pos = pose.y();
	if (!isnan(pose.x())) {
		// ��ʵ���������ת��Ϊһά�����е�λ������
		position = approPosition(x_pos, y_pos);
	}
	else
		position = -1;
}

std::string Router::getName() {
	return name;
}

int Router::getPosition() {
	return position;
}

double Router::getxPos() {
	return x_pos;
}

double Router::getyPos() {
	return y_pos;
}

