#include "midpoint.h"

static const char REDPOINT_MODEL_PATH[] =
"data/field/gimmick/allstage/Midpoint/redhata.x";

static const char BLUEPOINT_MODEL_PATH[] =
"data/field/gimmick/allstage/Midpoint/bluehata.x";


// コンストラクタ・デストラクタ
Cmidpoint::Cmidpoint()
{
	Init();
}

Cmidpoint::~Cmidpoint()
{
	Exit();
}

//初期化
void Cmidpoint::Init()
{
	//中間ポイント
	for (int i = 0; i < MIDPOINT_MAX; i++) {

		m_hndl_red[i] = -1;
		m_hndl_blue[i] = -1;
		m_Pos[i] = { 0.0f,0.0f,0.0f };
		m_Hitflag[i] = false;
	}
}

//ロード
void Cmidpoint::Load(int _stageNum,int _hndl)
{
	for (int i = 0; i < MIDPOINT_MAX; i++) {

		int hndl_1 = MV1LoadModel(REDPOINT_MODEL_PATH);
		int hndl_2 = MV1LoadModel(BLUEPOINT_MODEL_PATH);

		m_hndl_red[i] = MV1DuplicateModel(hndl_1);
		m_hndl_blue[i] = MV1DuplicateModel(hndl_2);

		MV1DeleteModel(hndl_1);
		MV1DeleteModel(hndl_2);

		switch (_stageNum)
		{
		case 1:
			if (i == 0)
			{
				m_Pos[0] = GetFramePos(_hndl, 106);
			}
			if (i == 1)
			{
				m_Pos[1] = GetFramePos(_hndl, 109);
			}
			if (i == 2)
			{
				m_Pos[2] = GetFramePos(_hndl, 112);
			}
			break;
		}

		MV1SetupCollInfo(m_hndl_red[i]);
	}
}

//更新処理
void Cmidpoint::Step()
{

}

//フィールドのアップデート
void Cmidpoint::Update()
{
	//三つの中間ポイントを配列で
	for (int i = 0; i < MIDPOINT_MAX; i++)
	{
		//ポリゴン情報も配列
		MV1SetPosition(m_hndl_red[i], m_Pos[i]);
		MV1SetPosition(m_hndl_blue[i], m_Pos[i]);
	}
}

//描画
void Cmidpoint::Draw()
{
	for (int i = 0; i < MIDPOINT_MAX; i++)
	{
		if (m_Hitflag[i] == true)
		{
			MV1DrawModel(m_hndl_blue[i]);
		}
		else
		{
			MV1DrawModel(m_hndl_red[i]);
		}
	}
}

//破棄
void Cmidpoint::Exit()
{
	for (int i = 0; i < MIDPOINT_MAX; i++) {

		if (m_hndl_red[i] != -1)
		{
			MV1TerminateCollInfo(m_hndl_red[i]);
			MV1DeleteModel(m_hndl_red[i]);
			m_hndl_red[i] = -1;
		}

		if (m_hndl_blue[i] != -1)
		{
			MV1DeleteModel(m_hndl_blue[i]);
			m_hndl_blue[i] = -1;
		}
	}
}

// 当たり判定
// @center  :  当たり判定する相手の座標
// @radius　:  球の半径
// @return  :  押し戻すべき距離と方向
bool Cmidpoint::midpointHitCheck(VECTOR center, float redius)
{
	//水に触れるとフラグをtureにする
	bool result = false;
	MV1_COLL_RESULT_POLY_DIM col;
	
	//個数分の当たり判定を行い、その結果を構造体に格納
	for (int i = 0; i < MIDPOINT_MAX; i++)
	{
		if (m_Hitflag[i] == false)
		{
			col = MV1CollCheck_Sphere(m_hndl_red[i], -1, center, redius);

			//ヒットしたポリゴンがあれば、フラグをオンに
			// ポリゴンと当たった
			if (col.HitNum != 0)
			{
				m_Hitflag[i] = true;
				//リザルトをtrueにする
				result = true;
			}
		}
	}

	//終了前にコリジョンデータを破棄
	MV1CollResultPolyDimTerminate(col);

	return result;
}