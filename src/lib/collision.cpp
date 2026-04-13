#include "collision.h"

//-------------------------------
// 点と四角の当たり判定
//-------------------------------

bool Collision::ChekHitDotToSquare(VECTOR dotPos, VECTOR squarePos,int width, int height)
{
	//四角形の上下左右それぞれの座標を計算する
	float up = squarePos.y - height * 0.5f;
	float down = squarePos.y + height * 0.5f;
	float left = squarePos.x - width * 0.5f;
	float right = squarePos.x + width * 0.5f;

	//4つの端をそれぞれチェックして、すべての条件を満たしたらヒット！
	if (dotPos.x >= left && dotPos.x <= right
		&& dotPos.y >= up && dotPos.y <= down)
	{
		return true; //無事ヒット！！
	}
	else return false; //ヒットならず
}

// 立方体同士の当たり判定
bool Collision::ChekHitSquareToSquare(VECTOR SquarePos1, int width1, int height1, VECTOR SquarePos2, int width2, int height2)
{
	//四角形の上下左右それぞれの座標を計算する
	float up1 = SquarePos1.y - height1 * 0.5f;
	float down1 = SquarePos1.y + height1 * 0.5f;
	float left1 = SquarePos1.x - width1 * 0.5f;
	float right1 = SquarePos1.x + width1 * 0.5f;

	//四角形の上下左右それぞれの座標を計算する
	float up2 = SquarePos2.y - height2 * 0.5f;
	float down2 = SquarePos2.y + height2 * 0.5f;
	float left2 = SquarePos2.x - width2 * 0.5f;
	float right2 = SquarePos2.x + width2 * 0.5f;

	//4つの端をそれぞれチェックして、すべての条件を満たしたらヒット！
	if (up1 <= down2 && down1 <= up2
		&& left1 >= right2 && right1 <= left2)
	{
		return true; //無事ヒット！！
	}
	else
	{
		return false; //ヒットならず
	}
}

//円同士の当たり判定
bool Collision::ChekHitCircleToCirsle(VECTOR CirslePos1, VECTOR CirslePos2,
	int radius1, int radius2)
{
	//横の長さの2乗を調べる
	float lenX = CirslePos1.x - CirslePos2.x;
	lenX *= lenX;

	//縦の長さの2乗を調べる
	float lenY = CirslePos1.y - CirslePos2.y;
	lenY *= lenY;

	//最短距離の2乗を計算
	float len = lenX + lenY;

	//半径２個を足した値の2乗を調べる
	float totalRadius = radius1 + radius2;
	totalRadius *= totalRadius;

	//最短距離の2乗 <= 半径を2個を足した値の2乗
	if (len <= totalRadius)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//ボックス同士の当たり判定
bool Collision::ChekHitBoxToBox(VECTOR BoxPos1, VECTOR size1, VECTOR BoxPos2, VECTOR size2)
{
	//四角形の上下左右手前奥それぞれの座標を計算する
	float up1 = BoxPos1.y - size1.y * 0.5f;
	float down1 = BoxPos1.y + size1.y * 0.5f;
	float left1 = BoxPos1.x - size1.x * 0.5f;
	float right1 = BoxPos1.x + size1.x * 0.5f;
	float flont1 = BoxPos1.z - size1.z * 0.5f;
	float Back1 = BoxPos1.z + size1.z * 0.5f;

	//四角形の上下左右手前奥それぞれの座標を計算する
	float up2 = BoxPos2.y - size2.y * 0.5f;
	float down2 = BoxPos2.y + size2.y * 0.5f;
	float left2 = BoxPos2.x - size2.x * 0.5f;
	float right2 = BoxPos2.x + size2.x * 0.5f;
	float flont2 = BoxPos2.z - size2.z * 0.5f;
	float Back2 = BoxPos2.z + size2.z * 0.5f;

	//6つの端をそれぞれチェックして、すべての条件を満たしたらヒット！
	if (flont1 <= Back2 && Back1 >= flont2 &&
		up1 <= down2 && down1 >= up2 &&
		left1 <= right2 && right1 >= left2)
	{
		return true; //無事ヒット！！
	}
	else
	{
		return false; //ヒットならず
	}
}

//3Dの円同士の当たり判定
bool Collision::ChekHitSphereToSphere(VECTOR SpherePos1, VECTOR SpherePos2, int radius1, int radius2)
{
	//横の長さの2乗を調べる
	float lenX = SpherePos1.x - SpherePos2.x;
	lenX *= lenX;

	//縦の長さの2乗を調べる
	float lenY = SpherePos1.y - SpherePos2.y;
	lenY *= lenY;

	//奥行の長さの2乗を調べる
	float lenZ = SpherePos1.z - SpherePos2.z;
	lenZ *= lenZ;

	//最短距離の2乗を計算
	float len = lenX + lenY + lenZ;

	//半径２個を足した値の2乗を調べる
	float totalRadius = radius1 + radius2;
	totalRadius *= totalRadius;

	//最短距離の2乗 <= 半径を2個を足した値の2乗
	if (len <= totalRadius)
	{
		return true;
	}
	else
	{
		return false;
	}
}