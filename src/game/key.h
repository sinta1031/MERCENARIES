#pragma once
#include <DxLib.h>

class Ckey {
private:

	int m_keyhndl;                  //鍵ハンドル
	float m_keyradius;              //鍵半径取得
	bool m_KeyisActive;             //鍵の生存フラグ
	VECTOR m_keyScale;              //鍵のスケール
	VECTOR m_keyPos;                //鍵の座標
	VECTOR m_kRot;                  //鍵の回転速度

public:

	// コンストラクタ・デストラクタ
	Ckey();
	~Ckey();

	//初期化
	void Init();

	//ロード
	void Load(int _stageNum,int _hndl);

	//更新処理
	void Step();

	//フィールドのアップデート
	void Update();

	//描画
	void Draw();

	//破棄
	void Exit();

	// 鍵位置情報取得
	VECTOR GetkeyPos();

	// 鍵当たり判定の座標用
	VECTOR GetkeyCenter();

	// 鍵の当たり判定の半径サイズを取得
	float GetKeyRadius() { return m_keyradius; }

	//鍵の生存情報取得
	bool KeyIsActive() { return m_KeyisActive; }
	void SetKeyActive(bool active) { m_KeyisActive = active; }

	//指定したフレームの座標を渡す
	VECTOR GetFramePos(int _hndl, int _frameNum) { return MV1GetFramePosition(_hndl, _frameNum); }
};