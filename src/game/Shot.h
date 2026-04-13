#pragma once
#include <DxLib.h>

class CShot {
private:
	
	VECTOR m_vPos;           // 座標
	VECTOR m_vSpeed;         // 移動速度
	float m_radius;          // 物体の半径取得
	int m_Hndl;              // モデルハンドル
	float m_gravity;         // 重力
	bool m_isActive;         // 生存フラグ
	int m_isActiveTime;      // フラグタイム
	
public:

	// コンストラクタ・デストラクタ
	CShot();
	~CShot();

	//初期化
	void Init();

	//ロード
	void Load(int orginHndl);

	//描画
	void Draw();

	//破棄
	void Exit();

	//行動処理
	void Step();

	//弾の更新
	void Update();

	//弾をリクエスト
	//@pos:どこから発射するか
	//@speed:どの方向に飛んでいくか
	//@return:生成成功か失敗か
	bool Request(const VECTOR& pos, const VECTOR& speed);

	//ヒット後の処理
	void HitCalc();

	//生存情報取得
	bool IsActive() { return m_isActive; }
	void SetActive(bool active) { m_isActive = active; }

	// 座標取得
	VECTOR GetPos() { return m_vPos; }

	// 当たり判定の座標用
	VECTOR GetCenter();

	// 当たり判定の半径サイズを取得
	float GetRadius() { return m_radius; }
};