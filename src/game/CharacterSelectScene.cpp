#include "CharacterSelectScene.h"
#include "../lib/input.h"
#include "../lib/InputPad.h"

//コンストラクタ
CCharacterSelectScene::CCharacterSelectScene()
{
	Init();
}

//デストラクタ
CCharacterSelectScene::~CCharacterSelectScene()
{
	Exit();
}

int CCharacterSelectScene::Loop()
{
	int iRet = -1;

	switch (m_SceneID)
	{
	case CCharacterSelectScene::CHARACTER_SELECT_SCENE_INIT:
		Init();
		m_SceneID = CHARACTER_SELECT_SCENE_LOAD;
		break;

	case CCharacterSelectScene::CHARACTER_SELECT_SCENE_LOAD:
		Load();
		m_SceneID = CHARACTER_SELECT_SCENE_LOOP;
		break;

	case CCharacterSelectScene::CHARACTER_SELECT_SCENE_LOOP:
		Step();
		break;

	case CCharacterSelectScene::CHARACTER_SELECT_SCENE_END:
		Exit();
		m_SceneID = CHARACTER_SELECT_SCENE_INIT;
		iRet = m_SelectID;
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
	m_SceneID = CHARACTER_SELECT_SCENE_INIT;
	m_SelectID = WAIT;
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
	if (Input::IsInputTrg(KEY_INPUT_RETURN) || InputPad::IsPushPadTrg(XINPUT_BUTTON_B))
	{
		c_SDM.Play(c_SDM.PUSH_SE, DX_PLAYTYPE_BACK);
		m_SelectID = NEXT;
		c_SDM.Stop(c_SDM.TITLE_BGM);
		m_SceneID = CHARACTER_SELECT_SCENE_END;
	}
	else if (Input::IsInputTrg(KEY_INPUT_SPACE) || InputPad::IsPushPadTrg(XINPUT_BUTTON_A))
	{
		m_SelectID = BACK;
		m_SceneID = CHARACTER_SELECT_SCENE_END;
	}
}