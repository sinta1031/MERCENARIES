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
	m_another.Init();

	// 初期状態は一緒にいる状態から
	b_id = ID_PEAR;

	// 分離後の初期状態は分身から
	m_id = ID_ANOTHER;
}

//----------------------------
// ロード
//----------------------------
void CPlayerManager::Load()
{
	// それぞれのプレイヤーをロード
	m_another.Load();
	m_play.Load();
}

//----------------------------
// メイン処理
//----------------------------
void CPlayerManager::Step()
{
	switch (b_id)
	{
	case CPlayerManager::ID_PEAR:
		StepPear();
		break;

	case CPlayerManager::ID_BUNR:
		StepSolo();
		break;
	}
}

//-------------------------
// ペアモードの更新処理
//-------------------------
void CPlayerManager::StepPear()
{
	m_play.Step();
}

//--------------------------
// 分離モードの更新処理
//--------------------------
void CPlayerManager::StepSolo()
{
	//ここから別々の操作
	switch (m_id)
	{
		//プレイヤーを操作
	case ID_PLAYER:
		m_play.Step();
		break;
		
		// 分身を操作
	case ID_ANOTHER:
		m_another.SetActive(true);
		m_another.Step(m_play.GetPos());
		break;
	}
}

//---------------------------------
// それぞれの位置情報アップデート
//---------------------------------
void CPlayerManager::Update()
{
	switch (b_id)
	{
	case CPlayerManager::ID_PEAR:
		m_play.Update();
		break;

	case CPlayerManager::ID_BUNR:
		switch (m_id)
		{
			// プレイヤーを操作
		case ID_PLAYER:
			m_play.Update();
			break;

			// 分身を操作
		case ID_ANOTHER:
			m_another.Update();
			break;
		}
		break;
	}
}

//---------------------------------
//    描画
//---------------------------------
void CPlayerManager::Draw()
{
	switch (b_id)
	{
	case CPlayerManager::ID_PEAR:
		m_play.Draw();
		break;

	case CPlayerManager::ID_BUNR:
		m_play.Draw();
		m_another.Draw();
		break;
	}
}

//--------
// 破棄
//--------
void CPlayerManager::Exit()
{
	m_play.Exit();
	m_another.Exit();
}

//------------------
// チェンジフラグ
//------------------
void CPlayerManager::changecheck()
{
	m_another.ResetPos();
	m_another.SetActive(false);
	m_another.SetisPos(false);
}

//-------------------------------
// プレイヤーのインスタンス取得
//-------------------------------
CPlayer& CPlayerManager::Getplayerinstance()
{
	return m_play;
}

//-----------------------------
// 分身のインスタンス取得
//-----------------------------
CAnother& CPlayerManager::GetAnotherinstance()
{
	return m_another;
}

//カメラの回転値をセット
void CPlayerManager::SetCameraRot(VECTOR p_camerarot,VECTOR a_camerarot)
{
	switch (b_id)
	{
	case CPlayerManager::ID_PEAR:
		m_play.SetCameraRot(p_camerarot);
		break;

	case CPlayerManager::ID_BUNR:
		switch (m_id)
		{
			// プレイヤーを操作
		case ID_PLAYER:
			m_play.SetCameraRot(p_camerarot);
			break;

			// 分身を操作
		case ID_ANOTHER:
			m_another.SetCameraRot(a_camerarot);
			break;
		}

		break;
	}
}
