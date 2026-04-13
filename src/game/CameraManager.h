#pragma once
#include <DxLib.h>
#include "PlayCamera.h"
#include "AnotherCamera.h"
#include "Debugcamera.h"
#include "Another.h"

// 複数のカメラを管理する
class CCameraManager {
public:
	
	enum tagCameraID {
		ID_PLAY,     // ゲームのメインカメラ
		ID_DEBUG,    // デバック時のカメラ
		ID_ANOTHER,  // 分身のカメラ

		ID_NUM,
	};

private:

	CPlayCamera m_play;       // メインとなるカメラ
	CDebugCamera m_debug;     // デバッグモードのカメラ
	CAnotherCamera m_another; // 分身操作時のカメラ
	tagCameraID m_id;         // 今どのカメラを使っているか	

public:

	// コンストラクタ
	CCameraManager();

	//初期化
	void Init();

	// カメラの座標計算
	// @focus :  プレイヤーの座標
	// @rotY  :  プレイヤーの角度
	void Step(VECTOR focus1, float rotY1, VECTOR focus2, float rotY2,CAnother& _Another);

	// カメラの更新
	void Update();

	// カメラのイベント
	void EventCamera(VECTOR focus);

	// カメラのタイプ切り替え
	void ChangeCamera(tagCameraID id) { m_id = id; }

	// カメラのタイプ取得
	tagCameraID GetID() { return m_id; }

	// カメラの座標取得
	VECTOR PGetCamareRot() { return  m_play.GetCamareRot(); }
	VECTOR AGetCamareRot() { return  m_another.GetCamareRot(); }

};

