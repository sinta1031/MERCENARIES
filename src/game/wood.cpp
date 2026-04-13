#include "wood.h"

static const VECTOR MAXSIZE = { 2.0f,2.0f,2.0f }; //最大サイズ値
static const VECTOR TONE = { 0.1f,0.1f,0.1f }; //サイズ増減値

static const char WOOD_MODEL_PATH[] =
"data/field/gimmick/1.stage/Wood/tulu.x";

// コンストラクタ・デストラクタ
Cwood::Cwood()
{
	Init();
}

Cwood::~Cwood()
{
	Exit();
}

//初期化
void Cwood::Init()
{
	//木
	m_woodhndl = -1;
	m_woodPos = { 0.0f,0.0f,0.0f };
	m_woodScale = { 0.0f,0.0f,0.0f };
}

//ロード
void Cwood::Load(int _hndl)
{
	if (m_woodhndl == -1)
	{
		m_woodhndl = MV1LoadModel(WOOD_MODEL_PATH);
	}

	m_woodPos = GetFramePos(_hndl, 115);
}

//更新処理
void Cwood::Step(Cbud& _Cbud)
{
	if (_Cbud.IsActive() == false)
	{
		//小さかったら
		if (m_woodScale.x <= MAXSIZE.x ||
			m_woodScale.y <= MAXSIZE.y ||
			m_woodScale.z <= MAXSIZE.z)
		{
			//大きくする
			m_woodScale = VAdd(m_woodScale, TONE);
		}
	}
}

//フィールドのアップデート
void Cwood::Update()
{
	MV1SetPosition(m_woodhndl, m_woodPos);
	MV1SetScale(m_woodhndl, m_woodScale);
	MV1SetupCollInfo(m_woodhndl);
}

//描画
void Cwood::Draw()
{
	MV1DrawModel(m_woodhndl);
}

//破棄
void Cwood::Exit()
{
	if (m_woodhndl != -1)
	{
		MV1DeleteModel(m_woodhndl);
		m_woodhndl = -1;
	}
}

VECTOR Cwood::woodHitCheck(VECTOR center, float radius)
{
	//押し戻し距離を呼び戻し元に伝えるために使用
	VECTOR result = { 0.0f };
	MV1_COLL_RESULT_POLY_DIM col;

	//当たり判定を行い、その結果を構造体に格納
	col = MV1CollCheck_Sphere(m_woodhndl, -1, center, radius);

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