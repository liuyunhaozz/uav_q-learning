#include "vehicles/multirotor/api/MultirotorRpcLibClient.hpp"
#include"QMatrix.h"


/*
	无人机类, 在 Q-learning 算法中模拟了无人机的操作, 并通过 Airsim API 在 UE4 引擎中实现了无人机的运行.
*/


class Drone {
	private:
		// 无人机的当前高度
		int currentAltitude;
		// 无人机的当前位置
		int currentState;
		// 无人机当前将要执行的动作
		int action;
		// 无人机的速度
		int speed;
		// 无人机的燃料
		int fuel;
	public:
		Drone() : currentAltitude(0), currentState(0), action(-1), speed(3), fuel(constants::num_steps_in_episode) {}
		// 重载了默认构造函数, 以无人机的高度和位置初始化
		Drone(int altitude, int state) : currentAltitude(altitude), currentState(state), action(-1), speed(3), fuel(constants::num_steps_in_episode) {}
		// 用高度, 位置, 和当前位置设置无人机的状态
		void setStatus(int altitude, int state, int act);
		// 获取无人机当前的位置
		int getState();
		// 获取无人机当前的高度
		int getAltitude();
		// 获取无人机将要执行的动作
		int getAction();
		// 减少无人机的燃料
		void decreaseFuel();
		// 获取无人机当前的燃料剩余量
		int getFuel();
		// 更新无人机的位置
		void updateState();
		// 更新无人机的高度
		void updateAltitude();
		// 训练时, 根据 ε-greedy 策略选择无人机在当前环境下采取的动作
		void chooseAction(QMatrix& qMatrix, double epsilon);
		// 验证时, 选择无人机在当前环境下采取的动作
		void chooseAction(QMatrix& qMatrix);
		// 通过 Airsim API 在 UE4 引擎中实现无人机的飞行.
		void takeAction(msr::airlib::MultirotorRpcLibClient& client);	
};