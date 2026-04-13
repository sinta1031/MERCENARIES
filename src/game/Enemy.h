#pragma once
#include <DxLib.h>
#include "player.h"

static const float WALK_SPEED = 0.5f;

class CEnemy {
private:

	VECTOR m_pos;    //座標
	VECTOR m_rot;    //回転速度
	VECTOR m_speed;  //移動方向と速度
	float m_radius;  //物体の半径取得
	int m_hndl;      //モデルハンドル
	bool m_isActive; //生存フラグ

public:

	//コンストラクタ
	CEnemy();
	~CEnemy();

	// 初期化
	void Init();

	// ロード
	void Load(int hndl);

	// 更新処理
	void Step();

	// 更新処理
	void Update();

	// 描画関数
	void Draw();

	// 廃棄処理
	void Exit();

	//出現関数
	bool Request(const VECTOR& pos/*, const VECTOR& speed*/);

	// 座標取得
	VECTOR GetPos() { return m_pos; }

	bool IsActive() { return m_isActive; }
	void SetActive(bool active) { m_isActive = active; }

	// ターゲットを追いかける
	void ChaceTarget(VECTOR targetPos);

	//ヒット後の処理
	void HitCalc();

	// 当たり判定の座標用
	VECTOR GetCenter();

	// 当たり判定の半径サイズを取得
	float GetRadius() { return m_radius; }
};