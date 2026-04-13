#include "filed.h"

static const char SKY_MODEL_PATH[] = 
"data/field/field/Sky/sky.mv1";

static const char FILED_MODEL_PATH[] =
"data/field/field/tutorialstage/stage.x";

  
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
	//ステージ
	m_fieldhndl = -1;
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
	switch (m_tagstage)
	{
	case CFiled::STAGE1:

		if (m_fieldhndl == -1)
		{
			m_fieldhndl = MV1LoadModel(FILED_MODEL_PATH);
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
	switch (m_tagstage)
	{

	case CFiled::STAGE1:

		break;
	}

	//ポリゴンの情報取得
	MV1SetupCollInfo(m_fieldhndl);
	MV1SetRotationXYZ(m_Skyhndl, m_Rot);

}

//描画
void  CFiled::Draw()
{
	//ステージ描画
	MV1DrawModel(m_fieldhndl);
	MV1DrawModel(m_Skyhndl);


	switch (m_tagstage)
	{
	case CFiled::STAGE1:

		break;
	}

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
		
		break;
	}

	if (m_fieldhndl != -1)
	{
		MV1TerminateCollInfo(m_fieldhndl);
		MV1DeleteModel(m_fieldhndl);
		m_fieldhndl = -1;
	}
	if (m_Skyhndl != -1)
	{
		MV1DeleteModel(m_Skyhndl);
		m_fieldhndl = -1;
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

	//当たり判定を行い、その結果を構造体に格納
	col = MV1CollCheck_Sphere(m_fieldhndl, -1, center, radius);

	//ヒットしたポリゴンがあれば、フラグをオンに
	if (col.HitNum != 0)
	{
		//当たった時の処理
		// 当たったデータをすべてチェックする
		for (int i = 0; i < col.HitNum; i++)
		{
			//まず中心点から最近点を引き算
			VECTOR v = VSub(center, col.Dim[i].HitPosition);

			//取得したベクトルを三平方の定理で長さに変換
			float len = VSize(v);

			//実際にめり込んだ距離を計算
			len = radius - len;

			//法線をめり込んだ距離分掛け算する
			v = VScale(col.Dim[i].Normal, len);

			//計算結果を合算していく
			result = VAdd(result, v);
		}
	}
	//終了前にコリジョンデータを破棄
	MV1CollResultPolyDimTerminate(col);

	return result;
}

