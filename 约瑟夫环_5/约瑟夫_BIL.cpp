#include "stdafx.h"
#include "Func_header.h"

void Joseph_BIL_Init(int** Joseph, int n)
{
	srand((unsigned)time(NULL));

	int layer = (int)log2(n - 1) + 1; bool odds;//�������
	Joseph[layer] = new int[n];//���һ����nԪ�� 
	for (int i = 0; i < n; i++) {//���������
		Joseph[layer][i] = 1;//��ʼ�����һ��Ϊ1
	}
	odds = n % 2; n = (n - 1) / 2 + 1; layer--;//��һ��Ԫ��Ϊ��һ��Ԫ�ص�һ��
	for (; layer >= 0; layer--) {//���²�Ļ����Ϲ����ϲ�
		Joseph[layer] = new int[n];//�˲�Ԫ��Ϊ��һ���һ��
		for (int i = 0; i < n - 1; i++) {
			Joseph[layer][i] = Joseph[layer + 1][2 * i] + Joseph[layer + 1][2 * i + 1];
		}
		if (!odds) { Joseph[layer][n - 1] = Joseph[layer + 1][2 * n - 1] + Joseph[layer + 1][2 * n - 2]; }
		else { Joseph[layer][n - 1] = Joseph[layer + 1][2 * n - 2]; }
		//�������ڵ��С�飬��ĸ�����һ��ֻ��������
		odds = n % 2; n = (n - 1) / 2 + 1;//�ж���ż
	}
}//Joseph_MTL_Init;

int Joseph_BIL_Delete(int** Joseph, int ID, int LAYER, unsigned long int range)
{
	for (int i = LAYER - 1; i >= 0; i--) {//����ÿһ�����ڵ��ֵ
		Joseph[i][ID]--; ID /= 2;
	}
	return random(range);//�����������
}

int Joseph_BIL_Traversal(int **Joseph, int m, int *n, coord *Current, int LAYER)
{
	if (m > 0) { m = -(((m - 1) % *n) - *n); }
	else { m = -(((m + 1) % *n) - 1); }//����Ѱ�ң����ұ���
	while (Current->depth) {//�ӵ�ǰ��λ�ÿ�ʼ��Ѱ��Ŀ��λ������һ��������С����֦��
		if (!(Current->distance % 2)) { Current->depth--; Current->distance /= 2; }//��С���ڴ�����ˣ������ϲ�Ѱ��
		else {
			if (Joseph[Current->depth][Current->distance - 1] < m) { m -= Joseph[Current->depth][Current->distance - 1]; Current->depth--; Current->distance /= 2; }//�����ֵܽڵ�
			else { Current->distance--; m--; break; }//Ŀ��һ�������С���ڣ�Ѱ�ҽ���
		}
	}
	if (!Current->depth) {
		Current->depth++;//���������ж�
		if (Joseph[1][1] >= m) { Current->distance = 1; m--; }
		else { m -= Joseph[1][1] + 1; }//�����ﶥ�㣬����������ж�
	}
	while (LAYER - 1 - Current->depth) {//���±���Ѱ��λ��
		if (Joseph[Current->depth][Current->distance] - Joseph[Current->depth + 1][Current->distance * 2] > m) {
			Current->distance = Current->distance * 2 + 1;
		}
		else { m -= Joseph[Current->depth][Current->distance] - Joseph[Current->depth + 1][Current->distance * 2]; Current->distance *= 2; }
		Current->depth++;//����m��ֵ�ж�Ŀ��Ԫ���ڵ�ǰС����ĸ���С��
	}
	return Current->distance;//����Ŀ���ַ
}//Joseph_MTL_Traversal;

double Joseph_BIL(int N, unsigned long int range)
{
	int n = N, m;
	if (n <= 1) { return n; }//��������Ĵ���
	int LAYER = (int)log2(n - 1) + 2;//������ܲ������ɾ����㷨���Ƴ�
	int **Joseph = new int*[LAYER];//��ά����
	m = rand() % (N - 1) + 1;//��ʼ����
	Joseph_BIL_Init(Joseph, N);//��ʼ����

	LARGE_INTEGER start;
	LARGE_INTEGER end;
	LARGE_INTEGER freq;

	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&start);

	m = m > 0 ? m % n - 1 : m % n + n + 1;
	coord Current; Current.depth = LAYER - 1; Current.distance = m;//��¼��ǰ�ڵ��λ��
	m = Joseph_BIL_Delete(Joseph, Current.distance, LAYER, range);//ɾ���ڵ㣬������ֵ
	while (--n) {//��Ԫ�ز��ϼ���
		m = Joseph_BIL_Delete(Joseph, Joseph_BIL_Traversal(Joseph, m, &n, &Current, LAYER), LAYER, range);//ѭ������ɾ��
	}

	for (int i = 0; i < LAYER; i++) {
		delete[]Joseph[i];
	}
	delete[]Joseph;
	QueryPerformanceCounter(&end);
	return (double)(end.QuadPart - start.QuadPart) / (double)freq.QuadPart;
}//Joseph_MTL;
