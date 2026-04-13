#include "ShotManager.h"
#include "math.h"
#include <DxLib.h>

CShot CShotManager::c_S[PL_SHOT_NUM];

static const int SHOT_NAM_MAX = 20;
static const float SHOT_SPEED = 3.0f;

static const char SHOT_MODEL_PATH[] =
"data/model/Shot/Shot.x";

//---------------------------
// コンストラクタ
//---------------------------
CShotManager::CShotManager()
{
	Init();
}

//----------------------------
// 初期化
//----------------------------
void CShotManager::Init()
{
	// それぞれの弾を初期化
	for (int i = 0; i < PL_SHOT_NUM; i++)
	{
		c_S[i].Init();
	}
}

//----------------
//  ロード
//----------------
void CShotManager::Load()
{
	// モデルのオリジナルデータをロード
	int Hndl = MV1LoadModel(SHOT_MODEL_PATH);

	for (int i = 0; i < PL_SHOT_NUM; i++)
	{
		c_S[i].Load(Hndl);
	}
}

//----------------------------
// メイン処理
//----------------------------
void CShotManager::Step()
{
	// それぞれの弾
	for (int i = 0; i < PL_SHOT_NUM; i++)
	{
		c_S[i].Step();
	}
}

//----------------
// 終了処理
//----------------
void CShotManager::Exit()
{
	// それぞれの弾
	for (int i = 0; i < PL_SHOT_NUM; i++)
	{
		c_S[i].Exit();
	}
}

//-----------------------
// 更新処理
//-----------------------
void CShotManager::Update()
{
	// それぞれの弾
	for (int i = 0; i < PL_SHOT_NUM; i++)
	{
		c_S[i].Update();
	}
}

//------------------
// 描画処理
//------------------
void CShotManager::Draw()
{
	// それぞれの弾
	for (int i = 0; i < PL_SHOT_NUM; i++)
	{
		c_S[i].Draw();
	}
}

//弾をリクエスト
void CShotManager::Request(const VECTOR& pos)
{
	//一時的に使う変数
	VECTOR ShotSpeed = VGet(0, 0, 0);
	VECTOR m_rad = VGet(0, 0, 0);
	int ShotNum = 0;//弾を撃った回数

	// それぞれの弾
	for (int i = 0; i < PL_SHOT_NUM; i++)
	{
		//弾の角度を算出
		m_rad.x = (((ShotNum)*DX_PI_F / SHOT_NAM_MAX / 2) - DX_PI_F);

		//移動速度を三角関数で計算
		ShotSpeed.x = (cosf((c_S[i].GetRadius() + (ShotNum * 7 / static_cast<float>((SHOT_NAM_MAX)))) - DX_PI_F)) * SHOT_SPEED;
		ShotSpeed.y = 0;//((ShotNum / static_cast<float>((SHOT_NAM_MAX / HALF))) - 1) * SHOT_SPEED;
		ShotSpeed.z = (sinf((c_S[i].GetRadius() + (ShotNum * 7 / static_cast<float>((SHOT_NAM_MAX)))) - DX_PI_F)) * SHOT_SPEED;

		// 弾を発射
		if (c_S[i].Request(pos, ShotSpeed))
		{
			ShotNum++;

			//出したい分だけ出したら終了
			if (ShotNum > SHOT_NAM_MAX)break;
		}
		/*else {
			continue;
		}*/
	}
}