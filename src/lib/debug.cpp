#include <Dxlib.h>
#include "debug.h"

#define FRAME_RATE (60)								// 1秒あたりのフレーム数
#define FRAME_RATE_MILLI_SECOND (1000/FRAME_RATE)	// 何ミリ秒で1フレームか

void FPS::IniFps()
{
	//基本的に0で初期化
	m_frameRate = 0.0f;
	m_nowTime = 0;
	m_prevTime = m_prevDrawTime = GetNowCount();
	m_count = 0;
}

//----------------------
//  FPS表示回数
//----------------------
void FPS::PrintFps(void)
{
	//まずはカウントを増やす
	m_count++;
	//最新の時間を取得
	m_nowTime = GetNowCount();
	//前回時間を取得してからどのぐらい時間がたったか
	int difTime = m_nowTime - m_prevDrawTime;

	//差が1秒以上あれば計算開始(1秒に1回フレームレートの表示を更新)
	if (difTime >= 1000)
	{
		//ある程度正常に動いていたら、m_countは60になっているはず
		float frameCount = (float)(m_count * 1000);
		//表示するfpsを更新
		m_frameRate = frameCount / difTime;
		//カウントは0に初期化
		m_count = 0;
		//ひとつ前の時間を更新
		m_prevDrawTime = m_nowTime;
	}
	//文字の表示　因数は「横の位置」「縦の位置」「色」「文字」
	SetFontSize(15);
	DrawFormatString(32, 32, GetColor(255, 0, 0), "FPS:%.2lf", m_frameRate);

}

//------------------------------
//  次のフレームに進めていいか
//------------------------------
bool FPS::IsNextFrame()
{
	//最新の時間を取得
	m_nowTime = GetNowCount();
	//前回時間を取得してからどのぐらい時間がたったか
	int difTime = m_nowTime - m_prevTime;

	//差が1秒以上あれば計算開始(1秒に1回フレームレートの表示を更新)
	if (difTime >= FRAME_RATE_MILLI_SECOND)
	{
		return true;
	}
	else return false;
}

//--------------------------
//   FPS更新処理
//--------------------------
void FPS::StepFps()
{
	// ここまで来たら時間を更新
	m_prevTime = m_nowTime;
}