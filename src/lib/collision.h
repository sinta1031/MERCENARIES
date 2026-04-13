#pragma once

#include <DxLib.h>

// 点と四角の当たり判定
// dotPos        :     点の座標
// squarePos     :     四角形の中心座標
// width         :     四角形の横幅
// height        :     四角形の縦幅
// @return       :     true=当たった　false=当たってない

class Collision {
public:

	static bool ChekHitDotToSquare(VECTOR dotPos, VECTOR squarePos,
		int width, int height);

	//矩形同士の当たり判定
	static bool ChekHitSquareToSquare(VECTOR SpuarePos1, int width1, int height1,
		VECTOR SquarePos2, int width2, int height2);

	//円同士の当たり判定
	static bool ChekHitCircleToCirsle(VECTOR CirslePos1, VECTOR CirslePos2,
		int radius1, int radius2);

	//ボックス同士の当たり判定
	static bool ChekHitBoxToBox(VECTOR BoxPos1, VECTOR Pos1,
		VECTOR BoxPos2, VECTOR Pos2);

	//3Dの円同士の当たり判定
	static bool ChekHitSphereToSphere(VECTOR SpherePos1, VECTOR SpherePos2,
		int radius1, int radius2);

};
