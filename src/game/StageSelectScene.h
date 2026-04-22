#pragma once
#include <DxLib.h>
#include "../lib/input.h"
#include "SoundManager.h"


class CStageSelectScene {
private:
	enum tagSTAGE_SELECT_SCENE {
		STAGE_SELECT_SCENE_INIT,
		STAGE_SELECT_SCENE_LOAD,
		STAGE_SELECT_SCENE_LOOP,
		STAGE_SELECT_SCENE_END,

		STAGE_SELECT_SCENE_NUM
	};

	enum tagSCENE_SELECT {
		BACK,
		NEXT,
		WAIT,
	};

	tagSTAGE_SELECT_SCENE m_SceneID; // シーン保存
	tagSCENE_SELECT m_SelectID;		 // 選択肢保存

	CSoundManager c_SDM;     // サウンドマネージャー

public:
	//コンストラクタ・デストラクタ
	CStageSelectScene();
	~CStageSelectScene();

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