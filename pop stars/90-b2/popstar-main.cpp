/* 2254287 侯俊皓 信05 */
#include <iostream>
#include "popstar.h"
#include "cmd_console_tools.h"
using namespace std;

int menu()
{
	char menu;
	cout << "--------------------------------------------" << endl;
	cout << "A.命令行找出可消除项并标识" << endl;
	cout << "B.命令行完成一次消除（分步骤显示）" << endl;
	cout << "C.命令行完成一关（分步骤显示）" << endl;
	cout << "D.伪图形界面下用鼠标选择一个色块（无分割线）" << endl;
	cout << "E.伪图形界面下用鼠标选择一个色块（有分割线）" << endl;
	cout << "F.伪图形界面完成一次消除（分步骤）" << endl;
	cout << "G.伪图形界面完整版" << endl;
	cout << "Q.退出" << endl;
	cout << "--------------------------------------------" << endl;
	cout << "[请选择:] ";

	while (1){
		menu = _getche();
		if (menu >= 'A' && menu <= 'Z')
			menu += 32;
		if (menu >= 'a' && menu <= 'g' || menu == 'q')
			break;
		else
			cout <<"\b \b";

	}
	return menu - 'a' + 1;
}

int main()
{
	int select;
	while (1) {
		select = menu();
		if (select == 17) {
			cct_gotoxy(0, 30);
			break;
		}
		choose(select);
	}

	return 0;
}

