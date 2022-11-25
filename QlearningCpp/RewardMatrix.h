#include<vector>
#include<math.h>
#include"Fastor/Fastor.h"
#include"constants.h"
#include"Router.h"
#include"Barrier.h"


/*
	����������, �̳��� Fastor ������, �洢���˻��ڲ�ͬ�����¿��Եõ��Ľ�����ͷ�, 
	�� Q-learning �㷨������������ĵ����ݽṹ Q-Table.
*/


class RewardMatrix : public Fastor::Tensor<double, constants::num_altitudes, constants::num_states, constants::num_actions> {
	public:
		RewardMatrix();
		// �Ե�ǰ��·�������ϰ��Ｏ��Ϊ��������ʼ����������
		void initReward(Router& route, std::vector<Barrier>& vecBarr);
		// �����˻���·���������λ��ȷ�����˻���õĽ���
		double calculateReward(int altitude, int goalState, double xPos, double yPos);
		// ����·���������˻�������
		std::pair<double, double> calcualteTheta(int altitude, int goalState, double xPos, double yPos);
};

