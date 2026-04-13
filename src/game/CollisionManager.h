#pragma once
#include "player.h"
#include "Another.h"
#include "EnemyManager.h"
#include "ShotManager.h"
#include "filed.h"

// 各種オブジェクトの当たり判定クラス
class CCollisionManager {
public:
	//プレイヤーの弾の当たり判定と敵の当たり判定
	static void CheckHitShotToEnemy(CShotManager& shot, CEnemyManager& enemy);

	//プレイヤーの当たり判定と敵の当たり判定
	static void CheckHitPlayerToEnemy(CPlayer& player, CEnemyManager& enemy);

};