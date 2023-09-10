#include <Novice.h>

const char kWindowTitle[] = "GC2B_04_サワダカズキ";


enum SCENE {
	TITLE,//タイトル画面
	STAGE1,//ゲーム画面
	STAGE2,
	STAGE3,
	GAMECLEAR,//ゲームクリア
	GAMECLEAR2,//STAGE2
	GAMECLEAR3,//STAGE3
	GAMEOVER,//ゲームオーバー
	GAMEOVER2,//STAGE2
};

int sceneNo = TITLE;
//画像読み込み-----------------------------------------------------------
//Map Classに移動する



//ブロックサイズの設定
const int KBlockSize = 32;
int playerPosX = 13 * KBlockSize;
int playerPosY = 672;
int playerR = 32;
int playerSpeed = KBlockSize;

int playerTmpX = 0;
int playerTmpY = 0;
int playerMapX = 0;
int playerMapY = 0;

int caramelMapX = 0;
int caramelMapY = 0;
int caramelTmpX = 0;
int caramelTmpY;

int blockPosX = 32;
int blockPosY = 32;
int blockTmpX = 0;
int blockTmpY = 0;
int blockMapX = 0;
int blockMapY = 0;

//ステージ2
/*int playerPosX = 13 * KBlockSize;
int playerPosY = 320;*/


//タイマー
int goalTimer = 60;//ゴール
int caramelTimer = 200;//カラメル
int deathTimer = 60;//ゲームオーバー
//フラグ-----------
int caramelFlag = 0;

//マップずらすための変数
int mapShift = 200;

int map[23][28] = {
{80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,83, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,0 ,0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,0 ,0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 0, 0,72, 0,73, 0,74, 0,75, 0,76, 0, 0, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0,41, 0, 4, 0,31, 0, 8, 0,23, 0,10, 0,40, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0,44, 0, 2, 0, 6, 0,13, 0,16, 0,56, 0,11, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0,36, 0,46, 0,15, 0, 3, 0,24, 0,17, 0,48, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,80, 0},
{80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80}
};

int mapFormat[23][28] = {
{80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,83, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,0 ,0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,0 ,0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 0, 0,72, 0,73, 0,74, 0,75, 0,76, 0, 0, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0,41, 0, 4, 0,31, 0, 8, 0,23, 0,10, 0,40, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0,44, 0, 2, 0, 6, 0,13, 0,16, 0,56, 0,11, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0,36, 0,46, 0,15, 0, 3, 0,24, 0,17, 0,48, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,80, 0},
{80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80}
};

int map2[23][28] = {
{80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,83, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,0 ,0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,0 ,0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0,72, 0,73, 0,74, 0,75, 0,76, 0,77, 0,78, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0,13, 0,35, 0,33, 0,52, 0, 6, 0,28, 0,28, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0,11, 0,12, 0,24, 0, 8, 0,11, 0,46, 0, 3, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 4, 0,46, 0,53, 0,64, 0,38, 0,20, 0, 5, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,80, 0},
{80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80}
};

int mapFormat2[23][28] = {
{80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,83, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,0 ,0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,0 ,0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0,72, 0,73, 0,74, 0,75, 0,76, 0,77, 0,78, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0,13, 0,35, 0,33, 0,52, 0, 6, 0,28, 0,28, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0,11, 0,12, 0,24, 0, 8, 0,11, 0,46, 0, 3, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 4, 0,46, 0,53, 0,64, 0,38, 0,20, 0, 5, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,80, 0},
{80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80}
};

int map3[23][28] = {
{80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,83, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,0 ,0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,0 ,0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 0, 0,72, 0,73, 0,74, 0,75, 0,76, 0, 0, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 1, 0, 9, 0,15, 0,17, 0,41, 0,25, 0,47, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 6, 0,22, 0,24, 0,39, 0,13, 0,30, 0,55, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 4, 0,37, 0, 8, 0,61, 0,51, 0,55, 0,23, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,80, 0},
{80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80},
};

int mapFormat3[23][28] = {
{80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,83, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,0 ,0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,0 ,0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 0, 0,72, 0,73, 0,74, 0,75, 0,76, 0, 0, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 1, 0, 9, 0,15, 0,17, 0,41, 0,25, 0,47, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 6, 0,22, 0,24, 0,39, 0,13, 0,30, 0,55, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 4, 0,37, 0, 8, 0,61, 0,51, 0,55, 0,23, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,80, 0},
{80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,80, 0},
{80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80},
};


enum HIRAGANA {

	YUKA,//0

	A, I, U, E, O,
	KA, KI, KU, KE, KO,
	SA, SHI, SU, SE, SO,
	TA, CHI, TSU, TE, TO,
	NA, NI, NU, NE, NO,
	HA, HI, FU, HE, HO,
	MA, MI, MU, ME, MO,
	YA, YU, YO,
	RA, RI, RU, RE, RO,
	WA, WO, NN,

	GA, GI, GU, GE, GO,
	ZA, ZI, ZU, ZE, ZO,
	DA, DI, DU, DE, DO,
	BA, BI, BU, BE, BO,
	PA, PI, PU, PE, PO,

	BLOCK1, BLOCK22, BLOCK3, BLOCK4,
	BLOCK5, BLOCK6, BLOCK7, BLOCK8,

	BLOCK,//1
	THORN,//2
	BLOCK222,//3
	GOAL,//4
	SYRUP,//5
	CANDY,//6
	CARAMEL,//7
};

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };
	int mapCountX = sizeof(map[0]) / sizeof(map[0][0]);
	int mapCountY = sizeof(map) / sizeof(map[0]);

	int mapCountX2 = sizeof(map2[0]) / sizeof(map2[0][0]);
	int mapCountY2 = sizeof(map2) / sizeof(map2[0]);

	int mapCountX3 = sizeof(map3[0]) / sizeof(map3[0][0]);
	int mapCountY3 = sizeof(map3) / sizeof(map3[0]);

	int a = Novice::LoadTexture("./images/a.png");
	int i = Novice::LoadTexture("./images/i.png");
	int u = Novice::LoadTexture("./images/u.png");
	int e = Novice::LoadTexture("./images/e.png");
	int o = Novice::LoadTexture("./images/o.png");

	int ka = Novice::LoadTexture("./images/ka.png");
	int ki = Novice::LoadTexture("./images/ki.png");
	int ku = Novice::LoadTexture("./images/ku.png");
	int ke = Novice::LoadTexture("./images/ke.png");
	int ko = Novice::LoadTexture("./images/ko.png");

	int sa = Novice::LoadTexture("./images/sa.png");
	int shi = Novice::LoadTexture("./images/si.png");
	int su = Novice::LoadTexture("./images/su.png");
	int se = Novice::LoadTexture("./images/se.png");
	int so = Novice::LoadTexture("./images/so.png");

	int ta = Novice::LoadTexture("./images/ta.png");
	int chi = Novice::LoadTexture("./images/ti.png");
	int tsu = Novice::LoadTexture("./images/tu.png");
	int te = Novice::LoadTexture("./images/te.png");
	int to = Novice::LoadTexture("./images/to.png");

	int na = Novice::LoadTexture("./images/na.png");
	int ni = Novice::LoadTexture("./images/ni.png");
	int nu = Novice::LoadTexture("./images/nu.png");
	int ne = Novice::LoadTexture("./images/ne.png");
	int no = Novice::LoadTexture("./images/no.png");

	int ha = Novice::LoadTexture("./images/ha.png");
	int hi = Novice::LoadTexture("./images/hi.png");
	int hu = Novice::LoadTexture("./images/hu.png");
	int he = Novice::LoadTexture("./images/he.png");
	int ho = Novice::LoadTexture("./images/ho.png");

	int ma = Novice::LoadTexture("./images/ma.png");
	int mi = Novice::LoadTexture("./images/mi.png");
	int mu = Novice::LoadTexture("./images/mu.png");
	int me = Novice::LoadTexture("./images/me.png");
	int mo = Novice::LoadTexture("./images/mo.png");

	int ya = Novice::LoadTexture("./images/ya.png");
	int yu = Novice::LoadTexture("./images/yu.png");
	int yo = Novice::LoadTexture("./images/yo.png");

	int ra = Novice::LoadTexture("./images/ra.png");
	int ri = Novice::LoadTexture("./images/ri.png");
	int ru = Novice::LoadTexture("./images/ru.png");
	int re = Novice::LoadTexture("./images/re.png");
	int ro = Novice::LoadTexture("./images/ro.png");

	int wa = Novice::LoadTexture("./images/wa.png");
	int wo = Novice::LoadTexture("./images/wo.png");
	int nn = Novice::LoadTexture("./images/n.png");

	int ga = Novice::LoadTexture("./images/ga.png");
	int gi = Novice::LoadTexture("./images/gi.png");
	int gu = Novice::LoadTexture("./images/gu.png");
	int ge = Novice::LoadTexture("./images/ge.png");
	int go = Novice::LoadTexture("./images/go.png");

	int za = Novice::LoadTexture("./images/za.png");
	int zi = Novice::LoadTexture("./images/zi.png");
	int zu = Novice::LoadTexture("./images/zu.png");
	int ze = Novice::LoadTexture("./images/ze.png");
	int zo = Novice::LoadTexture("./images/zo.png");

	int da = Novice::LoadTexture("./images/da.png");
	int di = Novice::LoadTexture("./images/di.png");
	int du = Novice::LoadTexture("./images/du.png");
	int de = Novice::LoadTexture("./images/de.png");
	int doo = Novice::LoadTexture("./images/do.png");

	int ba = Novice::LoadTexture("./images/ba.png");
	int bi = Novice::LoadTexture("./images/bi.png");
	int bu = Novice::LoadTexture("./images/bu.png");
	int be = Novice::LoadTexture("./images/be.png");
	int bo = Novice::LoadTexture("./images/bo.png");

	int pa = Novice::LoadTexture("./images/pa.png");
	int pi = Novice::LoadTexture("./images/pi.png");
	int pu = Novice::LoadTexture("./images/pu.png");
	int pe = Novice::LoadTexture("./images/pe.png");
	int po = Novice::LoadTexture("./images/po.png");

	int block = Novice::LoadTexture("./images/block.png");
	int goal = Novice::LoadTexture("./images/GOALS.png");
	int player = Novice::LoadTexture("./images/player.png");
	int gameClear = Novice::LoadTexture("./images/GAMECLEAR.png");
	int gameOver = Novice::LoadTexture("./images/GAMEOVERR.png");
	int title = Novice::LoadTexture("./images/TITLE.png");
	int MANUAL = Novice::LoadTexture("./images/MANUALS.png");

	bool isClearFlag = false;
	//int isLife = 3;

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		switch (sceneNo)
		{
		case TITLE:
			//初期化------------------------------------------------------------
			goalTimer = 60;
			deathTimer = 60;
			playerPosY = 672;
			playerSpeed = KBlockSize;
			for (int y = 0; y < mapCountY; y++)
			{
				for (int x = 0; x < mapCountX; x++)
				{
					map[y][x] = mapFormat[y][x];
				}
			}
			//--------------------------------------------------------------------
			if (keys[DIK_SPACE] && preKeys[DIK_SPACE] == 0)
			{
				sceneNo = STAGE1;
			}

			break;

		case STAGE1:
			//マップ情報-----------------------------------------------------------------------------------
			playerMapX = playerPosX / KBlockSize;//map[x][]
			playerMapY = playerPosY / KBlockSize;//map[][y]

			blockMapX = blockPosX / KBlockSize;
			blockMapY = blockPosY / KBlockSize;

			//リスタート
			if (keys[DIK_R] && preKeys[DIK_R] == 0)
			{
				goalTimer = 60;//初期化
				deathTimer = 60;
				playerPosX = 13 * KBlockSize;//プレイヤーの位置
				playerPosY = 672;
				playerSpeed = KBlockSize;
				for (int y = 0; y < mapCountY; y++)
				{
					for (int x = 0; x < mapCountX; x++)
					{
						map[y][x] = mapFormat[y][x];
					}
				}
			}



			//プレイヤー移動-------------------------------------------------------------------------------
			if (keys[DIK_W] && preKeys[DIK_W] == 0 || keys[DIK_UP] && preKeys[DIK_UP] == 0)
			{
				playerTmpY = playerPosY - playerSpeed;
				playerMapY = playerTmpY / KBlockSize;
				//何もないから実際に進ませる
				if (map[playerMapY][playerMapX] == YUKA)
				{
					playerPosY -= playerSpeed;
				}
				if (map[playerMapY][playerMapX] == BLOCK1)
				{
					playerPosY -= playerSpeed;
				}
				if (map[playerMapY][playerMapX] == GOAL)
				{
					playerPosY -= playerSpeed;
				}
				if (map[playerMapY][playerMapX] == THORN)
				{
					playerPosY -= playerSpeed;
				}

				if (map[playerMapY][playerMapX] == I)
				{
					if (map[playerMapY - 1][playerMapX] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = I;
						if (map[1][27] != BLOCK1 || map[1][27] == BLOCK1)
						{
							if (map[1][27] == BLOCK1 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK1;
								map[1][27] = YUKA;
							}
						}
						if (map[2][27] != BLOCK22 || map[2][27] == BLOCK22)
						{
							if (map[2][27] == BLOCK22 && map[playerMapY][playerMapX] == map[4][11])
							{
								map[playerMapY][playerMapX] = BLOCK22;
								map[2][27] = YUKA;
							}
						}
						if (map[3][27] != BLOCK3 || map[3][27] == BLOCK3)
						{
							if (map[3][27] == BLOCK3 && map[playerMapY][playerMapX] == map[4][13])
							{
								map[playerMapY][playerMapX] = BLOCK3;
								map[3][27] = YUKA;
							}
						}
						if (map[4][27] != BLOCK4 || map[4][27] == BLOCK4)
						{
							if (map[4][27] == BLOCK4 && map[playerMapY][playerMapX] == map[4][15])
							{
								map[playerMapY][playerMapX] = BLOCK4;
								map[4][27] = YUKA;
							}
						}
						if (map[5][27] != BLOCK5 || map[5][27] == BLOCK5)
						{
							if (map[5][27] == BLOCK5 && map[playerMapY][playerMapX] == map[4][17])
							{
								map[playerMapY][playerMapX] = BLOCK5;
								map[5][27] = YUKA;
							}
						}
						if (map[6][27] != BLOCK6 || map[6][27] == BLOCK6)
						{

							if (map[6][27] == BLOCK6 && map[playerMapY][playerMapX] == /*6以降は後で*/map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK6;
								map[6][27] = YUKA;
							}
						}
						if (map[7][27] != BLOCK7 || map[7][27] == BLOCK7)
						{
							if (map[7][27] == BLOCK7 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK7;
								map[7][27] = YUKA;
							}
						}
						if (map[8][27] != BLOCK8 || map[8][27] == BLOCK8)
						{
							if (map[8][27] == BLOCK8 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK8;
								map[8][27] = YUKA;
							}
						}
						playerPosY -= playerSpeed;
					}

					if (map[playerMapY - 1][playerMapX] == BLOCK1)
					{
						map[1][27] = BLOCK1;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = I;
						playerPosY -= playerSpeed;

					}

					if (map[playerMapY - 1][playerMapX] == BLOCK22)
					{
						map[2][27] = BLOCK22;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = I;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK3)
					{
						map[3][27] = BLOCK3;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = I;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK4)
					{
						map[4][27] = BLOCK4;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = I;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK5)
					{
						map[5][27] = BLOCK5;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = I;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK6)
					{
						map[6][27] = BLOCK6;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = I;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK7)
					{
						map[7][27] = BLOCK7;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = I;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK8)
					{
						map[8][27] = BLOCK8;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = I;
						playerPosY -= playerSpeed;

					}



				}

				// 1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111
				// ここから直して
				if (map[playerMapY][playerMapX] == U)
				{
					if (map[playerMapY - 1][playerMapX] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = U; //ここをUに変える　したも同じ
						if (map[1][27] != BLOCK1 || map[1][27] == BLOCK1)
						{
							if (map[1][27] == BLOCK1 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK1;
								map[1][27] = YUKA;
							}
						}
						if (map[2][27] != BLOCK22 || map[2][27] == BLOCK22)
						{
							if (map[2][27] == BLOCK22 && map[playerMapY][playerMapX] == map[4][11])
							{
								map[playerMapY][playerMapX] = BLOCK22;
								map[2][27] = YUKA;
							}
						}
						if (map[3][27] != BLOCK3 || map[3][27] == BLOCK3)
						{
							if (map[3][27] == BLOCK3 && map[playerMapY][playerMapX] == map[4][13])
							{
								map[playerMapY][playerMapX] = BLOCK3;
								map[3][27] = YUKA;
							}
						}
						if (map[4][27] != BLOCK4 || map[4][27] == BLOCK4)
						{
							if (map[4][27] == BLOCK4 && map[playerMapY][playerMapX] == map[4][15])
							{
								map[playerMapY][playerMapX] = BLOCK4;
								map[4][27] = YUKA;
							}
						}
						if (map[5][27] != BLOCK5 || map[5][27] == BLOCK5)
						{
							if (map[5][27] == BLOCK5 && map[playerMapY][playerMapX] == map[4][17])
							{
								map[playerMapY][playerMapX] = BLOCK5;
								map[5][27] = YUKA;
							}
						}
						if (map[6][27] != BLOCK6 || map[6][27] == BLOCK6)
						{

							if (map[6][27] == BLOCK6 && map[playerMapY][playerMapX] == /*6以降は後で*/map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK6;
								map[6][27] = YUKA;
							}
						}
						if (map[7][27] != BLOCK7 || map[7][27] == BLOCK7)
						{
							if (map[7][27] == BLOCK7 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK7;
								map[7][27] = YUKA;
							}
						}
						if (map[8][27] != BLOCK8 || map[8][27] == BLOCK8)
						{
							if (map[8][27] == BLOCK8 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK8;
								map[8][27] = YUKA;
							}
						}
						playerPosY -= playerSpeed;
					}

					if (map[playerMapY - 1][playerMapX] == BLOCK1)
					{
						map[1][27] = BLOCK1;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = U;
						playerPosY -= playerSpeed;

					}

					if (map[playerMapY - 1][playerMapX] == BLOCK22)
					{
						map[2][27] = BLOCK22;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = U;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK3)
					{
						map[3][27] = BLOCK3;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = U;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK4)
					{
						map[4][27] = BLOCK4;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = U;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK5)
					{
						map[5][27] = BLOCK5;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = U;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK6)
					{
						map[6][27] = BLOCK6;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = U;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK7)
					{
						map[7][27] = BLOCK7;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = U;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK8)
					{
						map[8][27] = BLOCK8;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = U;
						playerPosY -= playerSpeed;

					}
				}
				if (map[playerMapY][playerMapX] == E)
				{
					if (map[playerMapY - 1][playerMapX] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = E;
						if (map[1][27] != BLOCK1 || map[1][27] == BLOCK1)
						{
							if (map[1][27] == BLOCK1 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK1;
								map[1][27] = YUKA;
							}
						}
						if (map[2][27] != BLOCK22 || map[2][27] == BLOCK22)
						{
							if (map[2][27] == BLOCK22 && map[playerMapY][playerMapX] == map[4][11])
							{
								map[playerMapY][playerMapX] = BLOCK22;
								map[2][27] = YUKA;
							}
						}
						if (map[3][27] != BLOCK3 || map[3][27] == BLOCK3)
						{
							if (map[3][27] == BLOCK3 && map[playerMapY][playerMapX] == map[4][13])
							{
								map[playerMapY][playerMapX] = BLOCK3;
								map[3][27] = YUKA;
							}
						}
						if (map[4][27] != BLOCK4 || map[4][27] == BLOCK4)
						{
							if (map[4][27] == BLOCK4 && map[playerMapY][playerMapX] == map[4][15])
							{
								map[playerMapY][playerMapX] = BLOCK4;
								map[4][27] = YUKA;
							}
						}
						if (map[5][27] != BLOCK5 || map[5][27] == BLOCK5)
						{
							if (map[5][27] == BLOCK5 && map[playerMapY][playerMapX] == map[4][17])
							{
								map[playerMapY][playerMapX] = BLOCK5;
								map[5][27] = YUKA;
							}
						}
						if (map[6][27] != BLOCK6 || map[6][27] == BLOCK6)
						{

							if (map[6][27] == BLOCK6 && map[playerMapY][playerMapX] == /*6以降は後で*/map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK6;
								map[6][27] = YUKA;
							}
						}
						if (map[7][27] != BLOCK7 || map[7][27] == BLOCK7)
						{
							if (map[7][27] == BLOCK7 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK7;
								map[7][27] = YUKA;
							}
						}
						if (map[8][27] != BLOCK8 || map[8][27] == BLOCK8)
						{
							if (map[8][27] == BLOCK8 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK8;
								map[8][27] = YUKA;
							}
						}
						playerPosY -= playerSpeed;
					}
					if (map[playerMapY - 1][playerMapX] == BLOCK1)
					{
						map[1][27] = BLOCK1;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = E;
						playerPosY -= playerSpeed;

					}

					if (map[playerMapY - 1][playerMapX] == BLOCK22)
					{
						map[2][27] = BLOCK22;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = E;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK3)
					{
						map[3][27] = BLOCK3;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = E;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK4)
					{
						map[4][27] = BLOCK4;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = E;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK5)
					{
						map[5][27] = BLOCK5;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = E;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK6)
					{
						map[6][27] = BLOCK6;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = E;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK7)
					{
						map[7][27] = BLOCK7;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = E;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK8)
					{
						map[8][27] = BLOCK8;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = E;
						playerPosY -= playerSpeed;

					}
				}
				if (map[playerMapY][playerMapX] == KA)
				{
					if (map[playerMapY - 1][playerMapX] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = KA;
						if (map[1][27] != BLOCK1 || map[1][27] == BLOCK1)
						{
							if (map[1][27] == BLOCK1 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK1;
								map[1][27] = YUKA;
							}
						}
						if (map[2][27] != BLOCK22 || map[2][27] == BLOCK22)
						{
							if (map[2][27] == BLOCK22 && map[playerMapY][playerMapX] == map[4][11])
							{
								map[playerMapY][playerMapX] = BLOCK22;
								map[2][27] = YUKA;
							}
						}
						if (map[3][27] != BLOCK3 || map[3][27] == BLOCK3)
						{
							if (map[3][27] == BLOCK3 && map[playerMapY][playerMapX] == map[4][13])
							{
								map[playerMapY][playerMapX] = BLOCK3;
								map[3][27] = YUKA;
							}
						}
						if (map[4][27] != BLOCK4 || map[4][27] == BLOCK4)
						{
							if (map[4][27] == BLOCK4 && map[playerMapY][playerMapX] == map[4][15])
							{
								map[playerMapY][playerMapX] = BLOCK4;
								map[4][27] = YUKA;
							}
						}
						if (map[5][27] != BLOCK5 || map[5][27] == BLOCK5)
						{
							if (map[5][27] == BLOCK5 && map[playerMapY][playerMapX] == map[4][17])
							{
								map[playerMapY][playerMapX] = BLOCK5;
								map[5][27] = YUKA;
							}
						}
						if (map[6][27] != BLOCK6 || map[6][27] == BLOCK6)
						{

							if (map[6][27] == BLOCK6 && map[playerMapY][playerMapX] == /*6以降は後で*/map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK6;
								map[6][27] = YUKA;
							}
						}
						if (map[7][27] != BLOCK7 || map[7][27] == BLOCK7)
						{
							if (map[7][27] == BLOCK7 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK7;
								map[7][27] = YUKA;
							}
						}
						if (map[8][27] != BLOCK8 || map[8][27] == BLOCK8)
						{
							if (map[8][27] == BLOCK8 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK8;
								map[8][27] = YUKA;
							}
						}
						playerPosY -= playerSpeed;
					}

					if (map[playerMapY - 1][playerMapX] == BLOCK1)
					{
						map[1][27] = BLOCK1;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = KA;
						playerPosY -= playerSpeed;

					}

					if (map[playerMapY - 1][playerMapX] == BLOCK22)
					{
						map[2][27] = BLOCK22;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = KA;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK3)
					{
						map[3][27] = BLOCK3;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = KA;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK4)
					{
						map[4][27] = BLOCK4;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = KA;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK5)
					{
						map[5][27] = BLOCK5;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = KA;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK6)
					{
						map[6][27] = BLOCK6;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = KA;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK7)
					{
						map[7][27] = BLOCK7;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = KA;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK8)
					{
						map[8][27] = BLOCK8;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = KA;
						playerPosY -= playerSpeed;

					}
				}
				if (map[playerMapY][playerMapX] == KU)
				{
					if (map[playerMapY - 1][playerMapX] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = KU;
						if (map[1][27] != BLOCK1 || map[1][27] == BLOCK1)
						{
							if (map[1][27] == BLOCK1 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK1;
								map[1][27] = YUKA;
							}
						}
						if (map[2][27] != BLOCK22 || map[2][27] == BLOCK22)
						{
							if (map[2][27] == BLOCK22 && map[playerMapY][playerMapX] == map[4][11])
							{
								map[playerMapY][playerMapX] = BLOCK22;
								map[2][27] = YUKA;
							}
						}
						if (map[3][27] != BLOCK3 || map[3][27] == BLOCK3)
						{
							if (map[3][27] == BLOCK3 && map[playerMapY][playerMapX] == map[4][13])
							{
								map[playerMapY][playerMapX] = BLOCK3;
								map[3][27] = YUKA;
							}
						}
						if (map[4][27] != BLOCK4 || map[4][27] == BLOCK4)
						{
							if (map[4][27] == BLOCK4 && map[playerMapY][playerMapX] == map[4][15])
							{
								map[playerMapY][playerMapX] = BLOCK4;
								map[4][27] = YUKA;
							}
						}
						if (map[5][27] != BLOCK5 || map[5][27] == BLOCK5)
						{
							if (map[5][27] == BLOCK5 && map[playerMapY][playerMapX] == map[4][17])
							{
								map[playerMapY][playerMapX] = BLOCK5;
								map[5][27] = YUKA;
							}
						}
						if (map[6][27] != BLOCK6 || map[6][27] == BLOCK6)
						{

							if (map[6][27] == BLOCK6 && map[playerMapY][playerMapX] == /*6以降は後で*/map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK6;
								map[6][27] = YUKA;
							}
						}
						if (map[7][27] != BLOCK7 || map[7][27] == BLOCK7)
						{
							if (map[7][27] == BLOCK7 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK7;
								map[7][27] = YUKA;
							}
						}
						if (map[8][27] != BLOCK8 || map[8][27] == BLOCK8)
						{
							if (map[8][27] == BLOCK8 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK8;
								map[8][27] = YUKA;
							}
						}
						playerPosY -= playerSpeed;
					}

					if (map[playerMapY - 1][playerMapX] == BLOCK1)
					{
						map[1][27] = BLOCK1;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = KU;
						playerPosY -= playerSpeed;

					}

					if (map[playerMapY - 1][playerMapX] == BLOCK22)
					{
						map[2][27] = BLOCK22;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = KU;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK3)
					{
						map[3][27] = BLOCK3;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = KU;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK4)
					{
						map[4][27] = BLOCK4;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = KU;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK5)
					{
						map[5][27] = BLOCK5;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = KU;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK6)
					{
						map[6][27] = BLOCK6;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = KU;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK7)
					{
						map[7][27] = BLOCK7;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = KU;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK8)
					{
						map[8][27] = BLOCK8;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = KU;
						playerPosY -= playerSpeed;

					}
				}
				if (map[playerMapY][playerMapX] == KO)
				{
					if (map[playerMapY - 1][playerMapX] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = KO;
						if (map[1][27] != BLOCK1 || map[1][27] == BLOCK1)
						{
							if (map[1][27] == BLOCK1 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK1;
								map[1][27] = YUKA;
							}
						}
						if (map[2][27] != BLOCK22 || map[2][27] == BLOCK22)
						{
							if (map[2][27] == BLOCK22 && map[playerMapY][playerMapX] == map[4][11])
							{
								map[playerMapY][playerMapX] = BLOCK22;
								map[2][27] = YUKA;
							}
						}
						if (map[3][27] != BLOCK3 || map[3][27] == BLOCK3)
						{
							if (map[3][27] == BLOCK3 && map[playerMapY][playerMapX] == map[4][13])
							{
								map[playerMapY][playerMapX] = BLOCK3;
								map[3][27] = YUKA;
							}
						}
						if (map[4][27] != BLOCK4 || map[4][27] == BLOCK4)
						{
							if (map[4][27] == BLOCK4 && map[playerMapY][playerMapX] == map[4][15])
							{
								map[playerMapY][playerMapX] = BLOCK4;
								map[4][27] = YUKA;
							}
						}
						if (map[5][27] != BLOCK5 || map[5][27] == BLOCK5)
						{
							if (map[5][27] == BLOCK5 && map[playerMapY][playerMapX] == map[4][17])
							{
								map[playerMapY][playerMapX] = BLOCK5;
								map[5][27] = YUKA;
							}
						}
						if (map[6][27] != BLOCK6 || map[6][27] == BLOCK6)
						{

							if (map[6][27] == BLOCK6 && map[playerMapY][playerMapX] == /*6以降は後で*/map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK6;
								map[6][27] = YUKA;
							}
						}
						if (map[7][27] != BLOCK7 || map[7][27] == BLOCK7)
						{
							if (map[7][27] == BLOCK7 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK7;
								map[7][27] = YUKA;
							}
						}
						if (map[8][27] != BLOCK8 || map[8][27] == BLOCK8)
						{
							if (map[8][27] == BLOCK8 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK8;
								map[8][27] = YUKA;
							}
						}
						playerPosY -= playerSpeed;
					}

					if (map[playerMapY - 1][playerMapX] == BLOCK1)
					{
						map[1][27] = BLOCK1;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = KO;
						playerPosY -= playerSpeed;

					}

					if (map[playerMapY - 1][playerMapX] == BLOCK22)
					{
						map[2][27] = BLOCK22;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = KO;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK3)
					{
						map[3][27] = BLOCK3;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = KO;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK4)
					{
						map[4][27] = BLOCK4;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = KO;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK5)
					{
						map[5][27] = BLOCK5;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = KO;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK6)
					{
						map[6][27] = BLOCK6;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = KO;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK7)
					{
						map[7][27] = BLOCK7;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = KO;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK8)
					{
						map[8][27] = BLOCK8;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = KO;
						playerPosY -= playerSpeed;

					}
				}
				if (map[playerMapY][playerMapX] == SA)
				{
					if (map[playerMapY - 1][playerMapX] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = SA;
						if (map[1][27] != BLOCK1 || map[1][27] == BLOCK1)
						{
							if (map[1][27] == BLOCK1 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK1;
								map[1][27] = YUKA;
							}
						}
						if (map[2][27] != BLOCK22 || map[2][27] == BLOCK22)
						{
							if (map[2][27] == BLOCK22 && map[playerMapY][playerMapX] == map[4][11])
							{
								map[playerMapY][playerMapX] = BLOCK22;
								map[2][27] = YUKA;
							}
						}
						if (map[3][27] != BLOCK3 || map[3][27] == BLOCK3)
						{
							if (map[3][27] == BLOCK3 && map[playerMapY][playerMapX] == map[4][13])
							{
								map[playerMapY][playerMapX] = BLOCK3;
								map[3][27] = YUKA;
							}
						}
						if (map[4][27] != BLOCK4 || map[4][27] == BLOCK4)
						{
							if (map[4][27] == BLOCK4 && map[playerMapY][playerMapX] == map[4][15])
							{
								map[playerMapY][playerMapX] = BLOCK4;
								map[4][27] = YUKA;
							}
						}
						if (map[5][27] != BLOCK5 || map[5][27] == BLOCK5)
						{
							if (map[5][27] == BLOCK5 && map[playerMapY][playerMapX] == map[4][17])
							{
								map[playerMapY][playerMapX] = BLOCK5;
								map[5][27] = YUKA;
							}
						}
						if (map[6][27] != BLOCK6 || map[6][27] == BLOCK6)
						{

							if (map[6][27] == BLOCK6 && map[playerMapY][playerMapX] == /*6以降は後で*/map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK6;
								map[6][27] = YUKA;
							}
						}
						if (map[7][27] != BLOCK7 || map[7][27] == BLOCK7)
						{
							if (map[7][27] == BLOCK7 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK7;
								map[7][27] = YUKA;
							}
						}
						if (map[8][27] != BLOCK8 || map[8][27] == BLOCK8)
						{
							if (map[8][27] == BLOCK8 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK8;
								map[8][27] = YUKA;
							}
						}
						playerPosY -= playerSpeed;
					}
					if (map[playerMapY - 1][playerMapX] == BLOCK1)
					{
						map[1][27] = BLOCK1;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = SA;
						playerPosY -= playerSpeed;

					}

					if (map[playerMapY - 1][playerMapX] == BLOCK22)
					{
						map[2][27] = BLOCK22;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = SA;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK3)
					{
						map[3][27] = BLOCK3;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = SA;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK4)
					{
						map[4][27] = BLOCK4;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = SA;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK5)
					{
						map[5][27] = BLOCK5;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = SA;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK6)
					{
						map[6][27] = BLOCK6;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = SA;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK7)
					{
						map[7][27] = BLOCK7;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = SA;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK8)
					{
						map[8][27] = BLOCK8;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = SA;
						playerPosY -= playerSpeed;

					}
				}
				if (map[playerMapY][playerMapX] == SU)
				{
					if (map[playerMapY - 1][playerMapX] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = SU;
						if (map[1][27] != BLOCK1 || map[1][27] == BLOCK1)
						{
							if (map[1][27] == BLOCK1 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK1;
								map[1][27] = YUKA;
							}
						}
						if (map[2][27] != BLOCK22 || map[2][27] == BLOCK22)
						{
							if (map[2][27] == BLOCK22 && map[playerMapY][playerMapX] == map[4][11])
							{
								map[playerMapY][playerMapX] = BLOCK22;
								map[2][27] = YUKA;
							}
						}
						if (map[3][27] != BLOCK3 || map[3][27] == BLOCK3)
						{
							if (map[3][27] == BLOCK3 && map[playerMapY][playerMapX] == map[4][13])
							{
								map[playerMapY][playerMapX] = BLOCK3;
								map[3][27] = YUKA;
							}
						}
						if (map[4][27] != BLOCK4 || map[4][27] == BLOCK4)
						{
							if (map[4][27] == BLOCK4 && map[playerMapY][playerMapX] == map[4][15])
							{
								map[playerMapY][playerMapX] = BLOCK4;
								map[4][27] = YUKA;
							}
						}
						if (map[5][27] != BLOCK5 || map[5][27] == BLOCK5)
						{
							if (map[5][27] == BLOCK5 && map[playerMapY][playerMapX] == map[4][17])
							{
								map[playerMapY][playerMapX] = BLOCK5;
								map[5][27] = YUKA;
							}
						}
						if (map[6][27] != BLOCK6 || map[6][27] == BLOCK6)
						{

							if (map[6][27] == BLOCK6 && map[playerMapY][playerMapX] == /*6以降は後で*/map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK6;
								map[6][27] = YUKA;
							}
						}
						if (map[7][27] != BLOCK7 || map[7][27] == BLOCK7)
						{
							if (map[7][27] == BLOCK7 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK7;
								map[7][27] = YUKA;
							}
						}
						if (map[8][27] != BLOCK8 || map[8][27] == BLOCK8)
						{
							if (map[8][27] == BLOCK8 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK8;
								map[8][27] = YUKA;
							}
						}
						playerPosY -= playerSpeed;
					}

					if (map[playerMapY - 1][playerMapX] == BLOCK1)
					{
						map[1][27] = BLOCK1;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = SU;
						playerPosY -= playerSpeed;

					}

					if (map[playerMapY - 1][playerMapX] == BLOCK22)
					{
						map[2][27] = BLOCK22;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = SU;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK3)
					{
						map[3][27] = BLOCK3;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = SU;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK4)
					{
						map[4][27] = BLOCK4;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = SU;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK5)
					{
						map[5][27] = BLOCK5;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = SU;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK6)
					{
						map[6][27] = BLOCK6;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = SU;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK7)
					{
						map[7][27] = BLOCK7;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = SU;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK8)
					{
						map[8][27] = BLOCK8;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = SU;
						playerPosY -= playerSpeed;

					}
				}
				if (map[playerMapY][playerMapX] == SO)
				{
					if (map[playerMapY - 1][playerMapX] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = SO;
						if (map[1][27] != BLOCK1 || map[1][27] == BLOCK1)
						{
							if (map[1][27] == BLOCK1 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK1;
								map[1][27] = YUKA;
							}
						}
						if (map[2][27] != BLOCK22 || map[2][27] == BLOCK22)
						{
							if (map[2][27] == BLOCK22 && map[playerMapY][playerMapX] == map[4][11])
							{
								map[playerMapY][playerMapX] = BLOCK22;
								map[2][27] = YUKA;
							}
						}
						if (map[3][27] != BLOCK3 || map[3][27] == BLOCK3)
						{
							if (map[3][27] == BLOCK3 && map[playerMapY][playerMapX] == map[4][13])
							{
								map[playerMapY][playerMapX] = BLOCK3;
								map[3][27] = YUKA;
							}
						}
						if (map[4][27] != BLOCK4 || map[4][27] == BLOCK4)
						{
							if (map[4][27] == BLOCK4 && map[playerMapY][playerMapX] == map[4][15])
							{
								map[playerMapY][playerMapX] = BLOCK4;
								map[4][27] = YUKA;
							}
						}
						if (map[5][27] != BLOCK5 || map[5][27] == BLOCK5)
						{
							if (map[5][27] == BLOCK5 && map[playerMapY][playerMapX] == map[4][17])
							{
								map[playerMapY][playerMapX] = BLOCK5;
								map[5][27] = YUKA;
							}
						}
						if (map[6][27] != BLOCK6 || map[6][27] == BLOCK6)
						{

							if (map[6][27] == BLOCK6 && map[playerMapY][playerMapX] == /*6以降は後で*/map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK6;
								map[6][27] = YUKA;
							}
						}
						if (map[7][27] != BLOCK7 || map[7][27] == BLOCK7)
						{
							if (map[7][27] == BLOCK7 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK7;
								map[7][27] = YUKA;
							}
						}
						if (map[8][27] != BLOCK8 || map[8][27] == BLOCK8)
						{
							if (map[8][27] == BLOCK8 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK8;
								map[8][27] = YUKA;
							}
						}
						playerPosY -= playerSpeed;
					}

					if (map[playerMapY - 1][playerMapX] == BLOCK1)
					{
						map[1][27] = BLOCK1;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = SO;
						playerPosY -= playerSpeed;

					}

					if (map[playerMapY - 1][playerMapX] == BLOCK22)
					{
						map[2][27] = BLOCK22;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = SO;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK3)
					{
						map[3][27] = BLOCK3;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = SO;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK4)
					{
						map[4][27] = BLOCK4;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = SO;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK5)
					{
						map[5][27] = BLOCK5;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = SO;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK6)
					{
						map[6][27] = BLOCK6;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = SO;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK7)
					{
						map[7][27] = BLOCK7;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = SO;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK8)
					{
						map[8][27] = BLOCK8;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = SO;
						playerPosY -= playerSpeed;

					}
				}
				if (map[playerMapY][playerMapX] == TA)
				{
					if (map[playerMapY - 1][playerMapX] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = TA;
						if (map[1][27] != BLOCK1 || map[1][27] == BLOCK1)
						{
							if (map[1][27] == BLOCK1 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK1;
								map[1][27] = YUKA;
							}
						}
						if (map[2][27] != BLOCK22 || map[2][27] == BLOCK22)
						{
							if (map[2][27] == BLOCK22 && map[playerMapY][playerMapX] == map[4][11])
							{
								map[playerMapY][playerMapX] = BLOCK22;
								map[2][27] = YUKA;
							}
						}
						if (map[3][27] != BLOCK3 || map[3][27] == BLOCK3)
						{
							if (map[3][27] == BLOCK3 && map[playerMapY][playerMapX] == map[4][13])
							{
								map[playerMapY][playerMapX] = BLOCK3;
								map[3][27] = YUKA;
							}
						}
						if (map[4][27] != BLOCK4 || map[4][27] == BLOCK4)
						{
							if (map[4][27] == BLOCK4 && map[playerMapY][playerMapX] == map[4][15])
							{
								map[playerMapY][playerMapX] = BLOCK4;
								map[4][27] = YUKA;
							}
						}
						if (map[5][27] != BLOCK5 || map[5][27] == BLOCK5)
						{
							if (map[5][27] == BLOCK5 && map[playerMapY][playerMapX] == map[4][17])
							{
								map[playerMapY][playerMapX] = BLOCK5;
								map[5][27] = YUKA;
							}
						}
						if (map[6][27] != BLOCK6 || map[6][27] == BLOCK6)
						{

							if (map[6][27] == BLOCK6 && map[playerMapY][playerMapX] == /*6以降は後で*/map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK6;
								map[6][27] = YUKA;
							}
						}
						if (map[7][27] != BLOCK7 || map[7][27] == BLOCK7)
						{
							if (map[7][27] == BLOCK7 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK7;
								map[7][27] = YUKA;
							}
						}
						if (map[8][27] != BLOCK8 || map[8][27] == BLOCK8)
						{
							if (map[8][27] == BLOCK8 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK8;
								map[8][27] = YUKA;
							}
						}
						playerPosY -= playerSpeed;
					}

					if (map[playerMapY - 1][playerMapX] == BLOCK1)
					{
						map[1][27] = BLOCK1;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = TA;
						playerPosY -= playerSpeed;

					}

					if (map[playerMapY - 1][playerMapX] == BLOCK22)
					{
						map[2][27] = BLOCK22;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = TA;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK3)
					{
						map[3][27] = BLOCK3;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = TA;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK4)
					{
						map[4][27] = BLOCK4;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = TA;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK5)
					{
						map[5][27] = BLOCK5;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = TA;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK6)
					{
						map[6][27] = BLOCK6;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = TA;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK7)
					{
						map[7][27] = BLOCK7;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = TA;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK8)
					{
						map[8][27] = BLOCK8;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = TA;
						playerPosY -= playerSpeed;

					}
				}
				if (map[playerMapY][playerMapX] == CHI)
				{
					if (map[playerMapY - 1][playerMapX] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = CHI;
						if (map[1][27] != BLOCK1 || map[1][27] == BLOCK1)
						{
							if (map[1][27] == BLOCK1 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK1;
								map[1][27] = YUKA;
							}
						}
						if (map[2][27] != BLOCK22 || map[2][27] == BLOCK22)
						{
							if (map[2][27] == BLOCK22 && map[playerMapY][playerMapX] == map[4][11])
							{
								map[playerMapY][playerMapX] = BLOCK22;
								map[2][27] = YUKA;
							}
						}
						if (map[3][27] != BLOCK3 || map[3][27] == BLOCK3)
						{
							if (map[3][27] == BLOCK3 && map[playerMapY][playerMapX] == map[4][13])
							{
								map[playerMapY][playerMapX] = BLOCK3;
								map[3][27] = YUKA;
							}
						}
						if (map[4][27] != BLOCK4 || map[4][27] == BLOCK4)
						{
							if (map[4][27] == BLOCK4 && map[playerMapY][playerMapX] == map[4][15])
							{
								map[playerMapY][playerMapX] = BLOCK4;
								map[4][27] = YUKA;
							}
						}
						if (map[5][27] != BLOCK5 || map[5][27] == BLOCK5)
						{
							if (map[5][27] == BLOCK5 && map[playerMapY][playerMapX] == map[4][17])
							{
								map[playerMapY][playerMapX] = BLOCK5;
								map[5][27] = YUKA;
							}
						}
						if (map[6][27] != BLOCK6 || map[6][27] == BLOCK6)
						{

							if (map[6][27] == BLOCK6 && map[playerMapY][playerMapX] == /*6以降は後で*/map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK6;
								map[6][27] = YUKA;
							}
						}
						if (map[7][27] != BLOCK7 || map[7][27] == BLOCK7)
						{
							if (map[7][27] == BLOCK7 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK7;
								map[7][27] = YUKA;
							}
						}
						if (map[8][27] != BLOCK8 || map[8][27] == BLOCK8)
						{
							if (map[8][27] == BLOCK8 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK8;
								map[8][27] = YUKA;
							}
						}
						playerPosY -= playerSpeed;
					}

					if (map[playerMapY - 1][playerMapX] == BLOCK1)
					{
						map[1][27] = BLOCK1;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = CHI;
						playerPosY -= playerSpeed;

					}

					if (map[playerMapY - 1][playerMapX] == BLOCK22)
					{
						map[2][27] = BLOCK22;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = CHI;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK3)
					{
						map[3][27] = BLOCK3;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = CHI;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK4)
					{
						map[4][27] = BLOCK4;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = CHI;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK5)
					{
						map[5][27] = BLOCK5;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = CHI;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK6)
					{
						map[6][27] = BLOCK6;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = CHI;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK7)
					{
						map[7][27] = BLOCK7;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = CHI;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK8)
					{
						map[8][27] = BLOCK8;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = CHI;
						playerPosY -= playerSpeed;

					}
				}

				if (map[playerMapY][playerMapX] == NU)
				{
					if (map[playerMapY - 1][playerMapX] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = NU;
						if (map[1][27] != BLOCK1 || map[1][27] == BLOCK1)
						{
							if (map[1][27] == BLOCK1 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK1;
								map[1][27] = YUKA;
							}
						}
						if (map[2][27] != BLOCK22 || map[2][27] == BLOCK22)
						{
							if (map[2][27] == BLOCK22 && map[playerMapY][playerMapX] == map[4][11])
							{
								map[playerMapY][playerMapX] = BLOCK22;
								map[2][27] = YUKA;
							}
						}
						if (map[3][27] != BLOCK3 || map[3][27] == BLOCK3)
						{
							if (map[3][27] == BLOCK3 && map[playerMapY][playerMapX] == map[4][13])
							{
								map[playerMapY][playerMapX] = BLOCK3;
								map[3][27] = YUKA;
							}
						}
						if (map[4][27] != BLOCK4 || map[4][27] == BLOCK4)
						{
							if (map[4][27] == BLOCK4 && map[playerMapY][playerMapX] == map[4][15])
							{
								map[playerMapY][playerMapX] = BLOCK4;
								map[4][27] = YUKA;
							}
						}
						if (map[5][27] != BLOCK5 || map[5][27] == BLOCK5)
						{
							if (map[5][27] == BLOCK5 && map[playerMapY][playerMapX] == map[4][17])
							{
								map[playerMapY][playerMapX] = BLOCK5;
								map[5][27] = YUKA;
							}
						}
						if (map[6][27] != BLOCK6 || map[6][27] == BLOCK6)
						{

							if (map[6][27] == BLOCK6 && map[playerMapY][playerMapX] == /*6以降は後で*/map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK6;
								map[6][27] = YUKA;
							}
						}
						if (map[7][27] != BLOCK7 || map[7][27] == BLOCK7)
						{
							if (map[7][27] == BLOCK7 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK7;
								map[7][27] = YUKA;
							}
						}
						if (map[8][27] != BLOCK8 || map[8][27] == BLOCK8)
						{
							if (map[8][27] == BLOCK8 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK8;
								map[8][27] = YUKA;
							}
						}
						playerPosY -= playerSpeed;
					}

					if (map[playerMapY - 1][playerMapX] == BLOCK1)
					{
						map[1][27] = BLOCK1;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = NU;
						playerPosY -= playerSpeed;

					}

					if (map[playerMapY - 1][playerMapX] == BLOCK22)
					{
						map[2][27] = BLOCK22;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = NU;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK3)
					{
						map[3][27] = BLOCK3;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = NU;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK4)
					{
						map[4][27] = BLOCK4;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = NU;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK5)
					{
						map[5][27] = BLOCK5;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = NU;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK6)
					{
						map[6][27] = BLOCK6;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = NU;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK7)
					{
						map[7][27] = BLOCK7;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = NU;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK8)
					{
						map[8][27] = BLOCK8;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = NU;
						playerPosY -= playerSpeed;

					}
				}
				if (map[playerMapY][playerMapX] == NE)
				{
					if (map[playerMapY - 1][playerMapX] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = NE;
						if (map[1][27] != BLOCK1 || map[1][27] == BLOCK1)
						{
							if (map[1][27] == BLOCK1 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK1;
								map[1][27] = YUKA;
							}
						}
						if (map[2][27] != BLOCK22 || map[2][27] == BLOCK22)
						{
							if (map[2][27] == BLOCK22 && map[playerMapY][playerMapX] == map[4][11])
							{
								map[playerMapY][playerMapX] = BLOCK22;
								map[2][27] = YUKA;
							}
						}
						if (map[3][27] != BLOCK3 || map[3][27] == BLOCK3)
						{
							if (map[3][27] == BLOCK3 && map[playerMapY][playerMapX] == map[4][13])
							{
								map[playerMapY][playerMapX] = BLOCK3;
								map[3][27] = YUKA;
							}
						}
						if (map[4][27] != BLOCK4 || map[4][27] == BLOCK4)
						{
							if (map[4][27] == BLOCK4 && map[playerMapY][playerMapX] == map[4][15])
							{
								map[playerMapY][playerMapX] = BLOCK4;
								map[4][27] = YUKA;
							}
						}
						if (map[5][27] != BLOCK5 || map[5][27] == BLOCK5)
						{
							if (map[5][27] == BLOCK5 && map[playerMapY][playerMapX] == map[4][17])
							{
								map[playerMapY][playerMapX] = BLOCK5;
								map[5][27] = YUKA;
							}
						}
						if (map[6][27] != BLOCK6 || map[6][27] == BLOCK6)
						{

							if (map[6][27] == BLOCK6 && map[playerMapY][playerMapX] == /*6以降は後で*/map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK6;
								map[6][27] = YUKA;
							}
						}
						if (map[7][27] != BLOCK7 || map[7][27] == BLOCK7)
						{
							if (map[7][27] == BLOCK7 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK7;
								map[7][27] = YUKA;
							}
						}
						if (map[8][27] != BLOCK8 || map[8][27] == BLOCK8)
						{
							if (map[8][27] == BLOCK8 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK8;
								map[8][27] = YUKA;
							}
						}
						playerPosY -= playerSpeed;
					}

					if (map[playerMapY - 1][playerMapX] == BLOCK1)
					{
						map[1][27] = BLOCK1;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = NE;
						playerPosY -= playerSpeed;

					}

					if (map[playerMapY - 1][playerMapX] == BLOCK22)
					{
						map[2][27] = BLOCK22;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = NE;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK3)
					{
						map[3][27] = BLOCK3;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = NE;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK4)
					{
						map[4][27] = BLOCK4;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = NE;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK5)
					{
						map[5][27] = BLOCK5;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = NE;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK6)
					{
						map[6][27] = BLOCK6;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = NE;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK7)
					{
						map[7][27] = BLOCK7;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = NE;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK8)
					{
						map[8][27] = BLOCK8;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = NE;
						playerPosY -= playerSpeed;

					}
				}
				if (map[playerMapY][playerMapX] == MA)
				{
					if (map[playerMapY - 1][playerMapX] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = MA;
						if (map[1][27] != BLOCK1 || map[1][27] == BLOCK1)
						{
							if (map[1][27] == BLOCK1 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK1;
								map[1][27] = YUKA;
							}
						}
						if (map[2][27] != BLOCK22 || map[2][27] == BLOCK22)
						{
							if (map[2][27] == BLOCK22 && map[playerMapY][playerMapX] == map[4][11])
							{
								map[playerMapY][playerMapX] = BLOCK22;
								map[2][27] = YUKA;
							}
						}
						if (map[3][27] != BLOCK3 || map[3][27] == BLOCK3)
						{
							if (map[3][27] == BLOCK3 && map[playerMapY][playerMapX] == map[4][13])
							{
								map[playerMapY][playerMapX] = BLOCK3;
								map[3][27] = YUKA;
							}
						}
						if (map[4][27] != BLOCK4 || map[4][27] == BLOCK4)
						{
							if (map[4][27] == BLOCK4 && map[playerMapY][playerMapX] == map[4][15])
							{
								map[playerMapY][playerMapX] = BLOCK4;
								map[4][27] = YUKA;
							}
						}
						if (map[5][27] != BLOCK5 || map[5][27] == BLOCK5)
						{
							if (map[5][27] == BLOCK5 && map[playerMapY][playerMapX] == map[4][17])
							{
								map[playerMapY][playerMapX] = BLOCK5;
								map[5][27] = YUKA;
							}
						}
						if (map[6][27] != BLOCK6 || map[6][27] == BLOCK6)
						{

							if (map[6][27] == BLOCK6 && map[playerMapY][playerMapX] == /*6以降は後で*/map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK6;
								map[6][27] = YUKA;
							}
						}
						if (map[7][27] != BLOCK7 || map[7][27] == BLOCK7)
						{
							if (map[7][27] == BLOCK7 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK7;
								map[7][27] = YUKA;
							}
						}
						if (map[8][27] != BLOCK8 || map[8][27] == BLOCK8)
						{
							if (map[8][27] == BLOCK8 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK8;
								map[8][27] = YUKA;
							}
						}
						playerPosY -= playerSpeed;
					}

					if (map[playerMapY - 1][playerMapX] == BLOCK1)
					{
						map[1][27] = BLOCK1;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = MA;
						playerPosY -= playerSpeed;

					}

					if (map[playerMapY - 1][playerMapX] == BLOCK22)
					{
						map[2][27] = BLOCK22;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = MA;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK3)
					{
						map[3][27] = BLOCK3;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = MA;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK4)
					{
						map[4][27] = BLOCK4;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = MA;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK5)
					{
						map[5][27] = BLOCK5;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = MA;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK6)
					{
						map[6][27] = BLOCK6;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = MA;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK7)
					{
						map[7][27] = BLOCK7;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = MA;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK8)
					{
						map[8][27] = BLOCK8;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = MA;
						playerPosY -= playerSpeed;

					}
				}
				if (map[playerMapY][playerMapX] == YA)
				{
					if (map[playerMapY - 1][playerMapX] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = YA;
						if (map[1][27] != BLOCK1 || map[1][27] == BLOCK1)
						{
							if (map[1][27] == BLOCK1 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK1;
								map[1][27] = YUKA;
							}
						}
						if (map[2][27] != BLOCK22 || map[2][27] == BLOCK22)
						{
							if (map[2][27] == BLOCK22 && map[playerMapY][playerMapX] == map[4][11])
							{
								map[playerMapY][playerMapX] = BLOCK22;
								map[2][27] = YUKA;
							}
						}
						if (map[3][27] != BLOCK3 || map[3][27] == BLOCK3)
						{
							if (map[3][27] == BLOCK3 && map[playerMapY][playerMapX] == map[4][13])
							{
								map[playerMapY][playerMapX] = BLOCK3;
								map[3][27] = YUKA;
							}
						}
						if (map[4][27] != BLOCK4 || map[4][27] == BLOCK4)
						{
							if (map[4][27] == BLOCK4 && map[playerMapY][playerMapX] == map[4][15])
							{
								map[playerMapY][playerMapX] = BLOCK4;
								map[4][27] = YUKA;
							}
						}
						if (map[5][27] != BLOCK5 || map[5][27] == BLOCK5)
						{
							if (map[5][27] == BLOCK5 && map[playerMapY][playerMapX] == map[4][17])
							{
								map[playerMapY][playerMapX] = BLOCK5;
								map[5][27] = YUKA;
							}
						}
						if (map[6][27] != BLOCK6 || map[6][27] == BLOCK6)
						{

							if (map[6][27] == BLOCK6 && map[playerMapY][playerMapX] == /*6以降は後で*/map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK6;
								map[6][27] = YUKA;
							}
						}
						if (map[7][27] != BLOCK7 || map[7][27] == BLOCK7)
						{
							if (map[7][27] == BLOCK7 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK7;
								map[7][27] = YUKA;
							}
						}
						if (map[8][27] != BLOCK8 || map[8][27] == BLOCK8)
						{
							if (map[8][27] == BLOCK8 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK8;
								map[8][27] = YUKA;
							}
						}
						playerPosY -= playerSpeed;
					}

					if (map[playerMapY - 1][playerMapX] == BLOCK1)
					{
						map[1][27] = BLOCK1;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = YA;
						playerPosY -= playerSpeed;

					}

					if (map[playerMapY - 1][playerMapX] == BLOCK22)
					{
						map[2][27] = BLOCK22;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = YA;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK3)
					{
						map[3][27] = BLOCK3;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = YA;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK4)
					{
						map[4][27] = BLOCK4;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = YA;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK5)
					{
						map[5][27] = BLOCK5;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = YA;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK6)
					{
						map[6][27] = BLOCK6;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = YA;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK7)
					{
						map[7][27] = BLOCK7;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = YA;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK8)
					{
						map[8][27] = BLOCK8;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = YA;
						playerPosY -= playerSpeed;

					}
				}
				if (map[playerMapY][playerMapX] == RI)
				{
					if (map[playerMapY - 1][playerMapX] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = RI;
						if (map[1][27] != BLOCK1 || map[1][27] == BLOCK1)
						{
							if (map[1][27] == BLOCK1 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK1;
								map[1][27] = YUKA;
							}
						}
						if (map[2][27] != BLOCK22 || map[2][27] == BLOCK22)
						{
							if (map[2][27] == BLOCK22 && map[playerMapY][playerMapX] == map[4][11])
							{
								map[playerMapY][playerMapX] = BLOCK22;
								map[2][27] = YUKA;
							}
						}
						if (map[3][27] != BLOCK3 || map[3][27] == BLOCK3)
						{
							if (map[3][27] == BLOCK3 && map[playerMapY][playerMapX] == map[4][13])
							{
								map[playerMapY][playerMapX] = BLOCK3;
								map[3][27] = YUKA;
							}
						}
						if (map[4][27] != BLOCK4 || map[4][27] == BLOCK4)
						{
							if (map[4][27] == BLOCK4 && map[playerMapY][playerMapX] == map[4][15])
							{
								map[playerMapY][playerMapX] = BLOCK4;
								map[4][27] = YUKA;
							}
						}
						if (map[5][27] != BLOCK5 || map[5][27] == BLOCK5)
						{
							if (map[5][27] == BLOCK5 && map[playerMapY][playerMapX] == map[4][17])
							{
								map[playerMapY][playerMapX] = BLOCK5;
								map[5][27] = YUKA;
							}
						}
						if (map[6][27] != BLOCK6 || map[6][27] == BLOCK6)
						{

							if (map[6][27] == BLOCK6 && map[playerMapY][playerMapX] == /*6以降は後で*/map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK6;
								map[6][27] = YUKA;
							}
						}
						if (map[7][27] != BLOCK7 || map[7][27] == BLOCK7)
						{
							if (map[7][27] == BLOCK7 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK7;
								map[7][27] = YUKA;
							}
						}
						if (map[8][27] != BLOCK8 || map[8][27] == BLOCK8)
						{
							if (map[8][27] == BLOCK8 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK8;
								map[8][27] = YUKA;
							}
						}
						playerPosY -= playerSpeed;
					}

					if (map[playerMapY - 1][playerMapX] == BLOCK1)
					{
						map[1][27] = BLOCK1;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = RI;
						playerPosY -= playerSpeed;

					}

					if (map[playerMapY - 1][playerMapX] == BLOCK22)
					{
						map[2][27] = BLOCK22;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = RI;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK3)
					{
						map[3][27] = BLOCK3;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = RI;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK4)
					{
						map[4][27] = BLOCK4;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = RI;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK5)
					{
						map[5][27] = BLOCK5;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = RI;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK6)
					{
						map[6][27] = BLOCK6;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = RI;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK7)
					{
						map[7][27] = BLOCK7;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = RI;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK8)
					{
						map[8][27] = BLOCK8;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = RI;
						playerPosY -= playerSpeed;

					}
				}
				if (map[playerMapY][playerMapX] == RU)
				{
					if (map[playerMapY - 1][playerMapX] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = RU;
						if (map[1][27] != BLOCK1 || map[1][27] == BLOCK1)
						{
							if (map[1][27] == BLOCK1 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK1;
								map[1][27] = YUKA;
							}
						}
						if (map[2][27] != BLOCK22 || map[2][27] == BLOCK22)
						{
							if (map[2][27] == BLOCK22 && map[playerMapY][playerMapX] == map[4][11])
							{
								map[playerMapY][playerMapX] = BLOCK22;
								map[2][27] = YUKA;
							}
						}
						if (map[3][27] != BLOCK3 || map[3][27] == BLOCK3)
						{
							if (map[3][27] == BLOCK3 && map[playerMapY][playerMapX] == map[4][13])
							{
								map[playerMapY][playerMapX] = BLOCK3;
								map[3][27] = YUKA;
							}
						}
						if (map[4][27] != BLOCK4 || map[4][27] == BLOCK4)
						{
							if (map[4][27] == BLOCK4 && map[playerMapY][playerMapX] == map[4][15])
							{
								map[playerMapY][playerMapX] = BLOCK4;
								map[4][27] = YUKA;
							}
						}
						if (map[5][27] != BLOCK5 || map[5][27] == BLOCK5)
						{
							if (map[5][27] == BLOCK5 && map[playerMapY][playerMapX] == map[4][17])
							{
								map[playerMapY][playerMapX] = BLOCK5;
								map[5][27] = YUKA;
							}
						}
						if (map[6][27] != BLOCK6 || map[6][27] == BLOCK6)
						{

							if (map[6][27] == BLOCK6 && map[playerMapY][playerMapX] == /*6以降は後で*/map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK6;
								map[6][27] = YUKA;
							}
						}
						if (map[7][27] != BLOCK7 || map[7][27] == BLOCK7)
						{
							if (map[7][27] == BLOCK7 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK7;
								map[7][27] = YUKA;
							}
						}
						if (map[8][27] != BLOCK8 || map[8][27] == BLOCK8)
						{
							if (map[8][27] == BLOCK8 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK8;
								map[8][27] = YUKA;
							}
						}
						playerPosY -= playerSpeed;
					}

					if (map[playerMapY - 1][playerMapX] == BLOCK1)
					{
						map[1][27] = BLOCK1;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = RU;
						playerPosY -= playerSpeed;

					}

					if (map[playerMapY - 1][playerMapX] == BLOCK22)
					{
						map[2][27] = BLOCK22;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = RU;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK3)
					{
						map[3][27] = BLOCK3;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = RU;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK4)
					{
						map[4][27] = BLOCK4;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = RU;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK5)
					{
						map[5][27] = BLOCK5;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = RU;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK6)
					{
						map[6][27] = BLOCK6;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = RU;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK7)
					{
						map[7][27] = BLOCK7;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = RU;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK8)
					{
						map[8][27] = BLOCK8;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = RU;
						playerPosY -= playerSpeed;

					}
				}
				if (map[playerMapY][playerMapX] == WA)
				{
					if (map[playerMapY - 1][playerMapX] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = WA;
						if (map[1][27] != BLOCK1 || map[1][27] == BLOCK1)
						{
							if (map[1][27] == BLOCK1 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK1;
								map[1][27] = YUKA;
							}
						}
						if (map[2][27] != BLOCK22 || map[2][27] == BLOCK22)
						{
							if (map[2][27] == BLOCK22 && map[playerMapY][playerMapX] == map[4][11])
							{
								map[playerMapY][playerMapX] = BLOCK22;
								map[2][27] = YUKA;
							}
						}
						if (map[3][27] != BLOCK3 || map[3][27] == BLOCK3)
						{
							if (map[3][27] == BLOCK3 && map[playerMapY][playerMapX] == map[4][13])
							{
								map[playerMapY][playerMapX] = BLOCK3;
								map[3][27] = YUKA;
							}
						}
						if (map[4][27] != BLOCK4 || map[4][27] == BLOCK4)
						{
							if (map[4][27] == BLOCK4 && map[playerMapY][playerMapX] == map[4][15])
							{
								map[playerMapY][playerMapX] = BLOCK4;
								map[4][27] = YUKA;
							}
						}
						if (map[5][27] != BLOCK5 || map[5][27] == BLOCK5)
						{
							if (map[5][27] == BLOCK5 && map[playerMapY][playerMapX] == map[4][17])
							{
								map[playerMapY][playerMapX] = BLOCK5;
								map[5][27] = YUKA;
							}
						}
						if (map[6][27] != BLOCK6 || map[6][27] == BLOCK6)
						{

							if (map[6][27] == BLOCK6 && map[playerMapY][playerMapX] == /*6以降は後で*/map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK6;
								map[6][27] = YUKA;
							}
						}
						if (map[7][27] != BLOCK7 || map[7][27] == BLOCK7)
						{
							if (map[7][27] == BLOCK7 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK7;
								map[7][27] = YUKA;
							}
						}
						if (map[8][27] != BLOCK8 || map[8][27] == BLOCK8)
						{
							if (map[8][27] == BLOCK8 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK8;
								map[8][27] = YUKA;
							}
						}
						playerPosY -= playerSpeed;
					}

					if (map[playerMapY - 1][playerMapX] == BLOCK1)
					{
						map[1][27] = BLOCK1;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = WA;
						playerPosY -= playerSpeed;

					}

					if (map[playerMapY - 1][playerMapX] == BLOCK22)
					{
						map[2][27] = BLOCK22;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = WA;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK3)
					{
						map[3][27] = BLOCK3;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = WA;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK4)
					{
						map[4][27] = BLOCK4;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = WA;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK5)
					{
						map[5][27] = BLOCK5;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = WA;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK6)
					{
						map[6][27] = BLOCK6;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = WA;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK7)
					{
						map[7][27] = BLOCK7;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = WA;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK8)
					{
						map[8][27] = BLOCK8;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = WA;
						playerPosY -= playerSpeed;

					}
				}
				if (map[playerMapY][playerMapX] == NN)
				{
					if (map[playerMapY - 1][playerMapX] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = NN;
						if (map[1][27] != BLOCK1 || map[1][27] == BLOCK1)
						{
							if (map[1][27] == BLOCK1 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK1;
								map[1][27] = YUKA;
							}
						}
						if (map[2][27] != BLOCK22 || map[2][27] == BLOCK22)
						{
							if (map[2][27] == BLOCK22 && map[playerMapY][playerMapX] == map[4][11])
							{
								map[playerMapY][playerMapX] = BLOCK22;
								map[2][27] = YUKA;
							}
						}
						if (map[3][27] != BLOCK3 || map[3][27] == BLOCK3)
						{
							if (map[3][27] == BLOCK3 && map[playerMapY][playerMapX] == map[4][13])
							{
								map[playerMapY][playerMapX] = BLOCK3;
								map[3][27] = YUKA;
							}
						}
						if (map[4][27] != BLOCK4 || map[4][27] == BLOCK4)
						{
							if (map[4][27] == BLOCK4 && map[playerMapY][playerMapX] == map[4][15])
							{
								map[playerMapY][playerMapX] = BLOCK4;
								map[4][27] = YUKA;
							}
						}
						if (map[5][27] != BLOCK5 || map[5][27] == BLOCK5)
						{
							if (map[5][27] == BLOCK5 && map[playerMapY][playerMapX] == map[4][17])
							{
								map[playerMapY][playerMapX] = BLOCK5;
								map[5][27] = YUKA;
							}
						}
						if (map[6][27] != BLOCK6 || map[6][27] == BLOCK6)
						{

							if (map[6][27] == BLOCK6 && map[playerMapY][playerMapX] == /*6以降は後で*/map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK6;
								map[6][27] = YUKA;
							}
						}
						if (map[7][27] != BLOCK7 || map[7][27] == BLOCK7)
						{
							if (map[7][27] == BLOCK7 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK7;
								map[7][27] = YUKA;
							}
						}
						if (map[8][27] != BLOCK8 || map[8][27] == BLOCK8)
						{
							if (map[8][27] == BLOCK8 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK8;
								map[8][27] = YUKA;
							}
						}
						playerPosY -= playerSpeed;
					}

					if (map[playerMapY - 1][playerMapX] == BLOCK1)
					{
						map[1][27] = BLOCK1;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = NN;
						playerPosY -= playerSpeed;

					}

					if (map[playerMapY - 1][playerMapX] == BLOCK22)
					{
						map[2][27] = BLOCK22;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = NN;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK3)
					{
						map[3][27] = BLOCK3;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = NN;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK4)
					{
						map[4][27] = BLOCK4;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = NN;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK5)
					{
						map[5][27] = BLOCK5;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = NN;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK6)
					{
						map[6][27] = BLOCK6;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = NN;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK7)
					{
						map[7][27] = BLOCK7;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = NN;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK8)
					{
						map[8][27] = BLOCK8;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = NN;
						playerPosY -= playerSpeed;

					}
				}
				if (map[playerMapY][playerMapX] == GI)
				{
					if (map[playerMapY - 1][playerMapX] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = GI;
						if (map[1][27] != BLOCK1 || map[1][27] == BLOCK1)
						{
							if (map[1][27] == BLOCK1 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK1;
								map[1][27] = YUKA;
							}
						}
						if (map[2][27] != BLOCK22 || map[2][27] == BLOCK22)
						{
							if (map[2][27] == BLOCK22 && map[playerMapY][playerMapX] == map[4][11])
							{
								map[playerMapY][playerMapX] = BLOCK22;
								map[2][27] = YUKA;
							}
						}
						if (map[3][27] != BLOCK3 || map[3][27] == BLOCK3)
						{
							if (map[3][27] == BLOCK3 && map[playerMapY][playerMapX] == map[4][13])
							{
								map[playerMapY][playerMapX] = BLOCK3;
								map[3][27] = YUKA;
							}
						}
						if (map[4][27] != BLOCK4 || map[4][27] == BLOCK4)
						{
							if (map[4][27] == BLOCK4 && map[playerMapY][playerMapX] == map[4][15])
							{
								map[playerMapY][playerMapX] = BLOCK4;
								map[4][27] = YUKA;
							}
						}
						if (map[5][27] != BLOCK5 || map[5][27] == BLOCK5)
						{
							if (map[5][27] == BLOCK5 && map[playerMapY][playerMapX] == map[4][17])
							{
								map[playerMapY][playerMapX] = BLOCK5;
								map[5][27] = YUKA;
							}
						}
						if (map[6][27] != BLOCK6 || map[6][27] == BLOCK6)
						{

							if (map[6][27] == BLOCK6 && map[playerMapY][playerMapX] == /*6以降は後で*/map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK6;
								map[6][27] = YUKA;
							}
						}
						if (map[7][27] != BLOCK7 || map[7][27] == BLOCK7)
						{
							if (map[7][27] == BLOCK7 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK7;
								map[7][27] = YUKA;
							}
						}
						if (map[8][27] != BLOCK8 || map[8][27] == BLOCK8)
						{
							if (map[8][27] == BLOCK8 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK8;
								map[8][27] = YUKA;
							}
						}
						playerPosY -= playerSpeed;
					}

					if (map[playerMapY - 1][playerMapX] == BLOCK1)
					{
						map[1][27] = BLOCK1;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = GI;
						playerPosY -= playerSpeed;

					}

					if (map[playerMapY - 1][playerMapX] == BLOCK22)
					{
						map[2][27] = BLOCK22;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = GI;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK3)
					{
						map[3][27] = BLOCK3;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = GI;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK4)
					{
						map[4][27] = BLOCK4;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = GI;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK5)
					{
						map[5][27] = BLOCK5;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = GI;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK6)
					{
						map[6][27] = BLOCK6;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = GI;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK7)
					{
						map[7][27] = BLOCK7;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = GI;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK8)
					{
						map[8][27] = BLOCK8;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = GI;
						playerPosY -= playerSpeed;

					}
				}
				if (map[playerMapY][playerMapX] == ZO)
				{
					if (map[playerMapY - 1][playerMapX] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = ZO;
						if (map[1][27] != BLOCK1 || map[1][27] == BLOCK1)
						{
							if (map[1][27] == BLOCK1 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK1;
								map[1][27] = YUKA;
							}
						}
						if (map[2][27] != BLOCK22 || map[2][27] == BLOCK22)
						{
							if (map[2][27] == BLOCK22 && map[playerMapY][playerMapX] == map[4][11])
							{
								map[playerMapY][playerMapX] = BLOCK22;
								map[2][27] = YUKA;
							}
						}
						if (map[3][27] != BLOCK3 || map[3][27] == BLOCK3)
						{
							if (map[3][27] == BLOCK3 && map[playerMapY][playerMapX] == map[4][13])
							{
								map[playerMapY][playerMapX] = BLOCK3;
								map[3][27] = YUKA;
							}
						}
						if (map[4][27] != BLOCK4 || map[4][27] == BLOCK4)
						{
							if (map[4][27] == BLOCK4 && map[playerMapY][playerMapX] == map[4][15])
							{
								map[playerMapY][playerMapX] = BLOCK4;
								map[4][27] = YUKA;
							}
						}
						if (map[5][27] != BLOCK5 || map[5][27] == BLOCK5)
						{
							if (map[5][27] == BLOCK5 && map[playerMapY][playerMapX] == map[4][17])
							{
								map[playerMapY][playerMapX] = BLOCK5;
								map[5][27] = YUKA;
							}
						}
						if (map[6][27] != BLOCK6 || map[6][27] == BLOCK6)
						{

							if (map[6][27] == BLOCK6 && map[playerMapY][playerMapX] == /*6以降は後で*/map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK6;
								map[6][27] = YUKA;
							}
						}
						if (map[7][27] != BLOCK7 || map[7][27] == BLOCK7)
						{
							if (map[7][27] == BLOCK7 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK7;
								map[7][27] = YUKA;
							}
						}
						if (map[8][27] != BLOCK8 || map[8][27] == BLOCK8)
						{
							if (map[8][27] == BLOCK8 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK8;
								map[8][27] = YUKA;
							}
						}
						playerPosY -= playerSpeed;
					}
					if (map[playerMapY - 1][playerMapX] == BLOCK1)
					{
						map[1][27] = BLOCK1;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = ZO;
						playerPosY -= playerSpeed;

					}

					if (map[playerMapY - 1][playerMapX] == BLOCK22)
					{
						map[2][27] = BLOCK22;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = ZO;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK3)
					{
						map[3][27] = BLOCK3;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = ZO;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK4)
					{
						map[4][27] = BLOCK4;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = ZO;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK5)
					{
						map[5][27] = BLOCK5;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = ZO;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK6)
					{
						map[6][27] = BLOCK6;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = ZO;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK7)
					{
						map[7][27] = BLOCK7;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = ZO;
						playerPosY -= playerSpeed;

					}
					if (map[playerMapY - 1][playerMapX] == BLOCK8)
					{
						map[8][27] = BLOCK8;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY - 1][playerMapX] = ZO;
						playerPosY -= playerSpeed;

					}
				}
			}

			if (keys[DIK_A] && preKeys[DIK_A] == 0 || keys[DIK_LEFT] && preKeys[DIK_LEFT] == 0)
			{
				playerTmpX = playerPosX - playerSpeed;
				playerMapX = playerTmpX / KBlockSize;
				//何もないから実際に進ませる
				if (map[playerMapY][playerMapX] == YUKA)
				{
					playerPosX -= playerSpeed;
				}
				if (map[playerMapY][playerMapX] == BLOCK1)
				{
					playerPosX -= playerSpeed;
				}
				if (map[playerMapY][playerMapX] == GOAL)
				{
					playerPosX -= playerSpeed;
				}
				if (map[playerMapY][playerMapX] == THORN)
				{
					playerPosX -= playerSpeed;
				}

				if (map[playerMapY][playerMapX] == I)
				{
					if (map[playerMapY][playerMapX - 1] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX - 1] = I;
						if (map[1][27] != BLOCK1 || map[1][27] == BLOCK1)
						{
							if (map[1][27] == BLOCK1 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK1;
								map[1][27] = YUKA;
							}
						}
						if (map[2][27] != BLOCK22 || map[2][27] == BLOCK22)
						{
							if (map[2][27] == BLOCK22 && map[playerMapY][playerMapX] == map[4][11])
							{
								map[playerMapY][playerMapX] = BLOCK22;
								map[2][27] = YUKA;
							}
						}
						if (map[3][27] != BLOCK3 || map[3][27] == BLOCK3)
						{
							if (map[3][27] == BLOCK3 && map[playerMapY][playerMapX] == map[4][13])
							{
								map[playerMapY][playerMapX] = BLOCK3;
								map[3][27] = YUKA;
							}
						}
						if (map[4][27] != BLOCK4 || map[4][27] == BLOCK4)
						{
							if (map[4][27] == BLOCK4 && map[playerMapY][playerMapX] == map[4][15])
							{
								map[playerMapY][playerMapX] = BLOCK4;
								map[4][27] = YUKA;
							}
						}
						if (map[5][27] != BLOCK5 || map[5][27] == BLOCK5)
						{
							if (map[5][27] == BLOCK5 && map[playerMapY][playerMapX] == map[4][17])
							{
								map[playerMapY][playerMapX] = BLOCK5;
								map[5][27] = YUKA;
							}
						}
						if (map[6][27] != BLOCK6 || map[6][27] == BLOCK6)
						{

							if (map[6][27] == BLOCK6 && map[playerMapY][playerMapX] == /*6以降は後で*/map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK6;
								map[6][27] = YUKA;
							}
						}
						if (map[7][27] != BLOCK7 || map[7][27] == BLOCK7)
						{
							if (map[7][27] == BLOCK7 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK7;
								map[7][27] = YUKA;
							}
						}
						if (map[8][27] != BLOCK8 || map[8][27] == BLOCK8)
						{
							if (map[8][27] == BLOCK8 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK8;
								map[8][27] = YUKA;
							}
						}

						playerPosX -= playerSpeed;
					}
				}


			}

			// 1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111
			// ここから直して
			if (map[playerMapY][playerMapX] == U)
			{
				if (map[playerMapY][playerMapX - 1] == YUKA)
				{
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = U; //ここをUに変える　したも同じ
					if (map[1][27] != BLOCK1 || map[1][27] == BLOCK1)
					{
						if (map[1][27] == BLOCK1 && map[playerMapY][playerMapX] == map[4][9])
						{
							map[playerMapY][playerMapX] = BLOCK1;
							map[1][27] = YUKA;
						}
					}
					if (map[2][27] != BLOCK22 || map[2][27] == BLOCK22)
					{
						if (map[2][27] == BLOCK22 && map[playerMapY][playerMapX] == map[4][11])
						{
							map[playerMapY][playerMapX] = BLOCK22;
							map[2][27] = YUKA;
						}
					}
					if (map[3][27] != BLOCK3 || map[3][27] == BLOCK3)
					{
						if (map[3][27] == BLOCK3 && map[playerMapY][playerMapX] == map[4][13])
						{
							map[playerMapY][playerMapX] = BLOCK3;
							map[3][27] = YUKA;
						}
					}
					if (map[4][27] != BLOCK4 || map[4][27] == BLOCK4)
					{
						if (map[4][27] == BLOCK4 && map[playerMapY][playerMapX] == map[4][15])
						{
							map[playerMapY][playerMapX] = BLOCK4;
							map[4][27] = YUKA;
						}
					}
					if (map[5][27] != BLOCK5 || map[5][27] == BLOCK5)
					{
						if (map[5][27] == BLOCK5 && map[playerMapY][playerMapX] == map[4][17])
						{
							map[playerMapY][playerMapX] = BLOCK5;
							map[5][27] = YUKA;
						}
					}
					if (map[6][27] != BLOCK6 || map[6][27] == BLOCK6)
					{

						if (map[6][27] == BLOCK6 && map[playerMapY][playerMapX] == /*6以降は後で*/map[4][9])
						{
							map[playerMapY][playerMapX] = BLOCK6;
							map[6][27] = YUKA;
						}
					}
					if (map[7][27] != BLOCK7 || map[7][27] == BLOCK7)
					{
						if (map[7][27] == BLOCK7 && map[playerMapY][playerMapX] == map[4][9])
						{
							map[playerMapY][playerMapX] = BLOCK7;
							map[7][27] = YUKA;
						}
					}
					if (map[8][27] != BLOCK8 || map[8][27] == BLOCK8)
					{
						if (map[8][27] == BLOCK8 && map[playerMapY][playerMapX] == map[4][9])
						{
							map[playerMapY][playerMapX] = BLOCK8;
							map[8][27] = YUKA;
						}
					}

					playerPosX -= playerSpeed;
				}

				if (map[playerMapY][playerMapX - 1] == BLOCK1)
				{
					map[1][27] = BLOCK1;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = U;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK22)
				{
					map[2][27] = BLOCK22;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = U;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK3)
				{
					map[3][27] = BLOCK3;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = U;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK4)
				{
					map[4][27] = BLOCK4;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = U;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK5)
				{
					map[5][27] = BLOCK5;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = U;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK6)
				{
					map[6][27] = BLOCK6;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = U;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK7)
				{
					map[7][27] = BLOCK7;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = U;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK8)
				{
					map[8][27] = BLOCK8;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = U;
					playerPosX -= playerSpeed;

				}
			}
			if (map[playerMapY][playerMapX] == E)
			{
				if (map[playerMapY][playerMapX - 1] == YUKA)
				{
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = E;
					if (map[1][27] != BLOCK1 || map[1][27] == BLOCK1)
					{
						if (map[1][27] == BLOCK1 && map[playerMapY][playerMapX] == map[4][9])
						{
							map[playerMapY][playerMapX] = BLOCK1;
							map[1][27] = YUKA;
						}
					}
					if (map[2][27] != BLOCK22 || map[2][27] == BLOCK22)
					{
						if (map[2][27] == BLOCK22 && map[playerMapY][playerMapX] == map[4][11])
						{
							map[playerMapY][playerMapX] = BLOCK22;
							map[2][27] = YUKA;
						}
					}
					if (map[3][27] != BLOCK3 || map[3][27] == BLOCK3)
					{
						if (map[3][27] == BLOCK3 && map[playerMapY][playerMapX] == map[4][13])
						{
							map[playerMapY][playerMapX] = BLOCK3;
							map[3][27] = YUKA;
						}
					}
					if (map[4][27] != BLOCK4 || map[4][27] == BLOCK4)
					{
						if (map[4][27] == BLOCK4 && map[playerMapY][playerMapX] == map[4][15])
						{
							map[playerMapY][playerMapX] = BLOCK4;
							map[4][27] = YUKA;
						}
					}
					if (map[5][27] != BLOCK5 || map[5][27] == BLOCK5)
					{
						if (map[5][27] == BLOCK5 && map[playerMapY][playerMapX] == map[4][17])
						{
							map[playerMapY][playerMapX] = BLOCK5;
							map[5][27] = YUKA;
						}
					}
					if (map[6][27] != BLOCK6 || map[6][27] == BLOCK6)
					{

						if (map[6][27] == BLOCK6 && map[playerMapY][playerMapX] == /*6以降は後で*/map[4][9])
						{
							map[playerMapY][playerMapX] = BLOCK6;
							map[6][27] = YUKA;
						}
					}
					if (map[7][27] != BLOCK7 || map[7][27] == BLOCK7)
					{
						if (map[7][27] == BLOCK7 && map[playerMapY][playerMapX] == map[4][9])
						{
							map[playerMapY][playerMapX] = BLOCK7;
							map[7][27] = YUKA;
						}
					}
					if (map[8][27] != BLOCK8 || map[8][27] == BLOCK8)
					{
						if (map[8][27] == BLOCK8 && map[playerMapY][playerMapX] == map[4][9])
						{
							map[playerMapY][playerMapX] = BLOCK8;
							map[8][27] = YUKA;
						}
					}

					playerPosX -= playerSpeed;
				}
				if (map[playerMapY][playerMapX - 1] == BLOCK1)
				{
					map[1][27] = BLOCK1;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = E;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK22)
				{
					map[2][27] = BLOCK22;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = E;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK3)
				{
					map[3][27] = BLOCK3;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = E;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK4)
				{
					map[4][27] = BLOCK4;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = E;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK5)
				{
					map[5][27] = BLOCK5;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = E;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK6)
				{
					map[6][27] = BLOCK6;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = E;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK7)
				{
					map[7][27] = BLOCK7;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = E;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK8)
				{
					map[8][27] = BLOCK8;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = E;
					playerPosX -= playerSpeed;

				}
			}
			if (map[playerMapY][playerMapX] == KA)
			{
				if (map[playerMapY][playerMapX - 1] == YUKA)
				{
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = KA;
					if (map[1][27] != BLOCK1 || map[1][27] == BLOCK1)
					{
						if (map[1][27] == BLOCK1 && map[playerMapY][playerMapX] == map[4][9])
						{
							map[playerMapY][playerMapX] = BLOCK1;
							map[1][27] = YUKA;
						}
					}
					if (map[2][27] != BLOCK22 || map[2][27] == BLOCK22)
					{
						if (map[2][27] == BLOCK22 && map[playerMapY][playerMapX] == map[4][11])
						{
							map[playerMapY][playerMapX] = BLOCK22;
							map[2][27] = YUKA;
						}
					}
					if (map[3][27] != BLOCK3 || map[3][27] == BLOCK3)
					{
						if (map[3][27] == BLOCK3 && map[playerMapY][playerMapX] == map[4][13])
						{
							map[playerMapY][playerMapX] = BLOCK3;
							map[3][27] = YUKA;
						}
					}
					if (map[4][27] != BLOCK4 || map[4][27] == BLOCK4)
					{
						if (map[4][27] == BLOCK4 && map[playerMapY][playerMapX] == map[4][15])
						{
							map[playerMapY][playerMapX] = BLOCK4;
							map[4][27] = YUKA;
						}
					}
					if (map[5][27] != BLOCK5 || map[5][27] == BLOCK5)
					{
						if (map[5][27] == BLOCK5 && map[playerMapY][playerMapX] == map[4][17])
						{
							map[playerMapY][playerMapX] = BLOCK5;
							map[5][27] = YUKA;
						}
					}
					if (map[6][27] != BLOCK6 || map[6][27] == BLOCK6)
					{

						if (map[6][27] == BLOCK6 && map[playerMapY][playerMapX] == /*6以降は後で*/map[4][9])
						{
							map[playerMapY][playerMapX] = BLOCK6;
							map[6][27] = YUKA;
						}
					}
					if (map[7][27] != BLOCK7 || map[7][27] == BLOCK7)
					{
						if (map[7][27] == BLOCK7 && map[playerMapY][playerMapX] == map[4][9])
						{
							map[playerMapY][playerMapX] = BLOCK7;
							map[7][27] = YUKA;
						}
					}
					if (map[8][27] != BLOCK8 || map[8][27] == BLOCK8)
					{
						if (map[8][27] == BLOCK8 && map[playerMapY][playerMapX] == map[4][9])
						{
							map[playerMapY][playerMapX] = BLOCK8;
							map[8][27] = YUKA;
						}
					}

					playerPosX -= playerSpeed;
				}

				if (map[playerMapY][playerMapX - 1] == BLOCK1)
				{
					map[1][27] = BLOCK1;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = KA;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK22)
				{
					map[2][27] = BLOCK22;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = KA;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK3)
				{
					map[3][27] = BLOCK3;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = KA;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK4)
				{
					map[4][27] = BLOCK4;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = KA;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK5)
				{
					map[5][27] = BLOCK5;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = KA;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK6)
				{
					map[6][27] = BLOCK6;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = KA;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK7)
				{
					map[7][27] = BLOCK7;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = KA;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK8)
				{
					map[8][27] = BLOCK8;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = KA;
					playerPosX -= playerSpeed;

				}
			}
			if (map[playerMapY][playerMapX] == KU)
			{
				if (map[playerMapY][playerMapX - 1] == YUKA)
				{
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = KU;
					if (map[1][27] != BLOCK1 || map[1][27] == BLOCK1)
					{
						if (map[1][27] == BLOCK1 && map[playerMapY][playerMapX] == map[4][9])
						{
							map[playerMapY][playerMapX] = BLOCK1;
							map[1][27] = YUKA;
						}
					}
					if (map[2][27] != BLOCK22 || map[2][27] == BLOCK22)
					{
						if (map[2][27] == BLOCK22 && map[playerMapY][playerMapX] == map[4][11])
						{
							map[playerMapY][playerMapX] = BLOCK22;
							map[2][27] = YUKA;
						}
					}
					if (map[3][27] != BLOCK3 || map[3][27] == BLOCK3)
					{
						if (map[3][27] == BLOCK3 && map[playerMapY][playerMapX] == map[4][13])
						{
							map[playerMapY][playerMapX] = BLOCK3;
							map[3][27] = YUKA;
						}
					}
					if (map[4][27] != BLOCK4 || map[4][27] == BLOCK4)
					{
						if (map[4][27] == BLOCK4 && map[playerMapY][playerMapX] == map[4][15])
						{
							map[playerMapY][playerMapX] = BLOCK4;
							map[4][27] = YUKA;
						}
					}
					if (map[5][27] != BLOCK5 || map[5][27] == BLOCK5)
					{
						if (map[5][27] == BLOCK5 && map[playerMapY][playerMapX] == map[4][17])
						{
							map[playerMapY][playerMapX] = BLOCK5;
							map[5][27] = YUKA;
						}
					}
					if (map[6][27] != BLOCK6 || map[6][27] == BLOCK6)
					{

						if (map[6][27] == BLOCK6 && map[playerMapY][playerMapX] == /*6以降は後で*/map[4][9])
						{
							map[playerMapY][playerMapX] = BLOCK6;
							map[6][27] = YUKA;
						}
					}
					if (map[7][27] != BLOCK7 || map[7][27] == BLOCK7)
					{
						if (map[7][27] == BLOCK7 && map[playerMapY][playerMapX] == map[4][9])
						{
							map[playerMapY][playerMapX] = BLOCK7;
							map[7][27] = YUKA;
						}
					}
					if (map[8][27] != BLOCK8 || map[8][27] == BLOCK8)
					{
						if (map[8][27] == BLOCK8 && map[playerMapY][playerMapX] == map[4][9])
						{
							map[playerMapY][playerMapX] = BLOCK8;
							map[8][27] = YUKA;
						}
					}

					playerPosX -= playerSpeed;
				}

				if (map[playerMapY][playerMapX - 1] == BLOCK1)
				{
					map[1][27] = BLOCK1;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = KU;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK22)
				{
					map[2][27] = BLOCK22;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = KU;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK3)
				{
					map[3][27] = BLOCK3;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = KU;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK4)
				{
					map[4][27] = BLOCK4;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = KU;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK5)
				{
					map[5][27] = BLOCK5;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = KU;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK6)
				{
					map[6][27] = BLOCK6;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = KU;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK7)
				{
					map[7][27] = BLOCK7;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = KU;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK8)
				{
					map[8][27] = BLOCK8;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = KU;
					playerPosX -= playerSpeed;

				}
			}
			if (map[playerMapY][playerMapX] == KO)
			{
				if (map[playerMapY][playerMapX - 1] == YUKA)
				{
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = KO;
					if (map[1][27] != BLOCK1 || map[1][27] == BLOCK1)
					{
						if (map[1][27] == BLOCK1 && map[playerMapY][playerMapX] == map[4][9])
						{
							map[playerMapY][playerMapX] = BLOCK1;
							map[1][27] = YUKA;
						}
					}
					if (map[2][27] != BLOCK22 || map[2][27] == BLOCK22)
					{
						if (map[2][27] == BLOCK22 && map[playerMapY][playerMapX] == map[4][11])
						{
							map[playerMapY][playerMapX] = BLOCK22;
							map[2][27] = YUKA;
						}
					}
					if (map[3][27] != BLOCK3 || map[3][27] == BLOCK3)
					{
						if (map[3][27] == BLOCK3 && map[playerMapY][playerMapX] == map[4][13])
						{
							map[playerMapY][playerMapX] = BLOCK3;
							map[3][27] = YUKA;
						}
					}
					if (map[4][27] != BLOCK4 || map[4][27] == BLOCK4)
					{
						if (map[4][27] == BLOCK4 && map[playerMapY][playerMapX] == map[4][15])
						{
							map[playerMapY][playerMapX] = BLOCK4;
							map[4][27] = YUKA;
						}
					}
					if (map[5][27] != BLOCK5 || map[5][27] == BLOCK5)
					{
						if (map[5][27] == BLOCK5 && map[playerMapY][playerMapX] == map[4][17])
						{
							map[playerMapY][playerMapX] = BLOCK5;
							map[5][27] = YUKA;
						}
					}
					if (map[6][27] != BLOCK6 || map[6][27] == BLOCK6)
					{

						if (map[6][27] == BLOCK6 && map[playerMapY][playerMapX] == /*6以降は後で*/map[4][9])
						{
							map[playerMapY][playerMapX] = BLOCK6;
							map[6][27] = YUKA;
						}
					}
					if (map[7][27] != BLOCK7 || map[7][27] == BLOCK7)
					{
						if (map[7][27] == BLOCK7 && map[playerMapY][playerMapX] == map[4][9])
						{
							map[playerMapY][playerMapX] = BLOCK7;
							map[7][27] = YUKA;
						}
					}
					if (map[8][27] != BLOCK8 || map[8][27] == BLOCK8)
					{
						if (map[8][27] == BLOCK8 && map[playerMapY][playerMapX] == map[4][9])
						{
							map[playerMapY][playerMapX] = BLOCK8;
							map[8][27] = YUKA;
						}
					}

					playerPosX -= playerSpeed;
				}

				if (map[playerMapY][playerMapX - 1] == BLOCK1)
				{
					map[1][27] = BLOCK1;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = KO;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK22)
				{
					map[2][27] = BLOCK22;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = KO;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK3)
				{
					map[3][27] = BLOCK3;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = KO;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK4)
				{
					map[4][27] = BLOCK4;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = KO;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK5)
				{
					map[5][27] = BLOCK5;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = KO;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK6)
				{
					map[6][27] = BLOCK6;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = KO;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK7)
				{
					map[7][27] = BLOCK7;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = KO;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK8)
				{
					map[8][27] = BLOCK8;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = KO;
					playerPosX -= playerSpeed;

				}
			}
			if (map[playerMapY][playerMapX] == SA)
			{
				if (map[playerMapY][playerMapX - 1] == YUKA)
				{
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = SA;
					if (map[1][27] != BLOCK1 || map[1][27] == BLOCK1)
					{
						if (map[1][27] == BLOCK1 && map[playerMapY][playerMapX] == map[4][9])
						{
							map[playerMapY][playerMapX] = BLOCK1;
							map[1][27] = YUKA;
						}
					}
					if (map[2][27] != BLOCK22 || map[2][27] == BLOCK22)
					{
						if (map[2][27] == BLOCK22 && map[playerMapY][playerMapX] == map[4][11])
						{
							map[playerMapY][playerMapX] = BLOCK22;
							map[2][27] = YUKA;
						}
					}
					if (map[3][27] != BLOCK3 || map[3][27] == BLOCK3)
					{
						if (map[3][27] == BLOCK3 && map[playerMapY][playerMapX] == map[4][13])
						{
							map[playerMapY][playerMapX] = BLOCK3;
							map[3][27] = YUKA;
						}
					}
					if (map[4][27] != BLOCK4 || map[4][27] == BLOCK4)
					{
						if (map[4][27] == BLOCK4 && map[playerMapY][playerMapX] == map[4][15])
						{
							map[playerMapY][playerMapX] = BLOCK4;
							map[4][27] = YUKA;
						}
					}
					if (map[5][27] != BLOCK5 || map[5][27] == BLOCK5)
					{
						if (map[5][27] == BLOCK5 && map[playerMapY][playerMapX] == map[4][17])
						{
							map[playerMapY][playerMapX] = BLOCK5;
							map[5][27] = YUKA;
						}
					}
					if (map[6][27] != BLOCK6 || map[6][27] == BLOCK6)
					{

						if (map[6][27] == BLOCK6 && map[playerMapY][playerMapX] == /*6以降は後で*/map[4][9])
						{
							map[playerMapY][playerMapX] = BLOCK6;
							map[6][27] = YUKA;
						}
					}
					if (map[7][27] != BLOCK7 || map[7][27] == BLOCK7)
					{
						if (map[7][27] == BLOCK7 && map[playerMapY][playerMapX] == map[4][9])
						{
							map[playerMapY][playerMapX] = BLOCK7;
							map[7][27] = YUKA;
						}
					}
					if (map[8][27] != BLOCK8 || map[8][27] == BLOCK8)
					{
						if (map[8][27] == BLOCK8 && map[playerMapY][playerMapX] == map[4][9])
						{
							map[playerMapY][playerMapX] = BLOCK8;
							map[8][27] = YUKA;
						}
					}

					playerPosX -= playerSpeed;
				}
				if (map[playerMapY][playerMapX - 1] == BLOCK1)
				{
					map[1][27] = BLOCK1;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = SA;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK22)
				{
					map[2][27] = BLOCK22;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = SA;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK3)
				{
					map[3][27] = BLOCK3;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = SA;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK4)
				{
					map[4][27] = BLOCK4;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = SA;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK5)
				{
					map[5][27] = BLOCK5;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = SA;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK6)
				{
					map[6][27] = BLOCK6;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = SA;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK7)
				{
					map[7][27] = BLOCK7;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = SA;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK8)
				{
					map[8][27] = BLOCK8;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = SA;
					playerPosX -= playerSpeed;

				}
			}
			if (map[playerMapY][playerMapX] == SU)
			{
				if (map[playerMapY][playerMapX - 1] == YUKA)
				{
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = SU;
					if (map[1][27] != BLOCK1 || map[1][27] == BLOCK1)
					{
						if (map[1][27] == BLOCK1 && map[playerMapY][playerMapX] == map[4][9])
						{
							map[playerMapY][playerMapX] = BLOCK1;
							map[1][27] = YUKA;
						}
					}
					if (map[2][27] != BLOCK22 || map[2][27] == BLOCK22)
					{
						if (map[2][27] == BLOCK22 && map[playerMapY][playerMapX] == map[4][11])
						{
							map[playerMapY][playerMapX] = BLOCK22;
							map[2][27] = YUKA;
						}
					}
					if (map[3][27] != BLOCK3 || map[3][27] == BLOCK3)
					{
						if (map[3][27] == BLOCK3 && map[playerMapY][playerMapX] == map[4][13])
						{
							map[playerMapY][playerMapX] = BLOCK3;
							map[3][27] = YUKA;
						}
					}
					if (map[4][27] != BLOCK4 || map[4][27] == BLOCK4)
					{
						if (map[4][27] == BLOCK4 && map[playerMapY][playerMapX] == map[4][15])
						{
							map[playerMapY][playerMapX] = BLOCK4;
							map[4][27] = YUKA;
						}
					}
					if (map[5][27] != BLOCK5 || map[5][27] == BLOCK5)
					{
						if (map[5][27] == BLOCK5 && map[playerMapY][playerMapX] == map[4][17])
						{
							map[playerMapY][playerMapX] = BLOCK5;
							map[5][27] = YUKA;
						}
					}
					if (map[6][27] != BLOCK6 || map[6][27] == BLOCK6)
					{

						if (map[6][27] == BLOCK6 && map[playerMapY][playerMapX] == /*6以降は後で*/map[4][9])
						{
							map[playerMapY][playerMapX] = BLOCK6;
							map[6][27] = YUKA;
						}
					}
					if (map[7][27] != BLOCK7 || map[7][27] == BLOCK7)
					{
						if (map[7][27] == BLOCK7 && map[playerMapY][playerMapX] == map[4][9])
						{
							map[playerMapY][playerMapX] = BLOCK7;
							map[7][27] = YUKA;
						}
					}
					if (map[8][27] != BLOCK8 || map[8][27] == BLOCK8)
					{
						if (map[8][27] == BLOCK8 && map[playerMapY][playerMapX] == map[4][9])
						{
							map[playerMapY][playerMapX] = BLOCK8;
							map[8][27] = YUKA;
						}
					}
					playerPosX -= playerSpeed;
				}

				if (map[playerMapY][playerMapX - 1] == BLOCK1)
				{
					map[1][27] = BLOCK1;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = SU;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK22)
				{
					map[2][27] = BLOCK22;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = SU;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK3)
				{
					map[3][27] = BLOCK3;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = SU;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK4)
				{
					map[4][27] = BLOCK4;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = SU;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK5)
				{
					map[5][27] = BLOCK5;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = SU;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK6)
				{
					map[6][27] = BLOCK6;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = SU;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK7)
				{
					map[7][27] = BLOCK7;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = SU;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK8)
				{
					map[8][27] = BLOCK8;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = SU;
					playerPosX -= playerSpeed;

				}
			}
			if (map[playerMapY][playerMapX] == SO)
			{
				if (map[playerMapY][playerMapX - 1] == YUKA)
				{
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = SO;
					if (map[1][27] != BLOCK1 || map[1][27] == BLOCK1)
					{
						if (map[1][27] == BLOCK1 && map[playerMapY][playerMapX] == map[4][9])
						{
							map[playerMapY][playerMapX] = BLOCK1;
							map[1][27] = YUKA;
						}
					}
					if (map[2][27] != BLOCK22 || map[2][27] == BLOCK22)
					{
						if (map[2][27] == BLOCK22 && map[playerMapY][playerMapX] == map[4][11])
						{
							map[playerMapY][playerMapX] = BLOCK22;
							map[2][27] = YUKA;
						}
					}
					if (map[3][27] != BLOCK3 || map[3][27] == BLOCK3)
					{
						if (map[3][27] == BLOCK3 && map[playerMapY][playerMapX] == map[4][13])
						{
							map[playerMapY][playerMapX] = BLOCK3;
							map[3][27] = YUKA;
						}
					}
					if (map[4][27] != BLOCK4 || map[4][27] == BLOCK4)
					{
						if (map[4][27] == BLOCK4 && map[playerMapY][playerMapX] == map[4][15])
						{
							map[playerMapY][playerMapX] = BLOCK4;
							map[4][27] = YUKA;
						}
					}
					if (map[5][27] != BLOCK5 || map[5][27] == BLOCK5)
					{
						if (map[5][27] == BLOCK5 && map[playerMapY][playerMapX] == map[4][17])
						{
							map[playerMapY][playerMapX] = BLOCK5;
							map[5][27] = YUKA;
						}
					}
					if (map[6][27] != BLOCK6 || map[6][27] == BLOCK6)
					{

						if (map[6][27] == BLOCK6 && map[playerMapY][playerMapX] == /*6以降は後で*/map[4][9])
						{
							map[playerMapY][playerMapX] = BLOCK6;
							map[6][27] = YUKA;
						}
					}
					if (map[7][27] != BLOCK7 || map[7][27] == BLOCK7)
					{
						if (map[7][27] == BLOCK7 && map[playerMapY][playerMapX] == map[4][9])
						{
							map[playerMapY][playerMapX] = BLOCK7;
							map[7][27] = YUKA;
						}
					}
					if (map[8][27] != BLOCK8 || map[8][27] == BLOCK8)
					{
						if (map[8][27] == BLOCK8 && map[playerMapY][playerMapX] == map[4][9])
						{
							map[playerMapY][playerMapX] = BLOCK8;
							map[8][27] = YUKA;
						}
					}
					playerPosX -= playerSpeed;
				}

				if (map[playerMapY][playerMapX - 1] == BLOCK1)
				{
					map[1][27] = BLOCK1;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = SO;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK22)
				{
					map[2][27] = BLOCK22;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = SO;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK3)
				{
					map[3][27] = BLOCK3;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = SO;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK4)
				{
					map[4][27] = BLOCK4;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = SO;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK5)
				{
					map[5][27] = BLOCK5;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = SO;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK6)
				{
					map[6][27] = BLOCK6;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = SO;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK7)
				{
					map[7][27] = BLOCK7;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = SO;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK8)
				{
					map[8][27] = BLOCK8;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = SO;
					playerPosX -= playerSpeed;

				}
			}
			if (map[playerMapY][playerMapX] == TA)
			{
				if (map[playerMapY][playerMapX - 1] == YUKA)
				{
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = TA;
					if (map[1][27] != BLOCK1 || map[1][27] == BLOCK1)
					{
						if (map[1][27] == BLOCK1 && map[playerMapY][playerMapX] == map[4][9])
						{
							map[playerMapY][playerMapX] = BLOCK1;
							map[1][27] = YUKA;
						}
					}
					if (map[2][27] != BLOCK22 || map[2][27] == BLOCK22)
					{
						if (map[2][27] == BLOCK22 && map[playerMapY][playerMapX] == map[4][11])
						{
							map[playerMapY][playerMapX] = BLOCK22;
							map[2][27] = YUKA;
						}
					}
					if (map[3][27] != BLOCK3 || map[3][27] == BLOCK3)
					{
						if (map[3][27] == BLOCK3 && map[playerMapY][playerMapX] == map[4][13])
						{
							map[playerMapY][playerMapX] = BLOCK3;
							map[3][27] = YUKA;
						}
					}
					if (map[4][27] != BLOCK4 || map[4][27] == BLOCK4)
					{
						if (map[4][27] == BLOCK4 && map[playerMapY][playerMapX] == map[4][15])
						{
							map[playerMapY][playerMapX] = BLOCK4;
							map[4][27] = YUKA;
						}
					}
					if (map[5][27] != BLOCK5 || map[5][27] == BLOCK5)
					{
						if (map[5][27] == BLOCK5 && map[playerMapY][playerMapX] == map[4][17])
						{
							map[playerMapY][playerMapX] = BLOCK5;
							map[5][27] = YUKA;
						}
					}
					if (map[6][27] != BLOCK6 || map[6][27] == BLOCK6)
					{

						if (map[6][27] == BLOCK6 && map[playerMapY][playerMapX] == /*6以降は後で*/map[4][9])
						{
							map[playerMapY][playerMapX] = BLOCK6;
							map[6][27] = YUKA;
						}
					}
					if (map[7][27] != BLOCK7 || map[7][27] == BLOCK7)
					{
						if (map[7][27] == BLOCK7 && map[playerMapY][playerMapX] == map[4][9])
						{
							map[playerMapY][playerMapX] = BLOCK7;
							map[7][27] = YUKA;
						}
					}
					if (map[8][27] != BLOCK8 || map[8][27] == BLOCK8)
					{
						if (map[8][27] == BLOCK8 && map[playerMapY][playerMapX] == map[4][9])
						{
							map[playerMapY][playerMapX] = BLOCK8;
							map[8][27] = YUKA;
						}
					}
					playerPosX -= playerSpeed;
				}

				if (map[playerMapY][playerMapX - 1] == BLOCK1)
				{
					map[1][27] = BLOCK1;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = TA;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK22)
				{
					map[2][27] = BLOCK22;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = TA;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK3)
				{
					map[3][27] = BLOCK3;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = TA;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK4)
				{
					map[4][27] = BLOCK4;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = TA;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK5)
				{
					map[5][27] = BLOCK5;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = TA;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK6)
				{
					map[6][27] = BLOCK6;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = TA;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK7)
				{
					map[7][27] = BLOCK7;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = TA;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK8)
				{
					map[8][27] = BLOCK8;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = TA;
					playerPosX -= playerSpeed;

				}
			}
			if (map[playerMapY][playerMapX] == CHI)
			{
				if (map[playerMapY][playerMapX - 1] == YUKA)
				{
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = CHI;
					if (map[1][27] != BLOCK1 || map[1][27] == BLOCK1)
					{
						if (map[1][27] == BLOCK1 && map[playerMapY][playerMapX] == map[4][9])
						{
							map[playerMapY][playerMapX] = BLOCK1;
							map[1][27] = YUKA;
						}
					}
					if (map[2][27] != BLOCK22 || map[2][27] == BLOCK22)
					{
						if (map[2][27] == BLOCK22 && map[playerMapY][playerMapX] == map[4][11])
						{
							map[playerMapY][playerMapX] = BLOCK22;
							map[2][27] = YUKA;
						}
					}
					if (map[3][27] != BLOCK3 || map[3][27] == BLOCK3)
					{
						if (map[3][27] == BLOCK3 && map[playerMapY][playerMapX] == map[4][13])
						{
							map[playerMapY][playerMapX] = BLOCK3;
							map[3][27] = YUKA;
						}
					}
					if (map[4][27] != BLOCK4 || map[4][27] == BLOCK4)
					{
						if (map[4][27] == BLOCK4 && map[playerMapY][playerMapX] == map[4][15])
						{
							map[playerMapY][playerMapX] = BLOCK4;
							map[4][27] = YUKA;
						}
					}
					if (map[5][27] != BLOCK5 || map[5][27] == BLOCK5)
					{
						if (map[5][27] == BLOCK5 && map[playerMapY][playerMapX] == map[4][17])
						{
							map[playerMapY][playerMapX] = BLOCK5;
							map[5][27] = YUKA;
						}
					}
					if (map[6][27] != BLOCK6 || map[6][27] == BLOCK6)
					{

						if (map[6][27] == BLOCK6 && map[playerMapY][playerMapX] == /*6以降は後で*/map[4][9])
						{
							map[playerMapY][playerMapX] = BLOCK6;
							map[6][27] = YUKA;
						}
					}
					if (map[7][27] != BLOCK7 || map[7][27] == BLOCK7)
					{
						if (map[7][27] == BLOCK7 && map[playerMapY][playerMapX] == map[4][9])
						{
							map[playerMapY][playerMapX] = BLOCK7;
							map[7][27] = YUKA;
						}
					}
					if (map[8][27] != BLOCK8 || map[8][27] == BLOCK8)
					{
						if (map[8][27] == BLOCK8 && map[playerMapY][playerMapX] == map[4][9])
						{
							map[playerMapY][playerMapX] = BLOCK8;
							map[8][27] = YUKA;
						}
					}
					playerPosX -= playerSpeed;
				}

				if (map[playerMapY][playerMapX - 1] == BLOCK1)
				{
					map[1][27] = BLOCK1;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = CHI;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK22)
				{
					map[2][27] = BLOCK22;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = CHI;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK3)
				{
					map[3][27] = BLOCK3;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = CHI;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK4)
				{
					map[4][27] = BLOCK4;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = CHI;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK5)
				{
					map[5][27] = BLOCK5;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = CHI;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK6)
				{
					map[6][27] = BLOCK6;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = CHI;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK7)
				{
					map[7][27] = BLOCK7;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = CHI;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK8)
				{
					map[8][27] = BLOCK8;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = CHI;
					playerPosX -= playerSpeed;

				}
			}

			if (map[playerMapY][playerMapX] == NU)
			{
				if (map[playerMapY][playerMapX - 1] == YUKA)
				{
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = NU;
					if (map[1][27] != BLOCK1 || map[1][27] == BLOCK1)
					{
						if (map[1][27] == BLOCK1 && map[playerMapY][playerMapX] == map[4][9])
						{
							map[playerMapY][playerMapX] = BLOCK1;
							map[1][27] = YUKA;
						}
					}
					if (map[2][27] != BLOCK22 || map[2][27] == BLOCK22)
					{
						if (map[2][27] == BLOCK22 && map[playerMapY][playerMapX] == map[4][11])
						{
							map[playerMapY][playerMapX] = BLOCK22;
							map[2][27] = YUKA;
						}
					}
					if (map[3][27] != BLOCK3 || map[3][27] == BLOCK3)
					{
						if (map[3][27] == BLOCK3 && map[playerMapY][playerMapX] == map[4][13])
						{
							map[playerMapY][playerMapX] = BLOCK3;
							map[3][27] = YUKA;
						}
					}
					if (map[4][27] != BLOCK4 || map[4][27] == BLOCK4)
					{
						if (map[4][27] == BLOCK4 && map[playerMapY][playerMapX] == map[4][15])
						{
							map[playerMapY][playerMapX] = BLOCK4;
							map[4][27] = YUKA;
						}
					}
					if (map[5][27] != BLOCK5 || map[5][27] == BLOCK5)
					{
						if (map[5][27] == BLOCK5 && map[playerMapY][playerMapX] == map[4][17])
						{
							map[playerMapY][playerMapX] = BLOCK5;
							map[5][27] = YUKA;
						}
					}
					if (map[6][27] != BLOCK6 || map[6][27] == BLOCK6)
					{

						if (map[6][27] == BLOCK6 && map[playerMapY][playerMapX] == /*6以降は後で*/map[4][9])
						{
							map[playerMapY][playerMapX] = BLOCK6;
							map[6][27] = YUKA;
						}
					}
					if (map[7][27] != BLOCK7 || map[7][27] == BLOCK7)
					{
						if (map[7][27] == BLOCK7 && map[playerMapY][playerMapX] == map[4][9])
						{
							map[playerMapY][playerMapX] = BLOCK7;
							map[7][27] = YUKA;
						}
					}
					if (map[8][27] != BLOCK8 || map[8][27] == BLOCK8)
					{
						if (map[8][27] == BLOCK8 && map[playerMapY][playerMapX] == map[4][9])
						{
							map[playerMapY][playerMapX] = BLOCK8;
							map[8][27] = YUKA;
						}
					}
					playerPosX -= playerSpeed;
				}

				if (map[playerMapY][playerMapX - 1] == BLOCK1)
				{
					map[1][27] = BLOCK1;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = NU;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK22)
				{
					map[2][27] = BLOCK22;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = NU;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK3)
				{
					map[3][27] = BLOCK3;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = NU;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK4)
				{
					map[4][27] = BLOCK4;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = NU;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK5)
				{
					map[5][27] = BLOCK5;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = NU;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK6)
				{
					map[6][27] = BLOCK6;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = NU;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK7)
				{
					map[7][27] = BLOCK7;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = NU;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK8)
				{
					map[8][27] = BLOCK8;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = NU;
					playerPosX -= playerSpeed;

				}
			}
			if (map[playerMapY][playerMapX] == NE)
			{
				if (map[playerMapY][playerMapX - 1] == YUKA)
				{
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = NE;
					if (map[1][27] != BLOCK1 || map[1][27] == BLOCK1)
					{
						if (map[1][27] == BLOCK1 && map[playerMapY][playerMapX] == map[4][9])
						{
							map[playerMapY][playerMapX] = BLOCK1;
							map[1][27] = YUKA;
						}
					}
					if (map[2][27] != BLOCK22 || map[2][27] == BLOCK22)
					{
						if (map[2][27] == BLOCK22 && map[playerMapY][playerMapX] == map[4][11])
						{
							map[playerMapY][playerMapX] = BLOCK22;
							map[2][27] = YUKA;
						}
					}
					if (map[3][27] != BLOCK3 || map[3][27] == BLOCK3)
					{
						if (map[3][27] == BLOCK3 && map[playerMapY][playerMapX] == map[4][13])
						{
							map[playerMapY][playerMapX] = BLOCK3;
							map[3][27] = YUKA;
						}
					}
					if (map[4][27] != BLOCK4 || map[4][27] == BLOCK4)
					{
						if (map[4][27] == BLOCK4 && map[playerMapY][playerMapX] == map[4][15])
						{
							map[playerMapY][playerMapX] = BLOCK4;
							map[4][27] = YUKA;
						}
					}
					if (map[5][27] != BLOCK5 || map[5][27] == BLOCK5)
					{
						if (map[5][27] == BLOCK5 && map[playerMapY][playerMapX] == map[4][17])
						{
							map[playerMapY][playerMapX] = BLOCK5;
							map[5][27] = YUKA;
						}
					}
					if (map[6][27] != BLOCK6 || map[6][27] == BLOCK6)
					{

						if (map[6][27] == BLOCK6 && map[playerMapY][playerMapX] == /*6以降は後で*/map[4][9])
						{
							map[playerMapY][playerMapX] = BLOCK6;
							map[6][27] = YUKA;
						}
					}
					if (map[7][27] != BLOCK7 || map[7][27] == BLOCK7)
					{
						if (map[7][27] == BLOCK7 && map[playerMapY][playerMapX] == map[4][9])
						{
							map[playerMapY][playerMapX] = BLOCK7;
							map[7][27] = YUKA;
						}
					}
					if (map[8][27] != BLOCK8 || map[8][27] == BLOCK8)
					{
						if (map[8][27] == BLOCK8 && map[playerMapY][playerMapX] == map[4][9])
						{
							map[playerMapY][playerMapX] = BLOCK8;
							map[8][27] = YUKA;
						}
					}
					playerPosX -= playerSpeed;
				}

				if (map[playerMapY][playerMapX - 1] == BLOCK1)
				{
					map[1][27] = BLOCK1;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = NE;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK22)
				{
					map[2][27] = BLOCK22;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = NE;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK3)
				{
					map[3][27] = BLOCK3;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = NE;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK4)
				{
					map[4][27] = BLOCK4;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = NE;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK5)
				{
					map[5][27] = BLOCK5;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = NE;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK6)
				{
					map[6][27] = BLOCK6;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = NE;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK7)
				{
					map[7][27] = BLOCK7;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = NE;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK8)
				{
					map[8][27] = BLOCK8;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = NE;
					playerPosX -= playerSpeed;

				}
			}
			if (map[playerMapY][playerMapX] == MA)
			{
				if (map[playerMapY][playerMapX - 1] == YUKA)
				{
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = MA;
					if (map[1][27] != BLOCK1 || map[1][27] == BLOCK1)
					{
						if (map[1][27] == BLOCK1 && map[playerMapY][playerMapX] == map[4][9])
						{
							map[playerMapY][playerMapX] = BLOCK1;
							map[1][27] = YUKA;
						}
					}
					if (map[2][27] != BLOCK22 || map[2][27] == BLOCK22)
					{
						if (map[2][27] == BLOCK22 && map[playerMapY][playerMapX] == map[4][11])
						{
							map[playerMapY][playerMapX] = BLOCK22;
							map[2][27] = YUKA;
						}
					}
					if (map[3][27] != BLOCK3 || map[3][27] == BLOCK3)
					{
						if (map[3][27] == BLOCK3 && map[playerMapY][playerMapX] == map[4][13])
						{
							map[playerMapY][playerMapX] = BLOCK3;
							map[3][27] = YUKA;
						}
					}
					if (map[4][27] != BLOCK4 || map[4][27] == BLOCK4)
					{
						if (map[4][27] == BLOCK4 && map[playerMapY][playerMapX] == map[4][15])
						{
							map[playerMapY][playerMapX] = BLOCK4;
							map[4][27] = YUKA;
						}
					}
					if (map[5][27] != BLOCK5 || map[5][27] == BLOCK5)
					{
						if (map[5][27] == BLOCK5 && map[playerMapY][playerMapX] == map[4][17])
						{
							map[playerMapY][playerMapX] = BLOCK5;
							map[5][27] = YUKA;
						}
					}
					if (map[6][27] != BLOCK6 || map[6][27] == BLOCK6)
					{

						if (map[6][27] == BLOCK6 && map[playerMapY][playerMapX] == /*6以降は後で*/map[4][9])
						{
							map[playerMapY][playerMapX] = BLOCK6;
							map[6][27] = YUKA;
						}
					}
					if (map[7][27] != BLOCK7 || map[7][27] == BLOCK7)
					{
						if (map[7][27] == BLOCK7 && map[playerMapY][playerMapX] == map[4][9])
						{
							map[playerMapY][playerMapX] = BLOCK7;
							map[7][27] = YUKA;
						}
					}
					if (map[8][27] != BLOCK8 || map[8][27] == BLOCK8)
					{
						if (map[8][27] == BLOCK8 && map[playerMapY][playerMapX] == map[4][9])
						{
							map[playerMapY][playerMapX] = BLOCK8;
							map[8][27] = YUKA;
						}
					}
					playerPosX -= playerSpeed;
				}

				if (map[playerMapY][playerMapX - 1] == BLOCK1)
				{
					map[1][27] = BLOCK1;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = MA;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK22)
				{
					map[2][27] = BLOCK22;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = MA;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK3)
				{
					map[3][27] = BLOCK3;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = MA;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK4)
				{
					map[4][27] = BLOCK4;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = MA;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK5)
				{
					map[5][27] = BLOCK5;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = MA;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK6)
				{
					map[6][27] = BLOCK6;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = MA;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK7)
				{
					map[7][27] = BLOCK7;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = MA;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK8)
				{
					map[8][27] = BLOCK8;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = MA;
					playerPosX -= playerSpeed;

				}
			}
			if (map[playerMapY][playerMapX] == YA)
			{
				if (map[playerMapY][playerMapX - 1] == YUKA)
				{
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = YA;
					if (map[1][27] != BLOCK1 || map[1][27] == BLOCK1)
					{
						if (map[1][27] == BLOCK1 && map[playerMapY][playerMapX] == map[4][9])
						{
							map[playerMapY][playerMapX] = BLOCK1;
							map[1][27] = YUKA;
						}
					}
					if (map[2][27] != BLOCK22 || map[2][27] == BLOCK22)
					{
						if (map[2][27] == BLOCK22 && map[playerMapY][playerMapX] == map[4][11])
						{
							map[playerMapY][playerMapX] = BLOCK22;
							map[2][27] = YUKA;
						}
					}
					if (map[3][27] != BLOCK3 || map[3][27] == BLOCK3)
					{
						if (map[3][27] == BLOCK3 && map[playerMapY][playerMapX] == map[4][13])
						{
							map[playerMapY][playerMapX] = BLOCK3;
							map[3][27] = YUKA;
						}
					}
					if (map[4][27] != BLOCK4 || map[4][27] == BLOCK4)
					{
						if (map[4][27] == BLOCK4 && map[playerMapY][playerMapX] == map[4][15])
						{
							map[playerMapY][playerMapX] = BLOCK4;
							map[4][27] = YUKA;
						}
					}
					if (map[5][27] != BLOCK5 || map[5][27] == BLOCK5)
					{
						if (map[5][27] == BLOCK5 && map[playerMapY][playerMapX] == map[4][17])
						{
							map[playerMapY][playerMapX] = BLOCK5;
							map[5][27] = YUKA;
						}
					}
					if (map[6][27] != BLOCK6 || map[6][27] == BLOCK6)
					{

						if (map[6][27] == BLOCK6 && map[playerMapY][playerMapX] == /*6以降は後で*/map[4][9])
						{
							map[playerMapY][playerMapX] = BLOCK6;
							map[6][27] = YUKA;
						}
					}
					if (map[7][27] != BLOCK7 || map[7][27] == BLOCK7)
					{
						if (map[7][27] == BLOCK7 && map[playerMapY][playerMapX] == map[4][9])
						{
							map[playerMapY][playerMapX] = BLOCK7;
							map[7][27] = YUKA;
						}
					}
					if (map[8][27] != BLOCK8 || map[8][27] == BLOCK8)
					{
						if (map[8][27] == BLOCK8 && map[playerMapY][playerMapX] == map[4][9])
						{
							map[playerMapY][playerMapX] = BLOCK8;
							map[8][27] = YUKA;
						}
					}
					playerPosX -= playerSpeed;
				}

				if (map[playerMapY][playerMapX - 1] == BLOCK1)
				{
					map[1][27] = BLOCK1;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = YA;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK22)
				{
					map[2][27] = BLOCK22;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = YA;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK3)
				{
					map[3][27] = BLOCK3;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = YA;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK4)
				{
					map[4][27] = BLOCK4;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = YA;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK5)
				{
					map[5][27] = BLOCK5;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = YA;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK6)
				{
					map[6][27] = BLOCK6;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = YA;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK7)
				{
					map[7][27] = BLOCK7;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = YA;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK8)
				{
					map[8][27] = BLOCK8;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = YA;
					playerPosX -= playerSpeed;

				}
			}
			if (map[playerMapY][playerMapX] == RI)
			{
				if (map[playerMapY][playerMapX - 1] == YUKA)
				{
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = RI;
					if (map[1][27] != BLOCK1 || map[1][27] == BLOCK1)
					{
						if (map[1][27] == BLOCK1 && map[playerMapY][playerMapX] == map[4][9])
						{
							map[playerMapY][playerMapX] = BLOCK1;
							map[1][27] = YUKA;
						}
					}
					if (map[2][27] != BLOCK22 || map[2][27] == BLOCK22)
					{
						if (map[2][27] == BLOCK22 && map[playerMapY][playerMapX] == map[4][11])
						{
							map[playerMapY][playerMapX] = BLOCK22;
							map[2][27] = YUKA;
						}
					}
					if (map[3][27] != BLOCK3 || map[3][27] == BLOCK3)
					{
						if (map[3][27] == BLOCK3 && map[playerMapY][playerMapX] == map[4][13])
						{
							map[playerMapY][playerMapX] = BLOCK3;
							map[3][27] = YUKA;
						}
					}
					if (map[4][27] != BLOCK4 || map[4][27] == BLOCK4)
					{
						if (map[4][27] == BLOCK4 && map[playerMapY][playerMapX] == map[4][15])
						{
							map[playerMapY][playerMapX] = BLOCK4;
							map[4][27] = YUKA;
						}
					}
					if (map[5][27] != BLOCK5 || map[5][27] == BLOCK5)
					{
						if (map[5][27] == BLOCK5 && map[playerMapY][playerMapX] == map[4][17])
						{
							map[playerMapY][playerMapX] = BLOCK5;
							map[5][27] = YUKA;
						}
					}
					if (map[6][27] != BLOCK6 || map[6][27] == BLOCK6)
					{

						if (map[6][27] == BLOCK6 && map[playerMapY][playerMapX] == /*6以降は後で*/map[4][9])
						{
							map[playerMapY][playerMapX] = BLOCK6;
							map[6][27] = YUKA;
						}
					}
					if (map[7][27] != BLOCK7 || map[7][27] == BLOCK7)
					{
						if (map[7][27] == BLOCK7 && map[playerMapY][playerMapX] == map[4][9])
						{
							map[playerMapY][playerMapX] = BLOCK7;
							map[7][27] = YUKA;
						}
					}
					if (map[8][27] != BLOCK8 || map[8][27] == BLOCK8)
					{
						if (map[8][27] == BLOCK8 && map[playerMapY][playerMapX] == map[4][9])
						{
							map[playerMapY][playerMapX] = BLOCK8;
							map[8][27] = YUKA;
						}
					}
					playerPosX -= playerSpeed;
				}

				if (map[playerMapY][playerMapX - 1] == BLOCK1)
				{
					map[1][27] = BLOCK1;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = RI;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK22)
				{
					map[2][27] = BLOCK22;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = RI;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK3)
				{
					map[3][27] = BLOCK3;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = RI;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK4)
				{
					map[4][27] = BLOCK4;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = RI;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK5)
				{
					map[5][27] = BLOCK5;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = RI;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK6)
				{
					map[6][27] = BLOCK6;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = RI;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK7)
				{
					map[7][27] = BLOCK7;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = RI;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK8)
				{
					map[8][27] = BLOCK8;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = RI;
					playerPosX -= playerSpeed;

				}
			}
			if (map[playerMapY][playerMapX] == RU)
			{
				if (map[playerMapY][playerMapX - 1] == YUKA)
				{
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = RU;
					if (map[1][27] != BLOCK1 || map[1][27] == BLOCK1)
					{
						if (map[1][27] == BLOCK1 && map[playerMapY][playerMapX] == map[4][9])
						{
							map[playerMapY][playerMapX] = BLOCK1;
							map[1][27] = YUKA;
						}
					}
					if (map[2][27] != BLOCK22 || map[2][27] == BLOCK22)
					{
						if (map[2][27] == BLOCK22 && map[playerMapY][playerMapX] == map[4][11])
						{
							map[playerMapY][playerMapX] = BLOCK22;
							map[2][27] = YUKA;
						}
					}
					if (map[3][27] != BLOCK3 || map[3][27] == BLOCK3)
					{
						if (map[3][27] == BLOCK3 && map[playerMapY][playerMapX] == map[4][13])
						{
							map[playerMapY][playerMapX] = BLOCK3;
							map[3][27] = YUKA;
						}
					}
					if (map[4][27] != BLOCK4 || map[4][27] == BLOCK4)
					{
						if (map[4][27] == BLOCK4 && map[playerMapY][playerMapX] == map[4][15])
						{
							map[playerMapY][playerMapX] = BLOCK4;
							map[4][27] = YUKA;
						}
					}
					if (map[5][27] != BLOCK5 || map[5][27] == BLOCK5)
					{
						if (map[5][27] == BLOCK5 && map[playerMapY][playerMapX] == map[4][17])
						{
							map[playerMapY][playerMapX] = BLOCK5;
							map[5][27] = YUKA;
						}
					}
					if (map[6][27] != BLOCK6 || map[6][27] == BLOCK6)
					{

						if (map[6][27] == BLOCK6 && map[playerMapY][playerMapX] == /*6以降は後で*/map[4][9])
						{
							map[playerMapY][playerMapX] = BLOCK6;
							map[6][27] = YUKA;
						}
					}
					if (map[7][27] != BLOCK7 || map[7][27] == BLOCK7)
					{
						if (map[7][27] == BLOCK7 && map[playerMapY][playerMapX] == map[4][9])
						{
							map[playerMapY][playerMapX] = BLOCK7;
							map[7][27] = YUKA;
						}
					}
					if (map[8][27] != BLOCK8 || map[8][27] == BLOCK8)
					{
						if (map[8][27] == BLOCK8 && map[playerMapY][playerMapX] == map[4][9])
						{
							map[playerMapY][playerMapX] = BLOCK8;
							map[8][27] = YUKA;
						}
					}
					playerPosX -= playerSpeed;
				}

				if (map[playerMapY][playerMapX - 1] == BLOCK1)
				{
					map[1][27] = BLOCK1;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = RU;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK22)
				{
					map[2][27] = BLOCK22;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = RU;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK3)
				{
					map[3][27] = BLOCK3;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = RU;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK4)
				{
					map[4][27] = BLOCK4;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = RU;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK5)
				{
					map[5][27] = BLOCK5;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = RU;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK6)
				{
					map[6][27] = BLOCK6;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = RU;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK7)
				{
					map[7][27] = BLOCK7;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = RU;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK8)
				{
					map[8][27] = BLOCK8;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = RU;
					playerPosX -= playerSpeed;

				}
			}
			if (map[playerMapY][playerMapX] == WA)
			{
				if (map[playerMapY][playerMapX - 1] == YUKA)
				{
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = WA;
					if (map[1][27] != BLOCK1 || map[1][27] == BLOCK1)
					{
						if (map[1][27] == BLOCK1 && map[playerMapY][playerMapX] == map[4][9])
						{
							map[playerMapY][playerMapX] = BLOCK1;
							map[1][27] = YUKA;
						}
					}
					if (map[2][27] != BLOCK22 || map[2][27] == BLOCK22)
					{
						if (map[2][27] == BLOCK22 && map[playerMapY][playerMapX] == map[4][11])
						{
							map[playerMapY][playerMapX] = BLOCK22;
							map[2][27] = YUKA;
						}
					}
					if (map[3][27] != BLOCK3 || map[3][27] == BLOCK3)
					{
						if (map[3][27] == BLOCK3 && map[playerMapY][playerMapX] == map[4][13])
						{
							map[playerMapY][playerMapX] = BLOCK3;
							map[3][27] = YUKA;
						}
					}
					if (map[4][27] != BLOCK4 || map[4][27] == BLOCK4)
					{
						if (map[4][27] == BLOCK4 && map[playerMapY][playerMapX] == map[4][15])
						{
							map[playerMapY][playerMapX] = BLOCK4;
							map[4][27] = YUKA;
						}
					}
					if (map[5][27] != BLOCK5 || map[5][27] == BLOCK5)
					{
						if (map[5][27] == BLOCK5 && map[playerMapY][playerMapX] == map[4][17])
						{
							map[playerMapY][playerMapX] = BLOCK5;
							map[5][27] = YUKA;
						}
					}
					if (map[6][27] != BLOCK6 || map[6][27] == BLOCK6)
					{

						if (map[6][27] == BLOCK6 && map[playerMapY][playerMapX] == /*6以降は後で*/map[4][9])
						{
							map[playerMapY][playerMapX] = BLOCK6;
							map[6][27] = YUKA;
						}
					}
					if (map[7][27] != BLOCK7 || map[7][27] == BLOCK7)
					{
						if (map[7][27] == BLOCK7 && map[playerMapY][playerMapX] == map[4][9])
						{
							map[playerMapY][playerMapX] = BLOCK7;
							map[7][27] = YUKA;
						}
					}
					if (map[8][27] != BLOCK8 || map[8][27] == BLOCK8)
					{
						if (map[8][27] == BLOCK8 && map[playerMapY][playerMapX] == map[4][9])
						{
							map[playerMapY][playerMapX] = BLOCK8;
							map[8][27] = YUKA;
						}
					}
					playerPosX -= playerSpeed;
				}

				if (map[playerMapY][playerMapX - 1] == BLOCK1)
				{
					map[1][27] = BLOCK1;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = WA;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK22)
				{
					map[2][27] = BLOCK22;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = WA;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK3)
				{
					map[3][27] = BLOCK3;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = WA;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK4)
				{
					map[4][27] = BLOCK4;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = WA;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK5)
				{
					map[5][27] = BLOCK5;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = WA;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK6)
				{
					map[6][27] = BLOCK6;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = WA;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK7)
				{
					map[7][27] = BLOCK7;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = WA;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK8)
				{
					map[8][27] = BLOCK8;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = WA;
					playerPosX -= playerSpeed;

				}
			}
			if (map[playerMapY][playerMapX] == NN)
			{
				if (map[playerMapY][playerMapX - 1] == YUKA)
				{
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = NN;
					if (map[1][27] != BLOCK1 || map[1][27] == BLOCK1)
					{
						if (map[1][27] == BLOCK1 && map[playerMapY][playerMapX] == map[4][9])
						{
							map[playerMapY][playerMapX] = BLOCK1;
							map[1][27] = YUKA;
						}
					}
					if (map[2][27] != BLOCK22 || map[2][27] == BLOCK22)
					{
						if (map[2][27] == BLOCK22 && map[playerMapY][playerMapX] == map[4][11])
						{
							map[playerMapY][playerMapX] = BLOCK22;
							map[2][27] = YUKA;
						}
					}
					if (map[3][27] != BLOCK3 || map[3][27] == BLOCK3)
					{
						if (map[3][27] == BLOCK3 && map[playerMapY][playerMapX] == map[4][13])
						{
							map[playerMapY][playerMapX] = BLOCK3;
							map[3][27] = YUKA;
						}
					}
					if (map[4][27] != BLOCK4 || map[4][27] == BLOCK4)
					{
						if (map[4][27] == BLOCK4 && map[playerMapY][playerMapX] == map[4][15])
						{
							map[playerMapY][playerMapX] = BLOCK4;
							map[4][27] = YUKA;
						}
					}
					if (map[5][27] != BLOCK5 || map[5][27] == BLOCK5)
					{
						if (map[5][27] == BLOCK5 && map[playerMapY][playerMapX] == map[4][17])
						{
							map[playerMapY][playerMapX] = BLOCK5;
							map[5][27] = YUKA;
						}
					}
					if (map[6][27] != BLOCK6 || map[6][27] == BLOCK6)
					{

						if (map[6][27] == BLOCK6 && map[playerMapY][playerMapX] == /*6以降は後で*/map[4][9])
						{
							map[playerMapY][playerMapX] = BLOCK6;
							map[6][27] = YUKA;
						}
					}
					if (map[7][27] != BLOCK7 || map[7][27] == BLOCK7)
					{
						if (map[7][27] == BLOCK7 && map[playerMapY][playerMapX] == map[4][9])
						{
							map[playerMapY][playerMapX] = BLOCK7;
							map[7][27] = YUKA;
						}
					}
					if (map[8][27] != BLOCK8 || map[8][27] == BLOCK8)
					{
						if (map[8][27] == BLOCK8 && map[playerMapY][playerMapX] == map[4][9])
						{
							map[playerMapY][playerMapX] = BLOCK8;
							map[8][27] = YUKA;
						}
					}
					playerPosX -= playerSpeed;
				}

				if (map[playerMapY][playerMapX - 1] == BLOCK1)
				{
					map[1][27] = BLOCK1;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = NN;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK22)
				{
					map[2][27] = BLOCK22;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = NN;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK3)
				{
					map[3][27] = BLOCK3;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = NN;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK4)
				{
					map[4][27] = BLOCK4;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = NN;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK5)
				{
					map[5][27] = BLOCK5;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = NN;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK6)
				{
					map[6][27] = BLOCK6;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = NN;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK7)
				{
					map[7][27] = BLOCK7;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = NN;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK8)
				{
					map[8][27] = BLOCK8;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = NN;
					playerPosX -= playerSpeed;

				}
			}
			if (map[playerMapY][playerMapX] == GI)
			{
				if (map[playerMapY][playerMapX - 1] == YUKA)
				{
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = GI;
					if (map[1][27] != BLOCK1 || map[1][27] == BLOCK1)
					{
						if (map[1][27] == BLOCK1 && map[playerMapY][playerMapX] == map[4][9])
						{
							map[playerMapY][playerMapX] = BLOCK1;
							map[1][27] = YUKA;
						}
					}
					if (map[2][27] != BLOCK22 || map[2][27] == BLOCK22)
					{
						if (map[2][27] == BLOCK22 && map[playerMapY][playerMapX] == map[4][11])
						{
							map[playerMapY][playerMapX] = BLOCK22;
							map[2][27] = YUKA;
						}
					}
					if (map[3][27] != BLOCK3 || map[3][27] == BLOCK3)
					{
						if (map[3][27] == BLOCK3 && map[playerMapY][playerMapX] == map[4][13])
						{
							map[playerMapY][playerMapX] = BLOCK3;
							map[3][27] = YUKA;
						}
					}
					if (map[4][27] != BLOCK4 || map[4][27] == BLOCK4)
					{
						if (map[4][27] == BLOCK4 && map[playerMapY][playerMapX] == map[4][15])
						{
							map[playerMapY][playerMapX] = BLOCK4;
							map[4][27] = YUKA;
						}
					}
					if (map[5][27] != BLOCK5 || map[5][27] == BLOCK5)
					{
						if (map[5][27] == BLOCK5 && map[playerMapY][playerMapX] == map[4][17])
						{
							map[playerMapY][playerMapX] = BLOCK5;
							map[5][27] = YUKA;
						}
					}
					if (map[6][27] != BLOCK6 || map[6][27] == BLOCK6)
					{

						if (map[6][27] == BLOCK6 && map[playerMapY][playerMapX] == /*6以降は後で*/map[4][9])
						{
							map[playerMapY][playerMapX] = BLOCK6;
							map[6][27] = YUKA;
						}
					}
					if (map[7][27] != BLOCK7 || map[7][27] == BLOCK7)
					{
						if (map[7][27] == BLOCK7 && map[playerMapY][playerMapX] == map[4][9])
						{
							map[playerMapY][playerMapX] = BLOCK7;
							map[7][27] = YUKA;
						}
					}
					if (map[8][27] != BLOCK8 || map[8][27] == BLOCK8)
					{
						if (map[8][27] == BLOCK8 && map[playerMapY][playerMapX] == map[4][9])
						{
							map[playerMapY][playerMapX] = BLOCK8;
							map[8][27] = YUKA;
						}
					}
					playerPosX -= playerSpeed;
				}

				if (map[playerMapY][playerMapX - 1] == BLOCK1)
				{
					map[1][27] = BLOCK1;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = GI;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK22)
				{
					map[2][27] = BLOCK22;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = GI;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK3)
				{
					map[3][27] = BLOCK3;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = GI;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK4)
				{
					map[4][27] = BLOCK4;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = GI;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK5)
				{
					map[5][27] = BLOCK5;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = GI;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK6)
				{
					map[6][27] = BLOCK6;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = GI;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK7)
				{
					map[7][27] = BLOCK7;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = GI;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK8)
				{
					map[8][27] = BLOCK8;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = GI;
					playerPosX -= playerSpeed;

				}
			}
			if (map[playerMapY][playerMapX] == ZO)
			{
				if (map[playerMapY][playerMapX - 1] == YUKA)
				{
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = ZO;
					if (map[1][27] != BLOCK1 || map[1][27] == BLOCK1)
					{
						if (map[1][27] == BLOCK1 && map[playerMapY][playerMapX] == map[4][9])
						{
							map[playerMapY][playerMapX] = BLOCK1;
							map[1][27] = YUKA;
						}
					}
					if (map[2][27] != BLOCK22 || map[2][27] == BLOCK22)
					{
						if (map[2][27] == BLOCK22 && map[playerMapY][playerMapX] == map[4][11])
						{
							map[playerMapY][playerMapX] = BLOCK22;
							map[2][27] = YUKA;
						}
					}
					if (map[3][27] != BLOCK3 || map[3][27] == BLOCK3)
					{
						if (map[3][27] == BLOCK3 && map[playerMapY][playerMapX] == map[4][13])
						{
							map[playerMapY][playerMapX] = BLOCK3;
							map[3][27] = YUKA;
						}
					}
					if (map[4][27] != BLOCK4 || map[4][27] == BLOCK4)
					{
						if (map[4][27] == BLOCK4 && map[playerMapY][playerMapX] == map[4][15])
						{
							map[playerMapY][playerMapX] = BLOCK4;
							map[4][27] = YUKA;
						}
					}
					if (map[5][27] != BLOCK5 || map[5][27] == BLOCK5)
					{
						if (map[5][27] == BLOCK5 && map[playerMapY][playerMapX] == map[4][17])
						{
							map[playerMapY][playerMapX] = BLOCK5;
							map[5][27] = YUKA;
						}
					}
					if (map[6][27] != BLOCK6 || map[6][27] == BLOCK6)
					{

						if (map[6][27] == BLOCK6 && map[playerMapY][playerMapX] == /*6以降は後で*/map[4][9])
						{
							map[playerMapY][playerMapX] = BLOCK6;
							map[6][27] = YUKA;
						}
					}
					if (map[7][27] != BLOCK7 || map[7][27] == BLOCK7)
					{
						if (map[7][27] == BLOCK7 && map[playerMapY][playerMapX] == map[4][9])
						{
							map[playerMapY][playerMapX] = BLOCK7;
							map[7][27] = YUKA;
						}
					}
					if (map[8][27] != BLOCK8 || map[8][27] == BLOCK8)
					{
						if (map[8][27] == BLOCK8 && map[playerMapY][playerMapX] == map[4][9])
						{
							map[playerMapY][playerMapX] = BLOCK8;
							map[8][27] = YUKA;
						}
					}
					playerPosX -= playerSpeed;
				}
				if (map[playerMapY][playerMapX - 1] == BLOCK1)
				{
					map[1][27] = BLOCK1;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = ZO;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK22)
				{
					map[2][27] = BLOCK22;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = ZO;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK3)
				{
					map[3][27] = BLOCK3;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = ZO;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK4)
				{
					map[4][27] = BLOCK4;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = ZO;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK5)
				{
					map[5][27] = BLOCK5;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = ZO;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK6)
				{
					map[6][27] = BLOCK6;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = ZO;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK7)
				{
					map[7][27] = BLOCK7;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = ZO;
					playerPosX -= playerSpeed;

				}
				if (map[playerMapY][playerMapX - 1] == BLOCK8)
				{
					map[8][27] = BLOCK8;
					map[playerMapY][playerMapX] = YUKA;
					map[playerMapY][playerMapX - 1] = ZO;
					playerPosX -= playerSpeed;

				}
			}


			if (keys[DIK_D] && preKeys[DIK_D] == 0 || keys[DIK_RIGHT] && preKeys[DIK_RIGHT] == 0)
			{
				playerTmpX = playerPosX + playerSpeed;
				playerMapX = playerTmpX / KBlockSize;
				//何もないから実際に進ませる
				if (map[playerMapY][playerMapX] == YUKA)
				{
					playerPosX += playerSpeed;
				}
				if (map[playerMapY][playerMapX] == GOAL)
				{
					playerPosX += playerSpeed;
				}
				if (map[playerMapY][playerMapX] == THORN)
				{
					playerPosX += playerSpeed;
				}

				if (map[playerMapY][playerMapX] == I)
				{
					if (map[playerMapY][playerMapX + 1] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = I;
						if (map[1][27] != BLOCK1 || map[1][27] == BLOCK1)
						{
							if (map[1][27] == BLOCK1 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK1;
								map[1][27] = YUKA;
							}
						}
						if (map[2][27] != BLOCK22 || map[2][27] == BLOCK22)
						{
							if (map[2][27] == BLOCK22 && map[playerMapY][playerMapX] == map[4][11])
							{
								map[playerMapY][playerMapX] = BLOCK22;
								map[2][27] = YUKA;
							}
						}
						if (map[3][27] != BLOCK3 || map[3][27] == BLOCK3)
						{
							if (map[3][27] == BLOCK3 && map[playerMapY][playerMapX] == map[4][13])
							{
								map[playerMapY][playerMapX] = BLOCK3;
								map[3][27] = YUKA;
							}
						}
						if (map[4][27] != BLOCK4 || map[4][27] == BLOCK4)
						{
							if (map[4][27] == BLOCK4 && map[playerMapY][playerMapX] == map[4][15])
							{
								map[playerMapY][playerMapX] = BLOCK4;
								map[4][27] = YUKA;
							}
						}
						if (map[5][27] != BLOCK5 || map[5][27] == BLOCK5)
						{
							if (map[5][27] == BLOCK5 && map[playerMapY][playerMapX] == map[4][17])
							{
								map[playerMapY][playerMapX] = BLOCK5;
								map[5][27] = YUKA;
							}
						}
						if (map[6][27] != BLOCK6 || map[6][27] == BLOCK6)
						{

							if (map[6][27] == BLOCK6 && map[playerMapY][playerMapX] == /*6以降は後で*/map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK6;
								map[6][27] = YUKA;
							}
						}
						if (map[7][27] != BLOCK7 || map[7][27] == BLOCK7)
						{
							if (map[7][27] == BLOCK7 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK7;
								map[7][27] = YUKA;
							}
						}
						if (map[8][27] != BLOCK8 || map[8][27] == BLOCK8)
						{
							if (map[8][27] == BLOCK8 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK8;
								map[8][27] = YUKA;
							}
						}
						playerPosX += playerSpeed;
					}

					if (map[playerMapY][playerMapX + 1] == BLOCK1)
					{
						map[1][27] = BLOCK1;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = I;
						playerPosX += playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK22)
					{
						map[2][27] = BLOCK22;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = I;
						playerPosX += playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK3)
					{
						map[3][27] = BLOCK3;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = I;
						playerPosX += playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK4)
					{
						map[4][27] = BLOCK4;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = I;
						playerPosX += playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK5)
					{
						map[5][27] = BLOCK5;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = I;
						playerPosX += playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK6)
					{
						map[6][27] = BLOCK6;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = I;
						playerPosX += playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK7)
					{
						map[7][27] = BLOCK7;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = I;
						playerPosX = playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK8)
					{
						map[8][27] = BLOCK8;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = I;
						playerPosX += playerSpeed;

					}



				}

				// 1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111
				// ここから直して
				if (map[playerMapY][playerMapX] == U)
				{
					if (map[playerMapY][playerMapX + 1] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = U; //ここをUに変える　したも同じ
						if (map[1][27] != BLOCK1 || map[1][27] == BLOCK1)
						{
							if (map[1][27] == BLOCK1 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK1;
								map[1][27] = YUKA;
							}
						}
						if (map[2][27] != BLOCK22 || map[2][27] == BLOCK22)
						{
							if (map[2][27] == BLOCK22 && map[playerMapY][playerMapX] == map[4][11])
							{
								map[playerMapY][playerMapX] = BLOCK22;
								map[2][27] = YUKA;
							}
						}
						if (map[3][27] != BLOCK3 || map[3][27] == BLOCK3)
						{
							if (map[3][27] == BLOCK3 && map[playerMapY][playerMapX] == map[4][13])
							{
								map[playerMapY][playerMapX] = BLOCK3;
								map[3][27] = YUKA;
							}
						}
						if (map[4][27] != BLOCK4 || map[4][27] == BLOCK4)
						{
							if (map[4][27] == BLOCK4 && map[playerMapY][playerMapX] == map[4][15])
							{
								map[playerMapY][playerMapX] = BLOCK4;
								map[4][27] = YUKA;
							}
						}
						if (map[5][27] != BLOCK5 || map[5][27] == BLOCK5)
						{
							if (map[5][27] == BLOCK5 && map[playerMapY][playerMapX] == map[4][17])
							{
								map[playerMapY][playerMapX] = BLOCK5;
								map[5][27] = YUKA;
							}
						}
						if (map[6][27] != BLOCK6 || map[6][27] == BLOCK6)
						{

							if (map[6][27] == BLOCK6 && map[playerMapY][playerMapX] == /*6以降は後で*/map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK6;
								map[6][27] = YUKA;
							}
						}
						if (map[7][27] != BLOCK7 || map[7][27] == BLOCK7)
						{
							if (map[7][27] == BLOCK7 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK7;
								map[7][27] = YUKA;
							}
						}
						if (map[8][27] != BLOCK8 || map[8][27] == BLOCK8)
						{
							if (map[8][27] == BLOCK8 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK8;
								map[8][27] = YUKA;
							}
						}
						playerPosX += playerSpeed;
					}

					if (map[playerMapY][playerMapX + 1] == BLOCK1)
					{
						map[1][27] = BLOCK1;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = U;
						playerPosX += playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK22)
					{
						map[2][27] = BLOCK22;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = U;
						playerPosX += playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK3)
					{
						map[3][27] = BLOCK3;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = U;
						playerPosX += playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK4)
					{
						map[4][27] = BLOCK4;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = U;
						playerPosX += playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK5)
					{
						map[5][27] = BLOCK5;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = U;
						playerPosX += playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK6)
					{
						map[6][27] = BLOCK6;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = U;
						playerPosX += playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK7)
					{
						map[7][27] = BLOCK7;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = U;
						playerPosX = playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK8)
					{
						map[8][27] = BLOCK8;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = U;
						playerPosX += playerSpeed;

					}
				}
				if (map[playerMapY][playerMapX] == E)
				{
					if (map[playerMapY][playerMapX + 1] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = E;
						if (map[1][27] != BLOCK1 || map[1][27] == BLOCK1)
						{
							if (map[1][27] == BLOCK1 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK1;
								map[1][27] = YUKA;
							}
						}
						if (map[2][27] != BLOCK22 || map[2][27] == BLOCK22)
						{
							if (map[2][27] == BLOCK22 && map[playerMapY][playerMapX] == map[4][11])
							{
								map[playerMapY][playerMapX] = BLOCK22;
								map[2][27] = YUKA;
							}
						}
						if (map[3][27] != BLOCK3 || map[3][27] == BLOCK3)
						{
							if (map[3][27] == BLOCK3 && map[playerMapY][playerMapX] == map[4][13])
							{
								map[playerMapY][playerMapX] = BLOCK3;
								map[3][27] = YUKA;
							}
						}
						if (map[4][27] != BLOCK4 || map[4][27] == BLOCK4)
						{
							if (map[4][27] == BLOCK4 && map[playerMapY][playerMapX] == map[4][15])
							{
								map[playerMapY][playerMapX] = BLOCK4;
								map[4][27] = YUKA;
							}
						}
						if (map[5][27] != BLOCK5 || map[5][27] == BLOCK5)
						{
							if (map[5][27] == BLOCK5 && map[playerMapY][playerMapX] == map[4][17])
							{
								map[playerMapY][playerMapX] = BLOCK5;
								map[5][27] = YUKA;
							}
						}
						if (map[6][27] != BLOCK6 || map[6][27] == BLOCK6)
						{

							if (map[6][27] == BLOCK6 && map[playerMapY][playerMapX] == /*6以降は後で*/map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK6;
								map[6][27] = YUKA;
							}
						}
						if (map[7][27] != BLOCK7 || map[7][27] == BLOCK7)
						{
							if (map[7][27] == BLOCK7 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK7;
								map[7][27] = YUKA;
							}
						}
						if (map[8][27] != BLOCK8 || map[8][27] == BLOCK8)
						{
							if (map[8][27] == BLOCK8 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK8;
								map[8][27] = YUKA;
							}
						}
						playerPosX += playerSpeed;
					}
					if (map[playerMapY][playerMapX + 1] == BLOCK1)
					{
						map[1][27] = BLOCK1;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = E;
						playerPosX += playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK22)
					{
						map[2][27] = BLOCK22;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = E;
						playerPosX += playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK3)
					{
						map[3][27] = BLOCK3;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = E;
						playerPosX += playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK4)
					{
						map[4][27] = BLOCK4;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = E;
						playerPosX += playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK5)
					{
						map[5][27] = BLOCK5;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = E;
						playerPosX += playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK6)
					{
						map[6][27] = BLOCK6;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = E;
						playerPosX += playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK7)
					{
						map[7][27] = BLOCK7;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = E;
						playerPosX = playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK8)
					{
						map[8][27] = BLOCK8;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = E;
						playerPosX += playerSpeed;

					}
				}
				if (map[playerMapY][playerMapX] == KA)
				{
					if (map[playerMapY][playerMapX + 1] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = KA;
						if (map[1][27] != BLOCK1 || map[1][27] == BLOCK1)
						{
							if (map[1][27] == BLOCK1 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK1;
								map[1][27] = YUKA;
							}
						}
						if (map[2][27] != BLOCK22 || map[2][27] == BLOCK22)
						{
							if (map[2][27] == BLOCK22 && map[playerMapY][playerMapX] == map[4][11])
							{
								map[playerMapY][playerMapX] = BLOCK22;
								map[2][27] = YUKA;
							}
						}
						if (map[3][27] != BLOCK3 || map[3][27] == BLOCK3)
						{
							if (map[3][27] == BLOCK3 && map[playerMapY][playerMapX] == map[4][13])
							{
								map[playerMapY][playerMapX] = BLOCK3;
								map[3][27] = YUKA;
							}
						}
						if (map[4][27] != BLOCK4 || map[4][27] == BLOCK4)
						{
							if (map[4][27] == BLOCK4 && map[playerMapY][playerMapX] == map[4][15])
							{
								map[playerMapY][playerMapX] = BLOCK4;
								map[4][27] = YUKA;
							}
						}
						if (map[5][27] != BLOCK5 || map[5][27] == BLOCK5)
						{
							if (map[5][27] == BLOCK5 && map[playerMapY][playerMapX] == map[4][17])
							{
								map[playerMapY][playerMapX] = BLOCK5;
								map[5][27] = YUKA;
							}
						}
						if (map[6][27] != BLOCK6 || map[6][27] == BLOCK6)
						{

							if (map[6][27] == BLOCK6 && map[playerMapY][playerMapX] == /*6以降は後で*/map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK6;
								map[6][27] = YUKA;
							}
						}
						if (map[7][27] != BLOCK7 || map[7][27] == BLOCK7)
						{
							if (map[7][27] == BLOCK7 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK7;
								map[7][27] = YUKA;
							}
						}
						if (map[8][27] != BLOCK8 || map[8][27] == BLOCK8)
						{
							if (map[8][27] == BLOCK8 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK8;
								map[8][27] = YUKA;
							}
						}
						playerPosX += playerSpeed;
					}

					if (map[playerMapY][playerMapX + 1] == BLOCK1)
					{
						map[1][27] = BLOCK1;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = KA;
						playerPosX += playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK22)
					{
						map[2][27] = BLOCK22;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = KA;
						playerPosX += playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK3)
					{
						map[3][27] = BLOCK3;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = KA;
						playerPosX += playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK4)
					{
						map[4][27] = BLOCK4;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = KA;
						playerPosX += playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK5)
					{
						map[5][27] = BLOCK5;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = KA;
						playerPosX += playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK6)
					{
						map[6][27] = BLOCK6;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = KA;
						playerPosX += playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK7)
					{
						map[7][27] = BLOCK7;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = KA;
						playerPosX = playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK8)
					{
						map[8][27] = BLOCK8;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = KA;
						playerPosX += playerSpeed;

					}
				}
				if (map[playerMapY][playerMapX] == KU)
				{
					if (map[playerMapY][playerMapX + 1] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = KU;
						if (map[1][27] != BLOCK1 || map[1][27] == BLOCK1)
						{
							if (map[1][27] == BLOCK1 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK1;
								map[1][27] = YUKA;
							}
						}
						if (map[2][27] != BLOCK22 || map[2][27] == BLOCK22)
						{
							if (map[2][27] == BLOCK22 && map[playerMapY][playerMapX] == map[4][11])
							{
								map[playerMapY][playerMapX] = BLOCK22;
								map[2][27] = YUKA;
							}
						}
						if (map[3][27] != BLOCK3 || map[3][27] == BLOCK3)
						{
							if (map[3][27] == BLOCK3 && map[playerMapY][playerMapX] == map[4][13])
							{
								map[playerMapY][playerMapX] = BLOCK3;
								map[3][27] = YUKA;
							}
						}
						if (map[4][27] != BLOCK4 || map[4][27] == BLOCK4)
						{
							if (map[4][27] == BLOCK4 && map[playerMapY][playerMapX] == map[4][15])
							{
								map[playerMapY][playerMapX] = BLOCK4;
								map[4][27] = YUKA;
							}
						}
						if (map[5][27] != BLOCK5 || map[5][27] == BLOCK5)
						{
							if (map[5][27] == BLOCK5 && map[playerMapY][playerMapX] == map[4][17])
							{
								map[playerMapY][playerMapX] = BLOCK5;
								map[5][27] = YUKA;
							}
						}
						if (map[6][27] != BLOCK6 || map[6][27] == BLOCK6)
						{

							if (map[6][27] == BLOCK6 && map[playerMapY][playerMapX] == /*6以降は後で*/map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK6;
								map[6][27] = YUKA;
							}
						}
						if (map[7][27] != BLOCK7 || map[7][27] == BLOCK7)
						{
							if (map[7][27] == BLOCK7 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK7;
								map[7][27] = YUKA;
							}
						}
						if (map[8][27] != BLOCK8 || map[8][27] == BLOCK8)
						{
							if (map[8][27] == BLOCK8 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK8;
								map[8][27] = YUKA;
							}
						}
						playerPosX += playerSpeed;
					}

					if (map[playerMapY][playerMapX + 1] == BLOCK1)
					{
						map[1][27] = BLOCK1;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = KU;
						playerPosX += playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK22)
					{
						map[2][27] = BLOCK22;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = KU;
						playerPosX += playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK3)
					{
						map[3][27] = BLOCK3;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = KU;
						playerPosX += playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK4)
					{
						map[4][27] = BLOCK4;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = KU;
						playerPosX += playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK5)
					{
						map[5][27] = BLOCK5;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = KU;
						playerPosX += playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK6)
					{
						map[6][27] = BLOCK6;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = KU;
						playerPosX += playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK7)
					{
						map[7][27] = BLOCK7;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = KU;
						playerPosX = playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK8)
					{
						map[8][27] = BLOCK8;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = KU;
						playerPosX += playerSpeed;

					}
				}
				if (map[playerMapY][playerMapX] == KO)
				{
					if (map[playerMapY][playerMapX + 1] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = KO;
						if (map[1][27] != BLOCK1 || map[1][27] == BLOCK1)
						{
							if (map[1][27] == BLOCK1 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK1;
								map[1][27] = YUKA;
							}
						}
						if (map[2][27] != BLOCK22 || map[2][27] == BLOCK22)
						{
							if (map[2][27] == BLOCK22 && map[playerMapY][playerMapX] == map[4][11])
							{
								map[playerMapY][playerMapX] = BLOCK22;
								map[2][27] = YUKA;
							}
						}
						if (map[3][27] != BLOCK3 || map[3][27] == BLOCK3)
						{
							if (map[3][27] == BLOCK3 && map[playerMapY][playerMapX] == map[4][13])
							{
								map[playerMapY][playerMapX] = BLOCK3;
								map[3][27] = YUKA;
							}
						}
						if (map[4][27] != BLOCK4 || map[4][27] == BLOCK4)
						{
							if (map[4][27] == BLOCK4 && map[playerMapY][playerMapX] == map[4][15])
							{
								map[playerMapY][playerMapX] = BLOCK4;
								map[4][27] = YUKA;
							}
						}
						if (map[5][27] != BLOCK5 || map[5][27] == BLOCK5)
						{
							if (map[5][27] == BLOCK5 && map[playerMapY][playerMapX] == map[4][17])
							{
								map[playerMapY][playerMapX] = BLOCK5;
								map[5][27] = YUKA;
							}
						}
						if (map[6][27] != BLOCK6 || map[6][27] == BLOCK6)
						{

							if (map[6][27] == BLOCK6 && map[playerMapY][playerMapX] == /*6以降は後で*/map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK6;
								map[6][27] = YUKA;
							}
						}
						if (map[7][27] != BLOCK7 || map[7][27] == BLOCK7)
						{
							if (map[7][27] == BLOCK7 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK7;
								map[7][27] = YUKA;
							}
						}
						if (map[8][27] != BLOCK8 || map[8][27] == BLOCK8)
						{
							if (map[8][27] == BLOCK8 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK8;
								map[8][27] = YUKA;
							}
						}
						playerPosX += playerSpeed;
					}

					if (map[playerMapY][playerMapX + 1] == BLOCK1)
					{
						map[1][27] = BLOCK1;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = KO;
						playerPosX += playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK22)
					{
						map[2][27] = BLOCK22;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = KO;
						playerPosX += playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK3)
					{
						map[3][27] = BLOCK3;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = KO;
						playerPosX += playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK4)
					{
						map[4][27] = BLOCK4;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = KO;
						playerPosX += playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK5)
					{
						map[5][27] = BLOCK5;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = KO;
						playerPosX += playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK6)
					{
						map[6][27] = BLOCK6;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = KO;
						playerPosX += playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK7)
					{
						map[7][27] = BLOCK7;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = KO;
						playerPosX = playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK8)
					{
						map[8][27] = BLOCK8;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = KO;
						playerPosX += playerSpeed;

					}
				}
				if (map[playerMapY][playerMapX] == SA)
				{
					if (map[playerMapY][playerMapX + 1] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = SA;
						if (map[1][27] != BLOCK1 || map[1][27] == BLOCK1)
						{
							if (map[1][27] == BLOCK1 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK1;
								map[1][27] = YUKA;
							}
						}
						if (map[2][27] != BLOCK22 || map[2][27] == BLOCK22)
						{
							if (map[2][27] == BLOCK22 && map[playerMapY][playerMapX] == map[4][11])
							{
								map[playerMapY][playerMapX] = BLOCK22;
								map[2][27] = YUKA;
							}
						}
						if (map[3][27] != BLOCK3 || map[3][27] == BLOCK3)
						{
							if (map[3][27] == BLOCK3 && map[playerMapY][playerMapX] == map[4][13])
							{
								map[playerMapY][playerMapX] = BLOCK3;
								map[3][27] = YUKA;
							}
						}
						if (map[4][27] != BLOCK4 || map[4][27] == BLOCK4)
						{
							if (map[4][27] == BLOCK4 && map[playerMapY][playerMapX] == map[4][15])
							{
								map[playerMapY][playerMapX] = BLOCK4;
								map[4][27] = YUKA;
							}
						}
						if (map[5][27] != BLOCK5 || map[5][27] == BLOCK5)
						{
							if (map[5][27] == BLOCK5 && map[playerMapY][playerMapX] == map[4][17])
							{
								map[playerMapY][playerMapX] = BLOCK5;
								map[5][27] = YUKA;
							}
						}
						if (map[6][27] != BLOCK6 || map[6][27] == BLOCK6)
						{

							if (map[6][27] == BLOCK6 && map[playerMapY][playerMapX] == /*6以降は後で*/map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK6;
								map[6][27] = YUKA;
							}
						}
						if (map[7][27] != BLOCK7 || map[7][27] == BLOCK7)
						{
							if (map[7][27] == BLOCK7 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK7;
								map[7][27] = YUKA;
							}
						}
						if (map[8][27] != BLOCK8 || map[8][27] == BLOCK8)
						{
							if (map[8][27] == BLOCK8 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK8;
								map[8][27] = YUKA;
							}
						}
						playerPosX += playerSpeed;
					}
					if (map[playerMapY][playerMapX + 1] == BLOCK1)
					{
						map[1][27] = BLOCK1;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = SA;
						playerPosX += playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK22)
					{
						map[2][27] = BLOCK22;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = SA;
						playerPosX += playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK3)
					{
						map[3][27] = BLOCK3;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = SA;
						playerPosX += playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK4)
					{
						map[4][27] = BLOCK4;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = SA;
						playerPosX += playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK5)
					{
						map[5][27] = BLOCK5;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = SA;
						playerPosX += playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK6)
					{
						map[6][27] = BLOCK6;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = SA;
						playerPosX += playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK7)
					{
						map[7][27] = BLOCK7;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = SA;
						playerPosX = playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK8)
					{
						map[8][27] = BLOCK8;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = SA;
						playerPosX += playerSpeed;

					}
				}
				if (map[playerMapY][playerMapX] == SU)
				{
					if (map[playerMapY][playerMapX + 1] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = SU;
						if (map[1][27] != BLOCK1 || map[1][27] == BLOCK1)
						{
							if (map[1][27] == BLOCK1 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK1;
								map[1][27] = YUKA;
							}
						}
						if (map[2][27] != BLOCK22 || map[2][27] == BLOCK22)
						{
							if (map[2][27] == BLOCK22 && map[playerMapY][playerMapX] == map[4][11])
							{
								map[playerMapY][playerMapX] = BLOCK22;
								map[2][27] = YUKA;
							}
						}
						if (map[3][27] != BLOCK3 || map[3][27] == BLOCK3)
						{
							if (map[3][27] == BLOCK3 && map[playerMapY][playerMapX] == map[4][13])
							{
								map[playerMapY][playerMapX] = BLOCK3;
								map[3][27] = YUKA;
							}
						}
						if (map[4][27] != BLOCK4 || map[4][27] == BLOCK4)
						{
							if (map[4][27] == BLOCK4 && map[playerMapY][playerMapX] == map[4][15])
							{
								map[playerMapY][playerMapX] = BLOCK4;
								map[4][27] = YUKA;
							}
						}
						if (map[5][27] != BLOCK5 || map[5][27] == BLOCK5)
						{
							if (map[5][27] == BLOCK5 && map[playerMapY][playerMapX] == map[4][17])
							{
								map[playerMapY][playerMapX] = BLOCK5;
								map[5][27] = YUKA;
							}
						}
						if (map[6][27] != BLOCK6 || map[6][27] == BLOCK6)
						{

							if (map[6][27] == BLOCK6 && map[playerMapY][playerMapX] == /*6以降は後で*/map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK6;
								map[6][27] = YUKA;
							}
						}
						if (map[7][27] != BLOCK7 || map[7][27] == BLOCK7)
						{
							if (map[7][27] == BLOCK7 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK7;
								map[7][27] = YUKA;
							}
						}
						if (map[8][27] != BLOCK8 || map[8][27] == BLOCK8)
						{
							if (map[8][27] == BLOCK8 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK8;
								map[8][27] = YUKA;
							}
						}
						playerPosX += playerSpeed;
					}
					if (map[playerMapY][playerMapX + 1] == BLOCK1)
					{
						map[1][27] = BLOCK1;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = SU;
						playerPosX += playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK22)
					{
						map[2][27] = BLOCK22;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = SU;
						playerPosX += playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK3)
					{
						map[3][27] = BLOCK3;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = SU;
						playerPosX += playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK4)
					{
						map[4][27] = BLOCK4;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = SU;
						playerPosX += playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK5)
					{
						map[5][27] = BLOCK5;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = SU;
						playerPosX += playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK6)
					{
						map[6][27] = BLOCK6;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = SU;
						playerPosX += playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK7)
					{
						map[7][27] = BLOCK7;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = SU;
						playerPosX = playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK8)
					{
						map[8][27] = BLOCK8;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = SU;
						playerPosX += playerSpeed;

					}
				}
				if (map[playerMapY][playerMapX] == SO)
				{
					if (map[playerMapY][playerMapX + 1] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = SO;
						if (map[1][27] != BLOCK1 || map[1][27] == BLOCK1)
						{
							if (map[1][27] == BLOCK1 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK1;
								map[1][27] = YUKA;
							}
						}
						if (map[2][27] != BLOCK22 || map[2][27] == BLOCK22)
						{
							if (map[2][27] == BLOCK22 && map[playerMapY][playerMapX] == map[4][11])
							{
								map[playerMapY][playerMapX] = BLOCK22;
								map[2][27] = YUKA;
							}
						}
						if (map[3][27] != BLOCK3 || map[3][27] == BLOCK3)
						{
							if (map[3][27] == BLOCK3 && map[playerMapY][playerMapX] == map[4][13])
							{
								map[playerMapY][playerMapX] = BLOCK3;
								map[3][27] = YUKA;
							}
						}
						if (map[4][27] != BLOCK4 || map[4][27] == BLOCK4)
						{
							if (map[4][27] == BLOCK4 && map[playerMapY][playerMapX] == map[4][15])
							{
								map[playerMapY][playerMapX] = BLOCK4;
								map[4][27] = YUKA;
							}
						}
						if (map[5][27] != BLOCK5 || map[5][27] == BLOCK5)
						{
							if (map[5][27] == BLOCK5 && map[playerMapY][playerMapX] == map[4][17])
							{
								map[playerMapY][playerMapX] = BLOCK5;
								map[5][27] = YUKA;
							}
						}
						if (map[6][27] != BLOCK6 || map[6][27] == BLOCK6)
						{

							if (map[6][27] == BLOCK6 && map[playerMapY][playerMapX] == /*6以降は後で*/map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK6;
								map[6][27] = YUKA;
							}
						}
						if (map[7][27] != BLOCK7 || map[7][27] == BLOCK7)
						{
							if (map[7][27] == BLOCK7 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK7;
								map[7][27] = YUKA;
							}
						}
						if (map[8][27] != BLOCK8 || map[8][27] == BLOCK8)
						{
							if (map[8][27] == BLOCK8 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK8;
								map[8][27] = YUKA;
							}
						}
						playerPosX += playerSpeed;
					}

					if (map[playerMapY][playerMapX + 1] == BLOCK1)
					{
						map[1][27] = BLOCK1;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = SO;
						playerPosX += playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK22)
					{
						map[2][27] = BLOCK22;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = SO;
						playerPosX += playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK3)
					{
						map[3][27] = BLOCK3;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = SO;
						playerPosX += playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK4)
					{
						map[4][27] = BLOCK4;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = SO;
						playerPosX += playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK5)
					{
						map[5][27] = BLOCK5;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = SO;
						playerPosX += playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK6)
					{
						map[6][27] = BLOCK6;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = SO;
						playerPosX += playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK7)
					{
						map[7][27] = BLOCK7;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = SO;
						playerPosX = playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK8)
					{
						map[8][27] = BLOCK8;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = SO;
						playerPosX += playerSpeed;

					}
				}
				if (map[playerMapY][playerMapX] == TA)
				{
					if (map[playerMapY][playerMapX + 1] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = TA;
						if (map[1][27] != BLOCK1 || map[1][27] == BLOCK1)
						{
							if (map[1][27] == BLOCK1 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK1;
								map[1][27] = YUKA;
							}
						}
						if (map[2][27] != BLOCK22 || map[2][27] == BLOCK22)
						{
							if (map[2][27] == BLOCK22 && map[playerMapY][playerMapX] == map[4][11])
							{
								map[playerMapY][playerMapX] = BLOCK22;
								map[2][27] = YUKA;
							}
						}
						if (map[3][27] != BLOCK3 || map[3][27] == BLOCK3)
						{
							if (map[3][27] == BLOCK3 && map[playerMapY][playerMapX] == map[4][13])
							{
								map[playerMapY][playerMapX] = BLOCK3;
								map[3][27] = YUKA;
							}
						}
						if (map[4][27] != BLOCK4 || map[4][27] == BLOCK4)
						{
							if (map[4][27] == BLOCK4 && map[playerMapY][playerMapX] == map[4][15])
							{
								map[playerMapY][playerMapX] = BLOCK4;
								map[4][27] = YUKA;
							}
						}
						if (map[5][27] != BLOCK5 || map[5][27] == BLOCK5)
						{
							if (map[5][27] == BLOCK5 && map[playerMapY][playerMapX] == map[4][17])
							{
								map[playerMapY][playerMapX] = BLOCK5;
								map[5][27] = YUKA;
							}
						}
						if (map[6][27] != BLOCK6 || map[6][27] == BLOCK6)
						{

							if (map[6][27] == BLOCK6 && map[playerMapY][playerMapX] == /*6以降は後で*/map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK6;
								map[6][27] = YUKA;
							}
						}
						if (map[7][27] != BLOCK7 || map[7][27] == BLOCK7)
						{
							if (map[7][27] == BLOCK7 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK7;
								map[7][27] = YUKA;
							}
						}
						if (map[8][27] != BLOCK8 || map[8][27] == BLOCK8)
						{
							if (map[8][27] == BLOCK8 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK8;
								map[8][27] = YUKA;
							}
						}
						playerPosX += playerSpeed;
					}
					if (map[playerMapY][playerMapX + 1] == BLOCK1)
					{
						map[1][27] = BLOCK1;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = TA;
						playerPosX += playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK22)
					{
						map[2][27] = BLOCK22;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = TA;
						playerPosX += playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK3)
					{
						map[3][27] = BLOCK3;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = TA;
						playerPosX += playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK4)
					{
						map[4][27] = BLOCK4;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = TA;
						playerPosX += playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK5)
					{
						map[5][27] = BLOCK5;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = TA;
						playerPosX += playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK6)
					{
						map[6][27] = BLOCK6;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = TA;
						playerPosX += playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK7)
					{
						map[7][27] = BLOCK7;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = TA;
						playerPosX = playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK8)
					{
						map[8][27] = BLOCK8;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = TA;
						playerPosX += playerSpeed;

					}
				}
				if (map[playerMapY][playerMapX] == CHI)
				{
					if (map[playerMapY][playerMapX + 1] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = CHI;
						if (map[1][27] != BLOCK1 || map[1][27] == BLOCK1)
						{
							if (map[1][27] == BLOCK1 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK1;
								map[1][27] = YUKA;
							}
						}
						if (map[2][27] != BLOCK22 || map[2][27] == BLOCK22)
						{
							if (map[2][27] == BLOCK22 && map[playerMapY][playerMapX] == map[4][11])
							{
								map[playerMapY][playerMapX] = BLOCK22;
								map[2][27] = YUKA;
							}
						}
						if (map[3][27] != BLOCK3 || map[3][27] == BLOCK3)
						{
							if (map[3][27] == BLOCK3 && map[playerMapY][playerMapX] == map[4][13])
							{
								map[playerMapY][playerMapX] = BLOCK3;
								map[3][27] = YUKA;
							}
						}
						if (map[4][27] != BLOCK4 || map[4][27] == BLOCK4)
						{
							if (map[4][27] == BLOCK4 && map[playerMapY][playerMapX] == map[4][15])
							{
								map[playerMapY][playerMapX] = BLOCK4;
								map[4][27] = YUKA;
							}
						}
						if (map[5][27] != BLOCK5 || map[5][27] == BLOCK5)
						{
							if (map[5][27] == BLOCK5 && map[playerMapY][playerMapX] == map[4][17])
							{
								map[playerMapY][playerMapX] = BLOCK5;
								map[5][27] = YUKA;
							}
						}
						if (map[6][27] != BLOCK6 || map[6][27] == BLOCK6)
						{

							if (map[6][27] == BLOCK6 && map[playerMapY][playerMapX] == /*6以降は後で*/map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK6;
								map[6][27] = YUKA;
							}
						}
						if (map[7][27] != BLOCK7 || map[7][27] == BLOCK7)
						{
							if (map[7][27] == BLOCK7 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK7;
								map[7][27] = YUKA;
							}
						}
						if (map[8][27] != BLOCK8 || map[8][27] == BLOCK8)
						{
							if (map[8][27] == BLOCK8 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK8;
								map[8][27] = YUKA;
							}
						}
						playerPosX += playerSpeed;
					}

					if (map[playerMapY][playerMapX + 1] == BLOCK1)
					{
						map[1][27] = BLOCK1;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = CHI;
						playerPosX += playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK22)
					{
						map[2][27] = BLOCK22;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = CHI;
						playerPosX += playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK3)
					{
						map[3][27] = BLOCK3;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = CHI;
						playerPosX += playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK4)
					{
						map[4][27] = BLOCK4;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = CHI;
						playerPosX += playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK5)
					{
						map[5][27] = BLOCK5;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = CHI;
						playerPosX += playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK6)
					{
						map[6][27] = BLOCK6;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = CHI;
						playerPosX += playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK7)
					{
						map[7][27] = BLOCK7;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = CHI;
						playerPosX = playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK8)
					{
						map[8][27] = BLOCK8;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = CHI;
						playerPosX += playerSpeed;

					}
				}

				if (map[playerMapY][playerMapX] == NU)
				{
					if (map[playerMapY][playerMapX + 1] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = NU;
						if (map[1][27] != BLOCK1 || map[1][27] == BLOCK1)
						{
							if (map[1][27] == BLOCK1 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK1;
								map[1][27] = YUKA;
							}
						}
						if (map[2][27] != BLOCK22 || map[2][27] == BLOCK22)
						{
							if (map[2][27] == BLOCK22 && map[playerMapY][playerMapX] == map[4][11])
							{
								map[playerMapY][playerMapX] = BLOCK22;
								map[2][27] = YUKA;
							}
						}
						if (map[3][27] != BLOCK3 || map[3][27] == BLOCK3)
						{
							if (map[3][27] == BLOCK3 && map[playerMapY][playerMapX] == map[4][13])
							{
								map[playerMapY][playerMapX] = BLOCK3;
								map[3][27] = YUKA;
							}
						}
						if (map[4][27] != BLOCK4 || map[4][27] == BLOCK4)
						{
							if (map[4][27] == BLOCK4 && map[playerMapY][playerMapX] == map[4][15])
							{
								map[playerMapY][playerMapX] = BLOCK4;
								map[4][27] = YUKA;
							}
						}
						if (map[5][27] != BLOCK5 || map[5][27] == BLOCK5)
						{
							if (map[5][27] == BLOCK5 && map[playerMapY][playerMapX] == map[4][17])
							{
								map[playerMapY][playerMapX] = BLOCK5;
								map[5][27] = YUKA;
							}
						}
						if (map[6][27] != BLOCK6 || map[6][27] == BLOCK6)
						{

							if (map[6][27] == BLOCK6 && map[playerMapY][playerMapX] == /*6以降は後で*/map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK6;
								map[6][27] = YUKA;
							}
						}
						if (map[7][27] != BLOCK7 || map[7][27] == BLOCK7)
						{
							if (map[7][27] == BLOCK7 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK7;
								map[7][27] = YUKA;
							}
						}
						if (map[8][27] != BLOCK8 || map[8][27] == BLOCK8)
						{
							if (map[8][27] == BLOCK8 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK8;
								map[8][27] = YUKA;
							}
						}
						playerPosX += playerSpeed;
					}
					if (map[playerMapY][playerMapX + 1] == BLOCK1)
					{
						map[1][27] = BLOCK1;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = NU;
						playerPosX += playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK22)
					{
						map[2][27] = BLOCK22;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = NU;
						playerPosX += playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK3)
					{
						map[3][27] = BLOCK3;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = NU;
						playerPosX += playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK4)
					{
						map[4][27] = BLOCK4;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = NU;
						playerPosX += playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK5)
					{
						map[5][27] = BLOCK5;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = NU;
						playerPosX += playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK6)
					{
						map[6][27] = BLOCK6;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = NU;
						playerPosX += playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK7)
					{
						map[7][27] = BLOCK7;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = NU;
						playerPosX = playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK8)
					{
						map[8][27] = BLOCK8;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = NU;
						playerPosX += playerSpeed;

					}
				}
				if (map[playerMapY][playerMapX] == NE)
				{
					if (map[playerMapY][playerMapX + 1] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = NE;
						if (map[1][27] != BLOCK1 || map[1][27] == BLOCK1)
						{
							if (map[1][27] == BLOCK1 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK1;
								map[1][27] = YUKA;
							}
						}
						if (map[2][27] != BLOCK22 || map[2][27] == BLOCK22)
						{
							if (map[2][27] == BLOCK22 && map[playerMapY][playerMapX] == map[4][11])
							{
								map[playerMapY][playerMapX] = BLOCK22;
								map[2][27] = YUKA;
							}
						}
						if (map[3][27] != BLOCK3 || map[3][27] == BLOCK3)
						{
							if (map[3][27] == BLOCK3 && map[playerMapY][playerMapX] == map[4][13])
							{
								map[playerMapY][playerMapX] = BLOCK3;
								map[3][27] = YUKA;
							}
						}
						if (map[4][27] != BLOCK4 || map[4][27] == BLOCK4)
						{
							if (map[4][27] == BLOCK4 && map[playerMapY][playerMapX] == map[4][15])
							{
								map[playerMapY][playerMapX] = BLOCK4;
								map[4][27] = YUKA;
							}
						}
						if (map[5][27] != BLOCK5 || map[5][27] == BLOCK5)
						{
							if (map[5][27] == BLOCK5 && map[playerMapY][playerMapX] == map[4][17])
							{
								map[playerMapY][playerMapX] = BLOCK5;
								map[5][27] = YUKA;
							}
						}
						if (map[6][27] != BLOCK6 || map[6][27] == BLOCK6)
						{

							if (map[6][27] == BLOCK6 && map[playerMapY][playerMapX] == /*6以降は後で*/map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK6;
								map[6][27] = YUKA;
							}
						}
						if (map[7][27] != BLOCK7 || map[7][27] == BLOCK7)
						{
							if (map[7][27] == BLOCK7 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK7;
								map[7][27] = YUKA;
							}
						}
						if (map[8][27] != BLOCK8 || map[8][27] == BLOCK8)
						{
							if (map[8][27] == BLOCK8 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK8;
								map[8][27] = YUKA;
							}
						}
						playerPosX += playerSpeed;
					}

					if (map[playerMapY][playerMapX + 1] == BLOCK1)
					{
						map[1][27] = BLOCK1;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = NE;
						playerPosX += playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK22)
					{
						map[2][27] = BLOCK22;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = NE;
						playerPosX += playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK3)
					{
						map[3][27] = BLOCK3;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = NE;
						playerPosX += playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK4)
					{
						map[4][27] = BLOCK4;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = NE;
						playerPosX += playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK5)
					{
						map[5][27] = BLOCK5;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = NE;
						playerPosX += playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK6)
					{
						map[6][27] = BLOCK6;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = NE;
						playerPosX += playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK7)
					{
						map[7][27] = BLOCK7;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = NE;
						playerPosX = playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK8)
					{
						map[8][27] = BLOCK8;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = NE;
						playerPosX += playerSpeed;

					}
				}
				if (map[playerMapY][playerMapX] == MA)
				{
					if (map[playerMapY][playerMapX + 1] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = MA;
						if (map[1][27] != BLOCK1 || map[1][27] == BLOCK1)
						{
							if (map[1][27] == BLOCK1 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK1;
								map[1][27] = YUKA;
							}
						}
						if (map[2][27] != BLOCK22 || map[2][27] == BLOCK22)
						{
							if (map[2][27] == BLOCK22 && map[playerMapY][playerMapX] == map[4][11])
							{
								map[playerMapY][playerMapX] = BLOCK22;
								map[2][27] = YUKA;
							}
						}
						if (map[3][27] != BLOCK3 || map[3][27] == BLOCK3)
						{
							if (map[3][27] == BLOCK3 && map[playerMapY][playerMapX] == map[4][13])
							{
								map[playerMapY][playerMapX] = BLOCK3;
								map[3][27] = YUKA;
							}
						}
						if (map[4][27] != BLOCK4 || map[4][27] == BLOCK4)
						{
							if (map[4][27] == BLOCK4 && map[playerMapY][playerMapX] == map[4][15])
							{
								map[playerMapY][playerMapX] = BLOCK4;
								map[4][27] = YUKA;
							}
						}
						if (map[5][27] != BLOCK5 || map[5][27] == BLOCK5)
						{
							if (map[5][27] == BLOCK5 && map[playerMapY][playerMapX] == map[4][17])
							{
								map[playerMapY][playerMapX] = BLOCK5;
								map[5][27] = YUKA;
							}
						}
						if (map[6][27] != BLOCK6 || map[6][27] == BLOCK6)
						{

							if (map[6][27] == BLOCK6 && map[playerMapY][playerMapX] == /*6以降は後で*/map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK6;
								map[6][27] = YUKA;
							}
						}
						if (map[7][27] != BLOCK7 || map[7][27] == BLOCK7)
						{
							if (map[7][27] == BLOCK7 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK7;
								map[7][27] = YUKA;
							}
						}
						if (map[8][27] != BLOCK8 || map[8][27] == BLOCK8)
						{
							if (map[8][27] == BLOCK8 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK8;
								map[8][27] = YUKA;
							}
						}
						playerPosX += playerSpeed;
					}

					if (map[playerMapY][playerMapX + 1] == BLOCK1)
					{
						map[1][27] = BLOCK1;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = MA;
						playerPosX += playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK22)
					{
						map[2][27] = BLOCK22;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = MA;
						playerPosX += playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK3)
					{
						map[3][27] = BLOCK3;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = MA;
						playerPosX += playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK4)
					{
						map[4][27] = BLOCK4;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = MA;
						playerPosX += playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK5)
					{
						map[5][27] = BLOCK5;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = MA;
						playerPosX += playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK6)
					{
						map[6][27] = BLOCK6;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = MA;
						playerPosX += playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK7)
					{
						map[7][27] = BLOCK7;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = MA;
						playerPosX = playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK8)
					{
						map[8][27] = BLOCK8;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = MA;
						playerPosX += playerSpeed;

					}
				}
				if (map[playerMapY][playerMapX] == YA)
				{
					if (map[playerMapY][playerMapX + 1] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = YA;
						if (map[1][27] != BLOCK1 || map[1][27] == BLOCK1)
						{
							if (map[1][27] == BLOCK1 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK1;
								map[1][27] = YUKA;
							}
						}
						if (map[2][27] != BLOCK22 || map[2][27] == BLOCK22)
						{
							if (map[2][27] == BLOCK22 && map[playerMapY][playerMapX] == map[4][11])
							{
								map[playerMapY][playerMapX] = BLOCK22;
								map[2][27] = YUKA;
							}
						}
						if (map[3][27] != BLOCK3 || map[3][27] == BLOCK3)
						{
							if (map[3][27] == BLOCK3 && map[playerMapY][playerMapX] == map[4][13])
							{
								map[playerMapY][playerMapX] = BLOCK3;
								map[3][27] = YUKA;
							}
						}
						if (map[4][27] != BLOCK4 || map[4][27] == BLOCK4)
						{
							if (map[4][27] == BLOCK4 && map[playerMapY][playerMapX] == map[4][15])
							{
								map[playerMapY][playerMapX] = BLOCK4;
								map[4][27] = YUKA;
							}
						}
						if (map[5][27] != BLOCK5 || map[5][27] == BLOCK5)
						{
							if (map[5][27] == BLOCK5 && map[playerMapY][playerMapX] == map[4][17])
							{
								map[playerMapY][playerMapX] = BLOCK5;
								map[5][27] = YUKA;
							}
						}
						if (map[6][27] != BLOCK6 || map[6][27] == BLOCK6)
						{

							if (map[6][27] == BLOCK6 && map[playerMapY][playerMapX] == /*6以降は後で*/map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK6;
								map[6][27] = YUKA;
							}
						}
						if (map[7][27] != BLOCK7 || map[7][27] == BLOCK7)
						{
							if (map[7][27] == BLOCK7 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK7;
								map[7][27] = YUKA;
							}
						}
						if (map[8][27] != BLOCK8 || map[8][27] == BLOCK8)
						{
							if (map[8][27] == BLOCK8 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK8;
								map[8][27] = YUKA;
							}
						}
						playerPosX += playerSpeed;
					}

					if (map[playerMapY][playerMapX + 1] == BLOCK1)
					{
						map[1][27] = BLOCK1;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = YA;
						playerPosX += playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK22)
					{
						map[2][27] = BLOCK22;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = YA;
						playerPosX += playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK3)
					{
						map[3][27] = BLOCK3;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = YA;
						playerPosX += playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK4)
					{
						map[4][27] = BLOCK4;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = YA;
						playerPosX += playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK5)
					{
						map[5][27] = BLOCK5;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = YA;
						playerPosX += playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK6)
					{
						map[6][27] = BLOCK6;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = YA;
						playerPosX += playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK7)
					{
						map[7][27] = BLOCK7;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = YA;
						playerPosX = playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK8)
					{
						map[8][27] = BLOCK8;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = YA;
						playerPosX += playerSpeed;

					}
				}
				if (map[playerMapY][playerMapX] == RI)
				{
					if (map[playerMapY][playerMapX + 1] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = RI;
						if (map[1][27] != BLOCK1 || map[1][27] == BLOCK1)
						{
							if (map[1][27] == BLOCK1 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK1;
								map[1][27] = YUKA;
							}
						}
						if (map[2][27] != BLOCK22 || map[2][27] == BLOCK22)
						{
							if (map[2][27] == BLOCK22 && map[playerMapY][playerMapX] == map[4][11])
							{
								map[playerMapY][playerMapX] = BLOCK22;
								map[2][27] = YUKA;
							}
						}
						if (map[3][27] != BLOCK3 || map[3][27] == BLOCK3)
						{
							if (map[3][27] == BLOCK3 && map[playerMapY][playerMapX] == map[4][13])
							{
								map[playerMapY][playerMapX] = BLOCK3;
								map[3][27] = YUKA;
							}
						}
						if (map[4][27] != BLOCK4 || map[4][27] == BLOCK4)
						{
							if (map[4][27] == BLOCK4 && map[playerMapY][playerMapX] == map[4][15])
							{
								map[playerMapY][playerMapX] = BLOCK4;
								map[4][27] = YUKA;
							}
						}
						if (map[5][27] != BLOCK5 || map[5][27] == BLOCK5)
						{
							if (map[5][27] == BLOCK5 && map[playerMapY][playerMapX] == map[4][17])
							{
								map[playerMapY][playerMapX] = BLOCK5;
								map[5][27] = YUKA;
							}
						}
						if (map[6][27] != BLOCK6 || map[6][27] == BLOCK6)
						{

							if (map[6][27] == BLOCK6 && map[playerMapY][playerMapX] == /*6以降は後で*/map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK6;
								map[6][27] = YUKA;
							}
						}
						if (map[7][27] != BLOCK7 || map[7][27] == BLOCK7)
						{
							if (map[7][27] == BLOCK7 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK7;
								map[7][27] = YUKA;
							}
						}
						if (map[8][27] != BLOCK8 || map[8][27] == BLOCK8)
						{
							if (map[8][27] == BLOCK8 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK8;
								map[8][27] = YUKA;
							}
						}
						playerPosX += playerSpeed;
					}

					if (map[playerMapY][playerMapX + 1] == BLOCK1)
					{
						map[1][27] = BLOCK1;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = RI;
						playerPosX += playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK22)
					{
						map[2][27] = BLOCK22;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = RI;
						playerPosX += playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK3)
					{
						map[3][27] = BLOCK3;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = RI;
						playerPosX += playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK4)
					{
						map[4][27] = BLOCK4;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = RI;
						playerPosX += playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK5)
					{
						map[5][27] = BLOCK5;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = RI;
						playerPosX += playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK6)
					{
						map[6][27] = BLOCK6;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = RI;
						playerPosX += playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK7)
					{
						map[7][27] = BLOCK7;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = RI;
						playerPosX = playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK8)
					{
						map[8][27] = BLOCK8;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = I;
						playerPosX += playerSpeed;

					}
				}
				if (map[playerMapY][playerMapX] == RU)
				{
					if (map[playerMapY][playerMapX + 1] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = RU;
						if (map[1][27] != BLOCK1 || map[1][27] == BLOCK1)
						{
							if (map[1][27] == BLOCK1 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK1;
								map[1][27] = YUKA;
							}
						}
						if (map[2][27] != BLOCK22 || map[2][27] == BLOCK22)
						{
							if (map[2][27] == BLOCK22 && map[playerMapY][playerMapX] == map[4][11])
							{
								map[playerMapY][playerMapX] = BLOCK22;
								map[2][27] = YUKA;
							}
						}
						if (map[3][27] != BLOCK3 || map[3][27] == BLOCK3)
						{
							if (map[3][27] == BLOCK3 && map[playerMapY][playerMapX] == map[4][13])
							{
								map[playerMapY][playerMapX] = BLOCK3;
								map[3][27] = YUKA;
							}
						}
						if (map[4][27] != BLOCK4 || map[4][27] == BLOCK4)
						{
							if (map[4][27] == BLOCK4 && map[playerMapY][playerMapX] == map[4][15])
							{
								map[playerMapY][playerMapX] = BLOCK4;
								map[4][27] = YUKA;
							}
						}
						if (map[5][27] != BLOCK5 || map[5][27] == BLOCK5)
						{
							if (map[5][27] == BLOCK5 && map[playerMapY][playerMapX] == map[4][17])
							{
								map[playerMapY][playerMapX] = BLOCK5;
								map[5][27] = YUKA;
							}
						}
						if (map[6][27] != BLOCK6 || map[6][27] == BLOCK6)
						{

							if (map[6][27] == BLOCK6 && map[playerMapY][playerMapX] == /*6以降は後で*/map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK6;
								map[6][27] = YUKA;
							}
						}
						if (map[7][27] != BLOCK7 || map[7][27] == BLOCK7)
						{
							if (map[7][27] == BLOCK7 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK7;
								map[7][27] = YUKA;
							}
						}
						if (map[8][27] != BLOCK8 || map[8][27] == BLOCK8)
						{
							if (map[8][27] == BLOCK8 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK8;
								map[8][27] = YUKA;
							}
						}
						playerPosX += playerSpeed;
					}

					if (map[playerMapY][playerMapX + 1] == BLOCK1)
					{
						map[1][27] = BLOCK1;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = RU;
						playerPosX += playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK22)
					{
						map[2][27] = BLOCK22;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = RU;
						playerPosX += playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK3)
					{
						map[3][27] = BLOCK3;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = RU;
						playerPosX += playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK4)
					{
						map[4][27] = BLOCK4;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = RU;
						playerPosX += playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK5)
					{
						map[5][27] = BLOCK5;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = RU;
						playerPosX += playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK6)
					{
						map[6][27] = BLOCK6;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = RU;
						playerPosX += playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK7)
					{
						map[7][27] = BLOCK7;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = RU;
						playerPosX = playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK8)
					{
						map[8][27] = BLOCK8;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = RU;
						playerPosX += playerSpeed;

					}
				}
				if (map[playerMapY][playerMapX] == WA)
				{
					if (map[playerMapY][playerMapX + 1] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = WA;
						if (map[1][27] != BLOCK1 || map[1][27] == BLOCK1)
						{
							if (map[1][27] == BLOCK1 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK1;
								map[1][27] = YUKA;
							}
						}
						if (map[2][27] != BLOCK22 || map[2][27] == BLOCK22)
						{
							if (map[2][27] == BLOCK22 && map[playerMapY][playerMapX] == map[4][11])
							{
								map[playerMapY][playerMapX] = BLOCK22;
								map[2][27] = YUKA;
							}
						}
						if (map[3][27] != BLOCK3 || map[3][27] == BLOCK3)
						{
							if (map[3][27] == BLOCK3 && map[playerMapY][playerMapX] == map[4][13])
							{
								map[playerMapY][playerMapX] = BLOCK3;
								map[3][27] = YUKA;
							}
						}
						if (map[4][27] != BLOCK4 || map[4][27] == BLOCK4)
						{
							if (map[4][27] == BLOCK4 && map[playerMapY][playerMapX] == map[4][15])
							{
								map[playerMapY][playerMapX] = BLOCK4;
								map[4][27] = YUKA;
							}
						}
						if (map[5][27] != BLOCK5 || map[5][27] == BLOCK5)
						{
							if (map[5][27] == BLOCK5 && map[playerMapY][playerMapX] == map[4][17])
							{
								map[playerMapY][playerMapX] = BLOCK5;
								map[5][27] = YUKA;
							}
						}
						if (map[6][27] != BLOCK6 || map[6][27] == BLOCK6)
						{

							if (map[6][27] == BLOCK6 && map[playerMapY][playerMapX] == /*6以降は後で*/map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK6;
								map[6][27] = YUKA;
							}
						}
						if (map[7][27] != BLOCK7 || map[7][27] == BLOCK7)
						{
							if (map[7][27] == BLOCK7 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK7;
								map[7][27] = YUKA;
							}
						}
						if (map[8][27] != BLOCK8 || map[8][27] == BLOCK8)
						{
							if (map[8][27] == BLOCK8 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK8;
								map[8][27] = YUKA;
							}
						}
						playerPosX += playerSpeed;
					}
					if (map[playerMapY][playerMapX + 1] == BLOCK1)
					{
						map[1][27] = BLOCK1;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = WA;
						playerPosX += playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK22)
					{
						map[2][27] = BLOCK22;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = WA;
						playerPosX += playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK3)
					{
						map[3][27] = BLOCK3;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = WA;
						playerPosX += playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK4)
					{
						map[4][27] = BLOCK4;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = WA;
						playerPosX += playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK5)
					{
						map[5][27] = BLOCK5;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = WA;
						playerPosX += playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK6)
					{
						map[6][27] = BLOCK6;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = WA;
						playerPosX += playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK7)
					{
						map[7][27] = BLOCK7;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = WA;
						playerPosX = playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK8)
					{
						map[8][27] = BLOCK8;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = I;
						playerPosX += playerSpeed;

					}
				}
				if (map[playerMapY][playerMapX] == NN)
				{
					if (map[playerMapY][playerMapX + 1] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = NN;
						if (map[1][27] != BLOCK1 || map[1][27] == BLOCK1)
						{
							if (map[1][27] == BLOCK1 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK1;
								map[1][27] = YUKA;
							}
						}
						if (map[2][27] != BLOCK22 || map[2][27] == BLOCK22)
						{
							if (map[2][27] == BLOCK22 && map[playerMapY][playerMapX] == map[4][11])
							{
								map[playerMapY][playerMapX] = BLOCK22;
								map[2][27] = YUKA;
							}
						}
						if (map[3][27] != BLOCK3 || map[3][27] == BLOCK3)
						{
							if (map[3][27] == BLOCK3 && map[playerMapY][playerMapX] == map[4][13])
							{
								map[playerMapY][playerMapX] = BLOCK3;
								map[3][27] = YUKA;
							}
						}
						if (map[4][27] != BLOCK4 || map[4][27] == BLOCK4)
						{
							if (map[4][27] == BLOCK4 && map[playerMapY][playerMapX] == map[4][15])
							{
								map[playerMapY][playerMapX] = BLOCK4;
								map[4][27] = YUKA;
							}
						}
						if (map[5][27] != BLOCK5 || map[5][27] == BLOCK5)
						{
							if (map[5][27] == BLOCK5 && map[playerMapY][playerMapX] == map[4][17])
							{
								map[playerMapY][playerMapX] = BLOCK5;
								map[5][27] = YUKA;
							}
						}
						if (map[6][27] != BLOCK6 || map[6][27] == BLOCK6)
						{

							if (map[6][27] == BLOCK6 && map[playerMapY][playerMapX] == /*6以降は後で*/map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK6;
								map[6][27] = YUKA;
							}
						}
						if (map[7][27] != BLOCK7 || map[7][27] == BLOCK7)
						{
							if (map[7][27] == BLOCK7 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK7;
								map[7][27] = YUKA;
							}
						}
						if (map[8][27] != BLOCK8 || map[8][27] == BLOCK8)
						{
							if (map[8][27] == BLOCK8 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK8;
								map[8][27] = YUKA;
							}
						}
						playerPosX += playerSpeed;
					}

					if (map[playerMapY][playerMapX + 1] == BLOCK1)
					{
						map[1][27] = BLOCK1;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = NN;
						playerPosX += playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK22)
					{
						map[2][27] = BLOCK22;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = NN;
						playerPosX += playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK3)
					{
						map[3][27] = BLOCK3;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = NN;
						playerPosX += playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK4)
					{
						map[4][27] = BLOCK4;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = NN;
						playerPosX += playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK5)
					{
						map[5][27] = BLOCK5;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = NN;
						playerPosX += playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK6)
					{
						map[6][27] = BLOCK6;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = NN;
						playerPosX += playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK7)
					{
						map[7][27] = BLOCK7;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = NN;
						playerPosX = playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK8)
					{
						map[8][27] = BLOCK8;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = NN;
						playerPosX += playerSpeed;

					}
				}
				if (map[playerMapY][playerMapX] == GI)
				{
					if (map[playerMapY][playerMapX + 1] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = GI;
						if (map[1][27] != BLOCK1 || map[1][27] == BLOCK1)
						{
							if (map[1][27] == BLOCK1 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK1;
								map[1][27] = YUKA;
							}
						}
						if (map[2][27] != BLOCK22 || map[2][27] == BLOCK22)
						{
							if (map[2][27] == BLOCK22 && map[playerMapY][playerMapX] == map[4][11])
							{
								map[playerMapY][playerMapX] = BLOCK22;
								map[2][27] = YUKA;
							}
						}
						if (map[3][27] != BLOCK3 || map[3][27] == BLOCK3)
						{
							if (map[3][27] == BLOCK3 && map[playerMapY][playerMapX] == map[4][13])
							{
								map[playerMapY][playerMapX] = BLOCK3;
								map[3][27] = YUKA;
							}
						}
						if (map[4][27] != BLOCK4 || map[4][27] == BLOCK4)
						{
							if (map[4][27] == BLOCK4 && map[playerMapY][playerMapX] == map[4][15])
							{
								map[playerMapY][playerMapX] = BLOCK4;
								map[4][27] = YUKA;
							}
						}
						if (map[5][27] != BLOCK5 || map[5][27] == BLOCK5)
						{
							if (map[5][27] == BLOCK5 && map[playerMapY][playerMapX] == map[4][17])
							{
								map[playerMapY][playerMapX] = BLOCK5;
								map[5][27] = YUKA;
							}
						}
						if (map[6][27] != BLOCK6 || map[6][27] == BLOCK6)
						{

							if (map[6][27] == BLOCK6 && map[playerMapY][playerMapX] == /*6以降は後で*/map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK6;
								map[6][27] = YUKA;
							}
						}
						if (map[7][27] != BLOCK7 || map[7][27] == BLOCK7)
						{
							if (map[7][27] == BLOCK7 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK7;
								map[7][27] = YUKA;
							}
						}
						if (map[8][27] != BLOCK8 || map[8][27] == BLOCK8)
						{
							if (map[8][27] == BLOCK8 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK8;
								map[8][27] = YUKA;
							}
						}
						playerPosX += playerSpeed;
					}

					if (map[playerMapY][playerMapX + 1] == BLOCK1)
					{
						map[1][27] = BLOCK1;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = GI;
						playerPosX += playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK22)
					{
						map[2][27] = BLOCK22;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = GI;
						playerPosX += playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK3)
					{
						map[3][27] = BLOCK3;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = GI;
						playerPosX += playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK4)
					{
						map[4][27] = BLOCK4;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = GI;
						playerPosX += playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK5)
					{
						map[5][27] = BLOCK5;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = GI;
						playerPosX += playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK6)
					{
						map[6][27] = BLOCK6;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = GI;
						playerPosX += playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK7)
					{
						map[7][27] = BLOCK7;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = GI;
						playerPosX = playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK8)
					{
						map[8][27] = BLOCK8;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = GI;
						playerPosX += playerSpeed;

					}
				}
				if (map[playerMapY][playerMapX] == ZO)
				{
					if (map[playerMapY][playerMapX + 1] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = ZO;
						if (map[1][27] != BLOCK1 || map[1][27] == BLOCK1)
						{
							if (map[1][27] == BLOCK1 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK1;
								map[1][27] = YUKA;
							}
						}
						if (map[2][27] != BLOCK22 || map[2][27] == BLOCK22)
						{
							if (map[2][27] == BLOCK22 && map[playerMapY][playerMapX] == map[4][11])
							{
								map[playerMapY][playerMapX] = BLOCK22;
								map[2][27] = YUKA;
							}
						}
						if (map[3][27] != BLOCK3 || map[3][27] == BLOCK3)
						{
							if (map[3][27] == BLOCK3 && map[playerMapY][playerMapX] == map[4][13])
							{
								map[playerMapY][playerMapX] = BLOCK3;
								map[3][27] = YUKA;
							}
						}
						if (map[4][27] != BLOCK4 || map[4][27] == BLOCK4)
						{
							if (map[4][27] == BLOCK4 && map[playerMapY][playerMapX] == map[4][15])
							{
								map[playerMapY][playerMapX] = BLOCK4;
								map[4][27] = YUKA;
							}
						}
						if (map[5][27] != BLOCK5 || map[5][27] == BLOCK5)
						{
							if (map[5][27] == BLOCK5 && map[playerMapY][playerMapX] == map[4][17])
							{
								map[playerMapY][playerMapX] = BLOCK5;
								map[5][27] = YUKA;
							}
						}
						if (map[6][27] != BLOCK6 || map[6][27] == BLOCK6)
						{

							if (map[6][27] == BLOCK6 && map[playerMapY][playerMapX] == /*6以降は後で*/map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK6;
								map[6][27] = YUKA;
							}
						}
						if (map[7][27] != BLOCK7 || map[7][27] == BLOCK7)
						{
							if (map[7][27] == BLOCK7 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK7;
								map[7][27] = YUKA;
							}
						}
						if (map[8][27] != BLOCK8 || map[8][27] == BLOCK8)
						{
							if (map[8][27] == BLOCK8 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK8;
								map[8][27] = YUKA;
							}
						}
						playerPosX += playerSpeed;
					}
					if (map[playerMapY][playerMapX + 1] == BLOCK1)
					{
						map[1][27] = BLOCK1;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = ZO;
						playerPosX += playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK22)
					{
						map[2][27] = BLOCK22;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = ZO;
						playerPosX += playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK3)
					{
						map[3][27] = BLOCK3;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = ZO;
						playerPosX += playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK4)
					{
						map[4][27] = BLOCK4;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = ZO;
						playerPosX += playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK5)
					{
						map[5][27] = BLOCK5;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = ZO;
						playerPosX += playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK6)
					{
						map[6][27] = BLOCK6;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = ZO;
						playerPosX += playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK7)
					{
						map[7][27] = BLOCK7;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = ZO;
						playerPosX = playerSpeed;

					}
					if (map[playerMapY][playerMapX + 1] == BLOCK8)
					{
						map[8][27] = BLOCK8;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY][playerMapX + 1] = ZO;
						playerPosX += playerSpeed;

					}
				}
			}

			if (keys[DIK_S] && preKeys[DIK_S] == 0 || keys[DIK_DOWN] && preKeys[DIK_DOWN] == 0)
			{
				playerTmpY = playerPosY + playerSpeed;
				playerMapY = playerTmpY / KBlockSize;
				//何もないから実際に進ませる
				if (map[playerMapY][playerMapX] == YUKA)
				{
					playerPosY += playerSpeed;
				}
				if (map[playerMapY][playerMapX] == GOAL)
				{
					playerPosY += playerSpeed;
				}

				if (map[playerMapY][playerMapX] == I)
				{
					if (map[playerMapY + 1][playerMapX] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = I;
						if (map[1][27] != BLOCK1 || map[1][27] == BLOCK1)
						{
							if (map[1][27] == BLOCK1 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK1;
								map[1][27] = YUKA;
							}
						}
						if (map[2][27] != BLOCK22 || map[2][27] == BLOCK22)
						{
							if (map[2][27] == BLOCK22 && map[playerMapY][playerMapX] == map[4][11])
							{
								map[playerMapY][playerMapX] = BLOCK22;
								map[2][27] = YUKA;
							}
						}
						if (map[3][27] != BLOCK3 || map[3][27] == BLOCK3)
						{
							if (map[3][27] == BLOCK3 && map[playerMapY][playerMapX] == map[4][13])
							{
								map[playerMapY][playerMapX] = BLOCK3;
								map[3][27] = YUKA;
							}
						}
						if (map[4][27] != BLOCK4 || map[4][27] == BLOCK4)
						{
							if (map[4][27] == BLOCK4 && map[playerMapY][playerMapX] == map[4][15])
							{
								map[playerMapY][playerMapX] = BLOCK4;
								map[4][27] = YUKA;
							}
						}
						if (map[5][27] != BLOCK5 || map[5][27] == BLOCK5)
						{
							if (map[5][27] == BLOCK5 && map[playerMapY][playerMapX] == map[4][17])
							{
								map[playerMapY][playerMapX] = BLOCK5;
								map[5][27] = YUKA;
							}
						}
						if (map[6][27] != BLOCK6 || map[6][27] == BLOCK6)
						{

							if (map[6][27] == BLOCK6 && map[playerMapY][playerMapX] == /*6以降は後で*/map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK6;
								map[6][27] = YUKA;
							}
						}
						if (map[7][27] != BLOCK7 || map[7][27] == BLOCK7)
						{
							if (map[7][27] == BLOCK7 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK7;
								map[7][27] = YUKA;
							}
						}
						if (map[8][27] != BLOCK8 || map[8][27] == BLOCK8)
						{
							if (map[8][27] == BLOCK8 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK8;
								map[8][27] = YUKA;
							}
						}
						playerPosY += playerSpeed;
					}

					if (map[playerMapY + 1][playerMapX] == BLOCK1)
					{
						map[1][27] = BLOCK1;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = I;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK22)
					{
						map[2][27] = BLOCK22;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = I;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK3)
					{
						map[3][27] = BLOCK3;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = I;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK4)
					{
						map[4][27] = BLOCK4;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = I;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK5)
					{
						map[5][27] = BLOCK5;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = I;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK6)
					{
						map[6][27] = BLOCK6;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = I;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK7)
					{
						map[7][27] = BLOCK7;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = I;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK8)
					{
						map[8][27] = BLOCK8;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = I;
						playerPosY += playerSpeed;

					}



				}

				// 1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111
				// ここから直して
				if (map[playerMapY][playerMapX] == U)
				{
					if (map[playerMapY + 1][playerMapX] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = U; //ここをUに変える　したも同じ
						if (map[1][27] != BLOCK1 || map[1][27] == BLOCK1)
						{
							if (map[1][27] == BLOCK1 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK1;
								map[1][27] = YUKA;
							}
						}
						if (map[2][27] != BLOCK22 || map[2][27] == BLOCK22)
						{
							if (map[2][27] == BLOCK22 && map[playerMapY][playerMapX] == map[4][11])
							{
								map[playerMapY][playerMapX] = BLOCK22;
								map[2][27] = YUKA;
							}
						}
						if (map[3][27] != BLOCK3 || map[3][27] == BLOCK3)
						{
							if (map[3][27] == BLOCK3 && map[playerMapY][playerMapX] == map[4][13])
							{
								map[playerMapY][playerMapX] = BLOCK3;
								map[3][27] = YUKA;
							}
						}
						if (map[4][27] != BLOCK4 || map[4][27] == BLOCK4)
						{
							if (map[4][27] == BLOCK4 && map[playerMapY][playerMapX] == map[4][15])
							{
								map[playerMapY][playerMapX] = BLOCK4;
								map[4][27] = YUKA;
							}
						}
						if (map[5][27] != BLOCK5 || map[5][27] == BLOCK5)
						{
							if (map[5][27] == BLOCK5 && map[playerMapY][playerMapX] == map[4][17])
							{
								map[playerMapY][playerMapX] = BLOCK5;
								map[5][27] = YUKA;
							}
						}
						if (map[6][27] != BLOCK6 || map[6][27] == BLOCK6)
						{

							if (map[6][27] == BLOCK6 && map[playerMapY][playerMapX] == /*6以降は後で*/map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK6;
								map[6][27] = YUKA;
							}
						}
						if (map[7][27] != BLOCK7 || map[7][27] == BLOCK7)
						{
							if (map[7][27] == BLOCK7 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK7;
								map[7][27] = YUKA;
							}
						}
						if (map[8][27] != BLOCK8 || map[8][27] == BLOCK8)
						{
							if (map[8][27] == BLOCK8 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK8;
								map[8][27] = YUKA;
							}
						}
						playerPosY += playerSpeed;
					}

					if (map[playerMapY + 1][playerMapX] == BLOCK1)
					{
						map[1][27] = BLOCK1;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = U;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK22)
					{
						map[2][27] = BLOCK22;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = U;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK3)
					{
						map[3][27] = BLOCK3;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = U;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK4)
					{
						map[4][27] = BLOCK4;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = U;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK5)
					{
						map[5][27] = BLOCK5;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = U;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK6)
					{
						map[6][27] = BLOCK6;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = U;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK7)
					{
						map[7][27] = BLOCK7;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = U;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK8)
					{
						map[8][27] = BLOCK8;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = U;
						playerPosY += playerSpeed;

					}
				}
				if (map[playerMapY][playerMapX] == E)
				{
					if (map[playerMapY + 1][playerMapX] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = E;
						if (map[1][27] != BLOCK1 || map[1][27] == BLOCK1)
						{
							if (map[1][27] == BLOCK1 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK1;
								map[1][27] = YUKA;
							}
						}
						if (map[2][27] != BLOCK22 || map[2][27] == BLOCK22)
						{
							if (map[2][27] == BLOCK22 && map[playerMapY][playerMapX] == map[4][11])
							{
								map[playerMapY][playerMapX] = BLOCK22;
								map[2][27] = YUKA;
							}
						}
						if (map[3][27] != BLOCK3 || map[3][27] == BLOCK3)
						{
							if (map[3][27] == BLOCK3 && map[playerMapY][playerMapX] == map[4][13])
							{
								map[playerMapY][playerMapX] = BLOCK3;
								map[3][27] = YUKA;
							}
						}
						if (map[4][27] != BLOCK4 || map[4][27] == BLOCK4)
						{
							if (map[4][27] == BLOCK4 && map[playerMapY][playerMapX] == map[4][15])
							{
								map[playerMapY][playerMapX] = BLOCK4;
								map[4][27] = YUKA;
							}
						}
						if (map[5][27] != BLOCK5 || map[5][27] == BLOCK5)
						{
							if (map[5][27] == BLOCK5 && map[playerMapY][playerMapX] == map[4][17])
							{
								map[playerMapY][playerMapX] = BLOCK5;
								map[5][27] = YUKA;
							}
						}
						if (map[6][27] != BLOCK6 || map[6][27] == BLOCK6)
						{

							if (map[6][27] == BLOCK6 && map[playerMapY][playerMapX] == /*6以降は後で*/map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK6;
								map[6][27] = YUKA;
							}
						}
						if (map[7][27] != BLOCK7 || map[7][27] == BLOCK7)
						{
							if (map[7][27] == BLOCK7 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK7;
								map[7][27] = YUKA;
							}
						}
						if (map[8][27] != BLOCK8 || map[8][27] == BLOCK8)
						{
							if (map[8][27] == BLOCK8 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK8;
								map[8][27] = YUKA;
							}
						}
						playerPosY += playerSpeed;
					}
					if (map[playerMapY + 1][playerMapX] == BLOCK1)
					{
						map[1][27] = BLOCK1;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = E;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK22)
					{
						map[2][27] = BLOCK22;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = E;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK3)
					{
						map[3][27] = BLOCK3;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = E;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK4)
					{
						map[4][27] = BLOCK4;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = E;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK5)
					{
						map[5][27] = BLOCK5;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = E;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK6)
					{
						map[6][27] = BLOCK6;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = E;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK7)
					{
						map[7][27] = BLOCK7;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = E;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK8)
					{
						map[8][27] = BLOCK8;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = E;
						playerPosY += playerSpeed;

					}
				}
				if (map[playerMapY][playerMapX] == KA)
				{
					if (map[playerMapY + 1][playerMapX] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = KA;
						if (map[1][27] != BLOCK1 || map[1][27] == BLOCK1)
						{
							if (map[1][27] == BLOCK1 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK1;
								map[1][27] = YUKA;
							}
						}
						if (map[2][27] != BLOCK22 || map[2][27] == BLOCK22)
						{
							if (map[2][27] == BLOCK22 && map[playerMapY][playerMapX] == map[4][11])
							{
								map[playerMapY][playerMapX] = BLOCK22;
								map[2][27] = YUKA;
							}
						}
						if (map[3][27] != BLOCK3 || map[3][27] == BLOCK3)
						{
							if (map[3][27] == BLOCK3 && map[playerMapY][playerMapX] == map[4][13])
							{
								map[playerMapY][playerMapX] = BLOCK3;
								map[3][27] = YUKA;
							}
						}
						if (map[4][27] != BLOCK4 || map[4][27] == BLOCK4)
						{
							if (map[4][27] == BLOCK4 && map[playerMapY][playerMapX] == map[4][15])
							{
								map[playerMapY][playerMapX] = BLOCK4;
								map[4][27] = YUKA;
							}
						}
						if (map[5][27] != BLOCK5 || map[5][27] == BLOCK5)
						{
							if (map[5][27] == BLOCK5 && map[playerMapY][playerMapX] == map[4][17])
							{
								map[playerMapY][playerMapX] = BLOCK5;
								map[5][27] = YUKA;
							}
						}
						if (map[6][27] != BLOCK6 || map[6][27] == BLOCK6)
						{

							if (map[6][27] == BLOCK6 && map[playerMapY][playerMapX] == /*6以降は後で*/map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK6;
								map[6][27] = YUKA;
							}
						}
						if (map[7][27] != BLOCK7 || map[7][27] == BLOCK7)
						{
							if (map[7][27] == BLOCK7 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK7;
								map[7][27] = YUKA;
							}
						}
						if (map[8][27] != BLOCK8 || map[8][27] == BLOCK8)
						{
							if (map[8][27] == BLOCK8 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK8;
								map[8][27] = YUKA;
							}
						}
						playerPosY += playerSpeed;
					}

					if (map[playerMapY + 1][playerMapX] == BLOCK1)
					{
						map[1][27] = BLOCK1;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = KA;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK22)
					{
						map[2][27] = BLOCK22;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = KA;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK3)
					{
						map[3][27] = BLOCK3;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = KA;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK4)
					{
						map[4][27] = BLOCK4;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = KA;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK5)
					{
						map[5][27] = BLOCK5;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = KA;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK6)
					{
						map[6][27] = BLOCK6;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = KA;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK7)
					{
						map[7][27] = BLOCK7;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = KA;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK8)
					{
						map[8][27] = BLOCK8;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = KA;
						playerPosY += playerSpeed;

					}
				}
				if (map[playerMapY][playerMapX] == KU)
				{
					if (map[playerMapY + 1][playerMapX] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = KU;
						if (map[1][27] != BLOCK1 || map[1][27] == BLOCK1)
						{
							if (map[1][27] == BLOCK1 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK1;
								map[1][27] = YUKA;
							}
						}
						if (map[2][27] != BLOCK22 || map[2][27] == BLOCK22)
						{
							if (map[2][27] == BLOCK22 && map[playerMapY][playerMapX] == map[4][11])
							{
								map[playerMapY][playerMapX] = BLOCK22;
								map[2][27] = YUKA;
							}
						}
						if (map[3][27] != BLOCK3 || map[3][27] == BLOCK3)
						{
							if (map[3][27] == BLOCK3 && map[playerMapY][playerMapX] == map[4][13])
							{
								map[playerMapY][playerMapX] = BLOCK3;
								map[3][27] = YUKA;
							}
						}
						if (map[4][27] != BLOCK4 || map[4][27] == BLOCK4)
						{
							if (map[4][27] == BLOCK4 && map[playerMapY][playerMapX] == map[4][15])
							{
								map[playerMapY][playerMapX] = BLOCK4;
								map[4][27] = YUKA;
							}
						}
						if (map[5][27] != BLOCK5 || map[5][27] == BLOCK5)
						{
							if (map[5][27] == BLOCK5 && map[playerMapY][playerMapX] == map[4][17])
							{
								map[playerMapY][playerMapX] = BLOCK5;
								map[5][27] = YUKA;
							}
						}
						if (map[6][27] != BLOCK6 || map[6][27] == BLOCK6)
						{

							if (map[6][27] == BLOCK6 && map[playerMapY][playerMapX] == /*6以降は後で*/map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK6;
								map[6][27] = YUKA;
							}
						}
						if (map[7][27] != BLOCK7 || map[7][27] == BLOCK7)
						{
							if (map[7][27] == BLOCK7 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK7;
								map[7][27] = YUKA;
							}
						}
						if (map[8][27] != BLOCK8 || map[8][27] == BLOCK8)
						{
							if (map[8][27] == BLOCK8 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK8;
								map[8][27] = YUKA;
							}
						}
						playerPosY += playerSpeed;
					}

					if (map[playerMapY + 1][playerMapX] == BLOCK1)
					{
						map[1][27] = BLOCK1;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = KU;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK22)
					{
						map[2][27] = BLOCK22;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = KU;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK3)
					{
						map[3][27] = BLOCK3;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = KU;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK4)
					{
						map[4][27] = BLOCK4;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = KU;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK5)
					{
						map[5][27] = BLOCK5;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = KU;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK6)
					{
						map[6][27] = BLOCK6;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = KU;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK7)
					{
						map[7][27] = BLOCK7;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = KU;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK8)
					{
						map[8][27] = BLOCK8;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = KU;
						playerPosY += playerSpeed;

					}
				}
				if (map[playerMapY][playerMapX] == KO)
				{
					if (map[playerMapY + 1][playerMapX] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = KO;
						if (map[1][27] != BLOCK1 || map[1][27] == BLOCK1)
						{
							if (map[1][27] == BLOCK1 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK1;
								map[1][27] = YUKA;
							}
						}
						if (map[2][27] != BLOCK22 || map[2][27] == BLOCK22)
						{
							if (map[2][27] == BLOCK22 && map[playerMapY][playerMapX] == map[4][11])
							{
								map[playerMapY][playerMapX] = BLOCK22;
								map[2][27] = YUKA;
							}
						}
						if (map[3][27] != BLOCK3 || map[3][27] == BLOCK3)
						{
							if (map[3][27] == BLOCK3 && map[playerMapY][playerMapX] == map[4][13])
							{
								map[playerMapY][playerMapX] = BLOCK3;
								map[3][27] = YUKA;
							}
						}
						if (map[4][27] != BLOCK4 || map[4][27] == BLOCK4)
						{
							if (map[4][27] == BLOCK4 && map[playerMapY][playerMapX] == map[4][15])
							{
								map[playerMapY][playerMapX] = BLOCK4;
								map[4][27] = YUKA;
							}
						}
						if (map[5][27] != BLOCK5 || map[5][27] == BLOCK5)
						{
							if (map[5][27] == BLOCK5 && map[playerMapY][playerMapX] == map[4][17])
							{
								map[playerMapY][playerMapX] = BLOCK5;
								map[5][27] = YUKA;
							}
						}
						if (map[6][27] != BLOCK6 || map[6][27] == BLOCK6)
						{

							if (map[6][27] == BLOCK6 && map[playerMapY][playerMapX] == /*6以降は後で*/map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK6;
								map[6][27] = YUKA;
							}
						}
						if (map[7][27] != BLOCK7 || map[7][27] == BLOCK7)
						{
							if (map[7][27] == BLOCK7 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK7;
								map[7][27] = YUKA;
							}
						}
						if (map[8][27] != BLOCK8 || map[8][27] == BLOCK8)
						{
							if (map[8][27] == BLOCK8 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK8;
								map[8][27] = YUKA;
							}
						}
						playerPosY += playerSpeed;
					}

					if (map[playerMapY + 1][playerMapX] == BLOCK1)
					{
						map[1][27] = BLOCK1;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = KO;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK22)
					{
						map[2][27] = BLOCK22;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = KO;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK3)
					{
						map[3][27] = BLOCK3;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = KO;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK4)
					{
						map[4][27] = BLOCK4;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = KO;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK5)
					{
						map[5][27] = BLOCK5;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = KO;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK6)
					{
						map[6][27] = BLOCK6;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = KO;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK7)
					{
						map[7][27] = BLOCK7;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = KO;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK8)
					{
						map[8][27] = BLOCK8;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = KO;
						playerPosY += playerSpeed;

					}
				}
				if (map[playerMapY][playerMapX] == SA)
				{
					if (map[playerMapY + 1][playerMapX] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = SA;
						if (map[1][27] != BLOCK1 || map[1][27] == BLOCK1)
						{
							if (map[1][27] == BLOCK1 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK1;
								map[1][27] = YUKA;
							}
						}
						if (map[2][27] != BLOCK22 || map[2][27] == BLOCK22)
						{
							if (map[2][27] == BLOCK22 && map[playerMapY][playerMapX] == map[4][11])
							{
								map[playerMapY][playerMapX] = BLOCK22;
								map[2][27] = YUKA;
							}
						}
						if (map[3][27] != BLOCK3 || map[3][27] == BLOCK3)
						{
							if (map[3][27] == BLOCK3 && map[playerMapY][playerMapX] == map[4][13])
							{
								map[playerMapY][playerMapX] = BLOCK3;
								map[3][27] = YUKA;
							}
						}
						if (map[4][27] != BLOCK4 || map[4][27] == BLOCK4)
						{
							if (map[4][27] == BLOCK4 && map[playerMapY][playerMapX] == map[4][15])
							{
								map[playerMapY][playerMapX] = BLOCK4;
								map[4][27] = YUKA;
							}
						}
						if (map[5][27] != BLOCK5 || map[5][27] == BLOCK5)
						{
							if (map[5][27] == BLOCK5 && map[playerMapY][playerMapX] == map[4][17])
							{
								map[playerMapY][playerMapX] = BLOCK5;
								map[5][27] = YUKA;
							}
						}
						if (map[6][27] != BLOCK6 || map[6][27] == BLOCK6)
						{

							if (map[6][27] == BLOCK6 && map[playerMapY][playerMapX] == /*6以降は後で*/map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK6;
								map[6][27] = YUKA;
							}
						}
						if (map[7][27] != BLOCK7 || map[7][27] == BLOCK7)
						{
							if (map[7][27] == BLOCK7 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK7;
								map[7][27] = YUKA;
							}
						}
						if (map[8][27] != BLOCK8 || map[8][27] == BLOCK8)
						{
							if (map[8][27] == BLOCK8 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK8;
								map[8][27] = YUKA;
							}
						}
						playerPosY += playerSpeed;
					}
					if (map[playerMapY + 1][playerMapX] == BLOCK1)
					{
						map[1][27] = BLOCK1;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = SA;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK22)
					{
						map[2][27] = BLOCK22;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = SA;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK3)
					{
						map[3][27] = BLOCK3;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = SA;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK4)
					{
						map[4][27] = BLOCK4;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = SA;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK5)
					{
						map[5][27] = BLOCK5;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = SA;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK6)
					{
						map[6][27] = BLOCK6;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = SA;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK7)
					{
						map[7][27] = BLOCK7;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = SA;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK8)
					{
						map[8][27] = BLOCK8;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = SA;
						playerPosY += playerSpeed;

					}
				}
				if (map[playerMapY][playerMapX] == SU)
				{
					if (map[playerMapY + 1][playerMapX] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = SU;
						if (map[1][27] != BLOCK1 || map[1][27] == BLOCK1)
						{
							if (map[1][27] == BLOCK1 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK1;
								map[1][27] = YUKA;
							}
						}
						if (map[2][27] != BLOCK22 || map[2][27] == BLOCK22)
						{
							if (map[2][27] == BLOCK22 && map[playerMapY][playerMapX] == map[4][11])
							{
								map[playerMapY][playerMapX] = BLOCK22;
								map[2][27] = YUKA;
							}
						}
						if (map[3][27] != BLOCK3 || map[3][27] == BLOCK3)
						{
							if (map[3][27] == BLOCK3 && map[playerMapY][playerMapX] == map[4][13])
							{
								map[playerMapY][playerMapX] = BLOCK3;
								map[3][27] = YUKA;
							}
						}
						if (map[4][27] != BLOCK4 || map[4][27] == BLOCK4)
						{
							if (map[4][27] == BLOCK4 && map[playerMapY][playerMapX] == map[4][15])
							{
								map[playerMapY][playerMapX] = BLOCK4;
								map[4][27] = YUKA;
							}
						}
						if (map[5][27] != BLOCK5 || map[5][27] == BLOCK5)
						{
							if (map[5][27] == BLOCK5 && map[playerMapY][playerMapX] == map[4][17])
							{
								map[playerMapY][playerMapX] = BLOCK5;
								map[5][27] = YUKA;
							}
						}
						if (map[6][27] != BLOCK6 || map[6][27] == BLOCK6)
						{

							if (map[6][27] == BLOCK6 && map[playerMapY][playerMapX] == /*6以降は後で*/map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK6;
								map[6][27] = YUKA;
							}
						}
						if (map[7][27] != BLOCK7 || map[7][27] == BLOCK7)
						{
							if (map[7][27] == BLOCK7 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK7;
								map[7][27] = YUKA;
							}
						}
						if (map[8][27] != BLOCK8 || map[8][27] == BLOCK8)
						{
							if (map[8][27] == BLOCK8 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK8;
								map[8][27] = YUKA;
							}
						}
						playerPosY += playerSpeed;
					}

					if (map[playerMapY + 1][playerMapX] == BLOCK1)
					{
						map[1][27] = BLOCK1;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = SU;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK22)
					{
						map[2][27] = BLOCK22;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = SU;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK3)
					{
						map[3][27] = BLOCK3;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = SU;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK4)
					{
						map[4][27] = BLOCK4;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = SU;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK5)
					{
						map[5][27] = BLOCK5;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = SU;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK6)
					{
						map[6][27] = BLOCK6;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = SU;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK7)
					{
						map[7][27] = BLOCK7;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = SU;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK8)
					{
						map[8][27] = BLOCK8;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = SU;
						playerPosY += playerSpeed;

					}
				}
				if (map[playerMapY][playerMapX] == SO)
				{
					if (map[playerMapY + 1][playerMapX] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = SO;
						if (map[1][27] != BLOCK1 || map[1][27] == BLOCK1)
						{
							if (map[1][27] == BLOCK1 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK1;
								map[1][27] = YUKA;
							}
						}
						if (map[2][27] != BLOCK22 || map[2][27] == BLOCK22)
						{
							if (map[2][27] == BLOCK22 && map[playerMapY][playerMapX] == map[4][11])
							{
								map[playerMapY][playerMapX] = BLOCK22;
								map[2][27] = YUKA;
							}
						}
						if (map[3][27] != BLOCK3 || map[3][27] == BLOCK3)
						{
							if (map[3][27] == BLOCK3 && map[playerMapY][playerMapX] == map[4][13])
							{
								map[playerMapY][playerMapX] = BLOCK3;
								map[3][27] = YUKA;
							}
						}
						if (map[4][27] != BLOCK4 || map[4][27] == BLOCK4)
						{
							if (map[4][27] == BLOCK4 && map[playerMapY][playerMapX] == map[4][15])
							{
								map[playerMapY][playerMapX] = BLOCK4;
								map[4][27] = YUKA;
							}
						}
						if (map[5][27] != BLOCK5 || map[5][27] == BLOCK5)
						{
							if (map[5][27] == BLOCK5 && map[playerMapY][playerMapX] == map[4][17])
							{
								map[playerMapY][playerMapX] = BLOCK5;
								map[5][27] = YUKA;
							}
						}
						if (map[6][27] != BLOCK6 || map[6][27] == BLOCK6)
						{

							if (map[6][27] == BLOCK6 && map[playerMapY][playerMapX] == /*6以降は後で*/map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK6;
								map[6][27] = YUKA;
							}
						}
						if (map[7][27] != BLOCK7 || map[7][27] == BLOCK7)
						{
							if (map[7][27] == BLOCK7 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK7;
								map[7][27] = YUKA;
							}
						}
						if (map[8][27] != BLOCK8 || map[8][27] == BLOCK8)
						{
							if (map[8][27] == BLOCK8 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK8;
								map[8][27] = YUKA;
							}
						}
						playerPosY += playerSpeed;
					}

					if (map[playerMapY + 1][playerMapX] == BLOCK1)
					{
						map[1][27] = BLOCK1;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = SO;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK22)
					{
						map[2][27] = BLOCK22;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = SO;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK3)
					{
						map[3][27] = BLOCK3;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = SO;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK4)
					{
						map[4][27] = BLOCK4;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = SO;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK5)
					{
						map[5][27] = BLOCK5;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = SO;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK6)
					{
						map[6][27] = BLOCK6;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = SO;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK7)
					{
						map[7][27] = BLOCK7;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = SO;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK8)
					{
						map[8][27] = BLOCK8;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = SO;
						playerPosY += playerSpeed;

					}
				}
				if (map[playerMapY][playerMapX] == TA)
				{
					if (map[playerMapY + 1][playerMapX] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = TA;
						if (map[1][27] != BLOCK1 || map[1][27] == BLOCK1)
						{
							if (map[1][27] == BLOCK1 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK1;
								map[1][27] = YUKA;
							}
						}
						if (map[2][27] != BLOCK22 || map[2][27] == BLOCK22)
						{
							if (map[2][27] == BLOCK22 && map[playerMapY][playerMapX] == map[4][11])
							{
								map[playerMapY][playerMapX] = BLOCK22;
								map[2][27] = YUKA;
							}
						}
						if (map[3][27] != BLOCK3 || map[3][27] == BLOCK3)
						{
							if (map[3][27] == BLOCK3 && map[playerMapY][playerMapX] == map[4][13])
							{
								map[playerMapY][playerMapX] = BLOCK3;
								map[3][27] = YUKA;
							}
						}
						if (map[4][27] != BLOCK4 || map[4][27] == BLOCK4)
						{
							if (map[4][27] == BLOCK4 && map[playerMapY][playerMapX] == map[4][15])
							{
								map[playerMapY][playerMapX] = BLOCK4;
								map[4][27] = YUKA;
							}
						}
						if (map[5][27] != BLOCK5 || map[5][27] == BLOCK5)
						{
							if (map[5][27] == BLOCK5 && map[playerMapY][playerMapX] == map[4][17])
							{
								map[playerMapY][playerMapX] = BLOCK5;
								map[5][27] = YUKA;
							}
						}
						if (map[6][27] != BLOCK6 || map[6][27] == BLOCK6)
						{

							if (map[6][27] == BLOCK6 && map[playerMapY][playerMapX] == /*6以降は後で*/map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK6;
								map[6][27] = YUKA;
							}
						}
						if (map[7][27] != BLOCK7 || map[7][27] == BLOCK7)
						{
							if (map[7][27] == BLOCK7 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK7;
								map[7][27] = YUKA;
							}
						}
						if (map[8][27] != BLOCK8 || map[8][27] == BLOCK8)
						{
							if (map[8][27] == BLOCK8 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK8;
								map[8][27] = YUKA;
							}
						}
						playerPosY += playerSpeed;
					}

					if (map[playerMapY + 1][playerMapX] == BLOCK1)
					{
						map[1][27] = BLOCK1;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = TA;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK22)
					{
						map[2][27] = BLOCK22;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = TA;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK3)
					{
						map[3][27] = BLOCK3;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = TA;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK4)
					{
						map[4][27] = BLOCK4;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = TA;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK5)
					{
						map[5][27] = BLOCK5;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = TA;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK6)
					{
						map[6][27] = BLOCK6;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = TA;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK7)
					{
						map[7][27] = BLOCK7;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = TA;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK8)
					{
						map[8][27] = BLOCK8;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = TA;
						playerPosY += playerSpeed;

					}
				}
				if (map[playerMapY][playerMapX] == CHI)
				{
					if (map[playerMapY + 1][playerMapX] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = CHI;
						if (map[1][27] != BLOCK1 || map[1][27] == BLOCK1)
						{
							if (map[1][27] == BLOCK1 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK1;
								map[1][27] = YUKA;
							}
						}
						if (map[2][27] != BLOCK22 || map[2][27] == BLOCK22)
						{
							if (map[2][27] == BLOCK22 && map[playerMapY][playerMapX] == map[4][11])
							{
								map[playerMapY][playerMapX] = BLOCK22;
								map[2][27] = YUKA;
							}
						}
						if (map[3][27] != BLOCK3 || map[3][27] == BLOCK3)
						{
							if (map[3][27] == BLOCK3 && map[playerMapY][playerMapX] == map[4][13])
							{
								map[playerMapY][playerMapX] = BLOCK3;
								map[3][27] = YUKA;
							}
						}
						if (map[4][27] != BLOCK4 || map[4][27] == BLOCK4)
						{
							if (map[4][27] == BLOCK4 && map[playerMapY][playerMapX] == map[4][15])
							{
								map[playerMapY][playerMapX] = BLOCK4;
								map[4][27] = YUKA;
							}
						}
						if (map[5][27] != BLOCK5 || map[5][27] == BLOCK5)
						{
							if (map[5][27] == BLOCK5 && map[playerMapY][playerMapX] == map[4][17])
							{
								map[playerMapY][playerMapX] = BLOCK5;
								map[5][27] = YUKA;
							}
						}
						if (map[6][27] != BLOCK6 || map[6][27] == BLOCK6)
						{

							if (map[6][27] == BLOCK6 && map[playerMapY][playerMapX] == /*6以降は後で*/map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK6;
								map[6][27] = YUKA;
							}
						}
						if (map[7][27] != BLOCK7 || map[7][27] == BLOCK7)
						{
							if (map[7][27] == BLOCK7 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK7;
								map[7][27] = YUKA;
							}
						}
						if (map[8][27] != BLOCK8 || map[8][27] == BLOCK8)
						{
							if (map[8][27] == BLOCK8 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK8;
								map[8][27] = YUKA;
							}
						}
						playerPosY += playerSpeed;
					}

					if (map[playerMapY + 1][playerMapX] == BLOCK1)
					{
						map[1][27] = BLOCK1;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = CHI;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK22)
					{
						map[2][27] = BLOCK22;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = CHI;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK3)
					{
						map[3][27] = BLOCK3;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = CHI;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK4)
					{
						map[4][27] = BLOCK4;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = CHI;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK5)
					{
						map[5][27] = BLOCK5;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = CHI;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK6)
					{
						map[6][27] = BLOCK6;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = CHI;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK7)
					{
						map[7][27] = BLOCK7;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = CHI;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK8)
					{
						map[8][27] = BLOCK8;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = CHI;
						playerPosY += playerSpeed;

					}
				}

				if (map[playerMapY][playerMapX] == NU)
				{
					if (map[playerMapY + 1][playerMapX] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = NU;
						if (map[1][27] != BLOCK1 || map[1][27] == BLOCK1)
						{
							if (map[1][27] == BLOCK1 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK1;
								map[1][27] = YUKA;
							}
						}
						if (map[2][27] != BLOCK22 || map[2][27] == BLOCK22)
						{
							if (map[2][27] == BLOCK22 && map[playerMapY][playerMapX] == map[4][11])
							{
								map[playerMapY][playerMapX] = BLOCK22;
								map[2][27] = YUKA;
							}
						}
						if (map[3][27] != BLOCK3 || map[3][27] == BLOCK3)
						{
							if (map[3][27] == BLOCK3 && map[playerMapY][playerMapX] == map[4][13])
							{
								map[playerMapY][playerMapX] = BLOCK3;
								map[3][27] = YUKA;
							}
						}
						if (map[4][27] != BLOCK4 || map[4][27] == BLOCK4)
						{
							if (map[4][27] == BLOCK4 && map[playerMapY][playerMapX] == map[4][15])
							{
								map[playerMapY][playerMapX] = BLOCK4;
								map[4][27] = YUKA;
							}
						}
						if (map[5][27] != BLOCK5 || map[5][27] == BLOCK5)
						{
							if (map[5][27] == BLOCK5 && map[playerMapY][playerMapX] == map[4][17])
							{
								map[playerMapY][playerMapX] = BLOCK5;
								map[5][27] = YUKA;
							}
						}
						if (map[6][27] != BLOCK6 || map[6][27] == BLOCK6)
						{

							if (map[6][27] == BLOCK6 && map[playerMapY][playerMapX] == /*6以降は後で*/map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK6;
								map[6][27] = YUKA;
							}
						}
						if (map[7][27] != BLOCK7 || map[7][27] == BLOCK7)
						{
							if (map[7][27] == BLOCK7 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK7;
								map[7][27] = YUKA;
							}
						}
						if (map[8][27] != BLOCK8 || map[8][27] == BLOCK8)
						{
							if (map[8][27] == BLOCK8 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK8;
								map[8][27] = YUKA;
							}
						}
						playerPosY += playerSpeed;
					}

					if (map[playerMapY + 1][playerMapX] == BLOCK1)
					{
						map[1][27] = BLOCK1;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = NU;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK22)
					{
						map[2][27] = BLOCK22;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = NU;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK3)
					{
						map[3][27] = BLOCK3;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = NU;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK4)
					{
						map[4][27] = BLOCK4;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = NU;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK5)
					{
						map[5][27] = BLOCK5;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = NU;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK6)
					{
						map[6][27] = BLOCK6;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = NU;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK7)
					{
						map[7][27] = BLOCK7;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = NU;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK8)
					{
						map[8][27] = BLOCK8;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = NU;
						playerPosY += playerSpeed;

					}
				}
				if (map[playerMapY][playerMapX] == NE)
				{
					if (map[playerMapY + 1][playerMapX] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = NE;
						if (map[1][27] != BLOCK1 || map[1][27] == BLOCK1)
						{
							if (map[1][27] == BLOCK1 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK1;
								map[1][27] = YUKA;
							}
						}
						if (map[2][27] != BLOCK22 || map[2][27] == BLOCK22)
						{
							if (map[2][27] == BLOCK22 && map[playerMapY][playerMapX] == map[4][11])
							{
								map[playerMapY][playerMapX] = BLOCK22;
								map[2][27] = YUKA;
							}
						}
						if (map[3][27] != BLOCK3 || map[3][27] == BLOCK3)
						{
							if (map[3][27] == BLOCK3 && map[playerMapY][playerMapX] == map[4][13])
							{
								map[playerMapY][playerMapX] = BLOCK3;
								map[3][27] = YUKA;
							}
						}
						if (map[4][27] != BLOCK4 || map[4][27] == BLOCK4)
						{
							if (map[4][27] == BLOCK4 && map[playerMapY][playerMapX] == map[4][15])
							{
								map[playerMapY][playerMapX] = BLOCK4;
								map[4][27] = YUKA;
							}
						}
						if (map[5][27] != BLOCK5 || map[5][27] == BLOCK5)
						{
							if (map[5][27] == BLOCK5 && map[playerMapY][playerMapX] == map[4][17])
							{
								map[playerMapY][playerMapX] = BLOCK5;
								map[5][27] = YUKA;
							}
						}
						if (map[6][27] != BLOCK6 || map[6][27] == BLOCK6)
						{

							if (map[6][27] == BLOCK6 && map[playerMapY][playerMapX] == /*6以降は後で*/map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK6;
								map[6][27] = YUKA;
							}
						}
						if (map[7][27] != BLOCK7 || map[7][27] == BLOCK7)
						{
							if (map[7][27] == BLOCK7 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK7;
								map[7][27] = YUKA;
							}
						}
						if (map[8][27] != BLOCK8 || map[8][27] == BLOCK8)
						{
							if (map[8][27] == BLOCK8 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK8;
								map[8][27] = YUKA;
							}
						}
						playerPosY += playerSpeed;
					}

					if (map[playerMapY + 1][playerMapX] == BLOCK1)
					{
						map[1][27] = BLOCK1;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = NE;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK22)
					{
						map[2][27] = BLOCK22;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = NE;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK3)
					{
						map[3][27] = BLOCK3;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = NE;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK4)
					{
						map[4][27] = BLOCK4;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = NE;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK5)
					{
						map[5][27] = BLOCK5;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = NE;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK6)
					{
						map[6][27] = BLOCK6;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = NE;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK7)
					{
						map[7][27] = BLOCK7;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = NE;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK8)
					{
						map[8][27] = BLOCK8;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = NE;
						playerPosY += playerSpeed;

					}
				}
				if (map[playerMapY][playerMapX] == MA)
				{
					if (map[playerMapY + 1][playerMapX] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = MA;
						if (map[1][27] != BLOCK1 || map[1][27] == BLOCK1)
						{
							if (map[1][27] == BLOCK1 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK1;
								map[1][27] = YUKA;
							}
						}
						if (map[2][27] != BLOCK22 || map[2][27] == BLOCK22)
						{
							if (map[2][27] == BLOCK22 && map[playerMapY][playerMapX] == map[4][11])
							{
								map[playerMapY][playerMapX] = BLOCK22;
								map[2][27] = YUKA;
							}
						}
						if (map[3][27] != BLOCK3 || map[3][27] == BLOCK3)
						{
							if (map[3][27] == BLOCK3 && map[playerMapY][playerMapX] == map[4][13])
							{
								map[playerMapY][playerMapX] = BLOCK3;
								map[3][27] = YUKA;
							}
						}
						if (map[4][27] != BLOCK4 || map[4][27] == BLOCK4)
						{
							if (map[4][27] == BLOCK4 && map[playerMapY][playerMapX] == map[4][15])
							{
								map[playerMapY][playerMapX] = BLOCK4;
								map[4][27] = YUKA;
							}
						}
						if (map[5][27] != BLOCK5 || map[5][27] == BLOCK5)
						{
							if (map[5][27] == BLOCK5 && map[playerMapY][playerMapX] == map[4][17])
							{
								map[playerMapY][playerMapX] = BLOCK5;
								map[5][27] = YUKA;
							}
						}
						if (map[6][27] != BLOCK6 || map[6][27] == BLOCK6)
						{

							if (map[6][27] == BLOCK6 && map[playerMapY][playerMapX] == /*6以降は後で*/map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK6;
								map[6][27] = YUKA;
							}
						}
						if (map[7][27] != BLOCK7 || map[7][27] == BLOCK7)
						{
							if (map[7][27] == BLOCK7 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK7;
								map[7][27] = YUKA;
							}
						}
						if (map[8][27] != BLOCK8 || map[8][27] == BLOCK8)
						{
							if (map[8][27] == BLOCK8 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK8;
								map[8][27] = YUKA;
							}
						}
						playerPosY += playerSpeed;
					}

					if (map[playerMapY + 1][playerMapX] == BLOCK1)
					{
						map[1][27] = BLOCK1;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = MA;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK22)
					{
						map[2][27] = BLOCK22;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = MA;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK3)
					{
						map[3][27] = BLOCK3;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = MA;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK4)
					{
						map[4][27] = BLOCK4;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = MA;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK5)
					{
						map[5][27] = BLOCK5;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = MA;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK6)
					{
						map[6][27] = BLOCK6;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = MA;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK7)
					{
						map[7][27] = BLOCK7;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = MA;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK8)
					{
						map[8][27] = BLOCK8;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = MA;
						playerPosY += playerSpeed;

					}
				}
				if (map[playerMapY][playerMapX] == YA)
				{
					if (map[playerMapY + 1][playerMapX] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = YA;
						if (map[1][27] != BLOCK1 || map[1][27] == BLOCK1)
						{
							if (map[1][27] == BLOCK1 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK1;
								map[1][27] = YUKA;
							}
						}
						if (map[2][27] != BLOCK22 || map[2][27] == BLOCK22)
						{
							if (map[2][27] == BLOCK22 && map[playerMapY][playerMapX] == map[4][11])
							{
								map[playerMapY][playerMapX] = BLOCK22;
								map[2][27] = YUKA;
							}
						}
						if (map[3][27] != BLOCK3 || map[3][27] == BLOCK3)
						{
							if (map[3][27] == BLOCK3 && map[playerMapY][playerMapX] == map[4][13])
							{
								map[playerMapY][playerMapX] = BLOCK3;
								map[3][27] = YUKA;
							}
						}
						if (map[4][27] != BLOCK4 || map[4][27] == BLOCK4)
						{
							if (map[4][27] == BLOCK4 && map[playerMapY][playerMapX] == map[4][15])
							{
								map[playerMapY][playerMapX] = BLOCK4;
								map[4][27] = YUKA;
							}
						}
						if (map[5][27] != BLOCK5 || map[5][27] == BLOCK5)
						{
							if (map[5][27] == BLOCK5 && map[playerMapY][playerMapX] == map[4][17])
							{
								map[playerMapY][playerMapX] = BLOCK5;
								map[5][27] = YUKA;
							}
						}
						if (map[6][27] != BLOCK6 || map[6][27] == BLOCK6)
						{

							if (map[6][27] == BLOCK6 && map[playerMapY][playerMapX] == /*6以降は後で*/map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK6;
								map[6][27] = YUKA;
							}
						}
						if (map[7][27] != BLOCK7 || map[7][27] == BLOCK7)
						{
							if (map[7][27] == BLOCK7 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK7;
								map[7][27] = YUKA;
							}
						}
						if (map[8][27] != BLOCK8 || map[8][27] == BLOCK8)
						{
							if (map[8][27] == BLOCK8 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK8;
								map[8][27] = YUKA;
							}
						}
						playerPosY += playerSpeed;
					}

					if (map[playerMapY + 1][playerMapX] == BLOCK1)
					{
						map[1][27] = BLOCK1;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = YA;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK22)
					{
						map[2][27] = BLOCK22;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = YA;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK3)
					{
						map[3][27] = BLOCK3;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = YA;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK4)
					{
						map[4][27] = BLOCK4;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = YA;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK5)
					{
						map[5][27] = BLOCK5;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = YA;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK6)
					{
						map[6][27] = BLOCK6;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = YA;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK7)
					{
						map[7][27] = BLOCK7;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = YA;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK8)
					{
						map[8][27] = BLOCK8;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = YA;
						playerPosY += playerSpeed;

					}
				}
				if (map[playerMapY][playerMapX] == RI)
				{
					if (map[playerMapY + 1][playerMapX] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = RI;
						if (map[1][27] != BLOCK1 || map[1][27] == BLOCK1)
						{
							if (map[1][27] == BLOCK1 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK1;
								map[1][27] = YUKA;
							}
						}
						if (map[2][27] != BLOCK22 || map[2][27] == BLOCK22)
						{
							if (map[2][27] == BLOCK22 && map[playerMapY][playerMapX] == map[4][11])
							{
								map[playerMapY][playerMapX] = BLOCK22;
								map[2][27] = YUKA;
							}
						}
						if (map[3][27] != BLOCK3 || map[3][27] == BLOCK3)
						{
							if (map[3][27] == BLOCK3 && map[playerMapY][playerMapX] == map[4][13])
							{
								map[playerMapY][playerMapX] = BLOCK3;
								map[3][27] = YUKA;
							}
						}
						if (map[4][27] != BLOCK4 || map[4][27] == BLOCK4)
						{
							if (map[4][27] == BLOCK4 && map[playerMapY][playerMapX] == map[4][15])
							{
								map[playerMapY][playerMapX] = BLOCK4;
								map[4][27] = YUKA;
							}
						}
						if (map[5][27] != BLOCK5 || map[5][27] == BLOCK5)
						{
							if (map[5][27] == BLOCK5 && map[playerMapY][playerMapX] == map[4][17])
							{
								map[playerMapY][playerMapX] = BLOCK5;
								map[5][27] = YUKA;
							}
						}
						if (map[6][27] != BLOCK6 || map[6][27] == BLOCK6)
						{

							if (map[6][27] == BLOCK6 && map[playerMapY][playerMapX] == /*6以降は後で*/map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK6;
								map[6][27] = YUKA;
							}
						}
						if (map[7][27] != BLOCK7 || map[7][27] == BLOCK7)
						{
							if (map[7][27] == BLOCK7 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK7;
								map[7][27] = YUKA;
							}
						}
						if (map[8][27] != BLOCK8 || map[8][27] == BLOCK8)
						{
							if (map[8][27] == BLOCK8 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK8;
								map[8][27] = YUKA;
							}
						}
						playerPosY += playerSpeed;
					}

					if (map[playerMapY + 1][playerMapX] == BLOCK1)
					{
						map[1][27] = BLOCK1;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = RI;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK22)
					{
						map[2][27] = BLOCK22;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = RI;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK3)
					{
						map[3][27] = BLOCK3;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = RI;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK4)
					{
						map[4][27] = BLOCK4;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = RI;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK5)
					{
						map[5][27] = BLOCK5;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = RI;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK6)
					{
						map[6][27] = BLOCK6;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = RI;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK7)
					{
						map[7][27] = BLOCK7;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = RI;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK8)
					{
						map[8][27] = BLOCK8;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = RI;
						playerPosY += playerSpeed;

					}
				}
				if (map[playerMapY][playerMapX] == RU)
				{
					if (map[playerMapY + 1][playerMapX] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = RU;
						if (map[1][27] != BLOCK1 || map[1][27] == BLOCK1)
						{
							if (map[1][27] == BLOCK1 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK1;
								map[1][27] = YUKA;
							}
						}
						if (map[2][27] != BLOCK22 || map[2][27] == BLOCK22)
						{
							if (map[2][27] == BLOCK22 && map[playerMapY][playerMapX] == map[4][11])
							{
								map[playerMapY][playerMapX] = BLOCK22;
								map[2][27] = YUKA;
							}
						}
						if (map[3][27] != BLOCK3 || map[3][27] == BLOCK3)
						{
							if (map[3][27] == BLOCK3 && map[playerMapY][playerMapX] == map[4][13])
							{
								map[playerMapY][playerMapX] = BLOCK3;
								map[3][27] = YUKA;
							}
						}
						if (map[4][27] != BLOCK4 || map[4][27] == BLOCK4)
						{
							if (map[4][27] == BLOCK4 && map[playerMapY][playerMapX] == map[4][15])
							{
								map[playerMapY][playerMapX] = BLOCK4;
								map[4][27] = YUKA;
							}
						}
						if (map[5][27] != BLOCK5 || map[5][27] == BLOCK5)
						{
							if (map[5][27] == BLOCK5 && map[playerMapY][playerMapX] == map[4][17])
							{
								map[playerMapY][playerMapX] = BLOCK5;
								map[5][27] = YUKA;
							}
						}
						if (map[6][27] != BLOCK6 || map[6][27] == BLOCK6)
						{

							if (map[6][27] == BLOCK6 && map[playerMapY][playerMapX] == /*6以降は後で*/map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK6;
								map[6][27] = YUKA;
							}
						}
						if (map[7][27] != BLOCK7 || map[7][27] == BLOCK7)
						{
							if (map[7][27] == BLOCK7 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK7;
								map[7][27] = YUKA;
							}
						}
						if (map[8][27] != BLOCK8 || map[8][27] == BLOCK8)
						{
							if (map[8][27] == BLOCK8 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK8;
								map[8][27] = YUKA;
							}
						}
						playerPosY += playerSpeed;
					}

					if (map[playerMapY + 1][playerMapX] == BLOCK1)
					{
						map[1][27] = BLOCK1;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = RU;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK22)
					{
						map[2][27] = BLOCK22;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = RU;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK3)
					{
						map[3][27] = BLOCK3;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = RU;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK4)
					{
						map[4][27] = BLOCK4;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = RU;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK5)
					{
						map[5][27] = BLOCK5;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = RU;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK6)
					{
						map[6][27] = BLOCK6;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = RU;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK7)
					{
						map[7][27] = BLOCK7;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = RU;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK8)
					{
						map[8][27] = BLOCK8;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = RU;
						playerPosY += playerSpeed;

					}
				}
				if (map[playerMapY][playerMapX] == WA)
				{
					if (map[playerMapY + 1][playerMapX] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = WA;
						if (map[1][27] != BLOCK1 || map[1][27] == BLOCK1)
						{
							if (map[1][27] == BLOCK1 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK1;
								map[1][27] = YUKA;
							}
						}
						if (map[2][27] != BLOCK22 || map[2][27] == BLOCK22)
						{
							if (map[2][27] == BLOCK22 && map[playerMapY][playerMapX] == map[4][11])
							{
								map[playerMapY][playerMapX] = BLOCK22;
								map[2][27] = YUKA;
							}
						}
						if (map[3][27] != BLOCK3 || map[3][27] == BLOCK3)
						{
							if (map[3][27] == BLOCK3 && map[playerMapY][playerMapX] == map[4][13])
							{
								map[playerMapY][playerMapX] = BLOCK3;
								map[3][27] = YUKA;
							}
						}
						if (map[4][27] != BLOCK4 || map[4][27] == BLOCK4)
						{
							if (map[4][27] == BLOCK4 && map[playerMapY][playerMapX] == map[4][15])
							{
								map[playerMapY][playerMapX] = BLOCK4;
								map[4][27] = YUKA;
							}
						}
						if (map[5][27] != BLOCK5 || map[5][27] == BLOCK5)
						{
							if (map[5][27] == BLOCK5 && map[playerMapY][playerMapX] == map[4][17])
							{
								map[playerMapY][playerMapX] = BLOCK5;
								map[5][27] = YUKA;
							}
						}
						if (map[6][27] != BLOCK6 || map[6][27] == BLOCK6)
						{

							if (map[6][27] == BLOCK6 && map[playerMapY][playerMapX] == /*6以降は後で*/map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK6;
								map[6][27] = YUKA;
							}
						}
						if (map[7][27] != BLOCK7 || map[7][27] == BLOCK7)
						{
							if (map[7][27] == BLOCK7 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK7;
								map[7][27] = YUKA;
							}
						}
						if (map[8][27] != BLOCK8 || map[8][27] == BLOCK8)
						{
							if (map[8][27] == BLOCK8 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK8;
								map[8][27] = YUKA;
							}
						}
						playerPosY += playerSpeed;
					}

					if (map[playerMapY + 1][playerMapX] == BLOCK1)
					{
						map[1][27] = BLOCK1;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = WA;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK22)
					{
						map[2][27] = BLOCK22;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = WA;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK3)
					{
						map[3][27] = BLOCK3;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = WA;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK4)
					{
						map[4][27] = BLOCK4;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = WA;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK5)
					{
						map[5][27] = BLOCK5;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = WA;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK6)
					{
						map[6][27] = BLOCK6;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = WA;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK7)
					{
						map[7][27] = BLOCK7;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = WA;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK8)
					{
						map[8][27] = BLOCK8;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = WA;
						playerPosY += playerSpeed;

					}
				}
				if (map[playerMapY][playerMapX] == NN)
				{
					if (map[playerMapY + 1][playerMapX] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = NN;
						if (map[1][27] != BLOCK1 || map[1][27] == BLOCK1)
						{
							if (map[1][27] == BLOCK1 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK1;
								map[1][27] = YUKA;
							}
						}
						if (map[2][27] != BLOCK22 || map[2][27] == BLOCK22)
						{
							if (map[2][27] == BLOCK22 && map[playerMapY][playerMapX] == map[4][11])
							{
								map[playerMapY][playerMapX] = BLOCK22;
								map[2][27] = YUKA;
							}
						}
						if (map[3][27] != BLOCK3 || map[3][27] == BLOCK3)
						{
							if (map[3][27] == BLOCK3 && map[playerMapY][playerMapX] == map[4][13])
							{
								map[playerMapY][playerMapX] = BLOCK3;
								map[3][27] = YUKA;
							}
						}
						if (map[4][27] != BLOCK4 || map[4][27] == BLOCK4)
						{
							if (map[4][27] == BLOCK4 && map[playerMapY][playerMapX] == map[4][15])
							{
								map[playerMapY][playerMapX] = BLOCK4;
								map[4][27] = YUKA;
							}
						}
						if (map[5][27] != BLOCK5 || map[5][27] == BLOCK5)
						{
							if (map[5][27] == BLOCK5 && map[playerMapY][playerMapX] == map[4][17])
							{
								map[playerMapY][playerMapX] = BLOCK5;
								map[5][27] = YUKA;
							}
						}
						if (map[6][27] != BLOCK6 || map[6][27] == BLOCK6)
						{

							if (map[6][27] == BLOCK6 && map[playerMapY][playerMapX] == /*6以降は後で*/map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK6;
								map[6][27] = YUKA;
							}
						}
						if (map[7][27] != BLOCK7 || map[7][27] == BLOCK7)
						{
							if (map[7][27] == BLOCK7 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK7;
								map[7][27] = YUKA;
							}
						}
						if (map[8][27] != BLOCK8 || map[8][27] == BLOCK8)
						{
							if (map[8][27] == BLOCK8 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK8;
								map[8][27] = YUKA;
							}
						}
						playerPosY += playerSpeed;
					}

					if (map[playerMapY + 1][playerMapX] == BLOCK1)
					{
						map[1][27] = BLOCK1;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = NN;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK22)
					{
						map[2][27] = BLOCK22;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = NN;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK3)
					{
						map[3][27] = BLOCK3;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = NN;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK4)
					{
						map[4][27] = BLOCK4;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = NN;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK5)
					{
						map[5][27] = BLOCK5;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = NN;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK6)
					{
						map[6][27] = BLOCK6;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = NN;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK7)
					{
						map[7][27] = BLOCK7;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = NN;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK8)
					{
						map[8][27] = BLOCK8;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = NN;
						playerPosY += playerSpeed;

					}
				}
				if (map[playerMapY][playerMapX] == GI)
				{
					if (map[playerMapY + 1][playerMapX] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = GI;
						if (map[1][27] != BLOCK1 || map[1][27] == BLOCK1)
						{
							if (map[1][27] == BLOCK1 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK1;
								map[1][27] = YUKA;
							}
						}
						if (map[2][27] != BLOCK22 || map[2][27] == BLOCK22)
						{
							if (map[2][27] == BLOCK22 && map[playerMapY][playerMapX] == map[4][11])
							{
								map[playerMapY][playerMapX] = BLOCK22;
								map[2][27] = YUKA;
							}
						}
						if (map[3][27] != BLOCK3 || map[3][27] == BLOCK3)
						{
							if (map[3][27] == BLOCK3 && map[playerMapY][playerMapX] == map[4][13])
							{
								map[playerMapY][playerMapX] = BLOCK3;
								map[3][27] = YUKA;
							}
						}
						if (map[4][27] != BLOCK4 || map[4][27] == BLOCK4)
						{
							if (map[4][27] == BLOCK4 && map[playerMapY][playerMapX] == map[4][15])
							{
								map[playerMapY][playerMapX] = BLOCK4;
								map[4][27] = YUKA;
							}
						}
						if (map[5][27] != BLOCK5 || map[5][27] == BLOCK5)
						{
							if (map[5][27] == BLOCK5 && map[playerMapY][playerMapX] == map[4][17])
							{
								map[playerMapY][playerMapX] = BLOCK5;
								map[5][27] = YUKA;
							}
						}
						if (map[6][27] != BLOCK6 || map[6][27] == BLOCK6)
						{

							if (map[6][27] == BLOCK6 && map[playerMapY][playerMapX] == /*6以降は後で*/map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK6;
								map[6][27] = YUKA;
							}
						}
						if (map[7][27] != BLOCK7 || map[7][27] == BLOCK7)
						{
							if (map[7][27] == BLOCK7 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK7;
								map[7][27] = YUKA;
							}
						}
						if (map[8][27] != BLOCK8 || map[8][27] == BLOCK8)
						{
							if (map[8][27] == BLOCK8 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK8;
								map[8][27] = YUKA;
							}
						}
						playerPosY += playerSpeed;
					}

					if (map[playerMapY + 1][playerMapX] == BLOCK1)
					{
						map[1][27] = BLOCK1;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = GI;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK22)
					{
						map[2][27] = BLOCK22;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = GI;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK3)
					{
						map[3][27] = BLOCK3;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = GI;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK4)
					{
						map[4][27] = BLOCK4;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = GI;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK5)
					{
						map[5][27] = BLOCK5;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = GI;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK6)
					{
						map[6][27] = BLOCK6;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = GI;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK7)
					{
						map[7][27] = BLOCK7;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = GI;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK8)
					{
						map[8][27] = BLOCK8;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = GI;
						playerPosY += playerSpeed;

					}
				}
				if (map[playerMapY][playerMapX] == ZO)
				{
					if (map[playerMapY + 1][playerMapX] == YUKA)
					{
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = ZO;
						if (map[1][27] != BLOCK1 || map[1][27] == BLOCK1)
						{
							if (map[1][27] == BLOCK1 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK1;
								map[1][27] = YUKA;
							}
						}
						if (map[2][27] != BLOCK22 || map[2][27] == BLOCK22)
						{
							if (map[2][27] == BLOCK22 && map[playerMapY][playerMapX] == map[4][11])
							{
								map[playerMapY][playerMapX] = BLOCK22;
								map[2][27] = YUKA;
							}
						}
						if (map[3][27] != BLOCK3 || map[3][27] == BLOCK3)
						{
							if (map[3][27] == BLOCK3 && map[playerMapY][playerMapX] == map[4][13])
							{
								map[playerMapY][playerMapX] = BLOCK3;
								map[3][27] = YUKA;
							}
						}
						if (map[4][27] != BLOCK4 || map[4][27] == BLOCK4)
						{
							if (map[4][27] == BLOCK4 && map[playerMapY][playerMapX] == map[4][15])
							{
								map[playerMapY][playerMapX] = BLOCK4;
								map[4][27] = YUKA;
							}
						}
						if (map[5][27] != BLOCK5 || map[5][27] == BLOCK5)
						{
							if (map[5][27] == BLOCK5 && map[playerMapY][playerMapX] == map[4][17])
							{
								map[playerMapY][playerMapX] = BLOCK5;
								map[5][27] = YUKA;
							}
						}
						if (map[6][27] != BLOCK6 || map[6][27] == BLOCK6)
						{

							if (map[6][27] == BLOCK6 && map[playerMapY][playerMapX] == /*6以降は後で*/map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK6;
								map[6][27] = YUKA;
							}
						}
						if (map[7][27] != BLOCK7 || map[7][27] == BLOCK7)
						{
							if (map[7][27] == BLOCK7 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK7;
								map[7][27] = YUKA;
							}
						}
						if (map[8][27] != BLOCK8 || map[8][27] == BLOCK8)
						{
							if (map[8][27] == BLOCK8 && map[playerMapY][playerMapX] == map[4][9])
							{
								map[playerMapY][playerMapX] = BLOCK8;
								map[8][27] = YUKA;
							}
						}
						playerPosY += playerSpeed;
					}
					if (map[playerMapY + 1][playerMapX] == BLOCK1)
					{
						map[1][27] = BLOCK1;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = ZO;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK22)
					{
						map[2][27] = BLOCK22;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = ZO;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK3)
					{
						map[3][27] = BLOCK3;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = ZO;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK4)
					{
						map[4][27] = BLOCK4;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = ZO;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK5)
					{
						map[5][27] = BLOCK5;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = ZO;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK6)
					{
						map[6][27] = BLOCK6;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = ZO;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK7)
					{
						map[7][27] = BLOCK7;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = ZO;
						playerPosY += playerSpeed;

					}
					if (map[playerMapY + 1][playerMapX] == BLOCK8)
					{
						map[8][27] = BLOCK8;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = ZO;
						playerPosY += playerSpeed;

					}
				}

			}

			//状態変化--------------------------------------------------------------------------------------------------



			//ゴール条件---------------------------------


			// 解答が合ってたらクリアフラグがtrueになる
			if (map[4][9] == I)
			{
				if (map[4][11] == NU)
				{
					isClearFlag = true;
				}
			}

			// ステージ遷移　解答のシーンを作る予定
			//if (map[playerMapY][playerMapX] == GOAL && isClearFlag == true/* && keys[DIK_SPACE] && preKeys[DIK_SPACE] == 0*/)
			//{
			//	sceneNo = GAMECLEAR;
			//}

			if (map[playerMapY][playerMapX] == GOAL)
			{
				goalTimer--;
				playerSpeed = 0;
				if (goalTimer == 0)
				{
					sceneNo = GAMECLEAR;
				}
			}

			/*	if (map[playerMapY][playerMapX] == THORN)
				{
					deathTimer--;
					playerSpeed = 0;
					if (deathTimer == 0)
					{
						sceneNo = GAMEOVER;
					}
				}*/
			break;

		case STAGE2:
			//マップ情報-----------------------------------------------------------------------------------
			playerMapX = playerPosX / KBlockSize;//map[x][]
			playerMapY = playerPosY / KBlockSize;//map[][y]

			blockMapX = blockPosX / KBlockSize;
			blockMapY = blockPosY / KBlockSize;

			//リスタート
			if (keys[DIK_R] && preKeys[DIK_R] == 0)
			{
				goalTimer = 60;//初期化
				deathTimer = 60;
				playerPosX = 1 * KBlockSize;//プレイヤーの位置
				playerPosY = 20 * KBlockSize;
				playerSpeed = KBlockSize;
				for (int y = 0; y < mapCountY2; y++)
				{
					for (int x = 0; x < mapCountX2; x++)
					{
						map2[y][x] = mapFormat2[y][x];
					}
				}
			}

			//プレイヤー移動-------------------------------------------------------------------------------
			if (keys[DIK_W] && preKeys[DIK_W] == 0 || keys[DIK_UP] && preKeys[DIK_UP] == 0)
			{

				playerTmpY = playerPosY - playerSpeed;
				playerMapY = playerTmpY / KBlockSize;
				//何もないから実際に進ませる
				if (map2[playerMapY][playerMapX] == YUKA)
				{
					playerPosY -= playerSpeed;
				}
				if (map2[playerMapY][playerMapX] == BLOCK1)
				{
					playerPosY -= playerSpeed;
				}
				if (map2[playerMapY][playerMapX] == GOAL)
				{
					playerPosY -= playerSpeed;
				}
				if (map2[playerMapY][playerMapX] == THORN)
				{
					playerPosY -= playerSpeed;
				}

				if (map2[playerMapY][playerMapX] == U)
				{
					if (map2[playerMapY - 1][playerMapX] == YUKA)
					{
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = U;
						if (map2[1][27] != BLOCK1 || map2[1][27] == BLOCK1)
						{
							if (map2[1][27] == BLOCK1 && map2[playerMapY][playerMapX] == map[4][7])
							{
								map2[playerMapY][playerMapX] = BLOCK1;
								map2[1][27] = YUKA;
							}
						}
						if (map2[2][27] != BLOCK22 || map2[2][27] == BLOCK22)
						{
							if (map2[2][27] == BLOCK22 && map2[playerMapY][playerMapX] == map2[4][9])
							{
								map2[playerMapY][playerMapX] = BLOCK22;
								map2[2][27] = YUKA;
							}
						}//
						if (map2[3][27] != BLOCK3 || map2[3][27] == BLOCK3)
						{
							if (map2[3][27] == BLOCK3 && map2[playerMapY][playerMapX] == map2[4][11])
							{
								map2[playerMapY][playerMapX] = BLOCK3;
								map2[3][27] = YUKA;
							}
						}
						if (map2[4][27] != BLOCK4 || map2[4][27] == BLOCK4)
						{
							if (map2[4][27] == BLOCK4 && map2[playerMapY][playerMapX] == map2[4][13])
							{
								map2[playerMapY][playerMapX] = BLOCK4;
								map2[4][27] = YUKA;
							}
						}
						if (map2[5][27] != BLOCK5 || map2[5][27] == BLOCK5)
						{
							if (map2[5][27] == BLOCK5 && map2[playerMapY][playerMapX] == map2[4][15])
							{
								map2[playerMapY][playerMapX] = BLOCK5;
								map2[5][27] = YUKA;
							}
						}
						if (map2[6][27] != BLOCK6 || map2[6][27] == BLOCK6)
						{

							if (map2[6][27] == BLOCK6 && map2[playerMapY][playerMapX] == /*6以降は後で*/map2[4][17])
							{
								map2[playerMapY][playerMapX] = BLOCK6;
								map2[6][27] = YUKA;
							}
						}
						if (map2[7][27] != BLOCK7 || map2[7][27] == BLOCK7)
						{
							if (map2[7][27] == BLOCK7 && map2[playerMapY][playerMapX] == map2[4][19])
							{
								map2[playerMapY][playerMapX] = BLOCK7;
								map2[7][27] = YUKA;
							}
						}
						if (map2[8][27] != BLOCK8 || map2[8][27] == BLOCK8)
						{
							if (map2[8][27] == BLOCK8 && map2[playerMapY][playerMapX] == map2[4][21])
							{
								map2[playerMapY][playerMapX] = BLOCK8;
								map2[8][27] = YUKA;
							}
						}
						playerPosY -= playerSpeed;
					}

					if (map2[playerMapY - 1][playerMapX] == BLOCK1)
					{
						map2[1][27] = BLOCK1;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = U;
						playerPosY -= playerSpeed;

					}

					if (map2[playerMapY - 1][playerMapX] == BLOCK22)
					{
						map2[2][27] = BLOCK22;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = U;
						playerPosY -= playerSpeed;

					}
					if (map2[playerMapY - 1][playerMapX] == BLOCK3)
					{
						map2[3][27] = BLOCK3;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = U;
						playerPosY -= playerSpeed;

					}
					if (map2[playerMapY - 1][playerMapX] == BLOCK4)
					{
						map2[4][27] = BLOCK4;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = U;
						playerPosY -= playerSpeed;

					}
					if (map2[playerMapY - 1][playerMapX] == BLOCK5)
					{
						map2[5][27] = BLOCK5;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = U;
						playerPosY -= playerSpeed;

					}
					if (map2[playerMapY - 1][playerMapX] == BLOCK6)
					{
						map2[6][27] = BLOCK6;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = U;
						playerPosY -= playerSpeed;

					}
					if (map2[playerMapY - 1][playerMapX] == BLOCK7)
					{
						map2[7][27] = BLOCK7;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = U;
						playerPosY -= playerSpeed;

					}
					if (map2[playerMapY - 1][playerMapX] == BLOCK8)
					{
						map2[8][27] = BLOCK8;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = U;
						playerPosY -= playerSpeed;

					}



				}
				// 99999999999999999999999999999999999999999999999999
				// ここから直して
				if (map2[playerMapY][playerMapX] == E)
				{
					if (map2[playerMapY - 1][playerMapX] == YUKA)
					{
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = E; //ここをUに変える　したも同じ
						if (map2[1][27] != BLOCK1 || map2[1][27] == BLOCK1)
						{
							if (map2[1][27] == BLOCK1 && map2[playerMapY][playerMapX] == map2[4][7])
							{
								map2[playerMapY][playerMapX] = BLOCK1;
								map2[1][27] = YUKA;
							}
						}
						if (map2[2][27] != BLOCK22 || map2[2][27] == BLOCK22)
						{
							if (map2[2][27] == BLOCK22 && map2[playerMapY][playerMapX] == map2[4][9])
							{
								map2[playerMapY][playerMapX] = BLOCK22;
								map2[2][27] = YUKA;
							}
						}
						if (map2[3][27] != BLOCK3 || map2[3][27] == BLOCK3)
						{
							if (map2[3][27] == BLOCK3 && map2[playerMapY][playerMapX] == map2[4][11])
							{
								map2[playerMapY][playerMapX] = BLOCK3;
								map2[3][27] = YUKA;
							}
						}
						if (map2[4][27] != BLOCK4 || map2[4][27] == BLOCK4)
						{
							if (map2[4][27] == BLOCK4 && map2[playerMapY][playerMapX] == map2[4][13])
							{
								map2[playerMapY][playerMapX] = BLOCK4;
								map2[4][27] = YUKA;
							}
						}
						if (map2[5][27] != BLOCK5 || map2[5][27] == BLOCK5)
						{
							if (map2[5][27] == BLOCK5 && map2[playerMapY][playerMapX] == map2[4][15])
							{
								map2[playerMapY][playerMapX] = BLOCK5;
								map2[5][27] = YUKA;
							}
						}
						if (map2[6][27] != BLOCK6 || map2[6][27] == BLOCK6)
						{

							if (map2[6][27] == BLOCK6 && map2[playerMapY][playerMapX] == /*6以降は後で*/map2[4][17])
							{
								map2[playerMapY][playerMapX] = BLOCK6;
								map2[6][27] = YUKA;
							}
						}
						if (map2[7][27] != BLOCK7 || map2[7][27] == BLOCK7)
						{
							if (map2[7][27] == BLOCK7 && map2[playerMapY][playerMapX] == map2[4][19])
							{
								map2[playerMapY][playerMapX] = BLOCK7;
								map2[7][27] = YUKA;
							}
						}
						if (map2[8][27] != BLOCK8 || map2[8][27] == BLOCK8)
						{
							if (map2[8][27] == BLOCK8 && map2[playerMapY][playerMapX] == map2[4][21])
							{
								map2[playerMapY][playerMapX] = BLOCK8;
								map2[8][27] = YUKA;
							}
						}
						playerPosY -= playerSpeed;
					}

					if (map2[playerMapY - 1][playerMapX] == BLOCK1)
					{
						map2[1][27] = BLOCK1;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = E;
						playerPosY -= playerSpeed;

					}
					if (map2[playerMapY - 1][playerMapX] == BLOCK22)
					{
						map2[2][27] = BLOCK22;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = E;
						playerPosY -= playerSpeed;

					}
					if (map2[playerMapY - 1][playerMapX] == BLOCK3)
					{
						map2[3][27] = BLOCK3;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = E;
						playerPosY -= playerSpeed;

					}
					if (map2[playerMapY - 1][playerMapX] == BLOCK4)
					{
						map2[4][27] = BLOCK4;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = E;
						playerPosY -= playerSpeed;

					}
					if (map2[playerMapY - 1][playerMapX] == BLOCK5)
					{
						map2[5][27] = BLOCK5;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = E;
						playerPosY -= playerSpeed;

					}
					if (map2[playerMapY - 1][playerMapX] == BLOCK6)
					{
						map2[6][27] = BLOCK6;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = E;
						playerPosY -= playerSpeed;

					}
					if (map2[playerMapY - 1][playerMapX] == BLOCK7)
					{
						map2[7][27] = BLOCK7;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = E;
						playerPosY -= playerSpeed;

					}
					if (map2[playerMapY - 1][playerMapX] == BLOCK8)
					{
						map2[8][27] = BLOCK8;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = E;
						playerPosY -= playerSpeed;

					}
				}
				if (map2[playerMapY][playerMapX] == O)
				{
					if (map2[playerMapY - 1][playerMapX] == YUKA)
					{
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = O;
						if (map2[1][27] != BLOCK1 || map2[1][27] == BLOCK1)
						{
							if (map2[1][27] == BLOCK1 && map2[playerMapY][playerMapX] == map2[4][7])
							{
								map2[playerMapY][playerMapX] = BLOCK1;
								map2[1][27] = YUKA;
							}
						}
						if (map2[2][27] != BLOCK22 || map2[2][27] == BLOCK22)
						{
							if (map2[2][27] == BLOCK22 && map2[playerMapY][playerMapX] == map2[4][9])
							{
								map2[playerMapY][playerMapX] = BLOCK22;
								map2[2][27] = YUKA;
							}
						}
						if (map2[3][27] != BLOCK3 || map2[3][27] == BLOCK3)
						{
							if (map2[3][27] == BLOCK3 && map2[playerMapY][playerMapX] == map2[4][11])
							{
								map2[playerMapY][playerMapX] = BLOCK3;
								map2[3][27] = YUKA;
							}
						}
						if (map2[4][27] != BLOCK4 || map2[4][27] == BLOCK4)
						{
							if (map2[4][27] == BLOCK4 && map2[playerMapY][playerMapX] == map2[4][13])
							{
								map2[playerMapY][playerMapX] = BLOCK4;
								map2[4][27] = YUKA;
							}
						}
						if (map2[5][27] != BLOCK5 || map2[5][27] == BLOCK5)
						{
							if (map2[5][27] == BLOCK5 && map2[playerMapY][playerMapX] == map2[4][15])
							{
								map2[playerMapY][playerMapX] = BLOCK5;
								map2[5][27] = YUKA;
							}
						}
						if (map2[6][27] != BLOCK6 || map2[6][27] == BLOCK6)
						{

							if (map2[6][27] == BLOCK6 && map2[playerMapY][playerMapX] == /*6以降は後で*/map2[4][17])
							{
								map2[playerMapY][playerMapX] = BLOCK6;
								map2[6][27] = YUKA;
							}
						}
						if (map2[7][27] != BLOCK7 || map2[7][27] == BLOCK7)
						{
							if (map2[7][27] == BLOCK7 && map2[playerMapY][playerMapX] == map2[4][19])
							{
								map2[playerMapY][playerMapX] = BLOCK7;
								map2[7][27] = YUKA;
							}
						}
						if (map2[8][27] != BLOCK8 || map2[8][27] == BLOCK8)
						{
							if (map2[8][27] == BLOCK8 && map2[playerMapY][playerMapX] == map2[4][21])
							{
								map2[playerMapY][playerMapX] = BLOCK8;
								map2[8][27] = YUKA;
							}
						}
						playerPosY -= playerSpeed;
					}
					if (map2[playerMapY - 1][playerMapX] == BLOCK1)
					{
						map2[1][27] = BLOCK1;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = O;
						playerPosY -= playerSpeed;

					}
					if (map2[playerMapY - 1][playerMapX] == BLOCK22)
					{
						map2[2][27] = BLOCK22;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = O;
						playerPosY -= playerSpeed;

					}
					if (map2[playerMapY - 1][playerMapX] == BLOCK3)
					{
						map2[3][27] = BLOCK3;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = O;
						playerPosY -= playerSpeed;

					}
					if (map2[playerMapY - 1][playerMapX] == BLOCK4)
					{
						map2[4][27] = BLOCK4;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = O;
						playerPosY -= playerSpeed;

					}
					if (map2[playerMapY - 1][playerMapX] == BLOCK5)
					{
						map2[5][27] = BLOCK5;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = O;
						playerPosY -= playerSpeed;

					}
					if (map2[playerMapY - 1][playerMapX] == BLOCK6)
					{
						map2[6][27] = BLOCK6;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = O;
						playerPosY -= playerSpeed;

					}
					if (map2[playerMapY - 1][playerMapX] == BLOCK7)
					{
						map2[7][27] = BLOCK7;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = O;
						playerPosY -= playerSpeed;

					}
					if (map2[playerMapY - 1][playerMapX] == BLOCK8)
					{
						map2[8][27] = BLOCK8;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = O;
						playerPosY -= playerSpeed;

					}
				}
				if (map2[playerMapY][playerMapX] == KA)
				{
					if (map2[playerMapY - 1][playerMapX] == YUKA)
					{
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = KA;
						if (map2[1][27] != BLOCK1 || map2[1][27] == BLOCK1)
						{
							if (map2[1][27] == BLOCK1 && map2[playerMapY][playerMapX] == map2[4][7])
							{
								map2[playerMapY][playerMapX] = BLOCK1;
								map2[1][27] = YUKA;
							}
						}
						if (map2[2][27] != BLOCK22 || map2[2][27] == BLOCK22)
						{
							if (map2[2][27] == BLOCK22 && map2[playerMapY][playerMapX] == map2[4][9])
							{
								map2[playerMapY][playerMapX] = BLOCK22;
								map2[2][27] = YUKA;
							}
						}
						if (map2[3][27] != BLOCK3 || map2[3][27] == BLOCK3)
						{
							if (map2[3][27] == BLOCK3 && map2[playerMapY][playerMapX] == map2[4][11])
							{
								map2[playerMapY][playerMapX] = BLOCK3;
								map2[3][27] = YUKA;
							}
						}
						if (map2[4][27] != BLOCK4 || map2[4][27] == BLOCK4)
						{
							if (map2[4][27] == BLOCK4 && map2[playerMapY][playerMapX] == map2[4][13])
							{
								map2[playerMapY][playerMapX] = BLOCK4;
								map2[4][27] = YUKA;
							}
						}
						if (map2[5][27] != BLOCK5 || map2[5][27] == BLOCK5)
						{
							if (map2[5][27] == BLOCK5 && map2[playerMapY][playerMapX] == map2[4][15])
							{
								map2[playerMapY][playerMapX] = BLOCK5;
								map2[5][27] = YUKA;
							}
						}
						if (map2[6][27] != BLOCK6 || map2[6][27] == BLOCK6)
						{

							if (map2[6][27] == BLOCK6 && map2[playerMapY][playerMapX] == /*6以降は後で*/map2[4][17])
							{
								map2[playerMapY][playerMapX] = BLOCK6;
								map2[6][27] = YUKA;
							}
						}
						if (map2[7][27] != BLOCK7 || map2[7][27] == BLOCK7)
						{
							if (map2[7][27] == BLOCK7 && map2[playerMapY][playerMapX] == map2[4][19])
							{
								map2[playerMapY][playerMapX] = BLOCK7;
								map2[7][27] = YUKA;
							}
						}
						if (map2[8][27] != BLOCK8 || map2[8][27] == BLOCK8)
						{
							if (map2[8][27] == BLOCK8 && map2[playerMapY][playerMapX] == map2[4][21])
							{
								map2[playerMapY][playerMapX] = BLOCK8;
								map2[8][27] = YUKA;
							}
						}
						playerPosY -= playerSpeed;
					}

					if (map2[playerMapY - 1][playerMapX] == BLOCK1)
					{
						map2[1][27] = BLOCK1;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = KA;
						playerPosY -= playerSpeed;

					}
					if (map2[playerMapY - 1][playerMapX] == BLOCK22)
					{
						map2[2][27] = BLOCK22;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = KA;
						playerPosY -= playerSpeed;

					}
					if (map2[playerMapY - 1][playerMapX] == BLOCK3)
					{
						map2[3][27] = BLOCK3;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = KA;
						playerPosY -= playerSpeed;

					}
					if (map2[playerMapY - 1][playerMapX] == BLOCK4)
					{
						map2[4][27] = BLOCK4;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = KA;
						playerPosY -= playerSpeed;

					}
					if (map2[playerMapY - 1][playerMapX] == BLOCK5)
					{
						map2[5][27] = BLOCK5;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = KA;
						playerPosY -= playerSpeed;

					}
					if (map2[playerMapY - 1][playerMapX] == BLOCK6)
					{
						map2[6][27] = BLOCK6;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = KA;
						playerPosY -= playerSpeed;

					}
					if (map2[playerMapY - 1][playerMapX] == BLOCK7)
					{
						map2[7][27] = BLOCK7;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = KA;
						playerPosY -= playerSpeed;

					}
					if (map2[playerMapY - 1][playerMapX] == BLOCK8)
					{
						map2[8][27] = BLOCK8;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = KA;
						playerPosY -= playerSpeed;

					}
				}
				if (map2[playerMapY][playerMapX] == KU)
				{
					if (map2[playerMapY - 1][playerMapX] == YUKA)
					{
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = KU;
						if (map2[1][27] != BLOCK1 || map2[1][27] == BLOCK1)
						{
							if (map2[1][27] == BLOCK1 && map2[playerMapY][playerMapX] == map2[4][7])
							{
								map2[playerMapY][playerMapX] = BLOCK1;
								map2[1][27] = YUKA;
							}
						}
						if (map2[2][27] != BLOCK22 || map2[2][27] == BLOCK22)
						{
							if (map2[2][27] == BLOCK22 && map2[playerMapY][playerMapX] == map2[4][9])
							{
								map2[playerMapY][playerMapX] = BLOCK22;
								map2[2][27] = YUKA;
							}
						}
						if (map2[3][27] != BLOCK3 || map2[3][27] == BLOCK3)
						{
							if (map2[3][27] == BLOCK3 && map2[playerMapY][playerMapX] == map2[4][11])
							{
								map2[playerMapY][playerMapX] = BLOCK3;
								map2[3][27] = YUKA;
							}
						}
						if (map2[4][27] != BLOCK4 || map2[4][27] == BLOCK4)
						{
							if (map2[4][27] == BLOCK4 && map2[playerMapY][playerMapX] == map2[4][13])
							{
								map2[playerMapY][playerMapX] = BLOCK4;
								map2[4][27] = YUKA;
							}
						}
						if (map2[5][27] != BLOCK5 || map2[5][27] == BLOCK5)
						{
							if (map2[5][27] == BLOCK5 && map2[playerMapY][playerMapX] == map2[4][15])
							{
								map2[playerMapY][playerMapX] = BLOCK5;
								map2[5][27] = YUKA;
							}
						}
						if (map2[6][27] != BLOCK6 || map2[6][27] == BLOCK6)
						{

							if (map2[6][27] == BLOCK6 && map2[playerMapY][playerMapX] == /*6以降は後で*/map2[4][17])
							{
								map2[playerMapY][playerMapX] = BLOCK6;
								map2[6][27] = YUKA;
							}
						}
						if (map2[7][27] != BLOCK7 || map2[7][27] == BLOCK7)
						{
							if (map2[7][27] == BLOCK7 && map2[playerMapY][playerMapX] == map2[4][19])
							{
								map2[playerMapY][playerMapX] = BLOCK7;
								map2[7][27] = YUKA;
							}
						}
						if (map2[8][27] != BLOCK8 || map2[8][27] == BLOCK8)
						{
							if (map2[8][27] == BLOCK8 && map2[playerMapY][playerMapX] == map2[4][21])
							{
								map2[playerMapY][playerMapX] = BLOCK8;
								map2[8][27] = YUKA;
							}
						}
						playerPosY -= playerSpeed;
					}


					if (map2[playerMapY - 1][playerMapX] == BLOCK1)
					{
						map2[1][27] = BLOCK1;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = KU;
						playerPosY -= playerSpeed;

					}

					if (map2[playerMapY - 1][playerMapX] == BLOCK22)
					{
						map2[2][27] = BLOCK22;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = KU;
						playerPosY -= playerSpeed;

					}
					if (map2[playerMapY - 1][playerMapX] == BLOCK3)
					{
						map2[3][27] = BLOCK3;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = KU;
						playerPosY -= playerSpeed;

					}
					if (map2[playerMapY - 1][playerMapX] == BLOCK4)
					{
						map2[4][27] = BLOCK4;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = KU;
						playerPosY -= playerSpeed;

					}
					if (map2[playerMapY - 1][playerMapX] == BLOCK5)
					{
						map2[5][27] = BLOCK5;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = KU;
						playerPosY -= playerSpeed;

					}
					if (map2[playerMapY - 1][playerMapX] == BLOCK6)
					{
						map2[6][27] = BLOCK6;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = KU;
						playerPosY -= playerSpeed;

					}
					if (map2[playerMapY - 1][playerMapX] == BLOCK7)
					{
						map2[7][27] = BLOCK7;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = KU;
						playerPosY -= playerSpeed;

					}
					if (map2[playerMapY - 1][playerMapX] == BLOCK8)
					{
						map2[8][27] = BLOCK8;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = KU;
						playerPosY -= playerSpeed;

					}
				}

				if (map2[playerMapY][playerMapX] == SA)
				{
					if (map2[playerMapY - 1][playerMapX] == YUKA)
					{
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = SA;
						if (map2[1][27] != BLOCK1 || map2[1][27] == BLOCK1)
						{
							if (map2[1][27] == BLOCK1 && map2[playerMapY][playerMapX] == map2[4][7])
							{
								map2[playerMapY][playerMapX] = BLOCK1;
								map2[1][27] = YUKA;
							}
						}
						if (map2[2][27] != BLOCK22 || map2[2][27] == BLOCK22)
						{
							if (map2[2][27] == BLOCK22 && map2[playerMapY][playerMapX] == map2[4][9])
							{
								map2[playerMapY][playerMapX] = BLOCK22;
								map2[2][27] = YUKA;
							}
						}
						if (map2[3][27] != BLOCK3 || map2[3][27] == BLOCK3)
						{
							if (map2[3][27] == BLOCK3 && map2[playerMapY][playerMapX] == map2[4][11])
							{
								map2[playerMapY][playerMapX] = BLOCK3;
								map2[3][27] = YUKA;
							}
						}
						if (map2[4][27] != BLOCK4 || map2[4][27] == BLOCK4)
						{
							if (map2[4][27] == BLOCK4 && map2[playerMapY][playerMapX] == map2[4][13])
							{
								map2[playerMapY][playerMapX] = BLOCK4;
								map2[4][27] = YUKA;
							}
						}
						if (map2[5][27] != BLOCK5 || map2[5][27] == BLOCK5)
						{
							if (map2[5][27] == BLOCK5 && map2[playerMapY][playerMapX] == map2[4][15])
							{
								map2[playerMapY][playerMapX] = BLOCK5;
								map2[5][27] = YUKA;
							}
						}
						if (map2[6][27] != BLOCK6 || map2[6][27] == BLOCK6)
						{

							if (map2[6][27] == BLOCK6 && map2[playerMapY][playerMapX] == /*6以降は後で*/map2[4][17])
							{
								map2[playerMapY][playerMapX] = BLOCK6;
								map2[6][27] = YUKA;
							}
						}
						if (map2[7][27] != BLOCK7 || map2[7][27] == BLOCK7)
						{
							if (map2[7][27] == BLOCK7 && map2[playerMapY][playerMapX] == map2[4][19])
							{
								map2[playerMapY][playerMapX] = BLOCK7;
								map2[7][27] = YUKA;
							}
						}
						if (map2[8][27] != BLOCK8 || map2[8][27] == BLOCK8)
						{
							if (map2[8][27] == BLOCK8 && map2[playerMapY][playerMapX] == map2[4][21])
							{
								map2[playerMapY][playerMapX] = BLOCK8;
								map2[8][27] = YUKA;
							}
						}
						playerPosY -= playerSpeed;
					}


					if (map2[playerMapY - 1][playerMapX] == BLOCK1)
					{
						map2[1][27] = BLOCK1;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = SA;
						playerPosY -= playerSpeed;

					}

					if (map2[playerMapY - 1][playerMapX] == BLOCK22)
					{
						map2[2][27] = BLOCK22;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = SA;
						playerPosY -= playerSpeed;

					}
					if (map2[playerMapY - 1][playerMapX] == BLOCK3)
					{
						map2[3][27] = BLOCK3;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = SA;
						playerPosY -= playerSpeed;

					}
					if (map2[playerMapY - 1][playerMapX] == BLOCK4)
					{
						map2[4][27] = BLOCK4;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = SA;
						playerPosY -= playerSpeed;

					}
					if (map2[playerMapY - 1][playerMapX] == BLOCK5)
					{
						map2[5][27] = BLOCK5;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = SA;
						playerPosY -= playerSpeed;

					}
					if (map2[playerMapY - 1][playerMapX] == BLOCK6)
					{
						map2[6][27] = BLOCK6;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = SA;
						playerPosY -= playerSpeed;

					}
					if (map2[playerMapY - 1][playerMapX] == BLOCK7)
					{
						map2[7][27] = BLOCK7;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = SA;
						playerPosY -= playerSpeed;

					}
					if (map2[playerMapY - 1][playerMapX] == BLOCK8)
					{
						map2[8][27] = BLOCK8;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = SA;
						playerPosY -= playerSpeed;

					}
				}
				if (map2[playerMapY][playerMapX] == SHI)
				{
					if (map2[playerMapY - 1][playerMapX] == YUKA)
					{
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = SHI;
						if (map2[1][27] != BLOCK1 || map2[1][27] == BLOCK1)
						{
							if (map2[1][27] == BLOCK1 && map2[playerMapY][playerMapX] == map2[4][7])
							{
								map2[playerMapY][playerMapX] = BLOCK1;
								map2[1][27] = YUKA;
							}
						}
						if (map2[2][27] != BLOCK22 || map2[2][27] == BLOCK22)
						{
							if (map2[2][27] == BLOCK22 && map2[playerMapY][playerMapX] == map2[4][9])
							{
								map2[playerMapY][playerMapX] = BLOCK22;
								map2[2][27] = YUKA;
							}
						}
						if (map2[3][27] != BLOCK3 || map2[3][27] == BLOCK3)
						{
							if (map2[3][27] == BLOCK3 && map2[playerMapY][playerMapX] == map2[4][11])
							{
								map2[playerMapY][playerMapX] = BLOCK3;
								map2[3][27] = YUKA;
							}
						}
						if (map2[4][27] != BLOCK4 || map2[4][27] == BLOCK4)
						{
							if (map2[4][27] == BLOCK4 && map2[playerMapY][playerMapX] == map2[4][13])
							{
								map2[playerMapY][playerMapX] = BLOCK4;
								map2[4][27] = YUKA;
							}
						}
						if (map2[5][27] != BLOCK5 || map2[5][27] == BLOCK5)
						{
							if (map2[5][27] == BLOCK5 && map2[playerMapY][playerMapX] == map2[4][15])
							{
								map2[playerMapY][playerMapX] = BLOCK5;
								map2[5][27] = YUKA;
							}
						}
						if (map2[6][27] != BLOCK6 || map2[6][27] == BLOCK6)
						{

							if (map2[6][27] == BLOCK6 && map2[playerMapY][playerMapX] == /*6以降は後で*/map2[4][17])
							{
								map2[playerMapY][playerMapX] = BLOCK6;
								map2[6][27] = YUKA;
							}
						}
						if (map2[7][27] != BLOCK7 || map2[7][27] == BLOCK7)
						{
							if (map2[7][27] == BLOCK7 && map2[playerMapY][playerMapX] == map2[4][19])
							{
								map2[playerMapY][playerMapX] = BLOCK7;
								map2[7][27] = YUKA;
							}
						}
						if (map2[8][27] != BLOCK8 || map2[8][27] == BLOCK8)
						{
							if (map2[8][27] == BLOCK8 && map2[playerMapY][playerMapX] == map2[4][21])
							{
								map2[playerMapY][playerMapX] = BLOCK8;
								map2[8][27] = YUKA;
							}
						}
						playerPosY -= playerSpeed;
					}

					if (map2[playerMapY - 1][playerMapX] == BLOCK1)
					{
						map2[1][27] = BLOCK1;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = SHI;
						playerPosY -= playerSpeed;

					}

					if (map2[playerMapY - 1][playerMapX] == BLOCK22)
					{
						map2[2][27] = BLOCK22;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = SHI;
						playerPosY -= playerSpeed;

					}
					if (map2[playerMapY - 1][playerMapX] == BLOCK3)
					{
						map2[3][27] = BLOCK3;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = SHI;
						playerPosY -= playerSpeed;

					}
					if (map2[playerMapY - 1][playerMapX] == BLOCK4)
					{
						map2[4][27] = BLOCK4;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = SHI;
						playerPosY -= playerSpeed;

					}
					if (map2[playerMapY - 1][playerMapX] == BLOCK5)
					{
						map2[5][27] = BLOCK5;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = SHI;
						playerPosY -= playerSpeed;

					}
					if (map2[playerMapY - 1][playerMapX] == BLOCK6)
					{
						map2[6][27] = BLOCK6;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = SHI;
						playerPosY -= playerSpeed;

					}
					if (map2[playerMapY - 1][playerMapX] == BLOCK7)
					{
						map2[7][27] = BLOCK7;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = SHI;
						playerPosY -= playerSpeed;

					}
					if (map2[playerMapY - 1][playerMapX] == BLOCK8)
					{
						map2[8][27] = BLOCK8;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = SHI;
						playerPosY -= playerSpeed;

					}
				}
				if (map2[playerMapY][playerMapX] == SU)
				{
					if (map2[playerMapY - 1][playerMapX] == YUKA)
					{
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = SU;
						if (map2[1][27] != BLOCK1 || map2[1][27] == BLOCK1)
						{
							if (map2[1][27] == BLOCK1 && map2[playerMapY][playerMapX] == map2[4][7])
							{
								map2[playerMapY][playerMapX] = BLOCK1;
								map2[1][27] = YUKA;
							}
						}
						if (map2[2][27] != BLOCK22 || map2[2][27] == BLOCK22)
						{
							if (map2[2][27] == BLOCK22 && map2[playerMapY][playerMapX] == map2[4][9])
							{
								map2[playerMapY][playerMapX] = BLOCK22;
								map2[2][27] = YUKA;
							}
						}
						if (map2[3][27] != BLOCK3 || map2[3][27] == BLOCK3)
						{
							if (map2[3][27] == BLOCK3 && map2[playerMapY][playerMapX] == map2[4][11])
							{
								map2[playerMapY][playerMapX] = BLOCK3;
								map2[3][27] = YUKA;
							}
						}
						if (map2[4][27] != BLOCK4 || map2[4][27] == BLOCK4)
						{
							if (map2[4][27] == BLOCK4 && map2[playerMapY][playerMapX] == map2[4][13])
							{
								map2[playerMapY][playerMapX] = BLOCK4;
								map2[4][27] = YUKA;
							}
						}
						if (map2[5][27] != BLOCK5 || map2[5][27] == BLOCK5)
						{
							if (map2[5][27] == BLOCK5 && map2[playerMapY][playerMapX] == map2[4][15])
							{
								map2[playerMapY][playerMapX] = BLOCK5;
								map2[5][27] = YUKA;
							}
						}
						if (map2[6][27] != BLOCK6 || map2[6][27] == BLOCK6)
						{

							if (map2[6][27] == BLOCK6 && map2[playerMapY][playerMapX] == /*6以降は後で*/map2[4][7])
							{
								map2[playerMapY][playerMapX] = BLOCK6;
								map2[6][27] = YUKA;
							}
						}
						if (map2[7][27] != BLOCK7 || map2[7][27] == BLOCK7)
						{
							if (map2[7][27] == BLOCK7 && map2[playerMapY][playerMapX] == map2[4][7])
							{
								map2[playerMapY][playerMapX] = BLOCK7;
								map2[7][27] = YUKA;
							}
						}
						if (map2[8][27] != BLOCK8 || map2[8][27] == BLOCK8)
						{
							if (map2[8][27] == BLOCK8 && map2[playerMapY][playerMapX] == map2[4][7])
							{
								map2[playerMapY][playerMapX] = BLOCK8;
								map2[8][27] = YUKA;
							}
						}
						playerPosY -= playerSpeed;
					}


					if (map2[playerMapY - 1][playerMapX] == BLOCK1)
					{
						map2[1][27] = BLOCK1;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = SU;
						playerPosY -= playerSpeed;

					}

					if (map2[playerMapY - 1][playerMapX] == BLOCK22)
					{
						map2[2][27] = BLOCK22;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = SU;
						playerPosY -= playerSpeed;

					}
					if (map2[playerMapY - 1][playerMapX] == BLOCK3)
					{
						map2[3][27] = BLOCK3;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = SU;
						playerPosY -= playerSpeed;

					}
					if (map2[playerMapY - 1][playerMapX] == BLOCK4)
					{
						map2[4][27] = BLOCK4;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = SU;
						playerPosY -= playerSpeed;

					}
					if (map2[playerMapY - 1][playerMapX] == BLOCK5)
					{
						map2[5][27] = BLOCK5;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = SU;
						playerPosY -= playerSpeed;

					}
					if (map2[playerMapY - 1][playerMapX] == BLOCK6)
					{
						map2[6][27] = BLOCK6;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = SU;
						playerPosY -= playerSpeed;

					}
					if (map2[playerMapY - 1][playerMapX] == BLOCK7)
					{
						map2[7][27] = BLOCK7;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = SU;
						playerPosY -= playerSpeed;

					}
					if (map2[playerMapY - 1][playerMapX] == BLOCK8)
					{
						map2[8][27] = BLOCK8;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = SU;
						playerPosY -= playerSpeed;

					}
				}
				if (map2[playerMapY][playerMapX] == TO)
				{
					if (map2[playerMapY - 1][playerMapX] == YUKA)
					{
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = TO;
						if (map2[1][27] != BLOCK1 || map2[1][27] == BLOCK1)
						{
							if (map2[1][27] == BLOCK1 && map2[playerMapY][playerMapX] == map2[4][7])
							{
								map2[playerMapY][playerMapX] = BLOCK1;
								map2[1][27] = YUKA;
							}
						}
						if (map2[2][27] != BLOCK22 || map2[2][27] == BLOCK22)
						{
							if (map2[2][27] == BLOCK22 && map2[playerMapY][playerMapX] == map2[4][9])
							{
								map2[playerMapY][playerMapX] = BLOCK22;
								map2[2][27] = YUKA;
							}
						}
						if (map2[3][27] != BLOCK3 || map2[3][27] == BLOCK3)
						{
							if (map2[3][27] == BLOCK3 && map2[playerMapY][playerMapX] == map2[4][11])
							{
								map2[playerMapY][playerMapX] = BLOCK3;
								map2[3][27] = YUKA;
							}
						}
						if (map2[4][27] != BLOCK4 || map2[4][27] == BLOCK4)
						{
							if (map2[4][27] == BLOCK4 && map2[playerMapY][playerMapX] == map2[4][13])
							{
								map2[playerMapY][playerMapX] = BLOCK4;
								map2[4][27] = YUKA;
							}
						}
						if (map2[5][27] != BLOCK5 || map2[5][27] == BLOCK5)
						{
							if (map2[5][27] == BLOCK5 && map2[playerMapY][playerMapX] == map2[4][15])
							{
								map2[playerMapY][playerMapX] = BLOCK5;
								map2[5][27] = YUKA;
							}
						}
						if (map2[6][27] != BLOCK6 || map2[6][27] == BLOCK6)
						{

							if (map2[6][27] == BLOCK6 && map2[playerMapY][playerMapX] == /*6以降は後で*/map2[4][17])
							{
								map2[playerMapY][playerMapX] = BLOCK6;
								map2[6][27] = YUKA;
							}
						}
						if (map2[7][27] != BLOCK7 || map2[7][27] == BLOCK7)
						{
							if (map2[7][27] == BLOCK7 && map2[playerMapY][playerMapX] == map2[4][19])
							{
								map2[playerMapY][playerMapX] = BLOCK7;
								map2[7][27] = YUKA;
							}
						}
						if (map2[8][27] != BLOCK8 || map2[8][27] == BLOCK8)
						{
							if (map2[8][27] == BLOCK8 && map2[playerMapY][playerMapX] == map2[4][21])
							{
								map2[playerMapY][playerMapX] = BLOCK8;
								map2[8][27] = YUKA;
							}
						}
						playerPosY -= playerSpeed;
					}


					if (map2[playerMapY - 1][playerMapX] == BLOCK1)
					{
						map2[1][27] = BLOCK1;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = TO;
						playerPosY -= playerSpeed;

					}

					if (map2[playerMapY - 1][playerMapX] == BLOCK22)
					{
						map2[2][27] = BLOCK22;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = TO;
						playerPosY -= playerSpeed;

					}
					if (map2[playerMapY - 1][playerMapX] == BLOCK3)
					{
						map2[3][27] = BLOCK3;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = TO;
						playerPosY -= playerSpeed;

					}
					if (map2[playerMapY - 1][playerMapX] == BLOCK4)
					{
						map2[4][27] = BLOCK4;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = TO;
						playerPosY -= playerSpeed;

					}
					if (map2[playerMapY - 1][playerMapX] == BLOCK5)
					{
						map2[5][27] = BLOCK5;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = TO;
						playerPosY -= playerSpeed;

					}
					if (map2[playerMapY - 1][playerMapX] == BLOCK6)
					{
						map2[6][27] = BLOCK6;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = TO;
						playerPosY -= playerSpeed;

					}
					if (map2[playerMapY - 1][playerMapX] == BLOCK7)
					{
						map2[7][27] = BLOCK7;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = TO;
						playerPosY -= playerSpeed;

					}
					if (map2[playerMapY - 1][playerMapX] == BLOCK8)
					{
						map2[8][27] = BLOCK8;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = TO;
						playerPosY -= playerSpeed;

					}
				}
				if (map2[playerMapY][playerMapX] == NE)
				{
					if (map2[playerMapY - 1][playerMapX] == YUKA)
					{
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = NE;
						if (map2[1][27] != BLOCK1 || map2[1][27] == BLOCK1)
						{
							if (map2[1][27] == BLOCK1 && map2[playerMapY][playerMapX] == map2[4][7])
							{
								map2[playerMapY][playerMapX] = BLOCK1;
								map2[1][27] = YUKA;
							}
						}
						if (map2[2][27] != BLOCK22 || map2[2][27] == BLOCK22)
						{
							if (map2[2][27] == BLOCK22 && map2[playerMapY][playerMapX] == map2[4][9])
							{
								map2[playerMapY][playerMapX] = BLOCK22;
								map2[2][27] = YUKA;
							}
						}
						if (map2[3][27] != BLOCK3 || map2[3][27] == BLOCK3)
						{
							if (map2[3][27] == BLOCK3 && map2[playerMapY][playerMapX] == map2[4][11])
							{
								map2[playerMapY][playerMapX] = BLOCK3;
								map2[3][27] = YUKA;
							}
						}
						if (map2[4][27] != BLOCK4 || map2[4][27] == BLOCK4)
						{
							if (map2[4][27] == BLOCK4 && map2[playerMapY][playerMapX] == map2[4][13])
							{
								map2[playerMapY][playerMapX] = BLOCK4;
								map2[4][27] = YUKA;
							}
						}
						if (map2[5][27] != BLOCK5 || map2[5][27] == BLOCK5)
						{
							if (map2[5][27] == BLOCK5 && map2[playerMapY][playerMapX] == map2[4][15])
							{
								map2[playerMapY][playerMapX] = BLOCK5;
								map2[5][27] = YUKA;
							}
						}
						if (map2[6][27] != BLOCK6 || map2[6][27] == BLOCK6)
						{

							if (map2[6][27] == BLOCK6 && map2[playerMapY][playerMapX] == /*6以降は後で*/map2[4][17])
							{
								map2[playerMapY][playerMapX] = BLOCK6;
								map2[6][27] = YUKA;
							}
						}
						if (map2[7][27] != BLOCK7 || map2[7][27] == BLOCK7)
						{
							if (map2[7][27] == BLOCK7 && map2[playerMapY][playerMapX] == map2[4][19])
							{
								map2[playerMapY][playerMapX] = BLOCK7;
								map2[7][27] = YUKA;
							}
						}
						if (map2[8][27] != BLOCK8 || map2[8][27] == BLOCK8)
						{
							if (map2[8][27] == BLOCK8 && map2[playerMapY][playerMapX] == map2[4][21])
							{
								map2[playerMapY][playerMapX] = BLOCK8;
								map2[8][27] = YUKA;
							}
						}
						playerPosY -= playerSpeed;
					}


					if (map2[playerMapY - 1][playerMapX] == BLOCK1)
					{
						map2[1][27] = BLOCK1;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = NE;
						playerPosY -= playerSpeed;

					}

					if (map2[playerMapY - 1][playerMapX] == BLOCK22)
					{
						map2[2][27] = BLOCK22;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = NE;
						playerPosY -= playerSpeed;

					}
					if (map2[playerMapY - 1][playerMapX] == BLOCK3)
					{
						map2[3][27] = BLOCK3;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = NE;
						playerPosY -= playerSpeed;

					}
					if (map2[playerMapY - 1][playerMapX] == BLOCK4)
					{
						map2[4][27] = BLOCK4;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = NE;
						playerPosY -= playerSpeed;

					}
					if (map2[playerMapY - 1][playerMapX] == BLOCK5)
					{
						map2[5][27] = BLOCK5;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = NE;
						playerPosY -= playerSpeed;

					}
					if (map2[playerMapY - 1][playerMapX] == BLOCK6)
					{
						map2[6][27] = BLOCK6;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = NE;
						playerPosY -= playerSpeed;

					}
					if (map2[playerMapY - 1][playerMapX] == BLOCK7)
					{
						map2[7][27] = BLOCK7;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = NE;
						playerPosY -= playerSpeed;

					}
					if (map2[playerMapY - 1][playerMapX] == BLOCK8)
					{
						map2[8][27] = BLOCK8;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = NE;
						playerPosY -= playerSpeed;

					}
				}
				if (map2[playerMapY][playerMapX] == FU)
				{
					if (map2[playerMapY - 1][playerMapX] == YUKA)
					{
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = FU;
						if (map2[1][27] != BLOCK1 || map2[1][27] == BLOCK1)
						{
							if (map2[1][27] == BLOCK1 && map2[playerMapY][playerMapX] == map2[4][7])
							{
								map2[playerMapY][playerMapX] = BLOCK1;
								map2[1][27] = YUKA;
							}
						}
						if (map2[2][27] != BLOCK22 || map2[2][27] == BLOCK22)
						{
							if (map2[2][27] == BLOCK22 && map2[playerMapY][playerMapX] == map2[4][9])
							{
								map2[playerMapY][playerMapX] = BLOCK22;
								map2[2][27] = YUKA;
							}
						}
						if (map2[3][27] != BLOCK3 || map2[3][27] == BLOCK3)
						{
							if (map2[3][27] == BLOCK3 && map2[playerMapY][playerMapX] == map2[4][11])
							{
								map2[playerMapY][playerMapX] = BLOCK3;
								map2[3][27] = YUKA;
							}
						}
						if (map2[4][27] != BLOCK4 || map2[4][27] == BLOCK4)
						{
							if (map2[4][27] == BLOCK4 && map2[playerMapY][playerMapX] == map2[4][13])
							{
								map2[playerMapY][playerMapX] = BLOCK4;
								map2[4][27] = YUKA;
							}
						}
						if (map2[5][27] != BLOCK5 || map2[5][27] == BLOCK5)
						{
							if (map2[5][27] == BLOCK5 && map2[playerMapY][playerMapX] == map2[4][15])
							{
								map2[playerMapY][playerMapX] = BLOCK5;
								map2[5][27] = YUKA;
							}
						}
						if (map2[6][27] != BLOCK6 || map2[6][27] == BLOCK6)
						{

							if (map2[6][27] == BLOCK6 && map2[playerMapY][playerMapX] == /*6以降は後で*/map2[4][17])
							{
								map2[playerMapY][playerMapX] = BLOCK6;
								map2[6][27] = YUKA;
							}
						}
						if (map2[7][27] != BLOCK7 || map2[7][27] == BLOCK7)
						{
							if (map2[7][27] == BLOCK7 && map2[playerMapY][playerMapX] == map2[4][19])
							{
								map2[playerMapY][playerMapX] = BLOCK7;
								map2[7][27] = YUKA;
							}
						}
						if (map2[8][27] != BLOCK8 || map2[8][27] == BLOCK8)
						{
							if (map2[8][27] == BLOCK8 && map2[playerMapY][playerMapX] == map2[4][21])
							{
								map2[playerMapY][playerMapX] = BLOCK8;
								map2[8][27] = YUKA;
							}
						}
						playerPosY -= playerSpeed;
					}


					if (map2[playerMapY - 1][playerMapX] == BLOCK1)
					{
						map2[1][27] = BLOCK1;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = FU;
						playerPosY -= playerSpeed;

					}

					if (map2[playerMapY - 1][playerMapX] == BLOCK22)
					{
						map2[2][27] = BLOCK22;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = FU;
						playerPosY -= playerSpeed;

					}
					if (map2[playerMapY - 1][playerMapX] == BLOCK3)
					{
						map2[3][27] = BLOCK3;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = FU;
						playerPosY -= playerSpeed;

					}
					if (map2[playerMapY - 1][playerMapX] == BLOCK4)
					{
						map2[4][27] = BLOCK4;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = FU;
						playerPosY -= playerSpeed;

					}
					if (map2[playerMapY - 1][playerMapX] == BLOCK5)
					{
						map2[5][27] = BLOCK5;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = FU;
						playerPosY -= playerSpeed;

					}
					if (map2[playerMapY - 1][playerMapX] == BLOCK6)
					{
						map2[6][27] = BLOCK6;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = FU;
						playerPosY -= playerSpeed;

					}
					if (map2[playerMapY - 1][playerMapX] == BLOCK7)
					{
						map2[7][27] = BLOCK7;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = FU;
						playerPosY -= playerSpeed;

					}
					if (map2[playerMapY - 1][playerMapX] == BLOCK8)
					{
						map2[8][27] = BLOCK8;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = FU;
						playerPosY -= playerSpeed;

					}
				}

				if (map2[playerMapY][playerMapX] == MU)
				{
					if (map2[playerMapY - 1][playerMapX] == YUKA)
					{
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = MU;
						if (map2[1][27] != BLOCK1 || map2[1][27] == BLOCK1)
						{
							if (map2[1][27] == BLOCK1 && map2[playerMapY][playerMapX] == map2[4][7])
							{
								map2[playerMapY][playerMapX] = BLOCK1;
								map2[1][27] = YUKA;
							}
						}
						if (map2[2][27] != BLOCK22 || map2[2][27] == BLOCK22)
						{
							if (map2[2][27] == BLOCK22 && map2[playerMapY][playerMapX] == map2[4][9])
							{
								map2[playerMapY][playerMapX] = BLOCK22;
								map2[2][27] = YUKA;
							}
						}
						if (map2[3][27] != BLOCK3 || map2[3][27] == BLOCK3)
						{
							if (map2[3][27] == BLOCK3 && map2[playerMapY][playerMapX] == map2[4][11])
							{
								map2[playerMapY][playerMapX] = BLOCK3;
								map2[3][27] = YUKA;
							}
						}
						if (map2[4][27] != BLOCK4 || map2[4][27] == BLOCK4)
						{
							if (map2[4][27] == BLOCK4 && map2[playerMapY][playerMapX] == map2[4][13])
							{
								map2[playerMapY][playerMapX] = BLOCK4;
								map2[4][27] = YUKA;
							}
						}
						if (map2[5][27] != BLOCK5 || map2[5][27] == BLOCK5)
						{
							if (map2[5][27] == BLOCK5 && map2[playerMapY][playerMapX] == map2[4][15])
							{
								map2[playerMapY][playerMapX] = BLOCK5;
								map2[5][27] = YUKA;
							}
						}
						if (map2[6][27] != BLOCK6 || map2[6][27] == BLOCK6)
						{

							if (map2[6][27] == BLOCK6 && map2[playerMapY][playerMapX] == /*6以降は後で*/map2[4][17])
							{
								map2[playerMapY][playerMapX] = BLOCK6;
								map2[6][27] = YUKA;
							}
						}
						if (map2[7][27] != BLOCK7 || map2[7][27] == BLOCK7)
						{
							if (map2[7][27] == BLOCK7 && map2[playerMapY][playerMapX] == map2[4][19])
							{
								map2[playerMapY][playerMapX] = BLOCK7;
								map2[7][27] = YUKA;
							}
						}
						if (map2[8][27] != BLOCK8 || map2[8][27] == BLOCK8)
						{
							if (map2[8][27] == BLOCK8 && map2[playerMapY][playerMapX] == map2[4][21])
							{
								map2[playerMapY][playerMapX] = BLOCK8;
								map2[8][27] = YUKA;
							}
						}
						playerPosY -= playerSpeed;
					}


					if (map2[playerMapY - 1][playerMapX] == BLOCK1)
					{
						map2[1][27] = BLOCK1;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = MU;
						playerPosY -= playerSpeed;

					}

					if (map2[playerMapY - 1][playerMapX] == BLOCK22)
					{
						map2[2][27] = BLOCK22;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = MU;
						playerPosY -= playerSpeed;

					}
					if (map2[playerMapY - 1][playerMapX] == BLOCK3)
					{
						map2[3][27] = BLOCK3;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = MU;
						playerPosY -= playerSpeed;

					}
					if (map2[playerMapY - 1][playerMapX] == BLOCK4)
					{
						map2[4][27] = BLOCK4;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = MU;
						playerPosY -= playerSpeed;

					}
					if (map2[playerMapY - 1][playerMapX] == BLOCK5)
					{
						map2[5][27] = BLOCK5;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = MU;
						playerPosY -= playerSpeed;

					}
					if (map2[playerMapY - 1][playerMapX] == BLOCK6)
					{
						map2[6][27] = BLOCK6;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = MU;
						playerPosY -= playerSpeed;

					}
					if (map2[playerMapY - 1][playerMapX] == BLOCK7)
					{
						map2[7][27] = BLOCK7;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = MU;
						playerPosY -= playerSpeed;

					}
					if (map2[playerMapY - 1][playerMapX] == BLOCK8)
					{
						map2[8][27] = BLOCK8;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = MU;
						playerPosY -= playerSpeed;

					}
				}
				if (map2[playerMapY][playerMapX] == MO)
				{
					if (map2[playerMapY - 1][playerMapX] == YUKA)
					{
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = MO;
						if (map2[1][27] != BLOCK1 || map2[1][27] == BLOCK1)
						{
							if (map2[1][27] == BLOCK1 && map2[playerMapY][playerMapX] == map2[4][7])
							{
								map2[playerMapY][playerMapX] = BLOCK1;
								map2[1][27] = YUKA;
							}
						}
						if (map2[2][27] != BLOCK22 || map2[2][27] == BLOCK22)
						{
							if (map2[2][27] == BLOCK22 && map2[playerMapY][playerMapX] == map2[4][9])
							{
								map2[playerMapY][playerMapX] = BLOCK22;
								map2[2][27] = YUKA;
							}
						}
						if (map2[3][27] != BLOCK3 || map2[3][27] == BLOCK3)
						{
							if (map2[3][27] == BLOCK3 && map2[playerMapY][playerMapX] == map2[4][11])
							{
								map2[playerMapY][playerMapX] = BLOCK3;
								map2[3][27] = YUKA;
							}
						}
						if (map2[4][27] != BLOCK4 || map2[4][27] == BLOCK4)
						{
							if (map2[4][27] == BLOCK4 && map2[playerMapY][playerMapX] == map2[4][13])
							{
								map2[playerMapY][playerMapX] = BLOCK4;
								map2[4][27] = YUKA;
							}
						}
						if (map2[5][27] != BLOCK5 || map2[5][27] == BLOCK5)
						{
							if (map2[5][27] == BLOCK5 && map2[playerMapY][playerMapX] == map2[4][15])
							{
								map2[playerMapY][playerMapX] = BLOCK5;
								map2[5][27] = YUKA;
							}
						}
						if (map2[6][27] != BLOCK6 || map2[6][27] == BLOCK6)
						{

							if (map2[6][27] == BLOCK6 && map2[playerMapY][playerMapX] == /*6以降は後で*/map2[4][17])
							{
								map2[playerMapY][playerMapX] = BLOCK6;
								map2[6][27] = YUKA;
							}
						}
						if (map2[7][27] != BLOCK7 || map2[7][27] == BLOCK7)
						{
							if (map2[7][27] == BLOCK7 && map2[playerMapY][playerMapX] == map2[4][19])
							{
								map2[playerMapY][playerMapX] = BLOCK7;
								map2[7][27] = YUKA;
							}
						}
						if (map2[8][27] != BLOCK8 || map2[8][27] == BLOCK8)
						{
							if (map2[8][27] == BLOCK8 && map2[playerMapY][playerMapX] == map2[4][21])
							{
								map2[playerMapY][playerMapX] = BLOCK8;
								map2[8][27] = YUKA;
							}
						}
						playerPosY -= playerSpeed;
					}


					if (map2[playerMapY - 1][playerMapX] == BLOCK1)
					{
						map2[1][27] = BLOCK1;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = MO;
						playerPosY -= playerSpeed;

					}

					if (map2[playerMapY - 1][playerMapX] == BLOCK22)
					{
						map2[2][27] = BLOCK22;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = MO;
						playerPosY -= playerSpeed;

					}
					if (map2[playerMapY - 1][playerMapX] == BLOCK3)
					{
						map2[3][27] = BLOCK3;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = MO;
						playerPosY -= playerSpeed;

					}
					if (map2[playerMapY - 1][playerMapX] == BLOCK4)
					{
						map2[4][27] = BLOCK4;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = MO;
						playerPosY -= playerSpeed;

					}
					if (map2[playerMapY - 1][playerMapX] == BLOCK5)
					{
						map2[5][27] = BLOCK5;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = MO;
						playerPosY -= playerSpeed;

					}
					if (map2[playerMapY - 1][playerMapX] == BLOCK6)
					{
						map2[6][27] = BLOCK6;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = MO;
						playerPosY -= playerSpeed;

					}
					if (map2[playerMapY - 1][playerMapX] == BLOCK7)
					{
						map2[7][27] = BLOCK7;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = MO;
						playerPosY -= playerSpeed;

					}
					if (map2[playerMapY - 1][playerMapX] == BLOCK8)
					{
						map2[8][27] = BLOCK8;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = MO;
						playerPosY -= playerSpeed;

					}
				}
				if (map2[playerMapY][playerMapX] == YO)
				{
					if (map2[playerMapY - 1][playerMapX] == YUKA)
					{
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = YO;
						if (map2[1][27] != BLOCK1 || map2[1][27] == BLOCK1)
						{
							if (map2[1][27] == BLOCK1 && map2[playerMapY][playerMapX] == map2[4][7])
							{
								map2[playerMapY][playerMapX] = BLOCK1;
								map2[1][27] = YUKA;
							}
						}
						if (map2[2][27] != BLOCK22 || map2[2][27] == BLOCK22)
						{
							if (map2[2][27] == BLOCK22 && map2[playerMapY][playerMapX] == map2[4][9])
							{
								map2[playerMapY][playerMapX] = BLOCK22;
								map2[2][27] = YUKA;
							}
						}
						if (map2[3][27] != BLOCK3 || map2[3][27] == BLOCK3)
						{
							if (map2[3][27] == BLOCK3 && map2[playerMapY][playerMapX] == map2[4][11])
							{
								map2[playerMapY][playerMapX] = BLOCK3;
								map2[3][27] = YUKA;
							}
						}
						if (map2[4][27] != BLOCK4 || map2[4][27] == BLOCK4)
						{
							if (map2[4][27] == BLOCK4 && map2[playerMapY][playerMapX] == map2[4][13])
							{
								map2[playerMapY][playerMapX] = BLOCK4;
								map2[4][27] = YUKA;
							}
						}
						if (map2[5][27] != BLOCK5 || map2[5][27] == BLOCK5)
						{
							if (map2[5][27] == BLOCK5 && map2[playerMapY][playerMapX] == map2[4][15])
							{
								map2[playerMapY][playerMapX] = BLOCK5;
								map2[5][27] = YUKA;
							}
						}
						if (map2[6][27] != BLOCK6 || map2[6][27] == BLOCK6)
						{

							if (map2[6][27] == BLOCK6 && map2[playerMapY][playerMapX] == /*6以降は後で*/map2[4][17])
							{
								map2[playerMapY][playerMapX] = BLOCK6;
								map2[6][27] = YUKA;
							}
						}
						if (map2[7][27] != BLOCK7 || map2[7][27] == BLOCK7)
						{
							if (map2[7][27] == BLOCK7 && map2[playerMapY][playerMapX] == map2[4][19])
							{
								map2[playerMapY][playerMapX] = BLOCK7;
								map2[7][27] = YUKA;
							}
						}
						if (map2[8][27] != BLOCK8 || map2[8][27] == BLOCK8)
						{
							if (map2[8][27] == BLOCK8 && map2[playerMapY][playerMapX] == map2[4][21])
							{
								map2[playerMapY][playerMapX] = BLOCK8;
								map2[8][27] = YUKA;
							}
						}
						playerPosY -= playerSpeed;
					}


					if (map2[playerMapY - 1][playerMapX] == BLOCK1)
					{
						map2[1][27] = BLOCK1;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = YO;
						playerPosY -= playerSpeed;

					}

					if (map2[playerMapY - 1][playerMapX] == BLOCK22)
					{
						map2[2][27] = BLOCK22;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = YO;
						playerPosY -= playerSpeed;

					}
					if (map2[playerMapY - 1][playerMapX] == BLOCK3)
					{
						map2[3][27] = BLOCK3;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = YO;
						playerPosY -= playerSpeed;

					}
					if (map2[playerMapY - 1][playerMapX] == BLOCK4)
					{
						map2[4][27] = BLOCK4;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = YO;
						playerPosY -= playerSpeed;

					}
					if (map2[playerMapY - 1][playerMapX] == BLOCK5)
					{
						map2[5][27] = BLOCK5;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = YO;
						playerPosY -= playerSpeed;

					}
					if (map2[playerMapY - 1][playerMapX] == BLOCK6)
					{
						map2[6][27] = BLOCK6;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = YO;
						playerPosY -= playerSpeed;

					}
					if (map2[playerMapY - 1][playerMapX] == BLOCK7)
					{
						map2[7][27] = BLOCK7;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = YO;
						playerPosY -= playerSpeed;

					}
					if (map2[playerMapY - 1][playerMapX] == BLOCK8)
					{
						map2[8][27] = BLOCK8;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = YO;
						playerPosY -= playerSpeed;

					}
				}
				if (map2[playerMapY][playerMapX] == NN)
				{
					if (map2[playerMapY - 1][playerMapX] == YUKA)
					{
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = NN;
						if (map2[1][27] != BLOCK1 || map2[1][27] == BLOCK1)
						{
							if (map2[1][27] == BLOCK1 && map2[playerMapY][playerMapX] == map2[4][7])
							{
								map2[playerMapY][playerMapX] = BLOCK1;
								map2[1][27] = YUKA;
							}
						}
						if (map2[2][27] != BLOCK22 || map2[2][27] == BLOCK22)
						{
							if (map2[2][27] == BLOCK22 && map2[playerMapY][playerMapX] == map2[4][9])
							{
								map2[playerMapY][playerMapX] = BLOCK22;
								map2[2][27] = YUKA;
							}
						}
						if (map2[3][27] != BLOCK3 || map2[3][27] == BLOCK3)
						{
							if (map2[3][27] == BLOCK3 && map2[playerMapY][playerMapX] == map2[4][11])
							{
								map2[playerMapY][playerMapX] = BLOCK3;
								map2[3][27] = YUKA;
							}
						}
						if (map2[4][27] != BLOCK4 || map2[4][27] == BLOCK4)
						{
							if (map2[4][27] == BLOCK4 && map2[playerMapY][playerMapX] == map2[4][13])
							{
								map2[playerMapY][playerMapX] = BLOCK4;
								map2[4][27] = YUKA;
							}
						}
						if (map2[5][27] != BLOCK5 || map2[5][27] == BLOCK5)
						{
							if (map2[5][27] == BLOCK5 && map2[playerMapY][playerMapX] == map2[4][15])
							{
								map2[playerMapY][playerMapX] = BLOCK5;
								map2[5][27] = YUKA;
							}
						}
						if (map2[6][27] != BLOCK6 || map2[6][27] == BLOCK6)
						{

							if (map2[6][27] == BLOCK6 && map2[playerMapY][playerMapX] == /*6以降は後で*/map2[4][17])
							{
								map2[playerMapY][playerMapX] = BLOCK6;
								map2[6][27] = YUKA;
							}
						}
						if (map2[7][27] != BLOCK7 || map2[7][27] == BLOCK7)
						{
							if (map2[7][27] == BLOCK7 && map2[playerMapY][playerMapX] == map2[4][19])
							{
								map2[playerMapY][playerMapX] = BLOCK7;
								map2[7][27] = YUKA;
							}
						}
						if (map2[8][27] != BLOCK8 || map2[8][27] == BLOCK8)
						{
							if (map2[8][27] == BLOCK8 && map2[playerMapY][playerMapX] == map2[4][21])
							{
								map2[playerMapY][playerMapX] = BLOCK8;
								map2[8][27] = YUKA;
							}
						}
						playerPosY -= playerSpeed;
					}


					if (map2[playerMapY - 1][playerMapX] == BLOCK1)
					{
						map2[1][27] = BLOCK1;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = NN;
						playerPosY -= playerSpeed;

					}

					if (map2[playerMapY - 1][playerMapX] == BLOCK22)
					{
						map2[2][27] = BLOCK22;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = NN;
						playerPosY -= playerSpeed;

					}
					if (map2[playerMapY - 1][playerMapX] == BLOCK3)
					{
						map2[3][27] = BLOCK3;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = NN;
						playerPosY -= playerSpeed;

					}
					if (map2[playerMapY - 1][playerMapX] == BLOCK4)
					{
						map2[4][27] = BLOCK4;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = NN;
						playerPosY -= playerSpeed;

					}
					if (map2[playerMapY - 1][playerMapX] == BLOCK5)
					{
						map2[5][27] = BLOCK5;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = NN;
						playerPosY -= playerSpeed;

					}
					if (map2[playerMapY - 1][playerMapX] == BLOCK6)
					{
						map2[6][27] = BLOCK6;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = NN;
						playerPosY -= playerSpeed;

					}
					if (map2[playerMapY - 1][playerMapX] == BLOCK7)
					{
						map2[7][27] = BLOCK7;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = NN;
						playerPosY -= playerSpeed;

					}
					if (map2[playerMapY - 1][playerMapX] == BLOCK8)
					{
						map2[8][27] = BLOCK8;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = NN;
						playerPosY -= playerSpeed;

					}
				}
				if (map2[playerMapY][playerMapX] == ZA)
				{
					if (map2[playerMapY - 1][playerMapX] == YUKA)
					{
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = ZA;
						if (map2[1][27] != BLOCK1 || map2[1][27] == BLOCK1)
						{
							if (map2[1][27] == BLOCK1 && map2[playerMapY][playerMapX] == map2[4][7])
							{
								map2[playerMapY][playerMapX] = BLOCK1;
								map2[1][27] = YUKA;
							}
						}
						if (map2[2][27] != BLOCK22 || map2[2][27] == BLOCK22)
						{
							if (map2[2][27] == BLOCK22 && map2[playerMapY][playerMapX] == map2[4][9])
							{
								map2[playerMapY][playerMapX] = BLOCK22;
								map2[2][27] = YUKA;
							}
						}
						if (map2[3][27] != BLOCK3 || map2[3][27] == BLOCK3)
						{
							if (map2[3][27] == BLOCK3 && map2[playerMapY][playerMapX] == map2[4][11])
							{
								map2[playerMapY][playerMapX] = BLOCK3;
								map2[3][27] = YUKA;
							}
						}
						if (map2[4][27] != BLOCK4 || map2[4][27] == BLOCK4)
						{
							if (map2[4][27] == BLOCK4 && map2[playerMapY][playerMapX] == map2[4][13])
							{
								map2[playerMapY][playerMapX] = BLOCK4;
								map2[4][27] = YUKA;
							}
						}
						if (map2[5][27] != BLOCK5 || map2[5][27] == BLOCK5)
						{
							if (map2[5][27] == BLOCK5 && map2[playerMapY][playerMapX] == map2[4][15])
							{
								map2[playerMapY][playerMapX] = BLOCK5;
								map2[5][27] = YUKA;
							}
						}
						if (map2[6][27] != BLOCK6 || map2[6][27] == BLOCK6)
						{

							if (map2[6][27] == BLOCK6 && map2[playerMapY][playerMapX] == /*6以降は後で*/map2[4][17])
							{
								map2[playerMapY][playerMapX] = BLOCK6;
								map2[6][27] = YUKA;
							}
						}
						if (map2[7][27] != BLOCK7 || map2[7][27] == BLOCK7)
						{
							if (map2[7][27] == BLOCK7 && map2[playerMapY][playerMapX] == map2[4][19])
							{
								map2[playerMapY][playerMapX] = BLOCK7;
								map2[7][27] = YUKA;
							}
						}
						if (map2[8][27] != BLOCK8 || map2[8][27] == BLOCK8)
						{
							if (map2[8][27] == BLOCK8 && map2[playerMapY][playerMapX] == map2[4][21])
							{
								map2[playerMapY][playerMapX] = BLOCK8;
								map2[8][27] = YUKA;
							}
						}
						playerPosY -= playerSpeed;
					}


					if (map2[playerMapY - 1][playerMapX] == BLOCK1)
					{
						map2[1][27] = BLOCK1;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = ZA;
						playerPosY -= playerSpeed;

					}

					if (map2[playerMapY - 1][playerMapX] == BLOCK22)
					{
						map2[2][27] = BLOCK22;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = ZA;
						playerPosY -= playerSpeed;

					}
					if (map2[playerMapY - 1][playerMapX] == BLOCK3)
					{
						map2[3][27] = BLOCK3;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = ZA;
						playerPosY -= playerSpeed;

					}
					if (map2[playerMapY - 1][playerMapX] == BLOCK4)
					{
						map2[4][27] = BLOCK4;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = ZA;
						playerPosY -= playerSpeed;

					}
					if (map2[playerMapY - 1][playerMapX] == BLOCK5)
					{
						map2[5][27] = BLOCK5;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = ZA;
						playerPosY -= playerSpeed;

					}
					if (map2[playerMapY - 1][playerMapX] == BLOCK6)
					{
						map2[6][27] = BLOCK6;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = ZA;
						playerPosY -= playerSpeed;

					}
					if (map2[playerMapY - 1][playerMapX] == BLOCK7)
					{
						map2[7][27] = BLOCK7;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = ZA;
						playerPosY -= playerSpeed;

					}
					if (map2[playerMapY - 1][playerMapX] == BLOCK8)
					{
						map2[8][27] = BLOCK8;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = ZA;
						playerPosY -= playerSpeed;

					}
				}
				if (map2[playerMapY][playerMapX] == ZI)
				{
					if (map2[playerMapY - 1][playerMapX] == YUKA)
					{
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = ZI;
						if (map2[1][27] != BLOCK1 || map2[1][27] == BLOCK1)
						{
							if (map2[1][27] == BLOCK1 && map2[playerMapY][playerMapX] == map2[4][7])
							{
								map2[playerMapY][playerMapX] = BLOCK1;
								map2[1][27] = YUKA;
							}
						}
						if (map2[2][27] != BLOCK22 || map2[2][27] == BLOCK22)
						{
							if (map2[2][27] == BLOCK22 && map2[playerMapY][playerMapX] == map2[4][9])
							{
								map2[playerMapY][playerMapX] = BLOCK22;
								map2[2][27] = YUKA;
							}
						}
						if (map2[3][27] != BLOCK3 || map2[3][27] == BLOCK3)
						{
							if (map2[3][27] == BLOCK3 && map2[playerMapY][playerMapX] == map2[4][11])
							{
								map2[playerMapY][playerMapX] = BLOCK3;
								map2[3][27] = YUKA;
							}
						}
						if (map2[4][27] != BLOCK4 || map2[4][27] == BLOCK4)
						{
							if (map2[4][27] == BLOCK4 && map2[playerMapY][playerMapX] == map2[4][13])
							{
								map2[playerMapY][playerMapX] = BLOCK4;
								map2[4][27] = YUKA;
							}
						}
						if (map2[5][27] != BLOCK5 || map2[5][27] == BLOCK5)
						{
							if (map2[5][27] == BLOCK5 && map2[playerMapY][playerMapX] == map2[4][15])
							{
								map2[playerMapY][playerMapX] = BLOCK5;
								map2[5][27] = YUKA;
							}
						}
						if (map2[6][27] != BLOCK6 || map2[6][27] == BLOCK6)
						{

							if (map2[6][27] == BLOCK6 && map2[playerMapY][playerMapX] == /*6以降は後で*/map2[4][17])
							{
								map2[playerMapY][playerMapX] = BLOCK6;
								map2[6][27] = YUKA;
							}
						}
						if (map2[7][27] != BLOCK7 || map2[7][27] == BLOCK7)
						{
							if (map2[7][27] == BLOCK7 && map2[playerMapY][playerMapX] == map2[4][19])
							{
								map2[playerMapY][playerMapX] = BLOCK7;
								map2[7][27] = YUKA;
							}
						}
						if (map2[8][27] != BLOCK8 || map2[8][27] == BLOCK8)
						{
							if (map2[8][27] == BLOCK8 && map2[playerMapY][playerMapX] == map2[4][21])
							{
								map2[playerMapY][playerMapX] = BLOCK8;
								map2[8][27] = YUKA;
							}
						}
						playerPosY -= playerSpeed;
					}


					if (map2[playerMapY - 1][playerMapX] == BLOCK1)
					{
						map2[1][27] = BLOCK1;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = ZI;
						playerPosY -= playerSpeed;

					}

					if (map2[playerMapY - 1][playerMapX] == BLOCK22)
					{
						map2[2][27] = BLOCK22;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = ZI;
						playerPosY -= playerSpeed;

					}
					if (map2[playerMapY - 1][playerMapX] == BLOCK3)
					{
						map2[3][27] = BLOCK3;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = ZI;
						playerPosY -= playerSpeed;

					}
					if (map2[playerMapY - 1][playerMapX] == BLOCK4)
					{
						map2[4][27] = BLOCK4;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = ZI;
						playerPosY -= playerSpeed;

					}
					if (map2[playerMapY - 1][playerMapX] == BLOCK5)
					{
						map2[5][27] = BLOCK5;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = ZI;
						playerPosY -= playerSpeed;

					}
					if (map2[playerMapY - 1][playerMapX] == BLOCK6)
					{
						map2[6][27] = BLOCK6;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = ZI;
						playerPosY -= playerSpeed;

					}
					if (map2[playerMapY - 1][playerMapX] == BLOCK7)
					{
						map2[7][27] = BLOCK7;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = ZI;
						playerPosY -= playerSpeed;

					}
					if (map2[playerMapY - 1][playerMapX] == BLOCK8)
					{
						map2[8][27] = BLOCK8;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = ZI;
						playerPosY -= playerSpeed;

					}
				}
				if (map2[playerMapY][playerMapX] == BU)
				{
					if (map2[playerMapY - 1][playerMapX] == YUKA)
					{
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = BU;
						if (map2[1][27] != BLOCK1 || map2[1][27] == BLOCK1)
						{
							if (map2[1][27] == BLOCK1 && map2[playerMapY][playerMapX] == map2[4][7])
							{
								map2[playerMapY][playerMapX] = BLOCK1;
								map2[1][27] = YUKA;
							}
						}
						if (map2[2][27] != BLOCK22 || map2[2][27] == BLOCK22)
						{
							if (map2[2][27] == BLOCK22 && map2[playerMapY][playerMapX] == map2[4][9])
							{
								map2[playerMapY][playerMapX] = BLOCK22;
								map2[2][27] = YUKA;
							}
						}
						if (map2[3][27] != BLOCK3 || map2[3][27] == BLOCK3)
						{
							if (map2[3][27] == BLOCK3 && map2[playerMapY][playerMapX] == map2[4][11])
							{
								map2[playerMapY][playerMapX] = BLOCK3;
								map2[3][27] = YUKA;
							}
						}
						if (map2[4][27] != BLOCK4 || map2[4][27] == BLOCK4)
						{
							if (map2[4][27] == BLOCK4 && map2[playerMapY][playerMapX] == map2[4][13])
							{
								map2[playerMapY][playerMapX] = BLOCK4;
								map2[4][27] = YUKA;
							}
						}
						if (map2[5][27] != BLOCK5 || map2[5][27] == BLOCK5)
						{
							if (map2[5][27] == BLOCK5 && map2[playerMapY][playerMapX] == map2[4][15])
							{
								map2[playerMapY][playerMapX] = BLOCK5;
								map2[5][27] = YUKA;
							}
						}
						if (map2[6][27] != BLOCK6 || map2[6][27] == BLOCK6)
						{

							if (map2[6][27] == BLOCK6 && map2[playerMapY][playerMapX] == /*6以降は後で*/map2[4][17])
							{
								map2[playerMapY][playerMapX] = BLOCK6;
								map2[6][27] = YUKA;
							}
						}
						if (map2[7][27] != BLOCK7 || map2[7][27] == BLOCK7)
						{
							if (map2[7][27] == BLOCK7 && map2[playerMapY][playerMapX] == map2[4][19])
							{
								map2[playerMapY][playerMapX] = BLOCK7;
								map2[7][27] = YUKA;
							}
						}
						if (map2[8][27] != BLOCK8 || map2[8][27] == BLOCK8)
						{
							if (map2[8][27] == BLOCK8 && map2[playerMapY][playerMapX] == map2[4][21])
							{
								map2[playerMapY][playerMapX] = BLOCK8;
								map2[8][27] = YUKA;
							}
						}
						playerPosY -= playerSpeed;
					}


					if (map2[playerMapY - 1][playerMapX] == BLOCK1)
					{
						map2[1][27] = BLOCK1;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = BU;
						playerPosY -= playerSpeed;

					}

					if (map2[playerMapY - 1][playerMapX] == BLOCK22)
					{
						map2[2][27] = BLOCK22;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = BU;
						playerPosY -= playerSpeed;

					}
					if (map2[playerMapY - 1][playerMapX] == BLOCK3)
					{
						map2[3][27] = BLOCK3;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = BU;
						playerPosY -= playerSpeed;

					}
					if (map2[playerMapY - 1][playerMapX] == BLOCK4)
					{
						map2[4][27] = BLOCK4;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = BU;
						playerPosY -= playerSpeed;

					}
					if (map2[playerMapY - 1][playerMapX] == BLOCK5)
					{
						map2[5][27] = BLOCK5;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = BU;
						playerPosY -= playerSpeed;

					}
					if (map2[playerMapY - 1][playerMapX] == BLOCK6)
					{
						map2[6][27] = BLOCK6;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = BU;
						playerPosY -= playerSpeed;

					}
					if (map2[playerMapY - 1][playerMapX] == BLOCK7)
					{
						map2[7][27] = BLOCK7;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = BU;
						playerPosY -= playerSpeed;

					}
					if (map2[playerMapY - 1][playerMapX] == BLOCK8)
					{
						map2[8][27] = BLOCK8;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = BU;
						playerPosY -= playerSpeed;

					}
				}

			}

			if (keys[DIK_A] && preKeys[DIK_A] == 0 || keys[DIK_LEFT] && preKeys[DIK_LEFT] == 0)
			{
				playerTmpX = playerPosX - playerSpeed;
				playerMapX = playerTmpX / KBlockSize;
				//何もないから実際に進ませる
				if (map2[playerMapY][playerMapX] == YUKA)
				{
					playerPosX -= playerSpeed;
				}
				if (map2[playerMapY][playerMapX] == BLOCK1)
				{
					playerPosX -= playerSpeed;
				}
				if (map2[playerMapY][playerMapX] == GOAL)
				{
					playerPosX -= playerSpeed;
				}
				if (map2[playerMapY][playerMapX] == THORN)
				{
					playerPosX -= playerSpeed;
				}

				// 99999999999999999999999999999999999999999999999999
				// ここから直して
				if (map2[playerMapY][playerMapX] == U)
				{
					if (map2[playerMapY][playerMapX - 1] == YUKA)
					{
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = U; //ここをUに変える　したも同じ
						if (map2[1][27] != BLOCK1 || map2[1][27] == BLOCK1)
						{
							if (map2[1][27] == BLOCK1 && map2[playerMapY][playerMapX] == map2[4][7])
							{
								map2[playerMapY][playerMapX] = BLOCK1;
								map2[1][27] = YUKA;
							}
						}
						if (map2[2][27] != BLOCK22 || map2[2][27] == BLOCK22)
						{
							if (map2[2][27] == BLOCK22 && map2[playerMapY][playerMapX] == map2[4][9])
							{
								map2[playerMapY][playerMapX] = BLOCK22;
								map2[2][27] = YUKA;
							}
						}
						if (map2[3][27] != BLOCK3 || map2[3][27] == BLOCK3)
						{
							if (map2[3][27] == BLOCK3 && map2[playerMapY][playerMapX] == map2[4][11])
							{
								map2[playerMapY][playerMapX] = BLOCK3;
								map2[3][27] = YUKA;
							}
						}
						if (map2[4][27] != BLOCK4 || map2[4][27] == BLOCK4)
						{
							if (map2[4][27] == BLOCK4 && map2[playerMapY][playerMapX] == map2[4][13])
							{
								map2[playerMapY][playerMapX] = BLOCK4;
								map2[4][27] = YUKA;
							}
						}
						if (map2[5][27] != BLOCK5 || map2[5][27] == BLOCK5)
						{
							if (map2[5][27] == BLOCK5 && map2[playerMapY][playerMapX] == map2[4][15])
							{
								map2[playerMapY][playerMapX] = BLOCK5;
								map2[5][27] = YUKA;
							}
						}
						if (map2[6][27] != BLOCK6 || map2[6][27] == BLOCK6)
						{

							if (map2[6][27] == BLOCK6 && map2[playerMapY][playerMapX] == /*6以降は後で*/map2[4][17])
							{
								map2[playerMapY][playerMapX] = BLOCK6;
								map2[6][27] = YUKA;
							}
						}
						if (map2[7][27] != BLOCK7 || map2[7][27] == BLOCK7)
						{
							if (map2[7][27] == BLOCK7 && map2[playerMapY][playerMapX] == map2[4][19])
							{
								map2[playerMapY][playerMapX] = BLOCK7;
								map2[7][27] = YUKA;
							}
						}
						if (map2[8][27] != BLOCK8 || map2[8][27] == BLOCK8)
						{
							if (map2[8][27] == BLOCK8 && map2[playerMapY][playerMapX] == map2[4][21])
							{
								map2[playerMapY][playerMapX] = BLOCK8;
								map2[8][27] = YUKA;
							}
						}

						playerPosX -= playerSpeed;
					}

					if (map2[playerMapY][playerMapX - 1] == BLOCK1)
					{
						map2[1][27] = BLOCK1;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = U;
						playerPosX -= playerSpeed;

					}
					if (map2[playerMapY][playerMapX - 1] == BLOCK22)
					{
						map2[2][27] = BLOCK22;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = U;
						playerPosX -= playerSpeed;

					}
					if (map2[playerMapY][playerMapX - 1] == BLOCK3)
					{
						map2[3][27] = BLOCK3;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = U;
						playerPosX -= playerSpeed;

					}
					if (map2[playerMapY][playerMapX - 1] == BLOCK4)
					{
						map2[4][27] = BLOCK4;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = U;
						playerPosX -= playerSpeed;

					}
					if (map2[playerMapY][playerMapX - 1] == BLOCK5)
					{
						map2[5][27] = BLOCK5;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = U;
						playerPosX -= playerSpeed;

					}
					if (map2[playerMapY][playerMapX - 1] == BLOCK6)
					{
						map2[6][27] = BLOCK6;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = U;
						playerPosX -= playerSpeed;

					}
					if (map2[playerMapY][playerMapX - 1] == BLOCK7)
					{
						map2[7][27] = BLOCK7;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = U;
						playerPosX -= playerSpeed;

					}
					if (map2[playerMapY][playerMapX - 1] == BLOCK8)
					{
						map2[8][27] = BLOCK8;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = U;
						playerPosX -= playerSpeed;

					}
				}
				if (map2[playerMapY][playerMapX] == E)
				{
					if (map2[playerMapY][playerMapX - 1] == YUKA)
					{
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = E;
						if (map2[1][27] != BLOCK1 || map2[1][27] == BLOCK1)
						{
							if (map2[1][27] == BLOCK1 && map2[playerMapY][playerMapX] == map2[4][7])
							{
								map2[playerMapY][playerMapX] = BLOCK1;
								map2[1][27] = YUKA;
							}
						}
						if (map2[2][27] != BLOCK22 || map2[2][27] == BLOCK22)
						{
							if (map2[2][27] == BLOCK22 && map2[playerMapY][playerMapX] == map2[4][9])
							{
								map2[playerMapY][playerMapX] = BLOCK22;
								map2[2][27] = YUKA;
							}
						}
						if (map2[3][27] != BLOCK3 || map2[3][27] == BLOCK3)
						{
							if (map2[3][27] == BLOCK3 && map2[playerMapY][playerMapX] == map2[4][11])
							{
								map2[playerMapY][playerMapX] = BLOCK3;
								map2[3][27] = YUKA;
							}
						}
						if (map2[4][27] != BLOCK4 || map2[4][27] == BLOCK4)
						{
							if (map2[4][27] == BLOCK4 && map2[playerMapY][playerMapX] == map2[4][13])
							{
								map2[playerMapY][playerMapX] = BLOCK4;
								map2[4][27] = YUKA;
							}
						}
						if (map2[5][27] != BLOCK5 || map2[5][27] == BLOCK5)
						{
							if (map2[5][27] == BLOCK5 && map2[playerMapY][playerMapX] == map2[4][15])
							{
								map2[playerMapY][playerMapX] = BLOCK5;
								map2[5][27] = YUKA;
							}
						}
						if (map2[6][27] != BLOCK6 || map2[6][27] == BLOCK6)
						{

							if (map2[6][27] == BLOCK6 && map2[playerMapY][playerMapX] == /*6以降は後で*/map2[4][17])
							{
								map2[playerMapY][playerMapX] = BLOCK6;
								map2[6][27] = YUKA;
							}
						}
						if (map2[7][27] != BLOCK7 || map2[7][27] == BLOCK7)
						{
							if (map2[7][27] == BLOCK7 && map2[playerMapY][playerMapX] == map2[4][19])
							{
								map2[playerMapY][playerMapX] = BLOCK7;
								map2[7][27] = YUKA;
							}
						}
						if (map2[8][27] != BLOCK8 || map2[8][27] == BLOCK8)
						{
							if (map2[8][27] == BLOCK8 && map2[playerMapY][playerMapX] == map2[4][21])
							{
								map2[playerMapY][playerMapX] = BLOCK8;
								map2[8][27] = YUKA;
							}
						}

						playerPosX -= playerSpeed;
					}
					if (map2[playerMapY][playerMapX - 1] == BLOCK1)
					{
						map2[1][27] = BLOCK1;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = E;
						playerPosX -= playerSpeed;

					}
					if (map2[playerMapY][playerMapX - 1] == BLOCK22)
					{
						map2[2][27] = BLOCK22;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = E;
						playerPosX -= playerSpeed;

					}
					if (map2[playerMapY][playerMapX - 1] == BLOCK3)
					{
						map2[3][27] = BLOCK3;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = E;
						playerPosX -= playerSpeed;

					}
					if (map2[playerMapY][playerMapX - 1] == BLOCK4)
					{
						map2[4][27] = BLOCK4;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = E;
						playerPosX -= playerSpeed;

					}
					if (map2[playerMapY][playerMapX - 1] == BLOCK5)
					{
						map2[5][27] = BLOCK5;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = E;
						playerPosX -= playerSpeed;

					}
					if (map2[playerMapY][playerMapX - 1] == BLOCK6)
					{
						map2[6][27] = BLOCK6;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = E;
						playerPosX -= playerSpeed;

					}
					if (map2[playerMapY][playerMapX - 1] == BLOCK7)
					{
						map2[7][27] = BLOCK7;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = E;
						playerPosX -= playerSpeed;

					}
					if (map2[playerMapY][playerMapX - 1] == BLOCK8)
					{
						map2[8][27] = BLOCK8;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = E;
						playerPosX -= playerSpeed;

					}
				}
				if (map2[playerMapY][playerMapX] == O)
				{
					if (map2[playerMapY][playerMapX - 1] == YUKA)
					{
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = O;
						if (map2[1][27] != BLOCK1 || map2[1][27] == BLOCK1)
						{
							if (map2[1][27] == BLOCK1 && map2[playerMapY][playerMapX] == map2[4][7])
							{
								map2[playerMapY][playerMapX] = BLOCK1;
								map2[1][27] = YUKA;
							}
						}
						if (map2[2][27] != BLOCK22 || map2[2][27] == BLOCK22)
						{
							if (map2[2][27] == BLOCK22 && map2[playerMapY][playerMapX] == map2[4][9])
							{
								map2[playerMapY][playerMapX] = BLOCK22;
								map2[2][27] = YUKA;
							}
						}
						if (map2[3][27] != BLOCK3 || map2[3][27] == BLOCK3)
						{
							if (map2[3][27] == BLOCK3 && map2[playerMapY][playerMapX] == map2[4][11])
							{
								map2[playerMapY][playerMapX] = BLOCK3;
								map2[3][27] = YUKA;
							}
						}
						if (map2[4][27] != BLOCK4 || map2[4][27] == BLOCK4)
						{
							if (map2[4][27] == BLOCK4 && map2[playerMapY][playerMapX] == map2[4][13])
							{
								map2[playerMapY][playerMapX] = BLOCK4;
								map2[4][27] = YUKA;
							}
						}
						if (map2[5][27] != BLOCK5 || map2[5][27] == BLOCK5)
						{
							if (map2[5][27] == BLOCK5 && map2[playerMapY][playerMapX] == map2[4][15])
							{
								map2[playerMapY][playerMapX] = BLOCK5;
								map2[5][27] = YUKA;
							}
						}
						if (map2[6][27] != BLOCK6 || map2[6][27] == BLOCK6)
						{

							if (map2[6][27] == BLOCK6 && map2[playerMapY][playerMapX] == /*6以降は後で*/map2[4][17])
							{
								map2[playerMapY][playerMapX] = BLOCK6;
								map2[6][27] = YUKA;
							}
						}
						if (map2[7][27] != BLOCK7 || map2[7][27] == BLOCK7)
						{
							if (map2[7][27] == BLOCK7 && map2[playerMapY][playerMapX] == map2[4][19])
							{
								map2[playerMapY][playerMapX] = BLOCK7;
								map2[7][27] = YUKA;
							}
						}
						if (map2[8][27] != BLOCK8 || map2[8][27] == BLOCK8)
						{
							if (map2[8][27] == BLOCK8 && map2[playerMapY][playerMapX] == map2[4][21])
							{
								map2[playerMapY][playerMapX] = BLOCK8;
								map2[8][27] = YUKA;
							}
						}

						playerPosX -= playerSpeed;
					}

					if (map2[playerMapY][playerMapX - 1] == BLOCK1)
					{
						map2[1][27] = BLOCK1;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = O;
						playerPosX -= playerSpeed;

					}
					if (map2[playerMapY][playerMapX - 1] == BLOCK22)
					{
						map2[2][27] = BLOCK22;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = O;
						playerPosX -= playerSpeed;

					}
					if (map2[playerMapY][playerMapX - 1] == BLOCK3)
					{
						map2[3][27] = BLOCK3;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = O;
						playerPosX -= playerSpeed;

					}
					if (map2[playerMapY][playerMapX - 1] == BLOCK4)
					{
						map2[4][27] = BLOCK4;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = O;
						playerPosX -= playerSpeed;

					}
					if (map2[playerMapY][playerMapX - 1] == BLOCK5)
					{
						map2[5][27] = BLOCK5;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = O;
						playerPosX -= playerSpeed;

					}
					if (map2[playerMapY][playerMapX - 1] == BLOCK6)
					{
						map2[6][27] = BLOCK6;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = O;
						playerPosX -= playerSpeed;

					}
					if (map2[playerMapY][playerMapX - 1] == BLOCK7)
					{
						map2[7][27] = BLOCK7;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = O;
						playerPosX -= playerSpeed;

					}
					if (map2[playerMapY][playerMapX - 1] == BLOCK8)
					{
						map2[8][27] = BLOCK8;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = O;
						playerPosX -= playerSpeed;

					}
				}
				if (map2[playerMapY][playerMapX] == KA)
				{
					if (map2[playerMapY][playerMapX - 1] == YUKA)
					{
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = KA;
						if (map2[1][27] != BLOCK1 || map2[1][27] == BLOCK1)
						{
							if (map2[1][27] == BLOCK1 && map2[playerMapY][playerMapX] == map2[4][7])
							{
								map2[playerMapY][playerMapX] = BLOCK1;
								map2[1][27] = YUKA;
							}
						}
						if (map2[2][27] != BLOCK22 || map2[2][27] == BLOCK22)
						{
							if (map2[2][27] == BLOCK22 && map2[playerMapY][playerMapX] == map2[4][9])
							{
								map2[playerMapY][playerMapX] = BLOCK22;
								map2[2][27] = YUKA;
							}
						}
						if (map2[3][27] != BLOCK3 || map2[3][27] == BLOCK3)
						{
							if (map2[3][27] == BLOCK3 && map2[playerMapY][playerMapX] == map2[4][11])
							{
								map2[playerMapY][playerMapX] = BLOCK3;
								map2[3][27] = YUKA;
							}
						}
						if (map2[4][27] != BLOCK4 || map2[4][27] == BLOCK4)
						{
							if (map2[4][27] == BLOCK4 && map2[playerMapY][playerMapX] == map2[4][13])
							{
								map2[playerMapY][playerMapX] = BLOCK4;
								map2[4][27] = YUKA;
							}
						}
						if (map2[5][27] != BLOCK5 || map2[5][27] == BLOCK5)
						{
							if (map2[5][27] == BLOCK5 && map2[playerMapY][playerMapX] == map2[4][15])
							{
								map2[playerMapY][playerMapX] = BLOCK5;
								map2[5][27] = YUKA;
							}
						}
						if (map2[6][27] != BLOCK6 || map2[6][27] == BLOCK6)
						{

							if (map2[6][27] == BLOCK6 && map2[playerMapY][playerMapX] == /*6以降は後で*/map2[4][17])
							{
								map2[playerMapY][playerMapX] = BLOCK6;
								map2[6][27] = YUKA;
							}
						}
						if (map2[7][27] != BLOCK7 || map2[7][27] == BLOCK7)
						{
							if (map2[7][27] == BLOCK7 && map2[playerMapY][playerMapX] == map2[4][19])
							{
								map2[playerMapY][playerMapX] = BLOCK7;
								map2[7][27] = YUKA;
							}
						}
						if (map2[8][27] != BLOCK8 || map2[8][27] == BLOCK8)
						{
							if (map2[8][27] == BLOCK8 && map2[playerMapY][playerMapX] == map2[4][21])
							{
								map2[playerMapY][playerMapX] = BLOCK8;
								map2[8][27] = YUKA;
							}
						}

						playerPosX -= playerSpeed;
					}

					if (map2[playerMapY][playerMapX - 1] == BLOCK1)
					{
						map2[1][27] = BLOCK1;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = KA;
						playerPosX -= playerSpeed;

					}
					if (map2[playerMapY][playerMapX - 1] == BLOCK22)
					{
						map2[2][27] = BLOCK22;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = KA;
						playerPosX -= playerSpeed;

					}
					if (map2[playerMapY][playerMapX - 1] == BLOCK3)
					{
						map2[3][27] = BLOCK3;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = KA;
						playerPosX -= playerSpeed;

					}
					if (map2[playerMapY][playerMapX - 1] == BLOCK4)
					{
						map2[4][27] = BLOCK4;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = KA;
						playerPosX -= playerSpeed;

					}
					if (map2[playerMapY][playerMapX - 1] == BLOCK5)
					{
						map2[5][27] = BLOCK5;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = KA;
						playerPosX -= playerSpeed;

					}
					if (map2[playerMapY][playerMapX - 1] == BLOCK6)
					{
						map2[6][27] = BLOCK6;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = KA;
						playerPosX -= playerSpeed;

					}
					if (map2[playerMapY][playerMapX - 1] == BLOCK7)
					{
						map2[7][27] = BLOCK7;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = KA;
						playerPosX -= playerSpeed;

					}
					if (map2[playerMapY][playerMapX - 1] == BLOCK8)
					{
						map2[8][27] = BLOCK8;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = KA;
						playerPosX -= playerSpeed;

					}
				}
				if (map2[playerMapY][playerMapX] == KU)
				{
					if (map2[playerMapY][playerMapX - 1] == YUKA)
					{
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = KU;
						if (map2[1][27] != BLOCK1 || map2[1][27] == BLOCK1)
						{
							if (map2[1][27] == BLOCK1 && map2[playerMapY][playerMapX] == map2[4][7])
							{
								map2[playerMapY][playerMapX] = BLOCK1;
								map2[1][27] = YUKA;
							}
						}
						if (map2[2][27] != BLOCK22 || map2[2][27] == BLOCK22)
						{
							if (map2[2][27] == BLOCK22 && map2[playerMapY][playerMapX] == map2[4][9])
							{
								map2[playerMapY][playerMapX] = BLOCK22;
								map2[2][27] = YUKA;
							}
						}
						if (map2[3][27] != BLOCK3 || map2[3][27] == BLOCK3)
						{
							if (map2[3][27] == BLOCK3 && map2[playerMapY][playerMapX] == map2[4][11])
							{
								map2[playerMapY][playerMapX] = BLOCK3;
								map2[3][27] = YUKA;
							}
						}
						if (map2[4][27] != BLOCK4 || map2[4][27] == BLOCK4)
						{
							if (map2[4][27] == BLOCK4 && map2[playerMapY][playerMapX] == map2[4][13])
							{
								map2[playerMapY][playerMapX] = BLOCK4;
								map2[4][27] = YUKA;
							}
						}
						if (map2[5][27] != BLOCK5 || map2[5][27] == BLOCK5)
						{
							if (map2[5][27] == BLOCK5 && map2[playerMapY][playerMapX] == map2[4][15])
							{
								map2[playerMapY][playerMapX] = BLOCK5;
								map2[5][27] = YUKA;
							}
						}
						if (map2[6][27] != BLOCK6 || map2[6][27] == BLOCK6)
						{

							if (map2[6][27] == BLOCK6 && map2[playerMapY][playerMapX] == /*6以降は後で*/map2[4][17])
							{
								map2[playerMapY][playerMapX] = BLOCK6;
								map2[6][27] = YUKA;
							}
						}
						if (map2[7][27] != BLOCK7 || map2[7][27] == BLOCK7)
						{
							if (map2[7][27] == BLOCK7 && map2[playerMapY][playerMapX] == map2[4][19])
							{
								map2[playerMapY][playerMapX] = BLOCK7;
								map2[7][27] = YUKA;
							}
						}
						if (map2[8][27] != BLOCK8 || map2[8][27] == BLOCK8)
						{
							if (map2[8][27] == BLOCK8 && map2[playerMapY][playerMapX] == map2[4][21])
							{
								map2[playerMapY][playerMapX] = BLOCK8;
								map2[8][27] = YUKA;
							}
						}

						playerPosX -= playerSpeed;
					}

					if (map2[playerMapY][playerMapX - 1] == BLOCK1)
					{
						map2[1][27] = BLOCK1;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = KU;
						playerPosX -= playerSpeed;

					}
					if (map2[playerMapY][playerMapX - 1] == BLOCK22)
					{
						map2[2][27] = BLOCK22;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = KU;
						playerPosX -= playerSpeed;

					}
					if (map2[playerMapY][playerMapX - 1] == BLOCK3)
					{
						map2[3][27] = BLOCK3;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = KU;
						playerPosX -= playerSpeed;

					}
					if (map2[playerMapY][playerMapX - 1] == BLOCK4)
					{
						map2[4][27] = BLOCK4;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = KU;
						playerPosX -= playerSpeed;

					}
					if (map2[playerMapY][playerMapX - 1] == BLOCK5)
					{
						map2[5][27] = BLOCK5;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = KU;
						playerPosX -= playerSpeed;

					}
					if (map2[playerMapY][playerMapX - 1] == BLOCK6)
					{
						map2[6][27] = BLOCK6;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = KU;
						playerPosX -= playerSpeed;

					}
					if (map2[playerMapY][playerMapX - 1] == BLOCK7)
					{
						map2[7][27] = BLOCK7;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = KU;
						playerPosX -= playerSpeed;

					}
					if (map2[playerMapY][playerMapX - 1] == BLOCK8)
					{
						map2[8][27] = BLOCK8;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = KU;
						playerPosX -= playerSpeed;

					}
				}
				if (map2[playerMapY][playerMapX] == SA)
				{
					if (map2[playerMapY][playerMapX - 1] == YUKA)
					{
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = SA;
						if (map2[1][27] != BLOCK1 || map2[1][27] == BLOCK1)
						{
							if (map2[1][27] == BLOCK1 && map2[playerMapY][playerMapX] == map2[4][7])
							{
								map2[playerMapY][playerMapX] = BLOCK1;
								map2[1][27] = YUKA;
							}
						}
						if (map2[2][27] != BLOCK22 || map2[2][27] == BLOCK22)
						{
							if (map2[2][27] == BLOCK22 && map2[playerMapY][playerMapX] == map2[4][9])
							{
								map2[playerMapY][playerMapX] = BLOCK22;
								map2[2][27] = YUKA;
							}
						}
						if (map2[3][27] != BLOCK3 || map2[3][27] == BLOCK3)
						{
							if (map2[3][27] == BLOCK3 && map2[playerMapY][playerMapX] == map2[4][11])
							{
								map2[playerMapY][playerMapX] = BLOCK3;
								map2[3][27] = YUKA;
							}
						}
						if (map2[4][27] != BLOCK4 || map2[4][27] == BLOCK4)
						{
							if (map2[4][27] == BLOCK4 && map2[playerMapY][playerMapX] == map2[4][13])
							{
								map2[playerMapY][playerMapX] = BLOCK4;
								map2[4][27] = YUKA;
							}
						}
						if (map2[5][27] != BLOCK5 || map2[5][27] == BLOCK5)
						{
							if (map2[5][27] == BLOCK5 && map2[playerMapY][playerMapX] == map2[4][15])
							{
								map2[playerMapY][playerMapX] = BLOCK5;
								map2[5][27] = YUKA;
							}
						}
						if (map2[6][27] != BLOCK6 || map2[6][27] == BLOCK6)
						{

							if (map2[6][27] == BLOCK6 && map2[playerMapY][playerMapX] == /*6以降は後で*/map2[4][17])
							{
								map2[playerMapY][playerMapX] = BLOCK6;
								map2[6][27] = YUKA;
							}
						}
						if (map2[7][27] != BLOCK7 || map2[7][27] == BLOCK7)
						{
							if (map2[7][27] == BLOCK7 && map2[playerMapY][playerMapX] == map2[4][19])
							{
								map2[playerMapY][playerMapX] = BLOCK7;
								map2[7][27] = YUKA;
							}
						}
						if (map2[8][27] != BLOCK8 || map2[8][27] == BLOCK8)
						{
							if (map2[8][27] == BLOCK8 && map2[playerMapY][playerMapX] == map2[4][21])
							{
								map2[playerMapY][playerMapX] = BLOCK8;
								map2[8][27] = YUKA;
							}
						}

						playerPosX -= playerSpeed;
					}
					if (map2[playerMapY][playerMapX - 1] == BLOCK1)
					{
						map2[1][27] = BLOCK1;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = SA;
						playerPosX -= playerSpeed;

					}
					if (map2[playerMapY][playerMapX - 1] == BLOCK22)
					{
						map2[2][27] = BLOCK22;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = SA;
						playerPosX -= playerSpeed;

					}
					if (map2[playerMapY][playerMapX - 1] == BLOCK3)
					{
						map2[3][27] = BLOCK3;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = SA;
						playerPosX -= playerSpeed;

					}
					if (map2[playerMapY][playerMapX - 1] == BLOCK4)
					{
						map2[4][27] = BLOCK4;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = SA;
						playerPosX -= playerSpeed;

					}
					if (map2[playerMapY][playerMapX - 1] == BLOCK5)
					{
						map2[5][27] = BLOCK5;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = SA;
						playerPosX -= playerSpeed;

					}
					if (map2[playerMapY][playerMapX - 1] == BLOCK6)
					{
						map2[6][27] = BLOCK6;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = SA;
						playerPosX -= playerSpeed;

					}
					if (map2[playerMapY][playerMapX - 1] == BLOCK7)
					{
						map2[7][27] = BLOCK7;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = SA;
						playerPosX -= playerSpeed;

					}
					if (map2[playerMapY][playerMapX - 1] == BLOCK8)
					{
						map2[8][27] = BLOCK8;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = SA;
						playerPosX -= playerSpeed;

					}
				}
				if (map2[playerMapY][playerMapX] == SHI)
				{
					if (map2[playerMapY][playerMapX - 1] == YUKA)
					{
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = SHI;
						if (map2[1][27] != BLOCK1 || map2[1][27] == BLOCK1)
						{
							if (map2[1][27] == BLOCK1 && map2[playerMapY][playerMapX] == map2[4][7])
							{
								map2[playerMapY][playerMapX] = BLOCK1;
								map2[1][27] = YUKA;
							}
						}
						if (map2[2][27] != BLOCK22 || map2[2][27] == BLOCK22)
						{
							if (map2[2][27] == BLOCK22 && map2[playerMapY][playerMapX] == map2[4][9])
							{
								map2[playerMapY][playerMapX] = BLOCK22;
								map2[2][27] = YUKA;
							}
						}
						if (map2[3][27] != BLOCK3 || map2[3][27] == BLOCK3)
						{
							if (map2[3][27] == BLOCK3 && map2[playerMapY][playerMapX] == map2[4][11])
							{
								map2[playerMapY][playerMapX] = BLOCK3;
								map2[3][27] = YUKA;
							}
						}
						if (map2[4][27] != BLOCK4 || map2[4][27] == BLOCK4)
						{
							if (map2[4][27] == BLOCK4 && map2[playerMapY][playerMapX] == map2[4][13])
							{
								map2[playerMapY][playerMapX] = BLOCK4;
								map2[4][27] = YUKA;
							}
						}
						if (map2[5][27] != BLOCK5 || map2[5][27] == BLOCK5)
						{
							if (map2[5][27] == BLOCK5 && map2[playerMapY][playerMapX] == map2[4][15])
							{
								map2[playerMapY][playerMapX] = BLOCK5;
								map2[5][27] = YUKA;
							}
						}
						if (map2[6][27] != BLOCK6 || map2[6][27] == BLOCK6)
						{

							if (map2[6][27] == BLOCK6 && map2[playerMapY][playerMapX] == /*6以降は後で*/map2[4][17])
							{
								map2[playerMapY][playerMapX] = BLOCK6;
								map2[6][27] = YUKA;
							}
						}
						if (map2[7][27] != BLOCK7 || map2[7][27] == BLOCK7)
						{
							if (map2[7][27] == BLOCK7 && map2[playerMapY][playerMapX] == map2[4][19])
							{
								map2[playerMapY][playerMapX] = BLOCK7;
								map2[7][27] = YUKA;
							}
						}
						if (map2[8][27] != BLOCK8 || map2[8][27] == BLOCK8)
						{
							if (map2[8][27] == BLOCK8 && map2[playerMapY][playerMapX] == map2[4][21])
							{
								map2[playerMapY][playerMapX] = BLOCK8;
								map2[8][27] = YUKA;
							}
						}
						playerPosX -= playerSpeed;
					}

					if (map2[playerMapY][playerMapX - 1] == BLOCK1)
					{
						map2[1][27] = BLOCK1;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = SHI;
						playerPosX -= playerSpeed;

					}
					if (map2[playerMapY][playerMapX - 1] == BLOCK22)
					{
						map2[2][27] = BLOCK22;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = SHI;
						playerPosX -= playerSpeed;

					}
					if (map2[playerMapY][playerMapX - 1] == BLOCK3)
					{
						map2[3][27] = BLOCK3;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = SHI;
						playerPosX -= playerSpeed;

					}
					if (map2[playerMapY][playerMapX - 1] == BLOCK4)
					{
						map2[4][27] = BLOCK4;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = SHI;
						playerPosX -= playerSpeed;

					}
					if (map2[playerMapY][playerMapX - 1] == BLOCK5)
					{
						map2[5][27] = BLOCK5;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = SHI;
						playerPosX -= playerSpeed;

					}
					if (map2[playerMapY][playerMapX - 1] == BLOCK6)
					{
						map2[6][27] = BLOCK6;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = SHI;
						playerPosX -= playerSpeed;

					}
					if (map2[playerMapY][playerMapX - 1] == BLOCK7)
					{
						map2[7][27] = BLOCK7;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = SHI;
						playerPosX -= playerSpeed;

					}
					if (map2[playerMapY][playerMapX - 1] == BLOCK8)
					{
						map2[8][27] = BLOCK8;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = SHI;
						playerPosX -= playerSpeed;

					}
				}
				if (map2[playerMapY][playerMapX] == SU)
				{
					if (map2[playerMapY][playerMapX - 1] == YUKA)
					{
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = SU;
						if (map2[1][27] != BLOCK1 || map2[1][27] == BLOCK1)
						{
							if (map2[1][27] == BLOCK1 && map2[playerMapY][playerMapX] == map2[4][7])
							{
								map2[playerMapY][playerMapX] = BLOCK1;
								map2[1][27] = YUKA;
							}
						}
						if (map2[2][27] != BLOCK22 || map2[2][27] == BLOCK22)
						{
							if (map2[2][27] == BLOCK22 && map2[playerMapY][playerMapX] == map2[4][9])
							{
								map2[playerMapY][playerMapX] = BLOCK22;
								map2[2][27] = YUKA;
							}
						}
						if (map2[3][27] != BLOCK3 || map2[3][27] == BLOCK3)
						{
							if (map2[3][27] == BLOCK3 && map2[playerMapY][playerMapX] == map2[4][11])
							{
								map2[playerMapY][playerMapX] = BLOCK3;
								map2[3][27] = YUKA;
							}
						}
						if (map2[4][27] != BLOCK4 || map2[4][27] == BLOCK4)
						{
							if (map2[4][27] == BLOCK4 && map2[playerMapY][playerMapX] == map2[4][13])
							{
								map2[playerMapY][playerMapX] = BLOCK4;
								map2[4][27] = YUKA;
							}
						}
						if (map2[5][27] != BLOCK5 || map2[5][27] == BLOCK5)
						{
							if (map2[5][27] == BLOCK5 && map2[playerMapY][playerMapX] == map2[4][15])
							{
								map2[playerMapY][playerMapX] = BLOCK5;
								map2[5][27] = YUKA;
							}
						}
						if (map2[6][27] != BLOCK6 || map2[6][27] == BLOCK6)
						{

							if (map2[6][27] == BLOCK6 && map2[playerMapY][playerMapX] == /*6以降は後で*/map2[4][17])
							{
								map2[playerMapY][playerMapX] = BLOCK6;
								map2[6][27] = YUKA;
							}
						}
						if (map2[7][27] != BLOCK7 || map2[7][27] == BLOCK7)
						{
							if (map2[7][27] == BLOCK7 && map2[playerMapY][playerMapX] == map2[4][19])
							{
								map2[playerMapY][playerMapX] = BLOCK7;
								map2[7][27] = YUKA;
							}
						}
						if (map2[8][27] != BLOCK8 || map2[8][27] == BLOCK8)
						{
							if (map2[8][27] == BLOCK8 && map2[playerMapY][playerMapX] == map2[4][21])
							{
								map2[playerMapY][playerMapX] = BLOCK8;
								map2[8][27] = YUKA;
							}
						}
						playerPosX -= playerSpeed;
					}

					if (map2[playerMapY][playerMapX - 1] == BLOCK1)
					{
						map2[1][27] = BLOCK1;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = SU;
						playerPosX -= playerSpeed;

					}
					if (map2[playerMapY][playerMapX - 1] == BLOCK22)
					{
						map2[2][27] = BLOCK22;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = SU;
						playerPosX -= playerSpeed;

					}
					if (map2[playerMapY][playerMapX - 1] == BLOCK3)
					{
						map2[3][27] = BLOCK3;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = SU;
						playerPosX -= playerSpeed;

					}
					if (map2[playerMapY][playerMapX - 1] == BLOCK4)
					{
						map2[4][27] = BLOCK4;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = SU;
						playerPosX -= playerSpeed;

					}
					if (map2[playerMapY][playerMapX - 1] == BLOCK5)
					{
						map2[5][27] = BLOCK5;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = SU;
						playerPosX -= playerSpeed;

					}
					if (map2[playerMapY][playerMapX - 1] == BLOCK6)
					{
						map2[6][27] = BLOCK6;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = SU;
						playerPosX -= playerSpeed;

					}
					if (map2[playerMapY][playerMapX - 1] == BLOCK7)
					{
						map2[7][27] = BLOCK7;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = SU;
						playerPosX -= playerSpeed;

					}
					if (map2[playerMapY][playerMapX - 1] == BLOCK8)
					{
						map2[8][27] = BLOCK8;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = SU;
						playerPosX -= playerSpeed;

					}
				}
				if (map2[playerMapY][playerMapX] == TO)
				{
					if (map2[playerMapY][playerMapX - 1] == YUKA)
					{
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = TO;
						if (map2[1][27] != BLOCK1 || map2[1][27] == BLOCK1)
						{
							if (map2[1][27] == BLOCK1 && map2[playerMapY][playerMapX] == map2[4][7])
							{
								map2[playerMapY][playerMapX] = BLOCK1;
								map2[1][27] = YUKA;
							}
						}
						if (map2[2][27] != BLOCK22 || map2[2][27] == BLOCK22)
						{
							if (map2[2][27] == BLOCK22 && map2[playerMapY][playerMapX] == map2[4][9])
							{
								map2[playerMapY][playerMapX] = BLOCK22;
								map2[2][27] = YUKA;
							}
						}
						if (map2[3][27] != BLOCK3 || map2[3][27] == BLOCK3)
						{
							if (map2[3][27] == BLOCK3 && map2[playerMapY][playerMapX] == map2[4][11])
							{
								map2[playerMapY][playerMapX] = BLOCK3;
								map2[3][27] = YUKA;
							}
						}
						if (map2[4][27] != BLOCK4 || map2[4][27] == BLOCK4)
						{
							if (map2[4][27] == BLOCK4 && map2[playerMapY][playerMapX] == map2[4][13])
							{
								map2[playerMapY][playerMapX] = BLOCK4;
								map2[4][27] = YUKA;
							}
						}
						if (map2[5][27] != BLOCK5 || map2[5][27] == BLOCK5)
						{
							if (map2[5][27] == BLOCK5 && map2[playerMapY][playerMapX] == map2[4][15])
							{
								map2[playerMapY][playerMapX] = BLOCK5;
								map2[5][27] = YUKA;
							}
						}
						if (map2[6][27] != BLOCK6 || map2[6][27] == BLOCK6)
						{

							if (map2[6][27] == BLOCK6 && map2[playerMapY][playerMapX] == /*6以降は後で*/map2[4][17])
							{
								map2[playerMapY][playerMapX] = BLOCK6;
								map2[6][27] = YUKA;
							}
						}
						if (map2[7][27] != BLOCK7 || map2[7][27] == BLOCK7)
						{
							if (map2[7][27] == BLOCK7 && map2[playerMapY][playerMapX] == map2[4][19])
							{
								map2[playerMapY][playerMapX] = BLOCK7;
								map2[7][27] = YUKA;
							}
						}
						if (map2[8][27] != BLOCK8 || map2[8][27] == BLOCK8)
						{
							if (map2[8][27] == BLOCK8 && map2[playerMapY][playerMapX] == map2[4][21])
							{
								map2[playerMapY][playerMapX] = BLOCK8;
								map2[8][27] = YUKA;
							}
						}
						playerPosX -= playerSpeed;
					}

					if (map2[playerMapY][playerMapX - 1] == BLOCK1)
					{
						map2[1][27] = BLOCK1;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = TO;
						playerPosX -= playerSpeed;

					}
					if (map2[playerMapY][playerMapX - 1] == BLOCK22)
					{
						map2[2][27] = BLOCK22;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = TO;
						playerPosX -= playerSpeed;

					}
					if (map2[playerMapY][playerMapX - 1] == BLOCK3)
					{
						map2[3][27] = BLOCK3;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = TO;
						playerPosX -= playerSpeed;

					}
					if (map2[playerMapY][playerMapX - 1] == BLOCK4)
					{
						map2[4][27] = BLOCK4;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = TO;
						playerPosX -= playerSpeed;

					}
					if (map2[playerMapY][playerMapX - 1] == BLOCK5)
					{
						map2[5][27] = BLOCK5;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = TO;
						playerPosX -= playerSpeed;

					}
					if (map2[playerMapY][playerMapX - 1] == BLOCK6)
					{
						map2[6][27] = BLOCK6;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = TO;
						playerPosX -= playerSpeed;

					}
					if (map2[playerMapY][playerMapX - 1] == BLOCK7)
					{
						map2[7][27] = BLOCK7;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = TO;
						playerPosX -= playerSpeed;

					}
					if (map2[playerMapY][playerMapX - 1] == BLOCK8)
					{
						map2[8][27] = BLOCK8;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = TO;
						playerPosX -= playerSpeed;

					}
				}
				if (map2[playerMapY][playerMapX] == NE)
				{
					if (map2[playerMapY][playerMapX - 1] == YUKA)
					{
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = NE;
						if (map2[1][27] != BLOCK1 || map2[1][27] == BLOCK1)
						{
							if (map2[1][27] == BLOCK1 && map2[playerMapY][playerMapX] == map2[4][7])
							{
								map2[playerMapY][playerMapX] = BLOCK1;
								map2[1][27] = YUKA;
							}
						}
						if (map2[2][27] != BLOCK22 || map2[2][27] == BLOCK22)
						{
							if (map2[2][27] == BLOCK22 && map2[playerMapY][playerMapX] == map2[4][9])
							{
								map2[playerMapY][playerMapX] = BLOCK22;
								map2[2][27] = YUKA;
							}
						}
						if (map2[3][27] != BLOCK3 || map2[3][27] == BLOCK3)
						{
							if (map2[3][27] == BLOCK3 && map2[playerMapY][playerMapX] == map2[4][11])
							{
								map2[playerMapY][playerMapX] = BLOCK3;
								map2[3][27] = YUKA;
							}
						}
						if (map2[4][27] != BLOCK4 || map2[4][27] == BLOCK4)
						{
							if (map2[4][27] == BLOCK4 && map2[playerMapY][playerMapX] == map2[4][13])
							{
								map2[playerMapY][playerMapX] = BLOCK4;
								map2[4][27] = YUKA;
							}
						}
						if (map2[5][27] != BLOCK5 || map2[5][27] == BLOCK5)
						{
							if (map2[5][27] == BLOCK5 && map2[playerMapY][playerMapX] == map2[4][15])
							{
								map2[playerMapY][playerMapX] = BLOCK5;
								map2[5][27] = YUKA;
							}
						}
						if (map2[6][27] != BLOCK6 || map2[6][27] == BLOCK6)
						{

							if (map2[6][27] == BLOCK6 && map2[playerMapY][playerMapX] == /*6以降は後で*/map2[4][17])
							{
								map2[playerMapY][playerMapX] = BLOCK6;
								map2[6][27] = YUKA;
							}
						}
						if (map2[7][27] != BLOCK7 || map2[7][27] == BLOCK7)
						{
							if (map2[7][27] == BLOCK7 && map2[playerMapY][playerMapX] == map2[4][19])
							{
								map2[playerMapY][playerMapX] = BLOCK7;
								map2[7][27] = YUKA;
							}
						}
						if (map2[8][27] != BLOCK8 || map2[8][27] == BLOCK8)
						{
							if (map2[8][27] == BLOCK8 && map2[playerMapY][playerMapX] == map2[4][21])
							{
								map2[playerMapY][playerMapX] = BLOCK8;
								map2[8][27] = YUKA;
							}
						}
						playerPosX -= playerSpeed;
					}

					if (map2[playerMapY][playerMapX - 1] == BLOCK1)
					{
						map2[1][27] = BLOCK1;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = NE;
						playerPosX -= playerSpeed;

					}
					if (map2[playerMapY][playerMapX - 1] == BLOCK22)
					{
						map2[2][27] = BLOCK22;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = NE;
						playerPosX -= playerSpeed;

					}
					if (map2[playerMapY][playerMapX - 1] == BLOCK3)
					{
						map2[3][27] = BLOCK3;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = NE;
						playerPosX -= playerSpeed;

					}
					if (map2[playerMapY][playerMapX - 1] == BLOCK4)
					{
						map2[4][27] = BLOCK4;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = NE;
						playerPosX -= playerSpeed;

					}
					if (map2[playerMapY][playerMapX - 1] == BLOCK5)
					{
						map2[5][27] = BLOCK5;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = NE;
						playerPosX -= playerSpeed;

					}
					if (map2[playerMapY][playerMapX - 1] == BLOCK6)
					{
						map2[6][27] = BLOCK6;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = NE;
						playerPosX -= playerSpeed;

					}
					if (map2[playerMapY][playerMapX - 1] == BLOCK7)
					{
						map2[7][27] = BLOCK7;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = NE;
						playerPosX -= playerSpeed;

					}
					if (map2[playerMapY][playerMapX - 1] == BLOCK8)
					{
						map2[8][27] = BLOCK8;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = NE;
						playerPosX -= playerSpeed;

					}
				}

				if (map2[playerMapY][playerMapX] == FU)
				{
					if (map2[playerMapY][playerMapX - 1] == YUKA)
					{
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = FU;
						if (map2[1][27] != BLOCK1 || map2[1][27] == BLOCK1)
						{
							if (map2[1][27] == BLOCK1 && map2[playerMapY][playerMapX] == map2[4][7])
							{
								map2[playerMapY][playerMapX] = BLOCK1;
								map2[1][27] = YUKA;
							}
						}
						if (map2[2][27] != BLOCK22 || map2[2][27] == BLOCK22)
						{
							if (map2[2][27] == BLOCK22 && map2[playerMapY][playerMapX] == map2[4][9])
							{
								map2[playerMapY][playerMapX] = BLOCK22;
								map2[2][27] = YUKA;
							}
						}
						if (map2[3][27] != BLOCK3 || map2[3][27] == BLOCK3)
						{
							if (map2[3][27] == BLOCK3 && map2[playerMapY][playerMapX] == map2[4][11])
							{
								map2[playerMapY][playerMapX] = BLOCK3;
								map2[3][27] = YUKA;
							}
						}
						if (map2[4][27] != BLOCK4 || map2[4][27] == BLOCK4)
						{
							if (map2[4][27] == BLOCK4 && map2[playerMapY][playerMapX] == map2[4][13])
							{
								map2[playerMapY][playerMapX] = BLOCK4;
								map2[4][27] = YUKA;
							}
						}
						if (map2[5][27] != BLOCK5 || map2[5][27] == BLOCK5)
						{
							if (map2[5][27] == BLOCK5 && map2[playerMapY][playerMapX] == map2[4][15])
							{
								map2[playerMapY][playerMapX] = BLOCK5;
								map2[5][27] = YUKA;
							}
						}
						if (map2[6][27] != BLOCK6 || map2[6][27] == BLOCK6)
						{

							if (map2[6][27] == BLOCK6 && map2[playerMapY][playerMapX] == /*6以降は後で*/map2[4][17])
							{
								map2[playerMapY][playerMapX] = BLOCK6;
								map2[6][27] = YUKA;
							}
						}
						if (map2[7][27] != BLOCK7 || map2[7][27] == BLOCK7)
						{
							if (map2[7][27] == BLOCK7 && map2[playerMapY][playerMapX] == map2[4][19])
							{
								map2[playerMapY][playerMapX] = BLOCK7;
								map2[7][27] = YUKA;
							}
						}
						if (map2[8][27] != BLOCK8 || map2[8][27] == BLOCK8)
						{
							if (map2[8][27] == BLOCK8 && map2[playerMapY][playerMapX] == map2[4][21])
							{
								map2[playerMapY][playerMapX] = BLOCK8;
								map2[8][27] = YUKA;
							}
						}
						playerPosX -= playerSpeed;
					}

					if (map2[playerMapY][playerMapX - 1] == BLOCK1)
					{
						map2[1][27] = BLOCK1;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = FU;
						playerPosX -= playerSpeed;

					}
					if (map2[playerMapY][playerMapX - 1] == BLOCK22)
					{
						map2[2][27] = BLOCK22;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = FU;
						playerPosX -= playerSpeed;

					}
					if (map2[playerMapY][playerMapX - 1] == BLOCK3)
					{
						map2[3][27] = BLOCK3;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = FU;
						playerPosX -= playerSpeed;

					}
					if (map2[playerMapY][playerMapX - 1] == BLOCK4)
					{
						map2[4][27] = BLOCK4;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = FU;
						playerPosX -= playerSpeed;

					}
					if (map2[playerMapY][playerMapX - 1] == BLOCK5)
					{
						map2[5][27] = BLOCK5;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = FU;
						playerPosX -= playerSpeed;

					}
					if (map2[playerMapY][playerMapX - 1] == BLOCK6)
					{
						map2[6][27] = BLOCK6;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = FU;
						playerPosX -= playerSpeed;

					}
					if (map2[playerMapY][playerMapX - 1] == BLOCK7)
					{
						map2[7][27] = BLOCK7;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = FU;
						playerPosX -= playerSpeed;

					}
					if (map2[playerMapY][playerMapX - 1] == BLOCK8)
					{
						map2[8][27] = BLOCK8;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = FU;
						playerPosX -= playerSpeed;

					}
				}
				if (map2[playerMapY][playerMapX] == MU)
				{
					if (map2[playerMapY][playerMapX - 1] == YUKA)
					{
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = MU;
						if (map2[1][27] != BLOCK1 || map2[1][27] == BLOCK1)
						{
							if (map2[1][27] == BLOCK1 && map2[playerMapY][playerMapX] == map2[4][7])
							{
								map2[playerMapY][playerMapX] = BLOCK1;
								map2[1][27] = YUKA;
							}
						}
						if (map2[2][27] != BLOCK22 || map2[2][27] == BLOCK22)
						{
							if (map2[2][27] == BLOCK22 && map2[playerMapY][playerMapX] == map2[4][9])
							{
								map2[playerMapY][playerMapX] = BLOCK22;
								map2[2][27] = YUKA;
							}
						}
						if (map2[3][27] != BLOCK3 || map2[3][27] == BLOCK3)
						{
							if (map2[3][27] == BLOCK3 && map2[playerMapY][playerMapX] == map2[4][11])
							{
								map2[playerMapY][playerMapX] = BLOCK3;
								map2[3][27] = YUKA;
							}
						}
						if (map2[4][27] != BLOCK4 || map2[4][27] == BLOCK4)
						{
							if (map2[4][27] == BLOCK4 && map2[playerMapY][playerMapX] == map2[4][13])
							{
								map2[playerMapY][playerMapX] = BLOCK4;
								map2[4][27] = YUKA;
							}
						}
						if (map2[5][27] != BLOCK5 || map2[5][27] == BLOCK5)
						{
							if (map2[5][27] == BLOCK5 && map2[playerMapY][playerMapX] == map2[4][15])
							{
								map2[playerMapY][playerMapX] = BLOCK5;
								map2[5][27] = YUKA;
							}
						}
						if (map2[6][27] != BLOCK6 || map2[6][27] == BLOCK6)
						{

							if (map2[6][27] == BLOCK6 && map2[playerMapY][playerMapX] == /*6以降は後で*/map2[4][17])
							{
								map2[playerMapY][playerMapX] = BLOCK6;
								map2[6][27] = YUKA;
							}
						}
						if (map2[7][27] != BLOCK7 || map2[7][27] == BLOCK7)
						{
							if (map2[7][27] == BLOCK7 && map2[playerMapY][playerMapX] == map2[4][19])
							{
								map2[playerMapY][playerMapX] = BLOCK7;
								map2[7][27] = YUKA;
							}
						}
						if (map2[8][27] != BLOCK8 || map2[8][27] == BLOCK8)
						{
							if (map2[8][27] == BLOCK8 && map2[playerMapY][playerMapX] == map2[4][21])
							{
								map2[playerMapY][playerMapX] = BLOCK8;
								map2[8][27] = YUKA;
							}
						}
						playerPosX -= playerSpeed;
					}

					if (map2[playerMapY][playerMapX - 1] == BLOCK1)
					{
						map2[1][27] = BLOCK1;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = MU;
						playerPosX -= playerSpeed;

					}
					if (map2[playerMapY][playerMapX - 1] == BLOCK22)
					{
						map2[2][27] = BLOCK22;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = MU;
						playerPosX -= playerSpeed;

					}
					if (map2[playerMapY][playerMapX - 1] == BLOCK3)
					{
						map2[3][27] = BLOCK3;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = MU;
						playerPosX -= playerSpeed;

					}
					if (map2[playerMapY][playerMapX - 1] == BLOCK4)
					{
						map2[4][27] = BLOCK4;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = MU;
						playerPosX -= playerSpeed;

					}
					if (map2[playerMapY][playerMapX - 1] == BLOCK5)
					{
						map2[5][27] = BLOCK5;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = MU;
						playerPosX -= playerSpeed;

					}
					if (map2[playerMapY][playerMapX - 1] == BLOCK6)
					{
						map2[6][27] = BLOCK6;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = MU;
						playerPosX -= playerSpeed;

					}
					if (map2[playerMapY][playerMapX - 1] == BLOCK7)
					{
						map2[7][27] = BLOCK7;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = MU;
						playerPosX -= playerSpeed;

					}
					if (map2[playerMapY][playerMapX - 1] == BLOCK8)
					{
						map2[8][27] = BLOCK8;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = MU;
						playerPosX -= playerSpeed;

					}

				}
				if (map2[playerMapY][playerMapX] == MO)
				{
					if (map2[playerMapY][playerMapX - 1] == YUKA)
					{
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = MO;
						if (map2[1][27] != BLOCK1 || map2[1][27] == BLOCK1)
						{
							if (map2[1][27] == BLOCK1 && map2[playerMapY][playerMapX] == map2[4][7])
							{
								map2[playerMapY][playerMapX] = BLOCK1;
								map2[1][27] = YUKA;
							}
						}
						if (map2[2][27] != BLOCK22 || map2[2][27] == BLOCK22)
						{
							if (map2[2][27] == BLOCK22 && map2[playerMapY][playerMapX] == map2[4][9])
							{
								map2[playerMapY][playerMapX] = BLOCK22;
								map2[2][27] = YUKA;
							}
						}
						if (map2[3][27] != BLOCK3 || map2[3][27] == BLOCK3)
						{
							if (map2[3][27] == BLOCK3 && map2[playerMapY][playerMapX] == map2[4][11])
							{
								map2[playerMapY][playerMapX] = BLOCK3;
								map2[3][27] = YUKA;
							}
						}
						if (map2[4][27] != BLOCK4 || map2[4][27] == BLOCK4)
						{
							if (map2[4][27] == BLOCK4 && map2[playerMapY][playerMapX] == map2[4][13])
							{
								map2[playerMapY][playerMapX] = BLOCK4;
								map2[4][27] = YUKA;
							}
						}
						if (map2[5][27] != BLOCK5 || map2[5][27] == BLOCK5)
						{
							if (map2[5][27] == BLOCK5 && map2[playerMapY][playerMapX] == map2[4][15])
							{
								map2[playerMapY][playerMapX] = BLOCK5;
								map2[5][27] = YUKA;
							}
						}
						if (map2[6][27] != BLOCK6 || map2[6][27] == BLOCK6)
						{

							if (map2[6][27] == BLOCK6 && map2[playerMapY][playerMapX] == /*6以降は後で*/map2[4][17])
							{
								map2[playerMapY][playerMapX] = BLOCK6;
								map2[6][27] = YUKA;
							}
						}
						if (map2[7][27] != BLOCK7 || map2[7][27] == BLOCK7)
						{
							if (map2[7][27] == BLOCK7 && map2[playerMapY][playerMapX] == map2[4][19])
							{
								map2[playerMapY][playerMapX] = BLOCK7;
								map2[7][27] = YUKA;
							}
						}
						if (map2[8][27] != BLOCK8 || map2[8][27] == BLOCK8)
						{
							if (map2[8][27] == BLOCK8 && map2[playerMapY][playerMapX] == map2[4][21])
							{
								map2[playerMapY][playerMapX] = BLOCK8;
								map2[8][27] = YUKA;
							}
						}
						playerPosX -= playerSpeed;
					}

					if (map2[playerMapY][playerMapX - 1] == BLOCK1)
					{
						map2[1][27] = BLOCK1;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = MO;
						playerPosX -= playerSpeed;

					}
					if (map2[playerMapY][playerMapX - 1] == BLOCK22)
					{
						map2[2][27] = BLOCK22;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = MO;
						playerPosX -= playerSpeed;

					}
					if (map2[playerMapY][playerMapX - 1] == BLOCK3)
					{
						map2[3][27] = BLOCK3;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = MO;
						playerPosX -= playerSpeed;

					}
					if (map2[playerMapY][playerMapX - 1] == BLOCK4)
					{
						map2[4][27] = BLOCK4;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = MO;
						playerPosX -= playerSpeed;

					}
					if (map2[playerMapY][playerMapX - 1] == BLOCK5)
					{
						map2[5][27] = BLOCK5;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = MO;
						playerPosX -= playerSpeed;

					}
					if (map2[playerMapY][playerMapX - 1] == BLOCK6)
					{
						map2[6][27] = BLOCK6;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = MO;
						playerPosX -= playerSpeed;

					}
					if (map2[playerMapY][playerMapX - 1] == BLOCK7)
					{
						map2[7][27] = BLOCK7;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = MO;
						playerPosX -= playerSpeed;

					}
					if (map2[playerMapY][playerMapX - 1] == BLOCK8)
					{
						map2[8][27] = BLOCK8;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = MO;
						playerPosX -= playerSpeed;

					}
				}
				if (map2[playerMapY][playerMapX] == YO)
				{
					if (map2[playerMapY][playerMapX - 1] == YUKA)
					{
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = YO;
						if (map2[1][27] != BLOCK1 || map2[1][27] == BLOCK1)
						{
							if (map2[1][27] == BLOCK1 && map2[playerMapY][playerMapX] == map2[4][7])
							{
								map2[playerMapY][playerMapX] = BLOCK1;
								map2[1][27] = YUKA;
							}
						}
						if (map2[2][27] != BLOCK22 || map2[2][27] == BLOCK22)
						{
							if (map2[2][27] == BLOCK22 && map2[playerMapY][playerMapX] == map2[4][9])
							{
								map2[playerMapY][playerMapX] = BLOCK22;
								map2[2][27] = YUKA;
							}
						}
						if (map2[3][27] != BLOCK3 || map2[3][27] == BLOCK3)
						{
							if (map2[3][27] == BLOCK3 && map2[playerMapY][playerMapX] == map2[4][11])
							{
								map2[playerMapY][playerMapX] = BLOCK3;
								map2[3][27] = YUKA;
							}
						}
						if (map2[4][27] != BLOCK4 || map2[4][27] == BLOCK4)
						{
							if (map2[4][27] == BLOCK4 && map2[playerMapY][playerMapX] == map2[4][13])
							{
								map2[playerMapY][playerMapX] = BLOCK4;
								map2[4][27] = YUKA;
							}
						}
						if (map2[5][27] != BLOCK5 || map2[5][27] == BLOCK5)
						{
							if (map2[5][27] == BLOCK5 && map2[playerMapY][playerMapX] == map2[4][15])
							{
								map2[playerMapY][playerMapX] = BLOCK5;
								map2[5][27] = YUKA;
							}
						}
						if (map2[6][27] != BLOCK6 || map2[6][27] == BLOCK6)
						{

							if (map2[6][27] == BLOCK6 && map2[playerMapY][playerMapX] == /*6以降は後で*/map2[4][17])
							{
								map2[playerMapY][playerMapX] = BLOCK6;
								map2[6][27] = YUKA;
							}
						}
						if (map2[7][27] != BLOCK7 || map2[7][27] == BLOCK7)
						{
							if (map2[7][27] == BLOCK7 && map2[playerMapY][playerMapX] == map2[4][19])
							{
								map2[playerMapY][playerMapX] = BLOCK7;
								map2[7][27] = YUKA;
							}
						}
						if (map2[8][27] != BLOCK8 || map2[8][27] == BLOCK8)
						{
							if (map2[8][27] == BLOCK8 && map2[playerMapY][playerMapX] == map2[4][21])
							{
								map2[playerMapY][playerMapX] = BLOCK8;
								map2[8][27] = YUKA;
							}
						}
						playerPosX -= playerSpeed;
					}

					if (map2[playerMapY][playerMapX - 1] == BLOCK1)
					{
						map2[1][27] = BLOCK1;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = YO;
						playerPosX -= playerSpeed;

					}
					if (map2[playerMapY][playerMapX - 1] == BLOCK22)
					{
						map2[2][27] = BLOCK22;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = YO;
						playerPosX -= playerSpeed;

					}
					if (map2[playerMapY][playerMapX - 1] == BLOCK3)
					{
						map2[3][27] = BLOCK3;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = YO;
						playerPosX -= playerSpeed;

					}
					if (map2[playerMapY][playerMapX - 1] == BLOCK4)
					{
						map2[4][27] = BLOCK4;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = YO;
						playerPosX -= playerSpeed;

					}
					if (map2[playerMapY][playerMapX - 1] == BLOCK5)
					{
						map2[5][27] = BLOCK5;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = YO;
						playerPosX -= playerSpeed;

					}
					if (map2[playerMapY][playerMapX - 1] == BLOCK6)
					{
						map2[6][27] = BLOCK6;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = YO;
						playerPosX -= playerSpeed;

					}
					if (map2[playerMapY][playerMapX - 1] == BLOCK7)
					{
						map2[7][27] = BLOCK7;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = YO;
						playerPosX -= playerSpeed;

					}
					if (map2[playerMapY][playerMapX - 1] == BLOCK8)
					{
						map2[8][27] = BLOCK8;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = YO;
						playerPosX -= playerSpeed;

					}
				}
				if (map2[playerMapY][playerMapX] == NN)
				{
					if (map2[playerMapY][playerMapX - 1] == YUKA)
					{
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = NN;
						if (map2[1][27] != BLOCK1 || map2[1][27] == BLOCK1)
						{
							if (map2[1][27] == BLOCK1 && map2[playerMapY][playerMapX] == map2[4][7])
							{
								map2[playerMapY][playerMapX] = BLOCK1;
								map2[1][27] = YUKA;
							}
						}
						if (map2[2][27] != BLOCK22 || map2[2][27] == BLOCK22)
						{
							if (map2[2][27] == BLOCK22 && map2[playerMapY][playerMapX] == map2[4][9])
							{
								map2[playerMapY][playerMapX] = BLOCK22;
								map2[2][27] = YUKA;
							}
						}
						if (map2[3][27] != BLOCK3 || map2[3][27] == BLOCK3)
						{
							if (map2[3][27] == BLOCK3 && map2[playerMapY][playerMapX] == map2[4][11])
							{
								map2[playerMapY][playerMapX] = BLOCK3;
								map2[3][27] = YUKA;
							}
						}
						if (map2[4][27] != BLOCK4 || map2[4][27] == BLOCK4)
						{
							if (map2[4][27] == BLOCK4 && map2[playerMapY][playerMapX] == map2[4][13])
							{
								map2[playerMapY][playerMapX] = BLOCK4;
								map2[4][27] = YUKA;
							}
						}
						if (map2[5][27] != BLOCK5 || map2[5][27] == BLOCK5)
						{
							if (map2[5][27] == BLOCK5 && map2[playerMapY][playerMapX] == map2[4][15])
							{
								map2[playerMapY][playerMapX] = BLOCK5;
								map2[5][27] = YUKA;
							}
						}
						if (map2[6][27] != BLOCK6 || map2[6][27] == BLOCK6)
						{

							if (map2[6][27] == BLOCK6 && map2[playerMapY][playerMapX] == /*6以降は後で*/map2[4][17])
							{
								map2[playerMapY][playerMapX] = BLOCK6;
								map2[6][27] = YUKA;
							}
						}
						if (map2[7][27] != BLOCK7 || map2[7][27] == BLOCK7)
						{
							if (map2[7][27] == BLOCK7 && map2[playerMapY][playerMapX] == map2[4][19])
							{
								map2[playerMapY][playerMapX] = BLOCK7;
								map2[7][27] = YUKA;
							}
						}
						if (map2[8][27] != BLOCK8 || map2[8][27] == BLOCK8)
						{
							if (map2[8][27] == BLOCK8 && map2[playerMapY][playerMapX] == map2[4][21])
							{
								map2[playerMapY][playerMapX] = BLOCK8;
								map2[8][27] = YUKA;
							}
						}
						playerPosX -= playerSpeed;
					}

					if (map2[playerMapY][playerMapX - 1] == BLOCK1)
					{
						map2[1][27] = BLOCK1;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = NN;
						playerPosX -= playerSpeed;

					}
					if (map2[playerMapY][playerMapX - 1] == BLOCK22)
					{
						map2[2][27] = BLOCK22;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = NN;
						playerPosX -= playerSpeed;

					}
					if (map2[playerMapY][playerMapX - 1] == BLOCK3)
					{
						map2[3][27] = BLOCK3;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = NN;
						playerPosX -= playerSpeed;

					}
					if (map2[playerMapY][playerMapX - 1] == BLOCK4)
					{
						map2[4][27] = BLOCK4;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = NN;
						playerPosX -= playerSpeed;

					}
					if (map2[playerMapY][playerMapX - 1] == BLOCK5)
					{
						map2[5][27] = BLOCK5;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = NN;
						playerPosX -= playerSpeed;

					}
					if (map2[playerMapY][playerMapX - 1] == BLOCK6)
					{
						map2[6][27] = BLOCK6;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = NN;
						playerPosX -= playerSpeed;

					}
					if (map2[playerMapY][playerMapX - 1] == BLOCK7)
					{
						map2[7][27] = BLOCK7;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = NN;
						playerPosX -= playerSpeed;

					}
					if (map2[playerMapY][playerMapX - 1] == BLOCK8)
					{
						map2[8][27] = BLOCK8;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = NN;
						playerPosX -= playerSpeed;

					}
				}
				if (map2[playerMapY][playerMapX] == ZA)
				{
					if (map2[playerMapY][playerMapX - 1] == YUKA)
					{
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = ZA;
						if (map2[1][27] != BLOCK1 || map2[1][27] == BLOCK1)
						{
							if (map2[1][27] == BLOCK1 && map2[playerMapY][playerMapX] == map2[4][7])
							{
								map2[playerMapY][playerMapX] = BLOCK1;
								map2[1][27] = YUKA;
							}
						}
						if (map2[2][27] != BLOCK22 || map2[2][27] == BLOCK22)
						{
							if (map2[2][27] == BLOCK22 && map2[playerMapY][playerMapX] == map2[4][9])
							{
								map2[playerMapY][playerMapX] = BLOCK22;
								map2[2][27] = YUKA;
							}
						}
						if (map2[3][27] != BLOCK3 || map2[3][27] == BLOCK3)
						{
							if (map2[3][27] == BLOCK3 && map2[playerMapY][playerMapX] == map2[4][11])
							{
								map2[playerMapY][playerMapX] = BLOCK3;
								map2[3][27] = YUKA;
							}
						}
						if (map2[4][27] != BLOCK4 || map2[4][27] == BLOCK4)
						{
							if (map2[4][27] == BLOCK4 && map2[playerMapY][playerMapX] == map2[4][13])
							{
								map2[playerMapY][playerMapX] = BLOCK4;
								map2[4][27] = YUKA;
							}
						}
						if (map2[5][27] != BLOCK5 || map2[5][27] == BLOCK5)
						{
							if (map2[5][27] == BLOCK5 && map2[playerMapY][playerMapX] == map2[4][15])
							{
								map2[playerMapY][playerMapX] = BLOCK5;
								map2[5][27] = YUKA;
							}
						}
						if (map2[6][27] != BLOCK6 || map2[6][27] == BLOCK6)
						{

							if (map2[6][27] == BLOCK6 && map2[playerMapY][playerMapX] == /*6以降は後で*/map2[4][17])
							{
								map2[playerMapY][playerMapX] = BLOCK6;
								map2[6][27] = YUKA;
							}
						}
						if (map2[7][27] != BLOCK7 || map2[7][27] == BLOCK7)
						{
							if (map2[7][27] == BLOCK7 && map2[playerMapY][playerMapX] == map2[4][19])
							{
								map2[playerMapY][playerMapX] = BLOCK7;
								map2[7][27] = YUKA;
							}
						}
						if (map2[8][27] != BLOCK8 || map2[8][27] == BLOCK8)
						{
							if (map2[8][27] == BLOCK8 && map2[playerMapY][playerMapX] == map2[4][21])
							{
								map2[playerMapY][playerMapX] = BLOCK8;
								map2[8][27] = YUKA;
							}
						}
						playerPosX -= playerSpeed;
					}

					if (map2[playerMapY][playerMapX - 1] == BLOCK1)
					{
						map2[1][27] = BLOCK1;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = ZA;
						playerPosX -= playerSpeed;

					}
					if (map2[playerMapY][playerMapX - 1] == BLOCK22)
					{
						map2[2][27] = BLOCK22;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = ZA;
						playerPosX -= playerSpeed;

					}
					if (map2[playerMapY][playerMapX - 1] == BLOCK3)
					{
						map2[3][27] = BLOCK3;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = ZA;
						playerPosX -= playerSpeed;

					}
					if (map2[playerMapY][playerMapX - 1] == BLOCK4)
					{
						map2[4][27] = BLOCK4;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = ZA;
						playerPosX -= playerSpeed;

					}
					if (map2[playerMapY][playerMapX - 1] == BLOCK5)
					{
						map2[5][27] = BLOCK5;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = ZA;
						playerPosX -= playerSpeed;

					}
					if (map2[playerMapY][playerMapX - 1] == BLOCK6)
					{
						map2[6][27] = BLOCK6;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = ZA;
						playerPosX -= playerSpeed;

					}
					if (map2[playerMapY][playerMapX - 1] == BLOCK7)
					{
						map2[7][27] = BLOCK7;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = ZA;
						playerPosX -= playerSpeed;

					}
					if (map2[playerMapY][playerMapX - 1] == BLOCK8)
					{
						map2[8][27] = BLOCK8;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = ZA;
						playerPosX -= playerSpeed;

					}
				}
				if (map2[playerMapY][playerMapX] == ZI)
				{
					if (map2[playerMapY][playerMapX - 1] == YUKA)
					{
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = ZI;
						if (map2[1][27] != BLOCK1 || map2[1][27] == BLOCK1)
						{
							if (map2[1][27] == BLOCK1 && map2[playerMapY][playerMapX] == map2[4][7])
							{
								map2[playerMapY][playerMapX] = BLOCK1;
								map2[1][27] = YUKA;
							}
						}
						if (map2[2][27] != BLOCK22 || map2[2][27] == BLOCK22)
						{
							if (map2[2][27] == BLOCK22 && map2[playerMapY][playerMapX] == map2[4][9])
							{
								map2[playerMapY][playerMapX] = BLOCK22;
								map2[2][27] = YUKA;
							}
						}
						if (map2[3][27] != BLOCK3 || map2[3][27] == BLOCK3)
						{
							if (map2[3][27] == BLOCK3 && map2[playerMapY][playerMapX] == map2[4][11])
							{
								map2[playerMapY][playerMapX] = BLOCK3;
								map2[3][27] = YUKA;
							}
						}
						if (map2[4][27] != BLOCK4 || map2[4][27] == BLOCK4)
						{
							if (map2[4][27] == BLOCK4 && map2[playerMapY][playerMapX] == map2[4][13])
							{
								map2[playerMapY][playerMapX] = BLOCK4;
								map2[4][27] = YUKA;
							}
						}
						if (map2[5][27] != BLOCK5 || map2[5][27] == BLOCK5)
						{
							if (map2[5][27] == BLOCK5 && map2[playerMapY][playerMapX] == map2[4][15])
							{
								map2[playerMapY][playerMapX] = BLOCK5;
								map2[5][27] = YUKA;
							}
						}
						if (map2[6][27] != BLOCK6 || map2[6][27] == BLOCK6)
						{

							if (map2[6][27] == BLOCK6 && map2[playerMapY][playerMapX] == /*6以降は後で*/map2[4][17])
							{
								map2[playerMapY][playerMapX] = BLOCK6;
								map2[6][27] = YUKA;
							}
						}
						if (map2[7][27] != BLOCK7 || map2[7][27] == BLOCK7)
						{
							if (map2[7][27] == BLOCK7 && map2[playerMapY][playerMapX] == map2[4][19])
							{
								map2[playerMapY][playerMapX] = BLOCK7;
								map2[7][27] = YUKA;
							}
						}
						if (map2[8][27] != BLOCK8 || map2[8][27] == BLOCK8)
						{
							if (map2[8][27] == BLOCK8 && map2[playerMapY][playerMapX] == map2[4][21])
							{
								map2[playerMapY][playerMapX] = BLOCK8;
								map2[8][27] = YUKA;
							}
						}
						playerPosX -= playerSpeed;
					}

					if (map2[playerMapY][playerMapX - 1] == BLOCK1)
					{
						map2[1][27] = BLOCK1;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = ZI;
						playerPosX -= playerSpeed;

					}
					if (map2[playerMapY][playerMapX - 1] == BLOCK22)
					{
						map2[2][27] = BLOCK22;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = ZI;
						playerPosX -= playerSpeed;

					}
					if (map2[playerMapY][playerMapX - 1] == BLOCK3)
					{
						map2[3][27] = BLOCK3;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = ZI;
						playerPosX -= playerSpeed;

					}
					if (map2[playerMapY][playerMapX - 1] == BLOCK4)
					{
						map2[4][27] = BLOCK4;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = ZI;
						playerPosX -= playerSpeed;

					}
					if (map2[playerMapY][playerMapX - 1] == BLOCK5)
					{
						map2[5][27] = BLOCK5;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = ZI;
						playerPosX -= playerSpeed;

					}
					if (map2[playerMapY][playerMapX - 1] == BLOCK6)
					{
						map2[6][27] = BLOCK6;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = ZI;
						playerPosX -= playerSpeed;

					}
					if (map2[playerMapY][playerMapX - 1] == BLOCK7)
					{
						map2[7][27] = BLOCK7;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = ZI;
						playerPosX -= playerSpeed;

					}
					if (map2[playerMapY][playerMapX - 1] == BLOCK8)
					{
						map2[8][27] = BLOCK8;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = ZI;
						playerPosX -= playerSpeed;

					}
				}
				if (map2[playerMapY][playerMapX] == BU)
				{
					if (map2[playerMapY][playerMapX - 1] == YUKA)
					{
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = BU;
						if (map2[1][27] != BLOCK1 || map2[1][27] == BLOCK1)
						{
							if (map2[1][27] == BLOCK1 && map2[playerMapY][playerMapX] == map2[4][7])
							{
								map2[playerMapY][playerMapX] = BLOCK1;
								map2[1][27] = YUKA;
							}
						}
						if (map2[2][27] != BLOCK22 || map2[2][27] == BLOCK22)
						{
							if (map2[2][27] == BLOCK22 && map2[playerMapY][playerMapX] == map2[4][9])
							{
								map2[playerMapY][playerMapX] = BLOCK22;
								map2[2][27] = YUKA;
							}
						}
						if (map2[3][27] != BLOCK3 || map2[3][27] == BLOCK3)
						{
							if (map2[3][27] == BLOCK3 && map2[playerMapY][playerMapX] == map2[4][11])
							{
								map2[playerMapY][playerMapX] = BLOCK3;
								map2[3][27] = YUKA;
							}
						}
						if (map2[4][27] != BLOCK4 || map2[4][27] == BLOCK4)
						{
							if (map2[4][27] == BLOCK4 && map2[playerMapY][playerMapX] == map2[4][13])
							{
								map2[playerMapY][playerMapX] = BLOCK4;
								map2[4][27] = YUKA;
							}
						}
						if (map2[5][27] != BLOCK5 || map2[5][27] == BLOCK5)
						{
							if (map2[5][27] == BLOCK5 && map2[playerMapY][playerMapX] == map2[4][15])
							{
								map2[playerMapY][playerMapX] = BLOCK5;
								map2[5][27] = YUKA;
							}
						}
						if (map2[6][27] != BLOCK6 || map2[6][27] == BLOCK6)
						{

							if (map2[6][27] == BLOCK6 && map2[playerMapY][playerMapX] == /*6以降は後で*/map2[4][17])
							{
								map2[playerMapY][playerMapX] = BLOCK6;
								map2[6][27] = YUKA;
							}
						}
						if (map2[7][27] != BLOCK7 || map2[7][27] == BLOCK7)
						{
							if (map2[7][27] == BLOCK7 && map2[playerMapY][playerMapX] == map2[4][19])
							{
								map2[playerMapY][playerMapX] = BLOCK7;
								map2[7][27] = YUKA;
							}
						}
						if (map2[8][27] != BLOCK8 || map2[8][27] == BLOCK8)
						{
							if (map2[8][27] == BLOCK8 && map2[playerMapY][playerMapX] == map2[4][21])
							{
								map2[playerMapY][playerMapX] = BLOCK8;
								map2[8][27] = YUKA;
							}
						}
						playerPosX -= playerSpeed;
					}

					if (map2[playerMapY][playerMapX - 1] == BLOCK1)
					{
						map2[1][27] = BLOCK1;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = BU;
						playerPosX -= playerSpeed;

					}
					if (map2[playerMapY][playerMapX - 1] == BLOCK22)
					{
						map2[2][27] = BLOCK22;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = BU;
						playerPosX -= playerSpeed;

					}
					if (map2[playerMapY][playerMapX - 1] == BLOCK3)
					{
						map2[3][27] = BLOCK3;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = BU;
						playerPosX -= playerSpeed;

					}
					if (map2[playerMapY][playerMapX - 1] == BLOCK4)
					{
						map2[4][27] = BLOCK4;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = BU;
						playerPosX -= playerSpeed;

					}
					if (map2[playerMapY][playerMapX - 1] == BLOCK5)
					{
						map2[5][27] = BLOCK5;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = BU;
						playerPosX -= playerSpeed;

					}
					if (map2[playerMapY][playerMapX - 1] == BLOCK6)
					{
						map2[6][27] = BLOCK6;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = BU;
						playerPosX -= playerSpeed;

					}
					if (map2[playerMapY][playerMapX - 1] == BLOCK7)
					{
						map2[7][27] = BLOCK7;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = BU;
						playerPosX -= playerSpeed;

					}
					if (map2[playerMapY][playerMapX - 1] == BLOCK8)
					{
						map2[8][27] = BLOCK8;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX - 1] = BU;
						playerPosX -= playerSpeed;

					}
				}
			}

			if (keys[DIK_D] && preKeys[DIK_D] == 0 || keys[DIK_RIGHT] && preKeys[DIK_RIGHT] == 0)
			{
				playerTmpX = playerPosX + playerSpeed;
				playerMapX = playerTmpX / KBlockSize;
				//何もないから実際に進ませる
				if (map2[playerMapY][playerMapX] == YUKA)
				{
					playerPosX += playerSpeed;
				}
				if (map2[playerMapY][playerMapX] == GOAL)
				{
					playerPosX += playerSpeed;
				}
				if (map2[playerMapY][playerMapX] == THORN)
				{
					playerPosX += playerSpeed;
				}



				// 99999999999999999999999999999999999999999999999999
				// ここから直して
				if (map2[playerMapY][playerMapX] == U)
				{
					if (map2[playerMapY][playerMapX + 1] == YUKA)
					{
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = U; //ここをUに変える　したも同じ
						if (map2[1][27] != BLOCK1 || map2[1][27] == BLOCK1)
						{
							if (map2[1][27] == BLOCK1 && map2[playerMapY][playerMapX] == map2[4][7])
							{
								map2[playerMapY][playerMapX] = BLOCK1;
								map2[1][27] = YUKA;
							}
						}
						if (map2[2][27] != BLOCK22 || map2[2][27] == BLOCK22)
						{
							if (map2[2][27] == BLOCK22 && map2[playerMapY][playerMapX] == map2[4][9])
							{
								map2[playerMapY][playerMapX] = BLOCK22;
								map2[2][27] = YUKA;
							}
						}
						if (map2[3][27] != BLOCK3 || map2[3][27] == BLOCK3)
						{
							if (map2[3][27] == BLOCK3 && map2[playerMapY][playerMapX] == map2[4][11])
							{
								map2[playerMapY][playerMapX] = BLOCK3;
								map2[3][27] = YUKA;
							}
						}
						if (map2[4][27] != BLOCK4 || map2[4][27] == BLOCK4)
						{
							if (map2[4][27] == BLOCK4 && map2[playerMapY][playerMapX] == map2[4][13])
							{
								map2[playerMapY][playerMapX] = BLOCK4;
								map2[4][27] = YUKA;
							}
						}
						if (map2[5][27] != BLOCK5 || map2[5][27] == BLOCK5)
						{
							if (map2[5][27] == BLOCK5 && map2[playerMapY][playerMapX] == map2[4][15])
							{
								map2[playerMapY][playerMapX] = BLOCK5;
								map2[5][27] = YUKA;
							}
						}
						if (map2[6][27] != BLOCK6 || map2[6][27] == BLOCK6)
						{

							if (map2[6][27] == BLOCK6 && map2[playerMapY][playerMapX] == /*6以降は後で*/map2[4][17])
							{
								map2[playerMapY][playerMapX] = BLOCK6;
								map2[6][27] = YUKA;
							}
						}
						if (map2[7][27] != BLOCK7 || map2[7][27] == BLOCK7)
						{
							if (map2[7][27] == BLOCK7 && map2[playerMapY][playerMapX] == map2[4][19])
							{
								map2[playerMapY][playerMapX] = BLOCK7;
								map2[7][27] = YUKA;
							}
						}
						if (map2[8][27] != BLOCK8 || map2[8][27] == BLOCK8)
						{
							if (map2[8][27] == BLOCK8 && map2[playerMapY][playerMapX] == map2[4][21])
							{
								map2[playerMapY][playerMapX] = BLOCK8;
								map2[8][27] = YUKA;
							}
						}
						playerPosX += playerSpeed;
					}

					if (map2[playerMapY][playerMapX + 1] == BLOCK1)
					{
						map2[1][27] = BLOCK1;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = U;
						playerPosX += playerSpeed;

					}
					if (map2[playerMapY][playerMapX + 1] == BLOCK22)
					{
						map2[2][27] = BLOCK22;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = U;
						playerPosX += playerSpeed;

					}
					if (map2[playerMapY][playerMapX + 1] == BLOCK3)
					{
						map2[3][27] = BLOCK3;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = U;
						playerPosX += playerSpeed;

					}
					if (map2[playerMapY][playerMapX + 1] == BLOCK4)
					{
						map2[4][27] = BLOCK4;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = U;
						playerPosX += playerSpeed;

					}
					if (map2[playerMapY][playerMapX + 1] == BLOCK5)
					{
						map2[5][27] = BLOCK5;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = U;
						playerPosX += playerSpeed;

					}
					if (map2[playerMapY][playerMapX + 1] == BLOCK6)
					{
						map2[6][27] = BLOCK6;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = U;
						playerPosX += playerSpeed;

					}
					if (map2[playerMapY][playerMapX + 1] == BLOCK7)
					{
						map2[7][27] = BLOCK7;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = U;
						playerPosX += playerSpeed;

					}
					if (map2[playerMapY][playerMapX + 1] == BLOCK8)
					{
						map2[8][27] = BLOCK8;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = U;
						playerPosX += playerSpeed;

					}
				}
				if (map2[playerMapY][playerMapX] == E)
				{
					if (map2[playerMapY][playerMapX + 1] == YUKA)
					{
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = E;
						if (map2[1][27] != BLOCK1 || map2[1][27] == BLOCK1)
						{
							if (map2[1][27] == BLOCK1 && map2[playerMapY][playerMapX] == map2[4][7])
							{
								map2[playerMapY][playerMapX] = BLOCK1;
								map2[1][27] = YUKA;
							}
						}
						if (map2[2][27] != BLOCK22 || map2[2][27] == BLOCK22)
						{
							if (map2[2][27] == BLOCK22 && map2[playerMapY][playerMapX] == map2[4][9])
							{
								map2[playerMapY][playerMapX] = BLOCK22;
								map2[2][27] = YUKA;
							}
						}
						if (map2[3][27] != BLOCK3 || map2[3][27] == BLOCK3)
						{
							if (map2[3][27] == BLOCK3 && map2[playerMapY][playerMapX] == map2[4][11])
							{
								map2[playerMapY][playerMapX] = BLOCK3;
								map2[3][27] = YUKA;
							}
						}
						if (map2[4][27] != BLOCK4 || map2[4][27] == BLOCK4)
						{
							if (map2[4][27] == BLOCK4 && map2[playerMapY][playerMapX] == map2[4][13])
							{
								map2[playerMapY][playerMapX] = BLOCK4;
								map2[4][27] = YUKA;
							}
						}
						if (map2[5][27] != BLOCK5 || map2[5][27] == BLOCK5)
						{
							if (map2[5][27] == BLOCK5 && map2[playerMapY][playerMapX] == map2[4][15])
							{
								map2[playerMapY][playerMapX] = BLOCK5;
								map2[5][27] = YUKA;
							}
						}
						if (map2[6][27] != BLOCK6 || map2[6][27] == BLOCK6)
						{

							if (map2[6][27] == BLOCK6 && map2[playerMapY][playerMapX] == /*6以降は後で*/map2[4][17])
							{
								map2[playerMapY][playerMapX] = BLOCK6;
								map2[6][27] = YUKA;
							}
						}
						if (map2[7][27] != BLOCK7 || map2[7][27] == BLOCK7)
						{
							if (map2[7][27] == BLOCK7 && map2[playerMapY][playerMapX] == map2[4][19])
							{
								map2[playerMapY][playerMapX] = BLOCK7;
								map2[7][27] = YUKA;
							}
						}
						if (map2[8][27] != BLOCK8 || map2[8][27] == BLOCK8)
						{
							if (map2[8][27] == BLOCK8 && map2[playerMapY][playerMapX] == map2[4][21])
							{
								map2[playerMapY][playerMapX] = BLOCK8;
								map2[8][27] = YUKA;
							}
						}
						playerPosX += playerSpeed;
					}
					if (map2[playerMapY][playerMapX + 1] == BLOCK1)
					{
						map2[1][27] = BLOCK1;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = E;
						playerPosX += playerSpeed;

					}
					if (map2[playerMapY][playerMapX + 1] == BLOCK22)
					{
						map2[2][27] = BLOCK22;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = E;
						playerPosX += playerSpeed;

					}
					if (map2[playerMapY][playerMapX + 1] == BLOCK3)
					{
						map2[3][27] = BLOCK3;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = E;
						playerPosX += playerSpeed;

					}
					if (map2[playerMapY][playerMapX + 1] == BLOCK4)
					{
						map2[4][27] = BLOCK4;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = E;
						playerPosX += playerSpeed;

					}
					if (map2[playerMapY][playerMapX + 1] == BLOCK5)
					{
						map2[5][27] = BLOCK5;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = E;
						playerPosX += playerSpeed;

					}
					if (map2[playerMapY][playerMapX + 1] == BLOCK6)
					{
						map2[6][27] = BLOCK6;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = E;
						playerPosX += playerSpeed;

					}
					if (map2[playerMapY][playerMapX + 1] == BLOCK7)
					{
						map2[7][27] = BLOCK7;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = E;
						playerPosX += playerSpeed;

					}
					if (map2[playerMapY][playerMapX + 1] == BLOCK8)
					{
						map2[8][27] = BLOCK8;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = E;
						playerPosX += playerSpeed;

					}
				}
				if (map2[playerMapY][playerMapX] == O)
				{
					if (map2[playerMapY][playerMapX + 1] == YUKA)
					{
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = O;
						if (map2[1][27] != BLOCK1 || map2[1][27] == BLOCK1)
						{
							if (map2[1][27] == BLOCK1 && map2[playerMapY][playerMapX] == map2[4][7])
							{
								map2[playerMapY][playerMapX] = BLOCK1;
								map2[1][27] = YUKA;
							}
						}
						if (map2[2][27] != BLOCK22 || map2[2][27] == BLOCK22)
						{
							if (map2[2][27] == BLOCK22 && map2[playerMapY][playerMapX] == map2[4][9])
							{
								map2[playerMapY][playerMapX] = BLOCK22;
								map2[2][27] = YUKA;
							}
						}
						if (map2[3][27] != BLOCK3 || map2[3][27] == BLOCK3)
						{
							if (map2[3][27] == BLOCK3 && map2[playerMapY][playerMapX] == map2[4][11])
							{
								map2[playerMapY][playerMapX] = BLOCK3;
								map2[3][27] = YUKA;
							}
						}
						if (map2[4][27] != BLOCK4 || map2[4][27] == BLOCK4)
						{
							if (map2[4][27] == BLOCK4 && map2[playerMapY][playerMapX] == map2[4][13])
							{
								map2[playerMapY][playerMapX] = BLOCK4;
								map2[4][27] = YUKA;
							}
						}
						if (map2[5][27] != BLOCK5 || map2[5][27] == BLOCK5)
						{
							if (map2[5][27] == BLOCK5 && map2[playerMapY][playerMapX] == map2[4][15])
							{
								map2[playerMapY][playerMapX] = BLOCK5;
								map2[5][27] = YUKA;
							}
						}
						if (map2[6][27] != BLOCK6 || map2[6][27] == BLOCK6)
						{

							if (map2[6][27] == BLOCK6 && map2[playerMapY][playerMapX] == /*6以降は後で*/map2[4][17])
							{
								map2[playerMapY][playerMapX] = BLOCK6;
								map2[6][27] = YUKA;
							}
						}
						if (map2[7][27] != BLOCK7 || map2[7][27] == BLOCK7)
						{
							if (map2[7][27] == BLOCK7 && map2[playerMapY][playerMapX] == map2[4][19])
							{
								map2[playerMapY][playerMapX] = BLOCK7;
								map2[7][27] = YUKA;
							}
						}
						if (map2[8][27] != BLOCK8 || map2[8][27] == BLOCK8)
						{
							if (map2[8][27] == BLOCK8 && map2[playerMapY][playerMapX] == map2[4][21])
							{
								map2[playerMapY][playerMapX] = BLOCK8;
								map2[8][27] = YUKA;
							}
						}
						playerPosX += playerSpeed;
					}

					if (map2[playerMapY][playerMapX + 1] == BLOCK1)
					{
						map2[1][27] = BLOCK1;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = O;
						playerPosX += playerSpeed;

					}
					if (map2[playerMapY][playerMapX + 1] == BLOCK22)
					{
						map2[2][27] = BLOCK22;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = O;
						playerPosX += playerSpeed;

					}
					if (map2[playerMapY][playerMapX + 1] == BLOCK3)
					{
						map2[3][27] = BLOCK3;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = O;
						playerPosX += playerSpeed;

					}
					if (map2[playerMapY][playerMapX + 1] == BLOCK4)
					{
						map2[4][27] = BLOCK4;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = O;
						playerPosX += playerSpeed;

					}
					if (map2[playerMapY][playerMapX + 1] == BLOCK5)
					{
						map2[5][27] = BLOCK5;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = O;
						playerPosX += playerSpeed;

					}
					if (map2[playerMapY][playerMapX + 1] == BLOCK6)
					{
						map2[6][27] = BLOCK6;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = O;
						playerPosX += playerSpeed;

					}
					if (map2[playerMapY][playerMapX + 1] == BLOCK7)
					{
						map2[7][27] = BLOCK7;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = O;
						playerPosX += playerSpeed;

					}
					if (map2[playerMapY][playerMapX + 1] == BLOCK8)
					{
						map2[8][27] = BLOCK8;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = O;
						playerPosX += playerSpeed;

					}
				}
				if (map2[playerMapY][playerMapX] == KA)
				{
					if (map2[playerMapY][playerMapX + 1] == YUKA)
					{
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = KA;
						if (map2[1][27] != BLOCK1 || map2[1][27] == BLOCK1)
						{
							if (map2[1][27] == BLOCK1 && map2[playerMapY][playerMapX] == map2[4][7])
							{
								map2[playerMapY][playerMapX] = BLOCK1;
								map2[1][27] = YUKA;
							}
						}
						if (map2[2][27] != BLOCK22 || map2[2][27] == BLOCK22)
						{
							if (map2[2][27] == BLOCK22 && map2[playerMapY][playerMapX] == map2[4][9])
							{
								map2[playerMapY][playerMapX] = BLOCK22;
								map2[2][27] = YUKA;
							}
						}
						if (map2[3][27] != BLOCK3 || map2[3][27] == BLOCK3)
						{
							if (map2[3][27] == BLOCK3 && map2[playerMapY][playerMapX] == map2[4][11])
							{
								map2[playerMapY][playerMapX] = BLOCK3;
								map2[3][27] = YUKA;
							}
						}
						if (map2[4][27] != BLOCK4 || map2[4][27] == BLOCK4)
						{
							if (map2[4][27] == BLOCK4 && map2[playerMapY][playerMapX] == map2[4][13])
							{
								map2[playerMapY][playerMapX] = BLOCK4;
								map2[4][27] = YUKA;
							}
						}
						if (map2[5][27] != BLOCK5 || map2[5][27] == BLOCK5)
						{
							if (map2[5][27] == BLOCK5 && map2[playerMapY][playerMapX] == map2[4][15])
							{
								map2[playerMapY][playerMapX] = BLOCK5;
								map2[5][27] = YUKA;
							}
						}
						if (map2[6][27] != BLOCK6 || map2[6][27] == BLOCK6)
						{

							if (map2[6][27] == BLOCK6 && map2[playerMapY][playerMapX] == /*6以降は後で*/map2[4][17])
							{
								map2[playerMapY][playerMapX] = BLOCK6;
								map2[6][27] = YUKA;
							}
						}
						if (map2[7][27] != BLOCK7 || map2[7][27] == BLOCK7)
						{
							if (map2[7][27] == BLOCK7 && map2[playerMapY][playerMapX] == map2[4][19])
							{
								map2[playerMapY][playerMapX] = BLOCK7;
								map2[7][27] = YUKA;
							}
						}
						if (map2[8][27] != BLOCK8 || map2[8][27] == BLOCK8)
						{
							if (map2[8][27] == BLOCK8 && map2[playerMapY][playerMapX] == map2[4][21])
							{
								map2[playerMapY][playerMapX] = BLOCK8;
								map2[8][27] = YUKA;
							}
						}
						playerPosX += playerSpeed;
					}

					if (map2[playerMapY][playerMapX + 1] == BLOCK1)
					{
						map2[1][27] = BLOCK1;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = KA;
						playerPosX += playerSpeed;

					}
					if (map2[playerMapY][playerMapX + 1] == BLOCK22)
					{
						map2[2][27] = BLOCK22;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = KA;
						playerPosX += playerSpeed;

					}
					if (map2[playerMapY][playerMapX + 1] == BLOCK3)
					{
						map2[3][27] = BLOCK3;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = KA;
						playerPosX += playerSpeed;

					}
					if (map2[playerMapY][playerMapX + 1] == BLOCK4)
					{
						map2[4][27] = BLOCK4;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = KA;
						playerPosX += playerSpeed;

					}
					if (map2[playerMapY][playerMapX + 1] == BLOCK5)
					{
						map2[5][27] = BLOCK5;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = KA;
						playerPosX += playerSpeed;

					}
					if (map2[playerMapY][playerMapX + 1] == BLOCK6)
					{
						map2[6][27] = BLOCK6;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = KA;
						playerPosX += playerSpeed;

					}
					if (map2[playerMapY][playerMapX + 1] == BLOCK7)
					{
						map2[7][27] = BLOCK7;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = KA;
						playerPosX += playerSpeed;

					}
					if (map2[playerMapY][playerMapX + 1] == BLOCK8)
					{
						map2[8][27] = BLOCK8;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = KA;
						playerPosX += playerSpeed;

					}
				}
				if (map2[playerMapY][playerMapX] == KU)
				{
					if (map2[playerMapY][playerMapX + 1] == YUKA)
					{
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = KU;
						if (map2[1][27] != BLOCK1 || map2[1][27] == BLOCK1)
						{
							if (map2[1][27] == BLOCK1 && map2[playerMapY][playerMapX] == map2[4][7])
							{
								map2[playerMapY][playerMapX] = BLOCK1;
								map2[1][27] = YUKA;
							}
						}
						if (map2[2][27] != BLOCK22 || map2[2][27] == BLOCK22)
						{
							if (map2[2][27] == BLOCK22 && map2[playerMapY][playerMapX] == map2[4][9])
							{
								map2[playerMapY][playerMapX] = BLOCK22;
								map2[2][27] = YUKA;
							}
						}
						if (map2[3][27] != BLOCK3 || map2[3][27] == BLOCK3)
						{
							if (map2[3][27] == BLOCK3 && map2[playerMapY][playerMapX] == map2[4][11])
							{
								map2[playerMapY][playerMapX] = BLOCK3;
								map2[3][27] = YUKA;
							}
						}
						if (map2[4][27] != BLOCK4 || map2[4][27] == BLOCK4)
						{
							if (map2[4][27] == BLOCK4 && map2[playerMapY][playerMapX] == map2[4][13])
							{
								map2[playerMapY][playerMapX] = BLOCK4;
								map2[4][27] = YUKA;
							}
						}
						if (map2[5][27] != BLOCK5 || map2[5][27] == BLOCK5)
						{
							if (map2[5][27] == BLOCK5 && map2[playerMapY][playerMapX] == map2[4][15])
							{
								map2[playerMapY][playerMapX] = BLOCK5;
								map2[5][27] = YUKA;
							}
						}
						if (map2[6][27] != BLOCK6 || map2[6][27] == BLOCK6)
						{

							if (map2[6][27] == BLOCK6 && map2[playerMapY][playerMapX] == /*6以降は後で*/map2[4][17])
							{
								map2[playerMapY][playerMapX] = BLOCK6;
								map2[6][27] = YUKA;
							}
						}
						if (map2[7][27] != BLOCK7 || map2[7][27] == BLOCK7)
						{
							if (map2[7][27] == BLOCK7 && map2[playerMapY][playerMapX] == map2[4][19])
							{
								map2[playerMapY][playerMapX] = BLOCK7;
								map2[7][27] = YUKA;
							}
						}
						if (map2[8][27] != BLOCK8 || map2[8][27] == BLOCK8)
						{
							if (map2[8][27] == BLOCK8 && map2[playerMapY][playerMapX] == map2[4][21])
							{
								map2[playerMapY][playerMapX] = BLOCK8;
								map2[8][27] = YUKA;
							}
						}
						playerPosX += playerSpeed;
					}

					if (map2[playerMapY][playerMapX + 1] == BLOCK1)
					{
						map2[1][27] = BLOCK1;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = KU;
						playerPosX += playerSpeed;

					}
					if (map2[playerMapY][playerMapX + 1] == BLOCK22)
					{
						map2[2][27] = BLOCK22;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = KU;
						playerPosX += playerSpeed;

					}
					if (map2[playerMapY][playerMapX + 1] == BLOCK3)
					{
						map2[3][27] = BLOCK3;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = KU;
						playerPosX += playerSpeed;

					}
					if (map2[playerMapY][playerMapX + 1] == BLOCK4)
					{
						map2[4][27] = BLOCK4;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = KU;
						playerPosX += playerSpeed;

					}
					if (map2[playerMapY][playerMapX + 1] == BLOCK5)
					{
						map2[5][27] = BLOCK5;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = KU;
						playerPosX += playerSpeed;

					}
					if (map2[playerMapY][playerMapX + 1] == BLOCK6)
					{
						map2[6][27] = BLOCK6;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = KU;
						playerPosX += playerSpeed;

					}
					if (map2[playerMapY][playerMapX + 1] == BLOCK7)
					{
						map2[7][27] = BLOCK7;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = KU;
						playerPosX += playerSpeed;

					}
					if (map2[playerMapY][playerMapX + 1] == BLOCK8)
					{
						map2[8][27] = BLOCK8;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = KU;
						playerPosX += playerSpeed;

					}
				}
				if (map2[playerMapY][playerMapX] == SA)
				{
					if (map2[playerMapY][playerMapX + 1] == YUKA)
					{
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = SA;
						if (map2[1][27] != BLOCK1 || map2[1][27] == BLOCK1)
						{
							if (map2[1][27] == BLOCK1 && map2[playerMapY][playerMapX] == map2[4][7])
							{
								map2[playerMapY][playerMapX] = BLOCK1;
								map2[1][27] = YUKA;
							}
						}
						if (map2[2][27] != BLOCK22 || map2[2][27] == BLOCK22)
						{
							if (map2[2][27] == BLOCK22 && map2[playerMapY][playerMapX] == map2[4][9])
							{
								map2[playerMapY][playerMapX] = BLOCK22;
								map2[2][27] = YUKA;
							}
						}
						if (map2[3][27] != BLOCK3 || map2[3][27] == BLOCK3)
						{
							if (map2[3][27] == BLOCK3 && map2[playerMapY][playerMapX] == map2[4][11])
							{
								map2[playerMapY][playerMapX] = BLOCK3;
								map2[3][27] = YUKA;
							}
						}
						if (map2[4][27] != BLOCK4 || map2[4][27] == BLOCK4)
						{
							if (map2[4][27] == BLOCK4 && map2[playerMapY][playerMapX] == map2[4][13])
							{
								map2[playerMapY][playerMapX] = BLOCK4;
								map2[4][27] = YUKA;
							}
						}
						if (map2[5][27] != BLOCK5 || map2[5][27] == BLOCK5)
						{
							if (map2[5][27] == BLOCK5 && map2[playerMapY][playerMapX] == map2[4][15])
							{
								map2[playerMapY][playerMapX] = BLOCK5;
								map2[5][27] = YUKA;
							}
						}
						if (map2[6][27] != BLOCK6 || map2[6][27] == BLOCK6)
						{

							if (map2[6][27] == BLOCK6 && map2[playerMapY][playerMapX] == /*6以降は後で*/map2[4][17])
							{
								map2[playerMapY][playerMapX] = BLOCK6;
								map2[6][27] = YUKA;
							}
						}
						if (map2[7][27] != BLOCK7 || map2[7][27] == BLOCK7)
						{
							if (map2[7][27] == BLOCK7 && map2[playerMapY][playerMapX] == map2[4][19])
							{
								map2[playerMapY][playerMapX] = BLOCK7;
								map2[7][27] = YUKA;
							}
						}
						if (map2[8][27] != BLOCK8 || map2[8][27] == BLOCK8)
						{
							if (map2[8][27] == BLOCK8 && map2[playerMapY][playerMapX] == map2[4][21])
							{
								map2[playerMapY][playerMapX] = BLOCK8;
								map2[8][27] = YUKA;
							}
						}
						playerPosX += playerSpeed;
					}
					if (map2[playerMapY][playerMapX + 1] == BLOCK1)
					{
						map2[1][27] = BLOCK1;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = SA;
						playerPosX += playerSpeed;

					}
					if (map2[playerMapY][playerMapX + 1] == BLOCK22)
					{
						map2[2][27] = BLOCK22;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = SA;
						playerPosX += playerSpeed;

					}
					if (map2[playerMapY][playerMapX + 1] == BLOCK3)
					{
						map2[3][27] = BLOCK3;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = SA;
						playerPosX += playerSpeed;

					}
					if (map2[playerMapY][playerMapX + 1] == BLOCK4)
					{
						map2[4][27] = BLOCK4;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = SA;
						playerPosX += playerSpeed;

					}
					if (map2[playerMapY][playerMapX + 1] == BLOCK5)
					{
						map2[5][27] = BLOCK5;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = SA;
						playerPosX += playerSpeed;

					}
					if (map2[playerMapY][playerMapX + 1] == BLOCK6)
					{
						map2[6][27] = BLOCK6;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = SA;
						playerPosX += playerSpeed;

					}
					if (map2[playerMapY][playerMapX + 1] == BLOCK7)
					{
						map2[7][27] = BLOCK7;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = SA;
						playerPosX += playerSpeed;

					}
					if (map2[playerMapY][playerMapX + 1] == BLOCK8)
					{
						map2[8][27] = BLOCK8;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = SA;
						playerPosX += playerSpeed;

					}
				}
				if (map2[playerMapY][playerMapX] == SHI)
				{
					if (map2[playerMapY][playerMapX + 1] == YUKA)
					{
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = SHI;
						if (map2[1][27] != BLOCK1 || map2[1][27] == BLOCK1)
						{
							if (map2[1][27] == BLOCK1 && map2[playerMapY][playerMapX] == map2[4][7])
							{
								map2[playerMapY][playerMapX] = BLOCK1;
								map2[1][27] = YUKA;
							}
						}
						if (map2[2][27] != BLOCK22 || map2[2][27] == BLOCK22)
						{
							if (map2[2][27] == BLOCK22 && map2[playerMapY][playerMapX] == map2[4][9])
							{
								map2[playerMapY][playerMapX] = BLOCK22;
								map2[2][27] = YUKA;
							}
						}
						if (map2[3][27] != BLOCK3 || map2[3][27] == BLOCK3)
						{
							if (map2[3][27] == BLOCK3 && map2[playerMapY][playerMapX] == map2[4][11])
							{
								map2[playerMapY][playerMapX] = BLOCK3;
								map2[3][27] = YUKA;
							}
						}
						if (map2[4][27] != BLOCK4 || map2[4][27] == BLOCK4)
						{
							if (map2[4][27] == BLOCK4 && map2[playerMapY][playerMapX] == map2[4][13])
							{
								map2[playerMapY][playerMapX] = BLOCK4;
								map2[4][27] = YUKA;
							}
						}
						if (map2[5][27] != BLOCK5 || map2[5][27] == BLOCK5)
						{
							if (map2[5][27] == BLOCK5 && map2[playerMapY][playerMapX] == map2[4][15])
							{
								map2[playerMapY][playerMapX] = BLOCK5;
								map2[5][27] = YUKA;
							}
						}
						if (map2[6][27] != BLOCK6 || map2[6][27] == BLOCK6)
						{

							if (map2[6][27] == BLOCK6 && map2[playerMapY][playerMapX] == /*6以降は後で*/map2[4][17])
							{
								map2[playerMapY][playerMapX] = BLOCK6;
								map2[6][27] = YUKA;
							}
						}
						if (map2[7][27] != BLOCK7 || map2[7][27] == BLOCK7)
						{
							if (map2[7][27] == BLOCK7 && map2[playerMapY][playerMapX] == map2[4][19])
							{
								map2[playerMapY][playerMapX] = BLOCK7;
								map2[7][27] = YUKA;
							}
						}
						if (map2[8][27] != BLOCK8 || map2[8][27] == BLOCK8)
						{
							if (map2[8][27] == BLOCK8 && map2[playerMapY][playerMapX] == map2[4][21])
							{
								map2[playerMapY][playerMapX] = BLOCK8;
								map2[8][27] = YUKA;
							}
						}
						playerPosX += playerSpeed;
					}

					if (map2[playerMapY][playerMapX + 1] == BLOCK1)
					{
						map2[1][27] = BLOCK1;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = SHI;
						playerPosX += playerSpeed;

					}
					if (map2[playerMapY][playerMapX + 1] == BLOCK22)
					{
						map2[2][27] = BLOCK22;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = SHI;
						playerPosX += playerSpeed;

					}
					if (map2[playerMapY][playerMapX + 1] == BLOCK3)
					{
						map2[3][27] = BLOCK3;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = SHI;
						playerPosX += playerSpeed;

					}
					if (map2[playerMapY][playerMapX + 1] == BLOCK4)
					{
						map2[4][27] = BLOCK4;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = SHI;
						playerPosX += playerSpeed;

					}
					if (map2[playerMapY][playerMapX + 1] == BLOCK5)
					{
						map2[5][27] = BLOCK5;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = SHI;
						playerPosX += playerSpeed;

					}
					if (map2[playerMapY][playerMapX + 1] == BLOCK6)
					{
						map2[6][27] = BLOCK6;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = SHI;
						playerPosX += playerSpeed;

					}
					if (map2[playerMapY][playerMapX + 1] == BLOCK7)
					{
						map2[7][27] = BLOCK7;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = SHI;
						playerPosX += playerSpeed;

					}
					if (map2[playerMapY][playerMapX + 1] == BLOCK8)
					{
						map2[8][27] = BLOCK8;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = SHI;
						playerPosX += playerSpeed;

					}
				}
				if (map2[playerMapY][playerMapX] == SU)
				{
					if (map2[playerMapY][playerMapX + 1] == YUKA)
					{
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = SU;
						if (map2[1][27] != BLOCK1 || map2[1][27] == BLOCK1)
						{
							if (map2[1][27] == BLOCK1 && map2[playerMapY][playerMapX] == map2[4][7])
							{
								map2[playerMapY][playerMapX] = BLOCK1;
								map2[1][27] = YUKA;
							}
						}
						if (map2[2][27] != BLOCK22 || map2[2][27] == BLOCK22)
						{
							if (map2[2][27] == BLOCK22 && map2[playerMapY][playerMapX] == map2[4][9])
							{
								map2[playerMapY][playerMapX] = BLOCK22;
								map2[2][27] = YUKA;
							}
						}
						if (map2[3][27] != BLOCK3 || map2[3][27] == BLOCK3)
						{
							if (map2[3][27] == BLOCK3 && map2[playerMapY][playerMapX] == map2[4][11])
							{
								map2[playerMapY][playerMapX] = BLOCK3;
								map2[3][27] = YUKA;
							}
						}
						if (map2[4][27] != BLOCK4 || map2[4][27] == BLOCK4)
						{
							if (map2[4][27] == BLOCK4 && map2[playerMapY][playerMapX] == map2[4][13])
							{
								map2[playerMapY][playerMapX] = BLOCK4;
								map2[4][27] = YUKA;
							}
						}
						if (map2[5][27] != BLOCK5 || map2[5][27] == BLOCK5)
						{
							if (map2[5][27] == BLOCK5 && map2[playerMapY][playerMapX] == map2[4][15])
							{
								map2[playerMapY][playerMapX] = BLOCK5;
								map2[5][27] = YUKA;
							}
						}
						if (map2[6][27] != BLOCK6 || map2[6][27] == BLOCK6)
						{

							if (map2[6][27] == BLOCK6 && map2[playerMapY][playerMapX] == /*6以降は後で*/map2[4][17])
							{
								map2[playerMapY][playerMapX] = BLOCK6;
								map2[6][27] = YUKA;
							}
						}
						if (map2[7][27] != BLOCK7 || map2[7][27] == BLOCK7)
						{
							if (map2[7][27] == BLOCK7 && map2[playerMapY][playerMapX] == map2[4][19])
							{
								map2[playerMapY][playerMapX] = BLOCK7;
								map2[7][27] = YUKA;
							}
						}
						if (map2[8][27] != BLOCK8 || map2[8][27] == BLOCK8)
						{
							if (map2[8][27] == BLOCK8 && map2[playerMapY][playerMapX] == map2[4][21])
							{
								map2[playerMapY][playerMapX] = BLOCK8;
								map2[8][27] = YUKA;
							}
						}
						playerPosX += playerSpeed;
					}

					if (map2[playerMapY][playerMapX + 1] == BLOCK1)
					{
						map2[1][27] = BLOCK1;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = SU;
						playerPosX += playerSpeed;

					}
					if (map2[playerMapY][playerMapX + 1] == BLOCK22)
					{
						map2[2][27] = BLOCK22;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = SU;
						playerPosX += playerSpeed;

					}
					if (map2[playerMapY][playerMapX + 1] == BLOCK3)
					{
						map2[3][27] = BLOCK3;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = SU;
						playerPosX += playerSpeed;

					}
					if (map2[playerMapY][playerMapX + 1] == BLOCK4)
					{
						map2[4][27] = BLOCK4;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = SU;
						playerPosX += playerSpeed;

					}
					if (map2[playerMapY][playerMapX + 1] == BLOCK5)
					{
						map2[5][27] = BLOCK5;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = SU;
						playerPosX += playerSpeed;

					}
					if (map2[playerMapY][playerMapX + 1] == BLOCK6)
					{
						map2[6][27] = BLOCK6;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = SU;
						playerPosX += playerSpeed;

					}
					if (map2[playerMapY][playerMapX + 1] == BLOCK7)
					{
						map2[7][27] = BLOCK7;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = SU;
						playerPosX += playerSpeed;

					}
					if (map2[playerMapY][playerMapX + 1] == BLOCK8)
					{
						map2[8][27] = BLOCK8;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = SU;
						playerPosX += playerSpeed;

					}
				}
				if (map2[playerMapY][playerMapX] == TO)
				{
					if (map2[playerMapY][playerMapX + 1] == YUKA)
					{
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = TO;
						if (map2[1][27] != BLOCK1 || map2[1][27] == BLOCK1)
						{
							if (map2[1][27] == BLOCK1 && map2[playerMapY][playerMapX] == map2[4][7])
							{
								map2[playerMapY][playerMapX] = BLOCK1;
								map2[1][27] = YUKA;
							}
						}
						if (map2[2][27] != BLOCK22 || map2[2][27] == BLOCK22)
						{
							if (map2[2][27] == BLOCK22 && map2[playerMapY][playerMapX] == map2[4][9])
							{
								map2[playerMapY][playerMapX] = BLOCK22;
								map2[2][27] = YUKA;
							}
						}
						if (map2[3][27] != BLOCK3 || map2[3][27] == BLOCK3)
						{
							if (map2[3][27] == BLOCK3 && map2[playerMapY][playerMapX] == map2[4][11])
							{
								map2[playerMapY][playerMapX] = BLOCK3;
								map2[3][27] = YUKA;
							}
						}
						if (map2[4][27] != BLOCK4 || map2[4][27] == BLOCK4)
						{
							if (map2[4][27] == BLOCK4 && map2[playerMapY][playerMapX] == map2[4][13])
							{
								map2[playerMapY][playerMapX] = BLOCK4;
								map2[4][27] = YUKA;
							}
						}
						if (map2[5][27] != BLOCK5 || map2[5][27] == BLOCK5)
						{
							if (map2[5][27] == BLOCK5 && map2[playerMapY][playerMapX] == map2[4][15])
							{
								map2[playerMapY][playerMapX] = BLOCK5;
								map2[5][27] = YUKA;
							}
						}
						if (map2[6][27] != BLOCK6 || map2[6][27] == BLOCK6)
						{

							if (map2[6][27] == BLOCK6 && map2[playerMapY][playerMapX] == /*6以降は後で*/map2[4][17])
							{
								map2[playerMapY][playerMapX] = BLOCK6;
								map2[6][27] = YUKA;
							}
						}
						if (map2[7][27] != BLOCK7 || map2[7][27] == BLOCK7)
						{
							if (map2[7][27] == BLOCK7 && map2[playerMapY][playerMapX] == map2[4][19])
							{
								map2[playerMapY][playerMapX] = BLOCK7;
								map2[7][27] = YUKA;
							}
						}
						if (map2[8][27] != BLOCK8 || map2[8][27] == BLOCK8)
						{
							if (map2[8][27] == BLOCK8 && map2[playerMapY][playerMapX] == map2[4][21])
							{
								map2[playerMapY][playerMapX] = BLOCK8;
								map2[8][27] = YUKA;
							}
						}
						playerPosX += playerSpeed;
					}

					if (map2[playerMapY][playerMapX + 1] == BLOCK1)
					{
						map2[1][27] = BLOCK1;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = TO;
						playerPosX += playerSpeed;

					}
					if (map2[playerMapY][playerMapX + 1] == BLOCK22)
					{
						map2[2][27] = BLOCK22;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = TO;
						playerPosX += playerSpeed;

					}
					if (map2[playerMapY][playerMapX + 1] == BLOCK3)
					{
						map2[3][27] = BLOCK3;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = TO;
						playerPosX += playerSpeed;

					}
					if (map2[playerMapY][playerMapX + 1] == BLOCK4)
					{
						map2[4][27] = BLOCK4;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = TO;
						playerPosX += playerSpeed;

					}
					if (map2[playerMapY][playerMapX + 1] == BLOCK5)
					{
						map2[5][27] = BLOCK5;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = TO;
						playerPosX += playerSpeed;

					}
					if (map2[playerMapY][playerMapX + 1] == BLOCK6)
					{
						map2[6][27] = BLOCK6;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = TO;
						playerPosX += playerSpeed;

					}
					if (map2[playerMapY][playerMapX + 1] == BLOCK7)
					{
						map2[7][27] = BLOCK7;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = TO;
						playerPosX += playerSpeed;

					}
					if (map2[playerMapY][playerMapX + 1] == BLOCK8)
					{
						map2[8][27] = BLOCK8;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = TO;
						playerPosX += playerSpeed;

					}
				}
				if (map2[playerMapY][playerMapX] == NE)
				{
					if (map2[playerMapY][playerMapX + 1] == YUKA)
					{
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = NE;
						if (map2[1][27] != BLOCK1 || map2[1][27] == BLOCK1)
						{
							if (map2[1][27] == BLOCK1 && map2[playerMapY][playerMapX] == map2[4][7])
							{
								map2[playerMapY][playerMapX] = BLOCK1;
								map2[1][27] = YUKA;
							}
						}
						if (map2[2][27] != BLOCK22 || map2[2][27] == BLOCK22)
						{
							if (map2[2][27] == BLOCK22 && map2[playerMapY][playerMapX] == map2[4][9])
							{
								map2[playerMapY][playerMapX] = BLOCK22;
								map2[2][27] = YUKA;
							}
						}
						if (map2[3][27] != BLOCK3 || map2[3][27] == BLOCK3)
						{
							if (map2[3][27] == BLOCK3 && map2[playerMapY][playerMapX] == map2[4][11])
							{
								map2[playerMapY][playerMapX] = BLOCK3;
								map2[3][27] = YUKA;
							}
						}
						if (map2[4][27] != BLOCK4 || map2[4][27] == BLOCK4)
						{
							if (map2[4][27] == BLOCK4 && map2[playerMapY][playerMapX] == map2[4][13])
							{
								map2[playerMapY][playerMapX] = BLOCK4;
								map2[4][27] = YUKA;
							}
						}
						if (map2[5][27] != BLOCK5 || map2[5][27] == BLOCK5)
						{
							if (map2[5][27] == BLOCK5 && map2[playerMapY][playerMapX] == map2[4][15])
							{
								map2[playerMapY][playerMapX] = BLOCK5;
								map2[5][27] = YUKA;
							}
						}
						if (map2[6][27] != BLOCK6 || map2[6][27] == BLOCK6)
						{

							if (map2[6][27] == BLOCK6 && map2[playerMapY][playerMapX] == /*6以降は後で*/map2[4][17])
							{
								map2[playerMapY][playerMapX] = BLOCK6;
								map2[6][27] = YUKA;
							}
						}
						if (map2[7][27] != BLOCK7 || map2[7][27] == BLOCK7)
						{
							if (map2[7][27] == BLOCK7 && map2[playerMapY][playerMapX] == map2[4][19])
							{
								map2[playerMapY][playerMapX] = BLOCK7;
								map2[7][27] = YUKA;
							}
						}
						if (map2[8][27] != BLOCK8 || map2[8][27] == BLOCK8)
						{
							if (map2[8][27] == BLOCK8 && map2[playerMapY][playerMapX] == map2[4][21])
							{
								map2[playerMapY][playerMapX] = BLOCK8;
								map2[8][27] = YUKA;
							}
						}
						playerPosX += playerSpeed;
					}

					if (map2[playerMapY][playerMapX + 1] == BLOCK1)
					{
						map2[1][27] = BLOCK1;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = NE;
						playerPosX += playerSpeed;

					}
					if (map2[playerMapY][playerMapX + 1] == BLOCK22)
					{
						map2[2][27] = BLOCK22;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = NE;
						playerPosX += playerSpeed;

					}
					if (map2[playerMapY][playerMapX + 1] == BLOCK3)
					{
						map2[3][27] = BLOCK3;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = NE;
						playerPosX += playerSpeed;

					}
					if (map2[playerMapY][playerMapX + 1] == BLOCK4)
					{
						map2[4][27] = BLOCK4;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = NE;
						playerPosX += playerSpeed;

					}
					if (map2[playerMapY][playerMapX + 1] == BLOCK5)
					{
						map2[5][27] = BLOCK5;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = NE;
						playerPosX += playerSpeed;

					}
					if (map2[playerMapY][playerMapX + 1] == BLOCK6)
					{
						map2[6][27] = BLOCK6;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = NE;
						playerPosX += playerSpeed;

					}
					if (map2[playerMapY][playerMapX + 1] == BLOCK7)
					{
						map2[7][27] = BLOCK7;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = NE;
						playerPosX += playerSpeed;

					}
					if (map2[playerMapY][playerMapX + 1] == BLOCK8)
					{
						map2[8][27] = BLOCK8;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = NE;
						playerPosX += playerSpeed;

					}
				}

				if (map2[playerMapY][playerMapX] == FU)
				{
					if (map2[playerMapY][playerMapX + 1] == YUKA)
					{
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = FU;
						if (map2[1][27] != BLOCK1 || map2[1][27] == BLOCK1)
						{
							if (map2[1][27] == BLOCK1 && map2[playerMapY][playerMapX] == map2[4][7])
							{
								map2[playerMapY][playerMapX] = BLOCK1;
								map2[1][27] = YUKA;
							}
						}
						if (map2[2][27] != BLOCK22 || map2[2][27] == BLOCK22)
						{
							if (map2[2][27] == BLOCK22 && map2[playerMapY][playerMapX] == map2[4][9])
							{
								map2[playerMapY][playerMapX] = BLOCK22;
								map2[2][27] = YUKA;
							}
						}
						if (map2[3][27] != BLOCK3 || map2[3][27] == BLOCK3)
						{
							if (map2[3][27] == BLOCK3 && map2[playerMapY][playerMapX] == map2[4][11])
							{
								map2[playerMapY][playerMapX] = BLOCK3;
								map2[3][27] = YUKA;
							}
						}
						if (map2[4][27] != BLOCK4 || map2[4][27] == BLOCK4)
						{
							if (map2[4][27] == BLOCK4 && map2[playerMapY][playerMapX] == map2[4][13])
							{
								map2[playerMapY][playerMapX] = BLOCK4;
								map2[4][27] = YUKA;
							}
						}
						if (map2[5][27] != BLOCK5 || map2[5][27] == BLOCK5)
						{
							if (map2[5][27] == BLOCK5 && map2[playerMapY][playerMapX] == map2[4][15])
							{
								map2[playerMapY][playerMapX] = BLOCK5;
								map2[5][27] = YUKA;
							}
						}
						if (map2[6][27] != BLOCK6 || map2[6][27] == BLOCK6)
						{

							if (map2[6][27] == BLOCK6 && map2[playerMapY][playerMapX] == /*6以降は後で*/map2[4][17])
							{
								map2[playerMapY][playerMapX] = BLOCK6;
								map2[6][27] = YUKA;
							}
						}
						if (map2[7][27] != BLOCK7 || map2[7][27] == BLOCK7)
						{
							if (map2[7][27] == BLOCK7 && map2[playerMapY][playerMapX] == map2[4][19])
							{
								map2[playerMapY][playerMapX] = BLOCK7;
								map2[7][27] = YUKA;
							}
						}
						if (map2[8][27] != BLOCK8 || map2[8][27] == BLOCK8)
						{
							if (map2[8][27] == BLOCK8 && map2[playerMapY][playerMapX] == map2[4][21])
							{
								map2[playerMapY][playerMapX] = BLOCK8;
								map2[8][27] = YUKA;
							}
						}
						playerPosX += playerSpeed;
					}

					if (map2[playerMapY][playerMapX + 1] == BLOCK1)
					{
						map2[1][27] = BLOCK1;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = FU;
						playerPosX += playerSpeed;

					}
					if (map2[playerMapY][playerMapX + 1] == BLOCK22)
					{
						map2[2][27] = BLOCK22;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = FU;
						playerPosX += playerSpeed;

					}
					if (map2[playerMapY][playerMapX + 1] == BLOCK3)
					{
						map2[3][27] = BLOCK3;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = FU;
						playerPosX += playerSpeed;

					}
					if (map2[playerMapY][playerMapX + 1] == BLOCK4)
					{
						map2[4][27] = BLOCK4;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = FU;
						playerPosX += playerSpeed;

					}
					if (map2[playerMapY][playerMapX + 1] == BLOCK5)
					{
						map2[5][27] = BLOCK5;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = FU;
						playerPosX += playerSpeed;

					}
					if (map2[playerMapY][playerMapX + 1] == BLOCK6)
					{
						map2[6][27] = BLOCK6;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = FU;
						playerPosX += playerSpeed;

					}
					if (map2[playerMapY][playerMapX + 1] == BLOCK7)
					{
						map2[7][27] = BLOCK7;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = FU;
						playerPosX += playerSpeed;

					}
					if (map2[playerMapY][playerMapX + 1] == BLOCK8)
					{
						map2[8][27] = BLOCK8;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = FU;
						playerPosX += playerSpeed;

					}
				}
				if (map2[playerMapY][playerMapX] == MU)
				{
					if (map2[playerMapY][playerMapX + 1] == YUKA)
					{
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = MU;
						if (map2[1][27] != BLOCK1 || map2[1][27] == BLOCK1)
						{
							if (map2[1][27] == BLOCK1 && map2[playerMapY][playerMapX] == map2[4][7])
							{
								map2[playerMapY][playerMapX] = BLOCK1;
								map2[1][27] = YUKA;
							}
						}
						if (map2[2][27] != BLOCK22 || map2[2][27] == BLOCK22)
						{
							if (map2[2][27] == BLOCK22 && map2[playerMapY][playerMapX] == map2[4][9])
							{
								map2[playerMapY][playerMapX] = BLOCK22;
								map2[2][27] = YUKA;
							}
						}
						if (map2[3][27] != BLOCK3 || map2[3][27] == BLOCK3)
						{
							if (map2[3][27] == BLOCK3 && map2[playerMapY][playerMapX] == map2[4][11])
							{
								map2[playerMapY][playerMapX] = BLOCK3;
								map2[3][27] = YUKA;
							}
						}
						if (map2[4][27] != BLOCK4 || map2[4][27] == BLOCK4)
						{
							if (map2[4][27] == BLOCK4 && map2[playerMapY][playerMapX] == map2[4][13])
							{
								map2[playerMapY][playerMapX] = BLOCK4;
								map2[4][27] = YUKA;
							}
						}
						if (map2[5][27] != BLOCK5 || map2[5][27] == BLOCK5)
						{
							if (map2[5][27] == BLOCK5 && map2[playerMapY][playerMapX] == map2[4][15])
							{
								map2[playerMapY][playerMapX] = BLOCK5;
								map2[5][27] = YUKA;
							}
						}
						if (map2[6][27] != BLOCK6 || map2[6][27] == BLOCK6)
						{

							if (map2[6][27] == BLOCK6 && map2[playerMapY][playerMapX] == /*6以降は後で*/map2[4][17])
							{
								map2[playerMapY][playerMapX] = BLOCK6;
								map2[6][27] = YUKA;
							}
						}
						if (map2[7][27] != BLOCK7 || map2[7][27] == BLOCK7)
						{
							if (map2[7][27] == BLOCK7 && map2[playerMapY][playerMapX] == map2[4][19])
							{
								map2[playerMapY][playerMapX] = BLOCK7;
								map2[7][27] = YUKA;
							}
						}
						if (map2[8][27] != BLOCK8 || map2[8][27] == BLOCK8)
						{
							if (map2[8][27] == BLOCK8 && map2[playerMapY][playerMapX] == map2[4][21])
							{
								map2[playerMapY][playerMapX] = BLOCK8;
								map2[8][27] = YUKA;
							}
						}
						playerPosX += playerSpeed;
					}
					if (map2[playerMapY][playerMapX + 1] == BLOCK1)
					{
						map2[1][27] = BLOCK1;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = MU;
						playerPosX += playerSpeed;

					}
					if (map2[playerMapY][playerMapX + 1] == BLOCK22)
					{
						map2[2][27] = BLOCK22;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = MU;
						playerPosX += playerSpeed;

					}
					if (map2[playerMapY][playerMapX + 1] == BLOCK3)
					{
						map2[3][27] = BLOCK3;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = MU;
						playerPosX += playerSpeed;

					}
					if (map2[playerMapY][playerMapX + 1] == BLOCK4)
					{
						map2[4][27] = BLOCK4;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = MU;
						playerPosX += playerSpeed;

					}
					if (map2[playerMapY][playerMapX + 1] == BLOCK5)
					{
						map2[5][27] = BLOCK5;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = MU;
						playerPosX += playerSpeed;

					}
					if (map2[playerMapY][playerMapX + 1] == BLOCK6)
					{
						map2[6][27] = BLOCK6;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = MU;
						playerPosX += playerSpeed;

					}
					if (map2[playerMapY][playerMapX + 1] == BLOCK7)
					{
						map2[7][27] = BLOCK7;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = MU;
						playerPosX += playerSpeed;

					}
					if (map2[playerMapY][playerMapX + 1] == BLOCK8)
					{
						map2[8][27] = BLOCK8;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = MU;
						playerPosX += playerSpeed;

					}
				}
				if (map2[playerMapY][playerMapX] == MO)
				{
					if (map2[playerMapY][playerMapX + 1] == YUKA)
					{
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = MO;
						if (map2[1][27] != BLOCK1 || map2[1][27] == BLOCK1)
						{
							if (map2[1][27] == BLOCK1 && map2[playerMapY][playerMapX] == map2[4][7])
							{
								map2[playerMapY][playerMapX] = BLOCK1;
								map2[1][27] = YUKA;
							}
						}
						if (map2[2][27] != BLOCK22 || map2[2][27] == BLOCK22)
						{
							if (map2[2][27] == BLOCK22 && map2[playerMapY][playerMapX] == map2[4][9])
							{
								map2[playerMapY][playerMapX] = BLOCK22;
								map2[2][27] = YUKA;
							}
						}
						if (map2[3][27] != BLOCK3 || map2[3][27] == BLOCK3)
						{
							if (map2[3][27] == BLOCK3 && map2[playerMapY][playerMapX] == map2[4][11])
							{
								map2[playerMapY][playerMapX] = BLOCK3;
								map2[3][27] = YUKA;
							}
						}
						if (map2[4][27] != BLOCK4 || map2[4][27] == BLOCK4)
						{
							if (map2[4][27] == BLOCK4 && map2[playerMapY][playerMapX] == map2[4][13])
							{
								map2[playerMapY][playerMapX] = BLOCK4;
								map2[4][27] = YUKA;
							}
						}
						if (map2[5][27] != BLOCK5 || map2[5][27] == BLOCK5)
						{
							if (map2[5][27] == BLOCK5 && map2[playerMapY][playerMapX] == map2[4][15])
							{
								map2[playerMapY][playerMapX] = BLOCK5;
								map2[5][27] = YUKA;
							}
						}
						if (map2[6][27] != BLOCK6 || map2[6][27] == BLOCK6)
						{

							if (map2[6][27] == BLOCK6 && map2[playerMapY][playerMapX] == /*6以降は後で*/map2[4][17])
							{
								map2[playerMapY][playerMapX] = BLOCK6;
								map2[6][27] = YUKA;
							}
						}
						if (map2[7][27] != BLOCK7 || map2[7][27] == BLOCK7)
						{
							if (map2[7][27] == BLOCK7 && map2[playerMapY][playerMapX] == map2[4][19])
							{
								map2[playerMapY][playerMapX] = BLOCK7;
								map2[7][27] = YUKA;
							}
						}
						if (map2[8][27] != BLOCK8 || map2[8][27] == BLOCK8)
						{
							if (map2[8][27] == BLOCK8 && map2[playerMapY][playerMapX] == map2[4][21])
							{
								map2[playerMapY][playerMapX] = BLOCK8;
								map2[8][27] = YUKA;
							}
						}
						playerPosX += playerSpeed;
					}

					if (map2[playerMapY][playerMapX + 1] == BLOCK1)
					{
						map2[1][27] = BLOCK1;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = MO;
						playerPosX += playerSpeed;

					}
					if (map2[playerMapY][playerMapX + 1] == BLOCK22)
					{
						map2[2][27] = BLOCK22;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = MO;
						playerPosX += playerSpeed;

					}
					if (map2[playerMapY][playerMapX + 1] == BLOCK3)
					{
						map2[3][27] = BLOCK3;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = MO;
						playerPosX += playerSpeed;

					}
					if (map2[playerMapY][playerMapX + 1] == BLOCK4)
					{
						map2[4][27] = BLOCK4;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = MO;
						playerPosX += playerSpeed;

					}
					if (map2[playerMapY][playerMapX + 1] == BLOCK5)
					{
						map2[5][27] = BLOCK5;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = MO;
						playerPosX += playerSpeed;

					}
					if (map2[playerMapY][playerMapX + 1] == BLOCK6)
					{
						map2[6][27] = BLOCK6;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = MO;
						playerPosX += playerSpeed;

					}
					if (map2[playerMapY][playerMapX + 1] == BLOCK7)
					{
						map2[7][27] = BLOCK7;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = MO;
						playerPosX += playerSpeed;

					}
					if (map2[playerMapY][playerMapX + 1] == BLOCK8)
					{
						map2[8][27] = BLOCK8;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = MO;
						playerPosX += playerSpeed;

					}
				}
				if (map2[playerMapY][playerMapX] == YO)
				{
					if (map2[playerMapY][playerMapX + 1] == YUKA)
					{
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = YO;
						if (map2[1][27] != BLOCK1 || map2[1][27] == BLOCK1)
						{
							if (map2[1][27] == BLOCK1 && map2[playerMapY][playerMapX] == map2[4][7])
							{
								map2[playerMapY][playerMapX] = BLOCK1;
								map2[1][27] = YUKA;
							}
						}
						if (map2[2][27] != BLOCK22 || map2[2][27] == BLOCK22)
						{
							if (map2[2][27] == BLOCK22 && map2[playerMapY][playerMapX] == map2[4][9])
							{
								map2[playerMapY][playerMapX] = BLOCK22;
								map2[2][27] = YUKA;
							}
						}
						if (map2[3][27] != BLOCK3 || map2[3][27] == BLOCK3)
						{
							if (map2[3][27] == BLOCK3 && map2[playerMapY][playerMapX] == map2[4][11])
							{
								map2[playerMapY][playerMapX] = BLOCK3;
								map2[3][27] = YUKA;
							}
						}
						if (map2[4][27] != BLOCK4 || map2[4][27] == BLOCK4)
						{
							if (map2[4][27] == BLOCK4 && map2[playerMapY][playerMapX] == map2[4][13])
							{
								map2[playerMapY][playerMapX] = BLOCK4;
								map2[4][27] = YUKA;
							}
						}
						if (map2[5][27] != BLOCK5 || map2[5][27] == BLOCK5)
						{
							if (map2[5][27] == BLOCK5 && map2[playerMapY][playerMapX] == map2[4][15])
							{
								map2[playerMapY][playerMapX] = BLOCK5;
								map2[5][27] = YUKA;
							}
						}
						if (map2[6][27] != BLOCK6 || map2[6][27] == BLOCK6)
						{

							if (map2[6][27] == BLOCK6 && map2[playerMapY][playerMapX] == /*6以降は後で*/map2[4][17])
							{
								map2[playerMapY][playerMapX] = BLOCK6;
								map2[6][27] = YUKA;
							}
						}
						if (map2[7][27] != BLOCK7 || map2[7][27] == BLOCK7)
						{
							if (map2[7][27] == BLOCK7 && map2[playerMapY][playerMapX] == map2[4][19])
							{
								map2[playerMapY][playerMapX] = BLOCK7;
								map2[7][27] = YUKA;
							}
						}
						if (map2[8][27] != BLOCK8 || map2[8][27] == BLOCK8)
						{
							if (map2[8][27] == BLOCK8 && map2[playerMapY][playerMapX] == map2[4][21])
							{
								map2[playerMapY][playerMapX] = BLOCK8;
								map2[8][27] = YUKA;
							}
						}
						playerPosX += playerSpeed;
					}

					if (map2[playerMapY][playerMapX + 1] == BLOCK1)
					{
						map2[1][27] = BLOCK1;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = YO;
						playerPosX += playerSpeed;

					}
					if (map2[playerMapY][playerMapX + 1] == BLOCK22)
					{
						map2[2][27] = BLOCK22;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = YO;
						playerPosX += playerSpeed;

					}
					if (map2[playerMapY][playerMapX + 1] == BLOCK3)
					{
						map2[3][27] = BLOCK3;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = YO;
						playerPosX += playerSpeed;

					}
					if (map2[playerMapY][playerMapX + 1] == BLOCK4)
					{
						map2[4][27] = BLOCK4;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = YO;
						playerPosX += playerSpeed;

					}
					if (map2[playerMapY][playerMapX + 1] == BLOCK5)
					{
						map2[5][27] = BLOCK5;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = YO;
						playerPosX += playerSpeed;

					}
					if (map2[playerMapY][playerMapX + 1] == BLOCK6)
					{
						map2[6][27] = BLOCK6;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = YO;
						playerPosX += playerSpeed;

					}
					if (map2[playerMapY][playerMapX + 1] == BLOCK7)
					{
						map2[7][27] = BLOCK7;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = YO;
						playerPosX += playerSpeed;

					}
					if (map2[playerMapY][playerMapX + 1] == BLOCK8)
					{
						map2[8][27] = BLOCK8;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = YO;
						playerPosX += playerSpeed;

					}
				}
				if (map2[playerMapY][playerMapX] == NN)
				{
					if (map2[playerMapY][playerMapX + 1] == YUKA)
					{
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = NN;
						if (map2[1][27] != BLOCK1 || map2[1][27] == BLOCK1)
						{
							if (map2[1][27] == BLOCK1 && map2[playerMapY][playerMapX] == map2[4][7])
							{
								map2[playerMapY][playerMapX] = BLOCK1;
								map2[1][27] = YUKA;
							}
						}
						if (map2[2][27] != BLOCK22 || map2[2][27] == BLOCK22)
						{
							if (map2[2][27] == BLOCK22 && map2[playerMapY][playerMapX] == map2[4][9])
							{
								map2[playerMapY][playerMapX] = BLOCK22;
								map2[2][27] = YUKA;
							}
						}
						if (map2[3][27] != BLOCK3 || map2[3][27] == BLOCK3)
						{
							if (map2[3][27] == BLOCK3 && map2[playerMapY][playerMapX] == map2[4][11])
							{
								map2[playerMapY][playerMapX] = BLOCK3;
								map2[3][27] = YUKA;
							}
						}
						if (map2[4][27] != BLOCK4 || map2[4][27] == BLOCK4)
						{
							if (map2[4][27] == BLOCK4 && map2[playerMapY][playerMapX] == map2[4][13])
							{
								map2[playerMapY][playerMapX] = BLOCK4;
								map2[4][27] = YUKA;
							}
						}
						if (map2[5][27] != BLOCK5 || map2[5][27] == BLOCK5)
						{
							if (map2[5][27] == BLOCK5 && map2[playerMapY][playerMapX] == map2[4][15])
							{
								map2[playerMapY][playerMapX] = BLOCK5;
								map2[5][27] = YUKA;
							}
						}
						if (map2[6][27] != BLOCK6 || map2[6][27] == BLOCK6)
						{

							if (map2[6][27] == BLOCK6 && map2[playerMapY][playerMapX] == /*6以降は後で*/map2[4][17])
							{
								map2[playerMapY][playerMapX] = BLOCK6;
								map2[6][27] = YUKA;
							}
						}
						if (map2[7][27] != BLOCK7 || map2[7][27] == BLOCK7)
						{
							if (map2[7][27] == BLOCK7 && map2[playerMapY][playerMapX] == map2[4][19])
							{
								map2[playerMapY][playerMapX] = BLOCK7;
								map2[7][27] = YUKA;
							}
						}
						if (map2[8][27] != BLOCK8 || map2[8][27] == BLOCK8)
						{
							if (map2[8][27] == BLOCK8 && map2[playerMapY][playerMapX] == map2[4][21])
							{
								map2[playerMapY][playerMapX] = BLOCK8;
								map2[8][27] = YUKA;
							}
						}
						playerPosX += playerSpeed;
					}

					if (map2[playerMapY][playerMapX + 1] == BLOCK1)
					{
						map2[1][27] = BLOCK1;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = NN;
						playerPosX += playerSpeed;

					}
					if (map2[playerMapY][playerMapX + 1] == BLOCK22)
					{
						map2[2][27] = BLOCK22;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = NN;
						playerPosX += playerSpeed;

					}
					if (map2[playerMapY][playerMapX + 1] == BLOCK3)
					{
						map2[3][27] = BLOCK3;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = NN;
						playerPosX += playerSpeed;

					}
					if (map2[playerMapY][playerMapX + 1] == BLOCK4)
					{
						map2[4][27] = BLOCK4;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = NN;
						playerPosX += playerSpeed;

					}
					if (map2[playerMapY][playerMapX + 1] == BLOCK5)
					{
						map2[5][27] = BLOCK5;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = NN;
						playerPosX += playerSpeed;

					}
					if (map2[playerMapY][playerMapX + 1] == BLOCK6)
					{
						map2[6][27] = BLOCK6;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = NN;
						playerPosX += playerSpeed;

					}
					if (map2[playerMapY][playerMapX + 1] == BLOCK7)
					{
						map2[7][27] = BLOCK7;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = NN;
						playerPosX += playerSpeed;

					}
					if (map2[playerMapY][playerMapX + 1] == BLOCK8)
					{
						map2[8][27] = BLOCK8;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = NN;
						playerPosX += playerSpeed;

					}
				}
				if (map2[playerMapY][playerMapX] == ZA)
				{
					if (map2[playerMapY][playerMapX + 1] == YUKA)
					{
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = ZA;
						if (map2[1][27] != BLOCK1 || map2[1][27] == BLOCK1)
						{
							if (map2[1][27] == BLOCK1 && map2[playerMapY][playerMapX] == map2[4][7])
							{
								map2[playerMapY][playerMapX] = BLOCK1;
								map2[1][27] = YUKA;
							}
						}
						if (map2[2][27] != BLOCK22 || map2[2][27] == BLOCK22)
						{
							if (map2[2][27] == BLOCK22 && map2[playerMapY][playerMapX] == map2[4][9])
							{
								map2[playerMapY][playerMapX] = BLOCK22;
								map2[2][27] = YUKA;
							}
						}
						if (map2[3][27] != BLOCK3 || map2[3][27] == BLOCK3)
						{
							if (map2[3][27] == BLOCK3 && map2[playerMapY][playerMapX] == map2[4][11])
							{
								map2[playerMapY][playerMapX] = BLOCK3;
								map2[3][27] = YUKA;
							}
						}
						if (map2[4][27] != BLOCK4 || map2[4][27] == BLOCK4)
						{
							if (map2[4][27] == BLOCK4 && map2[playerMapY][playerMapX] == map2[4][13])
							{
								map2[playerMapY][playerMapX] = BLOCK4;
								map2[4][27] = YUKA;
							}
						}
						if (map2[5][27] != BLOCK5 || map2[5][27] == BLOCK5)
						{
							if (map2[5][27] == BLOCK5 && map2[playerMapY][playerMapX] == map2[4][15])
							{
								map2[playerMapY][playerMapX] = BLOCK5;
								map2[5][27] = YUKA;
							}
						}
						if (map2[6][27] != BLOCK6 || map2[6][27] == BLOCK6)
						{

							if (map2[6][27] == BLOCK6 && map2[playerMapY][playerMapX] == /*6以降は後で*/map2[4][17])
							{
								map2[playerMapY][playerMapX] = BLOCK6;
								map2[6][27] = YUKA;
							}
						}
						if (map2[7][27] != BLOCK7 || map2[7][27] == BLOCK7)
						{
							if (map2[7][27] == BLOCK7 && map2[playerMapY][playerMapX] == map2[4][19])
							{
								map2[playerMapY][playerMapX] = BLOCK7;
								map2[7][27] = YUKA;
							}
						}
						if (map2[8][27] != BLOCK8 || map2[8][27] == BLOCK8)
						{
							if (map2[8][27] == BLOCK8 && map2[playerMapY][playerMapX] == map2[4][21])
							{
								map2[playerMapY][playerMapX] = BLOCK8;
								map2[8][27] = YUKA;
							}
						}
						playerPosX += playerSpeed;
					}

					if (map2[playerMapY][playerMapX + 1] == BLOCK1)
					{
						map2[1][27] = BLOCK1;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = ZA;
						playerPosX += playerSpeed;

					}
					if (map2[playerMapY][playerMapX + 1] == BLOCK22)
					{
						map2[2][27] = BLOCK22;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = ZA;
						playerPosX += playerSpeed;

					}
					if (map2[playerMapY][playerMapX + 1] == BLOCK3)
					{
						map2[3][27] = BLOCK3;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = ZA;
						playerPosX += playerSpeed;

					}
					if (map2[playerMapY][playerMapX + 1] == BLOCK4)
					{
						map2[4][27] = BLOCK4;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = ZA;
						playerPosX += playerSpeed;

					}
					if (map2[playerMapY][playerMapX + 1] == BLOCK5)
					{
						map2[5][27] = BLOCK5;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = ZA;
						playerPosX += playerSpeed;

					}
					if (map2[playerMapY][playerMapX + 1] == BLOCK6)
					{
						map2[6][27] = BLOCK6;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = ZA;
						playerPosX += playerSpeed;

					}
					if (map2[playerMapY][playerMapX + 1] == BLOCK7)
					{
						map2[7][27] = BLOCK7;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = ZA;
						playerPosX += playerSpeed;

					}
					if (map2[playerMapY][playerMapX + 1] == BLOCK8)
					{
						map2[8][27] = BLOCK8;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = ZA;
						playerPosX += playerSpeed;

					}
				}
				if (map2[playerMapY][playerMapX] == ZI)
				{
					if (map2[playerMapY][playerMapX + 1] == YUKA)
					{
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = ZI;
						if (map2[1][27] != BLOCK1 || map2[1][27] == BLOCK1)
						{
							if (map2[1][27] == BLOCK1 && map2[playerMapY][playerMapX] == map2[4][7])
							{
								map2[playerMapY][playerMapX] = BLOCK1;
								map2[1][27] = YUKA;
							}
						}
						if (map2[2][27] != BLOCK22 || map2[2][27] == BLOCK22)
						{
							if (map2[2][27] == BLOCK22 && map2[playerMapY][playerMapX] == map2[4][9])
							{
								map2[playerMapY][playerMapX] = BLOCK22;
								map2[2][27] = YUKA;
							}
						}
						if (map2[3][27] != BLOCK3 || map2[3][27] == BLOCK3)
						{
							if (map2[3][27] == BLOCK3 && map2[playerMapY][playerMapX] == map2[4][11])
							{
								map2[playerMapY][playerMapX] = BLOCK3;
								map2[3][27] = YUKA;
							}
						}
						if (map2[4][27] != BLOCK4 || map2[4][27] == BLOCK4)
						{
							if (map2[4][27] == BLOCK4 && map2[playerMapY][playerMapX] == map2[4][13])
							{
								map2[playerMapY][playerMapX] = BLOCK4;
								map2[4][27] = YUKA;
							}
						}
						if (map2[5][27] != BLOCK5 || map2[5][27] == BLOCK5)
						{
							if (map2[5][27] == BLOCK5 && map2[playerMapY][playerMapX] == map2[4][15])
							{
								map2[playerMapY][playerMapX] = BLOCK5;
								map2[5][27] = YUKA;
							}
						}
						if (map2[6][27] != BLOCK6 || map2[6][27] == BLOCK6)
						{

							if (map2[6][27] == BLOCK6 && map2[playerMapY][playerMapX] == /*6以降は後で*/map2[4][17])
							{
								map2[playerMapY][playerMapX] = BLOCK6;
								map2[6][27] = YUKA;
							}
						}
						if (map2[7][27] != BLOCK7 || map2[7][27] == BLOCK7)
						{
							if (map2[7][27] == BLOCK7 && map2[playerMapY][playerMapX] == map2[4][19])
							{
								map2[playerMapY][playerMapX] = BLOCK7;
								map2[7][27] = YUKA;
							}
						}
						if (map2[8][27] != BLOCK8 || map2[8][27] == BLOCK8)
						{
							if (map2[8][27] == BLOCK8 && map2[playerMapY][playerMapX] == map2[4][21])
							{
								map2[playerMapY][playerMapX] = BLOCK8;
								map2[8][27] = YUKA;
							}
						}
						playerPosX += playerSpeed;
					}

					if (map2[playerMapY][playerMapX + 1] == BLOCK1)
					{
						map2[1][27] = BLOCK1;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = ZI;
						playerPosX += playerSpeed;

					}
					if (map2[playerMapY][playerMapX + 1] == BLOCK22)
					{
						map2[2][27] = BLOCK22;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = ZI;
						playerPosX += playerSpeed;

					}
					if (map2[playerMapY][playerMapX + 1] == BLOCK3)
					{
						map2[3][27] = BLOCK3;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = ZI;
						playerPosX += playerSpeed;

					}
					if (map2[playerMapY][playerMapX + 1] == BLOCK4)
					{
						map2[4][27] = BLOCK4;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = ZI;
						playerPosX += playerSpeed;

					}
					if (map2[playerMapY][playerMapX + 1] == BLOCK5)
					{
						map2[5][27] = BLOCK5;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = ZI;
						playerPosX += playerSpeed;

					}
					if (map2[playerMapY][playerMapX + 1] == BLOCK6)
					{
						map2[6][27] = BLOCK6;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = ZI;
						playerPosX += playerSpeed;

					}
					if (map2[playerMapY][playerMapX + 1] == BLOCK7)
					{
						map2[7][27] = BLOCK7;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = ZI;
						playerPosX += playerSpeed;

					}
					if (map2[playerMapY][playerMapX + 1] == BLOCK8)
					{
						map2[8][27] = BLOCK8;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = ZI;
						playerPosX += playerSpeed;

					}
				}
				if (map2[playerMapY][playerMapX] == BU)
				{
					if (map2[playerMapY][playerMapX + 1] == YUKA)
					{
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = BU;
						if (map2[1][27] != BLOCK1 || map2[1][27] == BLOCK1)
						{
							if (map2[1][27] == BLOCK1 && map2[playerMapY][playerMapX] == map2[4][7])
							{
								map2[playerMapY][playerMapX] = BLOCK1;
								map2[1][27] = YUKA;
							}
						}
						if (map2[2][27] != BLOCK22 || map2[2][27] == BLOCK22)
						{
							if (map2[2][27] == BLOCK22 && map2[playerMapY][playerMapX] == map2[4][9])
							{
								map2[playerMapY][playerMapX] = BLOCK22;
								map2[2][27] = YUKA;
							}
						}
						if (map2[3][27] != BLOCK3 || map2[3][27] == BLOCK3)
						{
							if (map2[3][27] == BLOCK3 && map2[playerMapY][playerMapX] == map2[4][11])
							{
								map2[playerMapY][playerMapX] = BLOCK3;
								map2[3][27] = YUKA;
							}
						}
						if (map2[4][27] != BLOCK4 || map2[4][27] == BLOCK4)
						{
							if (map2[4][27] == BLOCK4 && map2[playerMapY][playerMapX] == map2[4][13])
							{
								map2[playerMapY][playerMapX] = BLOCK4;
								map2[4][27] = YUKA;
							}
						}
						if (map2[5][27] != BLOCK5 || map2[5][27] == BLOCK5)
						{
							if (map2[5][27] == BLOCK5 && map2[playerMapY][playerMapX] == map2[4][15])
							{
								map2[playerMapY][playerMapX] = BLOCK5;
								map2[5][27] = YUKA;
							}
						}
						if (map2[6][27] != BLOCK6 || map2[6][27] == BLOCK6)
						{

							if (map2[6][27] == BLOCK6 && map2[playerMapY][playerMapX] == /*6以降は後で*/map2[4][17])
							{
								map2[playerMapY][playerMapX] = BLOCK6;
								map2[6][27] = YUKA;
							}
						}
						if (map2[7][27] != BLOCK7 || map2[7][27] == BLOCK7)
						{
							if (map2[7][27] == BLOCK7 && map2[playerMapY][playerMapX] == map2[4][19])
							{
								map2[playerMapY][playerMapX] = BLOCK7;
								map2[7][27] = YUKA;
							}
						}
						if (map2[8][27] != BLOCK8 || map2[8][27] == BLOCK8)
						{
							if (map2[8][27] == BLOCK8 && map2[playerMapY][playerMapX] == map2[4][21])
							{
								map2[playerMapY][playerMapX] = BLOCK8;
								map2[8][27] = YUKA;
							}
						}
						playerPosX += playerSpeed;
					}

					if (map2[playerMapY][playerMapX + 1] == BLOCK1)
					{
						map2[1][27] = BLOCK1;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = BU;
						playerPosX += playerSpeed;

					}
					if (map2[playerMapY][playerMapX + 1] == BLOCK22)
					{
						map2[2][27] = BLOCK22;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = BU;
						playerPosX += playerSpeed;

					}
					if (map2[playerMapY][playerMapX + 1] == BLOCK3)
					{
						map2[3][27] = BLOCK3;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = BU;
						playerPosX += playerSpeed;

					}
					if (map2[playerMapY][playerMapX + 1] == BLOCK4)
					{
						map2[4][27] = BLOCK4;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = BU;
						playerPosX += playerSpeed;

					}
					if (map2[playerMapY][playerMapX + 1] == BLOCK5)
					{
						map2[5][27] = BLOCK5;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = BU;
						playerPosX += playerSpeed;

					}
					if (map2[playerMapY][playerMapX + 1] == BLOCK6)
					{
						map2[6][27] = BLOCK6;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = BU;
						playerPosX += playerSpeed;

					}
					if (map2[playerMapY][playerMapX + 1] == BLOCK7)
					{
						map2[7][27] = BLOCK7;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = BU;
						playerPosX += playerSpeed;

					}
					if (map2[playerMapY][playerMapX + 1] == BLOCK8)
					{
						map2[8][27] = BLOCK8;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = BU;
						playerPosX += playerSpeed;

					}
				}

			}

			if (keys[DIK_S] && preKeys[DIK_S] == 0 || keys[DIK_DOWN] && preKeys[DIK_DOWN] == 0)
			{
				playerTmpY = playerPosY + playerSpeed;
				playerMapY = playerTmpY / KBlockSize;
				//何もないから実際に進ませる
				if (map2[playerMapY][playerMapX] == YUKA)
				{
					playerPosY += playerSpeed;
				}
				if (map2[playerMapY][playerMapX] == GOAL)
				{
					playerPosY += playerSpeed;
				}



				// 99999999999999999999999999999999999999999999999999
				// ここから直して
				if (map2[playerMapY][playerMapX] == U)
				{
					if (map2[playerMapY + 1][playerMapX] == YUKA)
					{
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = U; //ここをUに変える　したも同じ
						if (map2[1][27] != BLOCK1 || map2[1][27] == BLOCK1)
						{
							if (map2[1][27] == BLOCK1 && map2[playerMapY][playerMapX] == map2[4][7])
							{
								map2[playerMapY][playerMapX] = BLOCK1;
								map2[1][27] = YUKA;
							}
						}
						if (map2[2][27] != BLOCK22 || map2[2][27] == BLOCK22)
						{
							if (map2[2][27] == BLOCK22 && map2[playerMapY][playerMapX] == map2[4][9])
							{
								map2[playerMapY][playerMapX] = BLOCK22;
								map2[2][27] = YUKA;
							}
						}
						if (map2[3][27] != BLOCK3 || map2[3][27] == BLOCK3)
						{
							if (map2[3][27] == BLOCK3 && map2[playerMapY][playerMapX] == map2[4][11])
							{
								map2[playerMapY][playerMapX] = BLOCK3;
								map2[3][27] = YUKA;
							}
						}
						if (map2[4][27] != BLOCK4 || map2[4][27] == BLOCK4)
						{
							if (map2[4][27] == BLOCK4 && map2[playerMapY][playerMapX] == map2[4][13])
							{
								map2[playerMapY][playerMapX] = BLOCK4;
								map2[4][27] = YUKA;
							}
						}
						if (map2[5][27] != BLOCK5 || map2[5][27] == BLOCK5)
						{
							if (map2[5][27] == BLOCK5 && map2[playerMapY][playerMapX] == map2[4][15])
							{
								map2[playerMapY][playerMapX] = BLOCK5;
								map2[5][27] = YUKA;
							}
						}
						if (map2[6][27] != BLOCK6 || map2[6][27] == BLOCK6)
						{

							if (map2[6][27] == BLOCK6 && map2[playerMapY][playerMapX] == /*6以降は後で*/map2[4][17])
							{
								map2[playerMapY][playerMapX] = BLOCK6;
								map2[6][27] = YUKA;
							}
						}
						if (map2[7][27] != BLOCK7 || map2[7][27] == BLOCK7)
						{
							if (map2[7][27] == BLOCK7 && map2[playerMapY][playerMapX] == map2[4][19])
							{
								map2[playerMapY][playerMapX] = BLOCK7;
								map2[7][27] = YUKA;
							}
						}
						if (map2[8][27] != BLOCK8 || map2[8][27] == BLOCK8)
						{
							if (map2[8][27] == BLOCK8 && map2[playerMapY][playerMapX] == map2[4][21])
							{
								map2[playerMapY][playerMapX] = BLOCK8;
								map2[8][27] = YUKA;
							}
						}
						playerPosY += playerSpeed;
					}

					if (map2[playerMapY + 1][playerMapX] == BLOCK1)
					{
						map2[1][27] = BLOCK1;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = U;
						playerPosY += playerSpeed;

					}
					if (map2[playerMapY + 1][playerMapX] == BLOCK22)
					{
						map2[2][27] = BLOCK22;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = U;
						playerPosY += playerSpeed;

					}
					if (map2[playerMapY + 1][playerMapX] == BLOCK3)
					{
						map2[3][27] = BLOCK3;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = U;
						playerPosY += playerSpeed;

					}
					if (map2[playerMapY + 1][playerMapX] == BLOCK4)
					{
						map2[4][27] = BLOCK4;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = U;
						playerPosY += playerSpeed;

					}
					if (map2[playerMapY + 1][playerMapX] == BLOCK5)
					{
						map2[5][27] = BLOCK5;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = U;
						playerPosY += playerSpeed;

					}
					if (map2[playerMapY + 1][playerMapX] == BLOCK6)
					{
						map2[6][27] = BLOCK6;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = U;
						playerPosY += playerSpeed;

					}
					if (map2[playerMapY + 1][playerMapX] == BLOCK7)
					{
						map2[7][27] = BLOCK7;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = U;
						playerPosY += playerSpeed;

					}
					if (map2[playerMapY + 1][playerMapX] == BLOCK8)
					{
						map2[8][27] = BLOCK8;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = U;
						playerPosY += playerSpeed;

					}
				}
				if (map2[playerMapY][playerMapX] == E)
				{
					if (map2[playerMapY + 1][playerMapX] == YUKA)
					{
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = E;
						if (map2[1][27] != BLOCK1 || map2[1][27] == BLOCK1)
						{
							if (map2[1][27] == BLOCK1 && map2[playerMapY][playerMapX] == map2[4][7])
							{
								map2[playerMapY][playerMapX] = BLOCK1;
								map2[1][27] = YUKA;
							}
						}
						if (map2[2][27] != BLOCK22 || map2[2][27] == BLOCK22)
						{
							if (map2[2][27] == BLOCK22 && map2[playerMapY][playerMapX] == map2[4][9])
							{
								map2[playerMapY][playerMapX] = BLOCK22;
								map2[2][27] = YUKA;
							}
						}
						if (map2[3][27] != BLOCK3 || map2[3][27] == BLOCK3)
						{
							if (map2[3][27] == BLOCK3 && map2[playerMapY][playerMapX] == map2[4][11])
							{
								map2[playerMapY][playerMapX] = BLOCK3;
								map2[3][27] = YUKA;
							}
						}
						if (map2[4][27] != BLOCK4 || map2[4][27] == BLOCK4)
						{
							if (map2[4][27] == BLOCK4 && map2[playerMapY][playerMapX] == map2[4][13])
							{
								map2[playerMapY][playerMapX] = BLOCK4;
								map2[4][27] = YUKA;
							}
						}
						if (map2[5][27] != BLOCK5 || map2[5][27] == BLOCK5)
						{
							if (map2[5][27] == BLOCK5 && map2[playerMapY][playerMapX] == map2[4][15])
							{
								map2[playerMapY][playerMapX] = BLOCK5;
								map2[5][27] = YUKA;
							}
						}
						if (map2[6][27] != BLOCK6 || map2[6][27] == BLOCK6)
						{

							if (map2[6][27] == BLOCK6 && map2[playerMapY][playerMapX] == /*6以降は後で*/map2[4][17])
							{
								map2[playerMapY][playerMapX] = BLOCK6;
								map2[6][27] = YUKA;
							}
						}
						if (map2[7][27] != BLOCK7 || map2[7][27] == BLOCK7)
						{
							if (map2[7][27] == BLOCK7 && map2[playerMapY][playerMapX] == map2[4][19])
							{
								map2[playerMapY][playerMapX] = BLOCK7;
								map2[7][27] = YUKA;
							}
						}
						if (map2[8][27] != BLOCK8 || map2[8][27] == BLOCK8)
						{
							if (map2[8][27] == BLOCK8 && map2[playerMapY][playerMapX] == map2[4][21])
							{
								map2[playerMapY][playerMapX] = BLOCK8;
								map2[8][27] = YUKA;
							}
						}
						playerPosY += playerSpeed;
					}

					if (map2[playerMapY + 1][playerMapX] == BLOCK1)
					{
						map2[1][27] = BLOCK1;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = E;
						playerPosY += playerSpeed;

					}
					if (map2[playerMapY + 1][playerMapX] == BLOCK22)
					{
						map2[2][27] = BLOCK22;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = E;
						playerPosY += playerSpeed;

					}
					if (map2[playerMapY + 1][playerMapX] == BLOCK3)
					{
						map2[3][27] = BLOCK3;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = E;
						playerPosY += playerSpeed;

					}
					if (map2[playerMapY + 1][playerMapX] == BLOCK4)
					{
						map2[4][27] = BLOCK4;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = E;
						playerPosY += playerSpeed;

					}
					if (map2[playerMapY + 1][playerMapX] == BLOCK5)
					{
						map2[5][27] = BLOCK5;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = E;
						playerPosY += playerSpeed;

					}
					if (map2[playerMapY + 1][playerMapX] == BLOCK6)
					{
						map2[6][27] = BLOCK6;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = E;
						playerPosY += playerSpeed;

					}
					if (map2[playerMapY + 1][playerMapX] == BLOCK7)
					{
						map2[7][27] = BLOCK7;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = E;
						playerPosY += playerSpeed;

					}
					if (map2[playerMapY + 1][playerMapX] == BLOCK8)
					{
						map2[8][27] = BLOCK8;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = E;
						playerPosY += playerSpeed;

					}
				}

				if (map2[playerMapY][playerMapX] == O)
				{
					if (map2[playerMapY + 1][playerMapX] == YUKA)
					{
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = O;
						if (map2[1][27] != BLOCK1 || map2[1][27] == BLOCK1)
						{
							if (map2[1][27] == BLOCK1 && map2[playerMapY][playerMapX] == map2[4][7])
							{
								map2[playerMapY][playerMapX] = BLOCK1;
								map2[1][27] = YUKA;
							}
						}
						if (map2[2][27] != BLOCK22 || map2[2][27] == BLOCK22)
						{
							if (map2[2][27] == BLOCK22 && map2[playerMapY][playerMapX] == map2[4][9])
							{
								map2[playerMapY][playerMapX] = BLOCK22;
								map2[2][27] = YUKA;
							}
						}
						if (map2[3][27] != BLOCK3 || map2[3][27] == BLOCK3)
						{
							if (map2[3][27] == BLOCK3 && map2[playerMapY][playerMapX] == map2[4][11])
							{
								map2[playerMapY][playerMapX] = BLOCK3;
								map2[3][27] = YUKA;
							}
						}
						if (map2[4][27] != BLOCK4 || map2[4][27] == BLOCK4)
						{
							if (map2[4][27] == BLOCK4 && map2[playerMapY][playerMapX] == map2[4][13])
							{
								map2[playerMapY][playerMapX] = BLOCK4;
								map2[4][27] = YUKA;
							}
						}
						if (map2[5][27] != BLOCK5 || map2[5][27] == BLOCK5)
						{
							if (map2[5][27] == BLOCK5 && map2[playerMapY][playerMapX] == map2[4][15])
							{
								map2[playerMapY][playerMapX] = BLOCK5;
								map2[5][27] = YUKA;
							}
						}
						if (map2[6][27] != BLOCK6 || map2[6][27] == BLOCK6)
						{

							if (map2[6][27] == BLOCK6 && map2[playerMapY][playerMapX] == /*6以降は後で*/map2[4][17])
							{
								map2[playerMapY][playerMapX] = BLOCK6;
								map2[6][27] = YUKA;
							}
						}
						if (map2[7][27] != BLOCK7 || map2[7][27] == BLOCK7)
						{
							if (map2[7][27] == BLOCK7 && map2[playerMapY][playerMapX] == map2[4][19])
							{
								map2[playerMapY][playerMapX] = BLOCK7;
								map2[7][27] = YUKA;
							}
						}
						if (map2[8][27] != BLOCK8 || map2[8][27] == BLOCK8)
						{
							if (map2[8][27] == BLOCK8 && map2[playerMapY][playerMapX] == map2[4][21])
							{
								map2[playerMapY][playerMapX] = BLOCK8;
								map2[8][27] = YUKA;
							}
						}
						playerPosY += playerSpeed;
					}

					if (map2[playerMapY + 1][playerMapX] == BLOCK1)
					{
						map2[1][27] = BLOCK1;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = O;
						playerPosY += playerSpeed;

					}
					if (map2[playerMapY + 1][playerMapX] == BLOCK22)
					{
						map2[2][27] = BLOCK22;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = O;
						playerPosY += playerSpeed;

					}
					if (map2[playerMapY + 1][playerMapX] == BLOCK3)
					{
						map2[3][27] = BLOCK3;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = O;
						playerPosY += playerSpeed;

					}
					if (map2[playerMapY + 1][playerMapX] == BLOCK4)
					{
						map2[4][27] = BLOCK4;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = O;
						playerPosY += playerSpeed;

					}
					if (map2[playerMapY + 1][playerMapX] == BLOCK5)
					{
						map2[5][27] = BLOCK5;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = O;
						playerPosY += playerSpeed;

					}
					if (map2[playerMapY + 1][playerMapX] == BLOCK6)
					{
						map2[6][27] = BLOCK6;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = O;
						playerPosY += playerSpeed;

					}
					if (map2[playerMapY + 1][playerMapX] == BLOCK7)
					{
						map2[7][27] = BLOCK7;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = O;
						playerPosY += playerSpeed;

					}
					if (map2[playerMapY + 1][playerMapX] == BLOCK8)
					{
						map2[8][27] = BLOCK8;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = O;
						playerPosY += playerSpeed;

					}
				}

				if (map2[playerMapY][playerMapX] == KA)
				{
					if (map2[playerMapY + 1][playerMapX] == YUKA)
					{
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = KA;
						if (map2[1][27] != BLOCK1 || map2[1][27] == BLOCK1)
						{
							if (map2[1][27] == BLOCK1 && map2[playerMapY][playerMapX] == map2[4][7])
							{
								map2[playerMapY][playerMapX] = BLOCK1;
								map2[1][27] = YUKA;
							}
						}
						if (map2[2][27] != BLOCK22 || map2[2][27] == BLOCK22)
						{
							if (map2[2][27] == BLOCK22 && map2[playerMapY][playerMapX] == map2[4][9])
							{
								map2[playerMapY][playerMapX] = BLOCK22;
								map2[2][27] = YUKA;
							}
						}
						if (map2[3][27] != BLOCK3 || map2[3][27] == BLOCK3)
						{
							if (map2[3][27] == BLOCK3 && map2[playerMapY][playerMapX] == map2[4][11])
							{
								map2[playerMapY][playerMapX] = BLOCK3;
								map2[3][27] = YUKA;
							}
						}
						if (map2[4][27] != BLOCK4 || map2[4][27] == BLOCK4)
						{
							if (map2[4][27] == BLOCK4 && map2[playerMapY][playerMapX] == map2[4][13])
							{
								map2[playerMapY][playerMapX] = BLOCK4;
								map2[4][27] = YUKA;
							}
						}
						if (map2[5][27] != BLOCK5 || map2[5][27] == BLOCK5)
						{
							if (map2[5][27] == BLOCK5 && map2[playerMapY][playerMapX] == map2[4][15])
							{
								map2[playerMapY][playerMapX] = BLOCK5;
								map2[5][27] = YUKA;
							}
						}
						if (map2[6][27] != BLOCK6 || map2[6][27] == BLOCK6)
						{

							if (map2[6][27] == BLOCK6 && map2[playerMapY][playerMapX] == /*6以降は後で*/map2[4][17])
							{
								map2[playerMapY][playerMapX] = BLOCK6;
								map2[6][27] = YUKA;
							}
						}
						if (map2[7][27] != BLOCK7 || map2[7][27] == BLOCK7)
						{
							if (map2[7][27] == BLOCK7 && map2[playerMapY][playerMapX] == map2[4][19])
							{
								map2[playerMapY][playerMapX] = BLOCK7;
								map2[7][27] = YUKA;
							}
						}
						if (map2[8][27] != BLOCK8 || map2[8][27] == BLOCK8)
						{
							if (map2[8][27] == BLOCK8 && map2[playerMapY][playerMapX] == map2[4][21])
							{
								map2[playerMapY][playerMapX] = BLOCK8;
								map2[8][27] = YUKA;
							}
						}
						playerPosY += playerSpeed;
					}


					if (map2[playerMapY + 1][playerMapX] == BLOCK1)
					{
						map2[1][27] = BLOCK1;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = KA;
						playerPosY += playerSpeed;

					}
					if (map2[playerMapY + 1][playerMapX] == BLOCK22)
					{
						map2[2][27] = BLOCK22;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = KA;
						playerPosY += playerSpeed;

					}
					if (map2[playerMapY + 1][playerMapX] == BLOCK3)
					{
						map2[3][27] = BLOCK3;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = KA;
						playerPosY += playerSpeed;

					}
					if (map2[playerMapY + 1][playerMapX] == BLOCK4)
					{
						map2[4][27] = BLOCK4;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = KA;
						playerPosY += playerSpeed;

					}
					if (map2[playerMapY + 1][playerMapX] == BLOCK5)
					{
						map2[5][27] = BLOCK5;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = KA;
						playerPosY += playerSpeed;

					}
					if (map2[playerMapY + 1][playerMapX] == BLOCK6)
					{
						map2[6][27] = BLOCK6;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = KA;
						playerPosY += playerSpeed;

					}
					if (map2[playerMapY + 1][playerMapX] == BLOCK7)
					{
						map2[7][27] = BLOCK7;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = KA;
						playerPosY += playerSpeed;

					}
					if (map2[playerMapY + 1][playerMapX] == BLOCK8)
					{
						map2[8][27] = BLOCK8;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = KA;
						playerPosY += playerSpeed;

					}
				}
				if (map2[playerMapY][playerMapX] == KU)
				{
					if (map2[playerMapY + 1][playerMapX] == YUKA)
					{
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = KU;
						if (map2[1][27] != BLOCK1 || map2[1][27] == BLOCK1)
						{
							if (map2[1][27] == BLOCK1 && map2[playerMapY][playerMapX] == map2[4][7])
							{
								map2[playerMapY][playerMapX] = BLOCK1;
								map2[1][27] = YUKA;
							}
						}
						if (map2[2][27] != BLOCK22 || map2[2][27] == BLOCK22)
						{
							if (map2[2][27] == BLOCK22 && map2[playerMapY][playerMapX] == map2[4][9])
							{
								map2[playerMapY][playerMapX] = BLOCK22;
								map2[2][27] = YUKA;
							}
						}
						if (map2[3][27] != BLOCK3 || map2[3][27] == BLOCK3)
						{
							if (map2[3][27] == BLOCK3 && map2[playerMapY][playerMapX] == map2[4][11])
							{
								map2[playerMapY][playerMapX] = BLOCK3;
								map2[3][27] = YUKA;
							}
						}
						if (map2[4][27] != BLOCK4 || map2[4][27] == BLOCK4)
						{
							if (map2[4][27] == BLOCK4 && map2[playerMapY][playerMapX] == map2[4][13])
							{
								map2[playerMapY][playerMapX] = BLOCK4;
								map2[4][27] = YUKA;
							}
						}
						if (map2[5][27] != BLOCK5 || map2[5][27] == BLOCK5)
						{
							if (map2[5][27] == BLOCK5 && map2[playerMapY][playerMapX] == map2[4][15])
							{
								map2[playerMapY][playerMapX] = BLOCK5;
								map2[5][27] = YUKA;
							}
						}
						if (map2[6][27] != BLOCK6 || map2[6][27] == BLOCK6)
						{

							if (map2[6][27] == BLOCK6 && map2[playerMapY][playerMapX] == /*6以降は後で*/map2[4][17])
							{
								map2[playerMapY][playerMapX] = BLOCK6;
								map2[6][27] = YUKA;
							}
						}
						if (map2[7][27] != BLOCK7 || map2[7][27] == BLOCK7)
						{
							if (map2[7][27] == BLOCK7 && map2[playerMapY][playerMapX] == map2[4][19])
							{
								map2[playerMapY][playerMapX] = BLOCK7;
								map2[7][27] = YUKA;
							}
						}
						if (map2[8][27] != BLOCK8 || map2[8][27] == BLOCK8)
						{
							if (map2[8][27] == BLOCK8 && map2[playerMapY][playerMapX] == map2[4][21])
							{
								map2[playerMapY][playerMapX] = BLOCK8;
								map2[8][27] = YUKA;
							}
						}
						playerPosY += playerSpeed;
					}


					if (map2[playerMapY + 1][playerMapX] == BLOCK1)
					{
						map2[1][27] = BLOCK1;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = KU;
						playerPosY += playerSpeed;

					}
					if (map2[playerMapY + 1][playerMapX] == BLOCK22)
					{
						map2[2][27] = BLOCK22;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = KU;
						playerPosY += playerSpeed;

					}
					if (map2[playerMapY + 1][playerMapX] == BLOCK3)
					{
						map2[3][27] = BLOCK3;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = KU;
						playerPosY += playerSpeed;

					}
					if (map2[playerMapY + 1][playerMapX] == BLOCK4)
					{
						map2[4][27] = BLOCK4;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = KU;
						playerPosY += playerSpeed;

					}
					if (map2[playerMapY + 1][playerMapX] == BLOCK5)
					{
						map2[5][27] = BLOCK5;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = KU;
						playerPosY += playerSpeed;

					}
					if (map2[playerMapY + 1][playerMapX] == BLOCK6)
					{
						map2[6][27] = BLOCK6;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = KU;
						playerPosY += playerSpeed;

					}
					if (map2[playerMapY + 1][playerMapX] == BLOCK7)
					{
						map2[7][27] = BLOCK7;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = KU;
						playerPosY += playerSpeed;

					}
					if (map2[playerMapY + 1][playerMapX] == BLOCK8)
					{
						map2[8][27] = BLOCK8;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = KU;
						playerPosY += playerSpeed;

					}
				}

				if (map2[playerMapY][playerMapX] == SA)
				{
					if (map2[playerMapY + 1][playerMapX] == YUKA)
					{
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = SA;
						if (map2[1][27] != BLOCK1 || map2[1][27] == BLOCK1)
						{
							if (map2[1][27] == BLOCK1 && map2[playerMapY][playerMapX] == map2[4][7])
							{
								map2[playerMapY][playerMapX] = BLOCK1;
								map2[1][27] = YUKA;
							}
						}
						if (map2[2][27] != BLOCK22 || map2[2][27] == BLOCK22)
						{
							if (map2[2][27] == BLOCK22 && map2[playerMapY][playerMapX] == map2[4][9])
							{
								map2[playerMapY][playerMapX] = BLOCK22;
								map2[2][27] = YUKA;
							}
						}
						if (map2[3][27] != BLOCK3 || map2[3][27] == BLOCK3)
						{
							if (map2[3][27] == BLOCK3 && map2[playerMapY][playerMapX] == map2[4][11])
							{
								map2[playerMapY][playerMapX] = BLOCK3;
								map2[3][27] = YUKA;
							}
						}
						if (map2[4][27] != BLOCK4 || map2[4][27] == BLOCK4)
						{
							if (map2[4][27] == BLOCK4 && map2[playerMapY][playerMapX] == map2[4][13])
							{
								map2[playerMapY][playerMapX] = BLOCK4;
								map2[4][27] = YUKA;
							}
						}
						if (map2[5][27] != BLOCK5 || map2[5][27] == BLOCK5)
						{
							if (map2[5][27] == BLOCK5 && map2[playerMapY][playerMapX] == map2[4][15])
							{
								map2[playerMapY][playerMapX] = BLOCK5;
								map2[5][27] = YUKA;
							}
						}
						if (map2[6][27] != BLOCK6 || map2[6][27] == BLOCK6)
						{

							if (map2[6][27] == BLOCK6 && map2[playerMapY][playerMapX] == /*6以降は後で*/map2[4][17])
							{
								map2[playerMapY][playerMapX] = BLOCK6;
								map2[6][27] = YUKA;
							}
						}
						if (map2[7][27] != BLOCK7 || map2[7][27] == BLOCK7)
						{
							if (map2[7][27] == BLOCK7 && map2[playerMapY][playerMapX] == map2[4][19])
							{
								map2[playerMapY][playerMapX] = BLOCK7;
								map2[7][27] = YUKA;
							}
						}
						if (map2[8][27] != BLOCK8 || map2[8][27] == BLOCK8)
						{
							if (map2[8][27] == BLOCK8 && map2[playerMapY][playerMapX] == map2[4][21])
							{
								map2[playerMapY][playerMapX] = BLOCK8;
								map2[8][27] = YUKA;
							}
						}
						playerPosY += playerSpeed;
					}

					if (map2[playerMapY + 1][playerMapX] == BLOCK1)
					{
						map2[1][27] = BLOCK1;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = SA;
						playerPosY += playerSpeed;

					}
					if (map2[playerMapY + 1][playerMapX] == BLOCK22)
					{
						map2[2][27] = BLOCK22;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = SA;
						playerPosY += playerSpeed;

					}
					if (map2[playerMapY + 1][playerMapX] == BLOCK3)
					{
						map2[3][27] = BLOCK3;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = SA;
						playerPosY += playerSpeed;

					}
					if (map2[playerMapY + 1][playerMapX] == BLOCK4)
					{
						map2[4][27] = BLOCK4;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = SA;
						playerPosY += playerSpeed;

					}
					if (map2[playerMapY + 1][playerMapX] == BLOCK5)
					{
						map2[5][27] = BLOCK5;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = SA;
						playerPosY += playerSpeed;

					}
					if (map2[playerMapY + 1][playerMapX] == BLOCK6)
					{
						map2[6][27] = BLOCK6;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = SA;
						playerPosY += playerSpeed;

					}
					if (map2[playerMapY + 1][playerMapX] == BLOCK7)
					{
						map2[7][27] = BLOCK7;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = SA;
						playerPosY += playerSpeed;

					}
					if (map2[playerMapY + 1][playerMapX] == BLOCK8)
					{
						map2[8][27] = BLOCK8;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = SA;
						playerPosY += playerSpeed;

					}
				}
				if (map2[playerMapY][playerMapX] == SHI)
				{
					if (map2[playerMapY + 1][playerMapX] == YUKA)
					{
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = SHI;
						if (map2[1][27] != BLOCK1 || map2[1][27] == BLOCK1)
						{
							if (map2[1][27] == BLOCK1 && map2[playerMapY][playerMapX] == map2[4][7])
							{
								map2[playerMapY][playerMapX] = BLOCK1;
								map2[1][27] = YUKA;
							}
						}
						if (map2[2][27] != BLOCK22 || map2[2][27] == BLOCK22)
						{
							if (map2[2][27] == BLOCK22 && map2[playerMapY][playerMapX] == map2[4][9])
							{
								map2[playerMapY][playerMapX] = BLOCK22;
								map2[2][27] = YUKA;
							}
						}
						if (map2[3][27] != BLOCK3 || map2[3][27] == BLOCK3)
						{
							if (map2[3][27] == BLOCK3 && map2[playerMapY][playerMapX] == map2[4][11])
							{
								map2[playerMapY][playerMapX] = BLOCK3;
								map2[3][27] = YUKA;
							}
						}
						if (map2[4][27] != BLOCK4 || map2[4][27] == BLOCK4)
						{
							if (map2[4][27] == BLOCK4 && map2[playerMapY][playerMapX] == map2[4][13])
							{
								map2[playerMapY][playerMapX] = BLOCK4;
								map2[4][27] = YUKA;
							}
						}
						if (map2[5][27] != BLOCK5 || map2[5][27] == BLOCK5)
						{
							if (map2[5][27] == BLOCK5 && map2[playerMapY][playerMapX] == map2[4][15])
							{
								map2[playerMapY][playerMapX] = BLOCK5;
								map2[5][27] = YUKA;
							}
						}
						if (map2[6][27] != BLOCK6 || map2[6][27] == BLOCK6)
						{

							if (map2[6][27] == BLOCK6 && map2[playerMapY][playerMapX] == /*6以降は後で*/map2[4][17])
							{
								map2[playerMapY][playerMapX] = BLOCK6;
								map2[6][27] = YUKA;
							}
						}
						if (map2[7][27] != BLOCK7 || map2[7][27] == BLOCK7)
						{
							if (map2[7][27] == BLOCK7 && map2[playerMapY][playerMapX] == map2[4][19])
							{
								map2[playerMapY][playerMapX] = BLOCK7;
								map2[7][27] = YUKA;
							}
						}
						if (map2[8][27] != BLOCK8 || map2[8][27] == BLOCK8)
						{
							if (map2[8][27] == BLOCK8 && map2[playerMapY][playerMapX] == map2[4][21])
							{
								map2[playerMapY][playerMapX] = BLOCK8;
								map2[8][27] = YUKA;
							}
						}
						playerPosY += playerSpeed;
					}

					if (map2[playerMapY + 1][playerMapX] == BLOCK1)
					{
						map2[1][27] = BLOCK1;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = SHI;
						playerPosY += playerSpeed;

					}
					if (map2[playerMapY + 1][playerMapX] == BLOCK22)
					{
						map2[2][27] = BLOCK22;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = SHI;
						playerPosY += playerSpeed;

					}
					if (map2[playerMapY + 1][playerMapX] == BLOCK3)
					{
						map2[3][27] = BLOCK3;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = SHI;
						playerPosY += playerSpeed;

					}
					if (map2[playerMapY + 1][playerMapX] == BLOCK4)
					{
						map2[4][27] = BLOCK4;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = SHI;
						playerPosY += playerSpeed;

					}
					if (map2[playerMapY + 1][playerMapX] == BLOCK5)
					{
						map2[5][27] = BLOCK5;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = SHI;
						playerPosY += playerSpeed;

					}
					if (map2[playerMapY + 1][playerMapX] == BLOCK6)
					{
						map2[6][27] = BLOCK6;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = SHI;
						playerPosY += playerSpeed;

					}
					if (map2[playerMapY + 1][playerMapX] == BLOCK7)
					{
						map2[7][27] = BLOCK7;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = SHI;
						playerPosY += playerSpeed;

					}
					if (map2[playerMapY + 1][playerMapX] == BLOCK8)
					{
						map2[8][27] = BLOCK8;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = SHI;
						playerPosY += playerSpeed;

					}
				}
				if (map2[playerMapY][playerMapX] == SU)
				{
					if (map2[playerMapY + 1][playerMapX] == YUKA)
					{
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = SU;
						if (map2[1][27] != BLOCK1 || map2[1][27] == BLOCK1)
						{
							if (map2[1][27] == BLOCK1 && map2[playerMapY][playerMapX] == map2[4][7])
							{
								map2[playerMapY][playerMapX] = BLOCK1;
								map2[1][27] = YUKA;
							}
						}
						if (map2[2][27] != BLOCK22 || map2[2][27] == BLOCK22)
						{
							if (map2[2][27] == BLOCK22 && map2[playerMapY][playerMapX] == map2[4][9])
							{
								map2[playerMapY][playerMapX] = BLOCK22;
								map2[2][27] = YUKA;
							}
						}
						if (map2[3][27] != BLOCK3 || map2[3][27] == BLOCK3)
						{
							if (map2[3][27] == BLOCK3 && map2[playerMapY][playerMapX] == map2[4][11])
							{
								map2[playerMapY][playerMapX] = BLOCK3;
								map2[3][27] = YUKA;
							}
						}
						if (map2[4][27] != BLOCK4 || map2[4][27] == BLOCK4)
						{
							if (map2[4][27] == BLOCK4 && map2[playerMapY][playerMapX] == map2[4][13])
							{
								map2[playerMapY][playerMapX] = BLOCK4;
								map2[4][27] = YUKA;
							}
						}
						if (map2[5][27] != BLOCK5 || map2[5][27] == BLOCK5)
						{
							if (map2[5][27] == BLOCK5 && map2[playerMapY][playerMapX] == map2[4][15])
							{
								map2[playerMapY][playerMapX] = BLOCK5;
								map2[5][27] = YUKA;
							}
						}
						if (map2[6][27] != BLOCK6 || map2[6][27] == BLOCK6)
						{

							if (map2[6][27] == BLOCK6 && map2[playerMapY][playerMapX] == /*6以降は後で*/map2[4][17])
							{
								map2[playerMapY][playerMapX] = BLOCK6;
								map2[6][27] = YUKA;
							}
						}
						if (map2[7][27] != BLOCK7 || map2[7][27] == BLOCK7)
						{
							if (map2[7][27] == BLOCK7 && map2[playerMapY][playerMapX] == map2[4][19])
							{
								map2[playerMapY][playerMapX] = BLOCK7;
								map2[7][27] = YUKA;
							}
						}
						if (map2[8][27] != BLOCK8 || map2[8][27] == BLOCK8)
						{
							if (map2[8][27] == BLOCK8 && map2[playerMapY][playerMapX] == map2[4][21])
							{
								map2[playerMapY][playerMapX] = BLOCK8;
								map2[8][27] = YUKA;
							}
						}
						playerPosY += playerSpeed;
					}


					if (map2[playerMapY + 1][playerMapX] == BLOCK1)
					{
						map2[1][27] = BLOCK1;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = SU;
						playerPosY += playerSpeed;

					}
					if (map2[playerMapY + 1][playerMapX] == BLOCK22)
					{
						map2[2][27] = BLOCK22;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = SU;
						playerPosY += playerSpeed;

					}
					if (map2[playerMapY + 1][playerMapX] == BLOCK3)
					{
						map2[3][27] = BLOCK3;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = SU;
						playerPosY += playerSpeed;

					}
					if (map2[playerMapY + 1][playerMapX] == BLOCK4)
					{
						map2[4][27] = BLOCK4;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = SU;
						playerPosY += playerSpeed;

					}
					if (map2[playerMapY + 1][playerMapX] == BLOCK5)
					{
						map2[5][27] = BLOCK5;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = SU;
						playerPosY += playerSpeed;

					}
					if (map2[playerMapY + 1][playerMapX] == BLOCK6)
					{
						map2[6][27] = BLOCK6;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = SU;
						playerPosY += playerSpeed;

					}
					if (map2[playerMapY + 1][playerMapX] == BLOCK7)
					{
						map2[7][27] = BLOCK7;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = SU;
						playerPosY += playerSpeed;

					}
					if (map2[playerMapY + 1][playerMapX] == BLOCK8)
					{
						map2[8][27] = BLOCK8;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = SU;
						playerPosY += playerSpeed;

					}
				}

				if (map2[playerMapY][playerMapX] == TO)
				{
					if (map2[playerMapY + 1][playerMapX] == YUKA)
					{
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = TO;
						if (map2[1][27] != BLOCK1 || map2[1][27] == BLOCK1)
						{
							if (map2[1][27] == BLOCK1 && map2[playerMapY][playerMapX] == map2[4][7])
							{
								map2[playerMapY][playerMapX] = BLOCK1;
								map2[1][27] = YUKA;
							}
						}
						if (map2[2][27] != BLOCK22 || map2[2][27] == BLOCK22)
						{
							if (map2[2][27] == BLOCK22 && map2[playerMapY][playerMapX] == map2[4][9])
							{
								map2[playerMapY][playerMapX] = BLOCK22;
								map2[2][27] = YUKA;
							}
						}
						if (map2[3][27] != BLOCK3 || map2[3][27] == BLOCK3)
						{
							if (map2[3][27] == BLOCK3 && map2[playerMapY][playerMapX] == map2[4][11])
							{
								map2[playerMapY][playerMapX] = BLOCK3;
								map2[3][27] = YUKA;
							}
						}
						if (map2[4][27] != BLOCK4 || map2[4][27] == BLOCK4)
						{
							if (map2[4][27] == BLOCK4 && map2[playerMapY][playerMapX] == map2[4][13])
							{
								map2[playerMapY][playerMapX] = BLOCK4;
								map2[4][27] = YUKA;
							}
						}
						if (map2[5][27] != BLOCK5 || map2[5][27] == BLOCK5)
						{
							if (map2[5][27] == BLOCK5 && map2[playerMapY][playerMapX] == map2[4][15])
							{
								map2[playerMapY][playerMapX] = BLOCK5;
								map2[5][27] = YUKA;
							}
						}
						if (map2[6][27] != BLOCK6 || map2[6][27] == BLOCK6)
						{

							if (map2[6][27] == BLOCK6 && map2[playerMapY][playerMapX] == /*6以降は後で*/map2[4][17])
							{
								map2[playerMapY][playerMapX] = BLOCK6;
								map2[6][27] = YUKA;
							}
						}
						if (map2[7][27] != BLOCK7 || map2[7][27] == BLOCK7)
						{
							if (map2[7][27] == BLOCK7 && map2[playerMapY][playerMapX] == map2[4][19])
							{
								map2[playerMapY][playerMapX] = BLOCK7;
								map2[7][27] = YUKA;
							}
						}
						if (map2[8][27] != BLOCK8 || map2[8][27] == BLOCK8)
						{
							if (map2[8][27] == BLOCK8 && map2[playerMapY][playerMapX] == map2[4][21])
							{
								map2[playerMapY][playerMapX] = BLOCK8;
								map2[8][27] = YUKA;
							}
						}
						playerPosY += playerSpeed;
					}


					if (map2[playerMapY + 1][playerMapX] == BLOCK1)
					{
						map2[1][27] = BLOCK1;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = TO;
						playerPosY += playerSpeed;

					}
					if (map2[playerMapY + 1][playerMapX] == BLOCK22)
					{
						map2[2][27] = BLOCK22;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = TO;
						playerPosY += playerSpeed;

					}
					if (map2[playerMapY + 1][playerMapX] == BLOCK3)
					{
						map2[3][27] = BLOCK3;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = TO;
						playerPosY += playerSpeed;

					}
					if (map2[playerMapY + 1][playerMapX] == BLOCK4)
					{
						map2[4][27] = BLOCK4;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = TO;
						playerPosY += playerSpeed;

					}
					if (map2[playerMapY + 1][playerMapX] == BLOCK5)
					{
						map2[5][27] = BLOCK5;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = TO;
						playerPosY += playerSpeed;

					}
					if (map2[playerMapY + 1][playerMapX] == BLOCK6)
					{
						map2[6][27] = BLOCK6;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = TO;
						playerPosY += playerSpeed;

					}
					if (map2[playerMapY + 1][playerMapX] == BLOCK7)
					{
						map2[7][27] = BLOCK7;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = TO;
						playerPosY += playerSpeed;

					}
					if (map2[playerMapY + 1][playerMapX] == BLOCK8)
					{
						map2[8][27] = BLOCK8;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = TO;
						playerPosY += playerSpeed;

					}
				}
				if (map2[playerMapY][playerMapX] == NE)
				{
					if (map2[playerMapY + 1][playerMapX] == YUKA)
					{
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = NE;
						if (map2[1][27] != BLOCK1 || map2[1][27] == BLOCK1)
						{
							if (map2[1][27] == BLOCK1 && map2[playerMapY][playerMapX] == map2[4][7])
							{
								map2[playerMapY][playerMapX] = BLOCK1;
								map2[1][27] = YUKA;
							}
						}
						if (map2[2][27] != BLOCK22 || map2[2][27] == BLOCK22)
						{
							if (map2[2][27] == BLOCK22 && map2[playerMapY][playerMapX] == map2[4][9])
							{
								map2[playerMapY][playerMapX] = BLOCK22;
								map2[2][27] = YUKA;
							}
						}
						if (map2[3][27] != BLOCK3 || map2[3][27] == BLOCK3)
						{
							if (map2[3][27] == BLOCK3 && map2[playerMapY][playerMapX] == map2[4][11])
							{
								map2[playerMapY][playerMapX] = BLOCK3;
								map2[3][27] = YUKA;
							}
						}
						if (map2[4][27] != BLOCK4 || map2[4][27] == BLOCK4)
						{
							if (map2[4][27] == BLOCK4 && map2[playerMapY][playerMapX] == map2[4][13])
							{
								map2[playerMapY][playerMapX] = BLOCK4;
								map2[4][27] = YUKA;
							}
						}
						if (map2[5][27] != BLOCK5 || map2[5][27] == BLOCK5)
						{
							if (map2[5][27] == BLOCK5 && map2[playerMapY][playerMapX] == map2[4][15])
							{
								map2[playerMapY][playerMapX] = BLOCK5;
								map2[5][27] = YUKA;
							}
						}
						if (map2[6][27] != BLOCK6 || map2[6][27] == BLOCK6)
						{

							if (map2[6][27] == BLOCK6 && map2[playerMapY][playerMapX] == /*6以降は後で*/map2[4][17])
							{
								map2[playerMapY][playerMapX] = BLOCK6;
								map2[6][27] = YUKA;
							}
						}
						if (map2[7][27] != BLOCK7 || map2[7][27] == BLOCK7)
						{
							if (map2[7][27] == BLOCK7 && map2[playerMapY][playerMapX] == map2[4][19])
							{
								map2[playerMapY][playerMapX] = BLOCK7;
								map2[7][27] = YUKA;
							}
						}
						if (map2[8][27] != BLOCK8 || map2[8][27] == BLOCK8)
						{
							if (map2[8][27] == BLOCK8 && map2[playerMapY][playerMapX] == map2[4][21])
							{
								map2[playerMapY][playerMapX] = BLOCK8;
								map2[8][27] = YUKA;
							}
						}
						playerPosY += playerSpeed;
					}


					if (map2[playerMapY + 1][playerMapX] == BLOCK1)
					{
						map2[1][27] = BLOCK1;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = NE;
						playerPosY += playerSpeed;

					}
					if (map2[playerMapY + 1][playerMapX] == BLOCK22)
					{
						map2[2][27] = BLOCK22;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = NE;
						playerPosY += playerSpeed;

					}
					if (map2[playerMapY + 1][playerMapX] == BLOCK3)
					{
						map2[3][27] = BLOCK3;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = NE;
						playerPosY += playerSpeed;

					}
					if (map2[playerMapY + 1][playerMapX] == BLOCK4)
					{
						map2[4][27] = BLOCK4;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = NE;
						playerPosY += playerSpeed;

					}
					if (map2[playerMapY + 1][playerMapX] == BLOCK5)
					{
						map2[5][27] = BLOCK5;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = NE;
						playerPosY += playerSpeed;

					}
					if (map2[playerMapY + 1][playerMapX] == BLOCK6)
					{
						map2[6][27] = BLOCK6;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = NE;
						playerPosY += playerSpeed;

					}
					if (map2[playerMapY + 1][playerMapX] == BLOCK7)
					{
						map2[7][27] = BLOCK7;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = NE;
						playerPosY += playerSpeed;

					}
					if (map2[playerMapY + 1][playerMapX] == BLOCK8)
					{
						map2[8][27] = BLOCK8;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = NE;
						playerPosY += playerSpeed;

					}
				}

				if (map2[playerMapY][playerMapX] == FU)
				{
					if (map2[playerMapY + 1][playerMapX] == YUKA)
					{
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = FU;
						if (map2[1][27] != BLOCK1 || map2[1][27] == BLOCK1)
						{
							if (map2[1][27] == BLOCK1 && map2[playerMapY][playerMapX] == map2[4][7])
							{
								map2[playerMapY][playerMapX] = BLOCK1;
								map2[1][27] = YUKA;
							}
						}
						if (map2[2][27] != BLOCK22 || map2[2][27] == BLOCK22)
						{
							if (map2[2][27] == BLOCK22 && map2[playerMapY][playerMapX] == map2[4][9])
							{
								map2[playerMapY][playerMapX] = BLOCK22;
								map2[2][27] = YUKA;
							}
						}
						if (map2[3][27] != BLOCK3 || map2[3][27] == BLOCK3)
						{
							if (map2[3][27] == BLOCK3 && map2[playerMapY][playerMapX] == map2[4][11])
							{
								map2[playerMapY][playerMapX] = BLOCK3;
								map2[3][27] = YUKA;
							}
						}
						if (map2[4][27] != BLOCK4 || map2[4][27] == BLOCK4)
						{
							if (map2[4][27] == BLOCK4 && map2[playerMapY][playerMapX] == map2[4][13])
							{
								map2[playerMapY][playerMapX] = BLOCK4;
								map2[4][27] = YUKA;
							}
						}
						if (map2[5][27] != BLOCK5 || map2[5][27] == BLOCK5)
						{
							if (map2[5][27] == BLOCK5 && map2[playerMapY][playerMapX] == map2[4][15])
							{
								map2[playerMapY][playerMapX] = BLOCK5;
								map2[5][27] = YUKA;
							}
						}
						if (map2[6][27] != BLOCK6 || map2[6][27] == BLOCK6)
						{

							if (map2[6][27] == BLOCK6 && map2[playerMapY][playerMapX] == /*6以降は後で*/map2[4][17])
							{
								map2[playerMapY][playerMapX] = BLOCK6;
								map2[6][27] = YUKA;
							}
						}
						if (map2[7][27] != BLOCK7 || map2[7][27] == BLOCK7)
						{
							if (map2[7][27] == BLOCK7 && map2[playerMapY][playerMapX] == map2[4][19])
							{
								map2[playerMapY][playerMapX] = BLOCK7;
								map2[7][27] = YUKA;
							}
						}
						if (map2[8][27] != BLOCK8 || map2[8][27] == BLOCK8)
						{
							if (map2[8][27] == BLOCK8 && map2[playerMapY][playerMapX] == map2[4][21])
							{
								map2[playerMapY][playerMapX] = BLOCK8;
								map2[8][27] = YUKA;
							}
						}
						playerPosY += playerSpeed;
					}


					if (map2[playerMapY + 1][playerMapX] == BLOCK1)
					{
						map2[1][27] = BLOCK1;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = FU;
						playerPosY += playerSpeed;

					}
					if (map2[playerMapY + 1][playerMapX] == BLOCK22)
					{
						map2[2][27] = BLOCK22;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = FU;
						playerPosY += playerSpeed;

					}
					if (map2[playerMapY + 1][playerMapX] == BLOCK3)
					{
						map2[3][27] = BLOCK3;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = FU;
						playerPosY += playerSpeed;

					}
					if (map2[playerMapY + 1][playerMapX] == BLOCK4)
					{
						map2[4][27] = BLOCK4;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = FU;
						playerPosY += playerSpeed;

					}
					if (map2[playerMapY + 1][playerMapX] == BLOCK5)
					{
						map2[5][27] = BLOCK5;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = FU;
						playerPosY += playerSpeed;

					}
					if (map2[playerMapY + 1][playerMapX] == BLOCK6)
					{
						map2[6][27] = BLOCK6;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = FU;
						playerPosY += playerSpeed;

					}
					if (map2[playerMapY + 1][playerMapX] == BLOCK7)
					{
						map2[7][27] = BLOCK7;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = FU;
						playerPosY += playerSpeed;

					}
					if (map2[playerMapY + 1][playerMapX] == BLOCK8)
					{
						map2[8][27] = BLOCK8;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = FU;
						playerPosY += playerSpeed;

					}
				}
				if (map2[playerMapY][playerMapX] == MU)
				{
					if (map2[playerMapY + 1][playerMapX] == YUKA)
					{
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = MU;
						if (map2[1][27] != BLOCK1 || map2[1][27] == BLOCK1)
						{
							if (map2[1][27] == BLOCK1 && map2[playerMapY][playerMapX] == map2[4][7])
							{
								map2[playerMapY][playerMapX] = BLOCK1;
								map2[1][27] = YUKA;
							}
						}
						if (map2[2][27] != BLOCK22 || map2[2][27] == BLOCK22)
						{
							if (map2[2][27] == BLOCK22 && map2[playerMapY][playerMapX] == map2[4][9])
							{
								map2[playerMapY][playerMapX] = BLOCK22;
								map2[2][27] = YUKA;
							}
						}
						if (map2[3][27] != BLOCK3 || map2[3][27] == BLOCK3)
						{
							if (map2[3][27] == BLOCK3 && map2[playerMapY][playerMapX] == map2[4][11])
							{
								map2[playerMapY][playerMapX] = BLOCK3;
								map2[3][27] = YUKA;
							}
						}
						if (map2[4][27] != BLOCK4 || map2[4][27] == BLOCK4)
						{
							if (map2[4][27] == BLOCK4 && map2[playerMapY][playerMapX] == map2[4][13])
							{
								map2[playerMapY][playerMapX] = BLOCK4;
								map2[4][27] = YUKA;
							}
						}
						if (map2[5][27] != BLOCK5 || map2[5][27] == BLOCK5)
						{
							if (map2[5][27] == BLOCK5 && map2[playerMapY][playerMapX] == map2[4][15])
							{
								map2[playerMapY][playerMapX] = BLOCK5;
								map2[5][27] = YUKA;
							}
						}
						if (map2[6][27] != BLOCK6 || map2[6][27] == BLOCK6)
						{

							if (map2[6][27] == BLOCK6 && map2[playerMapY][playerMapX] == /*6以降は後で*/map2[4][17])
							{
								map2[playerMapY][playerMapX] = BLOCK6;
								map2[6][27] = YUKA;
							}
						}
						if (map2[7][27] != BLOCK7 || map2[7][27] == BLOCK7)
						{
							if (map2[7][27] == BLOCK7 && map2[playerMapY][playerMapX] == map2[4][19])
							{
								map2[playerMapY][playerMapX] = BLOCK7;
								map2[7][27] = YUKA;
							}
						}
						if (map2[8][27] != BLOCK8 || map2[8][27] == BLOCK8)
						{
							if (map2[8][27] == BLOCK8 && map2[playerMapY][playerMapX] == map2[4][21])
							{
								map2[playerMapY][playerMapX] = BLOCK8;
								map2[8][27] = YUKA;
							}
						}
						playerPosY += playerSpeed;
					}


					if (map2[playerMapY + 1][playerMapX] == BLOCK1)
					{
						map2[1][27] = BLOCK1;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = MU;
						playerPosY += playerSpeed;

					}
					if (map2[playerMapY + 1][playerMapX] == BLOCK22)
					{
						map2[2][27] = BLOCK22;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = MU;
						playerPosY += playerSpeed;

					}
					if (map2[playerMapY + 1][playerMapX] == BLOCK3)
					{
						map2[3][27] = BLOCK3;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = MU;
						playerPosY += playerSpeed;

					}
					if (map2[playerMapY + 1][playerMapX] == BLOCK4)
					{
						map2[4][27] = BLOCK4;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = MU;
						playerPosY += playerSpeed;

					}
					if (map2[playerMapY + 1][playerMapX] == BLOCK5)
					{
						map2[5][27] = BLOCK5;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = MU;
						playerPosY += playerSpeed;

					}
					if (map2[playerMapY + 1][playerMapX] == BLOCK6)
					{
						map2[6][27] = BLOCK6;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = MU;
						playerPosY += playerSpeed;

					}
					if (map2[playerMapY + 1][playerMapX] == BLOCK7)
					{
						map2[7][27] = BLOCK7;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = MU;
						playerPosY += playerSpeed;

					}
					if (map2[playerMapY + 1][playerMapX] == BLOCK8)
					{
						map2[8][27] = BLOCK8;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = MU;
						playerPosY += playerSpeed;

					}
				}
				if (map2[playerMapY][playerMapX] == MO)
				{
					if (map2[playerMapY + 1][playerMapX] == YUKA)
					{
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = MO;
						if (map2[1][27] != BLOCK1 || map2[1][27] == BLOCK1)
						{
							if (map2[1][27] == BLOCK1 && map2[playerMapY][playerMapX] == map2[4][7])
							{
								map2[playerMapY][playerMapX] = BLOCK1;
								map2[1][27] = YUKA;
							}
						}
						if (map2[2][27] != BLOCK22 || map2[2][27] == BLOCK22)
						{
							if (map2[2][27] == BLOCK22 && map2[playerMapY][playerMapX] == map2[4][9])
							{
								map2[playerMapY][playerMapX] = BLOCK22;
								map2[2][27] = YUKA;
							}
						}
						if (map2[3][27] != BLOCK3 || map2[3][27] == BLOCK3)
						{
							if (map2[3][27] == BLOCK3 && map2[playerMapY][playerMapX] == map2[4][11])
							{
								map2[playerMapY][playerMapX] = BLOCK3;
								map2[3][27] = YUKA;
							}
						}
						if (map2[4][27] != BLOCK4 || map2[4][27] == BLOCK4)
						{
							if (map2[4][27] == BLOCK4 && map2[playerMapY][playerMapX] == map2[4][13])
							{
								map2[playerMapY][playerMapX] = BLOCK4;
								map2[4][27] = YUKA;
							}
						}
						if (map2[5][27] != BLOCK5 || map2[5][27] == BLOCK5)
						{
							if (map2[5][27] == BLOCK5 && map2[playerMapY][playerMapX] == map2[4][15])
							{
								map2[playerMapY][playerMapX] = BLOCK5;
								map2[5][27] = YUKA;
							}
						}
						if (map2[6][27] != BLOCK6 || map2[6][27] == BLOCK6)
						{

							if (map2[6][27] == BLOCK6 && map2[playerMapY][playerMapX] == /*6以降は後で*/map2[4][17])
							{
								map2[playerMapY][playerMapX] = BLOCK6;
								map2[6][27] = YUKA;
							}
						}
						if (map2[7][27] != BLOCK7 || map2[7][27] == BLOCK7)
						{
							if (map2[7][27] == BLOCK7 && map2[playerMapY][playerMapX] == map2[4][19])
							{
								map2[playerMapY][playerMapX] = BLOCK7;
								map2[7][27] = YUKA;
							}
						}
						if (map2[8][27] != BLOCK8 || map2[8][27] == BLOCK8)
						{
							if (map2[8][27] == BLOCK8 && map2[playerMapY][playerMapX] == map2[4][21])
							{
								map2[playerMapY][playerMapX] = BLOCK8;
								map2[8][27] = YUKA;
							}
						}
						playerPosY += playerSpeed;
					}


					if (map2[playerMapY + 1][playerMapX] == BLOCK1)
					{
						map2[1][27] = BLOCK1;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = MO;
						playerPosY += playerSpeed;

					}
					if (map2[playerMapY + 1][playerMapX] == BLOCK22)
					{
						map2[2][27] = BLOCK22;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = MO;
						playerPosY += playerSpeed;

					}
					if (map2[playerMapY + 1][playerMapX] == BLOCK3)
					{
						map2[3][27] = BLOCK3;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = MO;
						playerPosY += playerSpeed;

					}
					if (map2[playerMapY + 1][playerMapX] == BLOCK4)
					{
						map2[4][27] = BLOCK4;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = MO;
						playerPosY += playerSpeed;

					}
					if (map2[playerMapY + 1][playerMapX] == BLOCK5)
					{
						map2[5][27] = BLOCK5;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = MO;
						playerPosY += playerSpeed;

					}
					if (map2[playerMapY + 1][playerMapX] == BLOCK6)
					{
						map2[6][27] = BLOCK6;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = MO;
						playerPosY += playerSpeed;

					}
					if (map2[playerMapY + 1][playerMapX] == BLOCK7)
					{
						map2[7][27] = BLOCK7;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = MO;
						playerPosY += playerSpeed;

					}
					if (map2[playerMapY + 1][playerMapX] == BLOCK8)
					{
						map2[8][27] = BLOCK8;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = MO;
						playerPosY += playerSpeed;

					}
				}
				if (map2[playerMapY][playerMapX] == YO)
				{
					if (map2[playerMapY + 1][playerMapX] == YUKA)
					{
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = YO;
						if (map2[1][27] != BLOCK1 || map2[1][27] == BLOCK1)
						{
							if (map2[1][27] == BLOCK1 && map2[playerMapY][playerMapX] == map2[4][7])
							{
								map2[playerMapY][playerMapX] = BLOCK1;
								map2[1][27] = YUKA;
							}
						}
						if (map2[2][27] != BLOCK22 || map2[2][27] == BLOCK22)
						{
							if (map2[2][27] == BLOCK22 && map2[playerMapY][playerMapX] == map2[4][9])
							{
								map2[playerMapY][playerMapX] = BLOCK22;
								map2[2][27] = YUKA;
							}
						}
						if (map2[3][27] != BLOCK3 || map2[3][27] == BLOCK3)
						{
							if (map2[3][27] == BLOCK3 && map2[playerMapY][playerMapX] == map2[4][11])
							{
								map2[playerMapY][playerMapX] = BLOCK3;
								map2[3][27] = YUKA;
							}
						}
						if (map2[4][27] != BLOCK4 || map2[4][27] == BLOCK4)
						{
							if (map2[4][27] == BLOCK4 && map2[playerMapY][playerMapX] == map2[4][13])
							{
								map2[playerMapY][playerMapX] = BLOCK4;
								map2[4][27] = YUKA;
							}
						}
						if (map2[5][27] != BLOCK5 || map2[5][27] == BLOCK5)
						{
							if (map2[5][27] == BLOCK5 && map2[playerMapY][playerMapX] == map2[4][15])
							{
								map2[playerMapY][playerMapX] = BLOCK5;
								map2[5][27] = YUKA;
							}
						}
						if (map2[6][27] != BLOCK6 || map2[6][27] == BLOCK6)
						{

							if (map2[6][27] == BLOCK6 && map2[playerMapY][playerMapX] == /*6以降は後で*/map2[4][17])
							{
								map2[playerMapY][playerMapX] = BLOCK6;
								map2[6][27] = YUKA;
							}
						}
						if (map2[7][27] != BLOCK7 || map2[7][27] == BLOCK7)
						{
							if (map2[7][27] == BLOCK7 && map2[playerMapY][playerMapX] == map2[4][19])
							{
								map2[playerMapY][playerMapX] = BLOCK7;
								map2[7][27] = YUKA;
							}
						}
						if (map2[8][27] != BLOCK8 || map2[8][27] == BLOCK8)
						{
							if (map2[8][27] == BLOCK8 && map2[playerMapY][playerMapX] == map2[4][21])
							{
								map2[playerMapY][playerMapX] = BLOCK8;
								map2[8][27] = YUKA;
							}
						}
						playerPosY += playerSpeed;
					}


					if (map2[playerMapY + 1][playerMapX] == BLOCK1)
					{
						map2[1][27] = BLOCK1;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = YO;
						playerPosY += playerSpeed;

					}
					if (map2[playerMapY + 1][playerMapX] == BLOCK22)
					{
						map2[2][27] = BLOCK22;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = YO;
						playerPosY += playerSpeed;

					}
					if (map2[playerMapY + 1][playerMapX] == BLOCK3)
					{
						map2[3][27] = BLOCK3;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = YO;
						playerPosY += playerSpeed;

					}
					if (map2[playerMapY + 1][playerMapX] == BLOCK4)
					{
						map2[4][27] = BLOCK4;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = YO;
						playerPosY += playerSpeed;

					}
					if (map2[playerMapY + 1][playerMapX] == BLOCK5)
					{
						map2[5][27] = BLOCK5;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = YO;
						playerPosY += playerSpeed;

					}
					if (map2[playerMapY + 1][playerMapX] == BLOCK6)
					{
						map2[6][27] = BLOCK6;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = YO;
						playerPosY += playerSpeed;

					}
					if (map2[playerMapY + 1][playerMapX] == BLOCK7)
					{
						map2[7][27] = BLOCK7;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = YO;
						playerPosY += playerSpeed;

					}
					if (map2[playerMapY + 1][playerMapX] == BLOCK8)
					{
						map2[8][27] = BLOCK8;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = YO;
						playerPosY += playerSpeed;

					}
				}
				if (map2[playerMapY][playerMapX] == NN)
				{
					if (map2[playerMapY + 1][playerMapX] == YUKA)
					{
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = NN;
						if (map2[1][27] != BLOCK1 || map2[1][27] == BLOCK1)
						{
							if (map2[1][27] == BLOCK1 && map2[playerMapY][playerMapX] == map2[4][7])
							{
								map2[playerMapY][playerMapX] = BLOCK1;
								map2[1][27] = YUKA;
							}
						}
						if (map2[2][27] != BLOCK22 || map2[2][27] == BLOCK22)
						{
							if (map2[2][27] == BLOCK22 && map2[playerMapY][playerMapX] == map2[4][9])
							{
								map2[playerMapY][playerMapX] = BLOCK22;
								map2[2][27] = YUKA;
							}
						}
						if (map2[3][27] != BLOCK3 || map2[3][27] == BLOCK3)
						{
							if (map2[3][27] == BLOCK3 && map2[playerMapY][playerMapX] == map2[4][11])
							{
								map2[playerMapY][playerMapX] = BLOCK3;
								map2[3][27] = YUKA;
							}
						}
						if (map2[4][27] != BLOCK4 || map2[4][27] == BLOCK4)
						{
							if (map2[4][27] == BLOCK4 && map2[playerMapY][playerMapX] == map2[4][13])
							{
								map2[playerMapY][playerMapX] = BLOCK4;
								map2[4][27] = YUKA;
							}
						}
						if (map2[5][27] != BLOCK5 || map2[5][27] == BLOCK5)
						{
							if (map2[5][27] == BLOCK5 && map2[playerMapY][playerMapX] == map2[4][15])
							{
								map2[playerMapY][playerMapX] = BLOCK5;
								map2[5][27] = YUKA;
							}
						}
						if (map2[6][27] != BLOCK6 || map2[6][27] == BLOCK6)
						{

							if (map2[6][27] == BLOCK6 && map2[playerMapY][playerMapX] == /*6以降は後で*/map2[4][17])
							{
								map2[playerMapY][playerMapX] = BLOCK6;
								map2[6][27] = YUKA;
							}
						}
						if (map2[7][27] != BLOCK7 || map2[7][27] == BLOCK7)
						{
							if (map2[7][27] == BLOCK7 && map2[playerMapY][playerMapX] == map2[4][19])
							{
								map2[playerMapY][playerMapX] = BLOCK7;
								map2[7][27] = YUKA;
							}
						}
						if (map2[8][27] != BLOCK8 || map2[8][27] == BLOCK8)
						{
							if (map2[8][27] == BLOCK8 && map2[playerMapY][playerMapX] == map2[4][21])
							{
								map2[playerMapY][playerMapX] = BLOCK8;
								map2[8][27] = YUKA;
							}
						}
						playerPosY += playerSpeed;
					}


					if (map2[playerMapY + 1][playerMapX] == BLOCK1)
					{
						map2[1][27] = BLOCK1;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = NN;
						playerPosY += playerSpeed;

					}
					if (map2[playerMapY + 1][playerMapX] == BLOCK22)
					{
						map2[2][27] = BLOCK22;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = NN;
						playerPosY += playerSpeed;

					}
					if (map2[playerMapY + 1][playerMapX] == BLOCK3)
					{
						map2[3][27] = BLOCK3;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = NN;
						playerPosY += playerSpeed;

					}
					if (map2[playerMapY + 1][playerMapX] == BLOCK4)
					{
						map2[4][27] = BLOCK4;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = NN;
						playerPosY += playerSpeed;

					}
					if (map2[playerMapY + 1][playerMapX] == BLOCK5)
					{
						map2[5][27] = BLOCK5;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = NN;
						playerPosY += playerSpeed;

					}
					if (map2[playerMapY + 1][playerMapX] == BLOCK6)
					{
						map2[6][27] = BLOCK6;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = NN;
						playerPosY += playerSpeed;

					}
					if (map2[playerMapY + 1][playerMapX] == BLOCK7)
					{
						map2[7][27] = BLOCK7;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = NN;
						playerPosY += playerSpeed;

					}
					if (map2[playerMapY + 1][playerMapX] == BLOCK8)
					{
						map2[8][27] = BLOCK8;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = NN;
						playerPosY += playerSpeed;

					}
				}
				if (map2[playerMapY][playerMapX] == ZA)
				{
					if (map2[playerMapY + 1][playerMapX] == YUKA)
					{
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = ZA;
						if (map2[1][27] != BLOCK1 || map2[1][27] == BLOCK1)
						{
							if (map2[1][27] == BLOCK1 && map2[playerMapY][playerMapX] == map2[4][7])
							{
								map2[playerMapY][playerMapX] = BLOCK1;
								map2[1][27] = YUKA;
							}
						}
						if (map2[2][27] != BLOCK22 || map2[2][27] == BLOCK22)
						{
							if (map2[2][27] == BLOCK22 && map2[playerMapY][playerMapX] == map2[4][9])
							{
								map2[playerMapY][playerMapX] = BLOCK22;
								map2[2][27] = YUKA;
							}
						}
						if (map2[3][27] != BLOCK3 || map2[3][27] == BLOCK3)
						{
							if (map2[3][27] == BLOCK3 && map2[playerMapY][playerMapX] == map2[4][11])
							{
								map2[playerMapY][playerMapX] = BLOCK3;
								map2[3][27] = YUKA;
							}
						}
						if (map2[4][27] != BLOCK4 || map2[4][27] == BLOCK4)
						{
							if (map2[4][27] == BLOCK4 && map2[playerMapY][playerMapX] == map2[4][13])
							{
								map2[playerMapY][playerMapX] = BLOCK4;
								map2[4][27] = YUKA;
							}
						}
						if (map2[5][27] != BLOCK5 || map2[5][27] == BLOCK5)
						{
							if (map2[5][27] == BLOCK5 && map2[playerMapY][playerMapX] == map2[4][15])
							{
								map2[playerMapY][playerMapX] = BLOCK5;
								map2[5][27] = YUKA;
							}
						}
						if (map2[6][27] != BLOCK6 || map2[6][27] == BLOCK6)
						{

							if (map2[6][27] == BLOCK6 && map2[playerMapY][playerMapX] == /*6以降は後で*/map2[4][17])
							{
								map2[playerMapY][playerMapX] = BLOCK6;
								map2[6][27] = YUKA;
							}
						}
						if (map2[7][27] != BLOCK7 || map2[7][27] == BLOCK7)
						{
							if (map2[7][27] == BLOCK7 && map2[playerMapY][playerMapX] == map2[4][19])
							{
								map2[playerMapY][playerMapX] = BLOCK7;
								map2[7][27] = YUKA;
							}
						}
						if (map2[8][27] != BLOCK8 || map2[8][27] == BLOCK8)
						{
							if (map2[8][27] == BLOCK8 && map2[playerMapY][playerMapX] == map2[4][21])
							{
								map2[playerMapY][playerMapX] = BLOCK8;
								map2[8][27] = YUKA;
							}
						}
						playerPosY += playerSpeed;
					}


					if (map2[playerMapY + 1][playerMapX] == BLOCK1)
					{
						map2[1][27] = BLOCK1;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = ZA;
						playerPosY += playerSpeed;

					}
					if (map2[playerMapY + 1][playerMapX] == BLOCK22)
					{
						map2[2][27] = BLOCK22;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = ZA;
						playerPosY += playerSpeed;

					}
					if (map2[playerMapY + 1][playerMapX] == BLOCK3)
					{
						map2[3][27] = BLOCK3;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = ZA;
						playerPosY += playerSpeed;

					}
					if (map2[playerMapY + 1][playerMapX] == BLOCK4)
					{
						map2[4][27] = BLOCK4;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = ZA;
						playerPosY += playerSpeed;

					}
					if (map2[playerMapY + 1][playerMapX] == BLOCK5)
					{
						map2[5][27] = BLOCK5;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = ZA;
						playerPosY += playerSpeed;

					}
					if (map2[playerMapY + 1][playerMapX] == BLOCK6)
					{
						map2[6][27] = BLOCK6;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = ZA;
						playerPosY += playerSpeed;

					}
					if (map2[playerMapY + 1][playerMapX] == BLOCK7)
					{
						map2[7][27] = BLOCK7;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = ZA;
						playerPosY += playerSpeed;

					}
					if (map2[playerMapY + 1][playerMapX] == BLOCK8)
					{
						map2[8][27] = BLOCK8;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = ZA;
						playerPosY += playerSpeed;

					}
				}
				if (map2[playerMapY][playerMapX] == ZI)
				{
					if (map2[playerMapY + 1][playerMapX] == YUKA)
					{
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = ZI;
						if (map2[1][27] != BLOCK1 || map2[1][27] == BLOCK1)
						{
							if (map2[1][27] == BLOCK1 && map2[playerMapY][playerMapX] == map2[4][7])
							{
								map2[playerMapY][playerMapX] = BLOCK1;
								map2[1][27] = YUKA;
							}
						}
						if (map2[2][27] != BLOCK22 || map2[2][27] == BLOCK22)
						{
							if (map2[2][27] == BLOCK22 && map2[playerMapY][playerMapX] == map2[4][9])
							{
								map2[playerMapY][playerMapX] = BLOCK22;
								map2[2][27] = YUKA;
							}
						}
						if (map2[3][27] != BLOCK3 || map2[3][27] == BLOCK3)
						{
							if (map2[3][27] == BLOCK3 && map2[playerMapY][playerMapX] == map2[4][11])
							{
								map2[playerMapY][playerMapX] = BLOCK3;
								map2[3][27] = YUKA;
							}
						}
						if (map2[4][27] != BLOCK4 || map2[4][27] == BLOCK4)
						{
							if (map2[4][27] == BLOCK4 && map2[playerMapY][playerMapX] == map2[4][13])
							{
								map2[playerMapY][playerMapX] = BLOCK4;
								map2[4][27] = YUKA;
							}
						}
						if (map2[5][27] != BLOCK5 || map2[5][27] == BLOCK5)
						{
							if (map2[5][27] == BLOCK5 && map2[playerMapY][playerMapX] == map2[4][15])
							{
								map2[playerMapY][playerMapX] = BLOCK5;
								map2[5][27] = YUKA;
							}
						}
						if (map2[6][27] != BLOCK6 || map2[6][27] == BLOCK6)
						{

							if (map2[6][27] == BLOCK6 && map2[playerMapY][playerMapX] == /*6以降は後で*/map2[4][17])
							{
								map2[playerMapY][playerMapX] = BLOCK6;
								map2[6][27] = YUKA;
							}
						}
						if (map2[7][27] != BLOCK7 || map2[7][27] == BLOCK7)
						{
							if (map2[7][27] == BLOCK7 && map2[playerMapY][playerMapX] == map2[4][19])
							{
								map2[playerMapY][playerMapX] = BLOCK7;
								map2[7][27] = YUKA;
							}
						}
						if (map2[8][27] != BLOCK8 || map2[8][27] == BLOCK8)
						{
							if (map2[8][27] == BLOCK8 && map2[playerMapY][playerMapX] == map2[4][21])
							{
								map2[playerMapY][playerMapX] = BLOCK8;
								map2[8][27] = YUKA;
							}
						}
						playerPosY += playerSpeed;
					}

					if (map2[playerMapY + 1][playerMapX] == BLOCK1)
					{
						map2[1][27] = BLOCK1;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = ZI;
						playerPosY += playerSpeed;

					}
					if (map2[playerMapY + 1][playerMapX] == BLOCK22)
					{
						map2[2][27] = BLOCK22;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = ZI;
						playerPosY += playerSpeed;

					}
					if (map2[playerMapY + 1][playerMapX] == BLOCK3)
					{
						map2[3][27] = BLOCK3;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = ZI;
						playerPosY += playerSpeed;

					}
					if (map2[playerMapY + 1][playerMapX] == BLOCK4)
					{
						map2[4][27] = BLOCK4;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = ZI;
						playerPosY += playerSpeed;

					}
					if (map2[playerMapY + 1][playerMapX] == BLOCK5)
					{
						map2[5][27] = BLOCK5;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = ZI;
						playerPosY += playerSpeed;

					}
					if (map2[playerMapY + 1][playerMapX] == BLOCK6)
					{
						map2[6][27] = BLOCK6;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = ZI;
						playerPosY += playerSpeed;

					}
					if (map2[playerMapY + 1][playerMapX] == BLOCK7)
					{
						map2[7][27] = BLOCK7;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = ZI;
						playerPosY += playerSpeed;

					}
					if (map2[playerMapY + 1][playerMapX] == BLOCK8)
					{
						map2[8][27] = BLOCK8;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = ZI;
						playerPosY += playerSpeed;

					}
				}
				if (map2[playerMapY][playerMapX] == BU)
				{
					if (map2[playerMapY + 1][playerMapX] == YUKA)
					{
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = BU;
						if (map2[1][27] != BLOCK1 || map2[1][27] == BLOCK1)
						{
							if (map2[1][27] == BLOCK1 && map2[playerMapY][playerMapX] == map2[4][7])
							{
								map2[playerMapY][playerMapX] = BLOCK1;
								map2[1][27] = YUKA;
							}
						}
						if (map2[2][27] != BLOCK22 || map2[2][27] == BLOCK22)
						{
							if (map2[2][27] == BLOCK22 && map2[playerMapY][playerMapX] == map2[4][9])
							{
								map2[playerMapY][playerMapX] = BLOCK22;
								map2[2][27] = YUKA;
							}
						}
						if (map2[3][27] != BLOCK3 || map2[3][27] == BLOCK3)
						{
							if (map2[3][27] == BLOCK3 && map2[playerMapY][playerMapX] == map2[4][11])
							{
								map2[playerMapY][playerMapX] = BLOCK3;
								map2[3][27] = YUKA;
							}
						}
						if (map2[4][27] != BLOCK4 || map2[4][27] == BLOCK4)
						{
							if (map2[4][27] == BLOCK4 && map2[playerMapY][playerMapX] == map2[4][13])
							{
								map2[playerMapY][playerMapX] = BLOCK4;
								map2[4][27] = YUKA;
							}
						}
						if (map2[5][27] != BLOCK5 || map2[5][27] == BLOCK5)
						{
							if (map2[5][27] == BLOCK5 && map2[playerMapY][playerMapX] == map2[4][15])
							{
								map2[playerMapY][playerMapX] = BLOCK5;
								map2[5][27] = YUKA;
							}
						}
						if (map2[6][27] != BLOCK6 || map2[6][27] == BLOCK6)
						{

							if (map2[6][27] == BLOCK6 && map2[playerMapY][playerMapX] == /*6以降は後で*/map2[4][17])
							{
								map2[playerMapY][playerMapX] = BLOCK6;
								map2[6][27] = YUKA;
							}
						}
						if (map2[7][27] != BLOCK7 || map2[7][27] == BLOCK7)
						{
							if (map2[7][27] == BLOCK7 && map2[playerMapY][playerMapX] == map2[4][19])
							{
								map2[playerMapY][playerMapX] = BLOCK7;
								map2[7][27] = YUKA;
							}
						}
						if (map2[8][27] != BLOCK8 || map2[8][27] == BLOCK8)
						{
							if (map2[8][27] == BLOCK8 && map2[playerMapY][playerMapX] == map2[4][21])
							{
								map2[playerMapY][playerMapX] = BLOCK8;
								map2[8][27] = YUKA;
							}
						}
						playerPosY += playerSpeed;
					}


					if (map2[playerMapY + 1][playerMapX] == BLOCK1)
					{
						map2[1][27] = BLOCK1;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = BU;
						playerPosY += playerSpeed;

					}
					if (map2[playerMapY + 1][playerMapX] == BLOCK22)
					{
						map2[2][27] = BLOCK22;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = BU;
						playerPosY += playerSpeed;

					}
					if (map2[playerMapY + 1][playerMapX] == BLOCK3)
					{
						map2[3][27] = BLOCK3;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = BU;
						playerPosY += playerSpeed;

					}
					if (map2[playerMapY + 1][playerMapX] == BLOCK4)
					{
						map2[4][27] = BLOCK4;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = BU;
						playerPosY += playerSpeed;

					}
					if (map2[playerMapY + 1][playerMapX] == BLOCK5)
					{
						map2[5][27] = BLOCK5;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = BU;
						playerPosY += playerSpeed;

					}
					if (map2[playerMapY + 1][playerMapX] == BLOCK6)
					{
						map2[6][27] = BLOCK6;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = BU;
						playerPosY += playerSpeed;

					}
					if (map2[playerMapY + 1][playerMapX] == BLOCK7)
					{
						map2[7][27] = BLOCK7;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = BU;
						playerPosY += playerSpeed;

					}
					if (map2[playerMapY + 1][playerMapX] == BLOCK8)
					{
						map2[8][27] = BLOCK8;
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = BU;
						playerPosY += playerSpeed;

					}
				}
			}

			//状態変化--------------------------------------------------------------------------------------------------



			//ゴール条件---------------------------------


			// 解答が合ってたらクリアフラグがtrueになる
			if (map2[4][7] == SA)
			{
				isClearFlag = true;
			}

			// ステージ遷移　解答のシーンを作る予定
			if (map2[playerMapY][playerMapX] == GOAL && isClearFlag == true /*&& keys[DIK_SPACE] && preKeys[DIK_SPACE] == 0*/)
			{
				sceneNo = STAGE3;
			}

			//if (map2[playerMapY][playerMapX] == GOAL)
			//{
			//	goalTimer--;
			//	playerSpeed = 0;
			//	if (goalTimer == 0)
			//	{
			//		sceneNo = GAMECLEAR;
			//	}
			//}

			break;

		case STAGE3:
			//マップ情報-----------------------------------------------------------------------------------
			playerMapX = playerPosX / KBlockSize;//map[x][]
			playerMapY = playerPosY / KBlockSize;//map[][y]

			blockMapX = blockPosX / KBlockSize;
			blockMapY = blockPosY / KBlockSize;

			//リスタート
			if (keys[DIK_R] && preKeys[DIK_R] == 0)
			{
				goalTimer = 60;//初期化
				deathTimer = 60;
				playerPosX = 12 * KBlockSize;//プレイヤーの位置
				playerPosY = 18 * KBlockSize;
				playerSpeed = KBlockSize;
				for (int y = 0; y < mapCountY3; y++)
				{
					for (int x = 0; x < mapCountX3; x++)
					{
						map3[y][x] = mapFormat3[y][x];
					}
				}
			}

			//プレイヤー移動-------------------------------------------------------------------------------
			if (keys[DIK_W] && preKeys[DIK_W] == 0 || keys[DIK_UP] && preKeys[DIK_UP] == 0)
			{
				playerTmpY = playerPosY - playerSpeed;
				playerMapY = playerTmpY / KBlockSize;
				//何もないから実際に進ませる
				if (map3[playerMapY][playerMapX] == YUKA)
				{
					playerPosY -= playerSpeed;
				}
				if (map3[playerMapY][playerMapX] == BLOCK1)
				{
					playerPosY -= playerSpeed;
				}
				if (map3[playerMapY][playerMapX] == GOAL)
				{
					playerPosY -= playerSpeed;
				}
				if (map3[playerMapY][playerMapX] == THORN)
				{
					playerPosY -= playerSpeed;
				}

				if (map3[playerMapY][playerMapX] == A)
				{
					if (map3[playerMapY - 1][playerMapX] == YUKA)
					{
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = A;
						if (map3[1][27] != BLOCK1 || map3[1][27] == BLOCK1)
						{
							if (map3[1][27] == BLOCK1 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK1;
								map3[1][27] = YUKA;
							}
						}
						if (map3[2][27] != BLOCK22 || map3[2][27] == BLOCK22)
						{
							if (map3[2][27] == BLOCK22 && map3[playerMapY][playerMapX] == map3[4][11])
							{
								map3[playerMapY][playerMapX] = BLOCK22;
								map3[2][27] = YUKA;
							}
						}
						if (map3[3][27] != BLOCK3 || map3[3][27] == BLOCK3)
						{
							if (map3[3][27] == BLOCK3 && map3[playerMapY][playerMapX] == map3[4][13])
							{
								map3[playerMapY][playerMapX] = BLOCK3;
								map3[3][27] = YUKA;
							}
						}
						if (map3[4][27] != BLOCK4 || map3[4][27] == BLOCK4)
						{
							if (map3[4][27] == BLOCK4 && map3[playerMapY][playerMapX] == map3[4][15])
							{
								map3[playerMapY][playerMapX] = BLOCK4;
								map3[4][27] = YUKA;
							}
						}
						if (map3[5][27] != BLOCK5 || map3[5][27] == BLOCK5)
						{
							if (map3[5][27] == BLOCK5 && map3[playerMapY][playerMapX] == map3[4][17])
							{
								map3[playerMapY][playerMapX] = BLOCK5;
								map3[5][27] = YUKA;
							}
						}
						if (map3[6][27] != BLOCK6 || map3[6][27] == BLOCK6)
						{

							if (map3[6][27] == BLOCK6 && map3[playerMapY][playerMapX] == /*6以降は後で*/map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK6;
								map3[6][27] = YUKA;
							}
						}
						if (map3[7][27] != BLOCK7 || map3[7][27] == BLOCK7)
						{
							if (map3[7][27] == BLOCK7 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK7;
								map3[7][27] = YUKA;
							}
						}
						if (map3[8][27] != BLOCK8 || map3[8][27] == BLOCK8)
						{
							if (map3[8][27] == BLOCK8 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK8;
								map3[8][27] = YUKA;
							}
						}
						playerPosY -= playerSpeed;
					}

					if (map3[playerMapY - 1][playerMapX] == BLOCK1)
					{
						map3[1][27] = BLOCK1;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = A;
						playerPosY -= playerSpeed;

					}

					if (map3[playerMapY - 1][playerMapX] == BLOCK22)
					{
						map3[2][27] = BLOCK22;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = A;
						playerPosY -= playerSpeed;

					}
					if (map3[playerMapY - 1][playerMapX] == BLOCK3)
					{
						map3[3][27] = BLOCK3;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = A;
						playerPosY -= playerSpeed;

					}
					if (map3[playerMapY - 1][playerMapX] == BLOCK4)
					{
						map3[4][27] = BLOCK4;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = A;
						playerPosY -= playerSpeed;

					}
					if (map3[playerMapY - 1][playerMapX] == BLOCK5)
					{
						map3[5][27] = BLOCK5;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = A;
						playerPosY -= playerSpeed;

					}
					if (map3[playerMapY - 1][playerMapX] == BLOCK6)
					{
						map3[6][27] = BLOCK6;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = A;
						playerPosY -= playerSpeed;

					}
					if (map3[playerMapY - 1][playerMapX] == BLOCK7)
					{
						map3[7][27] = BLOCK7;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = A;
						playerPosY -= playerSpeed;

					}
					if (map3[playerMapY - 1][playerMapX] == BLOCK8)
					{
						map3[8][27] = BLOCK8;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = A;
						playerPosY -= playerSpeed;

					}



				}

				// 1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111
				// ここから直して
				if (map3[playerMapY][playerMapX] == KE)
				{
					if (map3[playerMapY - 1][playerMapX] == YUKA)
					{
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = KE; //ここをKEに変える　したも同じ
						if (map3[1][27] != BLOCK1 || map3[1][27] == BLOCK1)
						{
							if (map3[1][27] == BLOCK1 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK1;
								map3[1][27] = YUKA;
							}
						}
						if (map3[2][27] != BLOCK22 || map3[2][27] == BLOCK22)
						{
							if (map3[2][27] == BLOCK22 && map3[playerMapY][playerMapX] == map3[4][11])
							{
								map3[playerMapY][playerMapX] = BLOCK22;
								map3[2][27] = YUKA;
							}
						}
						if (map3[3][27] != BLOCK3 || map3[3][27] == BLOCK3)
						{
							if (map3[3][27] == BLOCK3 && map3[playerMapY][playerMapX] == map3[4][13])
							{
								map3[playerMapY][playerMapX] = BLOCK3;
								map3[3][27] = YUKA;
							}
						}
						if (map3[4][27] != BLOCK4 || map3[4][27] == BLOCK4)
						{
							if (map3[4][27] == BLOCK4 && map3[playerMapY][playerMapX] == map3[4][15])
							{
								map3[playerMapY][playerMapX] = BLOCK4;
								map3[4][27] = YUKA;
							}
						}
						if (map3[5][27] != BLOCK5 || map3[5][27] == BLOCK5)
						{
							if (map3[5][27] == BLOCK5 && map3[playerMapY][playerMapX] == map3[4][17])
							{
								map3[playerMapY][playerMapX] = BLOCK5;
								map3[5][27] = YUKA;
							}
						}
						if (map3[6][27] != BLOCK6 || map3[6][27] == BLOCK6)
						{

							if (map3[6][27] == BLOCK6 && map3[playerMapY][playerMapX] == /*6以降は後で*/map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK6;
								map3[6][27] = YUKA;
							}
						}
						if (map3[7][27] != BLOCK7 || map3[7][27] == BLOCK7)
						{
							if (map3[7][27] == BLOCK7 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK7;
								map3[7][27] = YUKA;
							}
						}
						if (map3[8][27] != BLOCK8 || map3[8][27] == BLOCK8)
						{
							if (map3[8][27] == BLOCK8 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK8;
								map3[8][27] = YUKA;
							}
						}
						playerPosY -= playerSpeed;
					}

					if (map3[playerMapY - 1][playerMapX] == BLOCK1)
					{
						map3[1][27] = BLOCK1;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = KE;
						playerPosY -= playerSpeed;

					}

					if (map3[playerMapY - 1][playerMapX] == BLOCK22)
					{
						map3[2][27] = BLOCK22;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = KE;
						playerPosY -= playerSpeed;

					}
					if (map3[playerMapY - 1][playerMapX] == BLOCK3)
					{
						map3[3][27] = BLOCK3;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = KE;
						playerPosY -= playerSpeed;

					}
					if (map3[playerMapY - 1][playerMapX] == BLOCK4)
					{
						map3[4][27] = BLOCK4;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = KE;
						playerPosY -= playerSpeed;

					}
					if (map3[playerMapY - 1][playerMapX] == BLOCK5)
					{
						map3[5][27] = BLOCK5;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = KE;
						playerPosY -= playerSpeed;

					}
					if (map3[playerMapY - 1][playerMapX] == BLOCK6)
					{
						map3[6][27] = BLOCK6;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = KE;
						playerPosY -= playerSpeed;

					}
					if (map3[playerMapY - 1][playerMapX] == BLOCK7)
					{
						map3[7][27] = BLOCK7;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = KE;
						playerPosY -= playerSpeed;

					}
					if (map3[playerMapY - 1][playerMapX] == BLOCK8)
					{
						map3[8][27] = BLOCK8;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = KE;
						playerPosY -= playerSpeed;

					}
				}
				if (map3[playerMapY][playerMapX] == E)
				{
					if (map3[playerMapY - 1][playerMapX] == YUKA)
					{
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = E;
						if (map3[1][27] != BLOCK1 || map3[1][27] == BLOCK1)
						{
							if (map3[1][27] == BLOCK1 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK1;
								map3[1][27] = YUKA;
							}
						}
						if (map3[2][27] != BLOCK22 || map3[2][27] == BLOCK22)
						{
							if (map3[2][27] == BLOCK22 && map3[playerMapY][playerMapX] == map3[4][11])
							{
								map3[playerMapY][playerMapX] = BLOCK22;
								map3[2][27] = YUKA;
							}
						}
						if (map3[3][27] != BLOCK3 || map3[3][27] == BLOCK3)
						{
							if (map3[3][27] == BLOCK3 && map3[playerMapY][playerMapX] == map3[4][13])
							{
								map3[playerMapY][playerMapX] = BLOCK3;
								map3[3][27] = YUKA;
							}
						}
						if (map3[4][27] != BLOCK4 || map3[4][27] == BLOCK4)
						{
							if (map3[4][27] == BLOCK4 && map3[playerMapY][playerMapX] == map3[4][15])
							{
								map3[playerMapY][playerMapX] = BLOCK4;
								map3[4][27] = YUKA;
							}
						}
						if (map3[5][27] != BLOCK5 || map3[5][27] == BLOCK5)
						{
							if (map3[5][27] == BLOCK5 && map3[playerMapY][playerMapX] == map3[4][17])
							{
								map3[playerMapY][playerMapX] = BLOCK5;
								map3[5][27] = YUKA;
							}
						}
						if (map3[6][27] != BLOCK6 || map3[6][27] == BLOCK6)
						{

							if (map3[6][27] == BLOCK6 && map3[playerMapY][playerMapX] == /*6以降は後で*/map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK6;
								map3[6][27] = YUKA;
							}
						}
						if (map3[7][27] != BLOCK7 || map3[7][27] == BLOCK7)
						{
							if (map3[7][27] == BLOCK7 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK7;
								map3[7][27] = YUKA;
							}
						}
						if (map3[8][27] != BLOCK8 || map3[8][27] == BLOCK8)
						{
							if (map3[8][27] == BLOCK8 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK8;
								map3[8][27] = YUKA;
							}
						}
						playerPosY -= playerSpeed;
					}
					if (map3[playerMapY - 1][playerMapX] == BLOCK1)
					{
						map3[1][27] = BLOCK1;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = E;
						playerPosY -= playerSpeed;

					}

					if (map3[playerMapY - 1][playerMapX] == BLOCK22)
					{
						map3[2][27] = BLOCK22;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = E;
						playerPosY -= playerSpeed;

					}
					if (map3[playerMapY - 1][playerMapX] == BLOCK3)
					{
						map3[3][27] = BLOCK3;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = E;
						playerPosY -= playerSpeed;

					}
					if (map3[playerMapY - 1][playerMapX] == BLOCK4)
					{
						map3[4][27] = BLOCK4;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = E;
						playerPosY -= playerSpeed;

					}
					if (map3[playerMapY - 1][playerMapX] == BLOCK5)
					{
						map3[5][27] = BLOCK5;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = E;
						playerPosY -= playerSpeed;

					}
					if (map3[playerMapY - 1][playerMapX] == BLOCK6)
					{
						map3[6][27] = BLOCK6;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = E;
						playerPosY -= playerSpeed;

					}
					if (map3[playerMapY - 1][playerMapX] == BLOCK7)
					{
						map3[7][27] = BLOCK7;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = E;
						playerPosY -= playerSpeed;

					}
					if (map3[playerMapY - 1][playerMapX] == BLOCK8)
					{
						map3[8][27] = BLOCK8;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = E;
						playerPosY -= playerSpeed;

					}
				}
				if (map3[playerMapY][playerMapX] == KA)
				{
					if (map3[playerMapY - 1][playerMapX] == YUKA)
					{
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = KA;
						if (map3[1][27] != BLOCK1 || map3[1][27] == BLOCK1)
						{
							if (map3[1][27] == BLOCK1 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK1;
								map3[1][27] = YUKA;
							}
						}
						if (map3[2][27] != BLOCK22 || map3[2][27] == BLOCK22)
						{
							if (map3[2][27] == BLOCK22 && map3[playerMapY][playerMapX] == map3[4][11])
							{
								map3[playerMapY][playerMapX] = BLOCK22;
								map3[2][27] = YUKA;
							}
						}
						if (map3[3][27] != BLOCK3 || map3[3][27] == BLOCK3)
						{
							if (map3[3][27] == BLOCK3 && map3[playerMapY][playerMapX] == map3[4][13])
							{
								map3[playerMapY][playerMapX] = BLOCK3;
								map3[3][27] = YUKA;
							}
						}
						if (map3[4][27] != BLOCK4 || map3[4][27] == BLOCK4)
						{
							if (map3[4][27] == BLOCK4 && map3[playerMapY][playerMapX] == map3[4][15])
							{
								map3[playerMapY][playerMapX] = BLOCK4;
								map3[4][27] = YUKA;
							}
						}
						if (map3[5][27] != BLOCK5 || map3[5][27] == BLOCK5)
						{
							if (map3[5][27] == BLOCK5 && map3[playerMapY][playerMapX] == map3[4][17])
							{
								map3[playerMapY][playerMapX] = BLOCK5;
								map3[5][27] = YUKA;
							}
						}
						if (map3[6][27] != BLOCK6 || map3[6][27] == BLOCK6)
						{

							if (map3[6][27] == BLOCK6 && map3[playerMapY][playerMapX] == /*6以降は後で*/map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK6;
								map3[6][27] = YUKA;
							}
						}
						if (map3[7][27] != BLOCK7 || map3[7][27] == BLOCK7)
						{
							if (map3[7][27] == BLOCK7 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK7;
								map3[7][27] = YUKA;
							}
						}
						if (map3[8][27] != BLOCK8 || map3[8][27] == BLOCK8)
						{
							if (map3[8][27] == BLOCK8 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK8;
								map3[8][27] = YUKA;
							}
						}
						playerPosY -= playerSpeed;
					}

					if (map3[playerMapY - 1][playerMapX] == BLOCK1)
					{
						map3[1][27] = BLOCK1;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = KA;
						playerPosY -= playerSpeed;

					}

					if (map3[playerMapY - 1][playerMapX] == BLOCK22)
					{
						map3[2][27] = BLOCK22;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = KA;
						playerPosY -= playerSpeed;

					}
					if (map3[playerMapY - 1][playerMapX] == BLOCK3)
					{
						map3[3][27] = BLOCK3;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = KA;
						playerPosY -= playerSpeed;

					}
					if (map3[playerMapY - 1][playerMapX] == BLOCK4)
					{
						map3[4][27] = BLOCK4;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = KA;
						playerPosY -= playerSpeed;

					}
					if (map3[playerMapY - 1][playerMapX] == BLOCK5)
					{
						map3[5][27] = BLOCK5;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = KA;
						playerPosY -= playerSpeed;

					}
					if (map3[playerMapY - 1][playerMapX] == BLOCK6)
					{
						map3[6][27] = BLOCK6;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = KA;
						playerPosY -= playerSpeed;

					}
					if (map3[playerMapY - 1][playerMapX] == BLOCK7)
					{
						map3[7][27] = BLOCK7;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = KA;
						playerPosY -= playerSpeed;

					}
					if (map3[playerMapY - 1][playerMapX] == BLOCK8)
					{
						map3[8][27] = BLOCK8;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = KA;
						playerPosY -= playerSpeed;

					}
				}
				if (map3[playerMapY][playerMapX] == KU)
				{
					if (map3[playerMapY - 1][playerMapX] == YUKA)
					{
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = KU;
						if (map3[1][27] != BLOCK1 || map3[1][27] == BLOCK1)
						{
							if (map3[1][27] == BLOCK1 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK1;
								map3[1][27] = YUKA;
							}
						}
						if (map3[2][27] != BLOCK22 || map3[2][27] == BLOCK22)
						{
							if (map3[2][27] == BLOCK22 && map3[playerMapY][playerMapX] == map3[4][11])
							{
								map3[playerMapY][playerMapX] = BLOCK22;
								map3[2][27] = YUKA;
							}
						}
						if (map3[3][27] != BLOCK3 || map3[3][27] == BLOCK3)
						{
							if (map3[3][27] == BLOCK3 && map3[playerMapY][playerMapX] == map3[4][13])
							{
								map3[playerMapY][playerMapX] = BLOCK3;
								map3[3][27] = YUKA;
							}
						}
						if (map3[4][27] != BLOCK4 || map3[4][27] == BLOCK4)
						{
							if (map3[4][27] == BLOCK4 && map3[playerMapY][playerMapX] == map3[4][15])
							{
								map3[playerMapY][playerMapX] = BLOCK4;
								map3[4][27] = YUKA;
							}
						}
						if (map3[5][27] != BLOCK5 || map3[5][27] == BLOCK5)
						{
							if (map3[5][27] == BLOCK5 && map3[playerMapY][playerMapX] == map3[4][17])
							{
								map3[playerMapY][playerMapX] = BLOCK5;
								map3[5][27] = YUKA;
							}
						}
						if (map3[6][27] != BLOCK6 || map3[6][27] == BLOCK6)
						{

							if (map3[6][27] == BLOCK6 && map3[playerMapY][playerMapX] == /*6以降は後で*/map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK6;
								map3[6][27] = YUKA;
							}
						}
						if (map3[7][27] != BLOCK7 || map3[7][27] == BLOCK7)
						{
							if (map3[7][27] == BLOCK7 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK7;
								map3[7][27] = YUKA;
							}
						}
						if (map3[8][27] != BLOCK8 || map3[8][27] == BLOCK8)
						{
							if (map3[8][27] == BLOCK8 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK8;
								map3[8][27] = YUKA;
							}
						}
						playerPosY -= playerSpeed;
					}

					if (map3[playerMapY - 1][playerMapX] == BLOCK1)
					{
						map3[1][27] = BLOCK1;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = KU;
						playerPosY -= playerSpeed;

					}

					if (map3[playerMapY - 1][playerMapX] == BLOCK22)
					{
						map3[2][27] = BLOCK22;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = KU;
						playerPosY -= playerSpeed;

					}
					if (map3[playerMapY - 1][playerMapX] == BLOCK3)
					{
						map3[3][27] = BLOCK3;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = KU;
						playerPosY -= playerSpeed;

					}
					if (map3[playerMapY - 1][playerMapX] == BLOCK4)
					{
						map3[4][27] = BLOCK4;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = KU;
						playerPosY -= playerSpeed;

					}
					if (map3[playerMapY - 1][playerMapX] == BLOCK5)
					{
						map3[5][27] = BLOCK5;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = KU;
						playerPosY -= playerSpeed;

					}
					if (map3[playerMapY - 1][playerMapX] == BLOCK6)
					{
						map3[6][27] = BLOCK6;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = KU;
						playerPosY -= playerSpeed;

					}
					if (map3[playerMapY - 1][playerMapX] == BLOCK7)
					{
						map3[7][27] = BLOCK7;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = KU;
						playerPosY -= playerSpeed;

					}
					if (map3[playerMapY - 1][playerMapX] == BLOCK8)
					{
						map3[8][27] = BLOCK8;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = KU;
						playerPosY -= playerSpeed;

					}
				}
				if (map3[playerMapY][playerMapX] == NO)
				{
					if (map3[playerMapY - 1][playerMapX] == YUKA)
					{
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = NO;
						if (map3[1][27] != BLOCK1 || map3[1][27] == BLOCK1)
						{
							if (map3[1][27] == BLOCK1 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK1;
								map3[1][27] = YUKA;
							}
						}
						if (map3[2][27] != BLOCK22 || map3[2][27] == BLOCK22)
						{
							if (map3[2][27] == BLOCK22 && map3[playerMapY][playerMapX] == map3[4][11])
							{
								map3[playerMapY][playerMapX] = BLOCK22;
								map3[2][27] = YUKA;
							}
						}
						if (map3[3][27] != BLOCK3 || map3[3][27] == BLOCK3)
						{
							if (map3[3][27] == BLOCK3 && map3[playerMapY][playerMapX] == map3[4][13])
							{
								map3[playerMapY][playerMapX] = BLOCK3;
								map3[3][27] = YUKA;
							}
						}
						if (map3[4][27] != BLOCK4 || map3[4][27] == BLOCK4)
						{
							if (map3[4][27] == BLOCK4 && map3[playerMapY][playerMapX] == map3[4][15])
							{
								map3[playerMapY][playerMapX] = BLOCK4;
								map3[4][27] = YUKA;
							}
						}
						if (map3[5][27] != BLOCK5 || map3[5][27] == BLOCK5)
						{
							if (map3[5][27] == BLOCK5 && map3[playerMapY][playerMapX] == map3[4][17])
							{
								map3[playerMapY][playerMapX] = BLOCK5;
								map3[5][27] = YUKA;
							}
						}
						if (map3[6][27] != BLOCK6 || map3[6][27] == BLOCK6)
						{

							if (map3[6][27] == BLOCK6 && map3[playerMapY][playerMapX] == /*6以降は後で*/map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK6;
								map3[6][27] = YUKA;
							}
						}
						if (map3[7][27] != BLOCK7 || map3[7][27] == BLOCK7)
						{
							if (map3[7][27] == BLOCK7 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK7;
								map3[7][27] = YUKA;
							}
						}
						if (map3[8][27] != BLOCK8 || map3[8][27] == BLOCK8)
						{
							if (map3[8][27] == BLOCK8 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK8;
								map3[8][27] = YUKA;
							}
						}
						playerPosY -= playerSpeed;
					}

					if (map3[playerMapY - 1][playerMapX] == BLOCK1)
					{
						map3[1][27] = BLOCK1;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = NO;
						playerPosY -= playerSpeed;

					}

					if (map3[playerMapY - 1][playerMapX] == BLOCK22)
					{
						map3[2][27] = BLOCK22;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = NO;
						playerPosY -= playerSpeed;

					}
					if (map3[playerMapY - 1][playerMapX] == BLOCK3)
					{
						map3[3][27] = BLOCK3;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = NO;
						playerPosY -= playerSpeed;

					}
					if (map3[playerMapY - 1][playerMapX] == BLOCK4)
					{
						map3[4][27] = BLOCK4;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = NO;
						playerPosY -= playerSpeed;

					}
					if (map3[playerMapY - 1][playerMapX] == BLOCK5)
					{
						map3[5][27] = BLOCK5;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = NO;
						playerPosY -= playerSpeed;

					}
					if (map3[playerMapY - 1][playerMapX] == BLOCK6)
					{
						map3[6][27] = BLOCK6;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = NO;
						playerPosY -= playerSpeed;

					}
					if (map3[playerMapY - 1][playerMapX] == BLOCK7)
					{
						map3[7][27] = BLOCK7;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = NO;
						playerPosY -= playerSpeed;

					}
					if (map3[playerMapY - 1][playerMapX] == BLOCK8)
					{
						map3[8][27] = BLOCK8;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = NO;
						playerPosY -= playerSpeed;

					}
				}
				if (map3[playerMapY][playerMapX] == GA)
				{
					if (map3[playerMapY - 1][playerMapX] == YUKA)
					{
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = GA;
						if (map3[1][27] != BLOCK1 || map3[1][27] == BLOCK1)
						{
							if (map3[1][27] == BLOCK1 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK1;
								map3[1][27] = YUKA;
							}
						}
						if (map3[2][27] != BLOCK22 || map3[2][27] == BLOCK22)
						{
							if (map3[2][27] == BLOCK22 && map3[playerMapY][playerMapX] == map3[4][11])
							{
								map3[playerMapY][playerMapX] = BLOCK22;
								map3[2][27] = YUKA;
							}
						}
						if (map3[3][27] != BLOCK3 || map3[3][27] == BLOCK3)
						{
							if (map3[3][27] == BLOCK3 && map3[playerMapY][playerMapX] == map3[4][13])
							{
								map3[playerMapY][playerMapX] = BLOCK3;
								map3[3][27] = YUKA;
							}
						}
						if (map3[4][27] != BLOCK4 || map3[4][27] == BLOCK4)
						{
							if (map3[4][27] == BLOCK4 && map3[playerMapY][playerMapX] == map3[4][15])
							{
								map3[playerMapY][playerMapX] = BLOCK4;
								map3[4][27] = YUKA;
							}
						}
						if (map3[5][27] != BLOCK5 || map3[5][27] == BLOCK5)
						{
							if (map3[5][27] == BLOCK5 && map3[playerMapY][playerMapX] == map3[4][17])
							{
								map3[playerMapY][playerMapX] = BLOCK5;
								map3[5][27] = YUKA;
							}
						}
						if (map3[6][27] != BLOCK6 || map3[6][27] == BLOCK6)
						{

							if (map3[6][27] == BLOCK6 && map3[playerMapY][playerMapX] == /*6以降は後で*/map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK6;
								map3[6][27] = YUKA;
							}
						}
						if (map3[7][27] != BLOCK7 || map3[7][27] == BLOCK7)
						{
							if (map3[7][27] == BLOCK7 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK7;
								map3[7][27] = YUKA;
							}
						}
						if (map3[8][27] != BLOCK8 || map3[8][27] == BLOCK8)
						{
							if (map3[8][27] == BLOCK8 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK8;
								map3[8][27] = YUKA;
							}
						}
						playerPosY -= playerSpeed;
					}
					if (map3[playerMapY - 1][playerMapX] == BLOCK1)
					{
						map3[1][27] = BLOCK1;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = GA;
						playerPosY -= playerSpeed;

					}

					if (map3[playerMapY - 1][playerMapX] == BLOCK22)
					{
						map3[2][27] = BLOCK22;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = GA;
						playerPosY -= playerSpeed;

					}
					if (map3[playerMapY - 1][playerMapX] == BLOCK3)
					{
						map3[3][27] = BLOCK3;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = GA;
						playerPosY -= playerSpeed;

					}
					if (map3[playerMapY - 1][playerMapX] == BLOCK4)
					{
						map3[4][27] = BLOCK4;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = GA;
						playerPosY -= playerSpeed;

					}
					if (map3[playerMapY - 1][playerMapX] == BLOCK5)
					{
						map3[5][27] = BLOCK5;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = GA;
						playerPosY -= playerSpeed;

					}
					if (map3[playerMapY - 1][playerMapX] == BLOCK6)
					{
						map3[6][27] = BLOCK6;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = GA;
						playerPosY -= playerSpeed;

					}
					if (map3[playerMapY - 1][playerMapX] == BLOCK7)
					{
						map3[7][27] = BLOCK7;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = GA;
						playerPosY -= playerSpeed;

					}
					if (map3[playerMapY - 1][playerMapX] == BLOCK8)
					{
						map3[8][27] = BLOCK8;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = GA;
						playerPosY -= playerSpeed;

					}
				}
				if (map3[playerMapY][playerMapX] == SU)
				{
					if (map3[playerMapY - 1][playerMapX] == YUKA)
					{
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = SU;
						if (map3[1][27] != BLOCK1 || map3[1][27] == BLOCK1)
						{
							if (map3[1][27] == BLOCK1 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK1;
								map3[1][27] = YUKA;
							}
						}
						if (map3[2][27] != BLOCK22 || map3[2][27] == BLOCK22)
						{
							if (map3[2][27] == BLOCK22 && map3[playerMapY][playerMapX] == map3[4][11])
							{
								map3[playerMapY][playerMapX] = BLOCK22;
								map3[2][27] = YUKA;
							}
						}
						if (map3[3][27] != BLOCK3 || map3[3][27] == BLOCK3)
						{
							if (map3[3][27] == BLOCK3 && map3[playerMapY][playerMapX] == map3[4][13])
							{
								map3[playerMapY][playerMapX] = BLOCK3;
								map3[3][27] = YUKA;
							}
						}
						if (map3[4][27] != BLOCK4 || map3[4][27] == BLOCK4)
						{
							if (map3[4][27] == BLOCK4 && map3[playerMapY][playerMapX] == map3[4][15])
							{
								map3[playerMapY][playerMapX] = BLOCK4;
								map3[4][27] = YUKA;
							}
						}
						if (map3[5][27] != BLOCK5 || map3[5][27] == BLOCK5)
						{
							if (map3[5][27] == BLOCK5 && map3[playerMapY][playerMapX] == map3[4][17])
							{
								map3[playerMapY][playerMapX] = BLOCK5;
								map3[5][27] = YUKA;
							}
						}
						if (map3[6][27] != BLOCK6 || map3[6][27] == BLOCK6)
						{

							if (map3[6][27] == BLOCK6 && map3[playerMapY][playerMapX] == /*6以降は後で*/map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK6;
								map3[6][27] = YUKA;
							}
						}
						if (map3[7][27] != BLOCK7 || map3[7][27] == BLOCK7)
						{
							if (map3[7][27] == BLOCK7 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK7;
								map3[7][27] = YUKA;
							}
						}
						if (map3[8][27] != BLOCK8 || map3[8][27] == BLOCK8)
						{
							if (map3[8][27] == BLOCK8 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK8;
								map3[8][27] = YUKA;
							}
						}
						playerPosY -= playerSpeed;
					}

					if (map3[playerMapY - 1][playerMapX] == BLOCK1)
					{
						map3[1][27] = BLOCK1;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = SU;
						playerPosY -= playerSpeed;

					}

					if (map3[playerMapY - 1][playerMapX] == BLOCK22)
					{
						map3[2][27] = BLOCK22;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = SU;
						playerPosY -= playerSpeed;

					}
					if (map3[playerMapY - 1][playerMapX] == BLOCK3)
					{
						map3[3][27] = BLOCK3;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = SU;
						playerPosY -= playerSpeed;

					}
					if (map3[playerMapY - 1][playerMapX] == BLOCK4)
					{
						map3[4][27] = BLOCK4;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = SU;
						playerPosY -= playerSpeed;

					}
					if (map3[playerMapY - 1][playerMapX] == BLOCK5)
					{
						map3[5][27] = BLOCK5;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = SU;
						playerPosY -= playerSpeed;

					}
					if (map3[playerMapY - 1][playerMapX] == BLOCK6)
					{
						map3[6][27] = BLOCK6;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = SU;
						playerPosY -= playerSpeed;

					}
					if (map3[playerMapY - 1][playerMapX] == BLOCK7)
					{
						map3[7][27] = BLOCK7;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = SU;
						playerPosY -= playerSpeed;

					}
					if (map3[playerMapY - 1][playerMapX] == BLOCK8)
					{
						map3[8][27] = BLOCK8;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = SU;
						playerPosY -= playerSpeed;

					}
				}
				if (map3[playerMapY][playerMapX] == SO)
				{
					if (map3[playerMapY - 1][playerMapX] == YUKA)
					{
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = SO;
						if (map3[1][27] != BLOCK1 || map3[1][27] == BLOCK1)
						{
							if (map3[1][27] == BLOCK1 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK1;
								map3[1][27] = YUKA;
							}
						}
						if (map3[2][27] != BLOCK22 || map3[2][27] == BLOCK22)
						{
							if (map3[2][27] == BLOCK22 && map3[playerMapY][playerMapX] == map3[4][11])
							{
								map3[playerMapY][playerMapX] = BLOCK22;
								map3[2][27] = YUKA;
							}
						}
						if (map3[3][27] != BLOCK3 || map3[3][27] == BLOCK3)
						{
							if (map3[3][27] == BLOCK3 && map3[playerMapY][playerMapX] == map3[4][13])
							{
								map3[playerMapY][playerMapX] = BLOCK3;
								map3[3][27] = YUKA;
							}
						}
						if (map3[4][27] != BLOCK4 || map3[4][27] == BLOCK4)
						{
							if (map3[4][27] == BLOCK4 && map3[playerMapY][playerMapX] == map3[4][15])
							{
								map3[playerMapY][playerMapX] = BLOCK4;
								map3[4][27] = YUKA;
							}
						}
						if (map3[5][27] != BLOCK5 || map3[5][27] == BLOCK5)
						{
							if (map3[5][27] == BLOCK5 && map3[playerMapY][playerMapX] == map3[4][17])
							{
								map3[playerMapY][playerMapX] = BLOCK5;
								map3[5][27] = YUKA;
							}
						}
						if (map3[6][27] != BLOCK6 || map3[6][27] == BLOCK6)
						{

							if (map3[6][27] == BLOCK6 && map3[playerMapY][playerMapX] == /*6以降は後で*/map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK6;
								map3[6][27] = YUKA;
							}
						}
						if (map3[7][27] != BLOCK7 || map3[7][27] == BLOCK7)
						{
							if (map3[7][27] == BLOCK7 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK7;
								map3[7][27] = YUKA;
							}
						}
						if (map3[8][27] != BLOCK8 || map3[8][27] == BLOCK8)
						{
							if (map3[8][27] == BLOCK8 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK8;
								map3[8][27] = YUKA;
							}
						}
						playerPosY -= playerSpeed;
					}

					if (map3[playerMapY - 1][playerMapX] == BLOCK1)
					{
						map3[1][27] = BLOCK1;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = SO;
						playerPosY -= playerSpeed;

					}

					if (map3[playerMapY - 1][playerMapX] == BLOCK22)
					{
						map3[2][27] = BLOCK22;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = SO;
						playerPosY -= playerSpeed;

					}
					if (map3[playerMapY - 1][playerMapX] == BLOCK3)
					{
						map3[3][27] = BLOCK3;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = SO;
						playerPosY -= playerSpeed;

					}
					if (map3[playerMapY - 1][playerMapX] == BLOCK4)
					{
						map3[4][27] = BLOCK4;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = SO;
						playerPosY -= playerSpeed;

					}
					if (map3[playerMapY - 1][playerMapX] == BLOCK5)
					{
						map3[5][27] = BLOCK5;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = SO;
						playerPosY -= playerSpeed;

					}
					if (map3[playerMapY - 1][playerMapX] == BLOCK6)
					{
						map3[6][27] = BLOCK6;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = SO;
						playerPosY -= playerSpeed;

					}
					if (map3[playerMapY - 1][playerMapX] == BLOCK7)
					{
						map3[7][27] = BLOCK7;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = SO;
						playerPosY -= playerSpeed;

					}
					if (map3[playerMapY - 1][playerMapX] == BLOCK8)
					{
						map3[8][27] = BLOCK8;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = SO;
						playerPosY -= playerSpeed;

					}
				}
				if (map3[playerMapY][playerMapX] == NI)
				{
					if (map3[playerMapY - 1][playerMapX] == YUKA)
					{
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = NI;
						if (map3[1][27] != BLOCK1 || map3[1][27] == BLOCK1)
						{
							if (map3[1][27] == BLOCK1 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK1;
								map3[1][27] = YUKA;
							}
						}
						if (map3[2][27] != BLOCK22 || map3[2][27] == BLOCK22)
						{
							if (map3[2][27] == BLOCK22 && map3[playerMapY][playerMapX] == map3[4][11])
							{
								map3[playerMapY][playerMapX] = BLOCK22;
								map3[2][27] = YUKA;
							}
						}
						if (map3[3][27] != BLOCK3 || map3[3][27] == BLOCK3)
						{
							if (map3[3][27] == BLOCK3 && map3[playerMapY][playerMapX] == map3[4][13])
							{
								map3[playerMapY][playerMapX] = BLOCK3;
								map3[3][27] = YUKA;
							}
						}
						if (map3[4][27] != BLOCK4 || map3[4][27] == BLOCK4)
						{
							if (map3[4][27] == BLOCK4 && map3[playerMapY][playerMapX] == map3[4][15])
							{
								map3[playerMapY][playerMapX] = BLOCK4;
								map3[4][27] = YUKA;
							}
						}
						if (map3[5][27] != BLOCK5 || map3[5][27] == BLOCK5)
						{
							if (map3[5][27] == BLOCK5 && map3[playerMapY][playerMapX] == map3[4][17])
							{
								map3[playerMapY][playerMapX] = BLOCK5;
								map3[5][27] = YUKA;
							}
						}
						if (map3[6][27] != BLOCK6 || map3[6][27] == BLOCK6)
						{

							if (map3[6][27] == BLOCK6 && map3[playerMapY][playerMapX] == /*6以降は後で*/map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK6;
								map3[6][27] = YUKA;
							}
						}
						if (map3[7][27] != BLOCK7 || map3[7][27] == BLOCK7)
						{
							if (map3[7][27] == BLOCK7 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK7;
								map3[7][27] = YUKA;
							}
						}
						if (map3[8][27] != BLOCK8 || map3[8][27] == BLOCK8)
						{
							if (map3[8][27] == BLOCK8 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK8;
								map3[8][27] = YUKA;
							}
						}
						playerPosY -= playerSpeed;
					}

					if (map3[playerMapY - 1][playerMapX] == BLOCK1)
					{
						map3[1][27] = BLOCK1;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = NI;
						playerPosY -= playerSpeed;

					}

					if (map3[playerMapY - 1][playerMapX] == BLOCK22)
					{
						map3[2][27] = BLOCK22;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = NI;
						playerPosY -= playerSpeed;

					}
					if (map3[playerMapY - 1][playerMapX] == BLOCK3)
					{
						map3[3][27] = BLOCK3;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = NI;
						playerPosY -= playerSpeed;

					}
					if (map3[playerMapY - 1][playerMapX] == BLOCK4)
					{
						map3[4][27] = BLOCK4;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = NI;
						playerPosY -= playerSpeed;

					}
					if (map3[playerMapY - 1][playerMapX] == BLOCK5)
					{
						map3[5][27] = BLOCK5;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = NI;
						playerPosY -= playerSpeed;

					}
					if (map3[playerMapY - 1][playerMapX] == BLOCK6)
					{
						map3[6][27] = BLOCK6;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = NI;
						playerPosY -= playerSpeed;

					}
					if (map3[playerMapY - 1][playerMapX] == BLOCK7)
					{
						map3[7][27] = BLOCK7;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = NI;
						playerPosY -= playerSpeed;

					}
					if (map3[playerMapY - 1][playerMapX] == BLOCK8)
					{
						map3[8][27] = BLOCK8;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = NI;
						playerPosY -= playerSpeed;

					}
				}
				if (map3[playerMapY][playerMapX] == CHI)
				{
					if (map3[playerMapY - 1][playerMapX] == YUKA)
					{
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = CHI;
						if (map3[1][27] != BLOCK1 || map3[1][27] == BLOCK1)
						{
							if (map3[1][27] == BLOCK1 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK1;
								map3[1][27] = YUKA;
							}
						}
						if (map3[2][27] != BLOCK22 || map3[2][27] == BLOCK22)
						{
							if (map3[2][27] == BLOCK22 && map3[playerMapY][playerMapX] == map3[4][11])
							{
								map3[playerMapY][playerMapX] = BLOCK22;
								map3[2][27] = YUKA;
							}
						}
						if (map3[3][27] != BLOCK3 || map3[3][27] == BLOCK3)
						{
							if (map3[3][27] == BLOCK3 && map3[playerMapY][playerMapX] == map3[4][13])
							{
								map3[playerMapY][playerMapX] = BLOCK3;
								map3[3][27] = YUKA;
							}
						}
						if (map3[4][27] != BLOCK4 || map3[4][27] == BLOCK4)
						{
							if (map3[4][27] == BLOCK4 && map3[playerMapY][playerMapX] == map3[4][15])
							{
								map3[playerMapY][playerMapX] = BLOCK4;
								map3[4][27] = YUKA;
							}
						}
						if (map3[5][27] != BLOCK5 || map3[5][27] == BLOCK5)
						{
							if (map3[5][27] == BLOCK5 && map3[playerMapY][playerMapX] == map3[4][17])
							{
								map3[playerMapY][playerMapX] = BLOCK5;
								map3[5][27] = YUKA;
							}
						}
						if (map3[6][27] != BLOCK6 || map3[6][27] == BLOCK6)
						{

							if (map3[6][27] == BLOCK6 && map3[playerMapY][playerMapX] == /*6以降は後で*/map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK6;
								map3[6][27] = YUKA;
							}
						}
						if (map3[7][27] != BLOCK7 || map3[7][27] == BLOCK7)
						{
							if (map3[7][27] == BLOCK7 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK7;
								map3[7][27] = YUKA;
							}
						}
						if (map3[8][27] != BLOCK8 || map3[8][27] == BLOCK8)
						{
							if (map3[8][27] == BLOCK8 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK8;
								map3[8][27] = YUKA;
							}
						}
						playerPosY -= playerSpeed;
					}

					if (map3[playerMapY - 1][playerMapX] == BLOCK1)
					{
						map3[1][27] = BLOCK1;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = CHI;
						playerPosY -= playerSpeed;

					}

					if (map3[playerMapY - 1][playerMapX] == BLOCK22)
					{
						map3[2][27] = BLOCK22;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = CHI;
						playerPosY -= playerSpeed;

					}
					if (map3[playerMapY - 1][playerMapX] == BLOCK3)
					{
						map3[3][27] = BLOCK3;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = CHI;
						playerPosY -= playerSpeed;

					}
					if (map3[playerMapY - 1][playerMapX] == BLOCK4)
					{
						map3[4][27] = BLOCK4;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = CHI;
						playerPosY -= playerSpeed;

					}
					if (map3[playerMapY - 1][playerMapX] == BLOCK5)
					{
						map3[5][27] = BLOCK5;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = CHI;
						playerPosY -= playerSpeed;

					}
					if (map3[playerMapY - 1][playerMapX] == BLOCK6)
					{
						map3[6][27] = BLOCK6;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = CHI;
						playerPosY -= playerSpeed;

					}
					if (map3[playerMapY - 1][playerMapX] == BLOCK7)
					{
						map3[7][27] = BLOCK7;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = CHI;
						playerPosY -= playerSpeed;

					}
					if (map3[playerMapY - 1][playerMapX] == BLOCK8)
					{
						map3[8][27] = BLOCK8;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = CHI;
						playerPosY -= playerSpeed;

					}
				}

				if (map3[playerMapY][playerMapX] == NU)
				{
					if (map3[playerMapY - 1][playerMapX] == YUKA)
					{
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = NU;
						if (map3[1][27] != BLOCK1 || map3[1][27] == BLOCK1)
						{
							if (map3[1][27] == BLOCK1 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK1;
								map3[1][27] = YUKA;
							}
						}
						if (map3[2][27] != BLOCK22 || map3[2][27] == BLOCK22)
						{
							if (map3[2][27] == BLOCK22 && map3[playerMapY][playerMapX] == map3[4][11])
							{
								map3[playerMapY][playerMapX] = BLOCK22;
								map3[2][27] = YUKA;
							}
						}
						if (map3[3][27] != BLOCK3 || map3[3][27] == BLOCK3)
						{
							if (map3[3][27] == BLOCK3 && map3[playerMapY][playerMapX] == map3[4][13])
							{
								map3[playerMapY][playerMapX] = BLOCK3;
								map3[3][27] = YUKA;
							}
						}
						if (map3[4][27] != BLOCK4 || map3[4][27] == BLOCK4)
						{
							if (map3[4][27] == BLOCK4 && map3[playerMapY][playerMapX] == map3[4][15])
							{
								map3[playerMapY][playerMapX] = BLOCK4;
								map3[4][27] = YUKA;
							}
						}
						if (map3[5][27] != BLOCK5 || map3[5][27] == BLOCK5)
						{
							if (map3[5][27] == BLOCK5 && map3[playerMapY][playerMapX] == map3[4][17])
							{
								map3[playerMapY][playerMapX] = BLOCK5;
								map3[5][27] = YUKA;
							}
						}
						if (map3[6][27] != BLOCK6 || map3[6][27] == BLOCK6)
						{

							if (map3[6][27] == BLOCK6 && map3[playerMapY][playerMapX] == /*6以降は後で*/map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK6;
								map3[6][27] = YUKA;
							}
						}
						if (map3[7][27] != BLOCK7 || map3[7][27] == BLOCK7)
						{
							if (map3[7][27] == BLOCK7 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK7;
								map3[7][27] = YUKA;
							}
						}
						if (map3[8][27] != BLOCK8 || map3[8][27] == BLOCK8)
						{
							if (map3[8][27] == BLOCK8 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK8;
								map3[8][27] = YUKA;
							}
						}
						playerPosY -= playerSpeed;
					}

					if (map3[playerMapY - 1][playerMapX] == BLOCK1)
					{
						map3[1][27] = BLOCK1;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = NU;
						playerPosY -= playerSpeed;

					}

					if (map3[playerMapY - 1][playerMapX] == BLOCK22)
					{
						map3[2][27] = BLOCK22;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = NU;
						playerPosY -= playerSpeed;

					}
					if (map3[playerMapY - 1][playerMapX] == BLOCK3)
					{
						map3[3][27] = BLOCK3;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = NU;
						playerPosY -= playerSpeed;

					}
					if (map3[playerMapY - 1][playerMapX] == BLOCK4)
					{
						map3[4][27] = BLOCK4;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = NU;
						playerPosY -= playerSpeed;

					}
					if (map3[playerMapY - 1][playerMapX] == BLOCK5)
					{
						map3[5][27] = BLOCK5;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = NU;
						playerPosY -= playerSpeed;

					}
					if (map3[playerMapY - 1][playerMapX] == BLOCK6)
					{
						map3[6][27] = BLOCK6;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = NU;
						playerPosY -= playerSpeed;

					}
					if (map3[playerMapY - 1][playerMapX] == BLOCK7)
					{
						map3[7][27] = BLOCK7;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = NU;
						playerPosY -= playerSpeed;

					}
					if (map3[playerMapY - 1][playerMapX] == BLOCK8)
					{
						map3[8][27] = BLOCK8;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = NU;
						playerPosY -= playerSpeed;

					}
				}
				if (map3[playerMapY][playerMapX] == NE)
				{
					if (map3[playerMapY - 1][playerMapX] == YUKA)
					{
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = NE;
						if (map3[1][27] != BLOCK1 || map3[1][27] == BLOCK1)
						{
							if (map3[1][27] == BLOCK1 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK1;
								map3[1][27] = YUKA;
							}
						}
						if (map3[2][27] != BLOCK22 || map3[2][27] == BLOCK22)
						{
							if (map3[2][27] == BLOCK22 && map3[playerMapY][playerMapX] == map3[4][11])
							{
								map3[playerMapY][playerMapX] = BLOCK22;
								map3[2][27] = YUKA;
							}
						}
						if (map3[3][27] != BLOCK3 || map3[3][27] == BLOCK3)
						{
							if (map3[3][27] == BLOCK3 && map3[playerMapY][playerMapX] == map3[4][13])
							{
								map3[playerMapY][playerMapX] = BLOCK3;
								map3[3][27] = YUKA;
							}
						}
						if (map3[4][27] != BLOCK4 || map3[4][27] == BLOCK4)
						{
							if (map3[4][27] == BLOCK4 && map3[playerMapY][playerMapX] == map3[4][15])
							{
								map3[playerMapY][playerMapX] = BLOCK4;
								map3[4][27] = YUKA;
							}
						}
						if (map3[5][27] != BLOCK5 || map3[5][27] == BLOCK5)
						{
							if (map3[5][27] == BLOCK5 && map3[playerMapY][playerMapX] == map3[4][17])
							{
								map3[playerMapY][playerMapX] = BLOCK5;
								map3[5][27] = YUKA;
							}
						}
						if (map3[6][27] != BLOCK6 || map3[6][27] == BLOCK6)
						{

							if (map3[6][27] == BLOCK6 && map3[playerMapY][playerMapX] == /*6以降は後で*/map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK6;
								map3[6][27] = YUKA;
							}
						}
						if (map3[7][27] != BLOCK7 || map3[7][27] == BLOCK7)
						{
							if (map3[7][27] == BLOCK7 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK7;
								map3[7][27] = YUKA;
							}
						}
						if (map3[8][27] != BLOCK8 || map3[8][27] == BLOCK8)
						{
							if (map3[8][27] == BLOCK8 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK8;
								map3[8][27] = YUKA;
							}
						}
						playerPosY -= playerSpeed;
					}

					if (map3[playerMapY - 1][playerMapX] == BLOCK1)
					{
						map3[1][27] = BLOCK1;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = NE;
						playerPosY -= playerSpeed;

					}

					if (map3[playerMapY - 1][playerMapX] == BLOCK22)
					{
						map3[2][27] = BLOCK22;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = NE;
						playerPosY -= playerSpeed;

					}
					if (map3[playerMapY - 1][playerMapX] == BLOCK3)
					{
						map3[3][27] = BLOCK3;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = NE;
						playerPosY -= playerSpeed;

					}
					if (map3[playerMapY - 1][playerMapX] == BLOCK4)
					{
						map3[4][27] = BLOCK4;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = NE;
						playerPosY -= playerSpeed;

					}
					if (map3[playerMapY - 1][playerMapX] == BLOCK5)
					{
						map3[5][27] = BLOCK5;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = NE;
						playerPosY -= playerSpeed;

					}
					if (map3[playerMapY - 1][playerMapX] == BLOCK6)
					{
						map3[6][27] = BLOCK6;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = NE;
						playerPosY -= playerSpeed;

					}
					if (map3[playerMapY - 1][playerMapX] == BLOCK7)
					{
						map3[7][27] = BLOCK7;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = NE;
						playerPosY -= playerSpeed;

					}
					if (map3[playerMapY - 1][playerMapX] == BLOCK8)
					{
						map3[8][27] = BLOCK8;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = NE;
						playerPosY -= playerSpeed;

					}
				}
				if (map3[playerMapY][playerMapX] == RA)
				{
					if (map3[playerMapY - 1][playerMapX] == YUKA)
					{
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = RA;
						if (map3[1][27] != BLOCK1 || map3[1][27] == BLOCK1)
						{
							if (map3[1][27] == BLOCK1 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK1;
								map3[1][27] = YUKA;
							}
						}
						if (map3[2][27] != BLOCK22 || map3[2][27] == BLOCK22)
						{
							if (map3[2][27] == BLOCK22 && map3[playerMapY][playerMapX] == map3[4][11])
							{
								map3[playerMapY][playerMapX] = BLOCK22;
								map3[2][27] = YUKA;
							}
						}
						if (map3[3][27] != BLOCK3 || map3[3][27] == BLOCK3)
						{
							if (map3[3][27] == BLOCK3 && map3[playerMapY][playerMapX] == map3[4][13])
							{
								map3[playerMapY][playerMapX] = BLOCK3;
								map3[3][27] = YUKA;
							}
						}
						if (map3[4][27] != BLOCK4 || map3[4][27] == BLOCK4)
						{
							if (map3[4][27] == BLOCK4 && map3[playerMapY][playerMapX] == map3[4][15])
							{
								map3[playerMapY][playerMapX] = BLOCK4;
								map3[4][27] = YUKA;
							}
						}
						if (map3[5][27] != BLOCK5 || map3[5][27] == BLOCK5)
						{
							if (map3[5][27] == BLOCK5 && map3[playerMapY][playerMapX] == map3[4][17])
							{
								map3[playerMapY][playerMapX] = BLOCK5;
								map3[5][27] = YUKA;
							}
						}
						if (map3[6][27] != BLOCK6 || map3[6][27] == BLOCK6)
						{

							if (map3[6][27] == BLOCK6 && map3[playerMapY][playerMapX] == /*6以降は後で*/map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK6;
								map3[6][27] = YUKA;
							}
						}
						if (map3[7][27] != BLOCK7 || map3[7][27] == BLOCK7)
						{
							if (map3[7][27] == BLOCK7 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK7;
								map3[7][27] = YUKA;
							}
						}
						if (map3[8][27] != BLOCK8 || map3[8][27] == BLOCK8)
						{
							if (map3[8][27] == BLOCK8 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK8;
								map3[8][27] = YUKA;
							}
						}
						playerPosY -= playerSpeed;
					}

					if (map3[playerMapY - 1][playerMapX] == BLOCK1)
					{
						map3[1][27] = BLOCK1;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = RA;
						playerPosY -= playerSpeed;

					}

					if (map3[playerMapY - 1][playerMapX] == BLOCK22)
					{
						map3[2][27] = BLOCK22;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = RA;
						playerPosY -= playerSpeed;

					}
					if (map3[playerMapY - 1][playerMapX] == BLOCK3)
					{
						map3[3][27] = BLOCK3;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = RA;
						playerPosY -= playerSpeed;

					}
					if (map3[playerMapY - 1][playerMapX] == BLOCK4)
					{
						map3[4][27] = BLOCK4;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = RA;
						playerPosY -= playerSpeed;

					}
					if (map3[playerMapY - 1][playerMapX] == BLOCK5)
					{
						map3[5][27] = BLOCK5;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = RA;
						playerPosY -= playerSpeed;

					}
					if (map3[playerMapY - 1][playerMapX] == BLOCK6)
					{
						map3[6][27] = BLOCK6;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = RA;
						playerPosY -= playerSpeed;

					}
					if (map3[playerMapY - 1][playerMapX] == BLOCK7)
					{
						map3[7][27] = BLOCK7;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = RA;
						playerPosY -= playerSpeed;

					}
					if (map3[playerMapY - 1][playerMapX] == BLOCK8)
					{
						map3[8][27] = BLOCK8;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = RA;
						playerPosY -= playerSpeed;

					}
				}
				if (map3[playerMapY][playerMapX] == HO)
				{
					if (map3[playerMapY - 1][playerMapX] == YUKA)
					{
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = HO;
						if (map3[1][27] != BLOCK1 || map3[1][27] == BLOCK1)
						{
							if (map3[1][27] == BLOCK1 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK1;
								map3[1][27] = YUKA;
							}
						}
						if (map3[2][27] != BLOCK22 || map3[2][27] == BLOCK22)
						{
							if (map3[2][27] == BLOCK22 && map3[playerMapY][playerMapX] == map3[4][11])
							{
								map3[playerMapY][playerMapX] = BLOCK22;
								map3[2][27] = YUKA;
							}
						}
						if (map3[3][27] != BLOCK3 || map3[3][27] == BLOCK3)
						{
							if (map3[3][27] == BLOCK3 && map3[playerMapY][playerMapX] == map3[4][13])
							{
								map3[playerMapY][playerMapX] = BLOCK3;
								map3[3][27] = YUKA;
							}
						}
						if (map3[4][27] != BLOCK4 || map3[4][27] == BLOCK4)
						{
							if (map3[4][27] == BLOCK4 && map3[playerMapY][playerMapX] == map3[4][15])
							{
								map3[playerMapY][playerMapX] = BLOCK4;
								map3[4][27] = YUKA;
							}
						}
						if (map3[5][27] != BLOCK5 || map3[5][27] == BLOCK5)
						{
							if (map3[5][27] == BLOCK5 && map3[playerMapY][playerMapX] == map3[4][17])
							{
								map3[playerMapY][playerMapX] = BLOCK5;
								map3[5][27] = YUKA;
							}
						}
						if (map3[6][27] != BLOCK6 || map3[6][27] == BLOCK6)
						{

							if (map3[6][27] == BLOCK6 && map3[playerMapY][playerMapX] == /*6以降は後で*/map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK6;
								map3[6][27] = YUKA;
							}
						}
						if (map3[7][27] != BLOCK7 || map3[7][27] == BLOCK7)
						{
							if (map3[7][27] == BLOCK7 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK7;
								map3[7][27] = YUKA;
							}
						}
						if (map3[8][27] != BLOCK8 || map3[8][27] == BLOCK8)
						{
							if (map3[8][27] == BLOCK8 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK8;
								map3[8][27] = YUKA;
							}
						}
						playerPosY -= playerSpeed;
					}

					if (map3[playerMapY - 1][playerMapX] == BLOCK1)
					{
						map3[1][27] = BLOCK1;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = HO;
						playerPosY -= playerSpeed;

					}

					if (map3[playerMapY - 1][playerMapX] == BLOCK22)
					{
						map3[2][27] = BLOCK22;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = HO;
						playerPosY -= playerSpeed;

					}
					if (map3[playerMapY - 1][playerMapX] == BLOCK3)
					{
						map3[3][27] = BLOCK3;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = HO;
						playerPosY -= playerSpeed;

					}
					if (map3[playerMapY - 1][playerMapX] == BLOCK4)
					{
						map3[4][27] = BLOCK4;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = HO;
						playerPosY -= playerSpeed;

					}
					if (map3[playerMapY - 1][playerMapX] == BLOCK5)
					{
						map3[5][27] = BLOCK5;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = HO;
						playerPosY -= playerSpeed;

					}
					if (map3[playerMapY - 1][playerMapX] == BLOCK6)
					{
						map3[6][27] = BLOCK6;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = HO;
						playerPosY -= playerSpeed;

					}
					if (map3[playerMapY - 1][playerMapX] == BLOCK7)
					{
						map3[7][27] = BLOCK7;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = HO;
						playerPosY -= playerSpeed;

					}
					if (map3[playerMapY - 1][playerMapX] == BLOCK8)
					{
						map3[8][27] = BLOCK8;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = HO;
						playerPosY -= playerSpeed;

					}
				}
				if (map3[playerMapY][playerMapX] == ZE)
				{
					if (map3[playerMapY - 1][playerMapX] == YUKA)
					{
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = ZE;
						if (map3[1][27] != BLOCK1 || map3[1][27] == BLOCK1)
						{
							if (map3[1][27] == BLOCK1 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK1;
								map3[1][27] = YUKA;
							}
						}
						if (map3[2][27] != BLOCK22 || map3[2][27] == BLOCK22)
						{
							if (map3[2][27] == BLOCK22 && map3[playerMapY][playerMapX] == map3[4][11])
							{
								map3[playerMapY][playerMapX] = BLOCK22;
								map3[2][27] = YUKA;
							}
						}
						if (map3[3][27] != BLOCK3 || map3[3][27] == BLOCK3)
						{
							if (map3[3][27] == BLOCK3 && map3[playerMapY][playerMapX] == map3[4][13])
							{
								map3[playerMapY][playerMapX] = BLOCK3;
								map3[3][27] = YUKA;
							}
						}
						if (map3[4][27] != BLOCK4 || map3[4][27] == BLOCK4)
						{
							if (map3[4][27] == BLOCK4 && map3[playerMapY][playerMapX] == map3[4][15])
							{
								map3[playerMapY][playerMapX] = BLOCK4;
								map3[4][27] = YUKA;
							}
						}
						if (map3[5][27] != BLOCK5 || map3[5][27] == BLOCK5)
						{
							if (map3[5][27] == BLOCK5 && map3[playerMapY][playerMapX] == map3[4][17])
							{
								map3[playerMapY][playerMapX] = BLOCK5;
								map3[5][27] = YUKA;
							}
						}
						if (map3[6][27] != BLOCK6 || map3[6][27] == BLOCK6)
						{

							if (map3[6][27] == BLOCK6 && map3[playerMapY][playerMapX] == /*6以降は後で*/map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK6;
								map3[6][27] = YUKA;
							}
						}
						if (map3[7][27] != BLOCK7 || map3[7][27] == BLOCK7)
						{
							if (map3[7][27] == BLOCK7 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK7;
								map3[7][27] = YUKA;
							}
						}
						if (map3[8][27] != BLOCK8 || map3[8][27] == BLOCK8)
						{
							if (map3[8][27] == BLOCK8 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK8;
								map3[8][27] = YUKA;
							}
						}
						playerPosY -= playerSpeed;
					}

					if (map3[playerMapY - 1][playerMapX] == BLOCK1)
					{
						map3[1][27] = BLOCK1;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = ZE;
						playerPosY -= playerSpeed;

					}

					if (map3[playerMapY - 1][playerMapX] == BLOCK22)
					{
						map3[2][27] = BLOCK22;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = ZE;
						playerPosY -= playerSpeed;

					}
					if (map3[playerMapY - 1][playerMapX] == BLOCK3)
					{
						map3[3][27] = BLOCK3;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = ZE;
						playerPosY -= playerSpeed;

					}
					if (map3[playerMapY - 1][playerMapX] == BLOCK4)
					{
						map3[4][27] = BLOCK4;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = ZE;
						playerPosY -= playerSpeed;

					}
					if (map3[playerMapY - 1][playerMapX] == BLOCK5)
					{
						map3[5][27] = BLOCK5;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = ZE;
						playerPosY -= playerSpeed;

					}
					if (map3[playerMapY - 1][playerMapX] == BLOCK6)
					{
						map3[6][27] = BLOCK6;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = ZE;
						playerPosY -= playerSpeed;

					}
					if (map3[playerMapY - 1][playerMapX] == BLOCK7)
					{
						map3[7][27] = BLOCK7;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = ZE;
						playerPosY -= playerSpeed;

					}
					if (map3[playerMapY - 1][playerMapX] == BLOCK8)
					{
						map3[8][27] = BLOCK8;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = ZE;
						playerPosY -= playerSpeed;

					}
				}
				if (map3[playerMapY][playerMapX] == RU)
				{
					if (map3[playerMapY - 1][playerMapX] == YUKA)
					{
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = RU;
						if (map3[1][27] != BLOCK1 || map3[1][27] == BLOCK1)
						{
							if (map3[1][27] == BLOCK1 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK1;
								map3[1][27] = YUKA;
							}
						}
						if (map3[2][27] != BLOCK22 || map3[2][27] == BLOCK22)
						{
							if (map3[2][27] == BLOCK22 && map3[playerMapY][playerMapX] == map3[4][11])
							{
								map3[playerMapY][playerMapX] = BLOCK22;
								map3[2][27] = YUKA;
							}
						}
						if (map3[3][27] != BLOCK3 || map3[3][27] == BLOCK3)
						{
							if (map3[3][27] == BLOCK3 && map3[playerMapY][playerMapX] == map3[4][13])
							{
								map3[playerMapY][playerMapX] = BLOCK3;
								map3[3][27] = YUKA;
							}
						}
						if (map3[4][27] != BLOCK4 || map3[4][27] == BLOCK4)
						{
							if (map3[4][27] == BLOCK4 && map3[playerMapY][playerMapX] == map3[4][15])
							{
								map3[playerMapY][playerMapX] = BLOCK4;
								map3[4][27] = YUKA;
							}
						}
						if (map3[5][27] != BLOCK5 || map3[5][27] == BLOCK5)
						{
							if (map3[5][27] == BLOCK5 && map3[playerMapY][playerMapX] == map3[4][17])
							{
								map3[playerMapY][playerMapX] = BLOCK5;
								map3[5][27] = YUKA;
							}
						}
						if (map3[6][27] != BLOCK6 || map3[6][27] == BLOCK6)
						{

							if (map3[6][27] == BLOCK6 && map3[playerMapY][playerMapX] == /*6以降は後で*/map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK6;
								map3[6][27] = YUKA;
							}
						}
						if (map3[7][27] != BLOCK7 || map3[7][27] == BLOCK7)
						{
							if (map3[7][27] == BLOCK7 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK7;
								map3[7][27] = YUKA;
							}
						}
						if (map3[8][27] != BLOCK8 || map3[8][27] == BLOCK8)
						{
							if (map3[8][27] == BLOCK8 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK8;
								map3[8][27] = YUKA;
							}
						}
						playerPosY -= playerSpeed;
					}

					if (map3[playerMapY - 1][playerMapX] == BLOCK1)
					{
						map3[1][27] = BLOCK1;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = RU;
						playerPosY -= playerSpeed;

					}

					if (map3[playerMapY - 1][playerMapX] == BLOCK22)
					{
						map3[2][27] = BLOCK22;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = RU;
						playerPosY -= playerSpeed;

					}
					if (map3[playerMapY - 1][playerMapX] == BLOCK3)
					{
						map3[3][27] = BLOCK3;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = RU;
						playerPosY -= playerSpeed;

					}
					if (map3[playerMapY - 1][playerMapX] == BLOCK4)
					{
						map3[4][27] = BLOCK4;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = RU;
						playerPosY -= playerSpeed;

					}
					if (map3[playerMapY - 1][playerMapX] == BLOCK5)
					{
						map3[5][27] = BLOCK5;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = RU;
						playerPosY -= playerSpeed;

					}
					if (map3[playerMapY - 1][playerMapX] == BLOCK6)
					{
						map3[6][27] = BLOCK6;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = RU;
						playerPosY -= playerSpeed;

					}
					if (map3[playerMapY - 1][playerMapX] == BLOCK7)
					{
						map3[7][27] = BLOCK7;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = RU;
						playerPosY -= playerSpeed;

					}
					if (map3[playerMapY - 1][playerMapX] == BLOCK8)
					{
						map3[8][27] = BLOCK8;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = RU;
						playerPosY -= playerSpeed;

					}
				}
				if (map3[playerMapY][playerMapX] == YU)
				{
					if (map3[playerMapY - 1][playerMapX] == YUKA)
					{
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = YU;
						if (map3[1][27] != BLOCK1 || map3[1][27] == BLOCK1)
						{
							if (map3[1][27] == BLOCK1 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK1;
								map3[1][27] = YUKA;
							}
						}
						if (map3[2][27] != BLOCK22 || map3[2][27] == BLOCK22)
						{
							if (map3[2][27] == BLOCK22 && map3[playerMapY][playerMapX] == map3[4][11])
							{
								map3[playerMapY][playerMapX] = BLOCK22;
								map3[2][27] = YUKA;
							}
						}
						if (map3[3][27] != BLOCK3 || map3[3][27] == BLOCK3)
						{
							if (map3[3][27] == BLOCK3 && map3[playerMapY][playerMapX] == map3[4][13])
							{
								map3[playerMapY][playerMapX] = BLOCK3;
								map3[3][27] = YUKA;
							}
						}
						if (map3[4][27] != BLOCK4 || map3[4][27] == BLOCK4)
						{
							if (map3[4][27] == BLOCK4 && map3[playerMapY][playerMapX] == map3[4][15])
							{
								map3[playerMapY][playerMapX] = BLOCK4;
								map3[4][27] = YUKA;
							}
						}
						if (map3[5][27] != BLOCK5 || map3[5][27] == BLOCK5)
						{
							if (map3[5][27] == BLOCK5 && map3[playerMapY][playerMapX] == map3[4][17])
							{
								map3[playerMapY][playerMapX] = BLOCK5;
								map3[5][27] = YUKA;
							}
						}
						if (map3[6][27] != BLOCK6 || map3[6][27] == BLOCK6)
						{

							if (map3[6][27] == BLOCK6 && map3[playerMapY][playerMapX] == /*6以降は後で*/map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK6;
								map3[6][27] = YUKA;
							}
						}
						if (map3[7][27] != BLOCK7 || map3[7][27] == BLOCK7)
						{
							if (map3[7][27] == BLOCK7 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK7;
								map3[7][27] = YUKA;
							}
						}
						if (map3[8][27] != BLOCK8 || map3[8][27] == BLOCK8)
						{
							if (map3[8][27] == BLOCK8 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK8;
								map3[8][27] = YUKA;
							}
						}
						playerPosY -= playerSpeed;
					}

					if (map3[playerMapY - 1][playerMapX] == BLOCK1)
					{
						map3[1][27] = BLOCK1;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = YU;
						playerPosY -= playerSpeed;

					}

					if (map3[playerMapY - 1][playerMapX] == BLOCK22)
					{
						map3[2][27] = BLOCK22;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = YU;
						playerPosY -= playerSpeed;

					}
					if (map3[playerMapY - 1][playerMapX] == BLOCK3)
					{
						map3[3][27] = BLOCK3;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = YU;
						playerPosY -= playerSpeed;

					}
					if (map3[playerMapY - 1][playerMapX] == BLOCK4)
					{
						map3[4][27] = BLOCK4;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = YU;
						playerPosY -= playerSpeed;

					}
					if (map3[playerMapY - 1][playerMapX] == BLOCK5)
					{
						map3[5][27] = BLOCK5;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = YU;
						playerPosY -= playerSpeed;

					}
					if (map3[playerMapY - 1][playerMapX] == BLOCK6)
					{
						map3[6][27] = BLOCK6;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = YU;
						playerPosY -= playerSpeed;

					}
					if (map3[playerMapY - 1][playerMapX] == BLOCK7)
					{
						map3[7][27] = BLOCK7;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = YU;
						playerPosY -= playerSpeed;

					}
					if (map3[playerMapY - 1][playerMapX] == BLOCK8)
					{
						map3[8][27] = BLOCK8;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = YU;
						playerPosY -= playerSpeed;

					}
				}
				if (map3[playerMapY][playerMapX] == DO)
				{
					if (map3[playerMapY - 1][playerMapX] == YUKA)
					{
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = DO;
						if (map3[1][27] != BLOCK1 || map3[1][27] == BLOCK1)
						{
							if (map3[1][27] == BLOCK1 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK1;
								map3[1][27] = YUKA;
							}
						}
						if (map3[2][27] != BLOCK22 || map3[2][27] == BLOCK22)
						{
							if (map3[2][27] == BLOCK22 && map3[playerMapY][playerMapX] == map3[4][11])
							{
								map3[playerMapY][playerMapX] = BLOCK22;
								map3[2][27] = YUKA;
							}
						}
						if (map3[3][27] != BLOCK3 || map3[3][27] == BLOCK3)
						{
							if (map3[3][27] == BLOCK3 && map3[playerMapY][playerMapX] == map3[4][13])
							{
								map3[playerMapY][playerMapX] = BLOCK3;
								map3[3][27] = YUKA;
							}
						}
						if (map3[4][27] != BLOCK4 || map3[4][27] == BLOCK4)
						{
							if (map3[4][27] == BLOCK4 && map3[playerMapY][playerMapX] == map3[4][15])
							{
								map3[playerMapY][playerMapX] = BLOCK4;
								map3[4][27] = YUKA;
							}
						}
						if (map3[5][27] != BLOCK5 || map3[5][27] == BLOCK5)
						{
							if (map3[5][27] == BLOCK5 && map3[playerMapY][playerMapX] == map3[4][17])
							{
								map3[playerMapY][playerMapX] = BLOCK5;
								map3[5][27] = YUKA;
							}
						}
						if (map3[6][27] != BLOCK6 || map3[6][27] == BLOCK6)
						{

							if (map3[6][27] == BLOCK6 && map3[playerMapY][playerMapX] == /*6以降は後で*/map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK6;
								map3[6][27] = YUKA;
							}
						}
						if (map3[7][27] != BLOCK7 || map3[7][27] == BLOCK7)
						{
							if (map3[7][27] == BLOCK7 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK7;
								map3[7][27] = YUKA;
							}
						}
						if (map3[8][27] != BLOCK8 || map3[8][27] == BLOCK8)
						{
							if (map3[8][27] == BLOCK8 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK8;
								map3[8][27] = YUKA;
							}
						}
						playerPosY -= playerSpeed;
					}

					if (map3[playerMapY - 1][playerMapX] == BLOCK1)
					{
						map3[1][27] = BLOCK1;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = DO;
						playerPosY -= playerSpeed;

					}

					if (map3[playerMapY - 1][playerMapX] == BLOCK22)
					{
						map3[2][27] = BLOCK22;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = DO;
						playerPosY -= playerSpeed;

					}
					if (map3[playerMapY - 1][playerMapX] == BLOCK3)
					{
						map3[3][27] = BLOCK3;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = DO;
						playerPosY -= playerSpeed;

					}
					if (map3[playerMapY - 1][playerMapX] == BLOCK4)
					{
						map3[4][27] = BLOCK4;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = DO;
						playerPosY -= playerSpeed;

					}
					if (map3[playerMapY - 1][playerMapX] == BLOCK5)
					{
						map3[5][27] = BLOCK5;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = DO;
						playerPosY -= playerSpeed;

					}
					if (map3[playerMapY - 1][playerMapX] == BLOCK6)
					{
						map3[6][27] = BLOCK6;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = DO;
						playerPosY -= playerSpeed;

					}
					if (map3[playerMapY - 1][playerMapX] == BLOCK7)
					{
						map3[7][27] = BLOCK7;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = DO;
						playerPosY -= playerSpeed;

					}
					if (map3[playerMapY - 1][playerMapX] == BLOCK8)
					{
						map3[8][27] = BLOCK8;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = DO;
						playerPosY -= playerSpeed;

					}
				}
				if (map3[playerMapY][playerMapX] == GO)
				{
					if (map3[playerMapY - 1][playerMapX] == YUKA)
					{
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = GO;
						if (map3[1][27] != BLOCK1 || map3[1][27] == BLOCK1)
						{
							if (map3[1][27] == BLOCK1 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK1;
								map3[1][27] = YUKA;
							}
						}
						if (map3[2][27] != BLOCK22 || map3[2][27] == BLOCK22)
						{
							if (map3[2][27] == BLOCK22 && map3[playerMapY][playerMapX] == map3[4][11])
							{
								map3[playerMapY][playerMapX] = BLOCK22;
								map3[2][27] = YUKA;
							}
						}
						if (map3[3][27] != BLOCK3 || map3[3][27] == BLOCK3)
						{
							if (map3[3][27] == BLOCK3 && map3[playerMapY][playerMapX] == map3[4][13])
							{
								map3[playerMapY][playerMapX] = BLOCK3;
								map3[3][27] = YUKA;
							}
						}
						if (map3[4][27] != BLOCK4 || map3[4][27] == BLOCK4)
						{
							if (map3[4][27] == BLOCK4 && map3[playerMapY][playerMapX] == map3[4][15])
							{
								map3[playerMapY][playerMapX] = BLOCK4;
								map3[4][27] = YUKA;
							}
						}
						if (map3[5][27] != BLOCK5 || map3[5][27] == BLOCK5)
						{
							if (map3[5][27] == BLOCK5 && map3[playerMapY][playerMapX] == map3[4][17])
							{
								map3[playerMapY][playerMapX] = BLOCK5;
								map3[5][27] = YUKA;
							}
						}
						if (map3[6][27] != BLOCK6 || map3[6][27] == BLOCK6)
						{

							if (map3[6][27] == BLOCK6 && map3[playerMapY][playerMapX] == /*6以降は後で*/map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK6;
								map3[6][27] = YUKA;
							}
						}
						if (map3[7][27] != BLOCK7 || map3[7][27] == BLOCK7)
						{
							if (map3[7][27] == BLOCK7 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK7;
								map3[7][27] = YUKA;
							}
						}
						if (map3[8][27] != BLOCK8 || map3[8][27] == BLOCK8)
						{
							if (map3[8][27] == BLOCK8 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK8;
								map3[8][27] = YUKA;
							}
						}
						playerPosY -= playerSpeed;
					}

					if (map3[playerMapY - 1][playerMapX] == BLOCK1)
					{
						map3[1][27] = BLOCK1;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = GO;
						playerPosY -= playerSpeed;

					}

					if (map3[playerMapY - 1][playerMapX] == BLOCK22)
					{
						map3[2][27] = BLOCK22;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = GO;
						playerPosY -= playerSpeed;

					}
					if (map3[playerMapY - 1][playerMapX] == BLOCK3)
					{
						map3[3][27] = BLOCK3;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = GO;
						playerPosY -= playerSpeed;

					}
					if (map3[playerMapY - 1][playerMapX] == BLOCK4)
					{
						map3[4][27] = BLOCK4;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = GO;
						playerPosY -= playerSpeed;

					}
					if (map3[playerMapY - 1][playerMapX] == BLOCK5)
					{
						map3[5][27] = BLOCK5;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = GO;
						playerPosY -= playerSpeed;

					}
					if (map3[playerMapY - 1][playerMapX] == BLOCK6)
					{
						map3[6][27] = BLOCK6;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = GO;
						playerPosY -= playerSpeed;

					}
					if (map3[playerMapY - 1][playerMapX] == BLOCK7)
					{
						map3[7][27] = BLOCK7;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = GO;
						playerPosY -= playerSpeed;

					}
					if (map3[playerMapY - 1][playerMapX] == BLOCK8)
					{
						map3[8][27] = BLOCK8;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = GO;
						playerPosY -= playerSpeed;

					}
				}
				if (map3[playerMapY][playerMapX] == ZE)
				{
					if (map3[playerMapY - 1][playerMapX] == YUKA)
					{
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = ZE;
						if (map3[1][27] != BLOCK1 || map3[1][27] == BLOCK1)
						{
							if (map3[1][27] == BLOCK1 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK1;
								map3[1][27] = YUKA;
							}
						}
						if (map3[2][27] != BLOCK22 || map3[2][27] == BLOCK22)
						{
							if (map3[2][27] == BLOCK22 && map3[playerMapY][playerMapX] == map3[4][11])
							{
								map3[playerMapY][playerMapX] = BLOCK22;
								map3[2][27] = YUKA;
							}
						}
						if (map3[3][27] != BLOCK3 || map3[3][27] == BLOCK3)
						{
							if (map3[3][27] == BLOCK3 && map3[playerMapY][playerMapX] == map3[4][13])
							{
								map3[playerMapY][playerMapX] = BLOCK3;
								map3[3][27] = YUKA;
							}
						}
						if (map3[4][27] != BLOCK4 || map3[4][27] == BLOCK4)
						{
							if (map3[4][27] == BLOCK4 && map3[playerMapY][playerMapX] == map3[4][15])
							{
								map3[playerMapY][playerMapX] = BLOCK4;
								map3[4][27] = YUKA;
							}
						}
						if (map3[5][27] != BLOCK5 || map3[5][27] == BLOCK5)
						{
							if (map3[5][27] == BLOCK5 && map3[playerMapY][playerMapX] == map3[4][17])
							{
								map3[playerMapY][playerMapX] = BLOCK5;
								map3[5][27] = YUKA;
							}
						}
						if (map3[6][27] != BLOCK6 || map3[6][27] == BLOCK6)
						{

							if (map3[6][27] == BLOCK6 && map3[playerMapY][playerMapX] == /*6以降は後で*/map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK6;
								map3[6][27] = YUKA;
							}
						}
						if (map3[7][27] != BLOCK7 || map3[7][27] == BLOCK7)
						{
							if (map3[7][27] == BLOCK7 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK7;
								map3[7][27] = YUKA;
							}
						}
						if (map3[8][27] != BLOCK8 || map3[8][27] == BLOCK8)
						{
							if (map3[8][27] == BLOCK8 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK8;
								map3[8][27] = YUKA;
							}
						}
						playerPosY -= playerSpeed;
					}
					if (map3[playerMapY - 1][playerMapX] == BLOCK1)
					{
						map3[1][27] = BLOCK1;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = ZE;
						playerPosY -= playerSpeed;

					}

					if (map3[playerMapY - 1][playerMapX] == BLOCK22)
					{
						map3[2][27] = BLOCK22;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = ZE;
						playerPosY -= playerSpeed;

					}
					if (map3[playerMapY - 1][playerMapX] == BLOCK3)
					{
						map3[3][27] = BLOCK3;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = ZE;
						playerPosY -= playerSpeed;

					}
					if (map3[playerMapY - 1][playerMapX] == BLOCK4)
					{
						map3[4][27] = BLOCK4;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = ZE;
						playerPosY -= playerSpeed;

					}
					if (map3[playerMapY - 1][playerMapX] == BLOCK5)
					{
						map3[5][27] = BLOCK5;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = ZE;
						playerPosY -= playerSpeed;

					}
					if (map3[playerMapY - 1][playerMapX] == BLOCK6)
					{
						map3[6][27] = BLOCK6;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = ZE;
						playerPosY -= playerSpeed;

					}
					if (map3[playerMapY - 1][playerMapX] == BLOCK7)
					{
						map3[7][27] = BLOCK7;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = ZE;
						playerPosY -= playerSpeed;

					}
					if (map3[playerMapY - 1][playerMapX] == BLOCK8)
					{
						map3[8][27] = BLOCK8;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY - 1][playerMapX] = ZE;
						playerPosY -= playerSpeed;

					}
				}
			}

			if (keys[DIK_A] && preKeys[DIK_A] == 0 || keys[DIK_LEFT] && preKeys[DIK_LEFT] == 0)
			{
				playerTmpX = playerPosX - playerSpeed;
				playerMapX = playerTmpX / KBlockSize;
				//何もないから実際に進ませる
				if (map3[playerMapY][playerMapX] == YUKA)
				{
					playerPosX -= playerSpeed;
				}
				if (map3[playerMapY][playerMapX] == BLOCK1)
				{
					playerPosX -= playerSpeed;
				}
				if (map3[playerMapY][playerMapX] == GOAL)
				{
					playerPosX -= playerSpeed;
				}
				if (map3[playerMapY][playerMapX] == THORN)
				{
					playerPosX -= playerSpeed;
				}

				if (map3[playerMapY][playerMapX] == A)
				{
					if (map3[playerMapY][playerMapX - 1] == YUKA)
					{
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX - 1] = A;
						if (map3[1][27] != BLOCK1 || map3[1][27] == BLOCK1)
						{
							if (map3[1][27] == BLOCK1 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK1;
								map3[1][27] = YUKA;
							}
						}
						if (map3[2][27] != BLOCK22 || map3[2][27] == BLOCK22)
						{
							if (map3[2][27] == BLOCK22 && map3[playerMapY][playerMapX] == map3[4][11])
							{
								map3[playerMapY][playerMapX] = BLOCK22;
								map3[2][27] = YUKA;
							}
						}
						if (map3[3][27] != BLOCK3 || map3[3][27] == BLOCK3)
						{
							if (map3[3][27] == BLOCK3 && map3[playerMapY][playerMapX] == map3[4][13])
							{
								map3[playerMapY][playerMapX] = BLOCK3;
								map3[3][27] = YUKA;
							}
						}
						if (map3[4][27] != BLOCK4 || map3[4][27] == BLOCK4)
						{
							if (map3[4][27] == BLOCK4 && map3[playerMapY][playerMapX] == map3[4][15])
							{
								map3[playerMapY][playerMapX] = BLOCK4;
								map3[4][27] = YUKA;
							}
						}
						if (map3[5][27] != BLOCK5 || map3[5][27] == BLOCK5)
						{
							if (map3[5][27] == BLOCK5 && map3[playerMapY][playerMapX] == map3[4][17])
							{
								map3[playerMapY][playerMapX] = BLOCK5;
								map3[5][27] = YUKA;
							}
						}
						if (map3[6][27] != BLOCK6 || map3[6][27] == BLOCK6)
						{

							if (map3[6][27] == BLOCK6 && map3[playerMapY][playerMapX] == /*6以降は後で*/map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK6;
								map3[6][27] = YUKA;
							}
						}
						if (map3[7][27] != BLOCK7 || map3[7][27] == BLOCK7)
						{
							if (map3[7][27] == BLOCK7 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK7;
								map3[7][27] = YUKA;
							}
						}
						if (map3[8][27] != BLOCK8 || map3[8][27] == BLOCK8)
						{
							if (map3[8][27] == BLOCK8 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK8;
								map3[8][27] = YUKA;
							}
						}

						playerPosX -= playerSpeed;
					}
				}


			}

			// 1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111
			// ここから直して
			if (map3[playerMapY][playerMapX] == KE)
			{
				if (map3[playerMapY][playerMapX - 1] == YUKA)
				{
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = KE; //ここをKEに変える　したも同じ
					if (map3[1][27] != BLOCK1 || map3[1][27] == BLOCK1)
					{
						if (map3[1][27] == BLOCK1 && map3[playerMapY][playerMapX] == map3[4][9])
						{
							map3[playerMapY][playerMapX] = BLOCK1;
							map3[1][27] = YUKA;
						}
					}
					if (map3[2][27] != BLOCK22 || map3[2][27] == BLOCK22)
					{
						if (map3[2][27] == BLOCK22 && map3[playerMapY][playerMapX] == map3[4][11])
						{
							map3[playerMapY][playerMapX] = BLOCK22;
							map3[2][27] = YUKA;
						}
					}
					if (map3[3][27] != BLOCK3 || map3[3][27] == BLOCK3)
					{
						if (map3[3][27] == BLOCK3 && map3[playerMapY][playerMapX] == map3[4][13])
						{
							map3[playerMapY][playerMapX] = BLOCK3;
							map3[3][27] = YUKA;
						}
					}
					if (map3[4][27] != BLOCK4 || map3[4][27] == BLOCK4)
					{
						if (map3[4][27] == BLOCK4 && map3[playerMapY][playerMapX] == map3[4][15])
						{
							map3[playerMapY][playerMapX] = BLOCK4;
							map3[4][27] = YUKA;
						}
					}
					if (map3[5][27] != BLOCK5 || map3[5][27] == BLOCK5)
					{
						if (map3[5][27] == BLOCK5 && map3[playerMapY][playerMapX] == map3[4][17])
						{
							map3[playerMapY][playerMapX] = BLOCK5;
							map3[5][27] = YUKA;
						}
					}
					if (map3[6][27] != BLOCK6 || map3[6][27] == BLOCK6)
					{

						if (map3[6][27] == BLOCK6 && map3[playerMapY][playerMapX] == /*6以降は後で*/map3[4][9])
						{
							map3[playerMapY][playerMapX] = BLOCK6;
							map3[6][27] = YUKA;
						}
					}
					if (map3[7][27] != BLOCK7 || map3[7][27] == BLOCK7)
					{
						if (map3[7][27] == BLOCK7 && map3[playerMapY][playerMapX] == map3[4][9])
						{
							map3[playerMapY][playerMapX] = BLOCK7;
							map3[7][27] = YUKA;
						}
					}
					if (map3[8][27] != BLOCK8 || map3[8][27] == BLOCK8)
					{
						if (map3[8][27] == BLOCK8 && map3[playerMapY][playerMapX] == map3[4][9])
						{
							map3[playerMapY][playerMapX] = BLOCK8;
							map3[8][27] = YUKA;
						}
					}

					playerPosX -= playerSpeed;
				}

				if (map3[playerMapY][playerMapX - 1] == BLOCK1)
				{
					map3[1][27] = BLOCK1;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = KE;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK22)
				{
					map3[2][27] = BLOCK22;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = KE;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK3)
				{
					map3[3][27] = BLOCK3;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = KE;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK4)
				{
					map3[4][27] = BLOCK4;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = KE;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK5)
				{
					map3[5][27] = BLOCK5;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = KE;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK6)
				{
					map3[6][27] = BLOCK6;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = KE;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK7)
				{
					map3[7][27] = BLOCK7;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = KE;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK8)
				{
					map3[8][27] = BLOCK8;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = KE;
					playerPosX -= playerSpeed;

				}
			}
			if (map3[playerMapY][playerMapX] == E)
			{
				if (map3[playerMapY][playerMapX - 1] == YUKA)
				{
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = E;
					if (map3[1][27] != BLOCK1 || map3[1][27] == BLOCK1)
					{
						if (map3[1][27] == BLOCK1 && map3[playerMapY][playerMapX] == map3[4][9])
						{
							map3[playerMapY][playerMapX] = BLOCK1;
							map3[1][27] = YUKA;
						}
					}
					if (map3[2][27] != BLOCK22 || map3[2][27] == BLOCK22)
					{
						if (map3[2][27] == BLOCK22 && map3[playerMapY][playerMapX] == map3[4][11])
						{
							map3[playerMapY][playerMapX] = BLOCK22;
							map3[2][27] = YUKA;
						}
					}
					if (map3[3][27] != BLOCK3 || map3[3][27] == BLOCK3)
					{
						if (map3[3][27] == BLOCK3 && map3[playerMapY][playerMapX] == map3[4][13])
						{
							map3[playerMapY][playerMapX] = BLOCK3;
							map3[3][27] = YUKA;
						}
					}
					if (map3[4][27] != BLOCK4 || map3[4][27] == BLOCK4)
					{
						if (map3[4][27] == BLOCK4 && map3[playerMapY][playerMapX] == map3[4][15])
						{
							map3[playerMapY][playerMapX] = BLOCK4;
							map3[4][27] = YUKA;
						}
					}
					if (map3[5][27] != BLOCK5 || map3[5][27] == BLOCK5)
					{
						if (map3[5][27] == BLOCK5 && map3[playerMapY][playerMapX] == map3[4][17])
						{
							map3[playerMapY][playerMapX] = BLOCK5;
							map3[5][27] = YUKA;
						}
					}
					if (map3[6][27] != BLOCK6 || map3[6][27] == BLOCK6)
					{

						if (map3[6][27] == BLOCK6 && map3[playerMapY][playerMapX] == /*6以降は後で*/map3[4][9])
						{
							map3[playerMapY][playerMapX] = BLOCK6;
							map3[6][27] = YUKA;
						}
					}
					if (map3[7][27] != BLOCK7 || map3[7][27] == BLOCK7)
					{
						if (map3[7][27] == BLOCK7 && map3[playerMapY][playerMapX] == map3[4][9])
						{
							map3[playerMapY][playerMapX] = BLOCK7;
							map3[7][27] = YUKA;
						}
					}
					if (map3[8][27] != BLOCK8 || map3[8][27] == BLOCK8)
					{
						if (map3[8][27] == BLOCK8 && map3[playerMapY][playerMapX] == map3[4][9])
						{
							map3[playerMapY][playerMapX] = BLOCK8;
							map3[8][27] = YUKA;
						}
					}

					playerPosX -= playerSpeed;
				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK1)
				{
					map3[1][27] = BLOCK1;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = E;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK22)
				{
					map3[2][27] = BLOCK22;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = E;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK3)
				{
					map3[3][27] = BLOCK3;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = E;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK4)
				{
					map3[4][27] = BLOCK4;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = E;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK5)
				{
					map3[5][27] = BLOCK5;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = E;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK6)
				{
					map3[6][27] = BLOCK6;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = E;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK7)
				{
					map3[7][27] = BLOCK7;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = E;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK8)
				{
					map3[8][27] = BLOCK8;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = E;
					playerPosX -= playerSpeed;

				}
			}
			if (map3[playerMapY][playerMapX] == KA)
			{
				if (map3[playerMapY][playerMapX - 1] == YUKA)
				{
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = KA;
					if (map3[1][27] != BLOCK1 || map3[1][27] == BLOCK1)
					{
						if (map3[1][27] == BLOCK1 && map3[playerMapY][playerMapX] == map3[4][9])
						{
							map3[playerMapY][playerMapX] = BLOCK1;
							map3[1][27] = YUKA;
						}
					}
					if (map3[2][27] != BLOCK22 || map3[2][27] == BLOCK22)
					{
						if (map3[2][27] == BLOCK22 && map3[playerMapY][playerMapX] == map3[4][11])
						{
							map3[playerMapY][playerMapX] = BLOCK22;
							map3[2][27] = YUKA;
						}
					}
					if (map3[3][27] != BLOCK3 || map3[3][27] == BLOCK3)
					{
						if (map3[3][27] == BLOCK3 && map3[playerMapY][playerMapX] == map3[4][13])
						{
							map3[playerMapY][playerMapX] = BLOCK3;
							map3[3][27] = YUKA;
						}
					}
					if (map3[4][27] != BLOCK4 || map3[4][27] == BLOCK4)
					{
						if (map3[4][27] == BLOCK4 && map3[playerMapY][playerMapX] == map3[4][15])
						{
							map3[playerMapY][playerMapX] = BLOCK4;
							map3[4][27] = YUKA;
						}
					}
					if (map3[5][27] != BLOCK5 || map3[5][27] == BLOCK5)
					{
						if (map3[5][27] == BLOCK5 && map3[playerMapY][playerMapX] == map3[4][17])
						{
							map3[playerMapY][playerMapX] = BLOCK5;
							map3[5][27] = YUKA;
						}
					}
					if (map3[6][27] != BLOCK6 || map3[6][27] == BLOCK6)
					{

						if (map3[6][27] == BLOCK6 && map3[playerMapY][playerMapX] == /*6以降は後で*/map3[4][9])
						{
							map3[playerMapY][playerMapX] = BLOCK6;
							map3[6][27] = YUKA;
						}
					}
					if (map3[7][27] != BLOCK7 || map3[7][27] == BLOCK7)
					{
						if (map3[7][27] == BLOCK7 && map3[playerMapY][playerMapX] == map3[4][9])
						{
							map3[playerMapY][playerMapX] = BLOCK7;
							map3[7][27] = YUKA;
						}
					}
					if (map3[8][27] != BLOCK8 || map3[8][27] == BLOCK8)
					{
						if (map3[8][27] == BLOCK8 && map3[playerMapY][playerMapX] == map3[4][9])
						{
							map3[playerMapY][playerMapX] = BLOCK8;
							map3[8][27] = YUKA;
						}
					}

					playerPosX -= playerSpeed;
				}

				if (map3[playerMapY][playerMapX - 1] == BLOCK1)
				{
					map3[1][27] = BLOCK1;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = KA;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK22)
				{
					map3[2][27] = BLOCK22;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = KA;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK3)
				{
					map3[3][27] = BLOCK3;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = KA;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK4)
				{
					map3[4][27] = BLOCK4;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = KA;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK5)
				{
					map3[5][27] = BLOCK5;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = KA;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK6)
				{
					map3[6][27] = BLOCK6;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = KA;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK7)
				{
					map3[7][27] = BLOCK7;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = KA;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK8)
				{
					map3[8][27] = BLOCK8;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = KA;
					playerPosX -= playerSpeed;

				}
			}
			if (map3[playerMapY][playerMapX] == KU)
			{
				if (map3[playerMapY][playerMapX - 1] == YUKA)
				{
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = KU;
					if (map3[1][27] != BLOCK1 || map3[1][27] == BLOCK1)
					{
						if (map3[1][27] == BLOCK1 && map3[playerMapY][playerMapX] == map3[4][9])
						{
							map3[playerMapY][playerMapX] = BLOCK1;
							map3[1][27] = YUKA;
						}
					}
					if (map3[2][27] != BLOCK22 || map3[2][27] == BLOCK22)
					{
						if (map3[2][27] == BLOCK22 && map3[playerMapY][playerMapX] == map3[4][11])
						{
							map3[playerMapY][playerMapX] = BLOCK22;
							map3[2][27] = YUKA;
						}
					}
					if (map3[3][27] != BLOCK3 || map3[3][27] == BLOCK3)
					{
						if (map3[3][27] == BLOCK3 && map3[playerMapY][playerMapX] == map3[4][13])
						{
							map3[playerMapY][playerMapX] = BLOCK3;
							map3[3][27] = YUKA;
						}
					}
					if (map3[4][27] != BLOCK4 || map3[4][27] == BLOCK4)
					{
						if (map3[4][27] == BLOCK4 && map3[playerMapY][playerMapX] == map3[4][15])
						{
							map3[playerMapY][playerMapX] = BLOCK4;
							map3[4][27] = YUKA;
						}
					}
					if (map3[5][27] != BLOCK5 || map3[5][27] == BLOCK5)
					{
						if (map3[5][27] == BLOCK5 && map3[playerMapY][playerMapX] == map3[4][17])
						{
							map3[playerMapY][playerMapX] = BLOCK5;
							map3[5][27] = YUKA;
						}
					}
					if (map3[6][27] != BLOCK6 || map3[6][27] == BLOCK6)
					{

						if (map3[6][27] == BLOCK6 && map3[playerMapY][playerMapX] == /*6以降は後で*/map3[4][9])
						{
							map3[playerMapY][playerMapX] = BLOCK6;
							map3[6][27] = YUKA;
						}
					}
					if (map3[7][27] != BLOCK7 || map3[7][27] == BLOCK7)
					{
						if (map3[7][27] == BLOCK7 && map3[playerMapY][playerMapX] == map3[4][9])
						{
							map3[playerMapY][playerMapX] = BLOCK7;
							map3[7][27] = YUKA;
						}
					}
					if (map3[8][27] != BLOCK8 || map3[8][27] == BLOCK8)
					{
						if (map3[8][27] == BLOCK8 && map3[playerMapY][playerMapX] == map3[4][9])
						{
							map3[playerMapY][playerMapX] = BLOCK8;
							map3[8][27] = YUKA;
						}
					}

					playerPosX -= playerSpeed;
				}

				if (map3[playerMapY][playerMapX - 1] == BLOCK1)
				{
					map3[1][27] = BLOCK1;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = KU;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK22)
				{
					map3[2][27] = BLOCK22;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = KU;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK3)
				{
					map3[3][27] = BLOCK3;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = KU;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK4)
				{
					map3[4][27] = BLOCK4;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = KU;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK5)
				{
					map3[5][27] = BLOCK5;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = KU;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK6)
				{
					map3[6][27] = BLOCK6;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = KU;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK7)
				{
					map3[7][27] = BLOCK7;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = KU;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK8)
				{
					map3[8][27] = BLOCK8;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = KU;
					playerPosX -= playerSpeed;

				}
			}
			if (map3[playerMapY][playerMapX] == NO)
			{
				if (map3[playerMapY][playerMapX - 1] == YUKA)
				{
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = NO;
					if (map3[1][27] != BLOCK1 || map3[1][27] == BLOCK1)
					{
						if (map3[1][27] == BLOCK1 && map3[playerMapY][playerMapX] == map3[4][9])
						{
							map3[playerMapY][playerMapX] = BLOCK1;
							map3[1][27] = YUKA;
						}
					}
					if (map3[2][27] != BLOCK22 || map3[2][27] == BLOCK22)
					{
						if (map3[2][27] == BLOCK22 && map3[playerMapY][playerMapX] == map3[4][11])
						{
							map3[playerMapY][playerMapX] = BLOCK22;
							map3[2][27] = YUKA;
						}
					}
					if (map3[3][27] != BLOCK3 || map3[3][27] == BLOCK3)
					{
						if (map3[3][27] == BLOCK3 && map3[playerMapY][playerMapX] == map3[4][13])
						{
							map3[playerMapY][playerMapX] = BLOCK3;
							map3[3][27] = YUKA;
						}
					}
					if (map3[4][27] != BLOCK4 || map3[4][27] == BLOCK4)
					{
						if (map3[4][27] == BLOCK4 && map3[playerMapY][playerMapX] == map3[4][15])
						{
							map3[playerMapY][playerMapX] = BLOCK4;
							map3[4][27] = YUKA;
						}
					}
					if (map3[5][27] != BLOCK5 || map3[5][27] == BLOCK5)
					{
						if (map3[5][27] == BLOCK5 && map3[playerMapY][playerMapX] == map3[4][17])
						{
							map3[playerMapY][playerMapX] = BLOCK5;
							map3[5][27] = YUKA;
						}
					}
					if (map3[6][27] != BLOCK6 || map3[6][27] == BLOCK6)
					{

						if (map3[6][27] == BLOCK6 && map3[playerMapY][playerMapX] == /*6以降は後で*/map3[4][9])
						{
							map3[playerMapY][playerMapX] = BLOCK6;
							map3[6][27] = YUKA;
						}
					}
					if (map3[7][27] != BLOCK7 || map3[7][27] == BLOCK7)
					{
						if (map3[7][27] == BLOCK7 && map3[playerMapY][playerMapX] == map3[4][9])
						{
							map3[playerMapY][playerMapX] = BLOCK7;
							map3[7][27] = YUKA;
						}
					}
					if (map3[8][27] != BLOCK8 || map3[8][27] == BLOCK8)
					{
						if (map3[8][27] == BLOCK8 && map3[playerMapY][playerMapX] == map3[4][9])
						{
							map3[playerMapY][playerMapX] = BLOCK8;
							map3[8][27] = YUKA;
						}
					}

					playerPosX -= playerSpeed;
				}

				if (map3[playerMapY][playerMapX - 1] == BLOCK1)
				{
					map3[1][27] = BLOCK1;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = NO;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK22)
				{
					map3[2][27] = BLOCK22;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = NO;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK3)
				{
					map3[3][27] = BLOCK3;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = NO;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK4)
				{
					map3[4][27] = BLOCK4;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = NO;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK5)
				{
					map3[5][27] = BLOCK5;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = NO;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK6)
				{
					map3[6][27] = BLOCK6;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = NO;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK7)
				{
					map3[7][27] = BLOCK7;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = NO;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK8)
				{
					map3[8][27] = BLOCK8;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = NO;
					playerPosX -= playerSpeed;

				}
			}
			if (map3[playerMapY][playerMapX] == GA)
			{
				if (map3[playerMapY][playerMapX - 1] == YUKA)
				{
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = GA;
					if (map3[1][27] != BLOCK1 || map3[1][27] == BLOCK1)
					{
						if (map3[1][27] == BLOCK1 && map3[playerMapY][playerMapX] == map3[4][9])
						{
							map3[playerMapY][playerMapX] = BLOCK1;
							map3[1][27] = YUKA;
						}
					}
					if (map3[2][27] != BLOCK22 || map3[2][27] == BLOCK22)
					{
						if (map3[2][27] == BLOCK22 && map3[playerMapY][playerMapX] == map3[4][11])
						{
							map3[playerMapY][playerMapX] = BLOCK22;
							map3[2][27] = YUKA;
						}
					}
					if (map3[3][27] != BLOCK3 || map3[3][27] == BLOCK3)
					{
						if (map3[3][27] == BLOCK3 && map3[playerMapY][playerMapX] == map3[4][13])
						{
							map3[playerMapY][playerMapX] = BLOCK3;
							map3[3][27] = YUKA;
						}
					}
					if (map3[4][27] != BLOCK4 || map3[4][27] == BLOCK4)
					{
						if (map3[4][27] == BLOCK4 && map3[playerMapY][playerMapX] == map3[4][15])
						{
							map3[playerMapY][playerMapX] = BLOCK4;
							map3[4][27] = YUKA;
						}
					}
					if (map3[5][27] != BLOCK5 || map3[5][27] == BLOCK5)
					{
						if (map3[5][27] == BLOCK5 && map3[playerMapY][playerMapX] == map3[4][17])
						{
							map3[playerMapY][playerMapX] = BLOCK5;
							map3[5][27] = YUKA;
						}
					}
					if (map3[6][27] != BLOCK6 || map3[6][27] == BLOCK6)
					{

						if (map3[6][27] == BLOCK6 && map3[playerMapY][playerMapX] == /*6以降は後で*/map3[4][9])
						{
							map3[playerMapY][playerMapX] = BLOCK6;
							map3[6][27] = YUKA;
						}
					}
					if (map3[7][27] != BLOCK7 || map3[7][27] == BLOCK7)
					{
						if (map3[7][27] == BLOCK7 && map3[playerMapY][playerMapX] == map3[4][9])
						{
							map3[playerMapY][playerMapX] = BLOCK7;
							map3[7][27] = YUKA;
						}
					}
					if (map3[8][27] != BLOCK8 || map3[8][27] == BLOCK8)
					{
						if (map3[8][27] == BLOCK8 && map3[playerMapY][playerMapX] == map3[4][9])
						{
							map3[playerMapY][playerMapX] = BLOCK8;
							map3[8][27] = YUKA;
						}
					}

					playerPosX -= playerSpeed;
				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK1)
				{
					map3[1][27] = BLOCK1;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = GA;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK22)
				{
					map3[2][27] = BLOCK22;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = GA;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK3)
				{
					map3[3][27] = BLOCK3;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = GA;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK4)
				{
					map3[4][27] = BLOCK4;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = GA;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK5)
				{
					map3[5][27] = BLOCK5;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = GA;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK6)
				{
					map3[6][27] = BLOCK6;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = GA;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK7)
				{
					map3[7][27] = BLOCK7;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = GA;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK8)
				{
					map3[8][27] = BLOCK8;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = GA;
					playerPosX -= playerSpeed;

				}
			}
			if (map3[playerMapY][playerMapX] == SU)
			{
				if (map3[playerMapY][playerMapX - 1] == YUKA)
				{
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = SU;
					if (map3[1][27] != BLOCK1 || map3[1][27] == BLOCK1)
					{
						if (map3[1][27] == BLOCK1 && map3[playerMapY][playerMapX] == map3[4][9])
						{
							map3[playerMapY][playerMapX] = BLOCK1;
							map3[1][27] = YUKA;
						}
					}
					if (map3[2][27] != BLOCK22 || map3[2][27] == BLOCK22)
					{
						if (map3[2][27] == BLOCK22 && map3[playerMapY][playerMapX] == map3[4][11])
						{
							map3[playerMapY][playerMapX] = BLOCK22;
							map3[2][27] = YUKA;
						}
					}
					if (map3[3][27] != BLOCK3 || map3[3][27] == BLOCK3)
					{
						if (map3[3][27] == BLOCK3 && map3[playerMapY][playerMapX] == map3[4][13])
						{
							map3[playerMapY][playerMapX] = BLOCK3;
							map3[3][27] = YUKA;
						}
					}
					if (map3[4][27] != BLOCK4 || map3[4][27] == BLOCK4)
					{
						if (map3[4][27] == BLOCK4 && map3[playerMapY][playerMapX] == map3[4][15])
						{
							map3[playerMapY][playerMapX] = BLOCK4;
							map3[4][27] = YUKA;
						}
					}
					if (map3[5][27] != BLOCK5 || map3[5][27] == BLOCK5)
					{
						if (map3[5][27] == BLOCK5 && map3[playerMapY][playerMapX] == map3[4][17])
						{
							map3[playerMapY][playerMapX] = BLOCK5;
							map3[5][27] = YUKA;
						}
					}
					if (map3[6][27] != BLOCK6 || map3[6][27] == BLOCK6)
					{

						if (map3[6][27] == BLOCK6 && map3[playerMapY][playerMapX] == /*6以降は後で*/map3[4][9])
						{
							map3[playerMapY][playerMapX] = BLOCK6;
							map3[6][27] = YUKA;
						}
					}
					if (map3[7][27] != BLOCK7 || map3[7][27] == BLOCK7)
					{
						if (map3[7][27] == BLOCK7 && map3[playerMapY][playerMapX] == map3[4][9])
						{
							map3[playerMapY][playerMapX] = BLOCK7;
							map3[7][27] = YUKA;
						}
					}
					if (map3[8][27] != BLOCK8 || map3[8][27] == BLOCK8)
					{
						if (map3[8][27] == BLOCK8 && map3[playerMapY][playerMapX] == map3[4][9])
						{
							map3[playerMapY][playerMapX] = BLOCK8;
							map3[8][27] = YUKA;
						}
					}
					playerPosX -= playerSpeed;
				}

				if (map3[playerMapY][playerMapX - 1] == BLOCK1)
				{
					map3[1][27] = BLOCK1;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = SU;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK22)
				{
					map3[2][27] = BLOCK22;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = SU;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK3)
				{
					map3[3][27] = BLOCK3;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = SU;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK4)
				{
					map3[4][27] = BLOCK4;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = SU;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK5)
				{
					map3[5][27] = BLOCK5;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = SU;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK6)
				{
					map3[6][27] = BLOCK6;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = SU;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK7)
				{
					map3[7][27] = BLOCK7;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = SU;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK8)
				{
					map3[8][27] = BLOCK8;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = SU;
					playerPosX -= playerSpeed;

				}
			}
			if (map3[playerMapY][playerMapX] == SO)
			{
				if (map3[playerMapY][playerMapX - 1] == YUKA)
				{
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = SO;
					if (map3[1][27] != BLOCK1 || map3[1][27] == BLOCK1)
					{
						if (map3[1][27] == BLOCK1 && map3[playerMapY][playerMapX] == map3[4][9])
						{
							map3[playerMapY][playerMapX] = BLOCK1;
							map3[1][27] = YUKA;
						}
					}
					if (map3[2][27] != BLOCK22 || map3[2][27] == BLOCK22)
					{
						if (map3[2][27] == BLOCK22 && map3[playerMapY][playerMapX] == map3[4][11])
						{
							map3[playerMapY][playerMapX] = BLOCK22;
							map3[2][27] = YUKA;
						}
					}
					if (map3[3][27] != BLOCK3 || map3[3][27] == BLOCK3)
					{
						if (map3[3][27] == BLOCK3 && map3[playerMapY][playerMapX] == map3[4][13])
						{
							map3[playerMapY][playerMapX] = BLOCK3;
							map3[3][27] = YUKA;
						}
					}
					if (map3[4][27] != BLOCK4 || map3[4][27] == BLOCK4)
					{
						if (map3[4][27] == BLOCK4 && map3[playerMapY][playerMapX] == map3[4][15])
						{
							map3[playerMapY][playerMapX] = BLOCK4;
							map3[4][27] = YUKA;
						}
					}
					if (map3[5][27] != BLOCK5 || map3[5][27] == BLOCK5)
					{
						if (map3[5][27] == BLOCK5 && map3[playerMapY][playerMapX] == map3[4][17])
						{
							map3[playerMapY][playerMapX] = BLOCK5;
							map3[5][27] = YUKA;
						}
					}
					if (map3[6][27] != BLOCK6 || map3[6][27] == BLOCK6)
					{

						if (map3[6][27] == BLOCK6 && map3[playerMapY][playerMapX] == /*6以降は後で*/map3[4][9])
						{
							map3[playerMapY][playerMapX] = BLOCK6;
							map3[6][27] = YUKA;
						}
					}
					if (map3[7][27] != BLOCK7 || map3[7][27] == BLOCK7)
					{
						if (map3[7][27] == BLOCK7 && map3[playerMapY][playerMapX] == map3[4][9])
						{
							map3[playerMapY][playerMapX] = BLOCK7;
							map3[7][27] = YUKA;
						}
					}
					if (map3[8][27] != BLOCK8 || map3[8][27] == BLOCK8)
					{
						if (map3[8][27] == BLOCK8 && map3[playerMapY][playerMapX] == map3[4][9])
						{
							map3[playerMapY][playerMapX] = BLOCK8;
							map3[8][27] = YUKA;
						}
					}
					playerPosX -= playerSpeed;
				}

				if (map3[playerMapY][playerMapX - 1] == BLOCK1)
				{
					map3[1][27] = BLOCK1;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = SO;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK22)
				{
					map3[2][27] = BLOCK22;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = SO;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK3)
				{
					map3[3][27] = BLOCK3;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = SO;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK4)
				{
					map3[4][27] = BLOCK4;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = SO;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK5)
				{
					map3[5][27] = BLOCK5;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = SO;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK6)
				{
					map3[6][27] = BLOCK6;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = SO;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK7)
				{
					map3[7][27] = BLOCK7;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = SO;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK8)
				{
					map3[8][27] = BLOCK8;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = SO;
					playerPosX -= playerSpeed;

				}
			}
			if (map3[playerMapY][playerMapX] == NI)
			{
				if (map3[playerMapY][playerMapX - 1] == YUKA)
				{
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = NI;
					if (map3[1][27] != BLOCK1 || map3[1][27] == BLOCK1)
					{
						if (map3[1][27] == BLOCK1 && map3[playerMapY][playerMapX] == map3[4][9])
						{
							map3[playerMapY][playerMapX] = BLOCK1;
							map3[1][27] = YUKA;
						}
					}
					if (map3[2][27] != BLOCK22 || map3[2][27] == BLOCK22)
					{
						if (map3[2][27] == BLOCK22 && map3[playerMapY][playerMapX] == map3[4][11])
						{
							map3[playerMapY][playerMapX] = BLOCK22;
							map3[2][27] = YUKA;
						}
					}
					if (map3[3][27] != BLOCK3 || map3[3][27] == BLOCK3)
					{
						if (map3[3][27] == BLOCK3 && map3[playerMapY][playerMapX] == map3[4][13])
						{
							map3[playerMapY][playerMapX] = BLOCK3;
							map3[3][27] = YUKA;
						}
					}
					if (map3[4][27] != BLOCK4 || map3[4][27] == BLOCK4)
					{
						if (map3[4][27] == BLOCK4 && map3[playerMapY][playerMapX] == map3[4][15])
						{
							map3[playerMapY][playerMapX] = BLOCK4;
							map3[4][27] = YUKA;
						}
					}
					if (map3[5][27] != BLOCK5 || map3[5][27] == BLOCK5)
					{
						if (map3[5][27] == BLOCK5 && map3[playerMapY][playerMapX] == map3[4][17])
						{
							map3[playerMapY][playerMapX] = BLOCK5;
							map3[5][27] = YUKA;
						}
					}
					if (map3[6][27] != BLOCK6 || map3[6][27] == BLOCK6)
					{

						if (map3[6][27] == BLOCK6 && map3[playerMapY][playerMapX] == /*6以降は後で*/map3[4][9])
						{
							map3[playerMapY][playerMapX] = BLOCK6;
							map3[6][27] = YUKA;
						}
					}
					if (map3[7][27] != BLOCK7 || map3[7][27] == BLOCK7)
					{
						if (map3[7][27] == BLOCK7 && map3[playerMapY][playerMapX] == map3[4][9])
						{
							map3[playerMapY][playerMapX] = BLOCK7;
							map3[7][27] = YUKA;
						}
					}
					if (map3[8][27] != BLOCK8 || map3[8][27] == BLOCK8)
					{
						if (map3[8][27] == BLOCK8 && map3[playerMapY][playerMapX] == map3[4][9])
						{
							map3[playerMapY][playerMapX] = BLOCK8;
							map3[8][27] = YUKA;
						}
					}
					playerPosX -= playerSpeed;
				}

				if (map3[playerMapY][playerMapX - 1] == BLOCK1)
				{
					map3[1][27] = BLOCK1;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = NI;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK22)
				{
					map3[2][27] = BLOCK22;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = NI;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK3)
				{
					map3[3][27] = BLOCK3;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = NI;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK4)
				{
					map3[4][27] = BLOCK4;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = NI;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK5)
				{
					map3[5][27] = BLOCK5;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = NI;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK6)
				{
					map3[6][27] = BLOCK6;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = NI;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK7)
				{
					map3[7][27] = BLOCK7;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = NI;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK8)
				{
					map3[8][27] = BLOCK8;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = NI;
					playerPosX -= playerSpeed;

				}
			}
			if (map3[playerMapY][playerMapX] == CHI)
			{
				if (map3[playerMapY][playerMapX - 1] == YUKA)
				{
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = CHI;
					if (map3[1][27] != BLOCK1 || map3[1][27] == BLOCK1)
					{
						if (map3[1][27] == BLOCK1 && map3[playerMapY][playerMapX] == map3[4][9])
						{
							map3[playerMapY][playerMapX] = BLOCK1;
							map3[1][27] = YUKA;
						}
					}
					if (map3[2][27] != BLOCK22 || map3[2][27] == BLOCK22)
					{
						if (map3[2][27] == BLOCK22 && map3[playerMapY][playerMapX] == map3[4][11])
						{
							map3[playerMapY][playerMapX] = BLOCK22;
							map3[2][27] = YUKA;
						}
					}
					if (map3[3][27] != BLOCK3 || map3[3][27] == BLOCK3)
					{
						if (map3[3][27] == BLOCK3 && map3[playerMapY][playerMapX] == map3[4][13])
						{
							map3[playerMapY][playerMapX] = BLOCK3;
							map3[3][27] = YUKA;
						}
					}
					if (map3[4][27] != BLOCK4 || map3[4][27] == BLOCK4)
					{
						if (map3[4][27] == BLOCK4 && map3[playerMapY][playerMapX] == map3[4][15])
						{
							map3[playerMapY][playerMapX] = BLOCK4;
							map3[4][27] = YUKA;
						}
					}
					if (map3[5][27] != BLOCK5 || map3[5][27] == BLOCK5)
					{
						if (map3[5][27] == BLOCK5 && map3[playerMapY][playerMapX] == map3[4][17])
						{
							map3[playerMapY][playerMapX] = BLOCK5;
							map3[5][27] = YUKA;
						}
					}
					if (map3[6][27] != BLOCK6 || map3[6][27] == BLOCK6)
					{

						if (map3[6][27] == BLOCK6 && map3[playerMapY][playerMapX] == /*6以降は後で*/map3[4][9])
						{
							map3[playerMapY][playerMapX] = BLOCK6;
							map3[6][27] = YUKA;
						}
					}
					if (map3[7][27] != BLOCK7 || map3[7][27] == BLOCK7)
					{
						if (map3[7][27] == BLOCK7 && map3[playerMapY][playerMapX] == map3[4][9])
						{
							map3[playerMapY][playerMapX] = BLOCK7;
							map3[7][27] = YUKA;
						}
					}
					if (map3[8][27] != BLOCK8 || map3[8][27] == BLOCK8)
					{
						if (map3[8][27] == BLOCK8 && map3[playerMapY][playerMapX] == map3[4][9])
						{
							map3[playerMapY][playerMapX] = BLOCK8;
							map3[8][27] = YUKA;
						}
					}
					playerPosX -= playerSpeed;
				}

				if (map3[playerMapY][playerMapX - 1] == BLOCK1)
				{
					map3[1][27] = BLOCK1;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = CHI;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK22)
				{
					map3[2][27] = BLOCK22;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = CHI;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK3)
				{
					map3[3][27] = BLOCK3;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = CHI;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK4)
				{
					map3[4][27] = BLOCK4;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = CHI;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK5)
				{
					map3[5][27] = BLOCK5;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = CHI;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK6)
				{
					map3[6][27] = BLOCK6;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = CHI;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK7)
				{
					map3[7][27] = BLOCK7;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = CHI;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK8)
				{
					map3[8][27] = BLOCK8;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = CHI;
					playerPosX -= playerSpeed;

				}
			}

			if (map3[playerMapY][playerMapX] == NU)
			{
				if (map3[playerMapY][playerMapX - 1] == YUKA)
				{
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = NU;
					if (map3[1][27] != BLOCK1 || map3[1][27] == BLOCK1)
					{
						if (map3[1][27] == BLOCK1 && map3[playerMapY][playerMapX] == map3[4][9])
						{
							map3[playerMapY][playerMapX] = BLOCK1;
							map3[1][27] = YUKA;
						}
					}
					if (map3[2][27] != BLOCK22 || map3[2][27] == BLOCK22)
					{
						if (map3[2][27] == BLOCK22 && map3[playerMapY][playerMapX] == map3[4][11])
						{
							map3[playerMapY][playerMapX] = BLOCK22;
							map3[2][27] = YUKA;
						}
					}
					if (map3[3][27] != BLOCK3 || map3[3][27] == BLOCK3)
					{
						if (map3[3][27] == BLOCK3 && map3[playerMapY][playerMapX] == map3[4][13])
						{
							map3[playerMapY][playerMapX] = BLOCK3;
							map3[3][27] = YUKA;
						}
					}
					if (map3[4][27] != BLOCK4 || map3[4][27] == BLOCK4)
					{
						if (map3[4][27] == BLOCK4 && map3[playerMapY][playerMapX] == map3[4][15])
						{
							map3[playerMapY][playerMapX] = BLOCK4;
							map3[4][27] = YUKA;
						}
					}
					if (map3[5][27] != BLOCK5 || map3[5][27] == BLOCK5)
					{
						if (map3[5][27] == BLOCK5 && map3[playerMapY][playerMapX] == map3[4][17])
						{
							map3[playerMapY][playerMapX] = BLOCK5;
							map3[5][27] = YUKA;
						}
					}
					if (map3[6][27] != BLOCK6 || map3[6][27] == BLOCK6)
					{

						if (map3[6][27] == BLOCK6 && map3[playerMapY][playerMapX] == /*6以降は後で*/map3[4][9])
						{
							map3[playerMapY][playerMapX] = BLOCK6;
							map3[6][27] = YUKA;
						}
					}
					if (map3[7][27] != BLOCK7 || map3[7][27] == BLOCK7)
					{
						if (map3[7][27] == BLOCK7 && map3[playerMapY][playerMapX] == map3[4][9])
						{
							map3[playerMapY][playerMapX] = BLOCK7;
							map3[7][27] = YUKA;
						}
					}
					if (map3[8][27] != BLOCK8 || map3[8][27] == BLOCK8)
					{
						if (map3[8][27] == BLOCK8 && map3[playerMapY][playerMapX] == map3[4][9])
						{
							map3[playerMapY][playerMapX] = BLOCK8;
							map3[8][27] = YUKA;
						}
					}
					playerPosX -= playerSpeed;
				}

				if (map3[playerMapY][playerMapX - 1] == BLOCK1)
				{
					map3[1][27] = BLOCK1;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = NU;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK22)
				{
					map3[2][27] = BLOCK22;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = NU;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK3)
				{
					map3[3][27] = BLOCK3;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = NU;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK4)
				{
					map3[4][27] = BLOCK4;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = NU;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK5)
				{
					map3[5][27] = BLOCK5;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = NU;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK6)
				{
					map3[6][27] = BLOCK6;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = NU;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK7)
				{
					map3[7][27] = BLOCK7;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = NU;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK8)
				{
					map3[8][27] = BLOCK8;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = NU;
					playerPosX -= playerSpeed;

				}
			}
			if (map3[playerMapY][playerMapX] == NE)
			{
				if (map3[playerMapY][playerMapX - 1] == YUKA)
				{
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = NE;
					if (map3[1][27] != BLOCK1 || map3[1][27] == BLOCK1)
					{
						if (map3[1][27] == BLOCK1 && map3[playerMapY][playerMapX] == map3[4][9])
						{
							map3[playerMapY][playerMapX] = BLOCK1;
							map3[1][27] = YUKA;
						}
					}
					if (map3[2][27] != BLOCK22 || map3[2][27] == BLOCK22)
					{
						if (map3[2][27] == BLOCK22 && map3[playerMapY][playerMapX] == map3[4][11])
						{
							map3[playerMapY][playerMapX] = BLOCK22;
							map3[2][27] = YUKA;
						}
					}
					if (map3[3][27] != BLOCK3 || map3[3][27] == BLOCK3)
					{
						if (map3[3][27] == BLOCK3 && map3[playerMapY][playerMapX] == map3[4][13])
						{
							map3[playerMapY][playerMapX] = BLOCK3;
							map3[3][27] = YUKA;
						}
					}
					if (map3[4][27] != BLOCK4 || map3[4][27] == BLOCK4)
					{
						if (map3[4][27] == BLOCK4 && map3[playerMapY][playerMapX] == map3[4][15])
						{
							map3[playerMapY][playerMapX] = BLOCK4;
							map3[4][27] = YUKA;
						}
					}
					if (map3[5][27] != BLOCK5 || map3[5][27] == BLOCK5)
					{
						if (map3[5][27] == BLOCK5 && map3[playerMapY][playerMapX] == map3[4][17])
						{
							map3[playerMapY][playerMapX] = BLOCK5;
							map3[5][27] = YUKA;
						}
					}
					if (map3[6][27] != BLOCK6 || map3[6][27] == BLOCK6)
					{

						if (map3[6][27] == BLOCK6 && map3[playerMapY][playerMapX] == /*6以降は後で*/map3[4][9])
						{
							map3[playerMapY][playerMapX] = BLOCK6;
							map3[6][27] = YUKA;
						}
					}
					if (map3[7][27] != BLOCK7 || map3[7][27] == BLOCK7)
					{
						if (map3[7][27] == BLOCK7 && map3[playerMapY][playerMapX] == map3[4][9])
						{
							map3[playerMapY][playerMapX] = BLOCK7;
							map3[7][27] = YUKA;
						}
					}
					if (map3[8][27] != BLOCK8 || map3[8][27] == BLOCK8)
					{
						if (map3[8][27] == BLOCK8 && map3[playerMapY][playerMapX] == map3[4][9])
						{
							map3[playerMapY][playerMapX] = BLOCK8;
							map3[8][27] = YUKA;
						}
					}
					playerPosX -= playerSpeed;
				}

				if (map3[playerMapY][playerMapX - 1] == BLOCK1)
				{
					map3[1][27] = BLOCK1;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = NE;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK22)
				{
					map3[2][27] = BLOCK22;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = NE;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK3)
				{
					map3[3][27] = BLOCK3;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = NE;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK4)
				{
					map3[4][27] = BLOCK4;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = NE;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK5)
				{
					map3[5][27] = BLOCK5;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = NE;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK6)
				{
					map3[6][27] = BLOCK6;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = NE;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK7)
				{
					map3[7][27] = BLOCK7;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = NE;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK8)
				{
					map3[8][27] = BLOCK8;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = NE;
					playerPosX -= playerSpeed;

				}
			}
			if (map3[playerMapY][playerMapX] == RA)
			{
				if (map3[playerMapY][playerMapX - 1] == YUKA)
				{
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = RA;
					if (map3[1][27] != BLOCK1 || map3[1][27] == BLOCK1)
					{
						if (map3[1][27] == BLOCK1 && map3[playerMapY][playerMapX] == map3[4][9])
						{
							map3[playerMapY][playerMapX] = BLOCK1;
							map3[1][27] = YUKA;
						}
					}
					if (map3[2][27] != BLOCK22 || map3[2][27] == BLOCK22)
					{
						if (map3[2][27] == BLOCK22 && map3[playerMapY][playerMapX] == map3[4][11])
						{
							map3[playerMapY][playerMapX] = BLOCK22;
							map3[2][27] = YUKA;
						}
					}
					if (map3[3][27] != BLOCK3 || map3[3][27] == BLOCK3)
					{
						if (map3[3][27] == BLOCK3 && map3[playerMapY][playerMapX] == map3[4][13])
						{
							map3[playerMapY][playerMapX] = BLOCK3;
							map3[3][27] = YUKA;
						}
					}
					if (map3[4][27] != BLOCK4 || map3[4][27] == BLOCK4)
					{
						if (map3[4][27] == BLOCK4 && map3[playerMapY][playerMapX] == map3[4][15])
						{
							map3[playerMapY][playerMapX] = BLOCK4;
							map3[4][27] = YUKA;
						}
					}
					if (map3[5][27] != BLOCK5 || map3[5][27] == BLOCK5)
					{
						if (map3[5][27] == BLOCK5 && map3[playerMapY][playerMapX] == map3[4][17])
						{
							map3[playerMapY][playerMapX] = BLOCK5;
							map3[5][27] = YUKA;
						}
					}
					if (map3[6][27] != BLOCK6 || map3[6][27] == BLOCK6)
					{

						if (map3[6][27] == BLOCK6 && map3[playerMapY][playerMapX] == /*6以降は後で*/map3[4][9])
						{
							map3[playerMapY][playerMapX] = BLOCK6;
							map3[6][27] = YUKA;
						}
					}
					if (map3[7][27] != BLOCK7 || map3[7][27] == BLOCK7)
					{
						if (map3[7][27] == BLOCK7 && map3[playerMapY][playerMapX] == map3[4][9])
						{
							map3[playerMapY][playerMapX] = BLOCK7;
							map3[7][27] = YUKA;
						}
					}
					if (map3[8][27] != BLOCK8 || map3[8][27] == BLOCK8)
					{
						if (map3[8][27] == BLOCK8 && map3[playerMapY][playerMapX] == map3[4][9])
						{
							map3[playerMapY][playerMapX] = BLOCK8;
							map3[8][27] = YUKA;
						}
					}
					playerPosX -= playerSpeed;
				}

				if (map3[playerMapY][playerMapX - 1] == BLOCK1)
				{
					map3[1][27] = BLOCK1;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = RA;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK22)
				{
					map3[2][27] = BLOCK22;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = RA;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK3)
				{
					map3[3][27] = BLOCK3;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = RA;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK4)
				{
					map3[4][27] = BLOCK4;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = RA;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK5)
				{
					map3[5][27] = BLOCK5;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = RA;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK6)
				{
					map3[6][27] = BLOCK6;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = RA;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK7)
				{
					map3[7][27] = BLOCK7;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = RA;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK8)
				{
					map3[8][27] = BLOCK8;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = RA;
					playerPosX -= playerSpeed;

				}
			}
			if (map3[playerMapY][playerMapX] == HO)
			{
				if (map3[playerMapY][playerMapX - 1] == YUKA)
				{
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = HO;
					if (map3[1][27] != BLOCK1 || map3[1][27] == BLOCK1)
					{
						if (map3[1][27] == BLOCK1 && map3[playerMapY][playerMapX] == map3[4][9])
						{
							map3[playerMapY][playerMapX] = BLOCK1;
							map3[1][27] = YUKA;
						}
					}
					if (map3[2][27] != BLOCK22 || map3[2][27] == BLOCK22)
					{
						if (map3[2][27] == BLOCK22 && map3[playerMapY][playerMapX] == map3[4][11])
						{
							map3[playerMapY][playerMapX] = BLOCK22;
							map3[2][27] = YUKA;
						}
					}
					if (map3[3][27] != BLOCK3 || map3[3][27] == BLOCK3)
					{
						if (map3[3][27] == BLOCK3 && map3[playerMapY][playerMapX] == map3[4][13])
						{
							map3[playerMapY][playerMapX] = BLOCK3;
							map3[3][27] = YUKA;
						}
					}
					if (map3[4][27] != BLOCK4 || map3[4][27] == BLOCK4)
					{
						if (map3[4][27] == BLOCK4 && map3[playerMapY][playerMapX] == map3[4][15])
						{
							map3[playerMapY][playerMapX] = BLOCK4;
							map3[4][27] = YUKA;
						}
					}
					if (map3[5][27] != BLOCK5 || map3[5][27] == BLOCK5)
					{
						if (map3[5][27] == BLOCK5 && map3[playerMapY][playerMapX] == map3[4][17])
						{
							map3[playerMapY][playerMapX] = BLOCK5;
							map3[5][27] = YUKA;
						}
					}
					if (map3[6][27] != BLOCK6 || map3[6][27] == BLOCK6)
					{

						if (map3[6][27] == BLOCK6 && map3[playerMapY][playerMapX] == /*6以降は後で*/map3[4][9])
						{
							map3[playerMapY][playerMapX] = BLOCK6;
							map3[6][27] = YUKA;
						}
					}
					if (map3[7][27] != BLOCK7 || map3[7][27] == BLOCK7)
					{
						if (map3[7][27] == BLOCK7 && map3[playerMapY][playerMapX] == map3[4][9])
						{
							map3[playerMapY][playerMapX] = BLOCK7;
							map3[7][27] = YUKA;
						}
					}
					if (map3[8][27] != BLOCK8 || map3[8][27] == BLOCK8)
					{
						if (map3[8][27] == BLOCK8 && map3[playerMapY][playerMapX] == map3[4][9])
						{
							map3[playerMapY][playerMapX] = BLOCK8;
							map3[8][27] = YUKA;
						}
					}
					playerPosX -= playerSpeed;
				}

				if (map3[playerMapY][playerMapX - 1] == BLOCK1)
				{
					map3[1][27] = BLOCK1;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = HO;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK22)
				{
					map3[2][27] = BLOCK22;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = HO;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK3)
				{
					map3[3][27] = BLOCK3;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = HO;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK4)
				{
					map3[4][27] = BLOCK4;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = HO;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK5)
				{
					map3[5][27] = BLOCK5;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = HO;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK6)
				{
					map3[6][27] = BLOCK6;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = HO;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK7)
				{
					map3[7][27] = BLOCK7;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = HO;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK8)
				{
					map3[8][27] = BLOCK8;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = HO;
					playerPosX -= playerSpeed;

				}
			}
			if (map3[playerMapY][playerMapX] == ZE)
			{
				if (map3[playerMapY][playerMapX - 1] == YUKA)
				{
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = ZE;
					if (map3[1][27] != BLOCK1 || map3[1][27] == BLOCK1)
					{
						if (map3[1][27] == BLOCK1 && map3[playerMapY][playerMapX] == map3[4][9])
						{
							map3[playerMapY][playerMapX] = BLOCK1;
							map3[1][27] = YUKA;
						}
					}
					if (map3[2][27] != BLOCK22 || map3[2][27] == BLOCK22)
					{
						if (map3[2][27] == BLOCK22 && map3[playerMapY][playerMapX] == map3[4][11])
						{
							map3[playerMapY][playerMapX] = BLOCK22;
							map3[2][27] = YUKA;
						}
					}
					if (map3[3][27] != BLOCK3 || map3[3][27] == BLOCK3)
					{
						if (map3[3][27] == BLOCK3 && map3[playerMapY][playerMapX] == map3[4][13])
						{
							map3[playerMapY][playerMapX] = BLOCK3;
							map3[3][27] = YUKA;
						}
					}
					if (map3[4][27] != BLOCK4 || map3[4][27] == BLOCK4)
					{
						if (map3[4][27] == BLOCK4 && map3[playerMapY][playerMapX] == map3[4][15])
						{
							map3[playerMapY][playerMapX] = BLOCK4;
							map3[4][27] = YUKA;
						}
					}
					if (map3[5][27] != BLOCK5 || map3[5][27] == BLOCK5)
					{
						if (map3[5][27] == BLOCK5 && map3[playerMapY][playerMapX] == map3[4][17])
						{
							map3[playerMapY][playerMapX] = BLOCK5;
							map3[5][27] = YUKA;
						}
					}
					if (map3[6][27] != BLOCK6 || map3[6][27] == BLOCK6)
					{

						if (map3[6][27] == BLOCK6 && map3[playerMapY][playerMapX] == /*6以降は後で*/map3[4][9])
						{
							map3[playerMapY][playerMapX] = BLOCK6;
							map3[6][27] = YUKA;
						}
					}
					if (map3[7][27] != BLOCK7 || map3[7][27] == BLOCK7)
					{
						if (map3[7][27] == BLOCK7 && map3[playerMapY][playerMapX] == map3[4][9])
						{
							map3[playerMapY][playerMapX] = BLOCK7;
							map3[7][27] = YUKA;
						}
					}
					if (map3[8][27] != BLOCK8 || map3[8][27] == BLOCK8)
					{
						if (map3[8][27] == BLOCK8 && map3[playerMapY][playerMapX] == map3[4][9])
						{
							map3[playerMapY][playerMapX] = BLOCK8;
							map3[8][27] = YUKA;
						}
					}
					playerPosX -= playerSpeed;
				}

				if (map3[playerMapY][playerMapX - 1] == BLOCK1)
				{
					map3[1][27] = BLOCK1;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = ZE;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK22)
				{
					map3[2][27] = BLOCK22;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = ZE;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK3)
				{
					map3[3][27] = BLOCK3;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = ZE;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK4)
				{
					map3[4][27] = BLOCK4;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = ZE;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK5)
				{
					map3[5][27] = BLOCK5;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = ZE;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK6)
				{
					map3[6][27] = BLOCK6;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = ZE;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK7)
				{
					map3[7][27] = BLOCK7;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = ZE;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK8)
				{
					map3[8][27] = BLOCK8;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = ZE;
					playerPosX -= playerSpeed;

				}
			}
			if (map3[playerMapY][playerMapX] == RU)
			{
				if (map3[playerMapY][playerMapX - 1] == YUKA)
				{
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = RU;
					if (map3[1][27] != BLOCK1 || map3[1][27] == BLOCK1)
					{
						if (map3[1][27] == BLOCK1 && map3[playerMapY][playerMapX] == map3[4][9])
						{
							map3[playerMapY][playerMapX] = BLOCK1;
							map3[1][27] = YUKA;
						}
					}
					if (map3[2][27] != BLOCK22 || map3[2][27] == BLOCK22)
					{
						if (map3[2][27] == BLOCK22 && map3[playerMapY][playerMapX] == map3[4][11])
						{
							map3[playerMapY][playerMapX] = BLOCK22;
							map3[2][27] = YUKA;
						}
					}
					if (map3[3][27] != BLOCK3 || map3[3][27] == BLOCK3)
					{
						if (map3[3][27] == BLOCK3 && map3[playerMapY][playerMapX] == map3[4][13])
						{
							map3[playerMapY][playerMapX] = BLOCK3;
							map3[3][27] = YUKA;
						}
					}
					if (map3[4][27] != BLOCK4 || map3[4][27] == BLOCK4)
					{
						if (map3[4][27] == BLOCK4 && map3[playerMapY][playerMapX] == map3[4][15])
						{
							map3[playerMapY][playerMapX] = BLOCK4;
							map3[4][27] = YUKA;
						}
					}
					if (map3[5][27] != BLOCK5 || map3[5][27] == BLOCK5)
					{
						if (map3[5][27] == BLOCK5 && map3[playerMapY][playerMapX] == map3[4][17])
						{
							map3[playerMapY][playerMapX] = BLOCK5;
							map3[5][27] = YUKA;
						}
					}
					if (map3[6][27] != BLOCK6 || map3[6][27] == BLOCK6)
					{

						if (map3[6][27] == BLOCK6 && map3[playerMapY][playerMapX] == /*6以降は後で*/map3[4][9])
						{
							map3[playerMapY][playerMapX] = BLOCK6;
							map3[6][27] = YUKA;
						}
					}
					if (map3[7][27] != BLOCK7 || map3[7][27] == BLOCK7)
					{
						if (map3[7][27] == BLOCK7 && map3[playerMapY][playerMapX] == map3[4][9])
						{
							map3[playerMapY][playerMapX] = BLOCK7;
							map3[7][27] = YUKA;
						}
					}
					if (map3[8][27] != BLOCK8 || map3[8][27] == BLOCK8)
					{
						if (map3[8][27] == BLOCK8 && map3[playerMapY][playerMapX] == map3[4][9])
						{
							map3[playerMapY][playerMapX] = BLOCK8;
							map3[8][27] = YUKA;
						}
					}
					playerPosX -= playerSpeed;
				}

				if (map3[playerMapY][playerMapX - 1] == BLOCK1)
				{
					map3[1][27] = BLOCK1;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = RU;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK22)
				{
					map3[2][27] = BLOCK22;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = RU;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK3)
				{
					map3[3][27] = BLOCK3;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = RU;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK4)
				{
					map3[4][27] = BLOCK4;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = RU;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK5)
				{
					map3[5][27] = BLOCK5;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = RU;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK6)
				{
					map3[6][27] = BLOCK6;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = RU;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK7)
				{
					map3[7][27] = BLOCK7;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = RU;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK8)
				{
					map3[8][27] = BLOCK8;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = RU;
					playerPosX -= playerSpeed;

				}
			}
			if (map3[playerMapY][playerMapX] == YU)
			{
				if (map3[playerMapY][playerMapX - 1] == YUKA)
				{
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = YU;
					if (map3[1][27] != BLOCK1 || map3[1][27] == BLOCK1)
					{
						if (map3[1][27] == BLOCK1 && map3[playerMapY][playerMapX] == map3[4][9])
						{
							map3[playerMapY][playerMapX] = BLOCK1;
							map3[1][27] = YUKA;
						}
					}
					if (map3[2][27] != BLOCK22 || map3[2][27] == BLOCK22)
					{
						if (map3[2][27] == BLOCK22 && map3[playerMapY][playerMapX] == map3[4][11])
						{
							map3[playerMapY][playerMapX] = BLOCK22;
							map3[2][27] = YUKA;
						}
					}
					if (map3[3][27] != BLOCK3 || map3[3][27] == BLOCK3)
					{
						if (map3[3][27] == BLOCK3 && map3[playerMapY][playerMapX] == map3[4][13])
						{
							map3[playerMapY][playerMapX] = BLOCK3;
							map3[3][27] = YUKA;
						}
					}
					if (map3[4][27] != BLOCK4 || map3[4][27] == BLOCK4)
					{
						if (map3[4][27] == BLOCK4 && map3[playerMapY][playerMapX] == map3[4][15])
						{
							map3[playerMapY][playerMapX] = BLOCK4;
							map3[4][27] = YUKA;
						}
					}
					if (map3[5][27] != BLOCK5 || map3[5][27] == BLOCK5)
					{
						if (map3[5][27] == BLOCK5 && map3[playerMapY][playerMapX] == map3[4][17])
						{
							map3[playerMapY][playerMapX] = BLOCK5;
							map3[5][27] = YUKA;
						}
					}
					if (map3[6][27] != BLOCK6 || map3[6][27] == BLOCK6)
					{

						if (map3[6][27] == BLOCK6 && map3[playerMapY][playerMapX] == /*6以降は後で*/map3[4][9])
						{
							map3[playerMapY][playerMapX] = BLOCK6;
							map3[6][27] = YUKA;
						}
					}
					if (map3[7][27] != BLOCK7 || map3[7][27] == BLOCK7)
					{
						if (map3[7][27] == BLOCK7 && map3[playerMapY][playerMapX] == map3[4][9])
						{
							map3[playerMapY][playerMapX] = BLOCK7;
							map3[7][27] = YUKA;
						}
					}
					if (map3[8][27] != BLOCK8 || map3[8][27] == BLOCK8)
					{
						if (map3[8][27] == BLOCK8 && map3[playerMapY][playerMapX] == map3[4][9])
						{
							map3[playerMapY][playerMapX] = BLOCK8;
							map3[8][27] = YUKA;
						}
					}
					playerPosX -= playerSpeed;
				}

				if (map3[playerMapY][playerMapX - 1] == BLOCK1)
				{
					map3[1][27] = BLOCK1;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = YU;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK22)
				{
					map3[2][27] = BLOCK22;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = YU;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK3)
				{
					map3[3][27] = BLOCK3;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = YU;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK4)
				{
					map3[4][27] = BLOCK4;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = YU;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK5)
				{
					map3[5][27] = BLOCK5;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = YU;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK6)
				{
					map3[6][27] = BLOCK6;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = YU;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK7)
				{
					map3[7][27] = BLOCK7;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = YU;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK8)
				{
					map3[8][27] = BLOCK8;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = YU;
					playerPosX -= playerSpeed;

				}
			}
			if (map3[playerMapY][playerMapX] == DO)
			{
				if (map3[playerMapY][playerMapX - 1] == YUKA)
				{
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = DO;
					if (map3[1][27] != BLOCK1 || map3[1][27] == BLOCK1)
					{
						if (map3[1][27] == BLOCK1 && map3[playerMapY][playerMapX] == map3[4][9])
						{
							map3[playerMapY][playerMapX] = BLOCK1;
							map3[1][27] = YUKA;
						}
					}
					if (map3[2][27] != BLOCK22 || map3[2][27] == BLOCK22)
					{
						if (map3[2][27] == BLOCK22 && map3[playerMapY][playerMapX] == map3[4][11])
						{
							map3[playerMapY][playerMapX] = BLOCK22;
							map3[2][27] = YUKA;
						}
					}
					if (map3[3][27] != BLOCK3 || map3[3][27] == BLOCK3)
					{
						if (map3[3][27] == BLOCK3 && map3[playerMapY][playerMapX] == map3[4][13])
						{
							map3[playerMapY][playerMapX] = BLOCK3;
							map3[3][27] = YUKA;
						}
					}
					if (map3[4][27] != BLOCK4 || map3[4][27] == BLOCK4)
					{
						if (map3[4][27] == BLOCK4 && map3[playerMapY][playerMapX] == map3[4][15])
						{
							map3[playerMapY][playerMapX] = BLOCK4;
							map3[4][27] = YUKA;
						}
					}
					if (map3[5][27] != BLOCK5 || map3[5][27] == BLOCK5)
					{
						if (map3[5][27] == BLOCK5 && map3[playerMapY][playerMapX] == map3[4][17])
						{
							map3[playerMapY][playerMapX] = BLOCK5;
							map3[5][27] = YUKA;
						}
					}
					if (map3[6][27] != BLOCK6 || map3[6][27] == BLOCK6)
					{

						if (map3[6][27] == BLOCK6 && map3[playerMapY][playerMapX] == /*6以降は後で*/map3[4][9])
						{
							map3[playerMapY][playerMapX] = BLOCK6;
							map3[6][27] = YUKA;
						}
					}
					if (map3[7][27] != BLOCK7 || map3[7][27] == BLOCK7)
					{
						if (map3[7][27] == BLOCK7 && map3[playerMapY][playerMapX] == map3[4][9])
						{
							map3[playerMapY][playerMapX] = BLOCK7;
							map3[7][27] = YUKA;
						}
					}
					if (map3[8][27] != BLOCK8 || map3[8][27] == BLOCK8)
					{
						if (map3[8][27] == BLOCK8 && map3[playerMapY][playerMapX] == map3[4][9])
						{
							map3[playerMapY][playerMapX] = BLOCK8;
							map3[8][27] = YUKA;
						}
					}
					playerPosX -= playerSpeed;
				}

				if (map3[playerMapY][playerMapX - 1] == BLOCK1)
				{
					map3[1][27] = BLOCK1;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = DO;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK22)
				{
					map3[2][27] = BLOCK22;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = DO;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK3)
				{
					map3[3][27] = BLOCK3;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = DO;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK4)
				{
					map3[4][27] = BLOCK4;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = DO;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK5)
				{
					map3[5][27] = BLOCK5;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = DO;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK6)
				{
					map3[6][27] = BLOCK6;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = DO;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK7)
				{
					map3[7][27] = BLOCK7;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = DO;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK8)
				{
					map3[8][27] = BLOCK8;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = DO;
					playerPosX -= playerSpeed;

				}
			}
			if (map3[playerMapY][playerMapX] == GO)
			{
				if (map3[playerMapY][playerMapX - 1] == YUKA)
				{
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = GO;
					if (map3[1][27] != BLOCK1 || map3[1][27] == BLOCK1)
					{
						if (map3[1][27] == BLOCK1 && map3[playerMapY][playerMapX] == map3[4][9])
						{
							map3[playerMapY][playerMapX] = BLOCK1;
							map3[1][27] = YUKA;
						}
					}
					if (map3[2][27] != BLOCK22 || map3[2][27] == BLOCK22)
					{
						if (map3[2][27] == BLOCK22 && map3[playerMapY][playerMapX] == map3[4][11])
						{
							map3[playerMapY][playerMapX] = BLOCK22;
							map3[2][27] = YUKA;
						}
					}
					if (map3[3][27] != BLOCK3 || map3[3][27] == BLOCK3)
					{
						if (map3[3][27] == BLOCK3 && map3[playerMapY][playerMapX] == map3[4][13])
						{
							map3[playerMapY][playerMapX] = BLOCK3;
							map3[3][27] = YUKA;
						}
					}
					if (map3[4][27] != BLOCK4 || map3[4][27] == BLOCK4)
					{
						if (map3[4][27] == BLOCK4 && map3[playerMapY][playerMapX] == map3[4][15])
						{
							map3[playerMapY][playerMapX] = BLOCK4;
							map3[4][27] = YUKA;
						}
					}
					if (map3[5][27] != BLOCK5 || map3[5][27] == BLOCK5)
					{
						if (map3[5][27] == BLOCK5 && map3[playerMapY][playerMapX] == map3[4][17])
						{
							map3[playerMapY][playerMapX] = BLOCK5;
							map3[5][27] = YUKA;
						}
					}
					if (map3[6][27] != BLOCK6 || map3[6][27] == BLOCK6)
					{

						if (map3[6][27] == BLOCK6 && map3[playerMapY][playerMapX] == /*6以降は後で*/map3[4][9])
						{
							map3[playerMapY][playerMapX] = BLOCK6;
							map3[6][27] = YUKA;
						}
					}
					if (map3[7][27] != BLOCK7 || map3[7][27] == BLOCK7)
					{
						if (map3[7][27] == BLOCK7 && map3[playerMapY][playerMapX] == map3[4][9])
						{
							map3[playerMapY][playerMapX] = BLOCK7;
							map3[7][27] = YUKA;
						}
					}
					if (map3[8][27] != BLOCK8 || map3[8][27] == BLOCK8)
					{
						if (map3[8][27] == BLOCK8 && map3[playerMapY][playerMapX] == map3[4][9])
						{
							map3[playerMapY][playerMapX] = BLOCK8;
							map3[8][27] = YUKA;
						}
					}
					playerPosX -= playerSpeed;
				}

				if (map3[playerMapY][playerMapX - 1] == BLOCK1)
				{
					map3[1][27] = BLOCK1;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = GO;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK22)
				{
					map3[2][27] = BLOCK22;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = GO;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK3)
				{
					map3[3][27] = BLOCK3;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = GO;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK4)
				{
					map3[4][27] = BLOCK4;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = GO;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK5)
				{
					map3[5][27] = BLOCK5;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = GO;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK6)
				{
					map3[6][27] = BLOCK6;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = GO;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK7)
				{
					map3[7][27] = BLOCK7;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = GO;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK8)
				{
					map3[8][27] = BLOCK8;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = GO;
					playerPosX -= playerSpeed;

				}
			}
			if (map3[playerMapY][playerMapX] == ZE)
			{
				if (map3[playerMapY][playerMapX - 1] == YUKA)
				{
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = ZE;
					if (map3[1][27] != BLOCK1 || map3[1][27] == BLOCK1)
					{
						if (map3[1][27] == BLOCK1 && map3[playerMapY][playerMapX] == map3[4][9])
						{
							map3[playerMapY][playerMapX] = BLOCK1;
							map3[1][27] = YUKA;
						}
					}
					if (map3[2][27] != BLOCK22 || map3[2][27] == BLOCK22)
					{
						if (map3[2][27] == BLOCK22 && map3[playerMapY][playerMapX] == map3[4][11])
						{
							map3[playerMapY][playerMapX] = BLOCK22;
							map3[2][27] = YUKA;
						}
					}
					if (map3[3][27] != BLOCK3 || map3[3][27] == BLOCK3)
					{
						if (map3[3][27] == BLOCK3 && map3[playerMapY][playerMapX] == map3[4][13])
						{
							map3[playerMapY][playerMapX] = BLOCK3;
							map3[3][27] = YUKA;
						}
					}
					if (map3[4][27] != BLOCK4 || map3[4][27] == BLOCK4)
					{
						if (map3[4][27] == BLOCK4 && map3[playerMapY][playerMapX] == map3[4][15])
						{
							map3[playerMapY][playerMapX] = BLOCK4;
							map3[4][27] = YUKA;
						}
					}
					if (map3[5][27] != BLOCK5 || map3[5][27] == BLOCK5)
					{
						if (map3[5][27] == BLOCK5 && map3[playerMapY][playerMapX] == map3[4][17])
						{
							map3[playerMapY][playerMapX] = BLOCK5;
							map3[5][27] = YUKA;
						}
					}
					if (map3[6][27] != BLOCK6 || map3[6][27] == BLOCK6)
					{

						if (map3[6][27] == BLOCK6 && map3[playerMapY][playerMapX] == /*6以降は後で*/map3[4][9])
						{
							map3[playerMapY][playerMapX] = BLOCK6;
							map3[6][27] = YUKA;
						}
					}
					if (map3[7][27] != BLOCK7 || map3[7][27] == BLOCK7)
					{
						if (map3[7][27] == BLOCK7 && map3[playerMapY][playerMapX] == map3[4][9])
						{
							map3[playerMapY][playerMapX] = BLOCK7;
							map3[7][27] = YUKA;
						}
					}
					if (map3[8][27] != BLOCK8 || map3[8][27] == BLOCK8)
					{
						if (map3[8][27] == BLOCK8 && map3[playerMapY][playerMapX] == map3[4][9])
						{
							map3[playerMapY][playerMapX] = BLOCK8;
							map3[8][27] = YUKA;
						}
					}
					playerPosX -= playerSpeed;
				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK1)
				{
					map3[1][27] = BLOCK1;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = ZE;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK22)
				{
					map3[2][27] = BLOCK22;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = ZE;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK3)
				{
					map3[3][27] = BLOCK3;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = ZE;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK4)
				{
					map3[4][27] = BLOCK4;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = ZE;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK5)
				{
					map3[5][27] = BLOCK5;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = ZE;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK6)
				{
					map3[6][27] = BLOCK6;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = ZE;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK7)
				{
					map3[7][27] = BLOCK7;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = ZE;
					playerPosX -= playerSpeed;

				}
				if (map3[playerMapY][playerMapX - 1] == BLOCK8)
				{
					map3[8][27] = BLOCK8;
					map3[playerMapY][playerMapX] = YUKA;
					map3[playerMapY][playerMapX - 1] = ZE;
					playerPosX -= playerSpeed;

				}
			}


			if (keys[DIK_D] && preKeys[DIK_D] == 0 || keys[DIK_RIGHT] && preKeys[DIK_RIGHT] == 0)
			{
				playerTmpX = playerPosX + playerSpeed;
				playerMapX = playerTmpX / KBlockSize;
				//何もないから実際に進ませる
				if (map3[playerMapY][playerMapX] == YUKA)
				{
					playerPosX += playerSpeed;
				}
				if (map3[playerMapY][playerMapX] == GOAL)
				{
					playerPosX += playerSpeed;
				}
				if (map3[playerMapY][playerMapX] == THORN)
				{
					playerPosX += playerSpeed;
				}

				if (map3[playerMapY][playerMapX] == A)
				{
					if (map3[playerMapY][playerMapX + 1] == YUKA)
					{
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = A;
						if (map3[1][27] != BLOCK1 || map3[1][27] == BLOCK1)
						{
							if (map3[1][27] == BLOCK1 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK1;
								map3[1][27] = YUKA;
							}
						}
						if (map3[2][27] != BLOCK22 || map3[2][27] == BLOCK22)
						{
							if (map3[2][27] == BLOCK22 && map3[playerMapY][playerMapX] == map3[4][11])
							{
								map3[playerMapY][playerMapX] = BLOCK22;
								map3[2][27] = YUKA;
							}
						}
						if (map3[3][27] != BLOCK3 || map3[3][27] == BLOCK3)
						{
							if (map3[3][27] == BLOCK3 && map3[playerMapY][playerMapX] == map3[4][13])
							{
								map3[playerMapY][playerMapX] = BLOCK3;
								map3[3][27] = YUKA;
							}
						}
						if (map3[4][27] != BLOCK4 || map3[4][27] == BLOCK4)
						{
							if (map3[4][27] == BLOCK4 && map3[playerMapY][playerMapX] == map3[4][15])
							{
								map3[playerMapY][playerMapX] = BLOCK4;
								map3[4][27] = YUKA;
							}
						}
						if (map3[5][27] != BLOCK5 || map3[5][27] == BLOCK5)
						{
							if (map3[5][27] == BLOCK5 && map3[playerMapY][playerMapX] == map3[4][17])
							{
								map3[playerMapY][playerMapX] = BLOCK5;
								map3[5][27] = YUKA;
							}
						}
						if (map3[6][27] != BLOCK6 || map3[6][27] == BLOCK6)
						{

							if (map3[6][27] == BLOCK6 && map3[playerMapY][playerMapX] == /*6以降は後で*/map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK6;
								map3[6][27] = YUKA;
							}
						}
						if (map3[7][27] != BLOCK7 || map3[7][27] == BLOCK7)
						{
							if (map3[7][27] == BLOCK7 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK7;
								map3[7][27] = YUKA;
							}
						}
						if (map3[8][27] != BLOCK8 || map3[8][27] == BLOCK8)
						{
							if (map3[8][27] == BLOCK8 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK8;
								map3[8][27] = YUKA;
							}
						}
						playerPosX += playerSpeed;
					}

					if (map3[playerMapY][playerMapX + 1] == BLOCK1)
					{
						map3[1][27] = BLOCK1;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = A;
						playerPosX += playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK22)
					{
						map3[2][27] = BLOCK22;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = A;
						playerPosX += playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK3)
					{
						map3[3][27] = BLOCK3;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = A;
						playerPosX += playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK4)
					{
						map3[4][27] = BLOCK4;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = A;
						playerPosX += playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK5)
					{
						map3[5][27] = BLOCK5;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = A;
						playerPosX += playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK6)
					{
						map3[6][27] = BLOCK6;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = A;
						playerPosX += playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK7)
					{
						map3[7][27] = BLOCK7;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = A;
						playerPosX = playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK8)
					{
						map3[8][27] = BLOCK8;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = A;
						playerPosX += playerSpeed;

					}



				}

				// 1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111
				// ここから直して
				if (map3[playerMapY][playerMapX] == KE)
				{
					if (map3[playerMapY][playerMapX + 1] == YUKA)
					{
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = KE; //ここをKEに変える　したも同じ
						if (map3[1][27] != BLOCK1 || map3[1][27] == BLOCK1)
						{
							if (map3[1][27] == BLOCK1 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK1;
								map3[1][27] = YUKA;
							}
						}
						if (map3[2][27] != BLOCK22 || map3[2][27] == BLOCK22)
						{
							if (map3[2][27] == BLOCK22 && map3[playerMapY][playerMapX] == map3[4][11])
							{
								map3[playerMapY][playerMapX] = BLOCK22;
								map3[2][27] = YUKA;
							}
						}
						if (map3[3][27] != BLOCK3 || map3[3][27] == BLOCK3)
						{
							if (map3[3][27] == BLOCK3 && map3[playerMapY][playerMapX] == map3[4][13])
							{
								map3[playerMapY][playerMapX] = BLOCK3;
								map3[3][27] = YUKA;
							}
						}
						if (map3[4][27] != BLOCK4 || map3[4][27] == BLOCK4)
						{
							if (map3[4][27] == BLOCK4 && map3[playerMapY][playerMapX] == map3[4][15])
							{
								map3[playerMapY][playerMapX] = BLOCK4;
								map3[4][27] = YUKA;
							}
						}
						if (map3[5][27] != BLOCK5 || map3[5][27] == BLOCK5)
						{
							if (map3[5][27] == BLOCK5 && map3[playerMapY][playerMapX] == map3[4][17])
							{
								map3[playerMapY][playerMapX] = BLOCK5;
								map3[5][27] = YUKA;
							}
						}
						if (map3[6][27] != BLOCK6 || map3[6][27] == BLOCK6)
						{

							if (map3[6][27] == BLOCK6 && map3[playerMapY][playerMapX] == /*6以降は後で*/map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK6;
								map3[6][27] = YUKA;
							}
						}
						if (map3[7][27] != BLOCK7 || map3[7][27] == BLOCK7)
						{
							if (map3[7][27] == BLOCK7 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK7;
								map3[7][27] = YUKA;
							}
						}
						if (map3[8][27] != BLOCK8 || map3[8][27] == BLOCK8)
						{
							if (map3[8][27] == BLOCK8 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK8;
								map3[8][27] = YUKA;
							}
						}
						playerPosX += playerSpeed;
					}

					if (map3[playerMapY][playerMapX + 1] == BLOCK1)
					{
						map3[1][27] = BLOCK1;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = KE;
						playerPosX += playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK22)
					{
						map3[2][27] = BLOCK22;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = KE;
						playerPosX += playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK3)
					{
						map3[3][27] = BLOCK3;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = KE;
						playerPosX += playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK4)
					{
						map3[4][27] = BLOCK4;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = KE;
						playerPosX += playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK5)
					{
						map3[5][27] = BLOCK5;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = KE;
						playerPosX += playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK6)
					{
						map3[6][27] = BLOCK6;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = KE;
						playerPosX += playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK7)
					{
						map3[7][27] = BLOCK7;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = KE;
						playerPosX = playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK8)
					{
						map3[8][27] = BLOCK8;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = KE;
						playerPosX += playerSpeed;

					}
				}
				if (map3[playerMapY][playerMapX] == E)
				{
					if (map3[playerMapY][playerMapX + 1] == YUKA)
					{
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = E;
						if (map3[1][27] != BLOCK1 || map3[1][27] == BLOCK1)
						{
							if (map3[1][27] == BLOCK1 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK1;
								map3[1][27] = YUKA;
							}
						}
						if (map3[2][27] != BLOCK22 || map3[2][27] == BLOCK22)
						{
							if (map3[2][27] == BLOCK22 && map3[playerMapY][playerMapX] == map3[4][11])
							{
								map3[playerMapY][playerMapX] = BLOCK22;
								map3[2][27] = YUKA;
							}
						}
						if (map3[3][27] != BLOCK3 || map3[3][27] == BLOCK3)
						{
							if (map3[3][27] == BLOCK3 && map3[playerMapY][playerMapX] == map3[4][13])
							{
								map3[playerMapY][playerMapX] = BLOCK3;
								map3[3][27] = YUKA;
							}
						}
						if (map3[4][27] != BLOCK4 || map3[4][27] == BLOCK4)
						{
							if (map3[4][27] == BLOCK4 && map3[playerMapY][playerMapX] == map3[4][15])
							{
								map3[playerMapY][playerMapX] = BLOCK4;
								map3[4][27] = YUKA;
							}
						}
						if (map3[5][27] != BLOCK5 || map3[5][27] == BLOCK5)
						{
							if (map3[5][27] == BLOCK5 && map3[playerMapY][playerMapX] == map3[4][17])
							{
								map3[playerMapY][playerMapX] = BLOCK5;
								map3[5][27] = YUKA;
							}
						}
						if (map3[6][27] != BLOCK6 || map3[6][27] == BLOCK6)
						{

							if (map3[6][27] == BLOCK6 && map3[playerMapY][playerMapX] == /*6以降は後で*/map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK6;
								map3[6][27] = YUKA;
							}
						}
						if (map3[7][27] != BLOCK7 || map3[7][27] == BLOCK7)
						{
							if (map3[7][27] == BLOCK7 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK7;
								map3[7][27] = YUKA;
							}
						}
						if (map3[8][27] != BLOCK8 || map3[8][27] == BLOCK8)
						{
							if (map3[8][27] == BLOCK8 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK8;
								map3[8][27] = YUKA;
							}
						}
						playerPosX += playerSpeed;
					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK1)
					{
						map3[1][27] = BLOCK1;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = E;
						playerPosX += playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK22)
					{
						map3[2][27] = BLOCK22;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = E;
						playerPosX += playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK3)
					{
						map3[3][27] = BLOCK3;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = E;
						playerPosX += playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK4)
					{
						map3[4][27] = BLOCK4;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = E;
						playerPosX += playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK5)
					{
						map3[5][27] = BLOCK5;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = E;
						playerPosX += playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK6)
					{
						map3[6][27] = BLOCK6;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = E;
						playerPosX += playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK7)
					{
						map3[7][27] = BLOCK7;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = E;
						playerPosX = playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK8)
					{
						map3[8][27] = BLOCK8;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = E;
						playerPosX += playerSpeed;

					}
				}
				if (map3[playerMapY][playerMapX] == KA)
				{
					if (map3[playerMapY][playerMapX + 1] == YUKA)
					{
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = KA;
						if (map3[1][27] != BLOCK1 || map3[1][27] == BLOCK1)
						{
							if (map3[1][27] == BLOCK1 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK1;
								map3[1][27] = YUKA;
							}
						}
						if (map3[2][27] != BLOCK22 || map3[2][27] == BLOCK22)
						{
							if (map3[2][27] == BLOCK22 && map3[playerMapY][playerMapX] == map3[4][11])
							{
								map3[playerMapY][playerMapX] = BLOCK22;
								map3[2][27] = YUKA;
							}
						}
						if (map3[3][27] != BLOCK3 || map3[3][27] == BLOCK3)
						{
							if (map3[3][27] == BLOCK3 && map3[playerMapY][playerMapX] == map3[4][13])
							{
								map3[playerMapY][playerMapX] = BLOCK3;
								map3[3][27] = YUKA;
							}
						}
						if (map3[4][27] != BLOCK4 || map3[4][27] == BLOCK4)
						{
							if (map3[4][27] == BLOCK4 && map3[playerMapY][playerMapX] == map3[4][15])
							{
								map3[playerMapY][playerMapX] = BLOCK4;
								map3[4][27] = YUKA;
							}
						}
						if (map3[5][27] != BLOCK5 || map3[5][27] == BLOCK5)
						{
							if (map3[5][27] == BLOCK5 && map3[playerMapY][playerMapX] == map3[4][17])
							{
								map3[playerMapY][playerMapX] = BLOCK5;
								map3[5][27] = YUKA;
							}
						}
						if (map3[6][27] != BLOCK6 || map3[6][27] == BLOCK6)
						{

							if (map3[6][27] == BLOCK6 && map3[playerMapY][playerMapX] == /*6以降は後で*/map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK6;
								map3[6][27] = YUKA;
							}
						}
						if (map3[7][27] != BLOCK7 || map3[7][27] == BLOCK7)
						{
							if (map3[7][27] == BLOCK7 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK7;
								map3[7][27] = YUKA;
							}
						}
						if (map3[8][27] != BLOCK8 || map3[8][27] == BLOCK8)
						{
							if (map3[8][27] == BLOCK8 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK8;
								map3[8][27] = YUKA;
							}
						}
						playerPosX += playerSpeed;
					}

					if (map3[playerMapY][playerMapX + 1] == BLOCK1)
					{
						map3[1][27] = BLOCK1;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = KA;
						playerPosX += playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK22)
					{
						map3[2][27] = BLOCK22;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = KA;
						playerPosX += playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK3)
					{
						map3[3][27] = BLOCK3;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = KA;
						playerPosX += playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK4)
					{
						map3[4][27] = BLOCK4;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = KA;
						playerPosX += playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK5)
					{
						map3[5][27] = BLOCK5;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = KA;
						playerPosX += playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK6)
					{
						map3[6][27] = BLOCK6;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = KA;
						playerPosX += playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK7)
					{
						map3[7][27] = BLOCK7;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = KA;
						playerPosX = playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK8)
					{
						map3[8][27] = BLOCK8;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = KA;
						playerPosX += playerSpeed;

					}
				}
				if (map3[playerMapY][playerMapX] == KU)
				{
					if (map3[playerMapY][playerMapX + 1] == YUKA)
					{
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = KU;
						if (map3[1][27] != BLOCK1 || map3[1][27] == BLOCK1)
						{
							if (map3[1][27] == BLOCK1 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK1;
								map3[1][27] = YUKA;
							}
						}
						if (map3[2][27] != BLOCK22 || map3[2][27] == BLOCK22)
						{
							if (map3[2][27] == BLOCK22 && map3[playerMapY][playerMapX] == map3[4][11])
							{
								map3[playerMapY][playerMapX] = BLOCK22;
								map3[2][27] = YUKA;
							}
						}
						if (map3[3][27] != BLOCK3 || map3[3][27] == BLOCK3)
						{
							if (map3[3][27] == BLOCK3 && map3[playerMapY][playerMapX] == map3[4][13])
							{
								map3[playerMapY][playerMapX] = BLOCK3;
								map3[3][27] = YUKA;
							}
						}
						if (map3[4][27] != BLOCK4 || map3[4][27] == BLOCK4)
						{
							if (map3[4][27] == BLOCK4 && map3[playerMapY][playerMapX] == map3[4][15])
							{
								map3[playerMapY][playerMapX] = BLOCK4;
								map3[4][27] = YUKA;
							}
						}
						if (map3[5][27] != BLOCK5 || map3[5][27] == BLOCK5)
						{
							if (map3[5][27] == BLOCK5 && map3[playerMapY][playerMapX] == map3[4][17])
							{
								map3[playerMapY][playerMapX] = BLOCK5;
								map3[5][27] = YUKA;
							}
						}
						if (map3[6][27] != BLOCK6 || map3[6][27] == BLOCK6)
						{

							if (map3[6][27] == BLOCK6 && map3[playerMapY][playerMapX] == /*6以降は後で*/map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK6;
								map3[6][27] = YUKA;
							}
						}
						if (map3[7][27] != BLOCK7 || map3[7][27] == BLOCK7)
						{
							if (map3[7][27] == BLOCK7 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK7;
								map3[7][27] = YUKA;
							}
						}
						if (map3[8][27] != BLOCK8 || map3[8][27] == BLOCK8)
						{
							if (map3[8][27] == BLOCK8 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK8;
								map3[8][27] = YUKA;
							}
						}
						playerPosX += playerSpeed;
					}

					if (map3[playerMapY][playerMapX + 1] == BLOCK1)
					{
						map3[1][27] = BLOCK1;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = KU;
						playerPosX += playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK22)
					{
						map3[2][27] = BLOCK22;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = KU;
						playerPosX += playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK3)
					{
						map3[3][27] = BLOCK3;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = KU;
						playerPosX += playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK4)
					{
						map3[4][27] = BLOCK4;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = KU;
						playerPosX += playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK5)
					{
						map3[5][27] = BLOCK5;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = KU;
						playerPosX += playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK6)
					{
						map3[6][27] = BLOCK6;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = KU;
						playerPosX += playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK7)
					{
						map3[7][27] = BLOCK7;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = KU;
						playerPosX = playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK8)
					{
						map3[8][27] = BLOCK8;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = KU;
						playerPosX += playerSpeed;

					}
				}
				if (map3[playerMapY][playerMapX] == NO)
				{
					if (map3[playerMapY][playerMapX + 1] == YUKA)
					{
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = NO;
						if (map3[1][27] != BLOCK1 || map3[1][27] == BLOCK1)
						{
							if (map3[1][27] == BLOCK1 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK1;
								map3[1][27] = YUKA;
							}
						}
						if (map3[2][27] != BLOCK22 || map3[2][27] == BLOCK22)
						{
							if (map3[2][27] == BLOCK22 && map3[playerMapY][playerMapX] == map3[4][11])
							{
								map3[playerMapY][playerMapX] = BLOCK22;
								map3[2][27] = YUKA;
							}
						}
						if (map3[3][27] != BLOCK3 || map3[3][27] == BLOCK3)
						{
							if (map3[3][27] == BLOCK3 && map3[playerMapY][playerMapX] == map3[4][13])
							{
								map3[playerMapY][playerMapX] = BLOCK3;
								map3[3][27] = YUKA;
							}
						}
						if (map3[4][27] != BLOCK4 || map3[4][27] == BLOCK4)
						{
							if (map3[4][27] == BLOCK4 && map3[playerMapY][playerMapX] == map3[4][15])
							{
								map3[playerMapY][playerMapX] = BLOCK4;
								map3[4][27] = YUKA;
							}
						}
						if (map3[5][27] != BLOCK5 || map3[5][27] == BLOCK5)
						{
							if (map3[5][27] == BLOCK5 && map3[playerMapY][playerMapX] == map3[4][17])
							{
								map3[playerMapY][playerMapX] = BLOCK5;
								map3[5][27] = YUKA;
							}
						}
						if (map3[6][27] != BLOCK6 || map3[6][27] == BLOCK6)
						{

							if (map3[6][27] == BLOCK6 && map3[playerMapY][playerMapX] == /*6以降は後で*/map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK6;
								map3[6][27] = YUKA;
							}
						}
						if (map3[7][27] != BLOCK7 || map3[7][27] == BLOCK7)
						{
							if (map3[7][27] == BLOCK7 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK7;
								map3[7][27] = YUKA;
							}
						}
						if (map3[8][27] != BLOCK8 || map3[8][27] == BLOCK8)
						{
							if (map3[8][27] == BLOCK8 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK8;
								map3[8][27] = YUKA;
							}
						}
						playerPosX += playerSpeed;
					}

					if (map3[playerMapY][playerMapX + 1] == BLOCK1)
					{
						map3[1][27] = BLOCK1;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = NO;
						playerPosX += playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK22)
					{
						map3[2][27] = BLOCK22;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = NO;
						playerPosX += playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK3)
					{
						map3[3][27] = BLOCK3;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = NO;
						playerPosX += playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK4)
					{
						map3[4][27] = BLOCK4;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = NO;
						playerPosX += playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK5)
					{
						map3[5][27] = BLOCK5;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = NO;
						playerPosX += playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK6)
					{
						map3[6][27] = BLOCK6;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = NO;
						playerPosX += playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK7)
					{
						map3[7][27] = BLOCK7;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = NO;
						playerPosX = playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK8)
					{
						map3[8][27] = BLOCK8;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = NO;
						playerPosX += playerSpeed;

					}
				}
				if (map3[playerMapY][playerMapX] == GA)
				{
					if (map3[playerMapY][playerMapX + 1] == YUKA)
					{
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = GA;
						if (map3[1][27] != BLOCK1 || map3[1][27] == BLOCK1)
						{
							if (map3[1][27] == BLOCK1 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK1;
								map3[1][27] = YUKA;
							}
						}
						if (map3[2][27] != BLOCK22 || map3[2][27] == BLOCK22)
						{
							if (map3[2][27] == BLOCK22 && map3[playerMapY][playerMapX] == map3[4][11])
							{
								map3[playerMapY][playerMapX] = BLOCK22;
								map3[2][27] = YUKA;
							}
						}
						if (map3[3][27] != BLOCK3 || map3[3][27] == BLOCK3)
						{
							if (map3[3][27] == BLOCK3 && map3[playerMapY][playerMapX] == map3[4][13])
							{
								map3[playerMapY][playerMapX] = BLOCK3;
								map3[3][27] = YUKA;
							}
						}
						if (map3[4][27] != BLOCK4 || map3[4][27] == BLOCK4)
						{
							if (map3[4][27] == BLOCK4 && map3[playerMapY][playerMapX] == map3[4][15])
							{
								map3[playerMapY][playerMapX] = BLOCK4;
								map3[4][27] = YUKA;
							}
						}
						if (map3[5][27] != BLOCK5 || map3[5][27] == BLOCK5)
						{
							if (map3[5][27] == BLOCK5 && map3[playerMapY][playerMapX] == map3[4][17])
							{
								map3[playerMapY][playerMapX] = BLOCK5;
								map3[5][27] = YUKA;
							}
						}
						if (map3[6][27] != BLOCK6 || map3[6][27] == BLOCK6)
						{

							if (map3[6][27] == BLOCK6 && map3[playerMapY][playerMapX] == /*6以降は後で*/map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK6;
								map3[6][27] = YUKA;
							}
						}
						if (map3[7][27] != BLOCK7 || map3[7][27] == BLOCK7)
						{
							if (map3[7][27] == BLOCK7 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK7;
								map3[7][27] = YUKA;
							}
						}
						if (map3[8][27] != BLOCK8 || map3[8][27] == BLOCK8)
						{
							if (map3[8][27] == BLOCK8 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK8;
								map3[8][27] = YUKA;
							}
						}
						playerPosX += playerSpeed;
					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK1)
					{
						map3[1][27] = BLOCK1;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = GA;
						playerPosX += playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK22)
					{
						map3[2][27] = BLOCK22;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = GA;
						playerPosX += playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK3)
					{
						map3[3][27] = BLOCK3;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = GA;
						playerPosX += playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK4)
					{
						map3[4][27] = BLOCK4;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = GA;
						playerPosX += playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK5)
					{
						map3[5][27] = BLOCK5;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = GA;
						playerPosX += playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK6)
					{
						map3[6][27] = BLOCK6;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = GA;
						playerPosX += playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK7)
					{
						map3[7][27] = BLOCK7;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = GA;
						playerPosX = playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK8)
					{
						map3[8][27] = BLOCK8;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = GA;
						playerPosX += playerSpeed;

					}
				}
				if (map3[playerMapY][playerMapX] == SU)
				{
					if (map3[playerMapY][playerMapX + 1] == YUKA)
					{
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = SU;
						if (map3[1][27] != BLOCK1 || map3[1][27] == BLOCK1)
						{
							if (map3[1][27] == BLOCK1 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK1;
								map3[1][27] = YUKA;
							}
						}
						if (map3[2][27] != BLOCK22 || map3[2][27] == BLOCK22)
						{
							if (map3[2][27] == BLOCK22 && map3[playerMapY][playerMapX] == map3[4][11])
							{
								map3[playerMapY][playerMapX] = BLOCK22;
								map3[2][27] = YUKA;
							}
						}
						if (map3[3][27] != BLOCK3 || map3[3][27] == BLOCK3)
						{
							if (map3[3][27] == BLOCK3 && map3[playerMapY][playerMapX] == map3[4][13])
							{
								map3[playerMapY][playerMapX] = BLOCK3;
								map3[3][27] = YUKA;
							}
						}
						if (map3[4][27] != BLOCK4 || map3[4][27] == BLOCK4)
						{
							if (map3[4][27] == BLOCK4 && map3[playerMapY][playerMapX] == map3[4][15])
							{
								map3[playerMapY][playerMapX] = BLOCK4;
								map3[4][27] = YUKA;
							}
						}
						if (map3[5][27] != BLOCK5 || map3[5][27] == BLOCK5)
						{
							if (map3[5][27] == BLOCK5 && map3[playerMapY][playerMapX] == map3[4][17])
							{
								map3[playerMapY][playerMapX] = BLOCK5;
								map3[5][27] = YUKA;
							}
						}
						if (map3[6][27] != BLOCK6 || map3[6][27] == BLOCK6)
						{

							if (map3[6][27] == BLOCK6 && map3[playerMapY][playerMapX] == /*6以降は後で*/map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK6;
								map3[6][27] = YUKA;
							}
						}
						if (map3[7][27] != BLOCK7 || map3[7][27] == BLOCK7)
						{
							if (map3[7][27] == BLOCK7 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK7;
								map3[7][27] = YUKA;
							}
						}
						if (map3[8][27] != BLOCK8 || map3[8][27] == BLOCK8)
						{
							if (map3[8][27] == BLOCK8 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK8;
								map3[8][27] = YUKA;
							}
						}
						playerPosX += playerSpeed;
					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK1)
					{
						map3[1][27] = BLOCK1;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = SU;
						playerPosX += playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK22)
					{
						map3[2][27] = BLOCK22;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = SU;
						playerPosX += playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK3)
					{
						map3[3][27] = BLOCK3;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = SU;
						playerPosX += playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK4)
					{
						map3[4][27] = BLOCK4;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = SU;
						playerPosX += playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK5)
					{
						map3[5][27] = BLOCK5;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = SU;
						playerPosX += playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK6)
					{
						map3[6][27] = BLOCK6;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = SU;
						playerPosX += playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK7)
					{
						map3[7][27] = BLOCK7;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = SU;
						playerPosX = playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK8)
					{
						map3[8][27] = BLOCK8;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = SU;
						playerPosX += playerSpeed;

					}
				}
				if (map3[playerMapY][playerMapX] == SO)
				{
					if (map3[playerMapY][playerMapX + 1] == YUKA)
					{
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = SO;
						if (map3[1][27] != BLOCK1 || map3[1][27] == BLOCK1)
						{
							if (map3[1][27] == BLOCK1 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK1;
								map3[1][27] = YUKA;
							}
						}
						if (map3[2][27] != BLOCK22 || map3[2][27] == BLOCK22)
						{
							if (map3[2][27] == BLOCK22 && map3[playerMapY][playerMapX] == map3[4][11])
							{
								map3[playerMapY][playerMapX] = BLOCK22;
								map3[2][27] = YUKA;
							}
						}
						if (map3[3][27] != BLOCK3 || map3[3][27] == BLOCK3)
						{
							if (map3[3][27] == BLOCK3 && map3[playerMapY][playerMapX] == map3[4][13])
							{
								map3[playerMapY][playerMapX] = BLOCK3;
								map3[3][27] = YUKA;
							}
						}
						if (map3[4][27] != BLOCK4 || map3[4][27] == BLOCK4)
						{
							if (map3[4][27] == BLOCK4 && map3[playerMapY][playerMapX] == map3[4][15])
							{
								map3[playerMapY][playerMapX] = BLOCK4;
								map3[4][27] = YUKA;
							}
						}
						if (map3[5][27] != BLOCK5 || map3[5][27] == BLOCK5)
						{
							if (map3[5][27] == BLOCK5 && map3[playerMapY][playerMapX] == map3[4][17])
							{
								map3[playerMapY][playerMapX] = BLOCK5;
								map3[5][27] = YUKA;
							}
						}
						if (map3[6][27] != BLOCK6 || map3[6][27] == BLOCK6)
						{

							if (map3[6][27] == BLOCK6 && map3[playerMapY][playerMapX] == /*6以降は後で*/map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK6;
								map3[6][27] = YUKA;
							}
						}
						if (map3[7][27] != BLOCK7 || map3[7][27] == BLOCK7)
						{
							if (map3[7][27] == BLOCK7 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK7;
								map3[7][27] = YUKA;
							}
						}
						if (map3[8][27] != BLOCK8 || map3[8][27] == BLOCK8)
						{
							if (map3[8][27] == BLOCK8 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK8;
								map3[8][27] = YUKA;
							}
						}
						playerPosX += playerSpeed;
					}

					if (map3[playerMapY][playerMapX + 1] == BLOCK1)
					{
						map3[1][27] = BLOCK1;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = SO;
						playerPosX += playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK22)
					{
						map3[2][27] = BLOCK22;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = SO;
						playerPosX += playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK3)
					{
						map3[3][27] = BLOCK3;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = SO;
						playerPosX += playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK4)
					{
						map3[4][27] = BLOCK4;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = SO;
						playerPosX += playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK5)
					{
						map3[5][27] = BLOCK5;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = SO;
						playerPosX += playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK6)
					{
						map3[6][27] = BLOCK6;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = SO;
						playerPosX += playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK7)
					{
						map3[7][27] = BLOCK7;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = SO;
						playerPosX = playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK8)
					{
						map3[8][27] = BLOCK8;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = SO;
						playerPosX += playerSpeed;

					}
				}
				if (map3[playerMapY][playerMapX] == NI)
				{
					if (map3[playerMapY][playerMapX + 1] == YUKA)
					{
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = NI;
						if (map3[1][27] != BLOCK1 || map3[1][27] == BLOCK1)
						{
							if (map3[1][27] == BLOCK1 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK1;
								map3[1][27] = YUKA;
							}
						}
						if (map3[2][27] != BLOCK22 || map3[2][27] == BLOCK22)
						{
							if (map3[2][27] == BLOCK22 && map3[playerMapY][playerMapX] == map3[4][11])
							{
								map3[playerMapY][playerMapX] = BLOCK22;
								map3[2][27] = YUKA;
							}
						}
						if (map3[3][27] != BLOCK3 || map3[3][27] == BLOCK3)
						{
							if (map3[3][27] == BLOCK3 && map3[playerMapY][playerMapX] == map3[4][13])
							{
								map3[playerMapY][playerMapX] = BLOCK3;
								map3[3][27] = YUKA;
							}
						}
						if (map3[4][27] != BLOCK4 || map3[4][27] == BLOCK4)
						{
							if (map3[4][27] == BLOCK4 && map3[playerMapY][playerMapX] == map3[4][15])
							{
								map3[playerMapY][playerMapX] = BLOCK4;
								map3[4][27] = YUKA;
							}
						}
						if (map3[5][27] != BLOCK5 || map3[5][27] == BLOCK5)
						{
							if (map3[5][27] == BLOCK5 && map3[playerMapY][playerMapX] == map3[4][17])
							{
								map3[playerMapY][playerMapX] = BLOCK5;
								map3[5][27] = YUKA;
							}
						}
						if (map3[6][27] != BLOCK6 || map3[6][27] == BLOCK6)
						{

							if (map3[6][27] == BLOCK6 && map3[playerMapY][playerMapX] == /*6以降は後で*/map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK6;
								map3[6][27] = YUKA;
							}
						}
						if (map3[7][27] != BLOCK7 || map3[7][27] == BLOCK7)
						{
							if (map3[7][27] == BLOCK7 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK7;
								map3[7][27] = YUKA;
							}
						}
						if (map3[8][27] != BLOCK8 || map3[8][27] == BLOCK8)
						{
							if (map3[8][27] == BLOCK8 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK8;
								map3[8][27] = YUKA;
							}
						}
						playerPosX += playerSpeed;
					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK1)
					{
						map3[1][27] = BLOCK1;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = NI;
						playerPosX += playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK22)
					{
						map3[2][27] = BLOCK22;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = NI;
						playerPosX += playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK3)
					{
						map3[3][27] = BLOCK3;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = NI;
						playerPosX += playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK4)
					{
						map3[4][27] = BLOCK4;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = NI;
						playerPosX += playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK5)
					{
						map3[5][27] = BLOCK5;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = NI;
						playerPosX += playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK6)
					{
						map3[6][27] = BLOCK6;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = NI;
						playerPosX += playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK7)
					{
						map3[7][27] = BLOCK7;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = NI;
						playerPosX = playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK8)
					{
						map3[8][27] = BLOCK8;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = NI;
						playerPosX += playerSpeed;

					}
				}
				if (map3[playerMapY][playerMapX] == CHI)
				{
					if (map3[playerMapY][playerMapX + 1] == YUKA)
					{
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = CHI;
						if (map3[1][27] != BLOCK1 || map3[1][27] == BLOCK1)
						{
							if (map3[1][27] == BLOCK1 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK1;
								map3[1][27] = YUKA;
							}
						}
						if (map3[2][27] != BLOCK22 || map3[2][27] == BLOCK22)
						{
							if (map3[2][27] == BLOCK22 && map3[playerMapY][playerMapX] == map3[4][11])
							{
								map3[playerMapY][playerMapX] = BLOCK22;
								map3[2][27] = YUKA;
							}
						}
						if (map3[3][27] != BLOCK3 || map3[3][27] == BLOCK3)
						{
							if (map3[3][27] == BLOCK3 && map3[playerMapY][playerMapX] == map3[4][13])
							{
								map3[playerMapY][playerMapX] = BLOCK3;
								map3[3][27] = YUKA;
							}
						}
						if (map3[4][27] != BLOCK4 || map3[4][27] == BLOCK4)
						{
							if (map3[4][27] == BLOCK4 && map3[playerMapY][playerMapX] == map3[4][15])
							{
								map3[playerMapY][playerMapX] = BLOCK4;
								map3[4][27] = YUKA;
							}
						}
						if (map3[5][27] != BLOCK5 || map3[5][27] == BLOCK5)
						{
							if (map3[5][27] == BLOCK5 && map3[playerMapY][playerMapX] == map3[4][17])
							{
								map3[playerMapY][playerMapX] = BLOCK5;
								map3[5][27] = YUKA;
							}
						}
						if (map3[6][27] != BLOCK6 || map3[6][27] == BLOCK6)
						{

							if (map3[6][27] == BLOCK6 && map3[playerMapY][playerMapX] == /*6以降は後で*/map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK6;
								map3[6][27] = YUKA;
							}
						}
						if (map3[7][27] != BLOCK7 || map3[7][27] == BLOCK7)
						{
							if (map3[7][27] == BLOCK7 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK7;
								map3[7][27] = YUKA;
							}
						}
						if (map3[8][27] != BLOCK8 || map3[8][27] == BLOCK8)
						{
							if (map3[8][27] == BLOCK8 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK8;
								map3[8][27] = YUKA;
							}
						}
						playerPosX += playerSpeed;
					}

					if (map3[playerMapY][playerMapX + 1] == BLOCK1)
					{
						map3[1][27] = BLOCK1;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = CHI;
						playerPosX += playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK22)
					{
						map3[2][27] = BLOCK22;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = CHI;
						playerPosX += playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK3)
					{
						map3[3][27] = BLOCK3;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = CHI;
						playerPosX += playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK4)
					{
						map3[4][27] = BLOCK4;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = CHI;
						playerPosX += playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK5)
					{
						map3[5][27] = BLOCK5;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = CHI;
						playerPosX += playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK6)
					{
						map3[6][27] = BLOCK6;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = CHI;
						playerPosX += playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK7)
					{
						map3[7][27] = BLOCK7;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = CHI;
						playerPosX = playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK8)
					{
						map3[8][27] = BLOCK8;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = CHI;
						playerPosX += playerSpeed;

					}
				}

				if (map3[playerMapY][playerMapX] == NU)
				{
					if (map3[playerMapY][playerMapX + 1] == YUKA)
					{
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = NU;
						if (map3[1][27] != BLOCK1 || map3[1][27] == BLOCK1)
						{
							if (map3[1][27] == BLOCK1 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK1;
								map3[1][27] = YUKA;
							}
						}
						if (map3[2][27] != BLOCK22 || map3[2][27] == BLOCK22)
						{
							if (map3[2][27] == BLOCK22 && map3[playerMapY][playerMapX] == map3[4][11])
							{
								map3[playerMapY][playerMapX] = BLOCK22;
								map3[2][27] = YUKA;
							}
						}
						if (map3[3][27] != BLOCK3 || map3[3][27] == BLOCK3)
						{
							if (map3[3][27] == BLOCK3 && map3[playerMapY][playerMapX] == map3[4][13])
							{
								map3[playerMapY][playerMapX] = BLOCK3;
								map3[3][27] = YUKA;
							}
						}
						if (map3[4][27] != BLOCK4 || map3[4][27] == BLOCK4)
						{
							if (map3[4][27] == BLOCK4 && map3[playerMapY][playerMapX] == map3[4][15])
							{
								map3[playerMapY][playerMapX] = BLOCK4;
								map3[4][27] = YUKA;
							}
						}
						if (map3[5][27] != BLOCK5 || map3[5][27] == BLOCK5)
						{
							if (map3[5][27] == BLOCK5 && map3[playerMapY][playerMapX] == map3[4][17])
							{
								map3[playerMapY][playerMapX] = BLOCK5;
								map3[5][27] = YUKA;
							}
						}
						if (map3[6][27] != BLOCK6 || map3[6][27] == BLOCK6)
						{

							if (map3[6][27] == BLOCK6 && map3[playerMapY][playerMapX] == /*6以降は後で*/map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK6;
								map3[6][27] = YUKA;
							}
						}
						if (map3[7][27] != BLOCK7 || map3[7][27] == BLOCK7)
						{
							if (map3[7][27] == BLOCK7 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK7;
								map3[7][27] = YUKA;
							}
						}
						if (map3[8][27] != BLOCK8 || map3[8][27] == BLOCK8)
						{
							if (map3[8][27] == BLOCK8 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK8;
								map3[8][27] = YUKA;
							}
						}
						playerPosX += playerSpeed;
					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK1)
					{
						map3[1][27] = BLOCK1;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = NU;
						playerPosX += playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK22)
					{
						map3[2][27] = BLOCK22;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = NU;
						playerPosX += playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK3)
					{
						map3[3][27] = BLOCK3;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = NU;
						playerPosX += playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK4)
					{
						map3[4][27] = BLOCK4;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = NU;
						playerPosX += playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK5)
					{
						map3[5][27] = BLOCK5;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = NU;
						playerPosX += playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK6)
					{
						map3[6][27] = BLOCK6;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = NU;
						playerPosX += playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK7)
					{
						map3[7][27] = BLOCK7;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = NU;
						playerPosX = playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK8)
					{
						map3[8][27] = BLOCK8;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = NU;
						playerPosX += playerSpeed;

					}
				}
				if (map3[playerMapY][playerMapX] == NE)
				{
					if (map3[playerMapY][playerMapX + 1] == YUKA)
					{
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = NE;
						if (map3[1][27] != BLOCK1 || map3[1][27] == BLOCK1)
						{
							if (map3[1][27] == BLOCK1 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK1;
								map3[1][27] = YUKA;
							}
						}
						if (map3[2][27] != BLOCK22 || map3[2][27] == BLOCK22)
						{
							if (map3[2][27] == BLOCK22 && map3[playerMapY][playerMapX] == map3[4][11])
							{
								map3[playerMapY][playerMapX] = BLOCK22;
								map3[2][27] = YUKA;
							}
						}
						if (map3[3][27] != BLOCK3 || map3[3][27] == BLOCK3)
						{
							if (map3[3][27] == BLOCK3 && map3[playerMapY][playerMapX] == map3[4][13])
							{
								map3[playerMapY][playerMapX] = BLOCK3;
								map3[3][27] = YUKA;
							}
						}
						if (map3[4][27] != BLOCK4 || map3[4][27] == BLOCK4)
						{
							if (map3[4][27] == BLOCK4 && map3[playerMapY][playerMapX] == map3[4][15])
							{
								map3[playerMapY][playerMapX] = BLOCK4;
								map3[4][27] = YUKA;
							}
						}
						if (map3[5][27] != BLOCK5 || map3[5][27] == BLOCK5)
						{
							if (map3[5][27] == BLOCK5 && map3[playerMapY][playerMapX] == map3[4][17])
							{
								map3[playerMapY][playerMapX] = BLOCK5;
								map3[5][27] = YUKA;
							}
						}
						if (map3[6][27] != BLOCK6 || map3[6][27] == BLOCK6)
						{

							if (map3[6][27] == BLOCK6 && map3[playerMapY][playerMapX] == /*6以降は後で*/map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK6;
								map3[6][27] = YUKA;
							}
						}
						if (map3[7][27] != BLOCK7 || map3[7][27] == BLOCK7)
						{
							if (map3[7][27] == BLOCK7 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK7;
								map3[7][27] = YUKA;
							}
						}
						if (map3[8][27] != BLOCK8 || map3[8][27] == BLOCK8)
						{
							if (map3[8][27] == BLOCK8 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK8;
								map3[8][27] = YUKA;
							}
						}
						playerPosX += playerSpeed;
					}

					if (map3[playerMapY][playerMapX + 1] == BLOCK1)
					{
						map3[1][27] = BLOCK1;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = NE;
						playerPosX += playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK22)
					{
						map3[2][27] = BLOCK22;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = NE;
						playerPosX += playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK3)
					{
						map3[3][27] = BLOCK3;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = NE;
						playerPosX += playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK4)
					{
						map3[4][27] = BLOCK4;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = NE;
						playerPosX += playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK5)
					{
						map3[5][27] = BLOCK5;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = NE;
						playerPosX += playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK6)
					{
						map3[6][27] = BLOCK6;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = NE;
						playerPosX += playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK7)
					{
						map3[7][27] = BLOCK7;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = NE;
						playerPosX = playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK8)
					{
						map3[8][27] = BLOCK8;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = NE;
						playerPosX += playerSpeed;

					}
				}
				if (map3[playerMapY][playerMapX] == RA)
				{
					if (map3[playerMapY][playerMapX + 1] == YUKA)
					{
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = RA;
						if (map3[1][27] != BLOCK1 || map3[1][27] == BLOCK1)
						{
							if (map3[1][27] == BLOCK1 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK1;
								map3[1][27] = YUKA;
							}
						}
						if (map3[2][27] != BLOCK22 || map3[2][27] == BLOCK22)
						{
							if (map3[2][27] == BLOCK22 && map3[playerMapY][playerMapX] == map3[4][11])
							{
								map3[playerMapY][playerMapX] = BLOCK22;
								map3[2][27] = YUKA;
							}
						}
						if (map3[3][27] != BLOCK3 || map3[3][27] == BLOCK3)
						{
							if (map3[3][27] == BLOCK3 && map3[playerMapY][playerMapX] == map3[4][13])
							{
								map3[playerMapY][playerMapX] = BLOCK3;
								map3[3][27] = YUKA;
							}
						}
						if (map3[4][27] != BLOCK4 || map3[4][27] == BLOCK4)
						{
							if (map3[4][27] == BLOCK4 && map3[playerMapY][playerMapX] == map3[4][15])
							{
								map3[playerMapY][playerMapX] = BLOCK4;
								map3[4][27] = YUKA;
							}
						}
						if (map3[5][27] != BLOCK5 || map3[5][27] == BLOCK5)
						{
							if (map3[5][27] == BLOCK5 && map3[playerMapY][playerMapX] == map3[4][17])
							{
								map3[playerMapY][playerMapX] = BLOCK5;
								map3[5][27] = YUKA;
							}
						}
						if (map3[6][27] != BLOCK6 || map3[6][27] == BLOCK6)
						{

							if (map3[6][27] == BLOCK6 && map3[playerMapY][playerMapX] == /*6以降は後で*/map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK6;
								map3[6][27] = YUKA;
							}
						}
						if (map3[7][27] != BLOCK7 || map3[7][27] == BLOCK7)
						{
							if (map3[7][27] == BLOCK7 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK7;
								map3[7][27] = YUKA;
							}
						}
						if (map3[8][27] != BLOCK8 || map3[8][27] == BLOCK8)
						{
							if (map3[8][27] == BLOCK8 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK8;
								map3[8][27] = YUKA;
							}
						}
						playerPosX += playerSpeed;
					}

					if (map3[playerMapY][playerMapX + 1] == BLOCK1)
					{
						map3[1][27] = BLOCK1;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = RA;
						playerPosX += playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK22)
					{
						map3[2][27] = BLOCK22;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = RA;
						playerPosX += playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK3)
					{
						map3[3][27] = BLOCK3;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = RA;
						playerPosX += playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK4)
					{
						map3[4][27] = BLOCK4;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = RA;
						playerPosX += playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK5)
					{
						map3[5][27] = BLOCK5;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = RA;
						playerPosX += playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK6)
					{
						map3[6][27] = BLOCK6;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = RA;
						playerPosX += playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK7)
					{
						map3[7][27] = BLOCK7;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = RA;
						playerPosX = playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK8)
					{
						map3[8][27] = BLOCK8;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = RA;
						playerPosX += playerSpeed;

					}
				}
				if (map3[playerMapY][playerMapX] == HO)
				{
					if (map3[playerMapY][playerMapX + 1] == YUKA)
					{
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = HO;
						if (map3[1][27] != BLOCK1 || map3[1][27] == BLOCK1)
						{
							if (map3[1][27] == BLOCK1 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK1;
								map3[1][27] = YUKA;
							}
						}
						if (map3[2][27] != BLOCK22 || map3[2][27] == BLOCK22)
						{
							if (map3[2][27] == BLOCK22 && map3[playerMapY][playerMapX] == map3[4][11])
							{
								map3[playerMapY][playerMapX] = BLOCK22;
								map3[2][27] = YUKA;
							}
						}
						if (map3[3][27] != BLOCK3 || map3[3][27] == BLOCK3)
						{
							if (map3[3][27] == BLOCK3 && map3[playerMapY][playerMapX] == map3[4][13])
							{
								map3[playerMapY][playerMapX] = BLOCK3;
								map3[3][27] = YUKA;
							}
						}
						if (map3[4][27] != BLOCK4 || map3[4][27] == BLOCK4)
						{
							if (map3[4][27] == BLOCK4 && map3[playerMapY][playerMapX] == map3[4][15])
							{
								map3[playerMapY][playerMapX] = BLOCK4;
								map3[4][27] = YUKA;
							}
						}
						if (map3[5][27] != BLOCK5 || map3[5][27] == BLOCK5)
						{
							if (map3[5][27] == BLOCK5 && map3[playerMapY][playerMapX] == map3[4][17])
							{
								map3[playerMapY][playerMapX] = BLOCK5;
								map3[5][27] = YUKA;
							}
						}
						if (map3[6][27] != BLOCK6 || map3[6][27] == BLOCK6)
						{

							if (map3[6][27] == BLOCK6 && map3[playerMapY][playerMapX] == /*6以降は後で*/map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK6;
								map3[6][27] = YUKA;
							}
						}
						if (map3[7][27] != BLOCK7 || map3[7][27] == BLOCK7)
						{
							if (map3[7][27] == BLOCK7 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK7;
								map3[7][27] = YUKA;
							}
						}
						if (map3[8][27] != BLOCK8 || map3[8][27] == BLOCK8)
						{
							if (map3[8][27] == BLOCK8 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK8;
								map3[8][27] = YUKA;
							}
						}
						playerPosX += playerSpeed;
					}

					if (map3[playerMapY][playerMapX + 1] == BLOCK1)
					{
						map3[1][27] = BLOCK1;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = HO;
						playerPosX += playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK22)
					{
						map3[2][27] = BLOCK22;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = HO;
						playerPosX += playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK3)
					{
						map3[3][27] = BLOCK3;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = HO;
						playerPosX += playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK4)
					{
						map3[4][27] = BLOCK4;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = HO;
						playerPosX += playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK5)
					{
						map3[5][27] = BLOCK5;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = HO;
						playerPosX += playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK6)
					{
						map3[6][27] = BLOCK6;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = HO;
						playerPosX += playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK7)
					{
						map3[7][27] = BLOCK7;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = HO;
						playerPosX = playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK8)
					{
						map3[8][27] = BLOCK8;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = HO;
						playerPosX += playerSpeed;

					}
				}
				if (map3[playerMapY][playerMapX] == ZE)
				{
					if (map3[playerMapY][playerMapX + 1] == YUKA)
					{
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = ZE;
						if (map3[1][27] != BLOCK1 || map3[1][27] == BLOCK1)
						{
							if (map3[1][27] == BLOCK1 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK1;
								map3[1][27] = YUKA;
							}
						}
						if (map3[2][27] != BLOCK22 || map3[2][27] == BLOCK22)
						{
							if (map3[2][27] == BLOCK22 && map3[playerMapY][playerMapX] == map3[4][11])
							{
								map3[playerMapY][playerMapX] = BLOCK22;
								map3[2][27] = YUKA;
							}
						}
						if (map3[3][27] != BLOCK3 || map3[3][27] == BLOCK3)
						{
							if (map3[3][27] == BLOCK3 && map3[playerMapY][playerMapX] == map3[4][13])
							{
								map3[playerMapY][playerMapX] = BLOCK3;
								map3[3][27] = YUKA;
							}
						}
						if (map3[4][27] != BLOCK4 || map3[4][27] == BLOCK4)
						{
							if (map3[4][27] == BLOCK4 && map3[playerMapY][playerMapX] == map3[4][15])
							{
								map3[playerMapY][playerMapX] = BLOCK4;
								map3[4][27] = YUKA;
							}
						}
						if (map3[5][27] != BLOCK5 || map3[5][27] == BLOCK5)
						{
							if (map3[5][27] == BLOCK5 && map3[playerMapY][playerMapX] == map3[4][17])
							{
								map3[playerMapY][playerMapX] = BLOCK5;
								map3[5][27] = YUKA;
							}
						}
						if (map3[6][27] != BLOCK6 || map3[6][27] == BLOCK6)
						{

							if (map3[6][27] == BLOCK6 && map3[playerMapY][playerMapX] == /*6以降は後で*/map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK6;
								map3[6][27] = YUKA;
							}
						}
						if (map3[7][27] != BLOCK7 || map3[7][27] == BLOCK7)
						{
							if (map3[7][27] == BLOCK7 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK7;
								map3[7][27] = YUKA;
							}
						}
						if (map3[8][27] != BLOCK8 || map3[8][27] == BLOCK8)
						{
							if (map3[8][27] == BLOCK8 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK8;
								map3[8][27] = YUKA;
							}
						}
						playerPosX += playerSpeed;
					}

					if (map3[playerMapY][playerMapX + 1] == BLOCK1)
					{
						map3[1][27] = BLOCK1;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = ZE;
						playerPosX += playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK22)
					{
						map3[2][27] = BLOCK22;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = ZE;
						playerPosX += playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK3)
					{
						map3[3][27] = BLOCK3;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = ZE;
						playerPosX += playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK4)
					{
						map3[4][27] = BLOCK4;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = ZE;
						playerPosX += playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK5)
					{
						map3[5][27] = BLOCK5;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = ZE;
						playerPosX += playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK6)
					{
						map3[6][27] = BLOCK6;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = ZE;
						playerPosX += playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK7)
					{
						map3[7][27] = BLOCK7;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = ZE;
						playerPosX = playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK8)
					{
						map3[8][27] = BLOCK8;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = A;
						playerPosX += playerSpeed;

					}
				}
				if (map3[playerMapY][playerMapX] == RU)
				{
					if (map3[playerMapY][playerMapX + 1] == YUKA)
					{
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = RU;
						if (map3[1][27] != BLOCK1 || map3[1][27] == BLOCK1)
						{
							if (map3[1][27] == BLOCK1 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK1;
								map3[1][27] = YUKA;
							}
						}
						if (map3[2][27] != BLOCK22 || map3[2][27] == BLOCK22)
						{
							if (map3[2][27] == BLOCK22 && map3[playerMapY][playerMapX] == map3[4][11])
							{
								map3[playerMapY][playerMapX] = BLOCK22;
								map3[2][27] = YUKA;
							}
						}
						if (map3[3][27] != BLOCK3 || map3[3][27] == BLOCK3)
						{
							if (map3[3][27] == BLOCK3 && map3[playerMapY][playerMapX] == map3[4][13])
							{
								map3[playerMapY][playerMapX] = BLOCK3;
								map3[3][27] = YUKA;
							}
						}
						if (map3[4][27] != BLOCK4 || map3[4][27] == BLOCK4)
						{
							if (map3[4][27] == BLOCK4 && map3[playerMapY][playerMapX] == map3[4][15])
							{
								map3[playerMapY][playerMapX] = BLOCK4;
								map3[4][27] = YUKA;
							}
						}
						if (map3[5][27] != BLOCK5 || map3[5][27] == BLOCK5)
						{
							if (map3[5][27] == BLOCK5 && map3[playerMapY][playerMapX] == map3[4][17])
							{
								map3[playerMapY][playerMapX] = BLOCK5;
								map3[5][27] = YUKA;
							}
						}
						if (map3[6][27] != BLOCK6 || map3[6][27] == BLOCK6)
						{

							if (map3[6][27] == BLOCK6 && map3[playerMapY][playerMapX] == /*6以降は後で*/map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK6;
								map3[6][27] = YUKA;
							}
						}
						if (map3[7][27] != BLOCK7 || map3[7][27] == BLOCK7)
						{
							if (map3[7][27] == BLOCK7 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK7;
								map3[7][27] = YUKA;
							}
						}
						if (map3[8][27] != BLOCK8 || map3[8][27] == BLOCK8)
						{
							if (map3[8][27] == BLOCK8 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK8;
								map3[8][27] = YUKA;
							}
						}
						playerPosX += playerSpeed;
					}

					if (map3[playerMapY][playerMapX + 1] == BLOCK1)
					{
						map3[1][27] = BLOCK1;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = RU;
						playerPosX += playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK22)
					{
						map3[2][27] = BLOCK22;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = RU;
						playerPosX += playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK3)
					{
						map3[3][27] = BLOCK3;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = RU;
						playerPosX += playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK4)
					{
						map3[4][27] = BLOCK4;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = RU;
						playerPosX += playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK5)
					{
						map3[5][27] = BLOCK5;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = RU;
						playerPosX += playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK6)
					{
						map3[6][27] = BLOCK6;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = RU;
						playerPosX += playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK7)
					{
						map3[7][27] = BLOCK7;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = RU;
						playerPosX = playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK8)
					{
						map3[8][27] = BLOCK8;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = RU;
						playerPosX += playerSpeed;

					}
				}
				if (map3[playerMapY][playerMapX] == YU)
				{
					if (map3[playerMapY][playerMapX + 1] == YUKA)
					{
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = YU;
						if (map3[1][27] != BLOCK1 || map3[1][27] == BLOCK1)
						{
							if (map3[1][27] == BLOCK1 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK1;
								map3[1][27] = YUKA;
							}
						}
						if (map3[2][27] != BLOCK22 || map3[2][27] == BLOCK22)
						{
							if (map3[2][27] == BLOCK22 && map3[playerMapY][playerMapX] == map3[4][11])
							{
								map3[playerMapY][playerMapX] = BLOCK22;
								map3[2][27] = YUKA;
							}
						}
						if (map3[3][27] != BLOCK3 || map3[3][27] == BLOCK3)
						{
							if (map3[3][27] == BLOCK3 && map3[playerMapY][playerMapX] == map3[4][13])
							{
								map3[playerMapY][playerMapX] = BLOCK3;
								map3[3][27] = YUKA;
							}
						}
						if (map3[4][27] != BLOCK4 || map3[4][27] == BLOCK4)
						{
							if (map3[4][27] == BLOCK4 && map3[playerMapY][playerMapX] == map3[4][15])
							{
								map3[playerMapY][playerMapX] = BLOCK4;
								map3[4][27] = YUKA;
							}
						}
						if (map3[5][27] != BLOCK5 || map3[5][27] == BLOCK5)
						{
							if (map3[5][27] == BLOCK5 && map3[playerMapY][playerMapX] == map3[4][17])
							{
								map3[playerMapY][playerMapX] = BLOCK5;
								map3[5][27] = YUKA;
							}
						}
						if (map3[6][27] != BLOCK6 || map3[6][27] == BLOCK6)
						{

							if (map3[6][27] == BLOCK6 && map3[playerMapY][playerMapX] == /*6以降は後で*/map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK6;
								map3[6][27] = YUKA;
							}
						}
						if (map3[7][27] != BLOCK7 || map3[7][27] == BLOCK7)
						{
							if (map3[7][27] == BLOCK7 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK7;
								map3[7][27] = YUKA;
							}
						}
						if (map3[8][27] != BLOCK8 || map3[8][27] == BLOCK8)
						{
							if (map3[8][27] == BLOCK8 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK8;
								map3[8][27] = YUKA;
							}
						}
						playerPosX += playerSpeed;
					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK1)
					{
						map3[1][27] = BLOCK1;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = YU;
						playerPosX += playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK22)
					{
						map3[2][27] = BLOCK22;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = YU;
						playerPosX += playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK3)
					{
						map3[3][27] = BLOCK3;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = YU;
						playerPosX += playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK4)
					{
						map3[4][27] = BLOCK4;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = YU;
						playerPosX += playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK5)
					{
						map3[5][27] = BLOCK5;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = YU;
						playerPosX += playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK6)
					{
						map3[6][27] = BLOCK6;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = YU;
						playerPosX += playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK7)
					{
						map3[7][27] = BLOCK7;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = YU;
						playerPosX = playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK8)
					{
						map3[8][27] = BLOCK8;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = A;
						playerPosX += playerSpeed;

					}
				}
				if (map3[playerMapY][playerMapX] == DO)
				{
					if (map3[playerMapY][playerMapX + 1] == YUKA)
					{
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = DO;
						if (map3[1][27] != BLOCK1 || map3[1][27] == BLOCK1)
						{
							if (map3[1][27] == BLOCK1 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK1;
								map3[1][27] = YUKA;
							}
						}
						if (map3[2][27] != BLOCK22 || map3[2][27] == BLOCK22)
						{
							if (map3[2][27] == BLOCK22 && map3[playerMapY][playerMapX] == map3[4][11])
							{
								map3[playerMapY][playerMapX] = BLOCK22;
								map3[2][27] = YUKA;
							}
						}
						if (map3[3][27] != BLOCK3 || map3[3][27] == BLOCK3)
						{
							if (map3[3][27] == BLOCK3 && map3[playerMapY][playerMapX] == map3[4][13])
							{
								map3[playerMapY][playerMapX] = BLOCK3;
								map3[3][27] = YUKA;
							}
						}
						if (map3[4][27] != BLOCK4 || map3[4][27] == BLOCK4)
						{
							if (map3[4][27] == BLOCK4 && map3[playerMapY][playerMapX] == map3[4][15])
							{
								map3[playerMapY][playerMapX] = BLOCK4;
								map3[4][27] = YUKA;
							}
						}
						if (map3[5][27] != BLOCK5 || map3[5][27] == BLOCK5)
						{
							if (map3[5][27] == BLOCK5 && map3[playerMapY][playerMapX] == map3[4][17])
							{
								map3[playerMapY][playerMapX] = BLOCK5;
								map3[5][27] = YUKA;
							}
						}
						if (map3[6][27] != BLOCK6 || map3[6][27] == BLOCK6)
						{

							if (map3[6][27] == BLOCK6 && map3[playerMapY][playerMapX] == /*6以降は後で*/map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK6;
								map3[6][27] = YUKA;
							}
						}
						if (map3[7][27] != BLOCK7 || map3[7][27] == BLOCK7)
						{
							if (map3[7][27] == BLOCK7 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK7;
								map3[7][27] = YUKA;
							}
						}
						if (map3[8][27] != BLOCK8 || map3[8][27] == BLOCK8)
						{
							if (map3[8][27] == BLOCK8 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK8;
								map3[8][27] = YUKA;
							}
						}
						playerPosX += playerSpeed;
					}

					if (map3[playerMapY][playerMapX + 1] == BLOCK1)
					{
						map3[1][27] = BLOCK1;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = DO;
						playerPosX += playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK22)
					{
						map3[2][27] = BLOCK22;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = DO;
						playerPosX += playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK3)
					{
						map3[3][27] = BLOCK3;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = DO;
						playerPosX += playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK4)
					{
						map3[4][27] = BLOCK4;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = DO;
						playerPosX += playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK5)
					{
						map3[5][27] = BLOCK5;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = DO;
						playerPosX += playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK6)
					{
						map3[6][27] = BLOCK6;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = DO;
						playerPosX += playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK7)
					{
						map3[7][27] = BLOCK7;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = DO;
						playerPosX = playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK8)
					{
						map3[8][27] = BLOCK8;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = DO;
						playerPosX += playerSpeed;

					}
				}
				if (map3[playerMapY][playerMapX] == GO)
				{
					if (map3[playerMapY][playerMapX + 1] == YUKA)
					{
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = GO;
						if (map3[1][27] != BLOCK1 || map3[1][27] == BLOCK1)
						{
							if (map3[1][27] == BLOCK1 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK1;
								map3[1][27] = YUKA;
							}
						}
						if (map3[2][27] != BLOCK22 || map3[2][27] == BLOCK22)
						{
							if (map3[2][27] == BLOCK22 && map3[playerMapY][playerMapX] == map3[4][11])
							{
								map3[playerMapY][playerMapX] = BLOCK22;
								map3[2][27] = YUKA;
							}
						}
						if (map3[3][27] != BLOCK3 || map3[3][27] == BLOCK3)
						{
							if (map3[3][27] == BLOCK3 && map3[playerMapY][playerMapX] == map3[4][13])
							{
								map3[playerMapY][playerMapX] = BLOCK3;
								map3[3][27] = YUKA;
							}
						}
						if (map3[4][27] != BLOCK4 || map3[4][27] == BLOCK4)
						{
							if (map3[4][27] == BLOCK4 && map3[playerMapY][playerMapX] == map3[4][15])
							{
								map3[playerMapY][playerMapX] = BLOCK4;
								map3[4][27] = YUKA;
							}
						}
						if (map3[5][27] != BLOCK5 || map3[5][27] == BLOCK5)
						{
							if (map3[5][27] == BLOCK5 && map3[playerMapY][playerMapX] == map3[4][17])
							{
								map3[playerMapY][playerMapX] = BLOCK5;
								map3[5][27] = YUKA;
							}
						}
						if (map3[6][27] != BLOCK6 || map3[6][27] == BLOCK6)
						{

							if (map3[6][27] == BLOCK6 && map3[playerMapY][playerMapX] == /*6以降は後で*/map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK6;
								map3[6][27] = YUKA;
							}
						}
						if (map3[7][27] != BLOCK7 || map3[7][27] == BLOCK7)
						{
							if (map3[7][27] == BLOCK7 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK7;
								map3[7][27] = YUKA;
							}
						}
						if (map3[8][27] != BLOCK8 || map3[8][27] == BLOCK8)
						{
							if (map3[8][27] == BLOCK8 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK8;
								map3[8][27] = YUKA;
							}
						}
						playerPosX += playerSpeed;
					}

					if (map3[playerMapY][playerMapX + 1] == BLOCK1)
					{
						map3[1][27] = BLOCK1;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = GO;
						playerPosX += playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK22)
					{
						map3[2][27] = BLOCK22;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = GO;
						playerPosX += playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK3)
					{
						map3[3][27] = BLOCK3;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = GO;
						playerPosX += playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK4)
					{
						map3[4][27] = BLOCK4;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = GO;
						playerPosX += playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK5)
					{
						map3[5][27] = BLOCK5;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = GO;
						playerPosX += playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK6)
					{
						map3[6][27] = BLOCK6;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = GO;
						playerPosX += playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK7)
					{
						map3[7][27] = BLOCK7;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = GO;
						playerPosX = playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK8)
					{
						map3[8][27] = BLOCK8;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = GO;
						playerPosX += playerSpeed;

					}
				}
				if (map3[playerMapY][playerMapX] == ZE)
				{
					if (map3[playerMapY][playerMapX + 1] == YUKA)
					{
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = ZE;
						if (map3[1][27] != BLOCK1 || map3[1][27] == BLOCK1)
						{
							if (map3[1][27] == BLOCK1 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK1;
								map3[1][27] = YUKA;
							}
						}
						if (map3[2][27] != BLOCK22 || map3[2][27] == BLOCK22)
						{
							if (map3[2][27] == BLOCK22 && map3[playerMapY][playerMapX] == map3[4][11])
							{
								map3[playerMapY][playerMapX] = BLOCK22;
								map3[2][27] = YUKA;
							}
						}
						if (map3[3][27] != BLOCK3 || map3[3][27] == BLOCK3)
						{
							if (map3[3][27] == BLOCK3 && map3[playerMapY][playerMapX] == map3[4][13])
							{
								map3[playerMapY][playerMapX] = BLOCK3;
								map3[3][27] = YUKA;
							}
						}
						if (map3[4][27] != BLOCK4 || map3[4][27] == BLOCK4)
						{
							if (map3[4][27] == BLOCK4 && map3[playerMapY][playerMapX] == map3[4][15])
							{
								map3[playerMapY][playerMapX] = BLOCK4;
								map3[4][27] = YUKA;
							}
						}
						if (map3[5][27] != BLOCK5 || map3[5][27] == BLOCK5)
						{
							if (map3[5][27] == BLOCK5 && map3[playerMapY][playerMapX] == map3[4][17])
							{
								map3[playerMapY][playerMapX] = BLOCK5;
								map3[5][27] = YUKA;
							}
						}
						if (map3[6][27] != BLOCK6 || map3[6][27] == BLOCK6)
						{

							if (map3[6][27] == BLOCK6 && map3[playerMapY][playerMapX] == /*6以降は後で*/map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK6;
								map3[6][27] = YUKA;
							}
						}
						if (map3[7][27] != BLOCK7 || map3[7][27] == BLOCK7)
						{
							if (map3[7][27] == BLOCK7 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK7;
								map3[7][27] = YUKA;
							}
						}
						if (map3[8][27] != BLOCK8 || map3[8][27] == BLOCK8)
						{
							if (map3[8][27] == BLOCK8 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK8;
								map3[8][27] = YUKA;
							}
						}
						playerPosX += playerSpeed;
					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK1)
					{
						map3[1][27] = BLOCK1;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = ZE;
						playerPosX += playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK22)
					{
						map3[2][27] = BLOCK22;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = ZE;
						playerPosX += playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK3)
					{
						map3[3][27] = BLOCK3;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = ZE;
						playerPosX += playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK4)
					{
						map3[4][27] = BLOCK4;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = ZE;
						playerPosX += playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK5)
					{
						map3[5][27] = BLOCK5;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = ZE;
						playerPosX += playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK6)
					{
						map3[6][27] = BLOCK6;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = ZE;
						playerPosX += playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK7)
					{
						map3[7][27] = BLOCK7;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = ZE;
						playerPosX = playerSpeed;

					}
					if (map3[playerMapY][playerMapX + 1] == BLOCK8)
					{
						map3[8][27] = BLOCK8;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX + 1] = ZE;
						playerPosX += playerSpeed;

					}
				}
			}

			if (keys[DIK_S] && preKeys[DIK_S] == 0 || keys[DIK_DOWN] && preKeys[DIK_DOWN] == 0)
			{
				playerTmpY = playerPosY + playerSpeed;
				playerMapY = playerTmpY / KBlockSize;
				//何もないから実際に進ませる
				if (map3[playerMapY][playerMapX] == YUKA)
				{
					playerPosY += playerSpeed;
				}
				if (map3[playerMapY][playerMapX] == GOAL)
				{
					playerPosY += playerSpeed;
				}

				if (map3[playerMapY][playerMapX] == A)
				{
					if (map3[playerMapY + 1][playerMapX] == YUKA)
					{
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = A;
						if (map3[1][27] != BLOCK1 || map3[1][27] == BLOCK1)
						{
							if (map3[1][27] == BLOCK1 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK1;
								map3[1][27] = YUKA;
							}
						}
						if (map3[2][27] != BLOCK22 || map3[2][27] == BLOCK22)
						{
							if (map3[2][27] == BLOCK22 && map3[playerMapY][playerMapX] == map3[4][11])
							{
								map3[playerMapY][playerMapX] = BLOCK22;
								map3[2][27] = YUKA;
							}
						}
						if (map3[3][27] != BLOCK3 || map3[3][27] == BLOCK3)
						{
							if (map3[3][27] == BLOCK3 && map3[playerMapY][playerMapX] == map3[4][13])
							{
								map3[playerMapY][playerMapX] = BLOCK3;
								map3[3][27] = YUKA;
							}
						}
						if (map3[4][27] != BLOCK4 || map3[4][27] == BLOCK4)
						{
							if (map3[4][27] == BLOCK4 && map3[playerMapY][playerMapX] == map3[4][15])
							{
								map3[playerMapY][playerMapX] = BLOCK4;
								map3[4][27] = YUKA;
							}
						}
						if (map3[5][27] != BLOCK5 || map3[5][27] == BLOCK5)
						{
							if (map3[5][27] == BLOCK5 && map3[playerMapY][playerMapX] == map3[4][17])
							{
								map3[playerMapY][playerMapX] = BLOCK5;
								map3[5][27] = YUKA;
							}
						}
						if (map3[6][27] != BLOCK6 || map3[6][27] == BLOCK6)
						{

							if (map3[6][27] == BLOCK6 && map3[playerMapY][playerMapX] == /*6以降は後で*/map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK6;
								map3[6][27] = YUKA;
							}
						}
						if (map3[7][27] != BLOCK7 || map3[7][27] == BLOCK7)
						{
							if (map3[7][27] == BLOCK7 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK7;
								map3[7][27] = YUKA;
							}
						}
						if (map3[8][27] != BLOCK8 || map3[8][27] == BLOCK8)
						{
							if (map3[8][27] == BLOCK8 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK8;
								map3[8][27] = YUKA;
							}
						}
						playerPosY += playerSpeed;
					}

					if (map3[playerMapY + 1][playerMapX] == BLOCK1)
					{
						map3[1][27] = BLOCK1;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = A;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK22)
					{
						map3[2][27] = BLOCK22;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = A;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK3)
					{
						map3[3][27] = BLOCK3;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = A;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK4)
					{
						map3[4][27] = BLOCK4;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = A;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK5)
					{
						map3[5][27] = BLOCK5;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = A;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK6)
					{
						map3[6][27] = BLOCK6;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = A;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK7)
					{
						map3[7][27] = BLOCK7;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = A;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK8)
					{
						map3[8][27] = BLOCK8;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = A;
						playerPosY += playerSpeed;

					}



				}

				// 1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111
				// ここから直して
				if (map3[playerMapY][playerMapX] == KE)
				{
					if (map3[playerMapY + 1][playerMapX] == YUKA)
					{
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = KE; //ここをKEに変える　したも同じ
						if (map3[1][27] != BLOCK1 || map3[1][27] == BLOCK1)
						{
							if (map3[1][27] == BLOCK1 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK1;
								map3[1][27] = YUKA;
							}
						}
						if (map3[2][27] != BLOCK22 || map3[2][27] == BLOCK22)
						{
							if (map3[2][27] == BLOCK22 && map3[playerMapY][playerMapX] == map3[4][11])
							{
								map3[playerMapY][playerMapX] = BLOCK22;
								map3[2][27] = YUKA;
							}
						}
						if (map3[3][27] != BLOCK3 || map3[3][27] == BLOCK3)
						{
							if (map3[3][27] == BLOCK3 && map3[playerMapY][playerMapX] == map3[4][13])
							{
								map3[playerMapY][playerMapX] = BLOCK3;
								map3[3][27] = YUKA;
							}
						}
						if (map3[4][27] != BLOCK4 || map3[4][27] == BLOCK4)
						{
							if (map3[4][27] == BLOCK4 && map3[playerMapY][playerMapX] == map3[4][15])
							{
								map3[playerMapY][playerMapX] = BLOCK4;
								map3[4][27] = YUKA;
							}
						}
						if (map3[5][27] != BLOCK5 || map3[5][27] == BLOCK5)
						{
							if (map3[5][27] == BLOCK5 && map3[playerMapY][playerMapX] == map3[4][17])
							{
								map3[playerMapY][playerMapX] = BLOCK5;
								map3[5][27] = YUKA;
							}
						}
						if (map3[6][27] != BLOCK6 || map3[6][27] == BLOCK6)
						{

							if (map3[6][27] == BLOCK6 && map3[playerMapY][playerMapX] == /*6以降は後で*/map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK6;
								map3[6][27] = YUKA;
							}
						}
						if (map3[7][27] != BLOCK7 || map3[7][27] == BLOCK7)
						{
							if (map3[7][27] == BLOCK7 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK7;
								map3[7][27] = YUKA;
							}
						}
						if (map3[8][27] != BLOCK8 || map3[8][27] == BLOCK8)
						{
							if (map3[8][27] == BLOCK8 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK8;
								map3[8][27] = YUKA;
							}
						}
						playerPosY += playerSpeed;
					}

					if (map3[playerMapY + 1][playerMapX] == BLOCK1)
					{
						map3[1][27] = BLOCK1;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = KE;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK22)
					{
						map3[2][27] = BLOCK22;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = KE;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK3)
					{
						map3[3][27] = BLOCK3;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = KE;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK4)
					{
						map3[4][27] = BLOCK4;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = KE;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK5)
					{
						map3[5][27] = BLOCK5;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = KE;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK6)
					{
						map3[6][27] = BLOCK6;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = KE;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK7)
					{
						map3[7][27] = BLOCK7;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = KE;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK8)
					{
						map3[8][27] = BLOCK8;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = KE;
						playerPosY += playerSpeed;

					}
				}
				if (map3[playerMapY][playerMapX] == E)
				{
					if (map3[playerMapY + 1][playerMapX] == YUKA)
					{
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = E;
						if (map3[1][27] != BLOCK1 || map3[1][27] == BLOCK1)
						{
							if (map3[1][27] == BLOCK1 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK1;
								map3[1][27] = YUKA;
							}
						}
						if (map3[2][27] != BLOCK22 || map3[2][27] == BLOCK22)
						{
							if (map3[2][27] == BLOCK22 && map3[playerMapY][playerMapX] == map3[4][11])
							{
								map3[playerMapY][playerMapX] = BLOCK22;
								map3[2][27] = YUKA;
							}
						}
						if (map3[3][27] != BLOCK3 || map3[3][27] == BLOCK3)
						{
							if (map3[3][27] == BLOCK3 && map3[playerMapY][playerMapX] == map3[4][13])
							{
								map3[playerMapY][playerMapX] = BLOCK3;
								map3[3][27] = YUKA;
							}
						}
						if (map3[4][27] != BLOCK4 || map3[4][27] == BLOCK4)
						{
							if (map3[4][27] == BLOCK4 && map3[playerMapY][playerMapX] == map3[4][15])
							{
								map3[playerMapY][playerMapX] = BLOCK4;
								map3[4][27] = YUKA;
							}
						}
						if (map3[5][27] != BLOCK5 || map3[5][27] == BLOCK5)
						{
							if (map3[5][27] == BLOCK5 && map3[playerMapY][playerMapX] == map3[4][17])
							{
								map3[playerMapY][playerMapX] = BLOCK5;
								map3[5][27] = YUKA;
							}
						}
						if (map3[6][27] != BLOCK6 || map3[6][27] == BLOCK6)
						{

							if (map3[6][27] == BLOCK6 && map3[playerMapY][playerMapX] == /*6以降は後で*/map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK6;
								map3[6][27] = YUKA;
							}
						}
						if (map3[7][27] != BLOCK7 || map3[7][27] == BLOCK7)
						{
							if (map3[7][27] == BLOCK7 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK7;
								map3[7][27] = YUKA;
							}
						}
						if (map3[8][27] != BLOCK8 || map3[8][27] == BLOCK8)
						{
							if (map3[8][27] == BLOCK8 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK8;
								map3[8][27] = YUKA;
							}
						}
						playerPosY += playerSpeed;
					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK1)
					{
						map3[1][27] = BLOCK1;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = E;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK22)
					{
						map3[2][27] = BLOCK22;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = E;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK3)
					{
						map3[3][27] = BLOCK3;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = E;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK4)
					{
						map3[4][27] = BLOCK4;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = E;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK5)
					{
						map3[5][27] = BLOCK5;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = E;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK6)
					{
						map3[6][27] = BLOCK6;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = E;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK7)
					{
						map3[7][27] = BLOCK7;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = E;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK8)
					{
						map3[8][27] = BLOCK8;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = E;
						playerPosY += playerSpeed;

					}
				}
				if (map3[playerMapY][playerMapX] == KA)
				{
					if (map3[playerMapY + 1][playerMapX] == YUKA)
					{
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = KA;
						if (map3[1][27] != BLOCK1 || map3[1][27] == BLOCK1)
						{
							if (map3[1][27] == BLOCK1 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK1;
								map3[1][27] = YUKA;
							}
						}
						if (map3[2][27] != BLOCK22 || map3[2][27] == BLOCK22)
						{
							if (map3[2][27] == BLOCK22 && map3[playerMapY][playerMapX] == map3[4][11])
							{
								map3[playerMapY][playerMapX] = BLOCK22;
								map3[2][27] = YUKA;
							}
						}
						if (map3[3][27] != BLOCK3 || map3[3][27] == BLOCK3)
						{
							if (map3[3][27] == BLOCK3 && map3[playerMapY][playerMapX] == map3[4][13])
							{
								map3[playerMapY][playerMapX] = BLOCK3;
								map3[3][27] = YUKA;
							}
						}
						if (map3[4][27] != BLOCK4 || map3[4][27] == BLOCK4)
						{
							if (map3[4][27] == BLOCK4 && map3[playerMapY][playerMapX] == map3[4][15])
							{
								map3[playerMapY][playerMapX] = BLOCK4;
								map3[4][27] = YUKA;
							}
						}
						if (map3[5][27] != BLOCK5 || map3[5][27] == BLOCK5)
						{
							if (map3[5][27] == BLOCK5 && map3[playerMapY][playerMapX] == map3[4][17])
							{
								map3[playerMapY][playerMapX] = BLOCK5;
								map3[5][27] = YUKA;
							}
						}
						if (map3[6][27] != BLOCK6 || map3[6][27] == BLOCK6)
						{

							if (map3[6][27] == BLOCK6 && map3[playerMapY][playerMapX] == /*6以降は後で*/map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK6;
								map3[6][27] = YUKA;
							}
						}
						if (map3[7][27] != BLOCK7 || map3[7][27] == BLOCK7)
						{
							if (map3[7][27] == BLOCK7 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK7;
								map3[7][27] = YUKA;
							}
						}
						if (map3[8][27] != BLOCK8 || map3[8][27] == BLOCK8)
						{
							if (map3[8][27] == BLOCK8 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK8;
								map3[8][27] = YUKA;
							}
						}
						playerPosY += playerSpeed;
					}

					if (map3[playerMapY + 1][playerMapX] == BLOCK1)
					{
						map3[1][27] = BLOCK1;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = KA;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK22)
					{
						map3[2][27] = BLOCK22;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = KA;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK3)
					{
						map3[3][27] = BLOCK3;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = KA;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK4)
					{
						map3[4][27] = BLOCK4;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = KA;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK5)
					{
						map3[5][27] = BLOCK5;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = KA;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK6)
					{
						map3[6][27] = BLOCK6;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = KA;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK7)
					{
						map3[7][27] = BLOCK7;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = KA;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK8)
					{
						map3[8][27] = BLOCK8;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = KA;
						playerPosY += playerSpeed;

					}
				}
				if (map3[playerMapY][playerMapX] == KU)
				{
					if (map3[playerMapY + 1][playerMapX] == YUKA)
					{
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = KU;
						if (map3[1][27] != BLOCK1 || map3[1][27] == BLOCK1)
						{
							if (map3[1][27] == BLOCK1 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK1;
								map3[1][27] = YUKA;
							}
						}
						if (map3[2][27] != BLOCK22 || map3[2][27] == BLOCK22)
						{
							if (map3[2][27] == BLOCK22 && map3[playerMapY][playerMapX] == map3[4][11])
							{
								map3[playerMapY][playerMapX] = BLOCK22;
								map3[2][27] = YUKA;
							}
						}
						if (map3[3][27] != BLOCK3 || map3[3][27] == BLOCK3)
						{
							if (map3[3][27] == BLOCK3 && map3[playerMapY][playerMapX] == map3[4][13])
							{
								map3[playerMapY][playerMapX] = BLOCK3;
								map3[3][27] = YUKA;
							}
						}
						if (map3[4][27] != BLOCK4 || map3[4][27] == BLOCK4)
						{
							if (map3[4][27] == BLOCK4 && map3[playerMapY][playerMapX] == map3[4][15])
							{
								map3[playerMapY][playerMapX] = BLOCK4;
								map3[4][27] = YUKA;
							}
						}
						if (map3[5][27] != BLOCK5 || map3[5][27] == BLOCK5)
						{
							if (map3[5][27] == BLOCK5 && map3[playerMapY][playerMapX] == map3[4][17])
							{
								map3[playerMapY][playerMapX] = BLOCK5;
								map3[5][27] = YUKA;
							}
						}
						if (map3[6][27] != BLOCK6 || map3[6][27] == BLOCK6)
						{

							if (map3[6][27] == BLOCK6 && map3[playerMapY][playerMapX] == /*6以降は後で*/map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK6;
								map3[6][27] = YUKA;
							}
						}
						if (map3[7][27] != BLOCK7 || map3[7][27] == BLOCK7)
						{
							if (map3[7][27] == BLOCK7 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK7;
								map3[7][27] = YUKA;
							}
						}
						if (map3[8][27] != BLOCK8 || map3[8][27] == BLOCK8)
						{
							if (map3[8][27] == BLOCK8 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK8;
								map3[8][27] = YUKA;
							}
						}
						playerPosY += playerSpeed;
					}

					if (map3[playerMapY + 1][playerMapX] == BLOCK1)
					{
						map3[1][27] = BLOCK1;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = KU;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK22)
					{
						map3[2][27] = BLOCK22;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = KU;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK3)
					{
						map3[3][27] = BLOCK3;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = KU;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK4)
					{
						map3[4][27] = BLOCK4;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = KU;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK5)
					{
						map3[5][27] = BLOCK5;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = KU;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK6)
					{
						map3[6][27] = BLOCK6;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = KU;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK7)
					{
						map3[7][27] = BLOCK7;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = KU;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK8)
					{
						map3[8][27] = BLOCK8;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = KU;
						playerPosY += playerSpeed;

					}
				}
				if (map3[playerMapY][playerMapX] == NO)
				{
					if (map3[playerMapY + 1][playerMapX] == YUKA)
					{
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = NO;
						if (map3[1][27] != BLOCK1 || map3[1][27] == BLOCK1)
						{
							if (map3[1][27] == BLOCK1 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK1;
								map3[1][27] = YUKA;
							}
						}
						if (map3[2][27] != BLOCK22 || map3[2][27] == BLOCK22)
						{
							if (map3[2][27] == BLOCK22 && map3[playerMapY][playerMapX] == map3[4][11])
							{
								map3[playerMapY][playerMapX] = BLOCK22;
								map3[2][27] = YUKA;
							}
						}
						if (map3[3][27] != BLOCK3 || map3[3][27] == BLOCK3)
						{
							if (map3[3][27] == BLOCK3 && map3[playerMapY][playerMapX] == map3[4][13])
							{
								map3[playerMapY][playerMapX] = BLOCK3;
								map3[3][27] = YUKA;
							}
						}
						if (map3[4][27] != BLOCK4 || map3[4][27] == BLOCK4)
						{
							if (map3[4][27] == BLOCK4 && map3[playerMapY][playerMapX] == map3[4][15])
							{
								map3[playerMapY][playerMapX] = BLOCK4;
								map3[4][27] = YUKA;
							}
						}
						if (map3[5][27] != BLOCK5 || map3[5][27] == BLOCK5)
						{
							if (map3[5][27] == BLOCK5 && map3[playerMapY][playerMapX] == map3[4][17])
							{
								map3[playerMapY][playerMapX] = BLOCK5;
								map3[5][27] = YUKA;
							}
						}
						if (map3[6][27] != BLOCK6 || map3[6][27] == BLOCK6)
						{

							if (map3[6][27] == BLOCK6 && map3[playerMapY][playerMapX] == /*6以降は後で*/map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK6;
								map3[6][27] = YUKA;
							}
						}
						if (map3[7][27] != BLOCK7 || map3[7][27] == BLOCK7)
						{
							if (map3[7][27] == BLOCK7 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK7;
								map3[7][27] = YUKA;
							}
						}
						if (map3[8][27] != BLOCK8 || map3[8][27] == BLOCK8)
						{
							if (map3[8][27] == BLOCK8 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK8;
								map3[8][27] = YUKA;
							}
						}
						playerPosY += playerSpeed;
					}

					if (map3[playerMapY + 1][playerMapX] == BLOCK1)
					{
						map3[1][27] = BLOCK1;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = NO;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK22)
					{
						map3[2][27] = BLOCK22;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = NO;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK3)
					{
						map3[3][27] = BLOCK3;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = NO;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK4)
					{
						map3[4][27] = BLOCK4;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = NO;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK5)
					{
						map3[5][27] = BLOCK5;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = NO;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK6)
					{
						map3[6][27] = BLOCK6;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = NO;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK7)
					{
						map3[7][27] = BLOCK7;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = NO;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK8)
					{
						map3[8][27] = BLOCK8;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = NO;
						playerPosY += playerSpeed;

					}
				}
				if (map3[playerMapY][playerMapX] == GA)
				{
					if (map3[playerMapY + 1][playerMapX] == YUKA)
					{
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = GA;
						if (map3[1][27] != BLOCK1 || map3[1][27] == BLOCK1)
						{
							if (map3[1][27] == BLOCK1 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK1;
								map3[1][27] = YUKA;
							}
						}
						if (map3[2][27] != BLOCK22 || map3[2][27] == BLOCK22)
						{
							if (map3[2][27] == BLOCK22 && map3[playerMapY][playerMapX] == map3[4][11])
							{
								map3[playerMapY][playerMapX] = BLOCK22;
								map3[2][27] = YUKA;
							}
						}
						if (map3[3][27] != BLOCK3 || map3[3][27] == BLOCK3)
						{
							if (map3[3][27] == BLOCK3 && map3[playerMapY][playerMapX] == map3[4][13])
							{
								map3[playerMapY][playerMapX] = BLOCK3;
								map3[3][27] = YUKA;
							}
						}
						if (map3[4][27] != BLOCK4 || map3[4][27] == BLOCK4)
						{
							if (map3[4][27] == BLOCK4 && map3[playerMapY][playerMapX] == map3[4][15])
							{
								map3[playerMapY][playerMapX] = BLOCK4;
								map3[4][27] = YUKA;
							}
						}
						if (map3[5][27] != BLOCK5 || map3[5][27] == BLOCK5)
						{
							if (map3[5][27] == BLOCK5 && map3[playerMapY][playerMapX] == map3[4][17])
							{
								map3[playerMapY][playerMapX] = BLOCK5;
								map3[5][27] = YUKA;
							}
						}
						if (map3[6][27] != BLOCK6 || map3[6][27] == BLOCK6)
						{

							if (map3[6][27] == BLOCK6 && map3[playerMapY][playerMapX] == /*6以降は後で*/map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK6;
								map3[6][27] = YUKA;
							}
						}
						if (map3[7][27] != BLOCK7 || map3[7][27] == BLOCK7)
						{
							if (map3[7][27] == BLOCK7 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK7;
								map3[7][27] = YUKA;
							}
						}
						if (map3[8][27] != BLOCK8 || map3[8][27] == BLOCK8)
						{
							if (map3[8][27] == BLOCK8 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK8;
								map3[8][27] = YUKA;
							}
						}
						playerPosY += playerSpeed;
					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK1)
					{
						map3[1][27] = BLOCK1;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = GA;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK22)
					{
						map3[2][27] = BLOCK22;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = GA;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK3)
					{
						map3[3][27] = BLOCK3;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = GA;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK4)
					{
						map3[4][27] = BLOCK4;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = GA;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK5)
					{
						map3[5][27] = BLOCK5;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = GA;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK6)
					{
						map3[6][27] = BLOCK6;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = GA;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK7)
					{
						map3[7][27] = BLOCK7;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = GA;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK8)
					{
						map3[8][27] = BLOCK8;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = GA;
						playerPosY += playerSpeed;

					}
				}
				if (map3[playerMapY][playerMapX] == SU)
				{
					if (map3[playerMapY + 1][playerMapX] == YUKA)
					{
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = SU;
						if (map3[1][27] != BLOCK1 || map3[1][27] == BLOCK1)
						{
							if (map3[1][27] == BLOCK1 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK1;
								map3[1][27] = YUKA;
							}
						}
						if (map3[2][27] != BLOCK22 || map3[2][27] == BLOCK22)
						{
							if (map3[2][27] == BLOCK22 && map3[playerMapY][playerMapX] == map3[4][11])
							{
								map3[playerMapY][playerMapX] = BLOCK22;
								map3[2][27] = YUKA;
							}
						}
						if (map3[3][27] != BLOCK3 || map3[3][27] == BLOCK3)
						{
							if (map3[3][27] == BLOCK3 && map3[playerMapY][playerMapX] == map3[4][13])
							{
								map3[playerMapY][playerMapX] = BLOCK3;
								map3[3][27] = YUKA;
							}
						}
						if (map3[4][27] != BLOCK4 || map3[4][27] == BLOCK4)
						{
							if (map3[4][27] == BLOCK4 && map3[playerMapY][playerMapX] == map3[4][15])
							{
								map3[playerMapY][playerMapX] = BLOCK4;
								map3[4][27] = YUKA;
							}
						}
						if (map3[5][27] != BLOCK5 || map3[5][27] == BLOCK5)
						{
							if (map3[5][27] == BLOCK5 && map3[playerMapY][playerMapX] == map3[4][17])
							{
								map3[playerMapY][playerMapX] = BLOCK5;
								map3[5][27] = YUKA;
							}
						}
						if (map3[6][27] != BLOCK6 || map3[6][27] == BLOCK6)
						{

							if (map3[6][27] == BLOCK6 && map3[playerMapY][playerMapX] == /*6以降は後で*/map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK6;
								map3[6][27] = YUKA;
							}
						}
						if (map3[7][27] != BLOCK7 || map3[7][27] == BLOCK7)
						{
							if (map3[7][27] == BLOCK7 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK7;
								map3[7][27] = YUKA;
							}
						}
						if (map3[8][27] != BLOCK8 || map3[8][27] == BLOCK8)
						{
							if (map3[8][27] == BLOCK8 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK8;
								map3[8][27] = YUKA;
							}
						}
						playerPosY += playerSpeed;
					}

					if (map3[playerMapY + 1][playerMapX] == BLOCK1)
					{
						map3[1][27] = BLOCK1;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = SU;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK22)
					{
						map3[2][27] = BLOCK22;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = SU;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK3)
					{
						map3[3][27] = BLOCK3;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = SU;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK4)
					{
						map3[4][27] = BLOCK4;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = SU;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK5)
					{
						map3[5][27] = BLOCK5;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = SU;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK6)
					{
						map3[6][27] = BLOCK6;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = SU;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK7)
					{
						map3[7][27] = BLOCK7;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = SU;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK8)
					{
						map3[8][27] = BLOCK8;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = SU;
						playerPosY += playerSpeed;

					}
				}
				if (map3[playerMapY][playerMapX] == SO)
				{
					if (map3[playerMapY + 1][playerMapX] == YUKA)
					{
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = SO;
						if (map3[1][27] != BLOCK1 || map3[1][27] == BLOCK1)
						{
							if (map3[1][27] == BLOCK1 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK1;
								map3[1][27] = YUKA;
							}
						}
						if (map3[2][27] != BLOCK22 || map3[2][27] == BLOCK22)
						{
							if (map3[2][27] == BLOCK22 && map3[playerMapY][playerMapX] == map3[4][11])
							{
								map3[playerMapY][playerMapX] = BLOCK22;
								map3[2][27] = YUKA;
							}
						}
						if (map3[3][27] != BLOCK3 || map3[3][27] == BLOCK3)
						{
							if (map3[3][27] == BLOCK3 && map3[playerMapY][playerMapX] == map3[4][13])
							{
								map3[playerMapY][playerMapX] = BLOCK3;
								map3[3][27] = YUKA;
							}
						}
						if (map3[4][27] != BLOCK4 || map3[4][27] == BLOCK4)
						{
							if (map3[4][27] == BLOCK4 && map3[playerMapY][playerMapX] == map3[4][15])
							{
								map3[playerMapY][playerMapX] = BLOCK4;
								map3[4][27] = YUKA;
							}
						}
						if (map3[5][27] != BLOCK5 || map3[5][27] == BLOCK5)
						{
							if (map3[5][27] == BLOCK5 && map3[playerMapY][playerMapX] == map3[4][17])
							{
								map3[playerMapY][playerMapX] = BLOCK5;
								map3[5][27] = YUKA;
							}
						}
						if (map3[6][27] != BLOCK6 || map3[6][27] == BLOCK6)
						{

							if (map3[6][27] == BLOCK6 && map3[playerMapY][playerMapX] == /*6以降は後で*/map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK6;
								map3[6][27] = YUKA;
							}
						}
						if (map3[7][27] != BLOCK7 || map3[7][27] == BLOCK7)
						{
							if (map3[7][27] == BLOCK7 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK7;
								map3[7][27] = YUKA;
							}
						}
						if (map3[8][27] != BLOCK8 || map3[8][27] == BLOCK8)
						{
							if (map3[8][27] == BLOCK8 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK8;
								map3[8][27] = YUKA;
							}
						}
						playerPosY += playerSpeed;
					}

					if (map3[playerMapY + 1][playerMapX] == BLOCK1)
					{
						map3[1][27] = BLOCK1;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = SO;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK22)
					{
						map3[2][27] = BLOCK22;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = SO;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK3)
					{
						map3[3][27] = BLOCK3;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = SO;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK4)
					{
						map3[4][27] = BLOCK4;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = SO;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK5)
					{
						map3[5][27] = BLOCK5;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = SO;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK6)
					{
						map3[6][27] = BLOCK6;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = SO;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK7)
					{
						map3[7][27] = BLOCK7;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = SO;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK8)
					{
						map3[8][27] = BLOCK8;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = SO;
						playerPosY += playerSpeed;

					}
				}
				if (map3[playerMapY][playerMapX] == NI)
				{
					if (map3[playerMapY + 1][playerMapX] == YUKA)
					{
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = NI;
						if (map3[1][27] != BLOCK1 || map3[1][27] == BLOCK1)
						{
							if (map3[1][27] == BLOCK1 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK1;
								map3[1][27] = YUKA;
							}
						}
						if (map3[2][27] != BLOCK22 || map3[2][27] == BLOCK22)
						{
							if (map3[2][27] == BLOCK22 && map3[playerMapY][playerMapX] == map3[4][11])
							{
								map3[playerMapY][playerMapX] = BLOCK22;
								map3[2][27] = YUKA;
							}
						}
						if (map3[3][27] != BLOCK3 || map3[3][27] == BLOCK3)
						{
							if (map3[3][27] == BLOCK3 && map3[playerMapY][playerMapX] == map3[4][13])
							{
								map3[playerMapY][playerMapX] = BLOCK3;
								map3[3][27] = YUKA;
							}
						}
						if (map3[4][27] != BLOCK4 || map3[4][27] == BLOCK4)
						{
							if (map3[4][27] == BLOCK4 && map3[playerMapY][playerMapX] == map3[4][15])
							{
								map3[playerMapY][playerMapX] = BLOCK4;
								map3[4][27] = YUKA;
							}
						}
						if (map3[5][27] != BLOCK5 || map3[5][27] == BLOCK5)
						{
							if (map3[5][27] == BLOCK5 && map3[playerMapY][playerMapX] == map3[4][17])
							{
								map3[playerMapY][playerMapX] = BLOCK5;
								map3[5][27] = YUKA;
							}
						}
						if (map3[6][27] != BLOCK6 || map3[6][27] == BLOCK6)
						{

							if (map3[6][27] == BLOCK6 && map3[playerMapY][playerMapX] == /*6以降は後で*/map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK6;
								map3[6][27] = YUKA;
							}
						}
						if (map3[7][27] != BLOCK7 || map3[7][27] == BLOCK7)
						{
							if (map3[7][27] == BLOCK7 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK7;
								map3[7][27] = YUKA;
							}
						}
						if (map3[8][27] != BLOCK8 || map3[8][27] == BLOCK8)
						{
							if (map3[8][27] == BLOCK8 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK8;
								map3[8][27] = YUKA;
							}
						}
						playerPosY += playerSpeed;
					}

					if (map3[playerMapY + 1][playerMapX] == BLOCK1)
					{
						map3[1][27] = BLOCK1;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = NI;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK22)
					{
						map3[2][27] = BLOCK22;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = NI;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK3)
					{
						map3[3][27] = BLOCK3;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = NI;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK4)
					{
						map3[4][27] = BLOCK4;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = NI;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK5)
					{
						map3[5][27] = BLOCK5;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = NI;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK6)
					{
						map3[6][27] = BLOCK6;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = NI;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK7)
					{
						map3[7][27] = BLOCK7;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = NI;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK8)
					{
						map3[8][27] = BLOCK8;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = NI;
						playerPosY += playerSpeed;

					}
				}
				if (map3[playerMapY][playerMapX] == CHI)
				{
					if (map3[playerMapY + 1][playerMapX] == YUKA)
					{
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = CHI;
						if (map3[1][27] != BLOCK1 || map3[1][27] == BLOCK1)
						{
							if (map3[1][27] == BLOCK1 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK1;
								map3[1][27] = YUKA;
							}
						}
						if (map3[2][27] != BLOCK22 || map3[2][27] == BLOCK22)
						{
							if (map3[2][27] == BLOCK22 && map3[playerMapY][playerMapX] == map3[4][11])
							{
								map3[playerMapY][playerMapX] = BLOCK22;
								map3[2][27] = YUKA;
							}
						}
						if (map3[3][27] != BLOCK3 || map3[3][27] == BLOCK3)
						{
							if (map3[3][27] == BLOCK3 && map3[playerMapY][playerMapX] == map3[4][13])
							{
								map3[playerMapY][playerMapX] = BLOCK3;
								map3[3][27] = YUKA;
							}
						}
						if (map3[4][27] != BLOCK4 || map3[4][27] == BLOCK4)
						{
							if (map3[4][27] == BLOCK4 && map3[playerMapY][playerMapX] == map3[4][15])
							{
								map3[playerMapY][playerMapX] = BLOCK4;
								map3[4][27] = YUKA;
							}
						}
						if (map3[5][27] != BLOCK5 || map3[5][27] == BLOCK5)
						{
							if (map3[5][27] == BLOCK5 && map3[playerMapY][playerMapX] == map3[4][17])
							{
								map3[playerMapY][playerMapX] = BLOCK5;
								map3[5][27] = YUKA;
							}
						}
						if (map3[6][27] != BLOCK6 || map3[6][27] == BLOCK6)
						{

							if (map3[6][27] == BLOCK6 && map3[playerMapY][playerMapX] == /*6以降は後で*/map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK6;
								map3[6][27] = YUKA;
							}
						}
						if (map3[7][27] != BLOCK7 || map3[7][27] == BLOCK7)
						{
							if (map3[7][27] == BLOCK7 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK7;
								map3[7][27] = YUKA;
							}
						}
						if (map3[8][27] != BLOCK8 || map3[8][27] == BLOCK8)
						{
							if (map3[8][27] == BLOCK8 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK8;
								map3[8][27] = YUKA;
							}
						}
						playerPosY += playerSpeed;
					}

					if (map3[playerMapY + 1][playerMapX] == BLOCK1)
					{
						map3[1][27] = BLOCK1;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = CHI;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK22)
					{
						map3[2][27] = BLOCK22;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = CHI;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK3)
					{
						map3[3][27] = BLOCK3;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = CHI;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK4)
					{
						map3[4][27] = BLOCK4;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = CHI;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK5)
					{
						map3[5][27] = BLOCK5;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = CHI;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK6)
					{
						map3[6][27] = BLOCK6;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = CHI;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK7)
					{
						map3[7][27] = BLOCK7;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = CHI;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK8)
					{
						map3[8][27] = BLOCK8;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = CHI;
						playerPosY += playerSpeed;

					}
				}

				if (map3[playerMapY][playerMapX] == NU)
				{
					if (map3[playerMapY + 1][playerMapX] == YUKA)
					{
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = NU;
						if (map3[1][27] != BLOCK1 || map3[1][27] == BLOCK1)
						{
							if (map3[1][27] == BLOCK1 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK1;
								map3[1][27] = YUKA;
							}
						}
						if (map3[2][27] != BLOCK22 || map3[2][27] == BLOCK22)
						{
							if (map3[2][27] == BLOCK22 && map3[playerMapY][playerMapX] == map3[4][11])
							{
								map3[playerMapY][playerMapX] = BLOCK22;
								map3[2][27] = YUKA;
							}
						}
						if (map3[3][27] != BLOCK3 || map3[3][27] == BLOCK3)
						{
							if (map3[3][27] == BLOCK3 && map3[playerMapY][playerMapX] == map3[4][13])
							{
								map3[playerMapY][playerMapX] = BLOCK3;
								map3[3][27] = YUKA;
							}
						}
						if (map3[4][27] != BLOCK4 || map3[4][27] == BLOCK4)
						{
							if (map3[4][27] == BLOCK4 && map3[playerMapY][playerMapX] == map3[4][15])
							{
								map3[playerMapY][playerMapX] = BLOCK4;
								map3[4][27] = YUKA;
							}
						}
						if (map3[5][27] != BLOCK5 || map3[5][27] == BLOCK5)
						{
							if (map3[5][27] == BLOCK5 && map3[playerMapY][playerMapX] == map3[4][17])
							{
								map3[playerMapY][playerMapX] = BLOCK5;
								map3[5][27] = YUKA;
							}
						}
						if (map3[6][27] != BLOCK6 || map3[6][27] == BLOCK6)
						{

							if (map3[6][27] == BLOCK6 && map3[playerMapY][playerMapX] == /*6以降は後で*/map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK6;
								map3[6][27] = YUKA;
							}
						}
						if (map3[7][27] != BLOCK7 || map3[7][27] == BLOCK7)
						{
							if (map3[7][27] == BLOCK7 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK7;
								map3[7][27] = YUKA;
							}
						}
						if (map3[8][27] != BLOCK8 || map3[8][27] == BLOCK8)
						{
							if (map3[8][27] == BLOCK8 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK8;
								map3[8][27] = YUKA;
							}
						}
						playerPosY += playerSpeed;
					}

					if (map3[playerMapY + 1][playerMapX] == BLOCK1)
					{
						map3[1][27] = BLOCK1;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = NU;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK22)
					{
						map3[2][27] = BLOCK22;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = NU;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK3)
					{
						map3[3][27] = BLOCK3;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = NU;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK4)
					{
						map3[4][27] = BLOCK4;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = NU;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK5)
					{
						map3[5][27] = BLOCK5;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = NU;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK6)
					{
						map3[6][27] = BLOCK6;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = NU;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK7)
					{
						map3[7][27] = BLOCK7;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = NU;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK8)
					{
						map3[8][27] = BLOCK8;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = NU;
						playerPosY += playerSpeed;

					}
				}
				if (map3[playerMapY][playerMapX] == NE)
				{
					if (map3[playerMapY + 1][playerMapX] == YUKA)
					{
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = NE;
						if (map3[1][27] != BLOCK1 || map3[1][27] == BLOCK1)
						{
							if (map3[1][27] == BLOCK1 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK1;
								map3[1][27] = YUKA;
							}
						}
						if (map3[2][27] != BLOCK22 || map3[2][27] == BLOCK22)
						{
							if (map3[2][27] == BLOCK22 && map3[playerMapY][playerMapX] == map3[4][11])
							{
								map3[playerMapY][playerMapX] = BLOCK22;
								map3[2][27] = YUKA;
							}
						}
						if (map3[3][27] != BLOCK3 || map3[3][27] == BLOCK3)
						{
							if (map3[3][27] == BLOCK3 && map3[playerMapY][playerMapX] == map3[4][13])
							{
								map3[playerMapY][playerMapX] = BLOCK3;
								map3[3][27] = YUKA;
							}
						}
						if (map3[4][27] != BLOCK4 || map3[4][27] == BLOCK4)
						{
							if (map3[4][27] == BLOCK4 && map3[playerMapY][playerMapX] == map3[4][15])
							{
								map3[playerMapY][playerMapX] = BLOCK4;
								map3[4][27] = YUKA;
							}
						}
						if (map3[5][27] != BLOCK5 || map3[5][27] == BLOCK5)
						{
							if (map3[5][27] == BLOCK5 && map3[playerMapY][playerMapX] == map3[4][17])
							{
								map3[playerMapY][playerMapX] = BLOCK5;
								map3[5][27] = YUKA;
							}
						}
						if (map3[6][27] != BLOCK6 || map3[6][27] == BLOCK6)
						{

							if (map3[6][27] == BLOCK6 && map3[playerMapY][playerMapX] == /*6以降は後で*/map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK6;
								map3[6][27] = YUKA;
							}
						}
						if (map3[7][27] != BLOCK7 || map3[7][27] == BLOCK7)
						{
							if (map3[7][27] == BLOCK7 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK7;
								map3[7][27] = YUKA;
							}
						}
						if (map3[8][27] != BLOCK8 || map3[8][27] == BLOCK8)
						{
							if (map3[8][27] == BLOCK8 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK8;
								map3[8][27] = YUKA;
							}
						}
						playerPosY += playerSpeed;
					}

					if (map3[playerMapY + 1][playerMapX] == BLOCK1)
					{
						map3[1][27] = BLOCK1;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = NE;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK22)
					{
						map3[2][27] = BLOCK22;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = NE;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK3)
					{
						map3[3][27] = BLOCK3;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = NE;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK4)
					{
						map3[4][27] = BLOCK4;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = NE;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK5)
					{
						map3[5][27] = BLOCK5;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = NE;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK6)
					{
						map3[6][27] = BLOCK6;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = NE;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK7)
					{
						map3[7][27] = BLOCK7;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = NE;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK8)
					{
						map3[8][27] = BLOCK8;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = NE;
						playerPosY += playerSpeed;

					}
				}
				if (map3[playerMapY][playerMapX] == RA)
				{
					if (map3[playerMapY + 1][playerMapX] == YUKA)
					{
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = RA;
						if (map3[1][27] != BLOCK1 || map3[1][27] == BLOCK1)
						{
							if (map3[1][27] == BLOCK1 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK1;
								map3[1][27] = YUKA;
							}
						}
						if (map3[2][27] != BLOCK22 || map3[2][27] == BLOCK22)
						{
							if (map3[2][27] == BLOCK22 && map3[playerMapY][playerMapX] == map3[4][11])
							{
								map3[playerMapY][playerMapX] = BLOCK22;
								map3[2][27] = YUKA;
							}
						}
						if (map3[3][27] != BLOCK3 || map3[3][27] == BLOCK3)
						{
							if (map3[3][27] == BLOCK3 && map3[playerMapY][playerMapX] == map3[4][13])
							{
								map3[playerMapY][playerMapX] = BLOCK3;
								map3[3][27] = YUKA;
							}
						}
						if (map3[4][27] != BLOCK4 || map3[4][27] == BLOCK4)
						{
							if (map3[4][27] == BLOCK4 && map3[playerMapY][playerMapX] == map3[4][15])
							{
								map3[playerMapY][playerMapX] = BLOCK4;
								map3[4][27] = YUKA;
							}
						}
						if (map3[5][27] != BLOCK5 || map3[5][27] == BLOCK5)
						{
							if (map3[5][27] == BLOCK5 && map3[playerMapY][playerMapX] == map3[4][17])
							{
								map3[playerMapY][playerMapX] = BLOCK5;
								map3[5][27] = YUKA;
							}
						}
						if (map3[6][27] != BLOCK6 || map3[6][27] == BLOCK6)
						{

							if (map3[6][27] == BLOCK6 && map3[playerMapY][playerMapX] == /*6以降は後で*/map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK6;
								map3[6][27] = YUKA;
							}
						}
						if (map3[7][27] != BLOCK7 || map3[7][27] == BLOCK7)
						{
							if (map3[7][27] == BLOCK7 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK7;
								map3[7][27] = YUKA;
							}
						}
						if (map3[8][27] != BLOCK8 || map3[8][27] == BLOCK8)
						{
							if (map3[8][27] == BLOCK8 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK8;
								map3[8][27] = YUKA;
							}
						}
						playerPosY += playerSpeed;
					}

					if (map3[playerMapY + 1][playerMapX] == BLOCK1)
					{
						map3[1][27] = BLOCK1;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = RA;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK22)
					{
						map3[2][27] = BLOCK22;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = RA;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK3)
					{
						map3[3][27] = BLOCK3;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = RA;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK4)
					{
						map3[4][27] = BLOCK4;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = RA;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK5)
					{
						map3[5][27] = BLOCK5;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = RA;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK6)
					{
						map3[6][27] = BLOCK6;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = RA;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK7)
					{
						map3[7][27] = BLOCK7;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = RA;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK8)
					{
						map3[8][27] = BLOCK8;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = RA;
						playerPosY += playerSpeed;

					}
				}
				if (map3[playerMapY][playerMapX] == HO)
				{
					if (map3[playerMapY + 1][playerMapX] == YUKA)
					{
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = HO;
						if (map3[1][27] != BLOCK1 || map3[1][27] == BLOCK1)
						{
							if (map3[1][27] == BLOCK1 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK1;
								map3[1][27] = YUKA;
							}
						}
						if (map3[2][27] != BLOCK22 || map3[2][27] == BLOCK22)
						{
							if (map3[2][27] == BLOCK22 && map3[playerMapY][playerMapX] == map3[4][11])
							{
								map3[playerMapY][playerMapX] = BLOCK22;
								map3[2][27] = YUKA;
							}
						}
						if (map3[3][27] != BLOCK3 || map3[3][27] == BLOCK3)
						{
							if (map3[3][27] == BLOCK3 && map3[playerMapY][playerMapX] == map3[4][13])
							{
								map3[playerMapY][playerMapX] = BLOCK3;
								map3[3][27] = YUKA;
							}
						}
						if (map3[4][27] != BLOCK4 || map3[4][27] == BLOCK4)
						{
							if (map3[4][27] == BLOCK4 && map3[playerMapY][playerMapX] == map3[4][15])
							{
								map3[playerMapY][playerMapX] = BLOCK4;
								map3[4][27] = YUKA;
							}
						}
						if (map3[5][27] != BLOCK5 || map3[5][27] == BLOCK5)
						{
							if (map3[5][27] == BLOCK5 && map3[playerMapY][playerMapX] == map3[4][17])
							{
								map3[playerMapY][playerMapX] = BLOCK5;
								map3[5][27] = YUKA;
							}
						}
						if (map3[6][27] != BLOCK6 || map3[6][27] == BLOCK6)
						{

							if (map3[6][27] == BLOCK6 && map3[playerMapY][playerMapX] == /*6以降は後で*/map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK6;
								map3[6][27] = YUKA;
							}
						}
						if (map3[7][27] != BLOCK7 || map3[7][27] == BLOCK7)
						{
							if (map3[7][27] == BLOCK7 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK7;
								map3[7][27] = YUKA;
							}
						}
						if (map3[8][27] != BLOCK8 || map3[8][27] == BLOCK8)
						{
							if (map3[8][27] == BLOCK8 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK8;
								map3[8][27] = YUKA;
							}
						}
						playerPosY += playerSpeed;
					}

					if (map3[playerMapY + 1][playerMapX] == BLOCK1)
					{
						map3[1][27] = BLOCK1;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = HO;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK22)
					{
						map3[2][27] = BLOCK22;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = HO;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK3)
					{
						map3[3][27] = BLOCK3;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = HO;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK4)
					{
						map3[4][27] = BLOCK4;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = HO;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK5)
					{
						map3[5][27] = BLOCK5;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = HO;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK6)
					{
						map3[6][27] = BLOCK6;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = HO;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK7)
					{
						map3[7][27] = BLOCK7;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = HO;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK8)
					{
						map3[8][27] = BLOCK8;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = HO;
						playerPosY += playerSpeed;

					}
				}
				if (map3[playerMapY][playerMapX] == ZE)
				{
					if (map3[playerMapY + 1][playerMapX] == YUKA)
					{
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = ZE;
						if (map3[1][27] != BLOCK1 || map3[1][27] == BLOCK1)
						{
							if (map3[1][27] == BLOCK1 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK1;
								map3[1][27] = YUKA;
							}
						}
						if (map3[2][27] != BLOCK22 || map3[2][27] == BLOCK22)
						{
							if (map3[2][27] == BLOCK22 && map3[playerMapY][playerMapX] == map3[4][11])
							{
								map3[playerMapY][playerMapX] = BLOCK22;
								map3[2][27] = YUKA;
							}
						}
						if (map3[3][27] != BLOCK3 || map3[3][27] == BLOCK3)
						{
							if (map3[3][27] == BLOCK3 && map3[playerMapY][playerMapX] == map3[4][13])
							{
								map3[playerMapY][playerMapX] = BLOCK3;
								map3[3][27] = YUKA;
							}
						}
						if (map3[4][27] != BLOCK4 || map3[4][27] == BLOCK4)
						{
							if (map3[4][27] == BLOCK4 && map3[playerMapY][playerMapX] == map3[4][15])
							{
								map3[playerMapY][playerMapX] = BLOCK4;
								map3[4][27] = YUKA;
							}
						}
						if (map3[5][27] != BLOCK5 || map3[5][27] == BLOCK5)
						{
							if (map3[5][27] == BLOCK5 && map3[playerMapY][playerMapX] == map3[4][17])
							{
								map3[playerMapY][playerMapX] = BLOCK5;
								map3[5][27] = YUKA;
							}
						}
						if (map3[6][27] != BLOCK6 || map3[6][27] == BLOCK6)
						{

							if (map3[6][27] == BLOCK6 && map3[playerMapY][playerMapX] == /*6以降は後で*/map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK6;
								map3[6][27] = YUKA;
							}
						}
						if (map3[7][27] != BLOCK7 || map3[7][27] == BLOCK7)
						{
							if (map3[7][27] == BLOCK7 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK7;
								map3[7][27] = YUKA;
							}
						}
						if (map3[8][27] != BLOCK8 || map3[8][27] == BLOCK8)
						{
							if (map3[8][27] == BLOCK8 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK8;
								map3[8][27] = YUKA;
							}
						}
						playerPosY += playerSpeed;
					}

					if (map3[playerMapY + 1][playerMapX] == BLOCK1)
					{
						map3[1][27] = BLOCK1;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = ZE;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK22)
					{
						map3[2][27] = BLOCK22;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = ZE;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK3)
					{
						map3[3][27] = BLOCK3;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = ZE;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK4)
					{
						map3[4][27] = BLOCK4;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = ZE;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK5)
					{
						map3[5][27] = BLOCK5;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = ZE;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK6)
					{
						map3[6][27] = BLOCK6;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = ZE;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK7)
					{
						map3[7][27] = BLOCK7;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = ZE;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK8)
					{
						map3[8][27] = BLOCK8;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = ZE;
						playerPosY += playerSpeed;

					}
				}
				if (map3[playerMapY][playerMapX] == RU)
				{
					if (map3[playerMapY + 1][playerMapX] == YUKA)
					{
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = RU;
						if (map3[1][27] != BLOCK1 || map3[1][27] == BLOCK1)
						{
							if (map3[1][27] == BLOCK1 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK1;
								map3[1][27] = YUKA;
							}
						}
						if (map3[2][27] != BLOCK22 || map3[2][27] == BLOCK22)
						{
							if (map3[2][27] == BLOCK22 && map3[playerMapY][playerMapX] == map3[4][11])
							{
								map3[playerMapY][playerMapX] = BLOCK22;
								map3[2][27] = YUKA;
							}
						}
						if (map3[3][27] != BLOCK3 || map3[3][27] == BLOCK3)
						{
							if (map3[3][27] == BLOCK3 && map3[playerMapY][playerMapX] == map3[4][13])
							{
								map3[playerMapY][playerMapX] = BLOCK3;
								map3[3][27] = YUKA;
							}
						}
						if (map3[4][27] != BLOCK4 || map3[4][27] == BLOCK4)
						{
							if (map3[4][27] == BLOCK4 && map3[playerMapY][playerMapX] == map3[4][15])
							{
								map3[playerMapY][playerMapX] = BLOCK4;
								map3[4][27] = YUKA;
							}
						}
						if (map3[5][27] != BLOCK5 || map3[5][27] == BLOCK5)
						{
							if (map3[5][27] == BLOCK5 && map3[playerMapY][playerMapX] == map3[4][17])
							{
								map3[playerMapY][playerMapX] = BLOCK5;
								map3[5][27] = YUKA;
							}
						}
						if (map3[6][27] != BLOCK6 || map3[6][27] == BLOCK6)
						{

							if (map3[6][27] == BLOCK6 && map3[playerMapY][playerMapX] == /*6以降は後で*/map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK6;
								map3[6][27] = YUKA;
							}
						}
						if (map3[7][27] != BLOCK7 || map3[7][27] == BLOCK7)
						{
							if (map3[7][27] == BLOCK7 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK7;
								map3[7][27] = YUKA;
							}
						}
						if (map3[8][27] != BLOCK8 || map3[8][27] == BLOCK8)
						{
							if (map3[8][27] == BLOCK8 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK8;
								map3[8][27] = YUKA;
							}
						}
						playerPosY += playerSpeed;
					}

					if (map3[playerMapY + 1][playerMapX] == BLOCK1)
					{
						map3[1][27] = BLOCK1;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = RU;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK22)
					{
						map3[2][27] = BLOCK22;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = RU;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK3)
					{
						map3[3][27] = BLOCK3;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = RU;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK4)
					{
						map3[4][27] = BLOCK4;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = RU;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK5)
					{
						map3[5][27] = BLOCK5;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = RU;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK6)
					{
						map3[6][27] = BLOCK6;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = RU;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK7)
					{
						map3[7][27] = BLOCK7;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = RU;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK8)
					{
						map3[8][27] = BLOCK8;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = RU;
						playerPosY += playerSpeed;

					}
				}
				if (map3[playerMapY][playerMapX] == YU)
				{
					if (map3[playerMapY + 1][playerMapX] == YUKA)
					{
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = YU;
						if (map3[1][27] != BLOCK1 || map3[1][27] == BLOCK1)
						{
							if (map3[1][27] == BLOCK1 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK1;
								map3[1][27] = YUKA;
							}
						}
						if (map3[2][27] != BLOCK22 || map3[2][27] == BLOCK22)
						{
							if (map3[2][27] == BLOCK22 && map3[playerMapY][playerMapX] == map3[4][11])
							{
								map3[playerMapY][playerMapX] = BLOCK22;
								map3[2][27] = YUKA;
							}
						}
						if (map3[3][27] != BLOCK3 || map3[3][27] == BLOCK3)
						{
							if (map3[3][27] == BLOCK3 && map3[playerMapY][playerMapX] == map3[4][13])
							{
								map3[playerMapY][playerMapX] = BLOCK3;
								map3[3][27] = YUKA;
							}
						}
						if (map3[4][27] != BLOCK4 || map3[4][27] == BLOCK4)
						{
							if (map3[4][27] == BLOCK4 && map3[playerMapY][playerMapX] == map3[4][15])
							{
								map3[playerMapY][playerMapX] = BLOCK4;
								map3[4][27] = YUKA;
							}
						}
						if (map3[5][27] != BLOCK5 || map3[5][27] == BLOCK5)
						{
							if (map3[5][27] == BLOCK5 && map3[playerMapY][playerMapX] == map3[4][17])
							{
								map3[playerMapY][playerMapX] = BLOCK5;
								map3[5][27] = YUKA;
							}
						}
						if (map3[6][27] != BLOCK6 || map3[6][27] == BLOCK6)
						{

							if (map3[6][27] == BLOCK6 && map3[playerMapY][playerMapX] == /*6以降は後で*/map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK6;
								map3[6][27] = YUKA;
							}
						}
						if (map3[7][27] != BLOCK7 || map3[7][27] == BLOCK7)
						{
							if (map3[7][27] == BLOCK7 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK7;
								map3[7][27] = YUKA;
							}
						}
						if (map3[8][27] != BLOCK8 || map3[8][27] == BLOCK8)
						{
							if (map3[8][27] == BLOCK8 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK8;
								map3[8][27] = YUKA;
							}
						}
						playerPosY += playerSpeed;
					}

					if (map3[playerMapY + 1][playerMapX] == BLOCK1)
					{
						map3[1][27] = BLOCK1;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = YU;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK22)
					{
						map3[2][27] = BLOCK22;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = YU;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK3)
					{
						map3[3][27] = BLOCK3;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = YU;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK4)
					{
						map3[4][27] = BLOCK4;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = YU;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK5)
					{
						map3[5][27] = BLOCK5;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = YU;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK6)
					{
						map3[6][27] = BLOCK6;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = YU;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK7)
					{
						map3[7][27] = BLOCK7;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = YU;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK8)
					{
						map3[8][27] = BLOCK8;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = YU;
						playerPosY += playerSpeed;

					}
				}
				if (map3[playerMapY][playerMapX] == DO)
				{
					if (map3[playerMapY + 1][playerMapX] == YUKA)
					{
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = DO;
						if (map3[1][27] != BLOCK1 || map3[1][27] == BLOCK1)
						{
							if (map3[1][27] == BLOCK1 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK1;
								map3[1][27] = YUKA;
							}
						}
						if (map3[2][27] != BLOCK22 || map3[2][27] == BLOCK22)
						{
							if (map3[2][27] == BLOCK22 && map3[playerMapY][playerMapX] == map3[4][11])
							{
								map3[playerMapY][playerMapX] = BLOCK22;
								map3[2][27] = YUKA;
							}
						}
						if (map3[3][27] != BLOCK3 || map3[3][27] == BLOCK3)
						{
							if (map3[3][27] == BLOCK3 && map3[playerMapY][playerMapX] == map3[4][13])
							{
								map3[playerMapY][playerMapX] = BLOCK3;
								map3[3][27] = YUKA;
							}
						}
						if (map3[4][27] != BLOCK4 || map3[4][27] == BLOCK4)
						{
							if (map3[4][27] == BLOCK4 && map3[playerMapY][playerMapX] == map3[4][15])
							{
								map3[playerMapY][playerMapX] = BLOCK4;
								map3[4][27] = YUKA;
							}
						}
						if (map3[5][27] != BLOCK5 || map3[5][27] == BLOCK5)
						{
							if (map3[5][27] == BLOCK5 && map3[playerMapY][playerMapX] == map3[4][17])
							{
								map3[playerMapY][playerMapX] = BLOCK5;
								map3[5][27] = YUKA;
							}
						}
						if (map3[6][27] != BLOCK6 || map3[6][27] == BLOCK6)
						{

							if (map3[6][27] == BLOCK6 && map3[playerMapY][playerMapX] == /*6以降は後で*/map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK6;
								map3[6][27] = YUKA;
							}
						}
						if (map3[7][27] != BLOCK7 || map3[7][27] == BLOCK7)
						{
							if (map3[7][27] == BLOCK7 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK7;
								map3[7][27] = YUKA;
							}
						}
						if (map3[8][27] != BLOCK8 || map3[8][27] == BLOCK8)
						{
							if (map3[8][27] == BLOCK8 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK8;
								map3[8][27] = YUKA;
							}
						}
						playerPosY += playerSpeed;
					}

					if (map3[playerMapY + 1][playerMapX] == BLOCK1)
					{
						map3[1][27] = BLOCK1;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = DO;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK22)
					{
						map3[2][27] = BLOCK22;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = DO;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK3)
					{
						map3[3][27] = BLOCK3;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = DO;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK4)
					{
						map3[4][27] = BLOCK4;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = DO;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK5)
					{
						map3[5][27] = BLOCK5;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = DO;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK6)
					{
						map3[6][27] = BLOCK6;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = DO;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK7)
					{
						map3[7][27] = BLOCK7;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = DO;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK8)
					{
						map3[8][27] = BLOCK8;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = DO;
						playerPosY += playerSpeed;

					}
				}
				if (map3[playerMapY][playerMapX] == GO)
				{
					if (map3[playerMapY + 1][playerMapX] == YUKA)
					{
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = GO;
						if (map3[1][27] != BLOCK1 || map3[1][27] == BLOCK1)
						{
							if (map3[1][27] == BLOCK1 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK1;
								map3[1][27] = YUKA;
							}
						}
						if (map3[2][27] != BLOCK22 || map3[2][27] == BLOCK22)
						{
							if (map3[2][27] == BLOCK22 && map3[playerMapY][playerMapX] == map3[4][11])
							{
								map3[playerMapY][playerMapX] = BLOCK22;
								map3[2][27] = YUKA;
							}
						}
						if (map3[3][27] != BLOCK3 || map3[3][27] == BLOCK3)
						{
							if (map3[3][27] == BLOCK3 && map3[playerMapY][playerMapX] == map3[4][13])
							{
								map3[playerMapY][playerMapX] = BLOCK3;
								map3[3][27] = YUKA;
							}
						}
						if (map3[4][27] != BLOCK4 || map3[4][27] == BLOCK4)
						{
							if (map3[4][27] == BLOCK4 && map3[playerMapY][playerMapX] == map3[4][15])
							{
								map3[playerMapY][playerMapX] = BLOCK4;
								map3[4][27] = YUKA;
							}
						}
						if (map3[5][27] != BLOCK5 || map3[5][27] == BLOCK5)
						{
							if (map3[5][27] == BLOCK5 && map3[playerMapY][playerMapX] == map3[4][17])
							{
								map3[playerMapY][playerMapX] = BLOCK5;
								map3[5][27] = YUKA;
							}
						}
						if (map3[6][27] != BLOCK6 || map3[6][27] == BLOCK6)
						{

							if (map3[6][27] == BLOCK6 && map3[playerMapY][playerMapX] == /*6以降は後で*/map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK6;
								map3[6][27] = YUKA;
							}
						}
						if (map3[7][27] != BLOCK7 || map3[7][27] == BLOCK7)
						{
							if (map3[7][27] == BLOCK7 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK7;
								map3[7][27] = YUKA;
							}
						}
						if (map3[8][27] != BLOCK8 || map3[8][27] == BLOCK8)
						{
							if (map3[8][27] == BLOCK8 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK8;
								map3[8][27] = YUKA;
							}
						}
						playerPosY += playerSpeed;
					}

					if (map3[playerMapY + 1][playerMapX] == BLOCK1)
					{
						map3[1][27] = BLOCK1;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = GO;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK22)
					{
						map3[2][27] = BLOCK22;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = GO;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK3)
					{
						map3[3][27] = BLOCK3;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = GO;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK4)
					{
						map3[4][27] = BLOCK4;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = GO;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK5)
					{
						map3[5][27] = BLOCK5;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = GO;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK6)
					{
						map3[6][27] = BLOCK6;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = GO;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK7)
					{
						map3[7][27] = BLOCK7;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = GO;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK8)
					{
						map3[8][27] = BLOCK8;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = GO;
						playerPosY += playerSpeed;

					}
				}
				if (map3[playerMapY][playerMapX] == ZE)
				{
					if (map3[playerMapY + 1][playerMapX] == YUKA)
					{
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = ZE;
						if (map3[1][27] != BLOCK1 || map3[1][27] == BLOCK1)
						{
							if (map3[1][27] == BLOCK1 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK1;
								map3[1][27] = YUKA;
							}
						}
						if (map3[2][27] != BLOCK22 || map3[2][27] == BLOCK22)
						{
							if (map3[2][27] == BLOCK22 && map3[playerMapY][playerMapX] == map3[4][11])
							{
								map3[playerMapY][playerMapX] = BLOCK22;
								map3[2][27] = YUKA;
							}
						}
						if (map3[3][27] != BLOCK3 || map3[3][27] == BLOCK3)
						{
							if (map3[3][27] == BLOCK3 && map3[playerMapY][playerMapX] == map3[4][13])
							{
								map3[playerMapY][playerMapX] = BLOCK3;
								map3[3][27] = YUKA;
							}
						}
						if (map3[4][27] != BLOCK4 || map3[4][27] == BLOCK4)
						{
							if (map3[4][27] == BLOCK4 && map3[playerMapY][playerMapX] == map3[4][15])
							{
								map3[playerMapY][playerMapX] = BLOCK4;
								map3[4][27] = YUKA;
							}
						}
						if (map3[5][27] != BLOCK5 || map3[5][27] == BLOCK5)
						{
							if (map3[5][27] == BLOCK5 && map3[playerMapY][playerMapX] == map3[4][17])
							{
								map3[playerMapY][playerMapX] = BLOCK5;
								map3[5][27] = YUKA;
							}
						}
						if (map3[6][27] != BLOCK6 || map3[6][27] == BLOCK6)
						{

							if (map3[6][27] == BLOCK6 && map3[playerMapY][playerMapX] == /*6以降は後で*/map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK6;
								map3[6][27] = YUKA;
							}
						}
						if (map3[7][27] != BLOCK7 || map3[7][27] == BLOCK7)
						{
							if (map3[7][27] == BLOCK7 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK7;
								map3[7][27] = YUKA;
							}
						}
						if (map3[8][27] != BLOCK8 || map3[8][27] == BLOCK8)
						{
							if (map3[8][27] == BLOCK8 && map3[playerMapY][playerMapX] == map3[4][9])
							{
								map3[playerMapY][playerMapX] = BLOCK8;
								map3[8][27] = YUKA;
							}
						}
						playerPosY += playerSpeed;
					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK1)
					{
						map3[1][27] = BLOCK1;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = ZE;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK22)
					{
						map3[2][27] = BLOCK22;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = ZE;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK3)
					{
						map3[3][27] = BLOCK3;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = ZE;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK4)
					{
						map3[4][27] = BLOCK4;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = ZE;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK5)
					{
						map3[5][27] = BLOCK5;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = ZE;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK6)
					{
						map3[6][27] = BLOCK6;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = ZE;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK7)
					{
						map3[7][27] = BLOCK7;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = ZE;
						playerPosY += playerSpeed;

					}
					if (map3[playerMapY + 1][playerMapX] == BLOCK8)
					{
						map3[8][27] = BLOCK8;
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY + 1][playerMapX] = ZE;
						playerPosY += playerSpeed;

					}
				}

			}

			//状態変化--------------------------------------------------------------------------------------------------



			//ゴール条件---------------------------------


			// 解答が合ってたらクリアフラグがtrueになる
			if (map[blockMapY][blockMapX] == BLOCK1 && map[blockMapY][blockMapX] == I)
			{
				if (map[blockMapY][blockMapX] == BLOCK22 && map[blockMapY][blockMapX] == NU)
				{
					isClearFlag = true;
				}
			}

			// ステージ遷移　解答のシーンを作る予定
			if (map[playerMapY][playerMapX] == GOAL && isClearFlag == true && keys[DIK_SPACE] && preKeys[DIK_SPACE] == 0)
			{
				sceneNo = STAGE2;
			}

			/*if (map[playerMapY][playerMapX] == GOAL)
			{
				goalTimer--;
				playerSpeed = 0;
				if (goalTimer == 0)
				{
					sceneNo = GAMECLEAR;
				}
			}

			if (map[playerMapY][playerMapX] == THORN)
			{
				deathTimer--;
				playerSpeed = 0;
				if (deathTimer == 0)
				{
					sceneNo = GAMEOVER;
				}
			}*/

			break;

		case GAMECLEAR:
			if (keys[DIK_SPACE] && preKeys[DIK_SPACE] == 0)
			{
				playerPosX = 1 * KBlockSize;//プレイヤーの位置
				playerPosY = 20 * KBlockSize;
				playerMapX = playerPosX / KBlockSize;//map[x][]
				playerMapY = playerPosY / KBlockSize;//map[][y]
				playerSpeed = KBlockSize;
				goalTimer = 60;

				sceneNo = STAGE2;
			}
			break;

		case GAMECLEAR2:
			if (keys[DIK_SPACE] && preKeys[DIK_SPACE] == 0)
			{
				playerPosX = 12 * KBlockSize;//プレイヤーの位置
				playerPosY = 18 * KBlockSize;
				playerMapX = playerPosX / KBlockSize;//map[x][]
				playerMapY = playerPosY / KBlockSize;//map[][y]
				playerSpeed = KBlockSize;
				goalTimer = 60;

				sceneNo = STAGE3;
			}
			break;

		case GAMECLEAR3:
			if (keys[DIK_SPACE] && preKeys[DIK_SPACE] == 0)
			{
				sceneNo = TITLE;
			}
			break;


		case GAMEOVER:
			if (keys[DIK_SPACE] && preKeys[DIK_SPACE] == 0)
			{
				sceneNo = TITLE;
			}
			break;
		}
		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		switch (sceneNo)
		{
		case TITLE:
			Novice::DrawSprite(0, 0, title, 2, 2, 0, WHITE);
			break;
		case STAGE1:
			//数値見やすく--------------------------------------------------------------
			/*Novice::ScreenPrintf(865, 32, "goalTimer=%d", goalTimer);
			Novice::ScreenPrintf(865, 64, "deathTimer=%d",deathTimer);
			Novice::ScreenPrintf(865, 96, "playerSpeed=%d", playerSpeed);
			Novice::ScreenPrintf(865, 128, "caramelTimer=%d", caramelTimer);*/



			Novice::DrawBox(0, 0, 1280, 720, 0, BLACK, kFillModeSolid);

			for (int y = 0; y < mapCountY; y++)
			{
				for (int x = 0; x < mapCountX; x++)
				{
					//あ
					if (map[y][x] == A)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, a, 1, 1, 0, WHITE);
					}
					if (map[y][x] == I)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, i, 1, 1, 0, WHITE);
					}
					if (map[y][x] == U)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, u, 1, 1, 0, WHITE);
					}
					if (map[y][x] == E)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, e, 1, 1, 0, WHITE);
					}
					if (map[y][x] == O)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, o, 1, 1, 0, WHITE);
					}

					//か
					if (map[y][x] == KA)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, ka, 1, 1, 0, WHITE);
					}
					if (map[y][x] == KI)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, ki, 1, 1, 0, WHITE);
					}
					if (map[y][x] == KU)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, ku, 1, 1, 0, WHITE);
					}
					if (map[y][x] == KE)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, ke, 1, 1, 0, WHITE);
					}
					if (map[y][x] == KO)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, ko, 1, 1, 0, WHITE);
					}

					//さ
					if (map[y][x] == SA)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, sa, 1, 1, 0, WHITE);
					}
					if (map[y][x] == SHI)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, shi, 1, 1, 0, WHITE);
					}
					if (map[y][x] == SU)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, su, 1, 1, 0, WHITE);
					}
					if (map[y][x] == SE)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, se, 1, 1, 0, WHITE);
					}
					if (map[y][x] == SO)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, so, 1, 1, 0, WHITE);
					}

					//た
					if (map[y][x] == TA)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, ta, 1, 1, 0, WHITE);
					}
					if (map[y][x] == CHI)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, chi, 1, 1, 0, WHITE);
					}
					if (map[y][x] == TSU)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, tsu, 1, 1, 0, WHITE);
					}
					if (map[y][x] == TE)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, te, 1, 1, 0, WHITE);
					}
					if (map[y][x] == TO)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, to, 1, 1, 0, WHITE);
					}

					//な
					if (map[y][x] == NA)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, na, 1, 1, 0, WHITE);
					}
					if (map[y][x] == NI)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, ni, 1, 1, 0, WHITE);
					}
					if (map[y][x] == NU)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, nu, 1, 1, 0, WHITE);
					}
					if (map[y][x] == NE)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, ne, 1, 1, 0, WHITE);
					}
					if (map[y][x] == NO)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, no, 1, 1, 0, WHITE);
					}

					//は
					if (map[y][x] == HA)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, ha, 1, 1, 0, WHITE);
					}
					if (map[y][x] == HI)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, hi, 1, 1, 0, WHITE);
					}
					if (map[y][x] == FU)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, hu, 1, 1, 0, WHITE);
					}
					if (map[y][x] == HE)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, he, 1, 1, 0, WHITE);
					}
					if (map[y][x] == HO)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, ho, 1, 1, 0, WHITE);
					}

					//ま
					if (map[y][x] == MA)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, ma, 1, 1, 0, WHITE);
					}
					if (map[y][x] == MI)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, mi, 1, 1, 0, WHITE);
					}
					if (map[y][x] == MU)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, mu, 1, 1, 0, WHITE);
					}
					if (map[y][x] == ME)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, me, 1, 1, 0, WHITE);
					}
					if (map[y][x] == MO)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, mo, 1, 1, 0, WHITE);
					}

					//や
					if (map[y][x] == YA)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, ya, 1, 1, 0, WHITE);
					}
					if (map[y][x] == YU)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, yu, 1, 1, 0, WHITE);
					}
					if (map[y][x] == YO)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, yo, 1, 1, 0, WHITE);
					}

					//ら
					if (map[y][x] == RA)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, ra, 1, 1, 0, WHITE);
					}
					if (map[y][x] == RI)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, ri, 1, 1, 0, WHITE);
					}
					if (map[y][x] == RU)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, ru, 1, 1, 0, WHITE);
					}
					if (map[y][x] == RE)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, re, 1, 1, 0, WHITE);
					}
					if (map[y][x] == RO)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, ro, 1, 1, 0, WHITE);
					}

					//わ
					if (map[y][x] == WA)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, wa, 1, 1, 0, WHITE);
					}
					if (map[y][x] == WO)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, wo, 1, 1, 0, WHITE);
					}
					if (map[y][x] == NN)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, nn, 1, 1, 0, WHITE);
					}

					//が
					if (map[y][x] == GA)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, ga, 1, 1, 0, WHITE);
					}
					if (map[y][x] == GI)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, gi, 1, 1, 0, WHITE);
					}
					if (map[y][x] == GU)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, gu, 1, 1, 0, WHITE);
					}
					if (map[y][x] == GE)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, ge, 1, 1, 0, WHITE);
					}
					if (map[y][x] == GO)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, go, 1, 1, 0, WHITE);
					}

					//ざ
					if (map[y][x] == ZA)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, za, 1, 1, 0, WHITE);
					}
					if (map[y][x] == ZI)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, zi, 1, 1, 0, WHITE);
					}
					if (map[y][x] == ZU)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, zu, 1, 1, 0, WHITE);
					}
					if (map[y][x] == ZE)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, ze, 1, 1, 0, WHITE);
					}
					if (map[y][x] == ZO)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, zo, 1, 1, 0, WHITE);
					}

					//だ
					if (map[y][x] == DA)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, da, 1, 1, 0, WHITE);
					}
					if (map[y][x] == DI)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, di, 1, 1, 0, WHITE);
					}
					if (map[y][x] == DU)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, du, 1, 1, 0, WHITE);
					}
					if (map[y][x] == DE)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, de, 1, 1, 0, WHITE);
					}
					if (map[y][x] == DO)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, doo, 1, 1, 0, WHITE);
					}

					//ば
					if (map[y][x] == BA)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, ba, 1, 1, 0, WHITE);
					}
					if (map[y][x] == BI)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, bi, 1, 1, 0, WHITE);
					}
					if (map[y][x] == BU)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, bu, 1, 1, 0, WHITE);
					}
					if (map[y][x] == BE)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, be, 1, 1, 0, WHITE);
					}
					if (map[y][x] == BO)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, bo, 1, 1, 0, WHITE);
					}

					//ぱ
					if (map[y][x] == PA)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, pa, 1, 1, 0, WHITE);
					}
					if (map[y][x] == PI)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, pi, 1, 1, 0, WHITE);
					}
					if (map[y][x] == PU)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, pu, 1, 1, 0, WHITE);
					}
					if (map[y][x] == PE)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, pe, 1, 1, 0, WHITE);
					}
					if (map[y][x] == PO)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, po, 1, 1, 0, WHITE);
					}

					if (map[y][x] == YUKA)
					{
						Novice::DrawBox(x * KBlockSize, y * KBlockSize, KBlockSize, KBlockSize, 0, BLUE, kFillModeSolid);
					}
					if (map[y][x] == BLOCK)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, block, 1, 1, 0, WHITE);
					}
					/*if (map[y][x] == BLOCK22)
					{
						Novice::DrawBox(x * KBlockSize, y * KBlockSize, KBlockSize, KBlockSize, 0, RED, kFillModeSolid);
					}*/
					if (map[y][x] == GOAL)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, goal, 1, 1, 0, WHITE);
					}


				}
			}
			Novice::DrawSprite(playerPosX, playerPosY, player, 1, 1, 0, WHITE);
			Novice::DrawSprite(864, 0, MANUAL, 1, 1, 0, WHITE);
			break;

		case STAGE2:
			Novice::DrawBox(0, 0, 1280, 720, 0, BLACK, kFillModeSolid);
			for (int y = 0; y < mapCountY; y++)
			{
				for (int x = 0; x < mapCountX; x++)
				{
					//あ
					if (map2[y][x] == A)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, a, 1, 1, 0, WHITE);
					}
					if (map2[y][x] == I)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, i, 1, 1, 0, WHITE);
					}
					if (map2[y][x] == U)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, u, 1, 1, 0, WHITE);
					}
					if (map2[y][x] == E)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, e, 1, 1, 0, WHITE);
					}
					if (map2[y][x] == O)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, o, 1, 1, 0, WHITE);
					}

					//か
					if (map2[y][x] == KA)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, ka, 1, 1, 0, WHITE);
					}
					if (map2[y][x] == KI)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, ki, 1, 1, 0, WHITE);
					}
					if (map2[y][x] == KU)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, ku, 1, 1, 0, WHITE);
					}
					if (map2[y][x] == KE)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, ke, 1, 1, 0, WHITE);
					}
					if (map2[y][x] == KO)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, ko, 1, 1, 0, WHITE);
					}

					//さ
					if (map2[y][x] == SA)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, sa, 1, 1, 0, WHITE);
					}
					if (map2[y][x] == SHI)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, shi, 1, 1, 0, WHITE);
					}
					if (map2[y][x] == SU)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, su, 1, 1, 0, WHITE);
					}
					if (map2[y][x] == SE)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, se, 1, 1, 0, WHITE);
					}
					if (map2[y][x] == SO)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, so, 1, 1, 0, WHITE);
					}

					//た
					if (map2[y][x] == TA)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, ta, 1, 1, 0, WHITE);
					}
					if (map2[y][x] == CHI)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, chi, 1, 1, 0, WHITE);
					}
					if (map2[y][x] == TSU)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, tsu, 1, 1, 0, WHITE);
					}
					if (map2[y][x] == TE)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, te, 1, 1, 0, WHITE);
					}
					if (map2[y][x] == TO)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, to, 1, 1, 0, WHITE);
					}

					//な
					if (map2[y][x] == NA)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, na, 1, 1, 0, WHITE);
					}
					if (map2[y][x] == NI)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, ni, 1, 1, 0, WHITE);
					}
					if (map2[y][x] == NU)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, nu, 1, 1, 0, WHITE);
					}
					if (map2[y][x] == NE)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, ne, 1, 1, 0, WHITE);
					}
					if (map2[y][x] == NO)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, no, 1, 1, 0, WHITE);
					}

					//は
					if (map2[y][x] == HA)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, ha, 1, 1, 0, WHITE);
					}
					if (map2[y][x] == HI)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, hi, 1, 1, 0, WHITE);
					}
					if (map2[y][x] == FU)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, hu, 1, 1, 0, WHITE);
					}
					if (map2[y][x] == HE)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, he, 1, 1, 0, WHITE);
					}
					if (map2[y][x] == HO)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, ho, 1, 1, 0, WHITE);
					}

					//ま
					if (map2[y][x] == MA)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, ma, 1, 1, 0, WHITE);
					}
					if (map2[y][x] == MI)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, mi, 1, 1, 0, WHITE);
					}
					if (map2[y][x] == MU)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, mu, 1, 1, 0, WHITE);
					}
					if (map2[y][x] == ME)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, me, 1, 1, 0, WHITE);
					}
					if (map2[y][x] == MO)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, mo, 1, 1, 0, WHITE);
					}

					//や
					if (map2[y][x] == YA)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, ya, 1, 1, 0, WHITE);
					}
					if (map2[y][x] == YU)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, yu, 1, 1, 0, WHITE);
					}
					if (map2[y][x] == YO)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, yo, 1, 1, 0, WHITE);
					}

					//ら
					if (map2[y][x] == RA)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, ra, 1, 1, 0, WHITE);
					}
					if (map2[y][x] == RI)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, ri, 1, 1, 0, WHITE);
					}
					if (map2[y][x] == RU)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, ru, 1, 1, 0, WHITE);
					}
					if (map2[y][x] == RE)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, re, 1, 1, 0, WHITE);
					}
					if (map2[y][x] == RO)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, ro, 1, 1, 0, WHITE);
					}

					//わ
					if (map2[y][x] == WA)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, wa, 1, 1, 0, WHITE);
					}
					if (map2[y][x] == WO)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, wo, 1, 1, 0, WHITE);
					}
					if (map2[y][x] == NN)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, nn, 1, 1, 0, WHITE);
					}

					//が
					if (map2[y][x] == GA)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, ga, 1, 1, 0, WHITE);
					}
					if (map2[y][x] == GI)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, gi, 1, 1, 0, WHITE);
					}
					if (map2[y][x] == GU)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, gu, 1, 1, 0, WHITE);
					}
					if (map2[y][x] == GE)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, ge, 1, 1, 0, WHITE);
					}
					if (map2[y][x] == GO)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, go, 1, 1, 0, WHITE);
					}

					//ざ
					if (map2[y][x] == ZA)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, za, 1, 1, 0, WHITE);
					}
					if (map2[y][x] == ZI)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, zi, 1, 1, 0, WHITE);
					}
					if (map2[y][x] == ZU)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, zu, 1, 1, 0, WHITE);
					}
					if (map2[y][x] == ZE)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, ze, 1, 1, 0, WHITE);
					}
					if (map2[y][x] == ZO)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, zo, 1, 1, 0, WHITE);
					}

					//だ
					if (map2[y][x] == DA)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, da, 1, 1, 0, WHITE);
					}
					if (map2[y][x] == DI)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, di, 1, 1, 0, WHITE);
					}
					if (map2[y][x] == DU)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, du, 1, 1, 0, WHITE);
					}
					if (map2[y][x] == DE)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, de, 1, 1, 0, WHITE);
					}
					if (map2[y][x] == DO)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, doo, 1, 1, 0, WHITE);
					}

					//ば
					if (map2[y][x] == BA)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, ba, 1, 1, 0, WHITE);
					}
					if (map2[y][x] == BI)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, bi, 1, 1, 0, WHITE);
					}
					if (map2[y][x] == BU)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, bu, 1, 1, 0, WHITE);
					}
					if (map2[y][x] == BE)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, be, 1, 1, 0, WHITE);
					}
					if (map2[y][x] == BO)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, bo, 1, 1, 0, WHITE);
					}

					//ぱ
					if (map2[y][x] == PA)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, pa, 1, 1, 0, WHITE);
					}
					if (map2[y][x] == PI)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, pi, 1, 1, 0, WHITE);
					}
					if (map2[y][x] == PU)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, pu, 1, 1, 0, WHITE);
					}
					if (map2[y][x] == PE)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, pe, 1, 1, 0, WHITE);
					}
					if (map2[y][x] == PO)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, po, 1, 1, 0, WHITE);
					}

					if (map2[y][x] == YUKA)
					{
						Novice::DrawBox(x * KBlockSize, y * KBlockSize, KBlockSize, KBlockSize, 0, BLUE, kFillModeSolid);
					}
					if (map2[y][x] == BLOCK)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, block, 1, 1, 0, WHITE);
					}
					/*if (map[y][x] == BLOCK22)
					{
						Novice::DrawBox(x * KBlockSize, y * KBlockSize, KBlockSize, KBlockSize, 0, RED, kFillModeSolid);
					}*/
					if (map2[y][x] == GOAL)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, goal, 1, 1, 0, WHITE);
					}


				}
			}
			Novice::DrawSprite(playerPosX, playerPosY, player, 1, 1, 0, WHITE);
			Novice::DrawSprite(864, 0, MANUAL, 1, 1, 0, WHITE);
			break;

		case STAGE3:
			Novice::DrawBox(0, 0, 1280, 720, 0, BLACK, kFillModeSolid);
			for (int y = 0; y < mapCountY3; y++)
			{
				for (int x = 0; x < mapCountX3; x++)
				{
					if (map3[y][x] == A)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, a, 1, 1, 0, WHITE);
					}
					if (map3[y][x] == I)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, i, 1, 1, 0, WHITE);
					}
					if (map3[y][x] == U)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, u, 1, 1, 0, WHITE);
					}
					if (map3[y][x] == E)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, e, 1, 1, 0, WHITE);
					}
					if (map3[y][x] == O)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, o, 1, 1, 0, WHITE);
					}

					//か
					if (map3[y][x] == KA)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, ka, 1, 1, 0, WHITE);
					}
					if (map3[y][x] == KI)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, ki, 1, 1, 0, WHITE);
					}
					if (map3[y][x] == KU)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, ku, 1, 1, 0, WHITE);
					}
					if (map3[y][x] == KE)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, ke, 1, 1, 0, WHITE);
					}
					if (map3[y][x] == KO)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, ko, 1, 1, 0, WHITE);
					}

					//さ
					if (map3[y][x] == SA)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, sa, 1, 1, 0, WHITE);
					}
					if (map3[y][x] == SHI)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, shi, 1, 1, 0, WHITE);
					}
					if (map3[y][x] == SU)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, su, 1, 1, 0, WHITE);
					}
					if (map3[y][x] == SE)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, se, 1, 1, 0, WHITE);
					}
					if (map3[y][x] == SO)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, so, 1, 1, 0, WHITE);
					}

					//た
					if (map3[y][x] == TA)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, ta, 1, 1, 0, WHITE);
					}
					if (map3[y][x] == CHI)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, chi, 1, 1, 0, WHITE);
					}
					if (map3[y][x] == TSU)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, tsu, 1, 1, 0, WHITE);
					}
					if (map3[y][x] == TE)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, te, 1, 1, 0, WHITE);
					}
					if (map3[y][x] == TO)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, to, 1, 1, 0, WHITE);
					}

					//な
					if (map3[y][x] == NA)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, na, 1, 1, 0, WHITE);
					}
					if (map3[y][x] == NI)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, ni, 1, 1, 0, WHITE);
					}
					if (map3[y][x] == NU)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, nu, 1, 1, 0, WHITE);
					}
					if (map3[y][x] == NE)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, ne, 1, 1, 0, WHITE);
					}
					if (map3[y][x] == NO)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, no, 1, 1, 0, WHITE);
					}

					//は
					if (map3[y][x] == HA)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, ha, 1, 1, 0, WHITE);
					}
					if (map3[y][x] == HI)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, hi, 1, 1, 0, WHITE);
					}
					if (map3[y][x] == FU)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, hu, 1, 1, 0, WHITE);
					}
					if (map3[y][x] == HE)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, he, 1, 1, 0, WHITE);
					}
					if (map3[y][x] == HO)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, ho, 1, 1, 0, WHITE);
					}

					//ま
					if (map3[y][x] == MA)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, ma, 1, 1, 0, WHITE);
					}
					if (map3[y][x] == MI)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, mi, 1, 1, 0, WHITE);
					}
					if (map3[y][x] == MU)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, mu, 1, 1, 0, WHITE);
					}
					if (map3[y][x] == ME)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, me, 1, 1, 0, WHITE);
					}
					if (map3[y][x] == MO)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, mo, 1, 1, 0, WHITE);
					}

					//や
					if (map3[y][x] == YA)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, ya, 1, 1, 0, WHITE);
					}
					if (map3[y][x] == YU)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, yu, 1, 1, 0, WHITE);
					}
					if (map3[y][x] == YO)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, yo, 1, 1, 0, WHITE);
					}

					//ら
					if (map3[y][x] == RA)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, ra, 1, 1, 0, WHITE);
					}
					if (map3[y][x] == RI)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, ri, 1, 1, 0, WHITE);
					}
					if (map3[y][x] == RU)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, ru, 1, 1, 0, WHITE);
					}
					if (map3[y][x] == RE)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, re, 1, 1, 0, WHITE);
					}
					if (map3[y][x] == RO)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, ro, 1, 1, 0, WHITE);
					}

					//わ
					if (map3[y][x] == WA)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, wa, 1, 1, 0, WHITE);
					}
					if (map3[y][x] == WO)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, wo, 1, 1, 0, WHITE);
					}
					if (map3[y][x] == NN)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, nn, 1, 1, 0, WHITE);
					}

					//が
					if (map3[y][x] == GA)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, ga, 1, 1, 0, WHITE);
					}
					if (map3[y][x] == GI)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, gi, 1, 1, 0, WHITE);
					}
					if (map3[y][x] == GU)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, gu, 1, 1, 0, WHITE);
					}
					if (map3[y][x] == GE)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, ge, 1, 1, 0, WHITE);
					}
					if (map3[y][x] == GO)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, go, 1, 1, 0, WHITE);
					}

					//ざ
					if (map3[y][x] == ZA)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, za, 1, 1, 0, WHITE);
					}
					if (map3[y][x] == ZI)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, zi, 1, 1, 0, WHITE);
					}
					if (map3[y][x] == ZU)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, zu, 1, 1, 0, WHITE);
					}
					if (map3[y][x] == ZE)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, ze, 1, 1, 0, WHITE);
					}
					if (map3[y][x] == ZO)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, zo, 1, 1, 0, WHITE);
					}

					//だ
					if (map3[y][x] == DA)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, da, 1, 1, 0, WHITE);
					}
					if (map3[y][x] == DI)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, di, 1, 1, 0, WHITE);
					}
					if (map3[y][x] == DU)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, du, 1, 1, 0, WHITE);
					}
					if (map3[y][x] == DE)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, de, 1, 1, 0, WHITE);
					}
					if (map3[y][x] == DO)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, doo, 1, 1, 0, WHITE);
					}

					//ば
					if (map3[y][x] == BA)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, ba, 1, 1, 0, WHITE);
					}
					if (map3[y][x] == BI)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, bi, 1, 1, 0, WHITE);
					}
					if (map3[y][x] == BU)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, bu, 1, 1, 0, WHITE);
					}
					if (map3[y][x] == BE)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, be, 1, 1, 0, WHITE);
					}
					if (map3[y][x] == BO)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, bo, 1, 1, 0, WHITE);
					}

					//ぱ
					if (map3[y][x] == PA)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, pa, 1, 1, 0, WHITE);
					}
					if (map3[y][x] == PI)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, pi, 1, 1, 0, WHITE);
					}
					if (map3[y][x] == PU)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, pu, 1, 1, 0, WHITE);
					}
					if (map3[y][x] == PE)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, pe, 1, 1, 0, WHITE);
					}
					if (map3[y][x] == PO)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, po, 1, 1, 0, WHITE);
					}

					if (map3[y][x] == YUKA)
					{
						Novice::DrawBox(x * KBlockSize, y * KBlockSize, KBlockSize, KBlockSize, 0, BLUE, kFillModeSolid);
					}
					if (map3[y][x] == BLOCK)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, block, 1, 1, 0, WHITE);
					}
					/*if (map[y][x] == BLOCK22)
					{
						Novice::DrawBox(x * KBlockSize, y * KBlockSize, KBlockSize, KBlockSize, 0, RED, kFillModeSolid);
					}*/
					if (map3[y][x] == GOAL)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, goal, 1, 1, 0, WHITE);
					}

				}
			}
			Novice::DrawSprite(playerPosX, playerPosY, player, 1, 1, 0, WHITE);
			Novice::DrawSprite(864, 0, MANUAL, 1, 1, 0, WHITE);
			break;

		case GAMECLEAR:
			Novice::DrawSprite(0, 0, gameClear, 2, 2, 0, WHITE);
			break;

		case GAMECLEAR2:
			Novice::DrawSprite(0, 0, gameClear, 2, 2, 0, WHITE);
			break;

		case GAMECLEAR3:
			Novice::DrawSprite(0, 0, gameClear, 2, 2, 0, WHITE);
			break;

		case GAMEOVER2:
			Novice::DrawSprite(0, 0, gameOver, 2, 2, 0, WHITE);
			break;

		case GAMEOVER:
			Novice::DrawSprite(0, 0, gameOver, 2, 2, 0, WHITE);
			break;

		}


		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}