#include "oli.h"

static const char OLI_MODEL_PATH[] =
"data/field/gimmick/allstage/oli/oli.x";


// コンストラクタ・デストラクタ
Coli::Coli()
{
	Init();
}

Coli::~Coli()
{
	Exit();
}

//初期化
void Coli::Init()
{
	//檻
	m_olihndl = -1;
	m_oliPos = { 55.0f,0.5f,60.0 };
}

//ロード
void Coli::Load()
{
	if (m_olihndl == -1)
	{
		m_olihndl = MV1LoadModel(OLI_MODEL_PATH);
	}
}

//更新処理
void Coli::Step()
{

}

//フィールドのアップデート
void Coli::Update()
{
	MV1SetPosition(m_olihndl, m_oliPos);
	MV1SetupCollInfo(m_olihndl);
}

//描画
void Coli::Draw()
{
	MV1DrawModel(m_olihndl);
}

//破棄
void Coli::Exit()
{
	if (m_olihndl != -1)
	{
		MV1TerminateCollInfo(m_olihndl);
		MV1DeleteModel(m_olihndl);
		m_olihndl = -1;
	}
}

VECTOR Coli::oliHitCheck(VECTOR center, float radius)
{
	//押し戻し距離を呼び戻し元に伝えるために使用
	VECTOR result = { 0.0f };
	MV1_COLL_RESULT_POLY_DIM col;

	//当たり判定を行い、その結果を構造体に格納
	col = MV1CollCheck_Sphere(m_olihndl, -1, center, radius);

	//ヒットしたポリゴンがあれば、フラグをオンに
	// ポリゴンと当たった
	if (col.HitNum != 0)
	{
		//当たった時の処理
		// 当たったデータをすべてチェックする
		for (int i = 0; i < col.HitNum; i++)
		{
			//まず中心点から最近点を引き算
			VECTOR v = VSub(center, col.Dim[i].HitPosition);

			//取得したベクトルを三平方の低利で長さに変換
			float len = VSize(v);

			//実際にめり込んだ距離を計算
			len = radius - len;

			//法線をめり込んだ距離分掛け算する
			v = VScale(col.Dim[i].Normal, len);

			//計算結果を合算していく
			result = VAdd(result, v);
		}
	}
	//終了前にコリジョンデータを破棄
	MV1CollResultPolyDimTerminate(col);

	return result;
}