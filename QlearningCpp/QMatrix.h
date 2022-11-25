#include"Fastor/Fastor.h"
#include"constants.h"
#include"RewardMatrix.h"


/*
	Q 矩阵类, 继承自 Fastor 张量库, 存储无人机在不同环境下选择不同动作所带来的收益, 
	是 Q-learning 算法的核心.
*/

class QMatrix : public Fastor::Tensor<double, constants::num_altitudes, constants::num_states, constants::num_actions> {
	public:
		QMatrix();
		// 静态方法，获取无人机在确定环境下选择不同状态的收益最大值
		static double maxQValue(QMatrix& qMatrix, int currentState, int currentAltitude);
		// 核心函数，根据无人机在当前环境下选择的动作来更新 Q-Table
		void updateQMatrix(RewardMatrix& reward, int currentState, int nextState, int currentAltitude, int nextAltitude, int action);
};


