#pragma once

class FPS {

public:

		float m_frameRate;     //今のフレームレートを保存
		int m_nowTime;         //現在時間
		int m_prevTime;	       //ひとつ前の時間
		int m_prevDrawTime;    //ひとつ前の描画したPC時間
		int m_count;           //カウント用

	bool IsNextFrame();

	void IniFps();

	void StepFps();

	void PrintFps(void);

};