#include"Environments.h"

int Environments::approPosition(float x, float y) {
	x = abs(x);
	y = abs(y);
	// 若 x 的个位数大于 5, 向上取整; 否则向下取整
	if (int(x) % 10 > 5)
		x = int(int(ceil(x / 10.0)) * 10) / 10;
	else
		x = int(x / 10);
	// 若 y 的个位数大于 5, 向上取整; 否则向下取整
	if (int(y) % 10 > 5)
		y = int(int(ceil(y / 10.0)) * 10) / 10;
	else
		y = int(y / 10);
	// 地图坐标存放在 y 为行的由 7 * 7 网格转为的一维数组中
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