#include "switch.h"

static const char SWITCH_MODEL_PATH[] =
"data/field/gimmick/allstage/switch/switch.x";

static const char SWITCHPUSH_MODEL_PATH[] =
"data/field/gimmick/allstage/switch/switch1.x";

// コンストラクタ・デストラクタ
Cswitch::Cswitch()
{
	Init();
}

Cswitch::~Cswitch()
{
	Exit();
}

//初期化
void Cswitch::Init()
{
	//スイッチ
	m_switchhndl = -1;
	m_switchhndl1 = -1;
	m_switchradius = 5.0f;
	m_switchHitFlag = false;
	m_switchScale = { 0.1f,0.1f,0.1f };
	m_switchPos = { 70.0f,7.0f,55.0f };
}

//ロード
void Cswitch::Load()
{
	if (m_switchhndl == -1)
	{
		m_switchhndl = MV1LoadModel(SWITCH_MODEL_PATH);
	}

	if (m_switchhndl1 == -1)
	{
		m_switchhndl1 = MV1LoadModel(SWITCHPUSH_MODEL_PATH);
	}
}

//更新処理
void Cswitch::Step()
{

}

//フィールドのアップデート
void Cswitch::Update()
{
	MV1SetPosition(m_switchhndl, m_switchPos);
	MV1SetPosition(m_switchhndl1, m_switchPos);
	MV1SetScale(m_switchhndl, m_switchScale);
	MV1SetupCollInfo(m_switchhndl);
}

//描画
void Cswitch::Draw()
{
	//フラグがtrueならスイッチが押されている状態に
	if (m_switchHitFlag == true)
	{
		MV1DrawModel(m_switchhndl1);
	}
	else
	{
		MV1DrawModel(m_switchhndl);
	}
}

//破棄
void Cswitch::Exit()
{
	if (m_switchhndl != -1)
	{
		MV1DeleteModel(m_switchhndl);
		m_switchhndl = -1;
	}

	if (m_switchhndl1 != -1)
	{
		MV1DeleteModel(m_switchhndl1);
		m_switchhndl1 = -1;
	}
}

VECTOR Cswitch::switchHitCheck(VECTOR center, float radius)
{
	//押し戻し距離を呼び戻し元に伝えるために使用
	VECTOR result = { 0.0f };
	MV1_COLL_RESULT_POLY_DIM col;

	//一旦当たっていない状態にしておく
	m_switchHitFlag = false;

	//当たり判定を行い、その結果を構造体に格納
	col = MV1CollCheck_Sphere(m_switchhndl, -1, center, radius);

	//ヒットしたポリゴンがあれば、フラグをオンに
	// ポリゴンと当たった
	if (col.HitNum != 0)
	{
		//当たった時の処理
		//仕掛けのフラグをオンにする
		m_switchHitFlag = true;

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

			//当たり判定を少し埋める
			v = VScale(v, 0.1);

			//計算結果を合算していく
			result = VAdd(result, v);
		}
	}
	//終了前にコリジョンデータを破棄
	MV1CollResultPolyDimTerminate(col);

	return result;
}
