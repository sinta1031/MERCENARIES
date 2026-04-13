#pragma once
#include <DxLib.h>

class Csponge {
public:

	enum tagSpongeState {
		NORMAL,
		BIG,
	};

private:

	tagSpongeState m_tagstage;
	int m_spongehndl;
	VECTOR m_spongePos;
	VECTOR m_spongeScale;
	bool m_spomgehit;
	float m_spongeradius;
	int m_Time;	

public:

	// コンストラクタ・デストラクタ
	Csponge();
	~Csponge();

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

	//位置情報取得
	VECTOR GetPos();

	//当たり判定の座標用
	VECTOR GetCenter();

	//当たり判定の半径サイズを取得
	float GetRadius();

	//座標にフレームの座標を代入
	void FrameIndexPos(int _hndl,int _frameNum);

	//サイズタイプ切り替え
	void ChangeSpongeSize(tagSpongeState id,int _id);

	//サイズタイプ取得
	tagSpongeState GetID(int id);

	//指定したフレームの座標を渡す
	VECTOR GetFramePos(int _hndl, int _frameNum) { return MV1GetFramePosition(_hndl, _frameNum); }

	// 当たり判定
	// @center  :  当たり判定する相手の座標
	// @radius　:  球の半径
	// @return  :  押し戻すべき距離と方向
	VECTOR spongeHitCheck(VECTOR center, float radius);
};