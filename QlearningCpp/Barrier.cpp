#include<math.h>
#include"Barrier.h"



Barrier::Barrier(std::string nam, int h, msr::airlib::MultirotorRpcLibClient& client) {
	name = nam;
	height = h;
	// 调用 Airsim API 计算目标物体的坐标
	auto pose = client.simGetObjectPose(nam).position;
	if (!isnan(pose.x())) {
		// 将实际坐标近似转化为一维数组中的位置坐标
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