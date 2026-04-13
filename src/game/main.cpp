#include <crtdbg.h>
#include "SceneManager.h"
#include "filed.h"
#include "../lib/debug.h"
#include <math.h>
#include <memory>
#include "DxLib.h"

// プログラムは WinMain から始まります
int  WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	// メモリリーク発見用
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	// スクリーン設定
	ChangeWindowMode(TRUE);			// フルスクリーンorウィンドウモード
	SetGraphMode(1280, 720, 32);	// ウィンドウのサイズ

	SetWindowText("Game.exe");
	
#ifndef _DEBUG
	// リリース版はログを出さない
	SetOutApplicationLogValidFlag(false);
#endif

	// ＤＸライブラリ初期化処理
	if (DxLib_Init() == -1) return -1;

	//一番最初に１回だけやる処理
	SetDrawScreen(DX_SCREEN_BACK);
	
	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);

	// プレーヤーの定義
	CSceneManager c_SM;
	FPS c_FPS;

	c_FPS.IniFps();

	//ゲームメインループ
	while (ProcessMessage() != -1)
	{
		//エスケープキーが押されたら終了
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) break;

		if (!c_FPS.IsNextFrame())continue;

		ClearDrawScreen();	// 画面クリア

		//ここにゲームの本体を書く
		
		// プレイヤーの移動========================
		c_SM.Loop();
		c_FPS.StepFps();
		//=========================================
		// モデル表示
		c_SM.Draw();
		c_FPS.PrintFps();

		ScreenFlip();		// 描画切り替え
	}

	DxLib_End();			// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}