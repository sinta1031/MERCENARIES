#pragma once
#include <DxLib.h>
#include "../lib/input.h"
#include "SoundManager.h"
#include <vector>

using namespace std;

class CTitleScene {
private:

	enum tagTITLE_PICTURE {
		TITLE_PICTURE,
		TITLE_UI,
		PUSH_MANUAL,

		TITLE_PICTURE_NUM,
	};

	enum tagTITLE_FONT {
		TITLE_FONT_1,
		TITLE_FONT_2,
		TITLE_MENU_1,
		TITLE_MENU_2,

		TITLE_FONT_NUM,
	};

	enum tagTITLE_MENU {
		START_GAME,
		EXIT,
	};

	enum tagTITLE_SCENE {
		TITLE_SCENE_INIT,
		TITLE_SCENE_LOAD,
		TITLE_SCENE_LOOP,
		TITLE_SCENE_END,

		TITLE_SCENE_NUM
	};

	VECTOR m_pos;	// 表示する座標

	static vector<int>m_hndl; // 画像ハンドル
	static vector<int>m_Fhndl; // フォントハンドル

	tagTITLE_SCENE m_SceneID; // シーン保存
	tagTITLE_MENU m_MenuID;	  // 選択肢保存
	CSoundManager c_SDM;     // サウンドマネージャー

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