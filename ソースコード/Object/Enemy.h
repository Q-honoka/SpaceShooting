#pragma once
#include "Char.h"

class Enemy :public Char
{
public:
	void Move(void);		// 移動関数
	void SetPos(void);		// 座標セット関数
	int Col(int, int, int, int);	// プレイヤーとの衝突判定をとる関数(衝突していたら1を返す)
};