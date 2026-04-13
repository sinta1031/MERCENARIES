#pragma once
#include <DxLib.h>

class CDebugCamera {
private:

	VECTOR m_Pos;	    // カメラの位置
	VECTOR m_Rot;       // カメラの回転角度
	VECTOR m_targetPos; // カメラの注視点
	VECTOR m_upVec;     // カメラ上方向

public:
	// コンストラクタ・デストラクタ
	CDebugCamera();

	//初期化
	void Init();

	// カメラの座標計算
	void Step();

	// カメラの更新
	void Update();

	//階段の仕掛けが動くときに一度だけカメラを向ける
	void EventCamera(VECTOR focus);

};