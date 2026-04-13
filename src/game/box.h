#pragma once
#include <DxLib.h>

static const int BOX_X_MAX = 16;
static const int BOX_Y_MAX = 3;

class Cbox {
private:
	int m_boxhndl[BOX_X_MAX][BOX_Y_MAX];        //ボックスのハンドル
	VECTOR m_boxPos[BOX_X_MAX][BOX_Y_MAX];		//ボックスの座標
	bool m_boxisActive[BOX_X_MAX][BOX_Y_MAX];   //ボックスのアクティブ
	float m_boxgravity;							//ボックスの重力

public:
	// コンストラクタ・デストラクタ
	Cbox();
	~Cbox();

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

	//ボックスの生存情報
	void SetboxActive(bool active,int _X,int _Y) { m_boxisActive[_X][_Y] = active; }

	// 当たり判定
	// @center  :  当たり判定する相手の座標
	// @radius　:  球の半径
	// @return  :  押し戻すべき距離と方向
	VECTOR boxHitCheck(VECTOR center, float redius);
	bool boxHitDestroyCheck(VECTOR center, float redius);

	//現在位置に座標加算
	void ReflectCollision(VECTOR addVec);
};