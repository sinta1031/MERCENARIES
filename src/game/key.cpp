#include "key.h"

static const char KEY_MODEL_PATH[] =
"data/field/gimmick/allstage/key/Key.mv1";

// コンストラクタ・デストラクタ
Ckey::Ckey()
{
	Init();
}

Ckey::~Ckey()
{
	Exit();
}

//初期化
void Ckey::Init()
{
	//鍵
	m_keyhndl = -1;
	m_keyradius = 3.0f;
	m_KeyisActive = true;
	m_keyScale = { 0.1f,0.1f,0.1f };
	m_keyPos = { -70.0f,10.0f,-60.0f };
	m_kRot = { 0.0f,0.0f,0.0f };
}

//ロード
void Ckey::Load(int _stageNum, int _hndl)
{
	if (m_keyhndl == -1)
	{
		m_keyhndl = MV1LoadModel(KEY_MODEL_PATH);
	}

	switch (_stageNum)
	{
	case 0:
		m_keyPos = m_keyPos;
		break;

	case 1:
		m_keyPos = GetFramePos(_hndl, 122);
		break;
	}
}

//更新処理
void Ckey::Step()
{
	m_kRot.y += 0.1f;
}

//フィールドのアップデート
void Ckey::Update()
{
	MV1SetPosition(m_keyhndl, m_keyPos);
	MV1SetScale(m_keyhndl, m_keyScale);		
	MV1SetRotationXYZ(m_keyhndl, m_kRot);	//鍵の回転情報
}

//描画
void Ckey::Draw()
{
	//アクティブがtrueなら表示
	if (m_KeyisActive == true)
	{
		MV1DrawModel(m_keyhndl);
	}
}

//破棄
void Ckey::Exit()
{
	if (m_keyhndl != -1)
	{
		MV1DeleteModel(m_keyhndl);
		m_keyhndl = -1;
	}
}

// 鍵位置情報取得
VECTOR Ckey::GetkeyPos()
{
	return m_keyPos;
}

// 当たり判定の座標用
VECTOR Ckey::GetkeyCenter()
{
	// 基本は物体の座標の位置
	VECTOR ret = m_keyPos;
	// 高さだけ足元からの半分あげる
	ret.y += m_keyradius;

	return ret;
}