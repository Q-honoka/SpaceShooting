#pragma once
#include "Char.h"

class Player :public Char
{
protected:
	int score;	// スコア

public:
	void ResetScore(void);	// スコアを0にする関数
	void Move(void);		// 移動関数
	void AddScore(void);	// スコアを加算する関数
	int GetScore(void) const;		// スコアを取得する関数
	void ResetHiScore(void);		// ハイスコアをリセットする関数
	void SetHiScore(void) const;	// ハイスコアを記録する関数
	int GetHiScore(void);	// ハイスコアを取得する関数
};