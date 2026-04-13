#include "ResultScene.h"
#include "../lib/input.h"
#include "../lib/InputPad.h"

//コンストラクタ
CResultScene::CResultScene()
{
	m_SceneID = RESULT_SCENE_INIT;
}

//デストラクタ
CResultScene::~CResultScene()
{
	Exit();
}

int CResultScene::Loop()
{
	int iRet = 0;

	switch (m_SceneID)
	{
	case CResultScene::RESULT_SCENE_INIT:
		Init();
		m_SceneID = RESULT_SCENE_LOAD;
		break;

	case CResultScene::RESULT_SCENE_LOAD:
		Load();
		// タイトルのBGMを鳴らす
		/*c_SDM.RESULT(c_SDM.BGM_GAME, DX_RESULTTYPE_LOOP);*/
		m_SceneID = RESULT_SCENE_LOOP;
		break;

	case CResultScene::RESULT_SCENE_LOOP:
		Step();
		break;

	case CResultScene::RESULT_SCENE_END:
		Exit();
		//c_SDM.AllStop();
		m_SceneID = RESULT_SCENE_INIT;
		iRet = 1;
		break;
	
	}

	return iRet;
}

//更新処理
void CResultScene::Draw()
{
	DrawFormatString(640, 360, GetColor(255, 255, 255), "RESULT");
}

//初期化
void CResultScene::Init()
{
	
}

//終了処理
void CResultScene::Exit()
{

}
	

//データロード
void CResultScene::Load()
{
	
}

// 毎フレーム呼ぶ処理
void CResultScene::Step()
{
	if (CheckHitKey(KEY_INPUT_SPACE) || InputPad::IsPushPadTrg(XINPUT_BUTTON_B))
	{
		m_SceneID = RESULT_SCENE_END;
	}
}