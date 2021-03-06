// Sudoku.cpp : 定義主控台應用程式的進入點。
//

#include "pch.h"
#include <iostream>
#include <conio.h>
using namespace std;


void updateZ(int Z[9][9][10], int r, int c, int num)
{
	int x, y;
	for (x = 0; x < 9; x++)//把那個題目num的所有同列的那個num設0(ex題目有8就把同列的8都設為0 5.0,8~5,8,8都設0)
		Z[r][x][num] = 0;
	for (y = 0; y < 9; y++)//把同行的全部設0(ex 把0,7,8~8,7,8都設為0)
		Z[y][c][num] = 0;
	for (y = r / 3 * 3; y <= r / 3 * 3 + 2; y++)//九宮格從同列1、3、6開始跑
	{
		for (x = c / 3 * 3; x <= c / 3 * 3 + 2; x++)//從同行的1、3、6開始跑
		{
			Z[y][x][num] = 0;//把九宮格內的那個數(ex 8)都設為0
		}
	}
	Z[r][c][num] = 1;//那行那列那數設為1(ex把那格的8設為1(5,7,8設為1))
}

int findZ(int Z[9][9][10], int r, int c)
{
	int i, count, num;
	count = 0;
	for (i = 1; i <= 9; i++)
	{
		if (Z[r][c][i] == 1)
		{
			count++;
			num = i;
		}
	}
	if (count == 1)
		return num;
	else
		return 0;
}

void solve(int Q[9][9], int A[9][9])
{
	int Z[9][9][10];//一格裡給9個數字1~9，開陣列[10]，[0]不用，有機會是答案的都設1，否則為0
	int r, c, i;
	for (r = 0; r < 9; r++)
	{
		for (c = 0; c < 9; c++)
		{
			if (Q[r][c] > 0)//若題目空格有數字
			{
				A[r][c] = Q[r][c];//則答案與空格裡的數字一樣
				for (i = 1; i <= 9; i++)//那格裡有機會是答案的只有題目那個數字，他設1,其他8個數字設0
					Z[r][c][i] = 0;
				Z[r][c][Q[r][c]] = 1;
			}
			else
			{
				A[r][c] = 0;
				for (i = 1; i <= 9; i++)
					Z[r][c][i] = 1;
			}
		}
	}
	for (r = 0; r < 9; r++)
	{
		for (c = 0; c < 9; c++)
		{
			if (Q[r][c] > 0)//如果題目裡有數字(ex5,7格有8)
			{
				updateZ(Z, r, c, Q[r][c]);//把同行同列都設0  r,c被填上Q了所以要更新Z
			}
		}
	}
	int flag = 1, num;
	while (flag == 1)//沒人更新就跳出迴圈
	{
		flag = 0;
		for (r = 0; r < 9; r++)//找9*9內
		{
			for (c = 0; c < 9; c++)
			{
				if (A[r][c] == 0)//答案還未填
				{
					num = findZ(Z, r, c);
					if (num > 0)
					{
						flag = 1;//有更新就把flag設為1
						A[r][c] = num;
						updateZ(Z, r, c, num);
					}
				}
			}
		}
	}
}
void printUI(int M[9][9], int r, int c)
{	
			
	int R, C;
	cout << "------------------------------------------------" << endl;
	for (R = 0; R < 9; R++)
	{
		for (C = 0; C < 9; C++)
		{
			if(C==0)
				cout << "|";
			if (R == r && C == c)
			{
				if (M[R][c] == 0)
					cout << "[   ]";
				else
					cout << "[ " << M[R][C] << " ]";
			}
			else if (M[R][C] > 0)
				cout << "  " << M[R][C] << "  ";
			else
				cout << "     ";
			if ((C + 1) % 3 == 0)
				cout << "|";
		}
		if ((C + 1) % 3 == 0)
			cout << endl << endl << "|" << endl;
		else
		if ((R + 1) % 3 == 0)
			cout << endl << "------------------------------------------------" << endl;
		else
				cout << endl << endl<<endl;

	}
}

bool compare(int M[9][9], int M1[9][9])//bool布蘭 true=1 0 false=0
{
	int r, c;
	for (r = 0; r < 9; r++)
	{
		for (c = 0; c < 9; c++)
			if (M[r][c] != M1[r][c])
				return false;
	}
	return true;
}

int main()
{
	int Q[9][9] = { { 5, 3, 0, 0, 7 }, { 6, 0, 0, 1, 9, 5 }, { 0, 9, 8, 0, 0, 0, 0, 6 }, { 8, 0, 0, 0, 6, 0, 0, 0, 3 }, { 4, 0, 0, 8, 0, 3, 0, 0, 1 }, { 7, 0, 0, 0, 2, 0, 0, 0, 6 }, { 0, 6, 0, 0, 0, 0, 2, 8 }, { 0, 0, 0, 4, 1, 9, 0, 0, 5 }, { 0, 0, 0, 0, 8, 0, 0, 7, 9 } };
	int A[9][9],A1[9][9];
	int r = 0, c = 0,R,C;
	char x, y;
	for (R = 0; R < 9; R++)//????
	{
		for (C = 0; C < 9; C++)
			A[R][C] = Q[R][C];
	}
	do {
		system("cls");	
		printUI(A,r,c);//hw write printUI 將你填的答案顯示出來&美化
		x = _getch();//輸入數字或上下鍵
		if (x >= '0'&& x <= '9')
		{
			if (Q[r][c] == 0)//有題目的地方不能跳
				A[r][c] = x - '0';
		}
		if (x == -32)
		{
			y = _getch();
			switch (y)
			{
			case 72://向上
				r = (r + 8) % 9;
				break;
			case 75://向左
				c = (c + 8) % 9;
				break;
			case 77://向右
				c = (c + 1) % 9;
				break;
			case 80://向下
				r = (r + 1) % 9;
				break;
			}
		}
	} while (x != 13);
	solve(Q, A1);

	if (compare(A, A1))//A1是電腦的答案 A是你的答案
		cout << "Correct" << endl;
	else
		cout << "Try again" << endl;

	return 0;
}

