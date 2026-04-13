#pragma once
#include <DxLib.h>

static const int OIL_MAX = 4;

class Coil{
private:

	int m_oilhndl[OIL_MAX];			//オイルのハンドル
	int m_oilpoolhndl;				//オイルだまりのハンドル
	VECTOR m_oilPos[OIL_MAX];		//オイルの座標
	VECTOR m_oilpoolPos;			//オイルだまりの座標
	float m_oilgravity;				//オイルの重力
	bool m_isHitFlag;               //フィールドとの当たり判定

public:

	// コンストラクタ・デストラクタ
	Coil();
	~Coil();

	//初期化
	void Init();

	//ロード
	void Load(int _hndl);

	//更新処理
	void Step(int _hndl);

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
	bool oilpoolHitCheck(VECTOR center, float radius);
	bool oilHitCheck(VECTOR center, float radius);
};