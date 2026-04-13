#pragma once
#include <DxLib.h>

class Cgate {
private:

	int m_gatehndl;                 //ゲートのハンドル
	VECTOR m_gatePos;               //ゲートの座標

public:
	// コンストラクタ・デストラクタ
	Cgate();
	~Cgate();

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
};