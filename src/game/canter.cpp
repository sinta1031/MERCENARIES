#include "canter.h"

static const VECTOR ZERO = { 0.0f,0.0f,0.0f };
static const VECTOR INITPOS = { 0.0f,30.0f,0.0f };

static const char CANTER_MODEL_PATH[] =
"data/model/player/canter/canter.x";

// コンストラクタ・デストラクタ
Ccanter::Ccanter()
{
	Init();
}

Ccanter::~Ccanter()
{
	Exit();
}

//初期化
void Ccanter::Init()
{
	m_cPos = INITPOS;
	m_cRot = ZERO;
	m_Hndl = -1;

}

//ロード
void Ccanter::Load()
{
	if (m_Hndl == -1)
	{
		m_Hndl = MV1LoadModel(CANTER_MODEL_PATH);
	}
}

//描画
void Ccanter::Draw()
{
	MV1DrawModel(m_Hndl);
}

//破棄
void Ccanter::Exit()
{
	if (m_Hndl != -1)
	{
		MV1DeleteModel(m_Hndl);
		m_Hndl = -1;
	}
}

//行動処理
void Ccanter::Step(int hndl)
{
	// 計算した速度を座標計算に足し算する(カンテラ)
	m_cPos = GetFramePos(hndl, 13);
}

// プレイヤーの更新
void Ccanter::Update()
{
	MV1SetPosition(m_Hndl, m_cPos);
	MV1SetRotationXYZ(m_Hndl, m_cRot);
	MV1SetScale(m_Hndl, VGet(3.0f, 3.0f, 3.0f));
}