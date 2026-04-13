#include "AnotherCamera.h"
#include "../lib/InputPad.h"
#include "math.h"

static const float CMR_BACKPOS = 40.0f;      
static const float CMR_SETPOS_Y = 30.0f;
static const float TARGET_POS = 10.0f;

static const VECTOR ZERO = { 0.0f,0.0f,0.0f }; 

//---------------------------
// コンストラクタ
//---------------------------
CAnotherCamera::CAnotherCamera()
{
	Init();
}

//----------------------------
// 初期化
//----------------------------
void  CAnotherCamera::Init()
{
	m_cameraPos = ZERO;
	m_targetPos = ZERO;
	m_cameraRot = ZERO;
	m_upVec = { 0.0f,0.1f,0.0f };
}

//----------------------------
// カメラの座標計算
//----------------------------
void  CAnotherCamera::Step(VECTOR focus, float rotY , CAnother& _Another)
{
	//改良カメラ
	//===============================================================================
	//各種定義関連
	float MAX_LEN_NEAR = 50.0f;  // この距離より離れるとカメラ移動開始
	float MAX_LEN_FAR = 100.0f;  // これ以上離れさせない
	float MIN_LEN_NEAR = 40.0f;  // この距離より近づくとカメラ移動開始
	float MIN_LEN_FAR = 30.0f;   // これ以上は近づけさせない
	float CAM_MOVE_SPEED = 0.5f; // カメラの移動速度

	//カメラの回転処理(今回は簡易版)================================ 
	//外積を使うことで自分の進行方向に対して垂直なベクトルを取得する
	//これを今の位置と加算することで回転を実現させている
	if (CheckHitKey(KEY_INPUT_LEFT) || InputPad::GetRAnalogXInput() > 0)
	{
		VECTOR v1 = { 0.0f,1.0f,0.0f };
		VECTOR v2 = VSub(m_cameraPos, focus);
		VECTOR speed = VCross(v1, v2);
		speed = VNorm(speed);
		speed = VScale(speed, 2.0f);
		m_cameraPos = VAdd(m_cameraPos, speed);
	}
	if (CheckHitKey(KEY_INPUT_RIGHT) || InputPad::GetRAnalogXInput() < 0)
	{
		VECTOR v1 = { 0.0f,1.0f,0.0f };
		VECTOR v2 = VSub(m_cameraPos, focus);
		VECTOR speed = VCross(v2, v1);
		speed = VNorm(speed);
		speed = VScale(speed, 2.0f);
		m_cameraPos = VAdd(m_cameraPos, speed);
	}
	//==============================================================

	//現在のカメラの位置からキャラクターの位置までの方向ベクトルを取得
	VECTOR dir = VSub(m_cameraPos, focus);
	dir.y = 0.0f;   //高さを考慮するとややこしいんで、一旦無視

	//今回は長さが重要なので、先ほど計算したベクトルから長さを計算
	float len = VSize(dir);

	//長さを求めたので、方向ベクトルは正規化してしまう
	dir = VNorm(dir);

	//プレイヤーがBIGだったら
	if (_Another.GetID() == 1)
	{
		MAX_LEN_NEAR = 150.0f;
		MAX_LEN_FAR = 200.0f;
		MIN_LEN_NEAR = 80.0f;
		MIN_LEN_FAR = 70.0f;
	}

	//カメラとプレイヤーの距離が一定以上離れた
	if (len > MAX_LEN_NEAR)
	{
		//本来の到達地点を計算
		dir = VScale(dir, MAX_LEN_NEAR);
		VECTOR tempPos = VAdd(focus, dir);

		//現在のカメラの位置から上記到達地点までの方向ベクトルを計算
		VECTOR tempDir = VSub(tempPos, m_cameraPos);
		tempDir.y = 0.0f;             //高さは無視
		tempDir = VNorm(tempDir);     //方向ベクトルなので正規化

		//目標到達地点に向けて、カメラの座標を移動させる
		tempDir = VScale(tempDir, CAM_MOVE_SPEED); //カメラの速度を計算
		m_cameraPos = VAdd(m_cameraPos, tempDir);

		//離れてはいけない距離以上は慣れていた場合の処理===========
		//新しく計算した位置と、注視点までの距離を計算
		tempDir = VSub(m_cameraPos, focus);
		tempDir.y = 0.0f; //やっぱり高さは無視

		//離れてはいけない距離を超えたかチェック(計算量を減らすため、2乗した値で比較)
		if (VSize(tempDir) > MAX_LEN_FAR)
		{
			//再度正規化し、強制的に最大距離に変更
			tempDir = VNorm(tempDir);
			tempDir = VScale(tempDir, MAX_LEN_FAR);
			m_cameraPos = VAdd(focus, tempDir);
		}
		//======================================================================
	}
	//カメラとプレイヤーの距離が一定以上近づいた
	else if (len < MIN_LEN_NEAR)
	{
		//本来の到達地点を計算
		dir = VScale(dir, MIN_LEN_NEAR);
		VECTOR tempPos = VAdd(focus, dir);

		//現在のカメラの位置から上記到達地点までの方向ベクトルを計算
		VECTOR tempDir = VSub(tempPos, m_cameraPos);
		tempDir.y = 0.0f;             //高さは無視
		tempDir = VNorm(tempDir);     //方向ベクトルなので正規化

		//目標到達地点に向けて、カメラの座標を移動させる
		tempDir = VScale(tempDir, CAM_MOVE_SPEED); //カメラの速度を計算
		m_cameraPos = VAdd(m_cameraPos, tempDir);

		//離れてはいけない距離以上は慣れていた場合の処理===========
		//新しく計算した位置と、注視点までの距離を計算
		tempDir = VSub(m_cameraPos, focus);
		tempDir.y = 0.0f; //やっぱり高さは無視

		//離れてはいけない距離を超えたかチェック(計算量を減らすため、2乗した値で比較)
		if (VSize(tempDir) < MIN_LEN_FAR)
		{
			//再度正規化し、強制的に最大距離に変更
			tempDir = VNorm(tempDir);
			tempDir = VScale(tempDir, MIN_LEN_FAR);
			m_cameraPos = VAdd(focus, tempDir);
		}
		//====================================================================
	}
	//============================================================================

	//注視点はプレイヤーの上半身の位置当たりに
	m_targetPos = focus;

	//プレイヤーがBIGだったら
	if (_Another.GetID() == 1)
	{
		m_targetPos.y += 100.0;

		//視点は見下ろし型になるように、少し下に
		m_cameraPos.y = m_targetPos.y + 45.0f;
	}
	else
	{
		m_targetPos.y += 15.0;

		//視点は見下ろし型になるように、少し下に
		m_cameraPos.y = m_targetPos.y + 25.0f;
	}

	//プレイヤーの移動処理の関係でカメラの角度を使っているので
	//カメラの方向ベクトルを基にY軸回転角度を計算
	dir = VSub(m_cameraPos, m_targetPos);
	m_cameraRot.y = atan2f(dir.x, dir.z);

	//VECTOR r_cameraPos = { 0.0f,0.0f,0.0f };

	//// カメラ設定
	//r_cameraPos.x = sinf(rotY) * CMR_BACKPOS;
	//r_cameraPos.y = CMR_SETPOS_Y;
	//r_cameraPos.z = cosf(rotY) * CMR_BACKPOS;

	//// 計算した速度を座標計算に足し算する
	//m_cameraPos = VAdd(focus, r_cameraPos);

	//// 視点はプレイヤーの後方
	//m_targetPos = focus;
	//m_targetPos.y = TARGET_POS;

}

//-----------------------
// カメラの更新
//-----------------------
void  CAnotherCamera::Update()
{
	SetCameraPositionAndTargetAndUpVec(m_cameraPos, m_targetPos, m_upVec);
}