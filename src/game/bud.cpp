#include "bud.h"

static const char BUD_MODEL_PATH[] =
"data/field/gimmick/1.stage/bud/bud.x";

static const VECTOR TONE = { 0.1f,0.1f,0.1f }; //サイズ増減値
static const VECTOR ONE = { 0.0f,0.0f,0.0f };  //最小サイズ値

// コンストラクタ・デストラクタ
Cbud::Cbud()
{
	Init();
}

Cbud::~Cbud()
{
	Exit();
}

//初期化
void Cbud::Init()
{
	m_budhndl = -1;
	m_budPos = { 0.0f,0.0f,0.0f };
	m_budScale = { 1.0f,1.0f,1.0f };
	m_budradius = 15.0f;
	m_budflag = false;
	m_active = true;
}

//ロード
void Cbud::Load(int _hndl)
{
	if (m_budhndl == -1)
	{
		m_budhndl = MV1LoadModel(BUD_MODEL_PATH);
	}

	m_budPos = GetFramePos(_hndl, 115);
}

//更新処理
void Cbud::Step()
{
	//水と触れたとき
	if (m_budflag == true)
	{
		//まだあるなら
		if (m_budScale.x >= ONE.x ||
			m_budScale.y >= ONE.y ||
			m_budScale.z >= ONE.z)
		{
			//小さくする
			m_budScale = VSub(m_budScale, TONE);
		}

		//小さくなりきったら
		if (m_budScale.x <= ONE.x ||
			m_budScale.y <= ONE.y ||
			m_budScale.z <= ONE.z)
		{
			//生存を消す
			m_active = false;
		}
	}
}

//フィールドのアップデート
void Cbud::Update()
{
	MV1SetPosition(m_budhndl, m_budPos);
	MV1SetScale(m_budhndl, m_budScale);
}

//描画
void Cbud::Draw()
{
	if (m_active = true)
	{
		MV1DrawModel(m_budhndl);
	}
}

//破棄
void Cbud::Exit()
{
	if (m_budhndl != -1)
	{
		MV1DeleteModel(m_budhndl);
		m_budhndl = -1;
	}
}

//フラグ管理
void Cbud::HitCalc()
{
	m_budflag = true;
}

//位置情報取得
VECTOR Cbud::GetPos()
{
	return m_budPos;
}

//当たり判定の座標用
VECTOR Cbud::GetCenter()
{
	// 基本は物体の座標の位置
	VECTOR ret = m_budPos;
	// 高さだけ足元からの半分あげる
	ret.y += m_budradius;

	return ret;
}

//当たり判定の半径サイズを取得
float Cbud::GetRadius()
{
	return m_budradius;
}