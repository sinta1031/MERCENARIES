#pragma once
#include <DxLib.h>
#include "../lib/input.h"
#include "../lib/inputPad.h"
#include "math.h"

//ゲームプレイ中に使うカメラクラス
class PlayCamera {
private:
	VECTOR m_CameraPos;		//カメラ位置
	VECTOR m_TargetPos;		//注視点
	VECTOR m_UpVec;			//カメラの上方向
	VECTOR m_CameraRot;		//カメラ回転角度
	VECTOR m_CalcRot;
	VECTOR m_FocusPos;
	VECTOR m_CamRight;
	VECTOR m_TargetLookPos;
	VECTOR m_Forward;
	VECTOR m_ADSTarget;		//ADSの注視点
	float  m_MoveYam;
	float  m_ADSRate;		//ADSカメラ


	VECTOR m_CameraPoint;
	VECTOR m_TargetPoint;

	bool m_IsFree1;
	bool m_IsFree2;

	bool m_IsTarget1;
	bool m_IsTarget2;

	bool m_IsADS;

public:
	//コンストラクタ
	PlayCamera();

	//初期化
	void Init();

	//毎フレーム呼び出す処理(ノーマル)
	void Step(VECTOR _TargetPos, VECTOR _PlayerSpeed);

	//毎フレーム呼び出す処理(ロックオン)
	void Step(VECTOR _TargetPos,VECTOR _PlayerPos,bool _IsSPAtk);

	//更新処理
	void Update();

	//デバック用
	void Draw();

	//カメラの回転率
	VECTOR GetCameraRot() { return m_CameraRot; }

	VECTOR GetCameraPos() { return m_CameraPos; }

	VECTOR GetTarget() { return m_TargetPos; }

	bool GetIsTarget1() { return m_IsTarget1; }
	bool GetIsTarget2() { return m_IsTarget2; }

	bool GetIsAds() { return m_IsADS; }
};
