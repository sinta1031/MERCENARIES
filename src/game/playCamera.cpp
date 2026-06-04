#include "PlayCamera.h"

namespace {
	const float PLAYCAMERA_BACKPOS = 100.0f;
	const float PLAYCAMERA_POSY = 30.0f;
	const float TARGET_POS = 50.0f;
	const VECTOR UP_VEC = { 0.0f,10.0f,0.0f };
	const VECTOR VZERO = { 0.0f,0.0f,0.0f };
	const float CALC_LEN = 5.0f;
}

//コンストラクタ
PlayCamera::PlayCamera() {
	Init();
}
//初期化
void PlayCamera::Init() {
	m_CameraPoint = VZERO;			//カメラ位置
	m_CameraPos = VZERO;
	m_TargetPoint = VZERO;			//注視点
	m_TargetPos = VZERO;
	m_UpVec = UP_VEC;			//？？？
	m_CameraRot = VZERO;
	m_CalcRot = VZERO;
	m_IsTarget1 = false;
	m_IsTarget2 = false;
	m_IsFree1 = false;
	m_IsFree2 = false;

	////ゲーム開始時にプレイヤーの後頭部から始まるようにする
	//m_CameraPoint = { -0.5f,25.0f,52.5f };
	//m_CameraPos = { -0.5f,25.0f,52.5f };
}
//毎フレーム呼び出す処理(ノーマル)
void PlayCamera::Step(VECTOR _TargetPos) {

	//改良カメラ
	//===============================================================================
	//各種定義関連
	const float MAX_LEN_NEAR = 60.0f;   // この距離より離れるとカメラ移動開始
	const float MAX_LEN_FAR = 80.0f;    // これ以上離れさせない
	const float MIN_LEN_NEAR = 40.0f;   // この距離より近づくとカメラ移動開始
	const float MIN_LEN_FAR = 30.0f;    // これ以上は近づけさせない
	const float CAM_MOVE_SPEED = 0.5f;  // カメラの移動速度

	m_IsTarget1 = false;
	m_IsTarget2 = false;

	m_TargetPoint = _TargetPos;
	float RotSpeed = 0.05f;
	float RotX = 0.0f;
	float RotY = 0.0f;

	if (Input::IsInputRep(KEY_INPUT_UP)) {
		RotX += -RotSpeed;
	}
	else if (Input::IsInputRep(KEY_INPUT_DOWN)) {
		RotX += RotSpeed;
	}

	if (Input::IsInputRep(KEY_INPUT_LEFT)) {
		RotY += RotSpeed;
	}
	else if (Input::IsInputRep(KEY_INPUT_RIGHT)) {
		RotY += -RotSpeed;
	}

	if (InputPad::GetRAnalogYInput() > 0.0f) {
		RotX += (float)InputPad::GetRAnalogYInput()*0.05f;
	}
	else if (InputPad::GetRAnalogYInput() < 0.0f) {
		RotX += (float)InputPad::GetRAnalogYInput() * 0.05f;
	}

	if (InputPad::GetRAnalogXInput() < 0.0f) {
		RotY += InputPad::GetRAnalogXInput() * 0.05f;
	}
	else if (InputPad::GetRAnalogXInput() > 0.0f) {
		RotY += InputPad::GetRAnalogXInput() * 0.05f;
	}

	m_CalcRot.x += RotX;
	m_CalcRot.y += RotY;

	float DownLimit = DX_PI_F * 15.0f / 180.0f;
	float UpLimit = DX_PI_F * 20.0f / 180.0f;
	if (m_CalcRot.x > DownLimit) {
		m_CalcRot.x = DownLimit;
	}
	else if (m_CalcRot.x < -UpLimit) {
		m_CalcRot.x = -UpLimit;
	}

	//現在のカメラの位置からキャラクターの位置までの方向ベクトルを取得
	VECTOR dir = VSub(m_CameraPos, m_TargetPoint);
	dir.y = 0.0f;   //高さを考慮するとややこしいんで、一旦無視

	//今回は長さが重要なので、先ほど計算したベクトルから長さを計算
	float len = VSize(dir);

	//長さを求めたので、方向ベクトルは正規化してしまう
	dir = VNorm(dir);

	//カメラとプレイヤーの距離が一定以上離れた
	if (len > MAX_LEN_NEAR)
	{
		//本来の到達地点を計算
		dir = VScale(dir, MAX_LEN_NEAR);
		VECTOR tempPos = VAdd(m_TargetPoint, dir);

		//現在のカメラの位置から上記到達地点までの方向ベクトルを計算
		VECTOR tempDir = VSub(tempPos, m_CameraPos);
		tempDir.y = 0.0f;             //高さは無視
		tempDir = VNorm(tempDir);     //方向ベクトルなので正規化

		//目標到達地点に向けて、カメラの座標を移動させる
		tempDir = VScale(tempDir, CAM_MOVE_SPEED); //カメラの速度を計算
		m_CameraPos = VAdd(m_CameraPos, tempDir);

		//離れてはいけない距離以上は慣れていた場合の処理===========
		//新しく計算した位置と、注視点までの距離を計算
		tempDir = VSub(m_CameraPos, m_TargetPoint);
		tempDir.y = 0.0f; //やっぱり高さは無視

		//離れてはいけない距離を超えたかチェック(計算量を減らすため、2乗した値で比較)
		if (VSize(tempDir) > MAX_LEN_FAR)
		{
			//再度正規化し、強制的に最大距離に変更
			tempDir = VNorm(tempDir);
			tempDir = VScale(tempDir, MAX_LEN_FAR);
			m_CameraPos = VAdd(m_TargetPoint, tempDir);
		}
		//======================================================================
	}
	//カメラとプレイヤーの距離が一定以上近づいた
	else if (len < MIN_LEN_NEAR)
	{
		//本来の到達地点を計算
		dir = VScale(dir, MIN_LEN_NEAR);
		VECTOR tempPos = VAdd(m_TargetPoint, dir);

		//現在のカメラの位置から上記到達地点までの方向ベクトルを計算
		VECTOR tempDir = VSub(tempPos, m_CameraPos);
		tempDir.y = 0.0f;             //高さは無視
		tempDir = VNorm(tempDir);     //方向ベクトルなので正規化

		//目標到達地点に向けて、カメラの座標を移動させる
		tempDir = VScale(tempDir, CAM_MOVE_SPEED); //カメラの速度を計算
		m_CameraPos = VAdd(m_CameraPos, tempDir);

		//離れてはいけない距離以上は慣れていた場合の処理===========
		//新しく計算した位置と、注視点までの距離を計算
		tempDir = VSub(m_CameraPos, m_TargetPoint);
		tempDir.y = 0.0f; //やっぱり高さは無視

		//離れてはいけない距離を超えたかチェック(計算量を減らすため、2乗した値で比較)
		if (VSize(tempDir) < MIN_LEN_FAR)
		{
			//再度正規化し、強制的に最大距離に変更
			tempDir = VNorm(tempDir);
			tempDir = VScale(tempDir, MIN_LEN_FAR);
			m_CameraPos = VAdd(m_TargetPoint, tempDir);
		}
		//====================================================================
	}
	//============================================================================

	//回転行列作成
	MATRIX MatRotX = MGetRotX(m_CalcRot.x);
	MATRIX MatRotY = MGetRotY(m_CalcRot.y);

	//合成(Y→X)
	MATRIX MatRot = MMult(MatRotX, MatRotY);

	//相対ベクトル
	/*m_TargetPoint.y= 25.0f;*/
	VECTOR OffSet = VGet(0.0f, 35.0f, 60.0f);

	//カメラ位置
	VECTOR CameraPosCalc = VTransform(OffSet, MatRot);
	m_CameraPoint = VAdd(m_TargetPoint, CameraPosCalc);
	/*m_CameraPoint.y = 50.0f;*/

	/*m_TargetPos = m_TargetPoint;
	m_CameraPos = m_CameraPoint;*/
	m_CameraRot.y = m_CalcRot.y;

	if (!m_IsFree1 || !m_IsFree2) {
		VECTOR v1 = VSub(m_CameraPoint, m_CameraPos);
		float f1 = VSize(v1);
		if (f1 > CALC_LEN) {
			v1 = VNorm(v1);
			v1 = VScale(v1, 5.0f);
			m_CameraPos = VAdd(m_CameraPos, v1);
		}
		else {
			m_CameraPos = m_CameraPoint;
			m_IsFree1 = true;
		}

		VECTOR v2 = VSub(m_TargetPoint, m_TargetPos);
		float f2 = VSize(v2);
		if (f2 > CALC_LEN) {
			v2 = VNorm(v2);
			v2 = VScale(v2, 5.0f);
			m_TargetPos = VAdd(m_TargetPos, v2);
		}
		else {
			m_TargetPos = m_TargetPoint;
			m_IsFree2 = true;
		}
	}
	else {
		m_CameraPos = m_CameraPoint;
		m_TargetPos = m_TargetPoint;
	}
}
//ロックオン
void PlayCamera::Step(VECTOR _TargetPos, VECTOR _PlayerPos, bool _IsSPAtk) {
	m_IsFree1 = false;
	m_IsFree1 = false;

	//プレイヤー→敵の方向から回転角を作る
	VECTOR Dir = VSub(_TargetPos, _PlayerPos);
	Dir = VNorm(Dir);

	//Y軸回転
	m_CalcRot.y = atan2f(-Dir.x, -Dir.z);

	//X軸回転
	m_CalcRot.x = atan2f(Dir.y, sqrtf(Dir.x * Dir.x + Dir.z * Dir.z));

	//プレイヤー背面のオフセットを作る
	VECTOR Offset = VGet(0.0f, 20.0f, 100.0f);

	//回転行列を作る
	MATRIX MatRotX = MGetRotX(m_CalcRot.x);
	MATRIX MatRotY = MGetRotY(m_CalcRot.y);

	//X回転→Y回転
	MATRIX MatRot = MMult(MatRotX, MatRotY);

	//オフセットを回転させる
	Offset = VTransform(Offset, MatRot);

	//プレイヤー座標に足してカメラ座標へ
	m_CameraPoint = VAdd(_PlayerPos, Offset);

	//地面めり込み防止
	if (m_CameraPoint.y < 20.0f) {
		m_CameraPoint.y = 20.0f;
	}

	//_TargetPos代入
	m_TargetPoint = _TargetPos;
	m_TargetPoint.y -= 20.0f;

	/*m_TargetPos = m_TargetPoint;
	m_CameraPos = m_CameraPoint;*/

	if (!_IsSPAtk) {
		m_CameraRot.y = m_CalcRot.y;
	}

	if (!m_IsTarget1 || !m_IsTarget2) {
		VECTOR v1 = VSub(m_CameraPoint, m_CameraPos);

		float f1 = VSize(v1);
		if (f1 > CALC_LEN) {
			v1 = VNorm(v1);
			v1 = VScale(v1, 5.0f);
			m_CameraPos = VAdd(m_CameraPos, v1);
		}
		else {
			m_IsTarget1 = true;
			m_CameraPos = m_CameraPoint;
		}

		VECTOR v2 = VSub(m_TargetPoint, m_TargetPos);
		float f2 = VSize(v2);
		if (f2 > CALC_LEN) {
			v2 = VNorm(v2);
			v2 = VScale(v2, 5.0f);
			m_TargetPos = VAdd(m_TargetPos, v2);
		}
		else {
			m_IsTarget2 = true;
			m_TargetPos = m_TargetPoint;
		}
	}
	else {
		m_TargetPos = m_TargetPoint;
		m_CameraPos = m_CameraPoint;
	}
}
//更新処理
void PlayCamera::Update() {
	SetCameraPositionAndTargetAndUpVec(m_CameraPos, m_TargetPos, m_UpVec);
	VECTOR SoundUpVecY = VScale(m_CameraPos, -1.0f);
	/*SoundUpVecY = VGet(FZERO,FZERO,-1.0f);*/
	SoundUpVecY = VAdd(m_TargetPos, SoundUpVecY);
	Set3DSoundListenerPosAndFrontPos_UpVecY(m_TargetPos, SoundUpVecY);
	//SetCameraPositionAndAngle(m_CameraPos,m_CameraRot.x, m_CameraRot.y, m_CameraRot.z);
}
//デバック用
void PlayCamera::Draw() {
	DrawFormatString(50, 100, GetColor(255, 255, 0), "最終カメラ座標X:%f", m_CameraPoint.x);
	DrawFormatString(50, 125, GetColor(255, 255, 0), "最終カメラ座標Y:%f", m_CameraPoint.y);
	DrawFormatString(50, 150, GetColor(255, 255, 0), "最終カメラ座標Z:%f", m_CameraPoint.z);

	DrawFormatString(50, 200, GetColor(255, 255, 0), "カメラ座標X:%f", m_CameraPos.x);
	DrawFormatString(50, 225, GetColor(255, 255, 0), "カメラ座標Y:%f", m_CameraPos.y);
	DrawFormatString(50, 250, GetColor(255, 255, 0), "カメラ座標Z:%f", m_CameraPos.z);

	DrawFormatString(50, 300, GetColor(255, 255, 0), "最終注視点座標X:%f", m_TargetPoint.x);
	DrawFormatString(50, 325, GetColor(255, 255, 0), "最終注視点座標Y:%f", m_TargetPoint.y);
	DrawFormatString(50, 350, GetColor(255, 255, 0), "最終注視点座標Z:%f", m_TargetPoint.z);

	DrawFormatString(50, 400, GetColor(255, 255, 0), "注視点座標X:%f", m_TargetPos.x);
	DrawFormatString(50, 425, GetColor(255, 255, 0), "注視点座標Y:%f", m_TargetPos.y);
	DrawFormatString(50, 450, GetColor(255, 255, 0), "注視点座標Z:%f", m_TargetPos.z);
}
