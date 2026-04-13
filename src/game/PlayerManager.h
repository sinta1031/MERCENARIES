#pragma once
#include <DxLib.h>
#include "player.h"
#include "PlayCamera.h"


// 複数のプレイヤーを管理する
class CPlayerManager {
public:



private:

	CPlayer m_play;      // 主人公を操作している

	
public:

	// コンストラクタ
	CPlayerManager();
	~CPlayerManager();

	//初期化
	void Init();

	//ロード
	void Load();

	// 更新処理
	void Step();

	// プレイヤーの更新
	void Update();

	//描画
	void Draw();

	//破棄
	void Exit();

	// プレイヤーのインスタンス取得
	CPlayer& Getplayerinstance();

	void SetCameraRot(VECTOR p_camerarot);
};
