#include "TitleScene.h"
#include "../lib/input.h"
#include "../lib/InputPad.h"

// staticメンバ関数はここで各作業が必須!!
vector<int> CTitleScene::m_hndl;
vector<int> CTitleScene::m_Fhndl;

//コンストラクタ
CTitleScene::CTitleScene()
{
	Init();
}

//デストラクタ
CTitleScene::~CTitleScene()
{
	Exit();
}

int CTitleScene::Loop()
{
	switch (m_SceneID)
	{
	case CTitleScene::TITLE_SCENE_INIT:
		Init();
		m_SceneID = TITLE_SCENE_LOAD;
		break;

	case CTitleScene::TITLE_SCENE_LOAD:
		Load();
		// タイトルのBGMを鳴らす
		c_SDM.Play(c_SDM.TITLE_BGM, DX_PLAYTYPE_LOOP);
		m_SceneID = TITLE_SCENE_LOOP;
		break;

	case CTitleScene::TITLE_SCENE_LOOP:
		Step();
		break;

	case CTitleScene::TITLE_SCENE_END:
		Exit();
		m_SceneID = TITLE_SCENE_INIT;
		break;
	
	}

	return m_MenuID;
}

//更新処理
void CTitleScene::Draw()
{
	for (int i = 0; i < m_hndl.size(); i++)
	{
		if (m_hndl[i] != -1)
		{
			DrawRotaGraph((int)m_pos.x, (int)m_pos.y,
				0.9, 0.0, m_hndl[i], TRUE);
		}
	}

	for (int i = 0; i < m_Fhndl.size(); i++)
	{
		if (m_MenuID == START_GAME)
		{
			DrawRotaGraph((int)m_pos.x, (int)m_pos.y,
				0.9, 0.0, m_Fhndl[TITLE_FONT_1], TRUE);
		}

		if (m_MenuID == EXIT)
		{
			DrawRotaGraph((int)m_pos.x, (int)m_pos.y,
				0.9, 0.0, m_Fhndl[EXIT], TRUE);
		}
	}
}

//初期化
void CTitleScene::Init()
{
	m_pos.x = 1280 / 2;
	m_pos.y = 720 / 2;

	m_SceneID = TITLE_SCENE_INIT;
	m_MenuID = START_GAME;

	// 中身を空にする
	m_hndl.clear();
	m_Fhndl.clear();
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

	for (int i = 0; i < m_Fhndl.size(); i++)
	{
		if (m_Fhndl[i] != -1)
		{
			DeleteGraph(m_Fhndl[i]);
			m_Fhndl[i] = -1;
		}
	}
}
	

//データロード
void CTitleScene::Load()
{
	const char* filePath[TITLE_PICTURE_NUM] = {
		"data/background/Title/TITLE.png",
		"data/ui/Title/TITLE_UI.png",
		"data/ui/Title/Push_Manual.png",
		
	};

	const char* fontPath[TITLE_FONT_NUM] = {
		"data/ui/Title/TITLE_FONT_1.png",
		"data/ui/Title/TITLE_FONT_2.png",

	};

	for (int i = 0; i < TITLE_PICTURE_NUM; i++)
	{
		int hndl = LoadGraph(filePath[i]);
		m_hndl.push_back(hndl);
	}

	for (int i = 0; i < TITLE_FONT_NUM; i++)
	{
		int hndl = LoadGraph(fontPath[i]);
		m_Fhndl.push_back(hndl);
	}
}

// 毎フレーム呼ぶ処理
void CTitleScene::Step()
{
	switch (m_MenuID)
	{
	case CTitleScene::START_GAME:

		if (Input::IsInputTrg(KEY_INPUT_W) || Input::IsInputTrg(KEY_INPUT_S) || InputPad::IsPushPadTrg(XINPUT_BUTTON_DPAD_UP) || InputPad::IsPushPadTrg(XINPUT_BUTTON_DPAD_UP))
		{
			m_MenuID = EXIT;
		}

		break;

	case CTitleScene::EXIT:

		if (Input::IsInputTrg(KEY_INPUT_W) || Input::IsInputTrg(KEY_INPUT_S) || InputPad::IsPushPadTrg(XINPUT_BUTTON_DPAD_UP) || InputPad::IsPushPadTrg(XINPUT_BUTTON_DPAD_UP))
		{
			m_MenuID = START_GAME;
		}

		break;
	}

	if (CheckHitKey(KEY_INPUT_SPACE) || InputPad::IsPushPadTrg(XINPUT_BUTTON_B))
	{
		m_SceneID = TITLE_SCENE_END;
	}
}