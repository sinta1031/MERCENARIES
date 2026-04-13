#pragma once

//各キーの割り当て
#define KEY_UP      (0b1)				//上ボタン
#define KEY_DOWN    (0b10)				//下ボタン
#define KEY_LEFT    (0b100)				//左ボタン
#define KEY_RIGHT   (0b10000)           //右ボタン
#define KEY_UP2     (0b10000000000)	    //上ボタン
#define KEY_DOWN2   (0b1000000000)		//下ボタン
#define KEY_LEFT2   (0b100000000)		//左ボタン
#define KEY_RIGHT2  (0b10000000)        //右ボタン
#define KEY_SKILL   (0b100000)	 		//スキルボタン
#define KEY_ZSKILL  (0b1000000)		    //技ボタン
#define KEY_COMMAND (0b1000)			//コマンド選択ボタン
#define KEY_V       (0b100000000000)    //Vボタン
#define KEY_B       (0b1000000000000)   //Bボタン
#define KEY_SPACE   (0b10000000000000)  //SPACEボタン


typedef struct
{
	unsigned int m_nuwkey;      //現在のボタン情報
	unsigned int m_Prevker;     //フレーム前のボタン情報

}INPUT_DATA;
// 
class Input {

public:

	//キー入力情報に必要なデータをまとめた構造体
	

	//キー入力用にグローバルへ変数を作成
	//キー入力情報の初期化
	static void InitInput();

	//キー入力情報を更新
	static void UpdateInput();

	//キーを押したか(通常判定)
	static bool IsInputRep(unsigned int key);

	//キーを押したか(トリガー判定)
	static bool IsInputTrg(unsigned int key);

};

