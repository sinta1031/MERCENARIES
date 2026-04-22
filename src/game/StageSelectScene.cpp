#include "StageSelectScene.h"
#include "../lib/input.h"
#include "../lib/InputPad.h"

//コンストラクタ
CStageSelectScene::CStageSelectScene()
{
	m_SceneID = STAGE_SELECT_SCENE_INIT;
}

//デストラクタ
CStageSelectScene::~CStageSelectScene()
{
	Exit();
}

int CStageSelectScene::Loop()
{
	int iRet = -1;

	switch (m_SceneID)
	{
	case CStageSelectScene::STAGE_SELECT_SCENE_INIT:
		Init();
		m_SceneID = STAGE_SELECT_SCENE_LOAD;
		break;

	case CStageSelectScene::STAGE_SELECT_SCENE_LOAD:
		Load();
		m_SceneID = STAGE_SELECT_SCENE_LOOP;
		break;

	case CStageSelectScene::STAGE_SELECT_SCENE_LOOP:
		Step();
		break;

	case CStageSelectScene::STAGE_SELECT_SCENE_END:
		Exit();
		m_SceneID = STAGE_SELECT_SCENE_INIT;
		iRet = m_SelectID;
		break;
	
	}

	return iRet;
}

//更新処理
void CStageSelectScene::Draw()
{
	DrawFormatString(640, 360, GetColor(255, 255, 255), "STAGE_SELECT");
}

//初期化
void CStageSelectScene::Init()
{
	m_SelectID = WAIT;
}

//終了処理
void CStageSelectScene::Exit()
{

}

//データロード
void CStageSelectScene::Load()
{
	
}

// 毎フレーム呼ぶ処理
void CStageSelectScene::Step()
{
	if (Input::IsInputTrg(KEY_INPUT_RETURN) || InputPad::IsPushPadTrg(XINPUT_BUTTON_B))
	{
		c_SDM.Play(c_SDM.PUSH_SE, DX_PLAYTYPE_BACK);
		m_SelectID = NEXT;
		m_SceneID = STAGE_SELECT_SCENE_END;
	}
	else if (Input::IsInputTrg(KEY_INPUT_SPACE))
	{
		m_SelectID = BACK;
		m_SceneID = STAGE_SELECT_SCENE_END;
	}
}