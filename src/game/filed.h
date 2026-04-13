#pragma once
#include <DxLib.h>

class CFiled {
private:

	//ステージの状態簡易
	enum tagSTAGE {
		STAGE1,
		STAGE2,
		STAGE3,
	};

	tagSTAGE m_tagstage;            //ステージ状態
	int m_fieldhndl;                //フィールドハンドル
	int m_Skyhndl;					//スカイハンドル
	VECTOR m_SkyScale;				//スカイスケール
	VECTOR m_Rot;                   //回転速度
	bool m_isHitFlag;               //フィールドとの当たり判定

public:

	// コンストラクタ・デストラクタ
	CFiled();
	~CFiled();

	//初期化
	void Init();

	//ロード
	void Load();

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
	VECTOR FieldHitCheck(VECTOR center, float radius);
};