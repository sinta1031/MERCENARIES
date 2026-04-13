#include "TitleScene.h"
#include "../lib/input.h"
#include "../lib/InputPad.h"

//コンストラクタ
CTitleScene::CTitleScene()
{
	m_SceneID = TITLE_SCENE_INIT;
}

//デストラクタ
CTitleScene::~CTitleScene()
{
	Exit();
}

int CTitleScene::Loop()
{
	int iRet = 0;

	switch (m_SceneID)
	{
	case CTitleScene::TITLE_SCENE_INIT:
		Init();
		m_SceneID = TITLE_SCENE_LOAD;
		break;

	case CTitleScene::TITLE_SCENE_LOAD:
		Load();
		// タイトルのBGMを鳴らす
		/*c_SDM.TITLE(c_SDM.BGM_GAME, DX_TITLETYPE_LOOP);*/
		m_SceneID = TITLE_SCENE_LOOP;
		break;

	case CTitleScene::TITLE_SCENE_LOOP:
		Step();
		break;

	case CTitleScene::TITLE_SCENE_END:
		Exit();
		//c_SDM.AllStop();
		m_SceneID = TITLE_SCENE_INIT;
		iRet = 1;
		break;
	
	}

	return iRet;
}

//更新処理
void CTitleScene::Draw()
{
	DrawFormatString(640, 360, GetColor(255, 255, 255), "TITLE");
}

//初期化
void CTitleScene::Init()
{
	
}

//終了処理
void CTitleScene::Exit()
{

}
	

//データロード
void CTitleScene::Load()
{
	
}

// 毎フレーム呼ぶ処理
void CTitleScene::Step()
{
	if (CheckHitKey(KEY_INPUT_SPACE) || InputPad::IsPushPadTrg(XINPUT_BUTTON_B))
	{
		m_SceneID = TITLE_SCENE_END;
	}
}