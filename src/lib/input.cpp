#include "input.h"
#include <DxLib.h>


INPUT_DATA g_inputData;

//=============================
//キー入力情報の初期化
//=============================
void Input::InitInput() 
{
	g_inputData.m_Prevker = g_inputData.m_nuwkey = 0;
}

//============================
//キー入力情報を更新
//============================
void  Input::UpdateInput()
{
	//最新情報は１フレーム前の情報になる
	g_inputData.m_Prevker = g_inputData.m_nuwkey;
	//いったん最新情報は初期化
	g_inputData.m_nuwkey = 0;

	//最新情報を取得していく
	//上キー情報取得
	if (/*CheckHitKey(KEY_INPUT_UP) ||*/ CheckHitKey(KEY_INPUT_W) /*|| GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_UP*/)
	{
		g_inputData.m_nuwkey |= KEY_UP;
	}

	if (CheckHitKey(KEY_INPUT_UP))
	{
		g_inputData.m_nuwkey |= KEY_UP2;
	}

	//下キー情報取得
	if (/*CheckHitKey(KEY_INPUT_DOWN) ||*/ CheckHitKey(KEY_INPUT_S) /*|| GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_DOWN*/)
	{
		g_inputData.m_nuwkey |= KEY_DOWN;
	}
	if (CheckHitKey(KEY_INPUT_DOWN))
	{
		g_inputData.m_nuwkey |= KEY_DOWN2;
	}

	//左キー情報取得
	if (/*CheckHitKey(KEY_INPUT_LEFT) ||*/ CheckHitKey(KEY_INPUT_A) /*|| GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_LEFT*/)
	{
		g_inputData.m_nuwkey |= KEY_LEFT;
	}
	if (CheckHitKey(KEY_INPUT_LEFT))
	{
		g_inputData.m_nuwkey |= KEY_LEFT2;
	}

	//右キー情報取得
	if (/*CheckHitKey(KEY_INPUT_RIGHT) ||*/ CheckHitKey(KEY_INPUT_D) /*|| GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_UP*/)
	{
		g_inputData.m_nuwkey |= KEY_RIGHT;
	}
	if (CheckHitKey(KEY_INPUT_RIGHT))
	{
		g_inputData.m_nuwkey |= KEY_RIGHT2;
	}

	//スキルキー情報取得
	if (CheckHitKey(KEY_INPUT_E)/* || GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_DOWN*/)
	{
		g_inputData.m_nuwkey |= KEY_SKILL;
	}
	//Zスキルキー情報取得
	if (CheckHitKey(KEY_INPUT_Q) /*|| GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_LEFT*/)
	{
		g_inputData.m_nuwkey |= KEY_ZSKILL;
	}
	//コマンド情報取得
	if (CheckHitKey(KEY_INPUT_LSHIFT) || GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_2)
	{
		g_inputData.m_nuwkey |= KEY_COMMAND;
	}

	//Vキー情報取得
	if (CheckHitKey(KEY_INPUT_V))
	{
		g_inputData.m_nuwkey |= KEY_V;
	}
	//Bキー情報取得
	if (CheckHitKey(KEY_INPUT_B))
	{
		g_inputData.m_nuwkey |= KEY_B;
	}

	//SPACEキー情報取得
	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		g_inputData.m_nuwkey |= KEY_SPACE;
	}
}

//=============================
//キーを押したか(通常判定)
//=============================
bool  Input::IsInputRep(unsigned int key)
{
	if ((g_inputData.m_nuwkey & key) != 0)
	{
		return true;
	}
	else
	{
		return false;
	}
	
}

//=================================
//キーを押したか(トリガー判定)
//=================================
bool  Input::IsInputTrg(unsigned int key)
{
	//今回ボタンが押された　かつ　前回押されていない
	if ((g_inputData.m_nuwkey & key) != 0
		 && (g_inputData.m_Prevker & key) == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}