#include "water.h"

static const char WATER_MODEL_PATH[] =
"data/field/gimmick/1.stage/water source/water source.x";

// コンストラクタ・デストラクタ
Cwater::Cwater()
{
	Init();
}

Cwater::~Cwater()
{
	Exit();
}

//初期化
void Cwater::Init()
{
	//水場
	for (int i = 0; i < WATER_MAX; i++) {
		m_waterhndl[i] = -1;
		m_waterPos[i] = { 0.0f,0.0f,0.0f };
	}
}

//ロード
void Cwater::Load(int _hndl)
{
	for (int i = 0; i < WATER_MAX; i++) {

		int hndl = MV1LoadModel(WATER_MODEL_PATH);

		m_waterhndl[i] = MV1DuplicateModel(hndl);

		MV1DeleteModel(hndl);

		if (i == 0)
		{
			m_waterPos[0] = GetFramePos(_hndl, 1);
		}
		if (i == 1)
		{
			m_waterPos[1] = GetFramePos(_hndl, 4);
		}
		if (i == 2)
		{
			m_waterPos[2] = GetFramePos(_hndl, 7);
		}
		if (i == 3)
		{
			m_waterPos[3] = GetFramePos(_hndl, 124);
		}
	}
}

//更新処理
void Cwater::Step()
{

}

//フィールドのアップデート
void Cwater::Update()
{
	//三つの水場を配列で
	for (int i = 0; i < WATER_MAX; i++)
	{
		//ポリゴン情報も配列
		MV1SetPosition(m_waterhndl[i], m_waterPos[i]);
		MV1SetupCollInfo(m_waterhndl[i]);
	}
}

//描画
void Cwater::Draw()
{
	for (int i = 0; i < WATER_MAX; i++)
	{
		MV1DrawModel(m_waterhndl[i]);
	}
}

//破棄
void Cwater::Exit()
{
	for (int i = 0; i < WATER_MAX; i++) {
		if (m_waterhndl[i] != -1)
		{
			MV1TerminateCollInfo(m_waterhndl[i]);
			MV1DeleteModel(m_waterhndl[i]);
			m_waterhndl[i] = -1;
		}
	}
}

bool Cwater::waterHitCheck(VECTOR center, float redius)
{
	//水に触れるとフラグをtureにする
	bool result = false;
	MV1_COLL_RESULT_POLY_DIM col;

	//個数分の当たり判定を行い、その結果を構造体に格納
	for (int i = 0; i < WATER_MAX; i++)
	{
		col = MV1CollCheck_Sphere(m_waterhndl[i], -1, center, redius);

		//ヒットしたポリゴンがあれば、フラグをオンに
		// ポリゴンと当たった
		if (col.HitNum != 0)
		{
			//リザルトをtrueにする
			result = true;
		}
	}

	//終了前にコリジョンデータを破棄
	MV1CollResultPolyDimTerminate(col);

	return result;
}
