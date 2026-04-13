#pragma once
#include <DxLib.h>
#include "bud.h"

class Cwood {
private:
	int m_woodhndl;                 //木のハンドル
	VECTOR m_woodPos;				//木の座標
	VECTOR m_woodScale;				//木のスケール

public:

	// コンストラクタ・デストラクタ
	Cwood();
	~Cwood();

	//初期化
	void Init();

	//ロード
	void Load(int _hndl);

	//更新処理
	void Step(Cbud &_Cbud);

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
	VECTOR woodHitCheck(VECTOR center, float radius);
};