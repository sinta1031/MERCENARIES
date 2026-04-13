#include "Debugcamera.h"
#include "math.h"

static const VECTOR ZERO = { 0.0f,0.0f,0.0f };
static const float MOVE_SPEED = 1.0f;
static const float ROT_SPEED = 0.2f;

//---------------------------
// コンストラクタ
//---------------------------
CDebugCamera::CDebugCamera()
{
	Init();
}

//----------------------------
// 初期化
//----------------------------
void CDebugCamera::Init()
{
	m_Pos = ZERO;
	m_Rot = ZERO;
	m_targetPos = ZERO;
	m_upVec = { 0.0f, 1.0f, 0.0f };		 
}

//----------------------------
// カメラの座標計算
//----------------------------
void CDebugCamera::Step()
{
	//カメラの回転速度======================
	// 上下
	if (CheckHitKey(KEY_INPUT_UP) != 0)
	{
		m_Rot.x -= ROT_SPEED;
	}
	if (CheckHitKey(KEY_INPUT_DOWN) != 0)
	{
		m_Rot.x += ROT_SPEED;
	}

	// 左右
	if (CheckHitKey(KEY_INPUT_LEFT) != 0)
	{
		m_Rot.y -= ROT_SPEED;
	}
	if (CheckHitKey(KEY_INPUT_RIGHT) != 0)
	{
		m_Rot.y += ROT_SPEED;
	}

	//カメラの移動処理===================
	// 前進
	if (CheckHitKey(KEY_INPUT_W) != 0)
	{
		//カメラの角度がすべて0の時に進む速度
		VECTOR defaultDir = { 0.0f,0.0f,MOVE_SPEED };

		//上記を行列に変換
		MATRIX dir = MGetTranslate(defaultDir);

		//X軸回転行列
		MATRIX rotX = MGetRotX(m_Rot.x);

		//Y軸回転行列
		MATRIX rotY = MGetRotY(m_Rot.y);

		//各行列を合成していく
		MATRIX res = MMult(dir, rotX);
		res = MMult(res, rotY);

		//行列から移動情報だけを取り出す
		VECTOR move;
		move.x = res.m[3][0];
		move.y = res.m[3][1];
		move.z = res.m[3][2];

		//計算結果をカメラの現在の座標に足す
		m_Pos = VAdd(m_Pos, move);
	}
}

//-----------------------
// カメラの更新
//-----------------------
void CDebugCamera::Update()
{
	SetCameraPositionAndAngle(m_Pos, m_Rot.x, m_Rot.y, m_Rot.z);
}

//---------------------------------------------------
// 仕掛けが動くときに一度だけカメラを向ける
//---------------------------------------------------
void CDebugCamera::EventCamera(VECTOR focus)
{
	//現在のカメラの位置からターゲットの位置までの方向ベクトルを取得
	VECTOR dir = VSub(m_Pos, focus);
	//dir.y = 0.0f;   //高さを考慮するとややこしいんで、一旦無視

	//今回は長さが重要なので、先ほど計算したベクトルから長さを計算
	float len = VSize(dir);

	//長さを求めたので、方向ベクトルは正規化してしまう
	dir = VNorm(dir);

	//注視点は物体のの上側の位置当たりに
	m_targetPos = focus;
	m_targetPos.y += 15.0;

	//視点は見下ろし型になるように、少し下に
	m_Pos.y = m_targetPos.y + 25.0f;

	dir = VSub(m_Pos, m_targetPos);
	m_Rot.y = atan2f(dir.x, dir.z);
}