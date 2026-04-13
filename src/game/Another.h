#pragma once
#include <DxLib.h>

class CAnother {
public:

	//分身のサイズ状態
	enum tagSizeState {
		NORMAL,
		BIG,
	};

private:

	VECTOR m_vPos;					// 座標
	VECTOR m_vRot;					// 回転速度
	VECTOR m_vScale;				// 大きさ
	tagSizeState m_sState;			// 分身のサイズ状態
	float m_radius;					// 物体の半径取得
	float m_gravity;				// 重力
	int m_Hndl;						// モデルハンドル
	bool m_isActive;				// 生存フラグ
	bool m_isPos;					// 本体の位置に動かしたらtrueへ
	VECTOR m_CameraRot;				// カメラの回転率を代入する
	
public:

	// コンストラクタ・デストラクタ
	CAnother();
	~CAnother();

	//初期化
	void Init();

	//ロード
	void Load();

	//描画
	void Draw();

	//破棄
	void Exit();

	//行動処理
	void Step(VECTOR pos);

	// プレイヤーの更新
	void Update();

	// ジャンプ
	void jump();

	// 位置情報取得
	VECTOR GetPos();

	// 回転情報取得
	float GetRot();

	// 位置情報リセット
	VECTOR ResetPos();

	//落下判定
	void Falldetection();

	//ヒット後の処理
	void HitCalc();

	// 当たり判定の座標用
	VECTOR GetCenter();

	// 当たり判定の半径サイズを取得
	float GetRadius() { return m_radius; }

	//生存情報取得
	bool IsActive() { return m_isActive; }
	void SetActive(bool active) { m_isActive = active; }
	void SetisPos(bool pos) { m_isPos = pos; }

	void SetCameraRot(VECTOR camerarot) { m_CameraRot = camerarot; }

	//現在位置に座標加算
	void ReflectCollision(VECTOR addVec);

	//分身のサイズタイプ切り替え
	void ChangeAnotherSize(tagSizeState id) { m_sState = id; }

	//分身のサイズタイプ取得
	tagSizeState GetID() { return m_sState; }
};