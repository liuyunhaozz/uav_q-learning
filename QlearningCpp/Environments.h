#pragma once

#include<string>

/* 
	环境基类，包含了障碍物和路由器两个子类，
*/

class Environments {
	protected:
		// 环境的名称
		std::string name;
		// 环境的位置
		int position;
	public:
		// 返回环境名称
		virtual std::string getName() = 0;
		// 返回环境的位置
		virtual int getPosition() = 0;
		// 把 airsim API 获取到的位置坐标转换为整型
		int approPosition(float x, float y);
		
};

// 判断当前环境是否在地图前边界
bool isFowardBound(int pos);

// 判断当前环境是否在地图左边界
bool isLeftBound(int pos);

// 判断当前环境是否在地图右边界
bool isRightBound(int pos);

// 判断当前环境是否在地图后边界
bool isBackBound(int pos);