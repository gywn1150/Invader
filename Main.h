// define 설정
#define MAX_ENEMY           40  
#define MAXENEMY_BASE_ROW    4   
#define MAXENEMY_BASE_COL   10  
#define MAXENEMY_BULLET     10  
#define ENEMYSHIP_BASE_POSX 20   
#define ENEMYSHIP_BASE_POSY  2  
#define TRUE                 1
#define FALSE                0

#define MAXMY_BULLET         3   
#define MYSHIP_BASE_POSX    38  
#define MYSHIP_BASE_POSY    23  

// 헤더 설정
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <wincon.h>
#include "console.h"

// typedef 스트럭트 설정
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

// extern: 전역 변수 선언 (모든 구역에서 사용 가능)
extern BULLET     myship_bullet[MAXMY_BULLET];
extern BULLET     enemy_bullet[MAXENEMY_BULLET];
extern ENEMYSHIP  enemyship[MAX_ENEMY];
extern int        score, killnum;

/*
Q.함수를 선언해 놓는 이유 ?
컴파일러가 앞서 함수의 반환값과 같은 공간을 마련하고,
이후의 컴파일에서 해당 함수의 입력값과 반환값을 유추하기 위한 "프로토 타입"
이를 설정하지 않으면 모든 함수를 main 함수 위에 정의해야 함

Q. 헤더에 선언하는 이유?
분할 컴파일 시 함수가 다른 파일에 있으면 반드시 선언이 필요함
*/
void DrawMyship(UPOINT* pt, UPOINT*);
void InitMyship();
void MyBulletshot(UPOINT);
void DrawMyBullet();
int  CheckMybullet(UPOINT ptthisMypos);

void Drawenemyship();
void Initenemyship();
void CalenemyshipPos();
int  Checkenemypos();
int  Calflag();
void CalTime();
void Bulletshot();
void DrawBullet();
void InitBullet();
void CheckenemyBullet(ENEMYSHIP*);

void boom(UPOINT pt, int);
void play();

