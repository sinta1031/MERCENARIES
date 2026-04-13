#pragma once
#include <DxLib.h>
#include "player.h"
#include "Another.h"
#include "PlayCamera.h"


// 複数のプレイヤーを管理する
class CPlayerManager {
public:
	
	//モード変更
	enum tagModeID {
		ID_PEAR,  // 一緒にいる状態
		ID_BUNR,  // 分離状態

		ID_MODENUM
	};

	//操作キャラ変更
	enum tagPlayerID {
		ID_PLAYER,   // プレイヤー
		ID_ANOTHER,  // 分身

		ID_PLAYERNUM
	};

private:

	CPlayer m_play;      // 主人公を操作している
	CAnother m_another;  // 分身を操作している

	tagPlayerID m_id;    // 今どのプレイヤーを使っているか
	tagModeID b_id;      // 今プレイヤーがどのモードなのか
	
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

	// ペアモードの更新処理
	void StepPear();

	// 分離モードの更新処理
	void StepSolo();

	// プレイヤーの更新
	void Update();

	//描画
	void Draw();

	//破棄
	void Exit();

	//チェンジフラグ
	void changecheck();

	// プレイヤーのタイプ切り替え
	void ChangePlayer(tagPlayerID id) { m_id = id; }

	// モードのタイプ切り替え
	void ChangeMode(tagModeID id) { b_id = id; }

	// プレイヤーのタイプ取得
	tagPlayerID GetPlayerID() { return m_id; }

	// プレイヤーのタイプ取得
	tagModeID GetModeID() { return b_id; }

	// プレイヤーのインスタンス取得
	CPlayer& Getplayerinstance();

	//	分身のインスタンス取得
	CAnother& GetAnotherinstance();

	void SetCameraRot(VECTOR p_camerarot, VECTOR a_camerarot);
};
