#include "Player.h"
#include "DxLib.h"

// スコアを0にする関数
void Player::ResetScore(void)
{
	score = 0;
}

// 移動関数
void Player::Move(void)
{
	int ogSpeed = speed;	// 元の移動速度を保存
	char buf[256];
	GetHitKeyStateAll(buf);

	// キー入力処理
	if (buf[KEY_INPUT_LSHIFT] == 1 || buf[KEY_INPUT_RSHIFT] == 1)
		speed = 1;
	if (buf[KEY_INPUT_D] == 1 || buf[KEY_INPUT_RIGHT] == 1)
		x += speed;
	if (buf[KEY_INPUT_A] == 1 || buf[KEY_INPUT_LEFT] == 1)
		x -= speed;

	speed = ogSpeed;	// 移動速度を元に戻す

	// 画面の端から反対の端に移動
	if (x > 640 + w)
		x = 0 - w;
	else if (x < 0 - w)
		x = 640 + w;
}

// スコアを加算する関数
void Player::AddScore(void)
{
	score += 100;
}

// スコアを取得する関数
int Player::GetScore(void) const
{
	return score;
}

// ハイスコアをリセットする関数
void Player::ResetHiScore(void)
{
	FILE* fp;
	fp = fopen("score.txt", "w");
	if (fp != NULL)
	{
		fprintf(fp, "%d", 0);
		fclose(fp);
	}
}

// ハイスコアを記録する関数
void Player::SetHiScore(void) const
{
	FILE* fp;
	int hiScore;
	fp = fopen("score.txt", "r");
	if (fp != NULL)	// ファイルの中に書き込みがあった場合
	{
		fscanf(fp, "%d", &hiScore);
		fclose(fp);
	}
	if (fp == NULL || score > hiScore)	// ファイルの中が空もしくはハイスコアが更新された場合
	{
		fp = fopen("score.txt", "w");
		fprintf(fp, "%d", score);
		fclose(fp);
	}
}

// ハイスコアを取得する関数
int Player::GetHiScore(void)
{
	FILE* fp;
	int hiScore;
	fp = fopen("score.txt", "r");
	if (fp == NULL)
	{
		return 0;
	}
	fscanf(fp, "%d", &hiScore);
	fclose(fp);

	return hiScore;
}