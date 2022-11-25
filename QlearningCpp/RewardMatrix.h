#include<vector>
#include<math.h>
#include"Fastor/Fastor.h"
#include"constants.h"
#include"Router.h"
#include"Barrier.h"


/*
	奖励矩阵类, 继承自 Fastor 张量库, 存储无人机在不同环境下可以得到的奖励或惩罚, 
	在 Q-learning 算法中用来计算核心的数据结构 Q-Table.
*/


class RewardMatrix : public Fastor::Tensor<double, constants::num_altitudes, constants::num_states, constants::num_actions> {
	public:
		RewardMatrix();
		// 以当前的路由器和障碍物集合为参数，初始化奖励矩阵
		void initReward(Router& route, std::vector<Barrier>& vecBarr);
		// 由无人机和路由器的相对位置确定无人机获得的奖励
		double calculateReward(int altitude, int goalState, double xPos, double yPos);
		// 计算路由器对无人机的仰角
		std::pair<double, double> calcualteTheta(int altitude, int goalState, double xPos, double yPos);
};

