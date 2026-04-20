#pragma once
#include <DxLib.h>
#include "../lib/input.h"
#include <vector>

using namespace std;

class CTitleScene {
private:

	enum tagTITLE_PICTURE {
		TITLE_PICTURE,
		TITLE_UI,

		TITLE_PICTURE_NUM,
	};

	enum tagTITLE_SCENE {
		TITLE_SCENE_INIT,
		TITLE_SCENE_LOAD,
		TITLE_SCENE_LOOP,
		TITLE_SCENE_END,

		TITLE_SCENE_NUM
	};

	tagTITLE_SCENE m_SceneID; // シーン保存

	tagTITLE_PICTURE m_PictureID; // 画像保存

	static vector<int>m_hndl; // 画像ハンドル

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