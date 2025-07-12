#include "main.h"

// �� ����� ���
char  enemyship_shape[5] = "^V^";

ENEMYSHIP enemyship[MAX_ENEMY];// �� ����� ���� �迭
UPOINT ptOld[MAX_ENEMY];// �� ����� ��ġ ���� �迭
BULLET enemy_bullet[MAXENEMY_BULLET];// �� �Ѿ� ���� �迭
short flag;

// �� ����� �ʱ�ȭ
void InitEnemyShip()
{
	int i, j, k;
	k = 0;

	// ���� 10 ���� 4
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
	InitBullet(); // �Ѿ� �ʱ�ȭ
}

// �� ���� ���� ����
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

// ���� ���� ���� �÷���
int CalFlag()
{
	int add;

	// ù ��° �� ���� �� ���� ����� ��
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

// �� ����� �׸��� (��ġ �̵�)
void DrawEnemyShip()
{
	UPOINT pos, posOld;
	int i;

	for (i = 0; i < MAX_ENEMY; i++)
	{
		// �� ����Ⱑ �ı����� �ʾҴٸ�
		if (enemyship[i].flag == TRUE)
		{
			posOld.x = ptOld[i].x;
			posOld.y = ptOld[i].y;

			pos.x = enemyship[i].pos.x;
			pos.y = enemyship[i].pos.y;

			// ���� ��ġ�� ����
			gotoxy(posOld);
			printf("   ");
			// ���ο� ��ġ�� �� ����� �׸���
			gotoxy(pos);
			printf("%s", enemyship_shape);
		}
	}
}

// �Ѿ� ���� �߻� ����
// ���� ��¥ ������ �ƴ� �� ���� Ȯ�� ���
int BulletNum()
{
	int num;
	while (1)
	{
		num = rand() % 40;
		// �ı��� ������ ����
		if (enemyship[num].flag == FALSE)
			continue;
		break;
	}
	return num;
}

// �� �Ѿ� �ʱ�ȭ
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

// �� �Ѿ� �߻�
void BulletShot()
{
	int i, num;
	num = BulletNum();

	for (i = 0; i < MAXENEMY_BULLET; i++)
	{
		// ���� �߻���� ���� �Ѿ��̸�
		if (enemy_bullet[i].flag == FALSE)
		{
			enemy_bullet[i].flag = TRUE;
			enemy_bullet[i].pos.x = enemyship[num].pos.x;
			enemy_bullet[i].pos.y = enemyship[num].pos.y;
			break;
		}
	}
}

// �� �Ѿ� �׸���
void DrawBullet()
{
	int i;
	UPOINT ptpos, oldpos;

	for (i = 0; i < MAXENEMY_BULLET; i++)
	{
		// �߻�� �Ѿ��̸�
		if (enemy_bullet[i].flag == TRUE)
		{
			// �Ѿ��� �Ʒ��� ������ �ش� �Ѿ� ����
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
			++enemy_bullet[i].pos.y; // ��ġ�� ����
			ptpos.x = enemy_bullet[i].pos.x;
			ptpos.y = enemy_bullet[i].pos.y;
			// ���� ��ġ�� ����
			gotoxy(oldpos);
			printf(" ");
			// ���ο� ��ġ�� �� �Ѿ� �׸���
			gotoxy(ptpos);
			printf("|");
		}
	}
}

// ���� ������ �����ߴ��� Ȯ��
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

// �� ����� �ǰ� ����
void CheckEnemyShipStrike(ENEMYSHIP* enemyship)
{
	int i, j;
	// static: ���� ���� ����
	// ���α׷� ���� �� �Ҵ�, ���� �� �ı�. �Ҵ��� ���� 1��.
	static BULLET boompos[MAXMY_BULLET];
	static int flag;

	for (i = 0; i < MAXMY_BULLET; i++)
	{
		// �ǰ� ������ ��ġ�� �ִٸ�
		if (boompos[i].flag == TRUE)
		{
			// �ش� ��ġ ���� ����
			gotoxy(boompos[i].pos);
			printf("   ");
			boompos[i].flag = FALSE;
		}
	}

	for (i = 0; i < MAXMY_BULLET; i++)
	{
		// �� �Ѿ��� �߻�Ǿ��ٸ�
		if (myship_bullet[i].flag == TRUE)
		{
			for (j = 0; j < MAX_ENEMY; j++)
			{
				// ��� �� �� �ı����� ���� ���̸�
				if (enemyship[j].flag == TRUE)
				{
					// �ǰ� ����
					if (enemyship[j].pos.x <= myship_bullet[i].pos.x &&
						myship_bullet[i].pos.x <= (enemyship[j].pos.x + 2) &&
						(enemyship[j].pos.y == myship_bullet[i].pos.y))
					{
						enemyship[j].flag = FALSE;
						gotoxy(enemyship[j].pos);
						printf(" *** ");// �� ����� ���� ���
						myship_bullet[i].flag = FALSE;// �� �Ѿ� ����
						score += 100;// ���ھ� ����
						killnum++;// �� �ı� �� ����
						// �� ����� �ǰ� ��ġ ����
						boompos[i].pos = enemyship[j].pos;
						boompos[i].flag = TRUE;
					}
				}
			}
		}
	}
}


