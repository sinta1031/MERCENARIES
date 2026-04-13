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
	m_another.Init();
	SetCameraNearFar(1.0f, 10000.0f);
}

//----------------------------
// メイン処理
//----------------------------
void CCameraManager::Step(VECTOR focus1, float rotY1, VECTOR focus2, float rotY2, CAnother& _Another)
{
	switch (m_id)
	{
		// ゲーム中のメインカメラ
	case ID_PLAY:
		m_play.Step(focus1, rotY1);
		break;

		// 分身操作時のカメラ
	case ID_ANOTHER:
		m_another.Step(focus2, rotY2, _Another);
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

		// 分身操作時のカメラ
	case ID_ANOTHER:
		m_another.Update();
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