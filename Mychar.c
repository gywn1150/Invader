#include "main.h"

MYSHIP  myship;// �� ����� ����
BULLET myship_bullet[MAXMY_BULLET]; // �� �Ѿ� ����

// �� ����� ���
char  myship_shape[10] = "-i^i-";

// �� ����� �ʱ�ȭ
void InitMyship()
{
	myship.flag = TRUE;
	myship.pos.x = MYSHIP_BASE_POSX;
	myship.pos.y = MYSHIP_BASE_POSY;
}


// �� ����� �׸��� (��ġ �̵�)
void DrawMyship(UPOINT *pt,UPOINT *oldpt)
{
	// ���� ��ġ�� ����
	gotoxy(*oldpt); 
    printf("     ");// �� ������ ���� ũ��
	// ���ο� ��ġ�� �� ����� �׸���
	gotoxy(*pt); 
	printf("%s",myship_shape);
}

// �� �Ѿ� �׸���
void DrawMyBullet()
{
	int i;
	UPOINT ptpos,oldpos;
	
	// ���� ���� �Ѿ� ����(�ִ� 3��)
	for( i = 0; i < MAXENEMY_BULLET ; i++)
	{
		// �� �Ѿ� �� �߻�� ��
		if(myship_bullet[i].flag == TRUE)
		{
			// �� �Ѿ��� ȭ�� ������ ������ ���ְ�
			// �ش� �ݺ��� ����
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
		   --myship_bullet[i].pos.y; // ��ġ�� ����
		   ptpos.x = myship_bullet[i].pos.x;
		   ptpos.y = myship_bullet[i].pos.y;
		   // ���� ��ġ�� ����
		   gotoxy(oldpos);
		   printf(" ");
		   // ���ο� ��ġ�� �� �Ѿ� �׸���
		   gotoxy(ptpos);
		   printf("!");
		}
	}
}

// �� �Ѿ� ���
void MyBulletshot(UPOINT ptthisMypos)
{
	int i;
    
	// ���� ���� �Ѿ� ����(�ִ� 3��)
	for( i = 0; i < MAXMY_BULLET ; i++)
	{
		// �� �Ѿ� �� �߻���� ���� ��
		if(myship_bullet[i].flag == FALSE)
		{
		   myship_bullet[i].flag = TRUE;// �߻� ó��
		   myship_bullet[i].pos.x = ptthisMypos.x + 2;// �߾� ��ġ ���� ��
		   myship_bullet[i].pos.y = ptthisMypos.y - 1;
		   break;
		}
	}
}

// �ǰ� ����
int CheckMyShipStrike(UPOINT ptthisMypos)
{
	int i,flag;

	flag = FALSE;

	// ���� ���� �Ѿ� ����(�ִ� 10��)
	for( i = 0; i < MAXENEMY_BULLET ; i++)
	{
		// �� �Ѿ� �� �߻�� ��
		if(enemy_bullet[i].flag == TRUE)
		{ 
			// �ǰ� ����
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

	

