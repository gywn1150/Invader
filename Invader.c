#include "main.h"
// 포지션 스트럭트
UPOINT ptthisMypos;
int    timeflag = FALSE;
int    score, hiscore = 2000, killnum;
char* Aboom[8];

// 메인 화면 기능 제어
void main(void)
{
	UPOINT        ptend;
	int	loop = 1;

	// 폭발 모션
	Aboom[0] = "i<^>i ";
	Aboom[1] = "i(*)i ";
	Aboom[2] = " (* *) ";
	Aboom[3] = "(** **)";
	Aboom[4] = " (* *) ";
	Aboom[5] = "  (*)  ";
	Aboom[6] = "   *   ";
	Aboom[7] = "       ";
	ptend.x = 36;
	ptend.y = 12;
	while (loop)
	{
		DWORD         thisTickCount = GetTickCount();
		DWORD         bcount = thisTickCount;
		int           bp = 0;

		// 게임 시작
		play();
		test();

		// 흐른 시간 체크
		for (;;)
		{
			// 게임이 종료되었다면
			if (timeflag == FALSE)
			{
				thisTickCount = GetTickCount();

				// 0.1초보다 흐른 시간이 크면 실행
				// 폭발 모션을 보여주기 위함
				if (thisTickCount - bcount > 100)
				{
					// 죽은 위치 고정
					gotoxy(ptthisMypos);
					// 폭발 모션 실행
					printf("%s", Aboom[bp]);
					bp++;
					if (bp > 7)
						break;
					bcount = thisTickCount;
				}
			}
			else
				break;
		}

		// 비행기를 종료 위치로 리셋
		gotoxy(ptend);
		printf("당신의 비행기는 파괴되었습니다.");
		ptend.y += 1;
		gotoxy(ptend);
		printf("다시 할까요? (y/n)\n");

		if (_getch() == 'y')
		{
			ClearScreen();
			bp = 0;
			killnum = 0;
			timeflag = 0;
			ptend.y = 12;
			loop = 1;
		}
		else
			loop = 0;

	}
}

void test() {

}


// 게임 플레이
void  play()
{
	// Q. static으로 해놓은 이유?
	// static: 지역 변수 선언(해당 함수 내부에서만 사용 가능)
	static UPOINT ptMyoldpos;
	DWORD         gthisTickCount = GetTickCount();
	DWORD         gCount = gthisTickCount;
	DWORD         Count = gthisTickCount;
	DWORD         bulletcount = gthisTickCount;
	UPOINT        ptscore, pthi;
	int           juckspeed = 500;

	InitConsole(); // 
	InitMyship();
	Initenemyship();

	ptthisMypos.x = ptMyoldpos.x = MYSHIP_BASE_POSX;
	ptthisMypos.y = ptMyoldpos.y = MYSHIP_BASE_POSY;

	ptscore.x = 68;
	ptscore.y = 1;

	pthi.x = 2;
	pthi.y = 1;

	while (TRUE)
	{
		gthisTickCount = GetTickCount();

		// 키보드 입력
		if (_kbhit())
		{
			switch (_getch())
			{
				// 총알 슈팅
			case 'a':
				if (gthisTickCount - bulletcount > 500)
				{
					MyBulletshot(ptthisMypos);
					bulletcount = gthisTickCount;
				}
				break;

				// 왼쪽으로
			case 'j':
				ptMyoldpos.x = ptthisMypos.x;
				if (--ptthisMypos.x < 1)ptthisMypos.x = 1;
				DrawMyship(&ptthisMypos, &ptMyoldpos);
				break;

				// 오른쪽으로
			case 'l':
				ptMyoldpos.x = ptthisMypos.x;
				if (++ptthisMypos.x > 75)ptthisMypos.x = 75;
				DrawMyship(&ptthisMypos, &ptMyoldpos);
				break;
			}
		}

		if (gthisTickCount - Count > 150)
		{

			if (CheckMybullet(ptthisMypos) == 0)
			{
				if (score > 2000)
					hiscore = score;
				break;
			}
			CheckenemyBullet(enemyship);
			DrawMyBullet();
			DrawMyship(&ptthisMypos, &ptMyoldpos);
			gotoxy(ptscore);

			// 처치한 적이 40이 되면 종료
			if (killnum < 40)
				printf("점수 : %d", score);
			else
			{
				timeflag = TRUE;
				break;
			}

			// 처치한 적이 20 초과면 적의 속도 증가
			if (killnum > 20)
				juckspeed = 150;

			gotoxy(pthi);

			Count = gthisTickCount;
		}

		if (gthisTickCount - gCount > juckspeed)
		{
			Bulletshot();
			DrawBullet();
			CalenemyshipPos();
			Drawenemyship();
			if (Checkenemypos() == 1)
				break;
			gCount = gthisTickCount;
		}
	}

}
