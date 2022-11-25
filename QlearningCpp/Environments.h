#pragma once

#include<string>

/* 
	�������࣬�������ϰ����·�����������࣬
*/

class Environments {
	protected:
		// ����������
		std::string name;
		// ������λ��
		int position;
	public:
		// ���ػ�������
		virtual std::string getName() = 0;
		// ���ػ�����λ��
		virtual int getPosition() = 0;
		// �� airsim API ��ȡ����λ������ת��Ϊ����
		int approPosition(float x, float y);
		
};

// �жϵ�ǰ�����Ƿ��ڵ�ͼǰ�߽�
bool isFowardBound(int pos);

// �жϵ�ǰ�����Ƿ��ڵ�ͼ��߽�
bool isLeftBound(int pos);

// �жϵ�ǰ�����Ƿ��ڵ�ͼ�ұ߽�
bool isRightBound(int pos);

// �жϵ�ǰ�����Ƿ��ڵ�ͼ��߽�
bool isBackBound(int pos);