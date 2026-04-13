#pragma once
#include <DxLib.h>

class Coli {
private:

	int m_olihndl;                  //檻ハンドル
	VECTOR m_oliPos;                //檻の座標

public:

	// コンストラクタ・デストラクタ
	Coli();
	~Coli();

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

	// 当たり判定
	// @center  :  当たり判定する相手の座標
	// @radius　:  球の半径
	// @return  :  押し戻すべき距離と方向
	VECTOR oliHitCheck(VECTOR center, float radius);
};