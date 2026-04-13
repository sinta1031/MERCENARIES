#pragma once
#include <DxLib.h>

class Cbud {
private:

	int m_budhndl;                  //芽のハンドル
	float m_budradius;				//芽の半径
	bool m_budflag;					//芽のフラグ
	bool m_active;					//芽の生存フラグ
	VECTOR m_budPos;				//芽の座標
	VECTOR m_budScale;				//芽のスケール

public:

	// コンストラクタ・デストラクタ
	Cbud();
	~Cbud();

	//初期化
	void Init();

	//ロード
	void Load(int _hndl);

	//更新処理
	void Step();

	//フィールドのアップデート
	void Update();

	//描画
	void Draw();

	//破棄
	void Exit();

	//フラグ管理
	void HitCalc();

	//位置情報取得
	VECTOR GetPos();

	//当たり判定の座標用
	VECTOR GetCenter();

	//当たり判定の半径サイズを取得
	float GetRadius();

	//生存情報取得
	bool IsActive() { return m_active; }

	//指定したフレームの座標を渡す
	VECTOR GetFramePos(int _hndl, int _frameNum) { return MV1GetFramePosition(_hndl, _frameNum); }
};