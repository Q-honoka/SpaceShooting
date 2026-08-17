#pragma once

class backGround
{
protected:
	float x, y;	// 座標
	int handle;	// グラフィックハンドル

public:
	void Initialize(void);	// 初期化関数
	void Display(void);	// 表示関数
	void Scroll(void);	// スクロール関数
};