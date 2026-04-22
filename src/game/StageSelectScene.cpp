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
	int iRet = 0;

	switch (m_SceneID)
	{
	case CStageSelectScene::STAGE_SELECT_SCENE_INIT:
		Init();
		m_SceneID = STAGE_SELECT_SCENE_LOAD;
		break;

	case CStageSelectScene::STAGE_SELECT_SCENE_LOAD:
		Load();
		// タイトルのBGMを鳴らす
		/*c_SDM.RESULT(c_SDM.BGM_GAME, DX_RESULTTYPE_LOOP);*/
		m_SceneID = STAGE_SELECT_SCENE_LOOP;
		break;

	case CStageSelectScene::STAGE_SELECT_SCENE_LOOP:
		Step();
		break;

	case CStageSelectScene::STAGE_SELECT_SCENE_END:
		Exit();
		//c_SDM.AllStop();
		m_SceneID = STAGE_SELECT_SCENE_END;
		iRet = 1;
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
	if (Input::IsInputTrg(KEY_INPUT_SPACE) || InputPad::IsPushPadTrg(XINPUT_BUTTON_B))
	{
		m_SceneID = STAGE_SELECT_SCENE_END;
	}
}