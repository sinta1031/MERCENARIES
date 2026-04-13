#pragma once
#include "Enemy.h"

static const int ENEMY_MAXNUM = 150;
static const int ENEMY_NUM = 20;

class CEnemyManager {
private:
	CEnemy c_E[ENEMY_MAXNUM]; // 敵
	int m_waitCount;       // 敵が出るまでの時間

public:
	//コンストラクタ
	CEnemyManager();
	~CEnemyManager();

	// 初期化
	void Init();

	// ロード
	void Load();

	// 更新処理
	void Step(VECTOR targetpos);

	// 更新処理
	void Update();

	// 描画関数
	void Draw();

	// 廃棄処理
	void Exit();

	//リクエストする
	void Request();

	//エネミーの数分の生存判定を消す
	void AllIsActive();

	//敵一人分の情報取得
	CEnemy& GetEnemy(int _ID) { return c_E[_ID]; }
};