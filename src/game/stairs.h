#pragma once
#include <DxLib.h>

class Cstairs {
private:

	int m_stairshndl;               //階段ハンドル
	VECTOR m_stairsScale;           //階段のスケール
	VECTOR m_stairsPos;             //階段の座標

public:

	// コンストラクタ・デストラクタ
	Cstairs();
	~Cstairs();

	//初期化
	void Init();

	//ロード
	void Load();

	//更新処理
	void Step(bool flag);

	//フィールドのアップデート
	void Update();

	//描画
	void Draw();

	//破棄
	void Exit();

	//階段の仕掛け起動
	void StairsMechanism();

	// 階段位置情報取得
	VECTOR GetStairsPos();

	// 当たり判定
	// @center  :  当たり判定する相手の座標
	// @radius　:  球の半径
	// @return  :  押し戻すべき距離と方向
	VECTOR stairsHitCheck(VECTOR center, float radius);
};