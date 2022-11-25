#include<string>
#include "vehicles/multirotor/api/MultirotorRpcLibClient.hpp"
#include"Environments.h"


/*
	�ϰ�����, �̳��Ի�������
*/


class Barrier : public Environments {
	private:	
		// �ϰ���ĸ߶�
		int height;
	public:
		// ���캯�������ϰ�������ơ��߶Ⱥ� airsim �ͻ��˳�ʼ��
		Barrier(std::string nam, int h, msr::airlib::MultirotorRpcLibClient& client);
		// ��ȡ�ϰ�������
		virtual std::string getName();
		// ��ȡ�ϰ���λ��
		virtual int getPosition();
		// ��ȡ�ϰ���߶�
		int getHeight();
};
