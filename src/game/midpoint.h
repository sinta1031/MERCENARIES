#pragma once
#include <DxLib.h>

static const int MIDPOINT_MAX = 3;

class Cmidpoint {
private:

	int m_hndl_red[MIDPOINT_MAX];   //中間ポイントのハンドル(false)
	int m_hndl_blue[MIDPOINT_MAX];  //中間ポイントのハンドル(true)
	VECTOR m_Pos[MIDPOINT_MAX];		//中間ポイントの座標
	bool m_Hitflag[MIDPOINT_MAX];	//中間ポイントのフラグ(プレイヤーと当たったか？)

public:
	// コンストラクタ・デストラクタ
	Cmidpoint();
	~Cmidpoint();

	//初期化
	void Init();

	//ロード
	void Load(int _stageNum,int _hndl);

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
	bool midpointHitCheck(VECTOR center, float redius);

	//座標取得
	VECTOR GetPos();
};