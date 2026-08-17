#pragma once

class Shot
{
protected:
	int x;		// 中心のx座標
	int y;		// 中心のy座標
	int r;		// 半径
	int color;	// 色
	int speed;	// 移動速度
	int state;	// 使用フラグ

public:
	void Initialize(void);		// 初期化関数
	void Display(void) const;			// 表示関数
	void StateOn(void);			// 弾の使用フラグをONにする関数
	void SetPos(int, int, int);	// 弾の座標をセットする関数
	void Move(void);			// 移動関数
	int Col(int, int, int, int);	// 敵との衝突判定をとる関数(衝突していたら1を返す)
	int GetState(void) const;			// 弾の使用状況を取得する関数
};