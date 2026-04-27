#include "CameraManager.h"

//---------------------------
// コンストラクタ
//---------------------------
CCameraManager::CCameraManager()
{
	// 初期カメラはプレイカメラ
	m_id = ID_PLAY;
}

//----------------------------
// 初期化
//----------------------------
void CCameraManager::Init()
{
	// それぞれのカメラを初期化
	m_play.Init();
	m_debug.Init();
	SetCameraNearFar(1.0f, 10000.0f);
}

//----------------------------
// メイン処理
//----------------------------
void CCameraManager::Step(VECTOR focus1)
{
	switch (m_id)
	{
		// ゲーム中のメインカメラ
	case ID_PLAY:
		m_play.Step(focus1);
		break;

		// デバッグ用のカメラ
	case ID_DEBUG:
		m_debug.Step();
		break;
	
	}
}

//-----------------------
// ニアーファー
//-----------------------
void CCameraManager::Update()
{
	switch (m_id)
	{
		// ゲーム中のメインカメラ
	case ID_PLAY:
		m_play.Update();
		break;

		// デバッグ用のカメラ
	case ID_DEBUG:
		m_debug.Update();
		break;
	}	
}

//-------------------------
// イベントカメラ
//-------------------------
void CCameraManager::EventCamera(VECTOR focus)
{
	switch (m_id)
	{
	case ID_DEBUG:
		m_debug.EventCamera(focus);
		break;
	}
}