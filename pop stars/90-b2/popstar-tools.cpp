/* 2254287 侯俊皓 信05 */
#include <iostream>
#include "popstar.h"
#include "cmd_console_tools.h"
using namespace std;
//中止函数

void ending()
{
	char end[10];
	while (1)
	{
		cout << endl << "本小题结束，请输入End继续...";
		cin.clear();
		cin.ignore(2048, '\n');
		cin.getline(end, 10, '\n');
		if ((end[0] != 'e' && end[0] != 'E') || (end[1] != 'n' && end[1] != 'N') || (end[2] != 'd' && end[2] != 'D'))
			cout << "输入错误，请重新输入" << endl;
		else
			break;
	}
}
//停顿函数
void pause()
{
	char ch;
	while (1) {
		ch = _getch();
		if (ch == 13)
			cout << endl;
			break;
	}
	return;
}
//输入行和列
void input(int &xmax,int &ymax)
{
	while (1) {
		cout << "请输入行数(8-10)：" << endl;
		cin >> xmax;
		if (xmax >= 8 && xmax <= 10)
			break;
		else {
			cin.clear();
			cin.ignore(2048, '\n');
		}
	}
	while (1) {
		cout << "请输入列数(8-10)：" << endl;
		cin >> ymax;
		if (ymax >= 8 && ymax <= 10)
			break;
		else {
			cin.clear();
			cin.ignore(2048, '\n');
		}
	}
	return;
}
//输入非图形里的坐标
void input_zuobiao(char zuobiao[10],int xmax,int ymax,int mat[10][10])
{
	cout << endl;
	while (1) {
		cout << "请以字母+数字形式[例：c2]输入矩阵坐标：";
		for (int i = 0; i < 2; i++)
			cin >> zuobiao[i];
		for (int i = 0; i < 2; i++) {
			if (zuobiao[i] >= 'A' && zuobiao[i] <= 'Z')
				zuobiao[i] += 32;
		}
		
		if (zuobiao[0] >= 'a' && zuobiao[0] <= char('a' + xmax - 1) && zuobiao[1] >= 0 && zuobiao[1]-48<ymax ) {
			int cx = zuobiao[0] - 'a';
			int cy = zuobiao[1] - 48;
			int sign = 0;
			cout << "输入为" << char(zuobiao[0] - 32) << "行" << zuobiao[1] << "列" << endl;
			char mat00[10][10];
			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 10; j++)
					mat00[i][j] = '0';
			}
			if (find_same(mat, cx, cy, sign, xmax, ymax, mat00) == 0) {
				cout << "输入的矩阵坐标位置处无连续相同值，请重新输入" << endl;
				cin.clear();
				cin.ignore(2048, '\n');
			}
			else
				break;
		}
		else {
			cout << "输入错误，请重新输入." << endl;
			cin.clear();
			cin.ignore(2048, '\n');
		}
	}
	
}
//计算打印消除操作的分数
void scoring(int& score, int xmax, int ymax, char mat0[10][10], int tag)
{
	int score1 = 0;
	for (int i = 0; i < xmax; i++) {
		for (int j = 0; j < ymax; j++) {
			if (mat0[i][j] == '*')
				score1++;
		}
	}
	score1 = score1 * score1 * 5;
	score += score1;
	if (tag == 1) {
		cout << endl;
		cout << "本次得分：" << score1 << " 总得分：" << score << endl << endl;
	}
	if (tag == 2) {
		cct_showch(0, 0, ' ', 0, 7, 50);
		cct_gotoxy(0, 0);
		cout << "本次得分：" << score1 << " 总得分：" << score << endl << endl;
	}
}
//计算打印最后的加分和总分
void final_scoring(int& score, int xmax, int ymax, int mat[10][10])
{
	int score2 = 0, num = 0;
	for (int i = 0; i < xmax; i++) {
		for (int j = 0; j < ymax; j++) {
			if (mat[i][j] != 0)
				num++;
		}
	}
	if (num < 10)
		score2 += (10 - num) * 180;
	score += score2;
	cct_showch(0, 0, ' ', 0, 7, 50);
	cct_gotoxy(0, 0);
	cout << "奖励得分：" << score2 << " 总得分：" << score << endl;
}
//判断游戏是否结束了
int judge_gameover(int mat[10][10], int xmax, int ymax)
{
	int i, j;
	int tag = 0;
	char mat00[10][10];
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++)
			mat00[i][j] = '0';
	}
	for (i = 0; i < xmax; i++) {
		for (j = 0; j < ymax; j++) {
			int sign = 0;
			if (mat[i][j] != 0) {
				if (find_same(mat, i, j, sign, xmax, ymax, mat00) == 1)
					tag++;
			}
		}
	}
	if (tag == 0)
		return 1;
	else
		return 0;

	return 0;
}
//游戏结束时的操作
void gameover(int mat[10][10], int xmax, int ymax, int tag)
{
	int num = 0;
	for (int i = 0; i < xmax; i++) {
		for (int j = 0; j < ymax; j++){
			if (mat[i][j] != 0)
				num++;
		}
	}
	if (tag == 1) {
		cct_showch(0, 4 * xmax + 3, ' ', 0, 7, 50);
		cct_gotoxy(0, 4 * xmax + 2);
	}
	cct_setcolor(0, 14);
	cout << endl << "剩余" << num << "个不可消除项，本关结束!" << endl;
	cct_setcolor();
}
//主函数直接调用本函数，本函数再调用其他所有函数
void choose(int select)
{
	int mat[10][10];
	char mat0[10][10];
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++)
			mat0[i][j] = '0';
	}
	int xmax, ymax;
	char zuobiao[10];
	int sign = 0;
	int score=0;

	cct_cls();

	if (select == 1) {
		input(xmax, ymax);
		set_matrix(xmax, ymax, mat);
		print_matrix(mat, xmax, ymax);
		input_zuobiao(zuobiao, xmax, ymax, mat);
		int cx = zuobiao[0] - 'a';
		int cy = zuobiao[1] - 48;
		find_same(mat, cx, cy, sign, xmax, ymax, mat0);
		print_result_matrix(mat0, xmax, ymax);
		print_colored_matrix(mat, mat0, xmax, ymax);
		ending();
	}

	if (select == 2) {
		input(xmax, ymax);
		set_matrix(xmax, ymax, mat);
		while (1) {
			print_matrix(mat, xmax, ymax);
			input_zuobiao(zuobiao, xmax, ymax, mat);
			int cx = zuobiao[0] - 'a';
			int cy = zuobiao[1] - 48;
			find_same(mat, cx, cy, sign, xmax, ymax, mat0);
			print_result_matrix(mat0, xmax, ymax);
			print_colored_matrix(mat, mat0, xmax, ymax);
			int que1 = que_clear(cx, cy);
			if (que1 == 'y' || que1 == 'Y') {
				clear_matrix(mat, xmax, ymax, mat0);
				print_cleared_matrix(mat, mat0, xmax, ymax);
				scoring(score, xmax, ymax, mat0,1);
				fall_matrix(mat, xmax, ymax,1);
				ending();
				for (int i = 0; i < 10; i++) {
					for (int j = 0; j < 10; j++)
						mat0[i][j] = '0';
				}   //重置mat0
				break;
			}
			else if (que1 == 'n' || que1 == 'N') {
				for (int i = 0; i < 10; i++) {
					for (int j = 0; j < 10; j++)
						mat0[i][j] = '0';
				}   //重置mat0
				continue;
			}
			else {
				ending();
				break;
			}
		}
	}

	if (select == 3) {
		input(xmax, ymax);
		set_matrix(xmax, ymax, mat);
		while (1) {
			print_matrix(mat, xmax, ymax);
			input_zuobiao(zuobiao, xmax, ymax, mat);
			int cx = zuobiao[0] - 'a';
			int cy = zuobiao[1] - 48;
			find_same(mat, cx, cy, sign, xmax, ymax, mat0);
			print_result_matrix(mat0, xmax, ymax);
			print_colored_matrix(mat, mat0, xmax, ymax);

			int que1 = que_clear(cx, cy);
			if (que1 == 'y' || que1 == 'Y') {
				clear_matrix(mat, xmax, ymax, mat0);
				print_cleared_matrix(mat, mat0, xmax, ymax);
				scoring(score, xmax, ymax, mat0, 1);
				fall_matrix(mat, xmax, ymax,1);

				if (judge_gameover(mat, xmax, ymax) == 0) {
					cout << "本次消除结束，按回车继续新一次的消除..." << endl;
					pause();
					for (int i = 0; i < 10; i++) {
						for (int j = 0; j < 10; j++)
							mat0[i][j] = '0';
					}   //重置mat0
				}
				else if (judge_gameover(mat, xmax, ymax) == 1) {
					gameover(mat, xmax, ymax,0);
					ending();
					break;
				}
			}
			else if (que1 == 'n' || que1 == 'N') {
				for (int i = 0; i < 10; i++) {
					for (int j = 0; j < 10; j++)
						mat0[i][j] = '0';
				}   //重置mat0
				continue;
			}
			else {
				ending();
				break;
			}
		}
	}

	if (select == 4) {
		select_4(mat, xmax, ymax);
	}

	if (select == 5) {
		select_5(mat, xmax, ymax);
	}

	if (select == 6) {
		select_6(mat, mat0, xmax, ymax, score);
	}

	if (select == 7) {
		select_7(mat, mat0, xmax, ymax, score);
	}
	cct_cls();
	return;
}