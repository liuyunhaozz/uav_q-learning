#include<string>
#include"Environments.h"
#include "vehicles/multirotor/api/MultirotorRpcLibClient.hpp"


/*
	·������, �̳��Ի�������
*/

class Router : public Environments {
	private:
		// ·�����ڵ�ͼ�е� x ����
		double x_pos;
		// ·�����ڵ�ͼ�е� y ����
		double y_pos;
		// ·�����ڵ�ͼ�н��ƺ����������
		int position;
	public:
		// ���캯������·���������ƺ� airsim �ͻ��˳�ʼ��
		Router(std::string nam, msr::airlib::MultirotorRpcLibClient& client);
		// ��ȡ·��������
		virtual std::string getName();
		// ��ȡ·�������ƺ����������
		virtual int getPosition();
		// ��ȡ·������ x ����
		double getxPos();
		// ��ȡ·������ y ����
		double getyPos();
};
