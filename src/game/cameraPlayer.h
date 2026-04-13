#pragma once
#include <DxLib.h>

class CPlayerCamera {
private:
	VECTOR m_camPos;		//カメラの位置
	VECTOR m_targetPos;		//カメラの注視点
	VECTOR m_upVec;			//カメラの上方向
	VECTOR m_camRot;		//カメラの回転
public:
	CPlayerCamera();
	~CPlayerCamera();

	//初期化
	void Init();

	//カメラの座標計算
	//vForcus	:プレイヤーの座標
	//fRot		:プレイヤーの角度
	void Step(VECTOR vForcus);

	// カメラ座標の更新
	void Update();

	//--------------------------------------------
	//				ゲッター
	//--------------------------------------------
	//カメラの位置を取得
	VECTOR GetCameraPos() { return m_camPos; }
	//カメラの回転量ゲット
	VECTOR GetCameraRot() { return m_camRot; }
	//カメラのY軸回転ゲット
	float GetCameraRotY() { return m_camRot.y; }
	//カメラの注視点
	VECTOR GetFocus() { return m_targetPos; }

	//--------------------------------------------
	//				セッター
	//--------------------------------------------
	void SetCameraPos(VECTOR pos) { m_camPos = pos; }
	void SetCameraRot(VECTOR rot) { m_camRot = rot; }

private:
	////画面の外に出たか確認
	//bool MousePointCheck();
};