#pragma once
#include <DxLib.h>
#include "../lib/input.h"
#include "SoundManager.h"



class CCharacterSelectScene {
private:
	enum tagCHARACTER_SELECT_SCENE {
		CHARACTER_SELECT_SCENE_INIT,
		CHARACTER_SELECT_SCENE_LOAD,
		CHARACTER_SELECT_SCENE_LOOP,
		CHARACTER_SELECT_SCENE_END,

		CHARACTER_SELECT_SCENE_NUM
	};

	tagCHARACTER_SELECT_SCENE m_SceneID; // シーン保存

public:
	//コンストラクタ・デストラクタ
	CCharacterSelectScene();
	~CCharacterSelectScene();

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