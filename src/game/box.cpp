#include "box.h"

#define GRAVITY				( 0.05f ) //重力

static const char BOX_MODEL_PATH[] =
"data/field/gimmick/1.stage/fire Box/fire Box.x";

// コンストラクタ・デストラクタ
Cbox::Cbox()
{
	Init();
}

Cbox::~Cbox()
{
	Exit();
}

//初期化
void Cbox::Init()
{
	//ボックス
	for (int Y = 0; Y < BOX_Y_MAX; Y++)
	{
		for (int X = 0; X < BOX_X_MAX; X++)
		{
			m_boxhndl[X][Y] = -1;
			m_boxPos[X][Y] = { 0.0f,0.0f,0.0f };
			m_boxisActive[X][Y] = true;
		}
	}
	m_boxgravity = 0.0f;
}

//ロード
void Cbox::Load(int _hndl)
{
	for (int Y = 0; Y < BOX_Y_MAX; Y++)
	{
		for (int X = 0; X < BOX_X_MAX; X++)
		{
			int hndl = MV1LoadModel(BOX_MODEL_PATH);

			m_boxhndl[X][Y] = MV1DuplicateModel(hndl);

			MV1DeleteModel(hndl);

			m_boxPos[0][0] = GetFramePos(_hndl, 26);
			VECTOR BOX_COMIT_X = { m_boxPos[0][0].x + 50.0f * X,m_boxPos[0][0].y + 50.0f * Y,m_boxPos[0][0].z };	//ボックスX座標増減地

			m_boxPos[X][Y] = BOX_COMIT_X;
		}
	}
}

//更新処理
void Cbox::Step()
{
	//ボックスの重力
	/*for (int Y = 0; Y < BOX_Y_MAX; Y++)
	{
		for (int X = 0; X < BOX_X_MAX; X++)
		{
			if (m_boxisActive[X][Y] == true)
			{
				m_boxgravity = GRAVITY;
				m_boxPos[X][Y].y = m_boxgravity;
			}
		}
	}*/
}

//フィールドのアップデート
void Cbox::Update()
{
	for (int Y = 0; Y < BOX_Y_MAX; Y++)
	{
		for (int X = 0; X < BOX_X_MAX; X++)
		{
			MV1SetPosition(m_boxhndl[X][Y], m_boxPos[X][Y]);
		}
	}
}

//描画
void Cbox::Draw()
{
	for (int Y = 0; Y < BOX_Y_MAX; Y++)
	{
		for (int X = 0; X < BOX_X_MAX; X++)
		{
			if (m_boxisActive[X][Y] == true)
			{
				MV1DrawModel(m_boxhndl[X][Y]);
			}
		}
	}
}

//破棄
void Cbox::Exit()
{
	for (int Y = 0; Y < BOX_Y_MAX; Y++)
	{
		for (int X = 0; X < BOX_X_MAX; X++)
		{
			if (m_boxhndl[X][Y] != -1)
			{
				MV1DeleteModel(m_boxhndl[X][Y]);
				m_boxhndl[X][Y] = -1;
			}
		}
	}
}

VECTOR Cbox::boxHitCheck(VECTOR center, float redius)
{
	//水に触れるとフラグをtureにする
	VECTOR result = { 0.0f };
	MV1_COLL_RESULT_POLY_DIM col;

	//個数分の当たり判定を行い、その結果を構造体に格納
	for (int Y = 0; Y < BOX_Y_MAX; Y++)
	{
		for (int X = 0; X < BOX_X_MAX; X++)
		{
			col = MV1CollCheck_Sphere(m_boxhndl[X][Y], -1, center, redius);

			//生存判定があるなら
			if (m_boxisActive[X][Y] == true)
			{
				// ポリゴンと当たった
				if (col.HitNum != 0)
				{
					

					//当たった時の処理
					// 当たったデータをすべてチェックする
					for (int i = 0; i < col.HitNum; i++)
					{
						//まず中心点から最近点を引き算
						VECTOR v = VSub(center, col.Dim[i].HitPosition);

						//取得したベクトルを三平方の低利で長さに変換
						float len = VSize(v);

						//実際にめり込んだ距離を計算
						len = redius - len;

						//法線をめり込んだ距離分掛け算する
						v = VScale(col.Dim[i].Normal, len);

						//計算結果を合算していく
						result = VAdd(result, v);
					}
				}
			}
		}
	}

	//終了前にコリジョンデータを破棄
	MV1CollResultPolyDimTerminate(col);

	return result;
}

bool Cbox::boxHitDestroyCheck(VECTOR center, float redius)
{
	//水に触れるとフラグをtureにする
	bool result = false;
	MV1_COLL_RESULT_POLY_DIM col;

	//個数分の当たり判定を行い、その結果を構造体に格納
	for (int Y = 0; Y < BOX_Y_MAX; Y++)
	{
		for (int X = 0; X < BOX_X_MAX; X++)
		{
			col = MV1CollCheck_Sphere(m_boxhndl[X][Y], -1, center, redius);

			//生存判定があるなら
			if (m_boxisActive[X][Y] == true)
			{
				// ポリゴンと当たった
				if (col.HitNum != 0)
				{
					//リザルトをtrueにする
					result = true;

					//当たった時の処理
					// 当たったデータをすべてチェックする
					for (int i = 0; i < col.HitNum; i++)
					{
						SetboxActive(false, X, Y);
					}
				}
			}
		}
	}

	//終了前にコリジョンデータを破棄
	MV1CollResultPolyDimTerminate(col);

	return result;
}

//現在位置に座標加算
void Cbox::ReflectCollision(VECTOR addVec)
{

}