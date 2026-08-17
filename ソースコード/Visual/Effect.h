#pragma once

class Effect
{
protected:
	int x, y;	// エフェクトの中心座標
	int bigR;		// エフェクトの半径(拡大が早い)
	int smallR;		// エフェクトの半径(拡大が遅い)
	int flag;	// 表示のフラグ
	int count;	// 周回数カウンタ
	int start;	// 計測開始時間

public:
	void Initialize(void);	// 初期化関数
	void Display(void) const;		// 表示関数
	void setEffect(int, int);	// セット関数(引数に倒れた敵の座標)
	void Animation(void);	// アニメーション関数
	int getFlag(void) const;		// エフェクトの表示状態を返す
};