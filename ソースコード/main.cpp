#include "DxLib.h"
#include "Player.h"
#include "Enemy.h"
#include "Shot.h"
#include "main.h"
#include "Effect.h"
#include "background.h"

Player pl;
Enemy em[ENEMYS];
Shot shot[MAXSHOT];
Effect effect[ENEMYS];
backGround bg;

enum {
	TITLE,
	MANUAL,
	GAME,
	RESULT,
	END,
};

// グローバル変数
unsigned int StrColor;	// 文字の色
int Handle;				// 一時的な画像ハンドル
int NowCount;			// 経過時間
int State;				// ゲームの状態
int BigHandle;		// フォントサイズ大のハンドル
int littleHandle;	// フォントサイズ小のハンドル
unsigned int Cr;
int Key;	// 上下キーの入力保存(1=上、0=下)
int Space;	// 決定キーの入力保存
int CursorX, CursorY;	// 選択カーソルの一番上のxy座標
int hiScore;			// ハイスコア
unsigned int ScoreCr;	// スコアの表示色

// プロトタイプ宣言
void Title(void);				// タイトル	
void manual(void);				// 操作説明
void GameInitialize(void);		// 初期化
void GameDisplay(void);			// 表示
void GameEnd(void);				// 終了
void GameMain(void);			// メインループ
void result(void);				// リザルト

// プログラムは WinMain から始まります
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	SetGraphMode(WINDOW_WIDTH, WINDOW_HEIGHT, 16);
	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}
	SetDrawScreen(DX_SCREEN_BACK);

	State = TITLE;
	BigHandle = CreateFontToHandle(NULL, 46, -1);
	littleHandle = CreateFontToHandle(NULL, 15, -1);
	StrColor = GetColor(255, 255, 255);
	Cr = GetColor(255, 255, 0);

	while (ProcessMessage() == 0 && State != END)
	{
		switch (State)
		{
		case TITLE:
			Title();
			break;

		case MANUAL:
			manual();
			break;

		case GAME:
			GameMain();
			break;

		case RESULT:
			result();
			break;
		}
	}

	DeleteFontToHandle(BigHandle);
	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}

void Title(void)
{
	Key = 2;	// 上下キーの入力保存(1=上、0=下)
	Space = 0;	// 決定キーの入力保存
	int start = GetNowCount();
	CursorX = 280;
	CursorY = 237;
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		ClearDrawScreen();
		DrawTriangle(CursorX, CursorY, CursorX + 10, CursorY + 10, CursorX, CursorY + 20, Cr, TRUE);
		DrawStringToHandle(100, 40, "Space Shooting Game", GetColor(0, 255, 255), BigHandle);	// タイトル
		DrawFormatString(250, 150, StrColor, "HiScore : %05d", pl.GetHiScore());	// ハイスコアの表示
		DrawString(300, 240, "Start", StrColor);			// 選択肢「Start」
		DrawString(300, 280, "manual", StrColor);			// 選択肢「manual」
		DrawString(300, 320, "ResetHiScore", StrColor);		// 選択肢「ResetHiScore」
		DrawString(350, 400, "矢印キーで選択。spaceキーで決定。", StrColor);


		if (GetNowCount() - start > 80)
		{
			if (CheckHitKey(KEY_INPUT_W) || CheckHitKey(KEY_INPUT_UP)) Key += 1;			// 上キーが押されたらカーソルを上げる
			if (CheckHitKey(KEY_INPUT_S) || CheckHitKey(KEY_INPUT_DOWN)) Key -= 1;		// 下キーが押されたらカーソルを下げる
			if (CheckHitKey(KEY_INPUT_SPACE)) Space = 1;	// スペースキーが押されたら決定(1)にする

			if (Key >= 2)
			{
				CursorX = 280;
				CursorY = 237;
				if (Space == 1)
				{
					State = GAME;
					WaitTimer(500);
					break;	// ループを抜けてゲームをスタートする
				}
				Key = 2;
			}
			if (Key == 1)
			{
				CursorX = 280;
				CursorY = 280;
				if (Space == 1)
				{
					State = MANUAL;
					WaitTimer(500);
					break;
				}
			}
			if (Key <= 0)
			{
				CursorX = 280;
				CursorY = 320;
				if (Space == 1)
				{
					pl.ResetHiScore();
					DrawString(100, 400, "ハイスコアをリセットしました。", StrColor);
					ScreenFlip();
					Space = 0;
					WaitTimer(1000);
				}
				Key = 0;
			}
			start = GetNowCount();
		}

		ScreenFlip();
	}

	if(State != GAME && State != MANUAL)
		State = END;
}

