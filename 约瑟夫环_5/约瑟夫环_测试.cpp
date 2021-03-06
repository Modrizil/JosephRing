// 约瑟夫环_5.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Func_header.h"

int main() {
	int range = 10000;
	printf("\nJoseph_2D\n");
	for (int j = 1; j < 50; j++) {
		double sum = 0;
		for (int i = 0; i < 10; i++) {
			sum += Joseph_2D(j * 10000, range);
		}
		printf("%.10lf\n", sum * 100);
	}
	printf("\nJoseph_BIR\n");
	for (int j = 1; j < 50; j++) {
		double sum = 0;
		for (int i = 0; i < 10; i++) {
			sum += Joseph_BIR(j * 10000, range);
		}
		printf("%.10lf\n", sum * 100);
	}
	printf("\nJoseph_BIL\n");
	for (int j = 1; j < 50; j++) {
		double sum = 0;
		for (int i = 0; i < 10; i++) {
			sum += Joseph_BIL(j * 10000, range);
		}
		printf("%.10lf\n", sum * 100);
	}
	printf("\nJoseph_MD3\n");
	for (int j = 1; j < 50; j++) {
		double sum = 0;
		for (int i = 0; i < 10; i++) {
			sum += Joseph_MD3(j * 10000, range);
		}
		printf("%.10lf\n", sum * 100);
	}
	printf("\nJoseph_LDL\n");
	for (int j = 1; j < 50; j++) {
		double sum = 0;
		for (int i = 0; i < 10; i++) {
			sum += Joseph_LDL(j * 10000, range);
		}
		printf("%.10lf\n", sum * 100);
	}
}
