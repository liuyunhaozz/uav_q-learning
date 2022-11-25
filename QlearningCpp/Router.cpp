#include<math.h>
#include"Router.h"



Router::Router(std::string nam, msr::airlib::MultirotorRpcLibClient& client) {
	name = nam;
	// 调用 Airsim API 计算路由器的坐标
	auto pose = client.simGetObjectPose(nam).position;
	x_pos = pose.x();
	y_pos = pose.y();
	if (!isnan(pose.x())) {
		// 将实际坐标近似转化为一维数组中的位置坐标
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

