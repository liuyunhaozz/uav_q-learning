#include "vehicles/multirotor/api/MultirotorRpcLibClient.hpp"
#include"QMatrix.h"


/*
	���˻���, �� Q-learning �㷨��ģ�������˻��Ĳ���, ��ͨ�� Airsim API �� UE4 ������ʵ�������˻�������.
*/


class Drone {
	private:
		// ���˻��ĵ�ǰ�߶�
		int currentAltitude;
		// ���˻��ĵ�ǰλ��
		int currentState;
		// ���˻���ǰ��Ҫִ�еĶ���
		int action;
		// ���˻����ٶ�
		int speed;
		// ���˻���ȼ��
		int fuel;
	public:
		Drone() : currentAltitude(0), currentState(0), action(-1), speed(3), fuel(constants::num_steps_in_episode) {}
		// ������Ĭ�Ϲ��캯��, �����˻��ĸ߶Ⱥ�λ�ó�ʼ��
		Drone(int altitude, int state) : currentAltitude(altitude), currentState(state), action(-1), speed(3), fuel(constants::num_steps_in_episode) {}
		// �ø߶�, λ��, �͵�ǰλ���������˻���״̬
		void setStatus(int altitude, int state, int act);
		// ��ȡ���˻���ǰ��λ��
		int getState();
		// ��ȡ���˻���ǰ�ĸ߶�
		int getAltitude();
		// ��ȡ���˻���Ҫִ�еĶ���
		int getAction();
		// �������˻���ȼ��
		void decreaseFuel();
		// ��ȡ���˻���ǰ��ȼ��ʣ����
		int getFuel();
		// �������˻���λ��
		void updateState();
		// �������˻��ĸ߶�
		void updateAltitude();
		// ѵ��ʱ, ���� ��-greedy ����ѡ�����˻��ڵ�ǰ�����²�ȡ�Ķ���
		void chooseAction(QMatrix& qMatrix, double epsilon);
		// ��֤ʱ, ѡ�����˻��ڵ�ǰ�����²�ȡ�Ķ���
		void chooseAction(QMatrix& qMatrix);
		// ͨ�� Airsim API �� UE4 ������ʵ�����˻��ķ���.
		void takeAction(msr::airlib::MultirotorRpcLibClient& client);	
};