#define _CRT_SECURE_NO_WARNINGS

#include "Char.h"
#include "DxLib.h"
#include "main.h"
#include <stdio.h>

// 初期化関数
void Char::Initialize(int xx, int yy, int ww, int hh, int handle, int sspeed)
{
	x = xx;
	y = yy;
	w = ww;
	h = hh;
	gh = handle;
	speed = sspeed;
	live = ON;
}

// 表示関数
void Char::Display(void)
{
	if (live != ON)
		return;
	int x1 = x - w / 2;	// 左上x座標
	int y1 = y - h / 2;	// 左上y座標
	int x2 = x + w / 2;	// 右下x座標
	int y2 = y + h / 2;	// 右下y座標
	DrawExtendGraph(x1, y1, x2, y2, gh, TRUE);
}

// グラフィック消去関数
void Char::DeleteGh(void)
{
	DeleteGraph(gh);
}

// 生存フラグをOFFにする関数
void Char::LiveOff(void)
{
	live = OFF;
}

// x座標を取得する関数
int Char::GetX(void) const
{
	return x;
}

// y座標を取得する関数
int Char::GetY(void) const
{
	return y;
}

// 幅を取得する関数
int Char::GetW(void) const
{
	return w;
}

// 高さを取得する関数
int Char::GetH(void) const
{
	return h;
}

// 生存フラグを取得する関数
int Char::GetLive(void) const
{
	return live;
}