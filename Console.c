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

	CheckScreenSize();
}

// 원하는 위치로 커서 이동
void gotoxy(UPOINT pt)
{
	COORD pos;

	pos.X = pt.x;
	pos.Y = pt.y;

	SetConsoleCursorPosition(hout, pos);
}

// 스크린 사이즈를 시각적으로 보여주는 함수
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
		printf("─");

		pos.x = i;
		pos.y = 26;
		gotoxy(pos);
		printf("─");
	}
}
