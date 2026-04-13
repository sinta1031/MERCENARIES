#pragma once
#include <DxLib.h>

class Cswitch {
private:
	int m_switchhndl;               //ボタンハンドル
	int m_switchhndl1;              //ボタンハンドル1
	float m_switchradius;           //ボタン半径取得
	bool m_switchHitFlag;           //ボタンが押されたか
	VECTOR m_switchScale;           //ボタンのスケール
	VECTOR m_switchPos;             //ボタンの座標

public:
	// コンストラクタ・デストラクタ
	Cswitch();
	~Cswitch();

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

	//ボタンの押されたかのフラグ情報を取得
	bool GetswitchHitFlag() { return m_switchHitFlag; }

	// 当たり判定
	// @center  :  当たり判定する相手の座標
	// @radius　:  球の半径
	// @return  :  押し戻すべき距離と方向
	VECTOR switchHitCheck(VECTOR center, float radius);
};