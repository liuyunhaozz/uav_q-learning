#include"Fastor/Fastor.h"
#include"constants.h"
#include"RewardMatrix.h"


/*
	Q ������, �̳��� Fastor ������, �洢���˻��ڲ�ͬ������ѡ��ͬ����������������, 
	�� Q-learning �㷨�ĺ���.
*/

class QMatrix : public Fastor::Tensor<double, constants::num_altitudes, constants::num_states, constants::num_actions> {
	public:
		QMatrix();
		// ��̬��������ȡ���˻���ȷ��������ѡ��ͬ״̬���������ֵ
		static double maxQValue(QMatrix& qMatrix, int currentState, int currentAltitude);
		// ���ĺ������������˻��ڵ�ǰ������ѡ��Ķ��������� Q-Table
		void updateQMatrix(RewardMatrix& reward, int currentState, int nextState, int currentAltitude, int nextAltitude, int action);
};


