#include "main.h"
// ������ ��Ʈ��Ʈ
UPOINT ptthisMypos;
int    timeflag = FALSE;
int    score, hiscore = 2000, killnum;
char* Aboom[8];

// ���� ȭ�� ��� ����
void main(void)
{
	UPOINT        ptend;
	int	loop = 1;

	// ���� ���
	Aboom[0] = "i<^>i";
	Aboom[1] = "i(*)i";
	Aboom[2] = " (* *) ";
	Aboom[3] = "(** **)";
	Aboom[4] = " (* *) ";
	Aboom[5] = "  (*)  ";
	Aboom[6] = "   *   ";
	Aboom[7] = "       ";
	// ���� ��ġ
	ptend.x = 36;
	ptend.y = 12;
	while (loop)
	{
		DWORD         thisTickCount = GetTickCount();
		DWORD         bcount = thisTickCount;
		int           bp = 0;

		// ���� ����
		play();

		// �帥 �ð� üũ
		for (;;)
		{
			// ������ ����Ǿ��ٸ�
			if (timeflag == FALSE)
			{
				thisTickCount = GetTickCount();

				// 0.1�ʺ��� �帥 �ð��� ũ�� ����
				// ���� ����� �����ֱ� ����
				if (thisTickCount - bcount > 100)
				{
					// ���� ��ġ ����
					gotoxy(ptthisMypos);
					// ���� ��� ����
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

		// ����⸦ ���� ��ġ�� ����
		gotoxy(ptend);
		printf("����� ������ �ı��Ǿ����ϴ�.");
		ptend.y += 1;
		gotoxy(ptend);
		printf("�ٽ� �ұ��? (y/n)\n");

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

// ���� �÷���
void  play()
{
	// Q. static���� �س��� ����?
	// static: ���� ���� ����(�ش� �Լ� ���ο����� ��� ����)
	static UPOINT ptMyoldpos;
	DWORD         gthisTickCount = GetTickCount();
	DWORD         gCount = gthisTickCount;
	DWORD         Count = gthisTickCount;
	DWORD         bulletcount = gthisTickCount;
	UPOINT        ptscore, pthi;
	int           juckspeed = 500;

	InitConsole();// ȭ�� �ʱ�ȭ 
	InitMyship();// �� ����� �ʱ�ȭ
	InitEnemyShip();

	// �� ����� �ʱ� ��ġ
	ptthisMypos.x = ptMyoldpos.x = MYSHIP_BASE_POSX;
	ptthisMypos.y = ptMyoldpos.y = MYSHIP_BASE_POSY;

	ptscore.x = 68;
	ptscore.y = 1;

	pthi.x = 2;
	pthi.y = 1;

	// ��� ���ư���
	while (TRUE)
	{
		gthisTickCount = GetTickCount();

		// Ű���� �Է�
		if (_kbhit())
		{
			switch (_getch())
			{
				// �Ѿ� ����
			case KEY_SHOT:
				// �ּ� 0.5�� ���� �Է�
				if (gthisTickCount - bulletcount > 500)
				{
					MyBulletshot(ptthisMypos);// �� �Ѿ� ���
					bulletcount = gthisTickCount;
				}
				break;

				// ����
			case KEY_LEFT:
				ptMyoldpos = ptthisMypos;
				// ���� ���� ����
				if (--ptthisMypos.x < 1) ptthisMypos.x = 1;
				DrawMyship(&ptthisMypos, &ptMyoldpos);// �� ����� �׸��� (��ġ �̵�)
				break;

				// ������
			case KEY_RIGHT:
				ptMyoldpos = ptthisMypos;
				// ���� ���� ����
				if (++ptthisMypos.x > 75) ptthisMypos.x = 75;
				DrawMyship(&ptthisMypos, &ptMyoldpos);// �� ����� �׸��� (��ġ �̵�)
				break;

				// ��
			case KEY_UP:
				ptMyoldpos = ptthisMypos;
				// ���� ���� ����
				if (--ptthisMypos.y < 10) ptthisMypos.y = 10;
				DrawMyship(&ptthisMypos, &ptMyoldpos);// �� ����� �׸��� (��ġ �̵�)
				break;

				// �Ʒ�
			case KEY_DOWN:
				ptMyoldpos = ptthisMypos;
				// �Ʒ��� ���� ����
				if (++ptthisMypos.y > 25) ptthisMypos.y = 25;
				DrawMyship(&ptthisMypos, &ptMyoldpos);// �� ����� �׸��� (��ġ �̵�)
				break;
			}
		}

		// ������ �׸��� (0.15�� ����)
		if (gthisTickCount - Count > 150)
		{
			// �� ����� �ǰ� ����
			if (CheckMyShipStrike(ptthisMypos) == 0)
			{
				// 2000�� �̻��̸� ���� ������ ���
				// ���� ���̽��ھ� Ȱ�� �� ��
				if (score > 2000)
					hiscore = score;
				break;
			}
			CheckEnemyShipStrike(enemyship);// �� ����� �ǰ� ����
			DrawMyBullet();// �� �Ѿ� �׸���
			DrawMyship(&ptthisMypos, &ptMyoldpos);// �� ����� �׸��� (��ġ �̵�)
			gotoxy(ptscore);

			// óġ�� ���� 40�� �Ǹ� ����
			if (killnum < 40)
				printf("���� : %d", score);
			else
			{
				timeflag = TRUE;
				break;
			}

			// óġ�� ���� 20 �ʰ��� ���� �ӵ� ����
			if (killnum > 20)
				juckspeed = 150;

			gotoxy(pthi);

			Count = gthisTickCount;
		}

		// �� �ӵ��� ���� ���� (0.5 -> 0.15)
		if (gthisTickCount - gCount > juckspeed)
		{
			BulletShot();// �� �Ѿ� �߻�
			DrawBullet();// �� �Ѿ� �׸���
			CleanEnemyShipPos();// �� ���� ���� ����
			DrawEnemyShip();// �� ����� �׸��� (��ġ �̵�)
			// ���� ������ �����ߴ��� Ȯ��
			if (CheckEnemyPos() == 1)
				break;
			gCount = gthisTickCount;
		}
	}

}
