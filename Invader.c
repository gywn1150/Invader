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
	Aboom[0] = "i<^>i";
	Aboom[1] = "i(*)i";
	Aboom[2] = " (* *) ";
	Aboom[3] = "(** **)";
	Aboom[4] = " (* *) ";
	Aboom[5] = "  (*)  ";
	Aboom[6] = "   *   ";
	Aboom[7] = "       ";
	// 문구 위치
	ptend.x = 36;
	ptend.y = 12;
	while (loop)
	{
		DWORD         thisTickCount = GetTickCount();
		DWORD         bcount = thisTickCount;
		int           bp = 0;

		// 게임 시작
		play();

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

	InitConsole();// 화면 초기화 
	InitMyship();// 내 비행기 초기화
	InitEnemyShip();

	// 내 비행기 초기 위치
	ptthisMypos.x = ptMyoldpos.x = MYSHIP_BASE_POSX;
	ptthisMypos.y = ptMyoldpos.y = MYSHIP_BASE_POSY;

	ptscore.x = 68;
	ptscore.y = 1;

	pthi.x = 2;
	pthi.y = 1;

	// 계속 돌아가기
	while (TRUE)
	{
		gthisTickCount = GetTickCount();

		// 키보드 입력
		if (_kbhit())
		{
			switch (_getch())
			{
				// 총알 슈팅
			case KEY_SHOT:
				// 최소 0.5초 간격 입력
				if (gthisTickCount - bulletcount > 500)
				{
					MyBulletshot(ptthisMypos);// 내 총알 쏘기
					bulletcount = gthisTickCount;
				}
				break;

				// 왼쪽
			case KEY_LEFT:
				ptMyoldpos = ptthisMypos;
				// 좌측 범위 제한
				if (--ptthisMypos.x < 1) ptthisMypos.x = 1;
				DrawMyship(&ptthisMypos, &ptMyoldpos);// 내 비행기 그리기 (위치 이동)
				break;

				// 오른쪽
			case KEY_RIGHT:
				ptMyoldpos = ptthisMypos;
				// 우측 범위 제한
				if (++ptthisMypos.x > 75) ptthisMypos.x = 75;
				DrawMyship(&ptthisMypos, &ptMyoldpos);// 내 비행기 그리기 (위치 이동)
				break;

				// 위
			case KEY_UP:
				ptMyoldpos = ptthisMypos;
				// 위측 범위 제한
				if (--ptthisMypos.y < 10) ptthisMypos.y = 10;
				DrawMyship(&ptthisMypos, &ptMyoldpos);// 내 비행기 그리기 (위치 이동)
				break;

				// 아래
			case KEY_DOWN:
				ptMyoldpos = ptthisMypos;
				// 아래측 범위 제한
				if (++ptthisMypos.y > 25) ptthisMypos.y = 25;
				DrawMyship(&ptthisMypos, &ptMyoldpos);// 내 비행기 그리기 (위치 이동)
				break;
			}
		}

		// 움직임 그리기 (0.15초 간격)
		if (gthisTickCount - Count > 150)
		{
			// 내 비행기 피격 판정
			if (CheckMyShipStrike(ptthisMypos) == 0)
			{
				// 2000점 이상이면 높은 점수에 등록
				// 현재 하이스코어 활용 안 함
				if (score > 2000)
					hiscore = score;
				break;
			}
			CheckEnemyShipStrike(enemyship);// 적 비행기 피격 판정
			DrawMyBullet();// 내 총알 그리기
			DrawMyship(&ptthisMypos, &ptMyoldpos);// 내 비행기 그리기 (위치 이동)
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

		// 적 속도에 따라 변동 (0.5 -> 0.15)
		if (gthisTickCount - gCount > juckspeed)
		{
			BulletShot();// 적 총알 발사
			DrawBullet();// 적 총알 그리기
			CleanEnemyShipPos();// 적 진행 방향 조정
			DrawEnemyShip();// 적 비행기 그리기 (위치 이동)
			// 적이 끝까지 도착했는지 확인
			if (CheckEnemyPos() == 1)
				break;
			gCount = gthisTickCount;
		}
	}

}
