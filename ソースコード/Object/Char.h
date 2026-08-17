#pragma once

class Char
{
protected:
	int x;		// 中心のx座標
	int y;		// 中心のy座標
	int w;		// 幅
	int h;		// 高さ
	int gh;		// グラフィックハンドル
	int speed;	// 移動速度
	int live;	// 生存フラグ

public:
	void Initialize(int,int,int,int,int,int);	// 初期化関数
	void Display(void);		// 表示関数
	void DeleteGh(void);	// グラフィック消去関数
	void LiveOff(void);		// 生存フラグをOFFにする関数
	int GetX(void) const;	// x座標を取得する関数
	int GetY(void) const;	// y座標を取得する関数
	int GetW(void) const;	// 幅を取得する関数
	int GetH(void) const;	// 高さを取得する関数
	int GetLive(void) const;		// 生存フラグを取得する関数
};