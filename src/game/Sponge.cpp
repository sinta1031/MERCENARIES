#include "Sponge.h"


static const VECTOR MAXSIZE = { 3.0f,3.0f,3.0f }; //最大サイズ値
static const VECTOR TONE = { 0.1f,0.1f,0.1f }; //サイズ増減値
static const VECTOR ONE = { 1.0f,1.0f,1.0f };  //初期サイズ値


// コンストラクタ・デストラクタ
Csponge::Csponge()
{
	Init();
}

Csponge::~Csponge()
{
	Exit();
}

//初期化
void Csponge::Init()
{
	m_tagstage = NORMAL;
	m_spongehndl = -1;
	m_spongePos = { 0.0f,0.0f,0.0f };
	m_spongeScale = { 1.0f,1.0f,1.0f };
	m_spomgehit = false;
	m_spongeradius = 15.0f;
	m_Time = 1000;
}

//ロード
void Csponge::Load(int _hndl)
{
	if (m_spongehndl == -1)
	{
		m_spongehndl = MV1DuplicateModel(_hndl);
	}
}

//更新処理
void Csponge::Step()
{
	switch (m_tagstage)
	{
	case NORMAL:
		//NORMAL状態に大きかったら
		if (m_spongeScale.x >= ONE.x ||
			m_spongeScale.y >= ONE.y ||
			m_spongeScale.z >= ONE.z)
		{
			//小さくする
			m_spongeScale = VSub(m_spongeScale, TONE);
		}
		break;

	case BIG:
		//制限時間の間は大きい状態で
		m_Time--;
		if (m_Time >= 0)
		{
			//BIG状態に小さかったら
			if (m_spongeScale.x <= MAXSIZE.x ||
				m_spongeScale.y <= MAXSIZE.y ||
				m_spongeScale.z <= MAXSIZE.z)
			{
				//大きくする
				m_spongeScale = VAdd(m_spongeScale, TONE);
			}
		}

		//制限時間がなくなったら小さい状態に
		if (m_Time <= 0)
		{
			m_tagstage = NORMAL;
			m_Time = 1000;
		}
		
		break;
	}
}

//フィールドのアップデート
void Csponge::Update()
{
	//ポリゴン情報も配列
	MV1SetPosition(m_spongehndl, m_spongePos);
	MV1SetupCollInfo(m_spongehndl);
	MV1SetScale(m_spongehndl, m_spongeScale);
}

//描画
void Csponge::Draw()
{
	MV1DrawModel(m_spongehndl);
}

//破棄
void Csponge::Exit()
{	
	if (m_spongehndl != -1)
	{
		MV1TerminateCollInfo(m_spongehndl);
		MV1DeleteModel(m_spongehndl);
		m_spongehndl = -1;
	}
}

//座標にフレームの座標を代入
void Csponge::FrameIndexPos(int _hndl, int _frameNum)
{
	m_spongePos = GetFramePos(_hndl, _frameNum);
}

// 当たり判定
	// @center  :  当たり判定する相手の座標
	// @radius　:  球の半径
	// @return  :  押し戻すべき距離と方向
VECTOR Csponge::spongeHitCheck(VECTOR center, float radius)
{
	//押し戻し距離を呼び戻し元に伝えるために使用
	VECTOR result = { 0.0f };

	//当たり判定が格納される構造体
	MV1_COLL_RESULT_POLY_DIM col;

	//当たり判定を行い、その結果を構造体に格納
	col = MV1CollCheck_Sphere(m_spongehndl, -1, center, radius);

	//ヒットしたポリゴンがあれば、フラグをオンに
	if (col.HitNum != 0)
	{
		//当たった時の処理
		// 当たったデータをすべてチェックする
		for (int i = 0; i < col.HitNum; i++)
		{
			//まず中心点から最近点を引き算
			VECTOR v = VSub(center, col.Dim[i].HitPosition);

			//取得したベクトルを三平方の定理で長さに変換
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

//位置情報取得
VECTOR Csponge::GetPos()
{
	return m_spongePos;
}

//当たり判定の半径サイズを取得
float Csponge::GetRadius() 
{
	return m_spongeradius;
}

//サイズタイプ切り替え
void Csponge::ChangeSpongeSize(tagSpongeState id, int _id)
{ 
	m_tagstage = id;
}

//サイズタイプ取得
Csponge::tagSpongeState Csponge::GetID(int id)
{
	return m_tagstage;
}

//当たり判定の座標用
VECTOR Csponge::GetCenter()
{
	// 基本は物体の座標の位置
	VECTOR ret = m_spongePos;
	// 高さだけ足元からの半分あげる
	ret.y += m_spongeradius;

	return ret;
}