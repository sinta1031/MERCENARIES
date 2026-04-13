#pragma once
#include <DxLib.h>
#include "ShotManager.h"
#include "PlayCamera.h"

class CPlayer {
public:

	//プレイヤーの状態
	enum tagPlayerState {
		PLAYER_STATE_NORMAL,    // 待機・歩き中
		PLAYER_STATE_JUMP,      // ジャンプ中

		PLAYER_STATE_NUM,
	};

private:
	
		VECTOR m_vPos;               // 座標
		VECTOR m_vRot;               // 回転速度
		float m_gravity;             // 重力
		tagPlayerState m_eState;     // プレイヤーの状態
		int m_PosX;                  // 画面の座標X
		int m_PosY;                  // 画面の座標Y
		float m_radius;              // 物体の半径取得
		int m_Hndl;                  // モデルハンドル
		bool m_isActive;             // 生存フラグ
		VECTOR m_CameraRot;          // カメラの回転率を代入する

public:
	// コンストラクタ・デストラクタ
	CPlayer();
	~CPlayer();

	//初期化
	void Init();

	//ロード
	void Load();

	//描画
	void Draw();

	//破棄
	void Exit();

	//行動処理
	void Step();

	// プレイヤーの更新
	void Update();

	// ジャンプ
	void jump();

	//落下判定
	void Falldetection();

	//重力
	void gravity();

	// 位置情報取得
	VECTOR GetPos();

	// 回転情報取得
	float GetRot();

	//ヒット後の処理
	void HitCalc();

	// 当たり判定の座標用
	VECTOR GetCenter();

	// 当たり判定の半径サイズを取得
	float GetRadius() { return m_radius; }

	//生存情報取得
	bool IsActive() { return m_isActive; }
	void SetActive(bool active) { m_isActive = active; }

	//カメラの回転率代入
	void SetCameraRot(VECTOR camerarot) { m_CameraRot = camerarot; }

	//現在位置に座標加算
	void ReflectCollision(VECTOR addVec);
};