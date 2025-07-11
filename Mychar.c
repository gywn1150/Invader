#include "main.h"

MYSHIP  myship;// 내 비행기 정보
BULLET myship_bullet[MAXMY_BULLET]; // 내 총알 정보

// 내 비행기 모양
char  myship_shape[10] = "-i^i-";

// 내 비행기 초기화
void InitMyship()
{
	myship.flag = TRUE;
	myship.pos.x = MYSHIP_BASE_POSX;
	myship.pos.y = MYSHIP_BASE_POSY;
}


// 내 비행기 그리기 (위치 이동)
void DrawMyship(UPOINT *pt,UPOINT *oldpt)
{
	// 이전 위치를 비우기
	gotoxy(*oldpt); 
    printf("     ");// 내 비행기와 같은 크기
	// 새로운 위치에 내 비행기 그리기
	gotoxy(*pt); 
	printf("%s",myship_shape);
}

// 내 총알 그리기
void DrawMyBullet()
{
	int i;
	UPOINT ptpos,oldpos;
	
	// 내가 가진 총알 갯수(최대 3개)
	for( i = 0; i < MAXENEMY_BULLET ; i++)
	{
		// 내 총알 중 발사된 것
		if(myship_bullet[i].flag == TRUE)
		{
			// 내 총알이 화면 밖으로 나가면 없애고
			// 해당 반복문 종료
			if(myship_bullet[i].pos.y < 1)
			{
				myship_bullet[i].flag = FALSE;
				oldpos.x = myship_bullet[i].pos.x;
		        oldpos.y = myship_bullet[i].pos.y;
				gotoxy(oldpos);
		        printf(" ");
				break;
			}

		   oldpos.x = myship_bullet[i].pos.x;
		   oldpos.y = myship_bullet[i].pos.y;
		   --myship_bullet[i].pos.y; // 위치값 전진
		   ptpos.x = myship_bullet[i].pos.x;
		   ptpos.y = myship_bullet[i].pos.y;
		   // 이전 위치를 비우기
		   gotoxy(oldpos);
		   printf(" ");
		   // 새로운 위치에 내 총알 그리기
		   gotoxy(ptpos);
		   printf("!");
		}
	}
}

// 내 총알 쏘기
void MyBulletshot(UPOINT ptthisMypos)
{
	int i;
    
	// 내가 가진 총알 갯수(최대 3개)
	for( i = 0; i < MAXMY_BULLET ; i++)
	{
		// 내 총알 중 발사되지 않은 것
		if(myship_bullet[i].flag == FALSE)
		{
		   myship_bullet[i].flag = TRUE;// 발사 처리
		   myship_bullet[i].pos.x = ptthisMypos.x + 2;// 중앙 위치 조정 값
		   myship_bullet[i].pos.y = ptthisMypos.y - 1;
		   break;
		}
	}
}

// 피격 판정
int CheckMyShipStrike(UPOINT ptthisMypos)
{
	int i,flag;

	flag = FALSE;

	// 적이 가진 총알 갯수(최대 10개)
	for( i = 0; i < MAXENEMY_BULLET ; i++)
	{
		// 적 총알 중 발사된 것
		if(enemy_bullet[i].flag == TRUE)
		{ 
			// 피격 범위
			if( ptthisMypos.x <= enemy_bullet[i].pos.x && 
				(enemy_bullet[i].pos.x <= ptthisMypos.x + 4) && 
			    enemy_bullet[i].pos.y == ptthisMypos.y )
			{
				flag = TRUE;
				break;
			}
		}
	}
	
	if(flag == TRUE)
		return 0;
	else
		return 1;
}

	

