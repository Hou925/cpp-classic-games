/* 2254287 侯俊皓 信05 */
#include <iostream>
#include "popstar.h"
#include "cmd_console_tools.h"
using namespace std;

//打印一个方块内的星星
void print_one_block(int num, int x, int y,int color)
{
	if (num != 0) {
		cct_setcolor(num, color);
		cct_gotoxy(x, y);
		cout << "╔═╗";
		cct_gotoxy(x, y + 1);
		cout << "║★║";
		cct_gotoxy(x, y + 2);
		cout << "╚═╝";
		cct_setcolor();
	}
	else {
		cct_setcolor(15);
		cct_gotoxy(x, y);
		cout << "      ";
		cct_gotoxy(x, y + 1);
		cout << "      ";
		cct_gotoxy(x, y + 2);
		cout << "      ";
		cct_setcolor();
	}
}
//无边框所有星星打印
void print_initial_mat(int mat[10][10], int xmax, int ymax)
{
	for (int j = 0; j < xmax; j++) {
		for (int i = 0; i < ymax; i++) {
			print_one_block(mat[j][i], i * 6 + 4, j * 3 + 3,0);
		}
	}
}
//有边框所有星星打印
void print_initial_border_mat(int mat[10][10], int xmax, int ymax)
{
	for (int j = 0; j < xmax; j++) {
		for (int i = 0; i < ymax; i++) {
			print_one_block(mat[j][i], i * 8 + 4, j * 4 + 3,0);
		}
	}
}
//无边框的边框打印
void print_background(int xmax, int ymax)
{
	cct_gotoxy(0, 0);
	cout << "当前屏幕设置为：" << xmax * 3 + 8 << "行" << ymax * 6 + 7 << "列" << endl;
	cct_gotoxy(0, 1);
	cout <<" ";
	for (int i = 0; i <ymax; i++)
		cout << setw(6) << i;
	for (int i = 0; i < xmax; i++) {
		cct_gotoxy(0, i * 3 + 4);
		cout << char('A' + i);
	}

	cct_setcolor(15, 0);
	cct_gotoxy(2, 2);
	cout << "╔";
	for (int i = 0; i < ymax; i++) {
		Sleep(5);
		cout << "═══";
	}
	cout << "╗" << endl;
	for (int j = 2; j < 3 * xmax + 2; j++) {
		cct_gotoxy(2, j + 1);
		cout << "║";
		for (int i = 0; i < ymax; i++) {
			Sleep(5);
			cout << "      ";
		}
		cout << "║";
	}
	cct_gotoxy(2, 3 * xmax + 3);
	cout << "╚";
	for (int i = 0; i < ymax; i++) {
		Sleep(5);
		cout << "═══";
	}
	cout << "╝";

	cct_setcolor();
}
//有边框的边框打印
void print_background_border(int xmax, int ymax)
{
	cct_gotoxy(0, 0);
	cout << "当前屏幕设置为：" << xmax * 4 + 7 << "行" << ymax * 8 + 5 << "列" << endl;
	cct_gotoxy(0, 1);
	cout << " ";
	cout << setw(6) << 0;
	for (int i = 0; i < ymax-1; i++)
		cout << setw(8) << i + 1;
	for (int i = 0; i < xmax; i++) {
		cct_gotoxy(0, i * 4 + 4);
		cout << char('A' + i);
	}

	cct_setcolor(15, 0);
	cct_gotoxy(2, 2);
	cout << "╔";

	for (int i = 0; i < ymax - 1; i++) {
		Sleep(5);
		cout << "═══╦";
	}

	cout << "═══╗";

	for (int j = 2; j < 4 * xmax + 2; j++) {
		cct_gotoxy(2, j + 1);
		if (j % 4 != 1) {
			cout << "║";
			for (int i = 0; i < ymax; i++) {
				Sleep(5);
				cout << "      ║";
			}
		}
		else {
			cout << "╠";
			for (int i = 0; i < ymax - 1; i++) {
				Sleep(5);
				cout << "═══╬";
			}
			cout << "═══╣";
		}
	}
	cct_gotoxy(2, 4 * xmax + 2);
	cout << "╚";
	for (int i = 0; i < ymax - 1; i++) {
		cout << "═══╩";
	}
	cout << "═══╝";
	cct_setcolor();
}
//根据mat0矩阵判断点亮的星星
void highlight(int mat[10][10], char mat0[10][10], int xmax, int ymax,int x,int y, int tag)
{
	for (int i = 0; i < xmax; i++) {
		for (int j = 0; j < ymax; j++) {
			if (mat0[i][j] == '*' && tag == 1)
				print_one_block(mat[i][j], j * 6 + 4, i * 3 + 3, 7);
			else if (mat0[i][j] == '*' && tag == 2)
				print_one_block(mat[i][j], j * 8 + 4, i * 4 + 3, 7);
		}
	}
}
//可能会用到的取消点亮
void unhighlight(int mat[10][10], char mat0[10][10], int xmax, int ymax,int tag)
{
	for (int i = 0; i < xmax; i++) {
		for (int j = 0; j < ymax; j++) {
			if (mat0[i][j] == '*' && tag == 1)
				print_one_block(mat[i][j], j * 6 + 4, i * 3 + 3, 0);
			else if (mat0[i][j] == '*' && tag == 2)
				print_one_block(mat[i][j], j * 8 + 4, i * 4 + 3, 0);
		}
	}
}
//点击后合成函数
int click_hecheng(int mat[10][10], char mat0[10][10], int xmax, int ymax,int tag)
{
	int X = 0, Y = 0;
	int ret, maction;
	int keycode1, keycode2;
	int loop = 1;
	int signal = 0;

	cct_enable_mouse();
	cct_setcursor(CURSOR_INVISIBLE);	//关闭光标

	while (loop) {
		/* 读鼠标/键盘，返回值为下述操作中的某一种, 当前鼠标位置在<X,Y>处 */
		ret = cct_read_keyboard_and_mouse(X, Y, maction, keycode1, keycode2);

		if (ret == CCT_MOUSE_EVENT) {
			
			switch (maction) {
			case MOUSE_LEFT_BUTTON_CLICK:			//按下左键
				signal = 0;
				clear_matrix(mat, xmax, ymax, mat0);
				for (int i = 0; i < xmax; i++) {
					for (int j = 0; j < ymax; j++) {
						if (mat[i][j] == 0) {
							print_one_block(mat[i][j], j * (6 + tag * 2) + 4, i * (3 + tag) + 3, 0);
						}
					}
				}
				loop = 0;
				break;
			default:
				break;
			} //end of switch(maction)
		} //end of if (CCT_MOUSE_EVENT)

		else if (ret == CCT_KEYBOARD_EVENT) {

			switch (keycode1) {
			
			case 13:
				clear_matrix(mat, xmax, ymax, mat0);
				for (int i = 0; i < xmax; i++) {
					for (int j = 0; j < ymax; j++) {
						if (mat[i][j] == 0) {
							print_one_block(mat[i][j], j * (6 + tag * 2) + 4, i * (3 + tag) + 3, 0);
						}
					}
				}
				loop = 0;
				break;
			default:
				break;
			}//end of swicth(keycode1)
		}//end of else if(ret == CCT_KEYBOARD_EVENT）
	}
	cct_disable_mouse();	//禁用鼠标
	cct_setcursor(CURSOR_VISIBLE_NORMAL);	//打开光标
	if (signal == 0) {
		cct_gotoxy(0, (3 + tag) * xmax + 4 - tag);
		cout << "合成完成，回车键/单击左键下落" << endl;
	}
	return signal;
}
//点击后下落函数
void click_xialuo(int mat[10][10], char mat0[10][10], int xmax, int ymax,int tag)
{
	int X = 0, Y = 0;
	int ret, maction;
	int keycode1, keycode2;
	int loop = 1;

	cct_enable_mouse();
	cct_setcursor(CURSOR_INVISIBLE);	//关闭光标
	if (tag == 0) {
		while (loop) {
			/* 读鼠标/键盘，返回值为下述操作中的某一种, 当前鼠标位置在<X,Y>处 */
			ret = cct_read_keyboard_and_mouse(X, Y, maction, keycode1, keycode2);

			if (ret == CCT_MOUSE_EVENT) {

				switch (maction) {
				case MOUSE_LEFT_BUTTON_CLICK:			//按下左键
					falling_blocks(mat, xmax, ymax, tag);
					loop = 0;
					break;
				default:
					break;
				} //end of switch(maction)
			} //end of if (CCT_MOUSE_EVENT)

			else if (ret == CCT_KEYBOARD_EVENT) {

				switch (keycode1) {

				case 13:
					falling_blocks(mat, xmax, ymax, tag);
					loop = 0;
					break;
				default:
					break;
				}//end of swicth(keycode1)
			}//end of else if(ret == CCT_KEYBOARD_EVENT）
		}
	}
	else if (tag == 1) {
		falling_blocks(mat, xmax, ymax, tag);
	}
	cct_showch(0, (3 + tag) * xmax + 4 - tag, ' ', 0, 7, 70);
	cct_gotoxy(0, (3 + tag) * xmax + 4 - tag);
	cct_setcolor(0, 14);
	cout << "本次合成结束，按c/左键继续新一次的合成";
	cct_setcolor();
	cct_disable_mouse();	//禁用鼠标
	cct_setcursor(CURSOR_VISIBLE_NORMAL);	//打开光标
}
//移动鼠标后取消选中的判断，没有能够实现，但是放在这里
int yidongfanhui()
{
	int X = 0, Y = 0;
	int ret, maction;
	int keycode1, keycode2;
	int loop = 1;
	int sign = 0;

	cct_enable_mouse();
	cct_setcursor(CURSOR_INVISIBLE);	//关闭光标
	while (loop) {
		/* 读鼠标/键盘，返回值为下述操作中的某一种, 当前鼠标位置在<X,Y>处 */
		ret = cct_read_keyboard_and_mouse(X, Y, maction, keycode1, keycode2);
		if (ret == CCT_MOUSE_EVENT) {
			switch (maction) {
			case MOUSE_ONLY_MOVED:
				return 1;
				break;
			default:
				return 0;
				break;
			} //end of switch(maction)
		} //end of if (CCT_MOUSE_EVENT)

		else if (ret == CCT_KEYBOARD_EVENT) {

			switch (keycode1) {
			case 224:
				switch (keycode2) {
				case KB_ARROW_UP:
				case KB_ARROW_DOWN:
				case KB_ARROW_LEFT:
				case KB_ARROW_RIGHT:
					return 1;
					break;
				default:
					return 0;
					break;
				}
			default:
				return 0;
				break;
			}//end of swicth(keycode1)
		}//end of else if(ret == CCT_KEYBOARD_EVENT）
	}
	return 0;
}
//下落函数的实现
void falling_blocks(int mat[10][10], int xmax, int ymax,int tag)
{
	int i, j, k, t;
	int ox, oy, nx, ny;
	for (j = 0; j < ymax; j++) {
		for (i = xmax - 1; i >= 0; i--) {
			if (mat[i][j] == 0) {
				for (k = i - 1; k >= 0; k--) {
					if (mat[k][j] != 0)
						break;
				}
				if (k < 0)
					break;
				t = mat[i][j];
				mat[i][j] = mat[k][j];
				mat[k][j] = t;          //互换选中格子和下落格子的矩阵值
				ox = j * (6 + 2 * tag) + 4;
				oy = i * (3 + tag) + 3;
				nx = j * (6 + 2 * tag) + 4;
				ny = k * (3 + tag) + 3;
				for (ny; ny <= oy; ny++) {
					print_one_block(mat[i][j], nx, ny, 0);
					if (ny > 3)
						cct_showch(nx, ny - 1, ' ', 15, 15, 6);
					if (tag==1) {
						if ((ny + 1) % 4 == 0) {
							cct_setcolor(15, 0);
							cct_gotoxy(nx, ny - 1);
							cout << "═══";
						}
					}
					cct_setcolor();
					Sleep(10);
				}
			}
		}
	}
	for (j = 0; j < ymax; j++) {
		if (mat[xmax - 1][j] == 0 && j < ymax - 1) {
			for (k = j + 1; k <= ymax - 1; k++) {
				if (mat[xmax - 1][k] != 0)
					break;
			}
			if (k > ymax - 1)
				break;
			for (i = xmax - 1; i >= 0; i--) {
				t=mat[i][j];
				mat[i][j] = mat[i][k];
				mat[i][k] = t;
				ox = j * (6 + 2 * tag) + 4;
				oy = i * (3 + tag) + 3;
				nx = k * (6 + 2 * tag) + 4;
				ny = i * (3 + tag) + 3;
				for (nx; nx >= ox; nx -= 2) {
					if (mat[i][j] != 0) {
						print_one_block(mat[i][j], nx, ny, 0);
						if (nx - ox < 6 * (k - j + 2 * tag)) {
							cct_showch(nx + 6, ny, ' ', 15, 15, 2);
							cct_showch(nx + 6, ny + 1, ' ', 15, 15, 2);
							cct_showch(nx + 6, ny + 2, ' ', 15, 15, 2);
						}
						if (tag==1) {
							if ((nx - 4) % 8 == 0) {
								cct_setcolor(15, 0);
								cct_gotoxy(nx + 6, ny);
								cout << "║";
								cct_gotoxy(nx + 6, ny + 1);
								cout << "║";
								cct_gotoxy(nx + 6, ny + 2);
								cout << "║";
							}
						}
						cct_setcolor();
						Sleep(10);
					}
				}
			}
		}
	}
}
//以下的选项函数都把第一层鼠标/键盘循环写在里面了
void select_4(int mat[10][10],int &xmax,int &ymax)
{
	input(xmax, ymax);
	set_matrix(xmax, ymax, mat);
	cct_cls();
	cct_setconsoleborder(ymax * 6 + 7, xmax * 3 + 8);
	print_background(xmax, ymax);
	print_initial_mat(mat, xmax, ymax);
	cct_gotoxy(0, 3 * xmax + 4);
	cout << "箭头键/鼠标移动，回车键/单击左键选择并结束" << endl;

	int X = 0, Y = 0;
	int ret, maction;
	int keycode1, keycode2;
	int loop = 1;

	int cur_x = 0, cur_y = 0;  //方便后续的打印操作
	cct_enable_mouse();
	cct_setcursor(CURSOR_INVISIBLE);	//关闭光标
	print_one_block(mat[0][0], 4, 3, 15);//初始选中第一个方块

	while (loop) {
		/* 读鼠标/键盘，返回值为下述操作中的某一种, 当前鼠标位置在<X,Y>处 */
		ret = cct_read_keyboard_and_mouse(X, Y, maction, keycode1, keycode2);

		if (ret == CCT_MOUSE_EVENT) {
			if ( Y < 3 || X < 5 || Y > 3 * xmax + 2 || X > 6 * ymax + 3) {
				print_one_block(mat[cur_y][cur_x], cur_x * 6 + 4, cur_y * 3 + 3, 0);
				cct_showch(0, 3 * xmax + 4, ' ', 0, 7, 50);
				cct_gotoxy(0, 3 * xmax + 4);
				cout << "[当前鼠标] 位置非法";
			}
			else {
				print_one_block(mat[cur_y][cur_x], cur_x * 6 + 4, cur_y * 3 + 3, 0);
				cur_x = (X - 4) / 6;
				cur_y = (Y - 3) / 3;
				print_one_block(mat[cur_y][cur_x], cur_x * 6 + 4, cur_y * 3 + 3, 15);
				cct_showch(0, 3 * xmax + 4, ' ', 0, 7, 50);
				cct_gotoxy(0, 3 * xmax + 4);
				cout << "[当前鼠标] " << char(cur_y + 'A') << "行"<< cur_x << "列";
			}

			switch (maction) {
			case MOUSE_LEFT_BUTTON_CLICK:			//按下左键
				cct_showch(0, 3 * xmax + 4, ' ', 0, 7, 50);
				cct_gotoxy(0, 3 * xmax + 4);
				cout << "选中了" << char(cur_y + 'A') << "行" << cur_x << "列" << endl;
				loop = 0;
				break;
			default:
				break;
			} //end of switch(maction)
		} //end of if (CCT_MOUSE_EVENT)

		else if (ret == CCT_KEYBOARD_EVENT) {
			
			switch (keycode1) {
			case 224:
				switch (keycode2) {
				case KB_ARROW_UP:
					print_one_block(mat[cur_y][cur_x], cur_x * 6 + 4, cur_y * 3 + 3, 0);
					cur_y = (cur_y + xmax - 1) % xmax;
					print_one_block(mat[cur_y][cur_x], cur_x * 6 + 4, cur_y * 3 + 3, 15);
					cct_showch(0, 3 * xmax + 4, ' ', 0, 7, 50);
					cct_gotoxy(0, 3 * xmax + 4);
					cout << "[当前键盘] " << char(cur_y + 'A') << "行" << cur_x << "列";
					break;
				case KB_ARROW_DOWN:
					print_one_block(mat[cur_y][cur_x], cur_x * 6 + 4, cur_y * 3 + 3, 0);
					cur_y = (cur_y + xmax + 1) % xmax;
					print_one_block(mat[cur_y][cur_x], cur_x * 6 + 4, cur_y * 3 + 3, 15);
					cct_showch(0, 3 * xmax + 4, ' ', 0, 7, 50);
					cct_gotoxy(0, 3 * xmax + 4);
					cout << "[当前键盘] " << char(cur_y + 'A') << "行" << cur_x << "列";
					break;
				case KB_ARROW_LEFT:
					print_one_block(mat[cur_y][cur_x], cur_x * 6 + 4, cur_y * 3 + 3, 0);
					cur_x = (cur_x + ymax - 1) % ymax;
					print_one_block(mat[cur_y][cur_x], cur_x * 6 + 4, cur_y * 3 + 3, 15);
					cct_showch(0, 3 * xmax + 4, ' ', 0, 7, 50);
					cct_gotoxy(0, 3 * xmax + 4);
					cout << "[当前键盘] " << char(cur_y + 'A') << "行" << cur_x << "列";
					break;
				case KB_ARROW_RIGHT:
					print_one_block(mat[cur_y][cur_x], cur_x * 6 + 4, cur_y * 3 + 3, 0);
					cur_x = (cur_x + ymax + 1) % ymax;
					print_one_block(mat[cur_y][cur_x], cur_x * 6 + 4, cur_y * 3 + 3, 15);
					cct_showch(0, 3 * xmax + 4, ' ', 0, 7, 50);
					cct_gotoxy(0, 3 * xmax + 4);
					cout << "[当前键盘] " << char(cur_y + 'A') << "行" << cur_x << "列";
					break;
				}
				break;
			case 13:
				cct_showch(0, 3 * xmax + 4, ' ', 0, 7, 50);
				cct_gotoxy(0, 3 * xmax + 4);
				cout << "选中了" << char(cur_y + 'A') << "行" << cur_x << "列" << endl;
				loop = 0;
				break;
			default:
				break;
			}//end of swicth(keycode1)
		}//end of else if(ret == CCT_KEYBOARD_EVENT）
	}
	cct_disable_mouse();	//禁用鼠标
	cct_setcursor(CURSOR_VISIBLE_NORMAL);	//打开光标
	ending();
}

