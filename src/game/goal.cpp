#include "goal.h"

static const char GOAL_MODEL_PATH[] =
"data/field/goal/goal.x";

// コンストラクタ・デストラクタ
Cgoal::Cgoal()
{
	Init();
}

Cgoal::~Cgoal()
{
	Exit();
}

//初期化
void Cgoal::Init()
{
	//ゴール
	m_goalhndl = -1;
	m_goalradius = 3.0f;
	m_goalScale = { 0.1f,0.1f,0.1f };
	m_goalPos = { 70.0f,10.0f,-70.0f };
}

//ロード
void Cgoal::Load(int _stageNum, int _hndl)
{
	if (m_goalhndl == -1)
	{
		m_goalhndl = MV1LoadModel(GOAL_MODEL_PATH);
	}

	switch (_stageNum)
	{
	case 0:
		m_goalPos = m_goalPos;
		break;

	case 1:
		m_goalPos = GetFramePos(_hndl, 118);
		break;
	}
}

//更新処理
void Cgoal::Step()
{

}

//フィールドのアップデート
void Cgoal::Update()
{
	MV1SetPosition(m_goalhndl, m_goalPos);
	MV1SetScale(m_goalhndl, m_goalScale);
}

//描画
void Cgoal::Draw()
{
	MV1DrawModel(m_goalhndl);
}

//破棄
void Cgoal::Exit()
{
	if (m_goalhndl != -1)
	{
		MV1DeleteModel(m_goalhndl);
		m_goalhndl = -1;
	}
}

// ゴール位置情報取得
VECTOR Cgoal::GetgoalPos()
{
	return m_goalPos;
}

// 当たり判定の座標用
VECTOR Cgoal::GetgoalCenter()
{
	// 基本は物体の座標の位置
	VECTOR ret = m_goalPos;
	// 高さだけ足元からの半分あげる
	ret.y += m_goalradius;

	return ret;
}

