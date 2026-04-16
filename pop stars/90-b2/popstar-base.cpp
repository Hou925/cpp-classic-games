/* 2254287 侯俊皓 信05 */
#include <iostream>
#include "popstar.h"
#include "cmd_console_tools.h"
using namespace std;
//初始化随机矩阵
void set_matrix(int xmax, int ymax, int mat[10][10])
{
	int i, j;
	srand((unsigned)time(NULL));
	for (i = 0; i < xmax; i++) {
		for (j = 0; j < ymax; j++) {
			mat[i][j] = rand() % 5 + 1;
		}
	}
}
//打印初始化的矩阵
void print_matrix(int mat[10][10], int xmax, int ymax)
{
	cout << endl;
	cout << "当前数组：" << endl;
	cout << "  |";
	for (int i = 0; i < ymax; i++)
		cout << setw(3) << i ;
	cout << endl;
	cout << "--+";
	for (int i = 0; i < ymax; i++)
		cout << "---";
	cout << endl;
	for (int j = 0; j < xmax; j++) {
		cout << char('A' + j) << " |";
		for (int i = 0; i < ymax; i++) {
			if (mat[j][i] == 0) {
				cout << "  ";
				cct_setcolor(14, 0);
				cout << mat[j][i];
				cct_setcolor();
			}
			else
				cout << setw(3) << mat[j][i];
		}
		cout << endl;
	}
}
//查找函数，其中可以通过返回sign判断周围是否有一样的
int find_same(int mat[10][10],int cx,int cy,int sign,int xmax,int ymax,char mat0[10][10])
{
	mat0[cx][cy] = '*';
	if (cx + 1 <= xmax && mat0[cx + 1][cy] == '0' && mat[cx + 1][cy] == mat[cx][cy]) {
		mat0[cx + 1][cy] = '*';
		sign = 1;
		find_same(mat, cx + 1, cy, sign, xmax, ymax, mat0);
	}
	if (cx - 1 >= 0 && mat0[cx - 1][cy] == '0' && mat[cx - 1][cy] == mat[cx][cy]) {
		mat0[cx - 1][cy] = '*';
		sign = 1;
		find_same(mat, cx - 1, cy, sign, xmax, ymax, mat0);
	}
	if (cy + 1 <= ymax && mat0[cx][cy + 1] == '0' && mat[cx][cy + 1] == mat[cx][cy]) {
		mat0[cx][cy + 1] = '*';
		sign = 1;
		find_same(mat, cx, cy + 1, sign, xmax, ymax, mat0);
	}
	if (cy - 1 >= 0 && mat0[cx][cy - 1] == '0' && mat[cx][cy - 1] == mat[cx][cy]) {
		mat0[cx][cy - 1] = '*';
		sign = 1;
		find_same(mat, cx, cy - 1, sign, xmax, ymax, mat0);
	}
	return sign;
}
//打印带*的矩阵
void print_result_matrix(char mat0[10][10], int xmax, int ymax)
{
	cout << endl;
	cout << "查找结果数组：" << endl;
	cout << "  |";
	for (int i = 0; i < ymax; i++)
		cout << setw(3) << i;
	cout << endl;
	cout << "--+";
	for (int i = 0; i < ymax; i++)
		cout << "---";
	cout << endl;
	for (int j = 0; j < xmax; j++) {
		cout << char('A' + j) << " |";
		for (int i = 0; i < ymax; i++) {
			cout << setw(3) << mat0[j][i];
		}
		cout << endl;
	}
}
//打印选中后的矩阵
void print_colored_matrix(int mat[10][10],char mat0[10][10],int xmax, int ymax)
{
	cout << endl;
	cout << "当前数组(不同色标识)：" << endl;
	cout << "  |";
	for (int i = 0; i < ymax; i++)
		cout << setw(3) << i;
	cout << endl;
	cout << "--+";
	for (int i = 0; i < ymax; i++)
		cout << "---";
	cout << endl;
	for (int j = 0; j < xmax; j++) {
		cout << char('A' + j) << " |";
		for (int i = 0; i < ymax; i++) {
			if (mat0[j][i] == '*') {
				cout << "  ";
				cct_setcolor(14, 0);
				cout << mat[j][i];
				cct_setcolor();
			}
			else
				cout << setw(3) << mat[j][i];
		}
		cout << endl;
	}
}
//询问是否消除
char que_clear(int cx,int cy)
{
	char que;
	cout << endl;
	cout << "请确认是否把" << char(cx + 65) << cy << "及周围的相同值消除(Y/N/Q)：";
	while (1) {
		que = _getche();
		if (que == 'y' || que == 'Y' || que == 'n' || que == 'N' || que == 'q' || que == 'Q')
			break;
		else
			cout << "\b \b";
	}
	return que;
}
//将选中的格子变成0的操作
void clear_matrix(int mat[10][10], int xmax, int ymax, char mat0[10][10])
{
	cout << endl;
	for (int i = 0; i < xmax; i++) {
		for (int j = 0; j < ymax; j++) {
			if (mat0[i][j] == '*')
				mat[i][j] = 0;
		}
	}
}
//打印清除后的矩阵
void print_cleared_matrix(int mat[10][10], char mat0[10][10], int xmax, int ymax)
{
	cout << endl;
	cout << "相同值归并后的数组(不同色标识)：" << endl;
	cout << "  |";
	for (int i = 0; i < ymax; i++)
		cout << setw(3) << i;
	cout << endl;
	cout << "--+";
	for (int i = 0; i < ymax; i++)
		cout << "---";
	cout << endl;
	for (int j = 0; j < xmax; j++) {
		cout << char('A' + j) << " |";
		for (int i = 0; i < ymax; i++) {
			if (mat0[j][i] == '*') {
				cout << "  ";
				cct_setcolor(14, 0);
				cout << mat[j][i];
				cct_setcolor();
			}
			else
				cout << setw(3) << mat[j][i];
		}
		cout << endl;
	}
}
//非图形的下落函数
void fall_matrix(int mat[10][10], int xmax, int ymax,int tag0)
{
	if (tag0 == 1) {
		cout << "按回车进行数组下落操作..." << endl;
		pause();
	}
	int t = 0;
	int i, j, k;
	int tag = xmax;
	for (j = 0; j < ymax; j++) {
		for (i = xmax - 1; i > 0; i--) {
			if (mat[i][j] == 0){
				for (k = i - 1; k >= 0; k--) {
					if (mat[k][j] != 0 || k == 0)
						break;
				}
				mat[i][j] = mat[k][j];
				mat[k][j] = 0;
			}
		}
	}
	for (j = 0; j < ymax; j++) {
		if (mat[xmax - 1][j] == 0 && j < ymax - 1) {
			for (i = 0; i < xmax; i++) {
				mat[i][j] = mat[i][j + 1];
				mat[i][j + 1] = 0;
			}
		}
	}
	if (tag0 == 1) {
		cout << "下落后的数组：" << endl;
		cout << "  |";
		for (int i = 0; i < ymax; i++)
			cout << setw(3) << i;
		cout << endl;
		cout << "--+";
		for (int i = 0; i < ymax; i++)
			cout << "---";
		cout << endl;
		for (int j = 0; j < xmax; j++) {
			cout << char('A' + j) << " |";
			for (int i = 0; i < ymax; i++) {
				if (mat[j][i] == 0) {
					cout << "  ";
					cct_setcolor(14, 0);
					cout << mat[j][i];
					cct_setcolor();
				}
				else
					cout << setw(3) << mat[j][i];
			}
			cout << endl;
		}
	}
}