void select_5(int mat[10][10], int &xmax, int &ymax)
{
	input(xmax, ymax);
	set_matrix(xmax, ymax, mat);
	cct_cls();
	cct_setconsoleborder(ymax * 8 + 5, xmax * 4 + 7);
	print_background_border(xmax, ymax);
	print_initial_border_mat(mat, xmax, ymax);
	cct_gotoxy(0, 4 * xmax + 3);
	cout << "箭头键/鼠标移动，回车键/单击左键选择并结束" << endl;
	int X = 0, Y = 0;
	int ret, maction;
	int keycode1, keycode2;
	int loop = 1;

	int cur_x = 0, cur_y = 0;  //方便后续的打印操作
	cct_enable_mouse();
	cct_setcursor(CURSOR_INVISIBLE);	//关闭光标
	print_one_block(mat[0][0], 4, 3, 15);//初始选中第一个方块

	while (loop) {
		/* 读鼠标/键盘，返回值为下述操作中的某一种, 当前鼠标位置在<X,Y>处 */
		ret = cct_read_keyboard_and_mouse(X, Y, maction, keycode1, keycode2);

		if (ret == CCT_MOUSE_EVENT) {
			if (Y < 3 || X < 5 || Y > 4 * xmax + 1 || X > 8 * ymax + 2 || (Y - 2) % 4 == 0 || (X - 2) % 8 == 0 || (X - 2) % 8 == 1) {
				print_one_block(mat[cur_y][cur_x], cur_x * 8 + 4, cur_y * 4 + 3, 0);
				cct_showch(0, 4 * xmax + 3, ' ', 0, 7, 50);
				cct_gotoxy(0, 4 * xmax + 3);
				cout << "[当前鼠标] 位置非法";
			}
			else {
				print_one_block(mat[cur_y][cur_x], cur_x * 8 + 4, cur_y * 4 + 3, 0);
				cur_x = (X - 4) / 8;
				cur_y = (Y - 3) / 4;
				print_one_block(mat[cur_y][cur_x], cur_x * 8 + 4, cur_y * 4 + 3, 15);
				cct_showch(0, 4 * xmax + 3, ' ', 0, 7, 50);
				cct_gotoxy(0, 4 * xmax + 3);
				cout << "[当前鼠标] " << char(cur_y + 'A') << "行" << cur_x << "列";
			}

			switch (maction) {
			case MOUSE_LEFT_BUTTON_CLICK:			//按下左键
				cct_showch(0, 4 * xmax + 3, ' ', 0, 7, 50);
				cct_gotoxy(0, 4 * xmax + 3);
				cout << "选中了" << char(cur_y + 'A') << "行" << cur_x << "列" << endl;
				loop = 0;
				break;
			default:
				break;
			} //end of switch(maction)
		} //end of if (CCT_MOUSE_EVENT)

		else if (ret == CCT_KEYBOARD_EVENT) {

			switch (keycode1) {
			case 224:
				switch (keycode2) {
				case KB_ARROW_UP:
					print_one_block(mat[cur_y][cur_x], cur_x * 8 + 4, cur_y * 4 + 3, 0);
					cur_y = (cur_y + xmax - 1) % xmax;
					print_one_block(mat[cur_y][cur_x], cur_x * 8 + 4, cur_y * 4 + 3, 15);
					cct_showch(0, 4 * xmax + 3, ' ', 0, 7, 50);
					cct_gotoxy(0, 4 * xmax + 3);
					cout << "[当前键盘] " << char(cur_y + 'A') << "行" << cur_x << "列";
					break;
				case KB_ARROW_DOWN:
					print_one_block(mat[cur_y][cur_x], cur_x * 8 + 4, cur_y * 4 + 3, 0);
					cur_y = (cur_y + xmax + 1) % xmax;
					print_one_block(mat[cur_y][cur_x], cur_x * 8 + 4, cur_y * 4 + 3, 15);
					cct_showch(0, 4 * xmax + 3, ' ', 0, 7, 50);
					cct_gotoxy(0, 4 * xmax + 3);
					cout << "[当前键盘] " << char(cur_y + 'A') << "行" << cur_x << "列";
					break;
				case KB_ARROW_LEFT:
					print_one_block(mat[cur_y][cur_x], cur_x * 8 + 4, cur_y * 4 + 3, 0);
					cur_x = (cur_x + ymax - 1) % ymax;
					print_one_block(mat[cur_y][cur_x], cur_x * 8 + 4, cur_y * 4 + 3, 15);
					cct_showch(0, 4 * xmax + 3, ' ', 0, 7, 50);
					cct_gotoxy(0, 4 * xmax + 3);
					cout << "[当前键盘] " << char(cur_y + 'A') << "行" << cur_x << "列";
					break;
				case KB_ARROW_RIGHT:
					print_one_block(mat[cur_y][cur_x], cur_x * 8 + 4, cur_y * 4 + 3, 0);
					cur_x = (cur_x + ymax + 1) % ymax;
					print_one_block(mat[cur_y][cur_x], cur_x * 8 + 4, cur_y * 4 + 3, 15);
					cct_showch(0, 4 * xmax + 3, ' ', 0, 7, 50);
					cct_gotoxy(0, 4 * xmax + 3);
					cout << "[当前键盘] " << char(cur_y + 'A') << "行" << cur_x << "列";
					break;
				}
				break;
			case 13:
				cct_showch(0, 4 * xmax + 3, ' ', 0, 7, 50);
				cct_gotoxy(0, 4 * xmax + 3);
				cout << "选中了" << char(cur_y + 'A') << "行" << cur_x << "列" << endl;
				loop = 0;
				break;
			default:
				break;
			}//end of swicth(keycode1)
		}//end of else if(ret == CCT_KEYBOARD_EVENT）
	}
	cct_disable_mouse();	//禁用鼠标
	cct_setcursor(CURSOR_VISIBLE_NORMAL);	//打开光标
	ending();
}

