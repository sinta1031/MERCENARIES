#include "Another.h"
#include "SoundManager.h"
#include "ShotManager.h"
#include "../lib/input.h"
#include "../lib//InputPad.h"
#include <math.h>

#define GRAVITY				( 0.1f ) //重力
#define JUMPPOWER           ( 3.0f ) //ジャンプパワー

static const VECTOR ZERO = { 0.0f,0.0f,0.0f }; //初期値
static const VECTOR ONE = { 1.0f,1.0f,1.0f };  //初期サイズ値
static const VECTOR TONE = { 0.1f,0.1f,0.1f }; //サイズ増減値
static const VECTOR PURS = { 0.0f,0.0f,7.0f }; //出現場所加算値
static const VECTOR MAXSIZE = { 5.0f,5.0f,5.0f }; //最大サイズ値

static const char PLAYER_MODEL_PATH[] =
"data/model/player/slaim/slaim.mv1";

// コンストラクタ・デストラクタ
CAnother::CAnother()
{
	Init();
}

CAnother::~CAnother()
{
	Exit();
}

// プレーヤーの初期化
void CAnother::Init()
{
	m_vPos = ZERO;
	m_vRot = ZERO;
	m_vScale = ONE;
	m_sState = NORMAL;
	m_radius = 8.0f;
	m_gravity = 0.0f;
	m_isActive = true;
	m_Hndl = -1;
	m_isPos = false;
}

//ロード
void  CAnother::Load()
{
	if (m_Hndl == -1)
	{
		m_Hndl = MV1LoadModel(PLAYER_MODEL_PATH);
	}
}

//描画
void  CAnother::Draw()
{
	MV1DrawModel(m_Hndl);

	//DrawFormatString(20, 70, GetColor(255, 0, 0), "スライムY:%.4f", m_vPos.y);

	//当たり判定を目視できるように
	DrawSphere3D(GetCenter(), m_radius,
		16, GetColor(255, 0, 0),
		GetColor(255, 0, 0), FALSE);
}

//破棄
void CAnother::Exit()
{
	if (m_Hndl != -1)
	{
		MV1DeleteModel(m_Hndl);
		m_Hndl = -1;
	}
}

// プレイヤーの座標計算
void  CAnother::Step(VECTOR pos)
{
	//落下判定
	Falldetection();

	//出現するときはプレイヤーの後ろから
	if (m_isPos == false) {
		m_vPos = VAdd(pos, PURS);
		m_isPos = true;
	}

	//サイズの増減処理
	switch (m_sState)
	{
	case NORMAL:
		//NORMAL状態に大きかったら
		if (m_vScale.x >= ONE.x ||
			m_vScale.y >= ONE.y ||
			m_vScale.z >= ONE.z)
		{
			//小さくする
			m_vScale = VSub(m_vScale, TONE);
		}

		break;
	case BIG:
		//BIG状態に小さかったら
		if (m_vScale.x <= MAXSIZE.x ||
			m_vScale.y <= MAXSIZE.y ||
			m_vScale.z <= MAXSIZE.z)
		{
			//大きくする
			m_vScale = VAdd(m_vScale, TONE);
		}

		//でかい状態で小さくなりたいときに
		if (CheckHitKey(KEY_INPUT_Z) != 0 || InputPad::IsPushPadTrg(XINPUT_BUTTON_LEFT_THUMB))
		{
			CShotManager::Request(m_vPos);
			m_sState = NORMAL;
		}
		break;
	}

	//大きくなる
	/*if (CheckHitKey(KEY_INPUT_Z) != 0)
	{
		m_vScale = VAdd(m_vScale, TONE);
	}*/

	//小さくなる
	/*if (CheckHitKey(KEY_INPUT_X) != 0)
	{
		m_vScale = VSub(m_vScale, TONE);
	}*/

	float tempRotY = 180.0f * DX_PI_F / 180.0f;
	float PL_SPEED = 2.0f;
	VECTOR speed = ZERO;        // 移動速度
	VECTOR vSpeed;              // 移動速度

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
		m_vRot.y = atan2f(-vSpeed.x, -vSpeed.z);
	}

	//スペースキーが押されたらジャンプする
	if (Input::IsInputTrg(KEY_SPACE) || InputPad::IsPushPadTrg(XINPUT_BUTTON_A))
	{
		jump();
	}

	// 重力値更新 
	m_gravity -= GRAVITY;
	m_vPos.y += m_gravity;
}

// ジャンプ
void CAnother::jump()
{
	m_gravity = JUMPPOWER;
}

// プレイヤーの更新
void CAnother::Update()
{
	// 移動結果をプレイヤーに設定
	MV1SetPosition(m_Hndl, m_vPos);
	MV1SetRotationXYZ(m_Hndl, m_vRot);
	MV1SetScale(m_Hndl, m_vScale);
}

//落下判定
void CAnother::Falldetection()
{
	if (m_vPos.y <= -300.0f)
	{
		HitCalc();
	}
}

// 位置情報取得
VECTOR  CAnother::GetPos()
{
	return m_vPos;
}

// 回転情報取得
float CAnother::GetRot()
{
	return m_vRot.y;
}

// 位置情報リセット
VECTOR CAnother::ResetPos()
{
	m_vPos = ZERO;

	return m_vPos;
}

//ヒット後の処理
void CAnother::HitCalc()
{
	// 生存フラグを消す
	m_isActive = false;
}

// 当たり判定の座標用
VECTOR CAnother::GetCenter()
{
	// 基本は物体の座標の位置
	VECTOR ret = m_vPos;

	if (GetID() == 1)
	{
		m_radius = 40.0f;
	}
	else
	{
		m_radius = 8.0f;
	}

	// 高さだけ足元から弾の半分あげる
	ret.y += m_radius;

	return ret;
}

//現在位置に座標加算
void CAnother::ReflectCollision(VECTOR addVec)
{
	// オールゼロなら何もしない
	if (addVec.x == 0.0f && addVec.y == 0.0f && addVec.z == 0.0f) return;

	m_vPos = VAdd(m_vPos, addVec);
	m_gravity = 0.0f;	// とりあえず物体にぶつかったら重力を0に
}