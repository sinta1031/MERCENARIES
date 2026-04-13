#pragma once
#pragma once
#include "PlayScene.h"
#include "TitleScene.h"
#include "ResultScene.h"
#include "../lib/input.h"
#include "../lib/InputPad.h"

class CSceneManager {
private:
	enum tagSCENE {
		SCENE_TITLE,  // タイトル画面
		SCENE_PLAY,   // ゲーム中
		SCENE_RESULT, // リザルト画面

		SCENE_NUM
	};

	CPlayScene c_PS; 
	CTitleScene c_TS;
	CResultScene c_RS;
	Input c_I;
	InputPad c_IP;
	tagSCENE m_SceneID; // シーン保存

public:
	//コンストラクタ・デストラクタ
	CSceneManager();
	~CSceneManager();

	// 繰り返し行う処理
	int Loop();
	// 描画処理
	void Draw();
};