void select_6(int mat[10][10], char mat0[10][10],int& xmax, int& ymax,int &score)
{
	score = 0;
	input(xmax, ymax);
	set_matrix(xmax, ymax, mat);
	cct_cls();
	cct_setconsoleborder(ymax * 6 + 7, xmax * 3 + 8);
	print_background(xmax, ymax);
	print_initial_mat(mat, xmax, ymax);
	cct_gotoxy(0, 3 * xmax + 4);
	cout << "箭头键/鼠标移动，回车键/单击左键选择，Q/单击右键结束" << endl;
	int loop1 = 1;
	while (loop1) {
		int X = 0, Y = 0;
		int ret, maction;
		int keycode1, keycode2;
		int loop = 1;
		int sign = 0;

		int cur_x = 0, cur_y = 0;  //方便后续的打印操作
		cct_enable_mouse();
		cct_setcursor(CURSOR_INVISIBLE);	//关闭光标
		print_one_block(mat[0][0], 4, 3, 15);//初始选中第一个方块

		while (loop) {
			/* 读鼠标/键盘，返回值为下述操作中的某一种, 当前鼠标位置在<X,Y>处 */
			cct_enable_mouse();
			cct_setcursor(CURSOR_INVISIBLE);	//关闭光标
			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 10; j++)
					mat0[i][j] = '0';
			}
			ret = cct_read_keyboard_and_mouse(X, Y, maction, keycode1, keycode2);
			if (ret == CCT_MOUSE_EVENT) {
				if (Y < 3 || X < 5 || Y > 3 * xmax + 2 || X > 6 * ymax + 3) {
					print_one_block(mat[cur_y][cur_x], cur_x * 6 + 4, cur_y * 3 + 3, 0);
					unhighlight(mat, mat0, xmax, ymax, 1);

					cct_showch(0, 3 * xmax + 4, ' ', 0, 7, 70);
					cct_gotoxy(0, 3 * xmax + 4);
					cout << "[当前鼠标] 位置非法";
				}
				else {
					print_one_block(mat[cur_y][cur_x], cur_x * 6 + 4, cur_y * 3 + 3, 0);
					cur_x = (X - 4) / 6;
					cur_y = (Y - 3) / 3;
					if (mat[cur_x][cur_y] == 0) {
						cct_showch(0, 3 * xmax + 4, ' ', 0, 7, 70);
						cct_gotoxy(0, 3 * xmax + 4);
						cout << "[当前鼠标] 位置非法";
					}
					else {
						print_one_block(mat[cur_y][cur_x], cur_x * 6 + 4, cur_y * 3 + 3, 15);
						cct_showch(0, 3 * xmax + 4, ' ', 0, 7, 70);
						cct_gotoxy(0, 3 * xmax + 4);
						cout << "[当前鼠标] " << char(cur_y + 'A') << "行" << cur_x << "列";
					}
				}

				switch (maction) {
				case MOUSE_LEFT_BUTTON_CLICK:			//按下左键
					if (find_same(mat, cur_y, cur_x, sign, xmax, ymax, mat0) == 0) {
						for (int i = 0; i < 10; i++) {
							for (int j = 0; j < 10; j++)
								mat0[i][j] = '0';
						}
						cct_showch(0, 3 * xmax + 4, ' ', 0, 7, 70);
						cct_gotoxy(0, 3 * xmax + 4);
						cct_setcolor(0, 14);
						cout << "周围无相同值，";
						cct_setcolor();
						cout << "箭头键/鼠标移动，回车键/单击左键选择，Q/单击右键结束" << endl;
						loop = 0;
					}
					else {
						highlight(mat, mat0, xmax, ymax, cur_x, cur_y, 1);

						loop = 0;
					}
					break;
				case MOUSE_RIGHT_BUTTON_CLICK:
					loop = 0;
					cct_gotoxy(0, 3 * xmax + 4);
					ending();
					return;
					break;
				default:
					break;
				} //end of switch(maction)

			} //end of if (CCT_MOUSE_EVENT)

			else if (ret == CCT_KEYBOARD_EVENT) {

				switch (keycode1) {
				case 224:
					switch (keycode2) {
					case KB_ARROW_UP:
						print_one_block(mat[cur_y][cur_x], cur_x * 6 + 4, cur_y * 3 + 3, 0);
						cur_y = (cur_y + xmax - 1) % xmax;
						print_one_block(mat[cur_y][cur_x], cur_x * 6 + 4, cur_y * 3 + 3, 15);
						cct_showch(0, 3 * xmax + 4, ' ', 0, 7, 70);
						cct_gotoxy(0, 3 * xmax + 4);
						cout << "[当前键盘] " << char(cur_y + 'A') << "行" << cur_x << "列";
						break;
					case KB_ARROW_DOWN:
						print_one_block(mat[cur_y][cur_x], cur_x * 6 + 4, cur_y * 3 + 3, 0);
						cur_y = (cur_y + xmax + 1) % xmax;
						print_one_block(mat[cur_y][cur_x], cur_x * 6 + 4, cur_y * 3 + 3, 15);
						cct_showch(0, 3 * xmax + 4, ' ', 0, 7, 70);
						cct_gotoxy(0, 3 * xmax + 4);
						cout << "[当前键盘] " << char(cur_y + 'A') << "行" << cur_x << "列";
						break;
					case KB_ARROW_LEFT:
						print_one_block(mat[cur_y][cur_x], cur_x * 6 + 4, cur_y * 3 + 3, 0);
						cur_x = (cur_x + ymax - 1) % ymax;
						print_one_block(mat[cur_y][cur_x], cur_x * 6 + 4, cur_y * 3 + 3, 15);
						cct_showch(0, 3 * xmax + 4, ' ', 0, 7, 70);
						cct_gotoxy(0, 3 * xmax + 4);
						cout << "[当前键盘] " << char(cur_y + 'A') << "行" << cur_x << "列";
						break;
					case KB_ARROW_RIGHT:
						print_one_block(mat[cur_y][cur_x], cur_x * 6 + 4, cur_y * 3 + 3, 0);
						cur_x = (cur_x + ymax + 1) % ymax;
						print_one_block(mat[cur_y][cur_x], cur_x * 6 + 4, cur_y * 3 + 3, 15);
						cct_showch(0, 3 * xmax + 4, ' ', 0, 7, 70);
						cct_gotoxy(0, 3 * xmax + 4);
						cout << "[当前键盘] " << char(cur_y + 'A') << "行" << cur_x << "列";
						break;
					}
					break;
				case 13:
					if (find_same(mat, cur_y, cur_x, sign, xmax, ymax, mat0) == 0) {
						for (int i = 0; i < 10; i++) {
							for (int j = 0; j < 10; j++)
								mat0[i][j] = '0';
						}
						cct_showch(0, 3 * xmax + 4, ' ', 0, 7, 70);
						cct_gotoxy(0, 3 * xmax + 4);
						cct_setcolor(0, 14);
						cout << "周围无相同值，";
						cct_setcolor();
						cout << "箭头键/鼠标移动，回车键/单击左键选择，Q/单击右键结束" << endl;
						loop = 0;
					}
					else {
						highlight(mat, mat0, xmax, ymax, cur_x, cur_y, 1);
						loop = 0;
					}
					break;
				case 81:
				case 113:
					loop = 0;
					cct_gotoxy(0, 3 * xmax + 4);
					ending();
					return;
					break;
				default:
					break;
				}//end of swicth(keycode1)
			}//end of else if(ret == CCT_KEYBOARD_EVENT）
		}
		cct_disable_mouse();	//禁用鼠标
		cct_setcursor(CURSOR_VISIBLE_NORMAL);	//打开光标
		click_hecheng(mat, mat0, xmax, ymax, 0);
		click_xialuo(mat, mat0, xmax, ymax, 0);
		scoring(score, xmax, ymax, mat0, 2);
		loop1 = 0;
	}
	cct_gotoxy(0, 3 * xmax + 4);
	ending();
}

