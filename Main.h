
#pragma region define 설정

#define TRUE                 1
#define FALSE                0

// 적 비행기
#define MAX_ENEMY           40  
#define MAXENEMY_BASE_ROW    4   
#define MAXENEMY_BASE_COL   10  
#define MAXENEMY_BULLET     10  
#define ENEMYSHIP_BASE_POSX 20   
#define ENEMYSHIP_BASE_POSY  2  


// 내 비행기
#define MAXMY_BULLET         6   
#define MYSHIP_BASE_POSX    38  
#define MYSHIP_BASE_POSY    23  

// 키보드 맵핑
#define KEY_UP             119//w  
#define KEY_DOWN           115//s  
#define KEY_LEFT            97//a
#define KEY_RIGHT          100//d  
#define KEY_SHOT           112//p

// 기본적인 활동 범위
// TO DO: 각종 숫자들 이걸로 바꾸기
#define SIZE_SCREEN_MIN_X    2
#define SIZE_SCREEN_MAX_X   40
#define SIZE_SCREEN_MIN_Y    2
#define SIZE_SCREEN_MAX_Y   25

#pragma endregion

#pragma region 헤더 설정

#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <wincon.h>
#include "console.h"

#pragma endregion

#pragma region typedef 스트럭트 설정

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
extern: 전역 변수 선언 (모든 구역에서 사용 가능)
함수 포인터를 선언할 때도 전역 함수로 설정
외부 파일에서 작성된 변수를 타 파일에서 사용하기 위함
원본은 외부 파일에 선언된 변수
*/
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

