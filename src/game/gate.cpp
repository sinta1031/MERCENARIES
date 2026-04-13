#include "gate.h"

static const char GATE_MODEL_PATH[] =
"data/field/gimmick/1.stage/Gate/Gate.x";


// コンストラクタ・デストラクタ
Cgate::Cgate()
{
	Init();
}

Cgate::~Cgate()
{
	Exit();
}

//初期化
void Cgate::Init()
{
	//ゲート
	m_gatehndl = -1;
	m_gatePos = { 0.0f,0.0f,0.0f };
}

//ロード
void Cgate::Load()
{
	if (m_gatehndl == -1)
	{
		m_gatehndl = MV1LoadModel(GATE_MODEL_PATH);
	}
}

//更新処理
void Cgate::Step()
{

}

//フィールドのアップデート
void Cgate::Update()
{
	MV1SetPosition(m_gatehndl, m_gatePos);
}

//描画
void Cgate::Draw()
{
	MV1DrawModel(m_gatehndl);
}

//破棄
void Cgate::Exit()
{
	if (m_gatehndl != -1)
	{
		MV1DeleteModel(m_gatehndl);
		m_gatehndl = -1;
	}
}