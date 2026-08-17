#include "Enemy.h"
#include "main.h"
#include "DxLib.h"

// 移動関数
void Enemy::Move(void)
{
	if (live == OFF)
		return;

	y += speed;
	// 画面外の下に出たら画面外の上に移動
	if (y > 480 + h / 2)
		y = 0 - h / 2;
}

// 座標セット関数
void Enemy::SetPos(void)
{
	if (live == ON)
		return;

	live = ON;
	x = GetRand(640 - w) + w;
	y = GetRand(480 + h) - 480 - h;
}

// プレイヤーとの衝突判定をとる関数(衝突していたら1を返す)
int Enemy::Col(int xx, int yy, int ww, int hh)
{
	if (live == OFF)
		return 0;
	// プレイヤー(円)と敵(四角形)の衝突判定
	int r = (ww + hh) / 4;	// 円の半径
	int x1 = (x - w / 2) - r;	// 左端x座標
	int y1 = (y - h / 2) - r;	// 上端y座標
	int x2 = (x + w / 2) + r;	// 右端x座標
	int y2 = (y + h / 2) + r;	// 下端y座標

	// 四角形に半径を追加したエリア内に円の座標があったら衝突している
	if (xx > x1 && xx < x2 && yy > y1 && yy < y2)
	{

		return 1;
	}

	return 0;
}