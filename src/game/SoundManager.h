#pragma once
#include <DxLib.h>
#include <vector>

using namespace std;

class CSoundManager {
public:

	enum tagID{
		TITLE_BGM,			// タイトルとステージ選択のBGM
		PUSH_SE,			// 決定音
		KNIGHT_THEME,		// 騎士のBGM
		KNIGHT_MAYHEM,		// 騎士：メイヘムモード
		GUNMAN_THEME,		// ガンマンのBGM
		GUNMAN_MAYHEM,		// ガンマン：メイヘムモード
		FIGHTER_THEME,		// ファイターのBGM
		FIGHTER_MAYHEM,		// ファイター：メイヘムモード
		MILITARY_THEME,		// ミリタリーのBGM
		MILITARY_MAYHEM,	// ミリタリー：メイヘムモード
		MINI_BOSS_THEME,	// ミニボスのBGM
		MINI_BOSS_MAYHEM,	// ミニボス：メイヘムモード

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