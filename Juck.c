#include "main.h"

// 적 비행기 모양
char  enemyship_shape[5] = "^V^";

ENEMYSHIP enemyship[MAX_ENEMY];// 적 비행기 정보 배열
UPOINT ptOld[MAX_ENEMY];// 적 비행기 위치 정보 배열
BULLET enemy_bullet[MAXENEMY_BULLET];// 적 총알 정보 배열
short flag;

// 적 비행기 초기화
void InitEnemyShip()
{
	int i, j, k;
	k = 0;

	// 가로 10 세로 4
	for (i = 0; i < MAXENEMY_BASE_ROW; i++)
	{
		for (j = 0; j < MAXENEMY_BASE_COL; j++)
		{
			enemyship[k].flag = TRUE;
			enemyship[k].pos.x = ENEMYSHIP_BASE_POSX + j * 4;
			enemyship[k].pos.y = ENEMYSHIP_BASE_POSY + i * 2;
			ptOld[k].x = ENEMYSHIP_BASE_POSX + j * 4;
			ptOld[k].y = ENEMYSHIP_BASE_POSY + i * 2;
			k++;
		}
	}
	InitBullet(); // 총알 초기화
}

// 적 진행 방향 조정
void CleanEnemyShipPos()
{
	int i, j, k, XAdd, YAdd;

	k = 0;

	YAdd = CalFlag();
	if (flag == FALSE)
		XAdd = 1;
	else
		XAdd = -1;

	for (i = 0; i < MAXENEMY_BASE_ROW; i++)
	{
		for (j = 0; j < MAXENEMY_BASE_COL; j++)
		{
			ptOld[k].x = enemyship[k].pos.x;
			ptOld[k].y = enemyship[k].pos.y;
			enemyship[k].pos.x += XAdd;
			enemyship[k].pos.y += YAdd;
			k++;
		}
	}
}

// 진행 방향 결정 플래그
int CalFlag()
{
	int add;

	// 첫 번째 적 기준 양 옆에 닿았을 때
	if (enemyship[0].pos.x < 2 || enemyship[0].pos.x > 40)
	{
		if (flag == TRUE)
			flag = FALSE;
		else
			flag = TRUE;
		add = 1;
	}
	else
		add = 0;
	return add;
}

// 적 비행기 그리기 (위치 이동)
void DrawEnemyShip()
{
	UPOINT pos, posOld;
	int i;

	for (i = 0; i < MAX_ENEMY; i++)
	{
		// 적 비행기가 파괴되지 않았다면
		if (enemyship[i].flag == TRUE)
		{
			posOld.x = ptOld[i].x;
			posOld.y = ptOld[i].y;

			pos.x = enemyship[i].pos.x;
			pos.y = enemyship[i].pos.y;

			// 이전 위치를 비우기
			gotoxy(posOld);
			printf("   ");
			// 새로운 위치에 적 비행기 그리기
			gotoxy(pos);
			printf("%s", enemyship_shape);
		}
	}
}

// 총알 랜덤 발사 로직
// 현재 진짜 랜덤은 아닌 것 같음 확인 요망
int BulletNum()
{
	int num;
	while (1)
	{
		num = rand() % 40;
		// 파괴된 비행기는 제외
		if (enemyship[num].flag == FALSE)
			continue;
		break;
	}
	return num;
}

// 적 총알 초기화
void InitBullet()
{
	int i;

	for (i = 0; i < MAXENEMY_BULLET; i++)
	{
		enemy_bullet[i].flag = FALSE;
		enemy_bullet[i].pos.x = 0;
		enemy_bullet[i].pos.y = 0;
	}
}

// 적 총알 발사
void BulletShot()
{
	int i, num;
	num = BulletNum();

	for (i = 0; i < MAXENEMY_BULLET; i++)
	{
		// 아직 발사되지 않은 총알이면
		if (enemy_bullet[i].flag == FALSE)
		{
			enemy_bullet[i].flag = TRUE;
			enemy_bullet[i].pos.x = enemyship[num].pos.x;
			enemy_bullet[i].pos.y = enemyship[num].pos.y;
			break;
		}
	}
}

// 적 총알 그리기
void DrawBullet()
{
	int i;
	UPOINT ptpos, oldpos;

	for (i = 0; i < MAXENEMY_BULLET; i++)
	{
		// 발사된 총알이면
		if (enemy_bullet[i].flag == TRUE)
		{
			// 총알이 아래에 닿으면 해당 총알 끄기
			if (enemy_bullet[i].pos.y > 23)
			{
				enemy_bullet[i].flag = FALSE;
				oldpos.x = enemy_bullet[i].pos.x;
				oldpos.y = enemy_bullet[i].pos.y;
				gotoxy(oldpos);
				printf(" ");
				break;
			}
			oldpos.x = enemy_bullet[i].pos.x;
			oldpos.y = enemy_bullet[i].pos.y;
			++enemy_bullet[i].pos.y; // 위치값 전진
			ptpos.x = enemy_bullet[i].pos.x;
			ptpos.y = enemy_bullet[i].pos.y;
			// 이전 위치를 비우기
			gotoxy(oldpos);
			printf(" ");
			// 새로운 위치에 적 총알 그리기
			gotoxy(ptpos);
			printf("|");
		}
	}
}

// 적이 끝까지 도착했는지 확인
int CheckEnemyPos()
{
	int flag = FALSE, i;

	for (i = 0; i < MAX_ENEMY; i++)
	{
		if (enemyship[i].flag == TRUE && enemyship[i].pos.y == 23)
		{
			flag = TRUE;
			break;
		}
	}

	return flag;
}

// 적 비행기 피격 판정
void CheckEnemyShipStrike(ENEMYSHIP* enemyship)
{
	int i, j;
	// static: 내부 정적 변수
	// 프로그램 시작 시 할당, 종료 시 파괴. 할당은 최초 1번.
	static BULLET boompos[MAXMY_BULLET];
	static int flag;

	for (i = 0; i < MAXMY_BULLET; i++)
	{
		// 피격 판정된 위치가 있다면
		if (boompos[i].flag == TRUE)
		{
			// 해당 위치 잔해 비우기
			gotoxy(boompos[i].pos);
			printf("   ");
			boompos[i].flag = FALSE;
		}
	}

	for (i = 0; i < MAXMY_BULLET; i++)
	{
		// 내 총알이 발사되었다면
		if (myship_bullet[i].flag == TRUE)
		{
			for (j = 0; j < MAX_ENEMY; j++)
			{
				// 모든 적 중 파괴되지 않은 것이면
				if (enemyship[j].flag == TRUE)
				{
					// 피격 범위
					if (enemyship[j].pos.x <= myship_bullet[i].pos.x &&
						myship_bullet[i].pos.x <= (enemyship[j].pos.x + 2) &&
						(enemyship[j].pos.y == myship_bullet[i].pos.y))
					{
						enemyship[j].flag = FALSE;
						gotoxy(enemyship[j].pos);
						printf(" *** ");// 적 비행기 폭발 모션
						myship_bullet[i].flag = FALSE;// 내 총알 끄기
						score += 100;// 스코어 증가
						killnum++;// 적 파괴 수 증가
						// 적 비행기 피격 위치 저장
						boompos[i].pos = enemyship[j].pos;
						boompos[i].flag = TRUE;
					}
				}
			}
		}
	}
}


