#pragma once
#include <DxLib.h>
#include "../lib/input.h"


class CResultScene {
private:
	enum tagRESULT_SCENE {
		RESULT_SCENE_INIT,
		RESULT_SCENE_LOAD,
		RESULT_SCENE_LOOP,
		RESULT_SCENE_END,

		RESULT_SCENE_NUM
	};

	tagRESULT_SCENE m_SceneID; // シーン保存

public:
	//コンストラクタ・デストラクタ
	CResultScene();
	~CResultScene();

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