void manual(void)
{
	while (CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		ClearDrawScreen();
		// 操作説明を書く
		DrawString(40, 40, "矢印キーで左右に移動します。", StrColor);
		DrawString(40, 70, "Shiftキーを押しながら移動すると低速移動します。", StrColor);
		DrawString(40, 100, "画面外に出ると反対の端から出てきます。", StrColor);
		DrawString(40, 130, "スペースキーで弾を発射。一度に10発まで撃てます。", StrColor);
		DrawString(40, 160, "敵に当たるもしくは制限時間が終了するとゲームが終了します。", StrColor);
		DrawString(40, 190, "問題が起きた場合はescキーを押すと強制終了します。", StrColor);
		DrawString(40, 300, "Spaceキーでタイトルに戻る", StrColor);

		if (CheckHitKey(KEY_INPUT_SPACE))
		{
			State = TITLE;
			break;
		}

		ScreenFlip();
	}

	if(State != TITLE)
		State = END;
	else
		WaitTimer(500);
}

void GameInitialize(void)
{
	Handle = LoadGraph("image/player.png");
	pl.Initialize(320, 400, 30, 30, Handle, 3);	// プレイヤー初期化
	for (int i = 0; i < MAXSHOT; i++)
	{
		shot[i].Initialize();	// 弾の初期化
	}
	Handle = LoadGraph("image/enemy.png");
	for (int i = 0; i < ENEMYS; i++)
	{
		int x = GetRand(570) + 20;
		int y = GetRand(300) - 100;
		em[i].Initialize(x, y, 20, 20, Handle, 1);	// 敵の初期化
		effect[i].Initialize();		// エフェクトの初期化
	}
	bg.Initialize();
	StrColor = GetColor(255, 255, 255);
	pl.ResetScore();	// スコアの初期化
	hiScore = pl.GetHiScore(); // 表示ハイスコアの初期化
	ScoreCr = GetColor(255, 255, 255);	// 表示ハイスコアの文字色

	GameDisplay();	// 表示
}

void GameDisplay(void)
{
	ClearDrawScreen();
	bg.Display();	// 背景の表示
	for (int i = 0; i < ENEMYS; i++)
	{
		em[i].Display();	// 敵の表示
		effect[i].Display();	// エフェクトの表示
	}
	pl.Display();	// プレイヤーの表示
	for (int i = 0; i < MAXSHOT; i++)
	{
		shot[i].Display();	// 弾の表示
	}
	DrawFormatString(600, 0, StrColor, "%2d秒", NowCount);	// 制限時間の表示
	DrawFormatString(0, 0, StrColor, "Score   : %05d", pl.GetScore());	// スコアの表示
	
	if (hiScore != 0)
	{
		if (hiScore < pl.GetScore())
		{
			ScoreCr = GetColor(255, 100, 255);
			hiScore = pl.GetScore();
		}
		DrawFormatString(0, 30, ScoreCr, "HiScore : %05d", hiScore);	// ハイスコアの表示

	}

	ScreenFlip();
}

void GameEnd(void)
{
	pl.DeleteGh();	// プレイヤーのグラフィックハンドルの消去
	for (int i = 0; i < ENEMYS; i++)
	{
		em[i].DeleteGh();	// 敵のグラフィックハンドルの消去
	}
	DeleteGraph(Handle);
}

