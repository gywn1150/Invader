
#pragma region define ����

#define TRUE                 1
#define FALSE                0

// �� �����
#define MAX_ENEMY           40  
#define MAXENEMY_BASE_ROW    4   
#define MAXENEMY_BASE_COL   10  
#define MAXENEMY_BULLET     10  
#define ENEMYSHIP_BASE_POSX 20   
#define ENEMYSHIP_BASE_POSY  2  


// �� �����
#define MAXMY_BULLET         6   
#define MYSHIP_BASE_POSX    38  
#define MYSHIP_BASE_POSY    23  

// Ű���� ����
#define KEY_UP             119//w  
#define KEY_DOWN           115//s  
#define KEY_LEFT            97//a
#define KEY_RIGHT          100//d  
#define KEY_SHOT           112//p

// �⺻���� Ȱ�� ����
// TO DO: ���� ���ڵ� �̰ɷ� �ٲٱ�
#define SIZE_SCREEN_MIN_X    2
#define SIZE_SCREEN_MAX_X   40
#define SIZE_SCREEN_MIN_Y    2
#define SIZE_SCREEN_MAX_Y   25

#pragma endregion

#pragma region ��� ����

#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <wincon.h>
#include "console.h"

#pragma endregion

#pragma region typedef ��Ʈ��Ʈ ����

typedef struct {
	int flag;
	UPOINT pos;
} MYSHIP;

typedef struct {
	int flag;
	UPOINT pos;
} BULLET;

typedef struct {
	int flag;
	UPOINT pos;
} ENEMYSHIP;

#pragma endregion

#pragma region MyRegion

/*
extern: ���� ���� ���� (��� �������� ��� ����)
�Լ� �����͸� ������ ���� ���� �Լ��� ����
�ܺ� ���Ͽ��� �ۼ��� ������ Ÿ ���Ͽ��� ����ϱ� ����
������ �ܺ� ���Ͽ� ����� ����
*/
extern BULLET     myship_bullet[MAXMY_BULLET];
extern BULLET     enemy_bullet[MAXENEMY_BULLET];
extern ENEMYSHIP  enemyship[MAX_ENEMY];
extern int        score, killnum;

/*
Q.�Լ��� ������ ���� ���� ?
�����Ϸ��� �ռ� �Լ��� ��ȯ���� ���� ������ �����ϰ�,
������ �����Ͽ��� �ش� �Լ��� �Է°��� ��ȯ���� �����ϱ� ���� "������ Ÿ��"
�̸� �������� ������ ��� �Լ��� main �Լ� ���� �����ؾ� ��

Q. ����� �����ϴ� ����?
���� ������ �� �Լ��� �ٸ� ���Ͽ� ������ �ݵ�� ������ �ʿ���
*/
// Mychar.c
void DrawMyship(UPOINT* pt, UPOINT*);
void InitMyship();
void MyBulletshot(UPOINT);
void DrawMyBullet();
int  CheckMyShipStrike(UPOINT ptthisMypos);

// Juck.c
void DrawEnemyShip();
void InitEnemyShip();
void CleanEnemyShipPos();
int  CheckEnemyPos();
int  CalFlag();
void BulletShot();
void DrawBullet();
void InitBullet();
void CheckEnemyShipStrike(ENEMYSHIP*);

// invader.c
void play();

#pragma endregion

