#include "CharacterSelectScene.h"
#include "../lib/input.h"
#include "../lib/InputPad.h"

//コンストラクタ
CCharacterSelectScene::CCharacterSelectScene()
{
	m_SceneID = CHARACTER_SELECT_SCENE_INIT;
}

//デストラクタ
CCharacterSelectScene::~CCharacterSelectScene()
{
	Exit();
}

int CCharacterSelectScene::Loop()
{
	int iRet = 0;

	switch (m_SceneID)
	{
	case CCharacterSelectScene::CHARACTER_SELECT_SCENE_INIT:
		Init();
		m_SceneID = CHARACTER_SELECT_SCENE_LOAD;
		break;

	case CCharacterSelectScene::CHARACTER_SELECT_SCENE_LOAD:
		Load();
		// タイトルのBGMを鳴らす
		/*c_SDM.CHARACTER_SELECT(c_SDM.BGM_GAME, DX_CHARACTER_SELECTTYPE_LOOP);*/
		m_SceneID = CHARACTER_SELECT_SCENE_LOOP;
		break;

	case CCharacterSelectScene::CHARACTER_SELECT_SCENE_LOOP:
		Step();
		break;

	case CCharacterSelectScene::CHARACTER_SELECT_SCENE_END:
		Exit();
		//c_SDM.AllStop();
		m_SceneID = CHARACTER_SELECT_SCENE_INIT;
		iRet = 1;
		break;
	
	}

	return iRet;
}

//更新処理
void CCharacterSelectScene::Draw()
{
	DrawFormatString(640, 360, GetColor(255, 255, 255), "CHARACTER_SELECT");
}

//初期化
void CCharacterSelectScene::Init()
{
	
}

//終了処理
void CCharacterSelectScene::Exit()
{

}
	

//データロード
void CCharacterSelectScene::Load()
{
	
}

// 毎フレーム呼ぶ処理
void CCharacterSelectScene::Step()
{
	if (Input::IsInputTrg(KEY_INPUT_SPACE) || InputPad::IsPushPadTrg(XINPUT_BUTTON_B))
	{
		m_SceneID = CHARACTER_SELECT_SCENE_END;
	}
}