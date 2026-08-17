#include "DxLib.h"
#include "Effect.h"
#include "main.h"

#define MAX_R 20	// 最大半径
#define COLOR_BLUE GetColor(50, 50, 255)	// 青色
#define COLOR_GREEN GetColor(100, 255, 100)	// 緑色
#define SPAN 50		// 間隔
#define BIGR_SPEED 4	// 大きい半径の広がる速さ
#define SMALLR_SPEED 2	// 小さい半径の広がる速さ

// 初期化関数
void Effect::Initialize(void)
{
	flag = OFF;
}

// 表示関数
void Effect::Display(void) const
{
	// flagがOFFなら表示しない
	if (flag == OFF)
		return;

	DrawCircle(x, y, bigR, COLOR_BLUE, FALSE);
	DrawCircle(x, y, smallR, COLOR_GREEN, FALSE);
}

// セット関数
void Effect::setEffect(int ex, int ey)
{
	x = ex;
	y = ey;
	bigR = 0;
	smallR = 0;
	flag = ON;
	count = 0;
	start = GetNowCount();
}

// アニメーション関数
void Effect::Animation(void)
{
	// 経過時間がSPANに満たなければ実行しない
	if (GetNowCount() - start < SPAN)
		return;

	// 半径を大きくする
	bigR += BIGR_SPEED;
	smallR += SMALLR_SPEED;

	// 半径が最大半径を越えたら半径を0にする
	if (bigR > MAX_R)
	{
		bigR = 0;
		count++;
	}
	if (smallR > MAX_R)
	{
		smallR = 0;
	}

	// 周回数が3以上になったらアニメーションを終える
	if (count >= 3)
	{
		flag = OFF;
		bigR = 0;
		smallR = 0;
		count = 0;
	}
	start = GetNowCount();
}

// エフェクトの表示状態を返す
int Effect::getFlag(void) const
{
	return flag;
}