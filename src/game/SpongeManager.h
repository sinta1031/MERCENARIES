#pragma once
#include "Sponge.h"

// スポンジの最大数
static const int SPONGE_MAX = 25;

// 複数のスポンジを管理する
class CSpongeManager {
private:

	static Csponge c_S[SPONGE_MAX];

public:

	// コンストラクタ
	CSpongeManager();

	//初期化
	void Init();

	//ロード
	void Load(int _hndl);

	//終了処理
	void Exit();

	//描画処理
	void Draw();

	// 弾の更新
	void Step();

	// 弾の更新
	void Update();

	//プレイヤーとのDXライブラリの当たり判定
	VECTOR spongeHitCheck(VECTOR center, float radius);

	//弾一発分の情報取得
	Csponge& GetSponge(int _ID) { return c_S[_ID]; }
};