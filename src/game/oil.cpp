#include "oil.h"

#define GRAVITY				( 0.05f ) //重力

static const VECTOR OIL_COMIT = { 1.0f,0.0f,0.0f }; //オイルX座標増減地

static const char OILPOOL_MODEL_PATH[] =
"data/field/gimmick/1.stage/Oil/Oil Pool.x";

static const char OIL_MODEL_PATH[] =
"data/field/gimmick/1.stage/Oil/Oil.x";

// コンストラクタ・デストラクタ
Coil::Coil()
{
	Init();
}

Coil::~Coil ()
{
	Exit();
}

//初期化
void Coil::Init()
{
	//オイル
	for (int i = 0; i < OIL_MAX; i++)
	{
		m_oilhndl[i] = -1;
		m_oilPos[i] = { 0.0f,0.0f,0.0f };
	}
	m_oilpoolhndl = -1;
	m_oilpoolPos = { 0.0f,0.0f,0.0f };
	m_oilgravity = 0.0f;
	m_isHitFlag = false;
}

//ロード
void Coil::Load(int _hndl)
{
	if (m_oilpoolhndl == -1)
	{
		m_oilpoolhndl = MV1LoadModel(OILPOOL_MODEL_PATH);
	}

	for (int i = 0; i < OIL_MAX; i++)
	{
		int hndl = MV1LoadModel(OIL_MODEL_PATH);

		m_oilhndl[i] = MV1DuplicateModel(hndl);

		MV1DeleteModel(hndl);

		//まずは位置取得
		if (i == 0)
		{
			m_oilPos[0] = GetFramePos(_hndl, 11);
		}
		if (i == 1)
		{
			m_oilPos[1] = GetFramePos(_hndl, 14);
		}
		if (i == 2)
		{
			m_oilPos[2] = GetFramePos(_hndl, 17);
		}
		if (i == 3)
		{
			m_oilPos[3] = GetFramePos(_hndl, 20);
		}
	}
}

//引数にフィールドのハンドルを入れる
//更新処理
void Coil::Step(int _hndl)
{
	//オイルプールにボーンの位置取得
	m_oilpoolPos = GetFramePos(_hndl, 22);

	//四つの排気口からでてくるイメージ
	//ででいるように見せる
	m_oilPos[0] = VSub(m_oilPos[0], OIL_COMIT);
	m_oilPos[1] = VSub(m_oilPos[1], OIL_COMIT);
	m_oilPos[2] = VAdd(m_oilPos[2], OIL_COMIT);
	m_oilPos[3] = VAdd(m_oilPos[3], OIL_COMIT);

	//オイルの重力更新地
	m_oilgravity -= GRAVITY;
	m_oilPos[0].y += m_oilgravity;
	m_oilPos[1].y += m_oilgravity;
	m_oilPos[2].y += m_oilgravity;
	m_oilPos[3].y += m_oilgravity;

	//ある程度下へ行ったらまた戻す
	for (int i = 0; i < OIL_MAX; i++)
	{
		float length = 100.0f;
		if (m_oilPos[i].y < -length)
		{
			m_oilPos[i].y += length;
			m_oilgravity = 0.0f;

			if (i == 0)
			{
				m_oilPos[0] = GetFramePos(_hndl, 11);
			}
			if (i == 1)
			{
				m_oilPos[1] = GetFramePos(_hndl, 14);
			}
			if (i == 2)
			{
				m_oilPos[2] = GetFramePos(_hndl, 17);
			}
			if (i == 3)
			{
				m_oilPos[3] = GetFramePos(_hndl, 20);
			}
		}
	}
}

//フィールドのアップデート
void Coil::Update()
{
	MV1SetPosition(m_oilpoolhndl, m_oilpoolPos);

	for (int i = 0; i < OIL_MAX; i++)
	{
		MV1SetPosition(m_oilhndl[i], m_oilPos[i]);
	}

	MV1SetupCollInfo(m_oilpoolhndl);
}

//描画
void Coil::Draw()
{
	MV1DrawModel(m_oilpoolhndl);

	for (int i = 0; i < OIL_MAX; i++)
	{
		MV1DrawModel(m_oilhndl[i]);
	}

	/*if (m_isHitFlag == true)
	{
		DrawFormatString(32, 60, GetColor(255, 255, 255), "Hit!");
	}*/
}

//破棄
void Coil::Exit()
{
	if (m_oilpoolhndl != -1)
	{
		MV1DeleteModel(m_oilpoolhndl);
		m_oilpoolhndl = -1;
	}

	for (int i = 0; i < OIL_MAX; i++) {
		if (m_oilhndl[i] != -1)
		{
			MV1DeleteModel(m_oilhndl[i]);
			m_oilhndl[i] = -1;
		}
	}
}

// 当たり判定
// @center  :  当たり判定する相手の座標
// @radius　:  球の半径
// @return  :  押し戻すべき距離と方向
bool Coil::oilpoolHitCheck(VECTOR center, float radius)
{
	//水に触れるとフラグをtureにする
	bool result = false;
	m_isHitFlag = false;
	MV1_COLL_RESULT_POLY_DIM col;

	col = MV1CollCheck_Sphere(m_oilpoolhndl, -1, center, radius);

	//ヒットしたポリゴンがあれば、フラグをオンに
	// ポリゴンと当たった
	if (col.HitNum != 0)
	{
		m_isHitFlag = true;
		//リザルトをtrueにする
		result = true;
		
	}
	//終了前にコリジョンデータを破棄
	MV1CollResultPolyDimTerminate(col);

	return result;
}

bool Coil::oilHitCheck(VECTOR center, float radius)
{
	//水に触れるとフラグをtureにする
	bool result = false;
	m_isHitFlag = false;
	MV1_COLL_RESULT_POLY_DIM col;

	//個数分の当たり判定を行い、その結果を構造体に格納
	for (int i = 0; i < OIL_MAX; i++)
	{
		col = MV1CollCheck_Sphere(m_oilhndl[i], -1, center, radius);

		//ヒットしたポリゴンがあれば、フラグをオンに
		// ポリゴンと当たった
		if (col.HitNum != 0)
		{
			m_isHitFlag = true;
			//リザルトをtrueにする
			result = true;
		}
	}

	//終了前にコリジョンデータを破棄
	MV1CollResultPolyDimTerminate(col);

	return result;
}