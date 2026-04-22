#include "SceneManager.h"
#include "SoundManager.h"
#include"../lib/input.h"

//コンストラクタ
CSceneManager::CSceneManager()
{
	// 最初のシーンを設定
	m_SceneID = SCENE_TITLE;
	// 音の初期化
	CSoundManager::Init();
	CSoundManager::Load();
	Input::InitInput();
}

//デストラクタ
CSceneManager::~CSceneManager()
{
	CSoundManager::Exit();
}

int CSceneManager::Loop()
{
	Input::UpdateInput();
	InputPad::Update();
	int iRet = 0;

	int TitleRes = -1;

	switch (m_SceneID)
	{
	case CSceneManager::SCENE_TITLE:
		TitleRes = c_TS.Loop();
		if (TitleRes == 0)
		{
			m_SceneID = SCENE_STAGE_SELECT;
		}
		else if (TitleRes == 1) {
			iRet = 1;
		}
		break;

	case CSceneManager::SCENE_STAGE_SELECT:
		if (c_SSS.Loop() != 0)
		{
			m_SceneID = SCENE_CHARACTER_SELECT;
		}
		break;

	case CSceneManager::SCENE_CHARACTER_SELECT:
		if (c_CSS.Loop() != 0)
		{
			m_SceneID = SCENE_PLAY;
		}
		break;

	case CSceneManager::SCENE_PLAY:
		if (c_PS.Loop() != 0)
		{
			m_SceneID = SCENE_RESULT;
		}
		break;

	case CSceneManager::SCENE_RESULT:
		if (c_RS.Loop() != 0)
		{
			m_SceneID = SCENE_TITLE;
		}
		break;

	}

	return iRet;
}

//更新処理
void CSceneManager::Draw()
{
	switch (m_SceneID)
	{
	case CSceneManager::SCENE_TITLE:
		c_TS.Draw();
		break;

	case CSceneManager::SCENE_STAGE_SELECT:
		c_SSS.Draw();
		break;

	case CSceneManager::SCENE_CHARACTER_SELECT:
		c_CSS.Draw();
		break;

	case CSceneManager::SCENE_PLAY:
		c_PS.Draw();
		break;

	case CSceneManager::SCENE_RESULT:
		c_RS.Draw();
		break;

	}
}

