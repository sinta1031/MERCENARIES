#pragma once
#include <DxLib.h>

class Ccanter {
private:

	VECTOR m_cPos;               // カンテラの座標
	VECTOR m_cRot;               // カンテラの回転速度
	int m_Hndl;                  // カンテラのハンドル

public:

	// コンストラクタ・デストラクタ
	Ccanter();
	~Ccanter();

	//初期化
	void Init();

	//ロード
	void Load();

	//描画
	void Draw();

	//破棄
	void Exit();

	//行動処理
	void Step(int hndl);

	// プレイヤーの更新
	void Update();

	//指定したフレームの座標を渡す
	VECTOR GetFramePos(int _hndl, int _frameNum) { return MV1GetFramePosition(_hndl, _frameNum); }
};