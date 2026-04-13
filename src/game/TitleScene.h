#pragma once
#include <DxLib.h>
#include "../lib/input.h"


class CTitleScene {
private:
	enum tagTITLE_SCENE {
		TITLE_SCENE_INIT,
		TITLE_SCENE_LOAD,
		TITLE_SCENE_LOOP,
		TITLE_SCENE_END,

		TITLE_SCENE_NUM
	};

	tagTITLE_SCENE m_SceneID; // シーン保存

public:
	//コンストラクタ・デストラクタ
	CTitleScene();
	~CTitleScene();

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