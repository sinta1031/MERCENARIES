#include "stairs.h"

static const char STAIRS_MODEL_PATH[] =
"data/field/gimmick/0.tutorialstage/stairs/stairs.mv1";

// コンストラクタ・デストラクタ
Cstairs::Cstairs()
{
	Init();
}

Cstairs::~Cstairs()
{
	Exit();
}

//初期化
void Cstairs::Init()
{
	//階段
	m_stairshndl = -1;
	m_stairsScale = { 0.1f,0.1f,0.1f };
	m_stairsPos = { -65.0f,0.0f,0.0f };
}

//ロード
void Cstairs::Load()
{
	if (m_stairshndl == -1)
	{
		m_stairshndl = MV1LoadModel(STAIRS_MODEL_PATH);
	}
}

//更新処理
void Cstairs::Step(bool flag)
{
	//スイッチが押されたら階段の仕掛けが動く
	if (flag == true)
	{
		StairsMechanism();
	}
	else if (m_stairsPos.y > 0.0f)
	{
		m_stairsPos.y--;
	}
}

//フィールドのアップデート
void Cstairs::Update()
{
	MV1SetPosition(m_stairshndl, m_stairsPos);
	MV1SetScale(m_stairshndl, m_stairsScale);
	MV1SetupCollInfo(m_stairshndl);
}

//描画
void Cstairs::Draw()
{
	MV1DrawModel(m_stairshndl);
}

//破棄
void Cstairs::Exit()
{
	if (m_stairshndl != -1)
	{
		MV1DeleteModel(m_stairshndl);
		m_stairshndl = -1;
	}
}

//階段の仕掛け起動
void Cstairs::StairsMechanism()
{
	if (m_stairsPos.y <= 60.0f)
	{
		m_stairsPos.y += 0.1f;
	}
}

// 階段位置情報取得
VECTOR Cstairs::GetStairsPos()
{
	return m_stairsPos;
}

// 当たり判定
// @center  :  当たり判定する相手の座標
// @radius　:  球の半径
// @return  :  押し戻すべき距離と方向
VECTOR Cstairs::stairsHitCheck(VECTOR center, float radius)
{
	//押し戻し距離を呼び戻し元に伝えるために使用
	VECTOR result = { 0.0f };
	MV1_COLL_RESULT_POLY_DIM col;

	//当たり判定を行い、その結果を構造体に格納
	col = MV1CollCheck_Sphere(m_stairshndl, -1, center, radius);

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