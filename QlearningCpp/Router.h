#include<string>
#include"Environments.h"
#include "vehicles/multirotor/api/MultirotorRpcLibClient.hpp"


/*
	路由器类, 继承自环境基类
*/

class Router : public Environments {
	private:
		// 路由器在地图中的 x 坐标
		double x_pos;
		// 路由器在地图中的 y 坐标
		double y_pos;
		// 路由器在地图中近似后的整型坐标
		int position;
	public:
		// 构造函数，由路由器的名称和 airsim 客户端初始化
		Router(std::string nam, msr::airlib::MultirotorRpcLibClient& client);
		// 获取路由器名称
		virtual std::string getName();
		// 获取路由器近似后的整型坐标
		virtual int getPosition();
		// 获取路由器的 x 坐标
		double getxPos();
		// 获取路由器的 y 坐标
		double getyPos();
};
