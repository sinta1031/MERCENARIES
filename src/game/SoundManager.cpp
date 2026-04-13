#include "SoundManager.h"
#include <DxLib.h>

// staticメンバ関数はここで各作業が必須!!
vector<int> CSoundManager::m_hndl;

// 初期化
void CSoundManager::Init()
{
	// 中身を空にする
	m_hndl.clear();
}

// ロード
void CSoundManager::Load()
{
	const char* filePath[SOUND_NUM] = {
		"data/sound/bgm00.mp3",
		"data/sound/se_plshot.mp3",
		"data/sound/se_explore.mp3",

	};

	for (int i = 0; i < SOUND_NUM; i++)
	{
		int hndl = LoadSoundMem(filePath[i]);
		m_hndl.push_back(hndl);
	}
}

// 廃棄処理
void CSoundManager::Exit()
{
	for (int i = 0; i < m_hndl.size(); i++)
	{
		if (m_hndl[i] != -1)
		{
			DeleteSoundMem(m_hndl[i]);
			m_hndl[i] = -1;
		}
	}
}

// 音楽再生
	//@id : 再生する音楽
	//@type : DX_PLAYTYPE_BACK = 1回再生
	//        DX_PLAYTYPE_LOOP = 繰り返す再生
	//@isStart : true = 最初から再生, false = 途中から
	// return : true = 再生成功, false = 再生終了
bool CSoundManager::Play(tagID id, int type, bool isStart)
{
	int ret = PlaySoundMem(m_hndl[id], type, isStart);
	if (ret == -1)return false;
	else return true;
}

// 音楽停止
void CSoundManager::Stop(tagID id)
{
	StopSoundMem(m_hndl[id]);
}

// 全音楽停止
void CSoundManager::AllStop()
{
	for (int i = 0; i < m_hndl.size(); i++)
	{
		StopSoundMem(m_hndl[i]);
	}
}

// 音楽を再生中か
bool CSoundManager::IsPlay(tagID id)
{
	int result = CheckSoundMem(m_hndl[id]);
	if (result == 1)return true;
	else return false;
}