void GameMain(void)
{
	// 初期化
	GameInitialize();

	int StartTime = GetNowCount();
	int shotTime = GetNowCount();
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		// 時間処理
		NowCount = (LIMIT - (GetNowCount() - StartTime)) / 1000;	// 制限時間処理

		if (GetNowCount() - shotTime > TIMING && CheckHitKey(KEY_INPUT_SPACE) == 1 && pl.GetLive() == ON)	// 連射速度制限
		{
			for (int i = 0; i < MAXSHOT; i++)
			{
				if (shot[i].GetState() == OFF)	// 非使用の弾があれば処理する
				{
					shot[i].StateOn();	// shot[i]を使用にする
					shot[i].SetPos(pl.GetX(), pl.GetY(), pl.GetH());	// 座標をセットする
					shotTime = GetNowCount();	// カウントを初期化
					break;
				}
			}
		}

		// 背景スクロール
		bg.Scroll();

		// プレイヤー処理
		pl.Move();	// 移動
		for (int i = 0; i < MAXSHOT; i++)
		{
			shot[i].Move();	// 弾の移動
			for (int j = 0; j < ENEMYS; j++)
			{
				if (em[j].GetLive() == OFF)
					continue;
				int ex = em[j].GetX();
				int ey = em[j].GetY();
				int ew = em[j].GetW();
				int eh = em[j].GetH();
				if (shot[i].Col(ex, ey, ew, eh) == 1)	// 弾と敵の当たり判定
				{
					em[j].LiveOff();	// 敵消去
					pl.AddScore();	// スコア加算
					for (int k = 0; k < ENEMYS; k++)
					{
						if (effect[k].getFlag() == 0)
						{
							effect[k].setEffect(ex, ey);	// エフェクトのセット
							break;
						}
					}
				}
			}
		}

		// 敵処理
		int px = pl.GetX();
		int py = pl.GetY();
		int pw = pl.GetW();
		int ph = pl.GetH();
		for (int i = 0; i < ENEMYS; i++)
		{
			em[i].SetPos();	// 座標セット
			em[i].Move();	// 移動
			if (em[i].Col(px, py, pw, ph) == 1)
			{
				pl.LiveOff();	// プレイヤー消去
			}
		}

		// エフェクト処理
		for (int i = 0; i < ENEMYS; i++)
		{
			effect[i].Animation();
		}

		// 表示
		GameDisplay();

		if (NowCount <= 0 || pl.GetLive() == OFF)
		{
			pl.SetHiScore();
			State = RESULT;
			break;
		}
	}

	// ゲーム終了処理
	GameEnd();
	if (State != RESULT)
		State = END;
	else
		WaitTimer(500);
}

void result(void)
{
	Key = 1;	// 上下キーの入力保存(1=上、0=下)
	Space = 0;	// 決定キーの入力保存
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		ClearDrawScreen();
		DrawFormatStringToHandle(150, 40, ScoreCr, BigHandle, "Score : %05d", pl.GetScore());	// スコア
		DrawFormatString(250, 100, StrColor, "HiScore : %05d", pl.GetHiScore());	// ハイスコアの表示
		DrawString(300, 240, "Title", StrColor);		// 選択肢「Title」
		DrawString(300, 280, "Restart", StrColor);	// 選択肢「Restart」
		DrawString(350, 400, "矢印キーで選択。spaceキーで決定。", StrColor);

		if (CheckHitKey(KEY_INPUT_W) || CheckHitKey(KEY_INPUT_UP)) Key = 1;			// 上キーが押されたらカーソルを上げる
		if (CheckHitKey(KEY_INPUT_S) || CheckHitKey(KEY_INPUT_DOWN)) Key = 0;		// 下キーが押されたらカーソルを下げる
		if (CheckHitKey(KEY_INPUT_SPACE)) Space = 1;	// スペースキーが押されたら決定(1)にする

		if (Key == 1)
		{
			DrawTriangle(290, 247, 280, 237, 280, 257, Cr, TRUE);
			if (Space == 1)
			{
				State = TITLE;
				WaitTimer(500);
				break;
			}
		}
		if (Key == 0)
		{
			DrawTriangle(290, 290, 280, 280, 280, 300, Cr, TRUE);
			if (Space == 1)
			{
				State = GAME;
				WaitTimer(500);
				break;
			}
		}
		ScreenFlip();
	}

	if (State != TITLE && State != GAME)
		State = END;
}