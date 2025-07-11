#include <stdio.h>
#include "console.h"

HANDLE hout;

// 모든 화면 공백으로 클리어
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

// 화면 초기화
void InitConsole()
{
	CONSOLE_CURSOR_INFO coninfo;

	coninfo.bVisible = FALSE;
	coninfo.dwSize = 1;

	hout = GetStdHandle(STD_OUTPUT_HANDLE);

	// 화면 커서 숨기기
	SetConsoleCursorInfo(hout, &coninfo);
}

// 원하는 위치로 커서 이동
void gotoxy(UPOINT pt)
{
	COORD pos;

	pos.X = pt.x;
	pos.Y = pt.y;

	SetConsoleCursorPosition(hout, pos);
}
