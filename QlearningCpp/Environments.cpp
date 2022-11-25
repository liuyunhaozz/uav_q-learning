#include"Environments.h"

int Environments::approPosition(float x, float y) {
	x = abs(x);
	y = abs(y);
	// �� x �ĸ�λ������ 5, ����ȡ��; ��������ȡ��
	if (int(x) % 10 > 5)
		x = int(int(ceil(x / 10.0)) * 10) / 10;
	else
		x = int(x / 10);
	// �� y �ĸ�λ������ 5, ����ȡ��; ��������ȡ��
	if (int(y) % 10 > 5)
		y = int(int(ceil(y / 10.0)) * 10) / 10;
	else
		y = int(y / 10);
	// ��ͼ�������� y Ϊ�е��� 7 * 7 ����תΪ��һά������
	return x + 7 * y;
}

bool isFowardBound(int pos) {
	for (int i = 6; i < 55; i += 7) {
		if (pos == i)
			return true;
	}
	return false;
}

bool isLeftBound(int pos) {
	for (int i = 0; i < 7; i += 1) {
		if (pos == i)
			return true;
	}
	return false;
}

bool isRightBound(int pos) {
	for (int i = 42; i < 49; i += 1) {
		if (pos == i)
			return true;
	}
	return false;
}

bool isBackBound(int pos) {
	for (int i = 0; i < 49; i += 7) {
		if (pos == i)
			return true;
	}
	return false;
}