#pragma once
#include "Shot.h"

// 相方の水の最大数
static const int PL_SHOT_NUM =100;

// 複数の弾を管理する
class CShotManager {
private:

	static CShot c_S[PL_SHOT_NUM];

public:

	// コンストラクタ
	CShotManager();

	//初期化
	void Init();

	//ロード
	void Load();

	//終了処理
	void Exit();

	//描画処理
	void Draw();

	// 弾の更新
	void Step();

	// 弾の更新
	void Update();

	//弾をリクエスト
	//@pos:どこから発射するか
	//@speed:どの方向に飛んでいくか
	//@return:生成成功か失敗か
	static void Request(const VECTOR& pos);

	//弾一発分の情報取得
	CShot& GetShot(int _ID) { return c_S[_ID]; }
};