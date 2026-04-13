#pragma once
#include <DxLib.h>

class Cgoal {
private:

	int m_goalhndl;					//ゴールハンドル
	float m_goalradius;             //ゴール半径取得
	VECTOR m_goalScale;             //ゴールのスケール
	VECTOR m_goalPos;               //ゴールの座標

public:

	// コンストラクタ・デストラクタ
	Cgoal();
	~Cgoal();

	//初期化
	void Init();

	//ロード
	void Load(int _stageNum, int _hndl);

	//更新処理
	void Step();

	//フィールドのアップデート
	void Update();

	//描画
	void Draw();

	//破棄
	void Exit();

	// ゴール位置情報取得
	VECTOR GetgoalPos();

	// ゴール当たり判定の座標用
	VECTOR GetgoalCenter();

	// ゴールの当たり判定の半径サイズを取得
	float GetgoalRadius() { return m_goalradius; }

	//指定したフレームの座標を渡す
	VECTOR GetFramePos(int _hndl, int _frameNum) { return MV1GetFramePosition(_hndl, _frameNum); }
};