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
	c_PM.SetCameraRot(c_CM.PGetCamareRot(), c_CM.AGetCamareRot());
	c_PM.Step();
	c_CM.Step(c_PM.Getplayerinstance().GetPos(), c_PM.Getplayerinstance().GetRot(), c_PM.GetAnotherinstance().GetPos(), c_PM.GetAnotherinstance().GetRot(), c_PM.GetAnotherinstance());
	c_F.Step();
	c_SM.Step();

	c_CM.Update();
	c_PM.Update();
	c_SM.Update();
	c_EM.Update();
	c_F.Update();

	// カメラ設定
	//プレイヤーの状態切り替え
	if (Input::IsInputTrg(KEY_V) || InputPad::IsPushPadTrg(XINPUT_BUTTON_RIGHT_SHOULDER))
	{
		switch (c_PM.GetModeID())
		{
			//現在ペアモードなら分離モードに
		case 0:
			c_CM.ChangeCamera(CCameraManager::ID_ANOTHER);
			c_PM.ChangeMode(CPlayerManager::ID_BUNR);
			break;

			//現在分離モードならペアモードに
			//※PLAYERモードから戻るとき必ずPLAYER_IDをANOTHERモードに
		case 1:
			c_PM.changecheck();
			c_PM.ChangePlayer(CPlayerManager::ID_ANOTHER);
			c_CM.ChangeCamera(CCameraManager::ID_PLAY);
			c_PM.ChangeMode(CPlayerManager::ID_PEAR);
			break;
		}
	}

	//プレイヤーのモードが分離状態のとき
	if (c_PM.GetModeID() == 1)
	{
		if (Input::IsInputTrg(KEY_B) || InputPad::IsPushPadTrg(XINPUT_BUTTON_Y))
		{
			switch (c_PM.GetPlayerID())
			{
			case 0://PLAYERモードならANOTHERモードに
				c_CM.ChangeCamera(CCameraManager::ID_ANOTHER);
				c_PM.ChangePlayer(CPlayerManager::ID_ANOTHER);
				break;

			case 1://ANOTHERモードならPLAYERモードに
				c_CM.ChangeCamera(CCameraManager::ID_PLAY);
				c_PM.ChangePlayer(CPlayerManager::ID_PLAYER);
				break;
			}
		}
	}

	//--------------------------------------------------------------------
	// フィールド類の当たり判定処理-----------------------------------
	//プレイヤーの当たり判定
	VECTOR fieldout = c_F.FieldHitCheck(c_PM.Getplayerinstance().GetCenter(), c_PM.Getplayerinstance().GetRadius());
	VECTOR oliout =	c_F.Getoliinstance().oliHitCheck(c_PM.Getplayerinstance().GetCenter(), c_PM.Getplayerinstance().GetRadius());
	VECTOR stairsout = c_F.Getstairsinstance().stairsHitCheck(c_PM.Getplayerinstance().GetCenter(), c_PM.Getplayerinstance().GetRadius());
	VECTOR woodout = c_F.Getwoodinstance().woodHitCheck(c_PM.Getplayerinstance().GetCenter(), c_PM.Getplayerinstance().GetRadius());
	VECTOR boxout_p = c_F.Getboxinstance().boxHitCheck(c_PM.Getplayerinstance().GetCenter(), c_PM.Getplayerinstance().GetRadius());
	VECTOR woolout_p = c_F.Getwoolinstance().woolHitCheck(c_PM.Getplayerinstance().GetCenter(), c_PM.Getplayerinstance().GetRadius());
	VECTOR woolcageout = c_F.Getwoolinstance().woolcageHitCheck(c_PM.Getplayerinstance().GetCenter(), c_PM.Getplayerinstance().GetRadius());
	VECTOR spongeout_p = c_F.GetspongeManagerinstance().spongeHitCheck(c_PM.Getplayerinstance().GetCenter(), c_PM.Getplayerinstance().GetRadius());
	bool oilout_p =	c_F.Getoilinstance().oilHitCheck(c_PM.Getplayerinstance().GetCenter(), c_PM.Getplayerinstance().GetRadius());
	bool oilpoolout_p =	c_F.Getoilinstance().oilpoolHitCheck(c_PM.Getplayerinstance().GetCenter(), c_PM.Getplayerinstance().GetRadius());
	c_F.Getmidpointinstance().midpointHitCheck(c_PM.Getplayerinstance().GetCenter(), c_PM.Getplayerinstance().GetRadius());

	c_PM.Getplayerinstance().ReflectCollision(fieldout);
	c_PM.Getplayerinstance().ReflectCollision(oliout);
	c_PM.Getplayerinstance().ReflectCollision(stairsout);
	c_PM.Getplayerinstance().ReflectCollision(woodout);
	c_PM.Getplayerinstance().ReflectCollision(woolcageout);
	c_PM.Getplayerinstance().ReflectCollision(boxout_p);
	c_PM.Getplayerinstance().ReflectCollision(woolout_p);
	c_PM.Getplayerinstance().ReflectCollision(spongeout_p);
	c_CLM.CheckHitPlayerToKey(c_PM.Getplayerinstance(), c_F.Getkeyinstance());
	c_CLM.CheckHitPlayerToGoal(c_PM.Getplayerinstance(), c_F.Getgoalinstance());

	//アナザーの当たり判定
	VECTOR fieldaut = c_F.FieldHitCheck(c_PM.GetAnotherinstance().GetCenter(), c_PM.GetAnotherinstance().GetRadius());
	VECTOR stairsaut = c_F.Getstairsinstance().stairsHitCheck(c_PM.GetAnotherinstance().GetCenter(), c_PM.GetAnotherinstance().GetRadius());
	VECTOR switchaut = c_F.Getswitchinstance().switchHitCheck(c_PM.GetAnotherinstance().GetCenter(), c_PM.GetAnotherinstance().GetRadius());
	VECTOR boxaut_a = c_F.Getboxinstance().boxHitCheck(c_PM.GetAnotherinstance().GetCenter(), c_PM.GetAnotherinstance().GetRadius());
	VECTOR woolout_a = c_F.Getwoolinstance().woolHitCheck(c_PM.GetAnotherinstance().GetCenter(), c_PM.GetAnotherinstance().GetRadius());
	VECTOR spongeout_a = c_F.GetspongeManagerinstance().spongeHitCheck(c_PM.GetAnotherinstance().GetCenter(), c_PM.GetAnotherinstance().GetRadius());
	bool wateraut = c_F.Getwaterinstance().waterHitCheck(c_PM.GetAnotherinstance().GetCenter(), c_PM.GetAnotherinstance().GetRadius());
	bool oilout_a = c_F.Getoilinstance().oilHitCheck(c_PM.GetAnotherinstance().GetCenter(), c_PM.GetAnotherinstance().GetRadius());
	bool oilpoolout_a = c_F.Getoilinstance().oilpoolHitCheck(c_PM.GetAnotherinstance().GetCenter(), c_PM.GetAnotherinstance().GetRadius());

	c_PM.GetAnotherinstance().ReflectCollision(fieldaut);
	c_PM.GetAnotherinstance().ReflectCollision(stairsaut);
	c_PM.GetAnotherinstance().ReflectCollision(switchaut);
	c_PM.GetAnotherinstance().ReflectCollision(woolout_a);
	c_PM.GetAnotherinstance().ReflectCollision(spongeout_a);

	//水の当たり判定
	c_CLM.CheckHitShotToSponge(c_SM, c_F.GetspongeManagerinstance());
	c_CLM.CheckHitShotTobud(c_SM, c_F.Getbudinstance());

	//壁の当たり判定
	c_CLM.CheckHitAnotherToWool(c_PM.GetAnotherinstance(), c_F.Getwoolinstance());

	

	//ボックスにスライムが当たった時
	//BIG状態だったら
	if (c_PM.GetAnotherinstance().GetID() == 1)
	{
		c_F.Getboxinstance().boxHitDestroyCheck(c_PM.GetAnotherinstance().GetCenter(), c_PM.GetAnotherinstance().GetRadius());
	}
	else
	{
		c_PM.GetAnotherinstance().ReflectCollision(boxaut_a);
	}

	//オブジェクトの当たり判定--------------------------------------------
	//----------------------------------------------------------------
	
	//分身が水に触れたら
	if (wateraut == true)
	{
		//BIG状態にする
		if (c_PM.GetAnotherinstance().GetID() == 0)
		c_PM.GetAnotherinstance().ChangeAnotherSize(CAnother::BIG);
	}

	//相方がオイルに触れたら死ぬ&カメラを変える。プレイヤーに切り替わる
	if (oilout_a == true || oilpoolout_a == true)
	{
		if (c_PM.GetAnotherinstance().GetID() == 1)
		{
			c_PM.GetAnotherinstance().ChangeAnotherSize(CAnother::NORMAL);
			c_PM.GetAnotherinstance().jump();
		}
		else if (c_PM.GetAnotherinstance().GetID() == 0)
		{
			c_PM.GetAnotherinstance().HitCalc();
			c_PM.changecheck();
			c_CM.ChangeCamera(CCameraManager::ID_PLAY);
			c_PM.ChangeMode(CPlayerManager::ID_PEAR);
			c_PM.ChangePlayer(CPlayerManager::ID_ANOTHER);
		}
	}

	//プレイヤーがオイルに触れたら遅くする
	if (oilout_p == true || oilpoolout_p == true)
	{
		c_PM.Getplayerinstance().ChangePlayerstatus(CPlayer::PLAYER_STATE_OIL);
	}
	else
	{
		c_PM.Getplayerinstance().ChangePlayerstatus(CPlayer::PLAYER_STATE_NORMAL);
	}

	c_CLM.CheckHitShotToEnemy(c_SM, c_EM);
	c_CLM.CheckHitPlayerToEnemy(c_PM.Getplayerinstance(), c_EM);

	//プレイヤーの生存フラグが消えたら、またはゴールしたらゲーム終了へ
	if (c_PM.Getplayerinstance().IsActive() == false || c_PM.Getplayerinstance().GoalIsActive() == true)
	{
		m_SceneID = PLAY_SCENE_END;
	}
}