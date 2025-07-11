#include <stdio.h>
#include "console.h"

HANDLE hout;

// ��� ȭ�� �������� Ŭ����
void ClearScreen()
{
	int i, j;
	UPOINT pos;

	for (i = 1; i < 25; i++)
	{
		for (j = 1; j < 80; j++)
		{
			pos.x = j;
			pos.y = i;
			gotoxy(pos);
			printf(" ");
		}
	}
}

// ȭ�� �ʱ�ȭ
void InitConsole()
{
	CONSOLE_CURSOR_INFO coninfo;

	coninfo.bVisible = FALSE;
	coninfo.dwSize = 1;

	hout = GetStdHandle(STD_OUTPUT_HANDLE);

	// ȭ�� Ŀ�� �����
	SetConsoleCursorInfo(hout, &coninfo);

	CheckScreenSize();
}

// ���ϴ� ��ġ�� Ŀ�� �̵�
void gotoxy(UPOINT pt)
{
	COORD pos;

	pos.X = pt.x;
	pos.Y = pt.y;

	SetConsoleCursorPosition(hout, pos);
}

// ��ũ�� ����� �ð������� �����ִ� �Լ�
void CheckScreenSize() {
	int i, j;
	UPOINT pos;

	for (i = 0; i < 26; i++)
	{
		pos.x = 81;
		pos.y = i;
		gotoxy(pos);
		printf("|");
	}

	for (i = 0; i < 81; i++)
	{
		pos.x = i;
		pos.y = 0;
		gotoxy(pos);
		printf("��");

		pos.x = i;
		pos.y = 26;
		gotoxy(pos);
		printf("��");
	}
}
