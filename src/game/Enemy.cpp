#include "Enemy.h"
#include "SoundManager.h"

CEnemy::CEnemy()
{
	Init();
}

CEnemy::~CEnemy()
{
	Exit();
}

void CEnemy::Init()
{
	memset(&m_pos, 0, sizeof(m_pos));
	memset(&m_rot, 0, sizeof(m_rot));
	memset(&m_speed, 0, sizeof(m_speed));
	m_radius = 7.0f;
	m_hndl = -1;
	m_isActive = false;
}

void CEnemy::Load(int hndl)
{
	if (m_hndl = -1)
	{
		m_hndl = MV1DuplicateModel(hndl);
	}
}

void CEnemy::Step()
{
	if (m_isActive == false)return;

	m_pos = VAdd(m_pos, m_speed);

	float length = 300.0f;
	if (m_pos.x > length || m_pos.x < -length ||
		m_pos.y > length || m_pos.y < -length ||
		m_pos.z > length || m_pos.z < -length)
	{
		m_isActive = false;
	}
}

// ターゲットを追いかける
void CEnemy::ChaceTarget(VECTOR targetPos)
{
	//目的地に向かうためのベクトルを計算
	VECTOR dir = VSub(targetPos, m_pos);

	dir = VNorm(dir); //正規化する

	//正規化したベクトルを移動速度のサイズに
	dir = VScale(dir, WALK_SPEED);

	//今いる位置に移動速度を加算
	m_pos = VAdd(m_pos, dir);

	//進行方向を向かせる
	float rotY = atan2f(-dir.x, -dir.z);
	m_rot = (VGet(0.0f, rotY, 0.0f));
}


void CEnemy::Update()
{
	MV1SetPosition(m_hndl, m_pos);
	MV1SetRotationXYZ(m_hndl, m_rot);
}

void CEnemy::Draw()
{
	// 生存フラグオフの場合は即終了
	if (m_isActive == false)return;

	MV1DrawModel(m_hndl);

	//当たり判定を目視できるように
	DrawSphere3D(GetCenter(), m_radius,
		16, GetColor(255, 0, 0),
		GetColor(255, 0, 0), FALSE);
}

void CEnemy::Exit()
{
	if (m_hndl != -1)
	{
		MV1DeleteModel(m_hndl);
		m_hndl = -1;
	}
}

bool CEnemy::Request(const VECTOR& pos/*, const VECTOR& speed*/)
{
	if (m_isActive == true)return false;

	m_pos = pos;
	//m_speed = speed;
	m_isActive = true;

	return true;
}

//ヒット後の処理
void CEnemy::HitCalc()
{
	// 生存フラグを消す
	m_isActive = false;
	//CSoundManager::Play(CSoundManager::SE_EXPLOSION);
}

// 当たり判定の座標用
VECTOR CEnemy::GetCenter()
{
	// 基本は物体の座標の位置
	VECTOR ret = m_pos;
	// 高さだけ足元から弾の半分あげる
	ret.y += m_radius;

	return ret;
}