#include "Shot.h"
#include "../lib/input.h"
#include <math.h>

#define SHOT_SPEED (0.1f)
#define ACTIVE_TIME_MAX (100)

static const VECTOR ZERO = { 0.0f,0.0f,0.0f };
static const float GRAVITY = 0.02f;

// コンストラクタ・デストラクタ
CShot::CShot()
{
	Init();
}

CShot::~CShot()
{
	Exit();
}

// プレーヤーの初期化
void CShot::Init()
{
	m_vPos = ZERO;
	m_vSpeed = ZERO;
	m_radius = 15.0f;
	m_gravity = 0.0f;
	m_isActive = false;
	m_isActiveTime = 0;
	m_Hndl = -1;
}

//ロード
void  CShot::Load(int orginHndl)
{
	// ロードされていなければやる
	if (m_Hndl == -1)
	{
		// 3Dモデルデータ読み込み
		m_Hndl = MV1DuplicateModel(orginHndl);
	}
}

//描画
void  CShot::Draw()
{
	if (m_isActive == true)
	{
		MV1DrawModel(m_Hndl);
	}
}

//破棄
void  CShot::Exit()
{
	// データをロードしている時だけ削除
	if (m_Hndl != -1)
	{
		MV1DeleteModel(m_Hndl);
		m_Hndl = -1;
	}
}

// プレイヤーの座標計算
void  CShot::Step()
{
	//呼び出されていない場合は無効
	if (!m_isActive) return;

	//現在の座標に速度を加算する
	m_vPos = VAdd(m_vPos, m_vSpeed);

	//重力も付け足す？
	m_gravity -= GRAVITY;
	m_vPos.y += m_gravity;

	//時間がたったら弾を削除
	m_isActiveTime--;
	if (m_isActiveTime <= 0)
	{
		m_isActive = false;

		// とりあえず物体にぶつかったら重力を0に
		m_gravity = 0.0f;
	}
}

// プレイヤーの更新
void  CShot::Update()
{
	// 移動結果をプレイヤーに設定
	MV1SetPosition(m_Hndl, m_vPos);
}

// 弾をリクエスト
bool CShot::Request(const VECTOR& pos, const VECTOR& speed)
{
	// すでに発射されている弾は生成失敗
	if (m_isActive)return false;

	// 必要な情報を渡していく
	m_isActive = true;
	m_vPos = pos;
	m_vSpeed = speed;
	m_isActiveTime = ACTIVE_TIME_MAX;

	return true;
}

//ヒット後の処理
void CShot::HitCalc()
{
	// 生存フラグを消す
	m_isActive = false;

	// とりあえず物体にぶつかったら重力を0に
	m_gravity = 0.0f;	
}

// 当たり判定の座標用
VECTOR CShot::GetCenter()
{
	// 基本は物体の座標の位置
	VECTOR ret = m_vPos;
	// 高さだけ足元から弾の半分あげる
	ret.y += m_radius;

	return ret;
}