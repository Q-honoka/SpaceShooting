#include "Shot.h"
#include "DxLib.h"
#include "main.h"

// 初期化関数
void Shot::Initialize(void)
{
	x = 0;
	y = 0;
	r = 2;
	color = GetColor(255, 255, 0);
	speed = 5;
	state = OFF;
}

// 表示関数
void Shot::Display(void) const
{
	if (state != ON)
		return;
	DrawCircle(x, y, r, color, TRUE);
}

// 弾の使用フラグをONにする関数
void Shot::StateOn(void)
{
	state = ON;
}

// 弾の座標をセットする関数
void Shot::SetPos(int xx, int yy, int hh)
{
	x = xx;
	y = yy - hh / 2;
}

// 移動関数
void Shot::Move(void)
{
	if (state != ON)
		return;

	y -= speed;
	// 画面外に出たら消去
	if (y < 0)
		state = OFF;
}

// 敵との衝突判定をとる関数(衝突していたら1を返す)
int Shot::Col(int xx, int yy, int ww, int hh)
{
	if (state == OFF)
		return 0;

	int x1 = (xx - ww / 2) - r;	// 左端x座標
	int y1 = (yy - hh / 2) - r;	// 上端y座標
	int x2 = (xx + ww / 2) + r;	// 右端x座標
	int y2 = (yy + hh / 2) + r;	// 下端y座標

	// 四角形に半径を追加したエリア内に円の座標があったら衝突している
	if (x > x1 && x < x2 && y > y1 && y < y2)
	{
		state = OFF;
		return 1;
	}

	return 0;
}

// 弾の使用状況を取得する関数
int Shot::GetState(void) const
{
	return state;
}