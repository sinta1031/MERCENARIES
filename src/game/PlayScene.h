#pragma once
#include <DxLib.h>

#include "CameraManager.h"
#include "playerManager.h"
#include "filed.h"
#include "player.h"
#include "ShotManager.h"
#include "EnemyManager.h"
#include "CollisionManager.h"
#include "SoundManager.h"

class CPlayScene {
private:
	enum tagPLAY_SCENE {
		PLAY_SCENE_INIT,
		PLAY_SCENE_LOAD,
		PLAY_SCENE_LOOP,
		PLAY_SCENE_END,

		PLAY_SCENE_NUM
	};

	CCameraManager c_CM;     // カメラマネージャー
	CPlayerManager c_PM;     // プレイヤーマネージャー
	CCollisionManager c_CLM; // コリジョンマネージャー
	CShotManager c_SM;       // ショットマネージャー
	CEnemyManager c_EM;      // エネミーマネージャー
	CSoundManager c_SDM;     // サウンドマネージャー
	CFiled c_F;              // フィールド
	tagPLAY_SCENE m_SceneID; // シーン保存

public:
	//コンストラクタ・デストラクタ
	CPlayScene();
	~CPlayScene();

	// 繰り返し行う処理
	int Loop();
	// 描画処理
	void Draw();

private:
	// 初期化
	void Init();
	// 終了処理
	void Exit();
	// データロード
	void Load();
	// 毎フレーム呼ぶ処理
	void Step();
};