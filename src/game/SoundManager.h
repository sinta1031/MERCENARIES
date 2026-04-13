#pragma once
#include <DxLib.h>
#include <vector>

using namespace std;

class CSoundManager {
public:

	enum tagID{
		BGM_GAME,      // BGM ゲーム本編
		SE_PLSHOT,     // SE プレイヤーの弾
		SE_EXPLOSION,  // SE 爆発音
		VOICE_ENEMY,   // VOICE 敵の音声

		SOUND_NUM,
	};

private:

	static vector<int>m_hndl; // 音楽ハンドル

public:

	// 初期化
	static void Init();

	// ロード
	static void Load();

	// 廃棄処理
	static void Exit();

	// 音楽再生
	//@id : 再生する音楽
	//@type : DX_PLAYTYPE_BACK = 1回再生
	//        DX_PLAYTYPE_LOOP = 繰り返す再生
	//@isStart : true = 最初から再生, false = 途中から
	// return : true = 再生成功, false = 再生終了
	static bool Play(tagID id, int type = DX_PLAYTYPE_BACK, bool isStart = true);

	// 音楽停止
	static void Stop(tagID id);

	// 全音楽停止
	static void AllStop();

	// 音楽を再生中か
	static bool IsPlay(tagID id);
};