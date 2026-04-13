#include "player.h"
#include "SoundManager.h"
#include "../lib/input.h"
#include "../lib//InputPad.h"
#include <math.h>

#define GRAVITY				( 0.1f )	//重力
#define JUMPPOWER           ( 3.0f )	//ジャンプパワー

static const VECTOR ZERO = { 0.0f,0.0f,0.0f };
static const VECTOR INITPOS = { 0.0f,30.0f,0.0f };

static const char PLAYER_MODEL_PATH[] =
"data/model/player/player/player.mv1";

static const char KEY_PATH[] =
"data/ui/Key.png";

// コンストラクタ・デストラクタ
CPlayer::CPlayer()
{
	Init();
}

CPlayer::~CPlayer()
{
	Exit();
}

// プレーヤーの初期化
void CPlayer::Init()
{
	m_vPos = INITPOS;
	m_vRot = ZERO;
	m_PosX = 1200;
	m_PosY = 650;
	m_gravity = 0.0f;
	m_eState = PLAYER_STATE_NORMAL;
	m_radius = 8.0f;
	m_isActive = true;
	m_Hndl = -1;
}

//ロード
void  CPlayer::Load()
{
	if (m_Hndl == -1)
	{
		m_Hndl = MV1LoadModel(PLAYER_MODEL_PATH);
	}
}

//描画
void  CPlayer::Draw()
{
	MV1DrawModel(m_Hndl);

	//DrawFormatString(20, 20, GetColor(255, 0, 0), "プレイヤーX:%.4f", m_vPos.x);
	//DrawFormatString(20, 50, GetColor(255, 0, 0), "プレイヤーY:%.4f", m_vPos.y);
	//DrawFormatString(20, 60, GetColor(255, 0, 0), "プレイヤーZ:%.4f", m_vPos.z);

	//当たり判定を目視できるように
	DrawSphere3D(GetCenter(), m_radius,
		16, GetColor(255, 0, 0),
		GetColor(255, 0, 0), FALSE);
}

//破棄
void  CPlayer::Exit()
{
	if (m_Hndl != -1)
	{
		MV1DeleteModel(m_Hndl);
		m_Hndl = -1;
	}

}

// プレイヤーの座標計算
void  CPlayer::Step()
{
	float tempRotY = 180.0f * DX_PI_F / 180.0f;
	float PL_SPEED = 2.0f;
	VECTOR speed = ZERO;        // 移動速度
	VECTOR vSpeed;              // 移動速度

	//落下判定
	Falldetection();

	//縦移動
	if (CheckHitKey(KEY_INPUT_W) != 0 || InputPad::GetLAnalogYInput() > 0 || InputPad::IsPushPadRep(XINPUT_BUTTON_DPAD_UP))
	{
		speed.z = -PL_SPEED;
	}
	if (CheckHitKey(KEY_INPUT_S) != 0 || InputPad::GetLAnalogYInput() < 0 || InputPad::IsPushPadRep(XINPUT_BUTTON_DPAD_DOWN))
	{
		speed.z = PL_SPEED;
	}

	//横移動
	if (CheckHitKey(KEY_INPUT_A) != 0 || InputPad::GetLAnalogXInput() < 0 || InputPad::IsPushPadRep(XINPUT_BUTTON_DPAD_LEFT))
	{
		speed.x = PL_SPEED;
	}
	if (CheckHitKey(KEY_INPUT_D) != 0 || InputPad::GetLAnalogXInput() > 0 || InputPad::IsPushPadRep(XINPUT_BUTTON_DPAD_RIGHT))
	{
		speed.x = -PL_SPEED;
	}

	if (speed.x != 0.0f || speed.z != 0.0f)
	{
		// 移動速度で計算する
		MATRIX trans = MGetTranslate(speed);	         // 移動行列
		MATRIX rotY = MGetRotY(m_CameraRot.y);	//MGetRotY(GetRotCamera(m_plca.GetCamareRot()));   // 回転行列
		MATRIX res = MMult(trans, rotY);
		vSpeed.x = res.m[3][0];
		vSpeed.y = res.m[3][1];
		vSpeed.z = res.m[3][2];

		/*vSpeed.x = sinf(tempRotY);
		vSpeed.y = 0.0f;
		vSpeed.z = cosf(tempRotY);*/

		// 移動速度で計算する(カンテラ)
		/*vSpeed.x = sinf(tempRotY) * speed.x;
		vSpeed.y = 0.0f;
		vSpeed.z = cosf(tempRotY) * speed.z;*/

		// 計算した速度を座標計算に足し算する
		m_vPos = VAdd(m_vPos, vSpeed);

		/*MATRIX Temp1, Temp2;
		Temp1 = MV1GetFrameLocalWorldMatrix(m_Hndl, 2);
		Temp2 = MGetRotX(180.0f * DX_PI_F / 180.0f);
		Temp1 = MMult(Temp2, Temp1);
		MV1SetMatrix(m_Hndl1, Temp1);*/

		m_vRot.y = atan2f(-vSpeed.x, -vSpeed.z);
	}

	//スペースキーが押されたらジャンプする
	if (Input::IsInputTrg(KEY_SPACE) || InputPad::IsPushPadTrg(XINPUT_BUTTON_A))
	{
		jump();
	}

	gravity();
}

// ジャンプ
void CPlayer::jump()
{
	if (m_gravity == 0.0f)
	{
		m_gravity = JUMPPOWER;
	}	
}

//重力
void CPlayer::gravity()
{
	// 重力値更新 
	m_vPos.y += m_gravity;
}

// プレイヤーの更新
void  CPlayer::Update()
{
	// 移動結果をプレイヤーに設定
	MV1SetPosition(m_Hndl, m_vPos);
	MV1SetRotationXYZ(m_Hndl, m_vRot);
	MV1SetScale(m_Hndl, VGet(1.0f, 1.0f, 1.0f));
}

// 位置情報取得
VECTOR  CPlayer::GetPos()
{
	return m_vPos;
}

// 回転情報取得
float  CPlayer::GetRot()
{
	return m_vRot.y;
}

//落下判定
void CPlayer::Falldetection()
{
	if (m_vPos.y < -300.0f)
	{
		HitCalc();
	}
}

//ヒット後の処理
void CPlayer::HitCalc()
{
	// 生存フラグを消す
	m_isActive = false;
}

// 当たり判定の座標用
VECTOR CPlayer::GetCenter()
{
	// 基本は物体の座標の位置
	VECTOR ret = m_vPos;
	// 高さだけ足元から弾の半分あげる
	ret.y += m_radius;

	return ret;
}

//現在位置に座標加算
void CPlayer::ReflectCollision(VECTOR addVec)
{
	// オールゼロなら何もしない
	if (addVec.x == 0.0f && addVec.y == 0.0f && addVec.z == 0.0f) return;

	m_vPos = VAdd(m_vPos, addVec);
	m_gravity = 0.0f;	// とりあえず物体にぶつかったら重力を0に
}