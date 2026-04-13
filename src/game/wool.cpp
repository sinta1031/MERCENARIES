#include "wool.h"

static const char WOOL_MODEL_PATH[] =
"data/field/gimmick/1.stage/wool/wool.x";

static const char WOOLCAGE_MODEL_PATH[] =
"data/field/gimmick/1.stage/wool/wool Cage.x";

#define JUMPPOWER           ( 10.0f )	//ジャンプパワー
#define GRAVITY				( 0.2f )	//重力
#define SPEED				( 10.0f )	//スピード

// コンストラクタ・デストラクタ
Cwool::Cwool()
{
	Init();
}

Cwool::~Cwool()
{
	Exit();
}

//初期化
void Cwool::Init()
{
	m_woolhndl = -1;
	m_woolgravity = 0.0f;
	m_woolflg = false;
	m_woolHitflg = false;
	m_woolradius = 60.0f;
	m_woolPos = { 0.0f,0.0f,0.0f };
	m_woolRot = { 0.0f,0.0f,0.0f };

	m_woolcagehndl = -1;
	m_woolcagePos = { 0.0f,0.0f,0.0f };
}

//ロード
void Cwool::Load(int hndl)
{
	if (m_woolhndl == -1)
	{
		m_woolhndl = MV1LoadModel(WOOL_MODEL_PATH);
	}

	if (m_woolcagehndl == -1)
	{
		m_woolcagehndl = MV1LoadModel(WOOLCAGE_MODEL_PATH);
	}

	m_woolPos = GetFramePos(hndl, 28);
}

//更新処理
void Cwool::Step()
{
	if (m_woolHitflg == true)
	{
		Knockback();
	}

	if (m_woolPos.y < -2000)
	{
		Exit();
	}
}

//ぶっ飛ぶ処理
void Cwool::Knockback()
{
	//斜め上に飛ばす処理
	m_woolPos.z -= SPEED;
	m_woolRot = VAdd(m_woolRot, VGet(0.3f, 0.3f, 0.3f));
	
	if (m_woolflg == false)
	{
		m_woolgravity = JUMPPOWER;
		m_woolflg = true;
	}
	
	m_woolgravity -= GRAVITY;

	// 重力値更新 
	m_woolPos.y += m_woolgravity;
}

//フィールドのアップデート
void Cwool::Update()
{
	MV1SetPosition(m_woolhndl, m_woolPos);
	MV1SetRotationXYZ(m_woolhndl, m_woolRot);
	MV1SetupCollInfo(m_woolhndl);

	MV1SetPosition(m_woolcagehndl, m_woolcagePos);
	MV1SetupCollInfo(m_woolcagehndl);

	m_woolcagePos = GetFramePos(m_woolhndl, 4);
}

//描画
void Cwool::Draw()
{
	MV1DrawModel(m_woolhndl);
	MV1DrawModel(m_woolcagehndl);

	//当たり判定を目視できるように
	DrawSphere3D(GetCenter(), m_woolradius,
		16, GetColor(255, 0, 0),
		GetColor(255, 0, 0), FALSE);
}

//破棄
void Cwool::Exit()
{
	if (m_woolhndl != -1)
	{
		MV1TerminateCollInfo(m_woolhndl);
		MV1DeleteModel(m_woolhndl);
		m_woolhndl = -1;
	}

	if (m_woolcagehndl != -1)
	{
		MV1TerminateCollInfo(m_woolcagehndl);
		MV1DeleteModel(m_woolcagehndl);
		m_woolcagehndl = -1;
	}
}

// 当たり判定
	// @center  :  当たり判定する相手の座標
	// @radius　:  球の半径
	// @return  :  押し戻すべき距離と方向
VECTOR Cwool::woolHitCheck(VECTOR center, float redius)
{
	//押し戻し距離を呼び戻し元に伝えるために使用
	VECTOR result = { 0.0f };
	MV1_COLL_RESULT_POLY_DIM col;

	//当たり判定を行い、その結果を構造体に格納
	col = MV1CollCheck_Sphere(m_woolhndl, -1, center, redius);
	
	//壁がぶっ飛んで無かったら
	if (m_woolHitflg == false)
	{
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
				len = redius - len;

				//法線をめり込んだ距離分掛け算する
				v = VScale(col.Dim[i].Normal, len);

				//計算結果を合算していく
				result = VAdd(result, v);
			}
		}
	}
	
	//終了前にコリジョンデータを破棄
	MV1CollResultPolyDimTerminate(col);

	return result;
}

VECTOR Cwool::woolcageHitCheck(VECTOR center, float redius)
{
	//押し戻し距離を呼び戻し元に伝えるために使用
	VECTOR result = { 0.0f };
	MV1_COLL_RESULT_POLY_DIM col;

	//当たり判定を行い、その結果を構造体に格納
	col = MV1CollCheck_Sphere(m_woolcagehndl, -1, center, redius);

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
			len = redius - len;

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

// 当たり判定の座標用
VECTOR Cwool::GetCenter()
{
	// 基本は物体の座標の位置
	VECTOR ret = GetFramePos(m_woolhndl,1);
	// 高さだけ足元から弾の半分あげる
	ret.y += m_woolradius;

	return ret;
}