#include "filed.h"

// staticメンバ関数はここで各作業が必須!!
vector<int> CFiled::m_hndl;

static const char SKY_MODEL_PATH[] = 
"data/field/field/Sky/VILLAGE/sky.mv1";

// コンストラクタ・デストラクタ
CFiled::CFiled()
{
	Init();
}

CFiled::~CFiled()
{
	Exit();
}

//背景の初期化
void CFiled::Init()
{
	m_tagstage = STAGE1;

	//ステージ
	m_hndl.clear();
	m_isHitFlag = false;

	//背景
	m_Skyhndl = -1;
	m_SkyScale = { 30.0f,30.0f,30.0f };
	m_Rot = { 0.0f,0.0f,0.0f };
}

//更新処理
void CFiled::Step()
{
	m_Rot.y += 0.0001f;
}

//ロード
void  CFiled::Load()
{
	//最初にロード
	const char* VillagePath[VILLAGE_PARTS_NUM] = {
	"data/field/field/Village/Village.mv1",
	"data/field/field/Village/Village1.mv1",
	"data/field/field/Village/Village2.mv1",

	};

	switch (m_tagstage)
	{
	case CFiled::STAGE1:
		for (int i = 0; i < VILLAGE_PARTS_NUM; i++)
		{
			int hndl = MV1LoadModel(VillagePath[i]);
			m_hndl.push_back(hndl);
		}

		if (m_Skyhndl == -1)
		{
			m_Skyhndl = MV1LoadModel(SKY_MODEL_PATH);
			MV1SetScale(m_Skyhndl, m_SkyScale);
		}

		break;
	case CFiled::STAGE2:
		break;
	case CFiled::STAGE3:
		break;
	}
	
}

//フィールドのアップデート
void CFiled::Update()
{
	//ステージ専用のギミックがあるなら
	switch (m_tagstage)
	{
		//それぞれに記入
	case CFiled::STAGE1:
		for (int i = 0; i < m_hndl.size(); i++)
		{
			if (m_hndl[i] != -1)
			{
				//ポリゴンの情報取得
				MV1SetupCollInfo(m_hndl[i]);
			}
		}

		break;
	case CFiled::STAGE2:

		break;
	case CFiled::STAGE3:

		break;
	}

	//ポリゴンの情報取得
	MV1SetRotationXYZ(m_Skyhndl, m_Rot);

}

//描画
void  CFiled::Draw()
{
	//ステージ描画
	switch (m_tagstage)
	{
	case CFiled::STAGE1:

		for (int i = 0; i < m_hndl.size(); i++)
		{
			if (m_hndl[i] != -1)
			{
				MV1DrawModel(m_hndl[i]);
			}
		}

		break;
	}

	MV1DrawModel(m_Skyhndl);

	////当たり判定を目視できるように
	//DrawSphere3D(GetgoalCenter(), goalradius,
	//	16, GetColor(255, 0, 0),
	//	GetColor(255, 0, 0), FALSE);

	/*if (m_isHitFlag == true)
	{
		DrawFormatString(32, 60, GetColor(255, 255, 255), "Hit!");
	}*/
}

//破棄
void  CFiled::Exit()
{
	switch (m_tagstage)
	{
	case CFiled::STAGE1:
		
		for (int i = 0; i < m_hndl.size(); i++)
		{
			if (m_hndl[i] != -1)
			{
				MV1DeleteModel(m_hndl[i]);
				m_hndl[i] = -1;
			}
		}

		break;
	}

	if (m_Skyhndl != -1)
	{
		MV1DeleteModel(m_Skyhndl);
		m_Skyhndl = -1;
	}
}

// 当たり判定
// @center  :  当たり判定する相手の座標
// @radius　:  球の半径
// @return  :  押し戻すべき距離と方向
VECTOR CFiled::FieldHitCheck(VECTOR center, float radius)
{
	//押し戻し距離を呼び戻し元に伝えるために使用
	VECTOR result = { 0.0f };

	//当たり判定が格納される構造体
	MV1_COLL_RESULT_POLY_DIM col;

	for (int i = 0; i < m_hndl.size(); i++)
	{
		//当たり判定を行い、その結果を構造体に格納
		col = MV1CollCheck_Sphere(m_hndl[i], -1, center, radius);

		//ヒットしたポリゴンがあれば、フラグをオンに
		if (col.HitNum != 0)
		{
			//当たった時の処理
			// 当たったデータをすべてチェックする
			for (int j = 0; j < col.HitNum; j++)
			{
				//まず中心点から最近点を引き算
				VECTOR v = VSub(center, col.Dim[j].HitPosition);

				//取得したベクトルを三平方の定理で長さに変換
				float len = VSize(v);

				//実際にめり込んだ距離を計算
				len = radius - len;

				//法線をめり込んだ距離分掛け算する
				v = VScale(col.Dim[j].Normal, len);

				//計算結果を合算していく
				result = VAdd(result, v);
			}
		}

		//終了前にコリジョンデータを破棄
		MV1CollResultPolyDimTerminate(col);
	}

	return result;
}