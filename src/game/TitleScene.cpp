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
		//c_SDM.TITLE(c_SDM.BGM_GAME, DX_TITLETYPE_LOOP);
		m_SceneID = TITLE_SCENE_LOOP;
		break;

	case CTitleScene::TITLE_SCENE_LOOP:
		Step();
		break;

	case CTitleScene::TITLE_SCENE_END:
		Exit();
		m_SceneID = TITLE_SCENE_INIT;
		iRet = 1;
		break;
	
	}

	return iRet;
}

//更新処理
void CTitleScene::Draw()
{

}

//初期化
void CTitleScene::Init()
{
	// 中身を空にする
	m_hndl.clear();
}

//終了処理
void CTitleScene::Exit()
{
	for (int i = 0; i < m_hndl.size(); i++)
	{
		if (m_hndl[i] != -1)
		{
			DeleteGraph(m_hndl[i]);
			m_hndl[i] = -1;
		}
	}
}
	

//データロード
void CTitleScene::Load()
{
	const char* filePath[TITLE_PICTURE_NUM] = {
		"data/background/Title/TITLE",
		"data/ui/Title/TITLE_UI",

	};

	for (int i = 0; i < TITLE_PICTURE_NUM; i++)
	{
		int hndl = LoadGraph(filePath[i]);
		m_hndl.push_back(hndl);
	}
}

// 毎フレーム呼ぶ処理
void CTitleScene::Step()
{
	if (CheckHitKey(KEY_INPUT_SPACE) || InputPad::IsPushPadTrg(XINPUT_BUTTON_B))
	{
		m_SceneID = TITLE_SCENE_END;
	}
}