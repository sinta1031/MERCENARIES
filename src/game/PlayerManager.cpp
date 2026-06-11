#include "PlayerManager.h"

//---------------------------
// コンストラクタ
//---------------------------
CPlayerManager::CPlayerManager()
{
	Init();
}

//-----------------------------
// デストラクタ
//-----------------------------
CPlayerManager::~CPlayerManager()
{
	Exit();
}

//----------------------------
// 初期化
//----------------------------
void CPlayerManager::Init()
{
	// それぞれのプレイヤーを初期化
	m_play.Init();
}

//----------------------------
// ロード
//----------------------------
void CPlayerManager::Load()
{
	// それぞれのプレイヤーをロード
	m_play.Load();
}

//----------------------------
// メイン処理
//----------------------------
void CPlayerManager::Step()
{
	m_play.Step();
}

//---------------------------------
// それぞれの位置情報アップデート
//---------------------------------
void CPlayerManager::Update()
{
	m_play.Update();
}

//---------------------------------
//    描画
//---------------------------------
void CPlayerManager::Draw()
{
	m_play.Draw();
}

//--------
// 破棄
//--------
void CPlayerManager::Exit()
{
	m_play.Exit();
}

//-------------------------------
// プレイヤーのインスタンス取得
//-------------------------------
CPlayer& CPlayerManager::Getplayerinstance()
{
	return m_play;
}

//カメラの回転値をセット
void CPlayerManager::SetCameraRot(VECTOR p_camerarot)
{
	m_play.SetCameraRot(p_camerarot);
}

//カメラのADSを取得してここから渡す
void CPlayerManager::SetADS(bool _IsADS)
{
	m_play.SetADS(_IsADS);
}