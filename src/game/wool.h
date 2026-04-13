#pragma once
#include <DxLib.h>

class Cwool {
private:

	int m_woolhndl;			//壁ハンドル
	float m_woolgravity;	//壁の重力
	float m_woolradius;		//壁の当たり判定の半径
	bool m_woolflg;			//壁のフラグ
	bool m_woolHitflg;		//壁の当たり判定のフラグ
	VECTOR m_woolPos;		//壁の座標
	VECTOR m_woolRot;		//壁の回転

	int m_woolcagehndl;		//壁の中の檻
	VECTOR m_woolcagePos;	//壁の中の檻

public:
	// コンストラクタ・デストラクタ
	Cwool();
	~Cwool();

	//初期化
	void Init();

	//ロード
	void Load(int hndl);

	//更新処理
	void Step();

	//フィールドのアップデート
	void Update();

	//描画
	void Draw();

	//破棄
	void Exit();

	//ぶっ飛ぶ処理
	void Knockback();

	// 当たり判定の座標用
	VECTOR GetCenter();

	// 当たり判定の半径サイズを取得
	float GetRadius() { return m_woolradius; }

	void SetActive(bool active) { m_woolHitflg = active; }

	//指定したフレームの座標を渡す
	VECTOR GetFramePos(int _hndl, int _frameNum) { 
		return MV1GetFramePosition(_hndl, _frameNum); 
	}

	// 当たり判定
	// @center  :  当たり判定する相手の座標
	// @radius　:  球の半径
	// @return  :  押し戻すべき距離と方向
	VECTOR woolHitCheck(VECTOR center, float redius);
	VECTOR woolcageHitCheck(VECTOR center, float redius);
};