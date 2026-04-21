#include "input.h"
#include <DxLib.h>

char Input::m_nuwkey[KEYBOARD_NUM];     //現在のボタン情報
char Input::m_Prevker[KEYBOARD_NUM];    //フレーム前のボタン情報

//=============================
//キー入力情報の初期化
//=============================
void Input::InitInput() 
{
	memset(m_nuwkey, 0, KEYBOARD_NUM);
	memset(m_Prevker, 0, KEYBOARD_NUM);
}

//============================
//キー入力情報を更新
//============================
void  Input::UpdateInput()
{
	memcpy(m_Prevker, m_nuwkey, KEYBOARD_NUM);
	GetHitKeyStateAll(m_nuwkey);
}

//=============================
//キーを押したか(通常判定)
//=============================
bool  Input::IsInputRep(unsigned int key)
{
	return m_nuwkey[key] == 1;
}

//=================================
//キーを押したか(トリガー判定)
//=================================
bool  Input::IsInputTrg(unsigned int key)
{
		//今回ボタンが押された　かつ　前回押されていない
	return (m_nuwkey[key] == 1 && m_Prevker[key] != 1);
}