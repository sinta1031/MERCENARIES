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

	enum FrameNamber{
		ARMATURE,				//原点とれるよ
		HIP,					//お尻
		SPINE,					//脊髄
		CHEST,					//胸骨
		HEAD,					//頭蓋骨
		HEAD_END,				//頭の頂点
		SHOULDER_LEFT,			//左鎖骨
		UPPERARM_LEFT,			//左上腕骨
		LOWERARM_LEFT,			//左尺骨
		LOWERARM_LEFT_END,		//左指骨
		SHOULDER_RIGHT,			//右鎖骨
		UPEERARM_RIGHT,			//右上腕骨
		LOWERARM_RIGHT,			//右尺骨
		LOWERARM_RIGHT_END,		//右指骨
		TARGET_BOON,			//プレイヤーの注視点
		TARGET_BOON_END,		//プレイヤーの注視点
		PELBIS_LEFT,			//左骨盤
		UPPERLEG_LEFT,			//左大腿骨
		LOWERLEG_LEFT,			//左脛骨
		LOWERLEG_LEFT_END,		//左指骨
		PELBIS_RIGHT,			//右骨盤
		UPEERLEG_RIGHT,			//右大腿骨
		LOWERLEG_RIGHT,			//右脛骨
		LOWERLEG_RIGHT_END,		//右指骨
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

	//モデルハンドル取得
	int GetHndl() { return m_Hndl; }

	//生存情報取得
	bool IsActive() { return m_isActive; }
	void SetActive(bool active) { m_isActive = active; }

	//カメラの回転率代入
	void SetCameraRot(VECTOR camerarot) { m_CameraRot = camerarot; }

	//現在位置に座標加算
	void ReflectCollision(VECTOR addVec);

	//指定したフレームの座標を渡す
	VECTOR GetFramePos(int _Hndl, int _FrameNum)const { return MV1GetFramePosition(_Hndl, _FrameNum); }
};