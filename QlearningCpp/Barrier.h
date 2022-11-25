#include<string>
#include "vehicles/multirotor/api/MultirotorRpcLibClient.hpp"
#include"Environments.h"


/*
	障碍物类, 继承自环境基类
*/


class Barrier : public Environments {
	private:	
		// 障碍物的高度
		int height;
	public:
		// 构造函数，由障碍物的名称、高度和 airsim 客户端初始化
		Barrier(std::string nam, int h, msr::airlib::MultirotorRpcLibClient& client);
		// 获取障碍物名称
		virtual std::string getName();
		// 获取障碍物位置
		virtual int getPosition();
		// 获取障碍物高度
		int getHeight();
};