void select_7(int mat[10][10], char mat0[10][10], int& xmax, int& ymax, int& score)
{
	score = 0;
	input(xmax, ymax);
	while (1) {
		set_matrix(xmax, ymax, mat);
		cct_cls();
		cct_setconsoleborder(ymax * 8 + 5, xmax * 4 + 7);
		print_background_border(xmax, ymax);
		print_initial_border_mat(mat, xmax, ymax);
		cct_gotoxy(0, 4 * xmax + 3);
		cout << "箭头键/鼠标移动，回车键/单击左键选择并结束" << endl;
		int loop0 = 1;
		while (loop0) {
			int X = 0, Y = 0;
			int ret, maction;
			int keycode1, keycode2;
			int loop = 1;
			int sign = 0;
			unhighlight(mat, mat0, xmax, ymax, 2);
			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 10; j++)
					mat0[i][j] = '0';
			}

			int cur_x = 0, cur_y = 0;  //方便后续的打印操作
			cct_enable_mouse();
			cct_setcursor(CURSOR_INVISIBLE);	//关闭光标
			//print_one_block(mat[0][0], 4, 3, 15);//初始选中第一个方块

			while (loop) {
				/* 读鼠标/键盘，返回值为下述操作中的某一种, 当前鼠标位置在<X,Y>处 */
				ret = cct_read_keyboard_and_mouse(X, Y, maction, keycode1, keycode2);

				if (ret == CCT_MOUSE_EVENT) {
					if (Y < 3 || X < 5 || Y > 4 * xmax + 1 || X > 8 * ymax + 2 || (Y - 2) % 4 == 0 || (X - 2) % 8 == 0 || (X - 2) % 8 == 1) {
						print_one_block(mat[cur_y][cur_x], cur_x * 8 + 4, cur_y * 4 + 3, 0);
						cct_showch(0, 4 * xmax + 3, ' ', 0, 7, 50);
						cct_gotoxy(0, 4 * xmax + 3);
						cout << "[当前鼠标] 位置非法";
					}
					else {
						print_one_block(mat[cur_y][cur_x], cur_x * 8 + 4, cur_y * 4 + 3, 0);
						cur_x = (X - 4) / 8;
						cur_y = (Y - 3) / 4;
						if (mat[cur_x][cur_y] == 0) {
							cct_showch(0, 4 * xmax + 3, ' ', 0, 7, 50);
							cct_gotoxy(0, 4 * xmax + 3);
							cout << "[当前鼠标] 位置非法";
						}
						else {
							print_one_block(mat[cur_y][cur_x], cur_x * 8 + 4, cur_y * 4 + 3, 15);
							cct_showch(0, 4 * xmax + 3, ' ', 0, 7, 50);
							cct_gotoxy(0, 4 * xmax + 3);
							cout << "[当前鼠标] " << char(cur_y + 'A') << "行" << cur_x << "列";
						}
					}

					switch (maction) {
					case MOUSE_LEFT_BUTTON_CLICK:			//按下左键
						if (find_same(mat, cur_y, cur_x, sign, xmax, ymax, mat0) == 0) {
							for (int i = 0; i < 10; i++) {
								for (int j = 0; j < 10; j++)
									mat0[i][j] = '0';
							}
							cct_showch(0, 4 * xmax + 3, ' ', 0, 7, 50);
							cct_gotoxy(0, 4 * xmax + 3);
							cct_setcolor(0, 14);
							cout << "周围无相同值，";
							cct_setcolor();
							cout << "箭头键/鼠标移动，回车键/单击左键选择，Q/单击右键结束" << endl;
							loop = 0;
						}
						else {
							highlight(mat, mat0, xmax, ymax, cur_x, cur_y, 2);
							loop = 0;
						}
						break;
					case MOUSE_RIGHT_BUTTON_CLICK:
						loop = 0;
						cct_gotoxy(0, 4 * xmax + 3);
						ending();
						return;
						break;
					default:
						break;
					} //end of switch(maction)
				} //end of if (CCT_MOUSE_EVENT)

				else if (ret == CCT_KEYBOARD_EVENT) {

					switch (keycode1) {
					case 224:
						switch (keycode2) {
						case KB_ARROW_UP:
							print_one_block(mat[cur_y][cur_x], cur_x * 8 + 4, cur_y * 4 + 3, 0);
							cur_y = (cur_y + xmax - 1) % xmax;
							print_one_block(mat[cur_y][cur_x], cur_x * 8 + 4, cur_y * 4 + 3, 15);
							cct_showch(0, 4 * xmax + 3, ' ', 0, 7, 50);
							cct_gotoxy(0, 4 * xmax + 3);
							cout << "[当前键盘] " << char(cur_y + 'A') << "行" << cur_x << "列";
							break;
						case KB_ARROW_DOWN:
							print_one_block(mat[cur_y][cur_x], cur_x * 8 + 4, cur_y * 4 + 3, 0);
							cur_y = (cur_y + xmax + 1) % xmax;
							print_one_block(mat[cur_y][cur_x], cur_x * 8 + 4, cur_y * 4 + 3, 15);
							cct_showch(0, 4 * xmax + 3, ' ', 0, 7, 50);
							cct_gotoxy(0, 4 * xmax + 3);
							cout << "[当前键盘] " << char(cur_y + 'A') << "行" << cur_x << "列";
							break;
						case KB_ARROW_LEFT:
							print_one_block(mat[cur_y][cur_x], cur_x * 8 + 4, cur_y * 4 + 3, 0);
							cur_x = (cur_x + ymax - 1) % ymax;
							print_one_block(mat[cur_y][cur_x], cur_x * 8 + 4, cur_y * 4 + 3, 15);
							cct_showch(0, 4 * xmax + 3, ' ', 0, 7, 50);
							cct_gotoxy(0, 4 * xmax + 3);
							cout << "[当前键盘] " << char(cur_y + 'A') << "行" << cur_x << "列";
							break;
						case KB_ARROW_RIGHT:
							print_one_block(mat[cur_y][cur_x], cur_x * 8 + 4, cur_y * 4 + 3, 0);
							cur_x = (cur_x + ymax + 1) % ymax;
							print_one_block(mat[cur_y][cur_x], cur_x * 8 + 4, cur_y * 4 + 3, 15);
							cct_showch(0, 4 * xmax + 3, ' ', 0, 7, 50);
							cct_gotoxy(0, 4 * xmax + 3);
							cout << "[当前键盘] " << char(cur_y + 'A') << "行" << cur_x << "列";
							break;
						}
						break;
					case 13:
						if (find_same(mat, cur_y, cur_x, sign, xmax, ymax, mat0) == 0) {
							for (int i = 0; i < 10; i++) {
								for (int j = 0; j < 10; j++)
									mat0[i][j] = '0';
							}
							cct_showch(0, 4 * xmax + 3, ' ', 0, 7, 50);
							cct_gotoxy(0, 4 * xmax + 3);
							cct_setcolor(0, 14);
							cout << "周围无相同值，";
							cct_setcolor();
							cout << "箭头键/鼠标移动，回车键/单击左键选择，Q/单击右键结束" << endl;
							loop = 0;
						}
						else {
							highlight(mat, mat0, xmax, ymax, cur_x, cur_y, 2);

							loop = 0;
						}
						break;
					case 81:
					case 113:
						loop = 0;
						cct_gotoxy(0, 4 * xmax + 3);
						ending();
						return;
						break;
					default:
						break;
					}//end of swicth(keycode1)
				}//end of else if(ret == CCT_KEYBOARD_EVENT）
			}
			cct_disable_mouse();	//禁用鼠标
			cct_setcursor(CURSOR_VISIBLE_NORMAL);	//打开光标
			click_hecheng(mat, mat0, xmax, ymax, 1);
			click_xialuo(mat, mat0, xmax, ymax, 1);
			scoring(score, xmax, ymax, mat0, 2);
			if (judge_gameover(mat, xmax, ymax)) {
				final_scoring(score, xmax, ymax, mat);
				gameover(mat, xmax, ymax, 1);
				loop0 = 0;
			}
		}
		cct_gotoxy(0, 4 * xmax + 4);
		cout << "回车继续下一关" << endl;
		pause();
	}
	
	ending();
}