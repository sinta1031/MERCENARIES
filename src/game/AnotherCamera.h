#pragma once
#include <DxLib.h>
#include "Another.h"

class CAnotherCamera {
private:
	
	VECTOR m_cameraPos = { 0.0f,20.0f,-50.0f };	   // カメラの位置
	VECTOR m_targetPos = { 0.0f,0.0f,0.0f };       // カメラの注視店
	VECTOR m_cameraRot = { 0.0f,0.0f,0.0f };       // カメラの回転値
	VECTOR m_upVec = { 0.0f, 1.0f, 0.0f };		   // カメラ上方向

public:
	// コンストラクタ・デストラクタ
	CAnotherCamera();

	//初期化
	void Init();

	// カメラの座標計算
	// @focus :  プレイヤーの座標
	// @rotY  :  プレイヤーの角度
	void Step(VECTOR focus, float rotY, CAnother& _Another);

	// カメラの更新
	void Update();

	// カメラの座標取得
	VECTOR GetCamareRot() { return  m_cameraRot; }
};

