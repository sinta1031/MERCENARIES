#include "PlayScene.h"
#include "../lib/input.h"
#include "../lib/InputPad.h"

//コンストラクタ
CPlayScene::CPlayScene()
{
	m_SceneID = PLAY_SCENE_INIT;
}

//デストラクタ
CPlayScene::~CPlayScene()
{
	Exit();
}

int CPlayScene::Loop()
{
	int iRet = 0;

	switch (m_SceneID)
	{
	case CPlayScene::PLAY_SCENE_INIT:
		Init();
		m_SceneID = PLAY_SCENE_LOAD;
		break;

	case CPlayScene::PLAY_SCENE_LOAD:
		Load();
		// ゲーム本編のBGMを鳴らす
		/*c_SDM.Play(c_SDM.BGM_GAME, DX_PLAYTYPE_LOOP);*/
		m_SceneID = PLAY_SCENE_LOOP;
		break;

	case CPlayScene::PLAY_SCENE_LOOP:
		Step();
		break;

	case CPlayScene::PLAY_SCENE_END:
		Exit();
		//c_SDM.AllStop();
		m_SceneID = PLAY_SCENE_INIT;
		iRet = 1;
		break;
	
	}

	return iRet;
}

//更新処理
void CPlayScene::Draw()
{
	c_F.Draw();
	c_EM.Draw();
	c_PM.Draw();
	c_SM.Draw();
}

//初期化
void CPlayScene::Init()
{
	c_CM.Init();
	c_SM.Init();
	c_EM.Init();
	c_PM.Init();
	c_F.Init();
}

//終了処理
void CPlayScene::Exit()
{
	c_PM.Exit();
	c_F.Exit();
	c_SM.Exit();
	c_EM.Exit();
}

//データロード
void CPlayScene::Load()
{
	c_PM.Load();
	c_F.Load();
	c_SM.Load();
	c_EM.Load();
}

// 毎フレーム呼ぶ処理
void CPlayScene::Step()
{
	c_PM.SetCameraRot(c_CM.PGetCamareRot());
	c_PM.Step();
	c_CM.Step(c_PM.Getplayerinstance().GetPos());
	c_F.Step();
	c_SM.Step();

	c_CM.Update();
	c_PM.Update();
	c_SM.Update();
	c_EM.Update();
	c_F.Update();

	//--------------------------------------------------------------------
	// フィールド類の当たり判定処理-----------------------------------
	//プレイヤーの当たり判定
	VECTOR fieldout = c_F.FieldHitCheck(c_PM.Getplayerinstance().GetCenter(), c_PM.Getplayerinstance().GetRadius());
	
	c_PM.Getplayerinstance().ReflectCollision(fieldout);

	c_CLM.CheckHitShotToEnemy(c_SM, c_EM);
	c_CLM.CheckHitPlayerToEnemy(c_PM.Getplayerinstance(), c_EM);

	//プレイヤーの生存フラグが消えたらゲーム終了へ
	if (c_PM.Getplayerinstance().IsActive() == false)
	{
		m_SceneID = PLAY_SCENE_END;
	}
}