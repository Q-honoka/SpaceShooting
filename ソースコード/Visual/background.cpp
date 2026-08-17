#include "DxLib.h"
#include "background.h"
#include "main.h"

#define BG_SPEED 0.5f	// スクロールスピード
#define BG_SIZE 480		// 背景の縦のサイズ

// 初期化関数
void backGround::Initialize(void)
{
	x = 0.0f;
	y = 0.0f;
	handle = LoadGraph("image/background.png");
}

// 表示関数
void backGround::Display(void)
{
	DrawGraphF(x, y, handle, TRUE);
}

// スクロール関数
void backGround::Scroll(void)
{
	y += BG_SPEED;	// 背景を下に移動させる

	if (y >= 0)	// 背景が消えたら
		y -= BG_SIZE;	// 画像サイズ分上に戻す
}