#pragma once
#include <DxLib.h>

static const int WATER_MAX = 4;

class Cwater {
private:

	int m_waterhndl[WATER_MAX];     //水場のハンドル
	VECTOR m_waterPos[WATER_MAX];   //水場の座標

public:
	// コンストラクタ・デストラクタ
	Cwater();
	~Cwater();

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

	//指定したフレームの座標を渡す
	VECTOR GetFramePos(int _hndl, int _frameNum) { return MV1GetFramePosition(_hndl, _frameNum); }

	// 当たり判定
	// @center  :  当たり判定する相手の座標
	// @radius　:  球の半径
	// @return  :  押し戻すべき距離と方向
	bool waterHitCheck(VECTOR center, float redius);
};