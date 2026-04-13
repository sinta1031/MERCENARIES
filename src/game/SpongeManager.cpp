#include "SpongeManager.h"
#include "math.h"
#include <DxLib.h>

Csponge CSpongeManager::c_S[SPONGE_MAX];

static const char SPONGE_MODEL_PATH[] =
"data/field/gimmick/1.stage/Sponge/Sponge.x";

//---------------------------
// コンストラクタ
//---------------------------
CSpongeManager::CSpongeManager()
{
	Init();
}

//----------------------------
// 初期化
//----------------------------
void CSpongeManager::Init()
{
	// それぞれのスポンジを初期化
	for (int i = 0; i < SPONGE_MAX; i++)
	{
		c_S[i].Init();
	}
}

//----------------
//  ロード
//----------------
void CSpongeManager::Load(int _hndl)
{
	// モデルのオリジナルデータをロード
	int Hndl = MV1LoadModel(SPONGE_MODEL_PATH);
	int FrameIndex = 31;

	for (int i = 0; i < SPONGE_MAX; i++)
	{
		c_S[i].Load(Hndl);

		c_S[i].FrameIndexPos(_hndl, FrameIndex);
		FrameIndex = FrameIndex + 3;
	}
}

//----------------------------
// メイン処理
//----------------------------
void CSpongeManager::Step()
{
	// それぞれのスポンジ
	for (int i = 0; i < SPONGE_MAX; i++)
	{
		c_S[i].Step();
	}
}

//----------------
// 終了処理
//----------------
void CSpongeManager::Exit()
{
	// それぞれのスポンジ
	for (int i = 0; i < SPONGE_MAX; i++)
	{
		c_S[i].Exit();
	}
}

//-----------------------
// 更新処理
//-----------------------
void CSpongeManager::Update()
{
	// それぞれのスポンジ
	for (int i = 0; i < SPONGE_MAX; i++)
	{
		c_S[i].Update();
	}
}

//------------------
// 描画処理
//------------------
void CSpongeManager::Draw()
{
	// それぞれのスポンジ
	for (int i = 0; i < SPONGE_MAX; i++)
	{
		c_S[i].Draw();
	}
}

//-----------------------------------------
//プレイヤーとのDXライブラリの当たり判定
//-----------------------------------------
VECTOR CSpongeManager::spongeHitCheck(VECTOR center, float radius)
{
	//戻り値
	VECTOR result = { 0.0f };

	//それぞれの当たり判定
	for (int i = 0; i < SPONGE_MAX; i++)
	{
		result = VAdd(result,c_S[i].spongeHitCheck(center, radius));
	}

	return result;
}