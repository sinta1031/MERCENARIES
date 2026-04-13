#include "CollisionManager.h"
#include "../lib/collision.h"

//プレイヤーの弾の当たり判定と敵の当たり判定
void CCollisionManager::CheckHitShotToEnemy(CShotManager& shot, CEnemyManager& enemy)
{
	// 弾の数だけループ
	for (int shotID = 0; shotID < PL_SHOT_NUM; shotID++)
	{
		// 弾一発分の情報を取得し、生存確認
		CShot& oneShot = shot.GetShot(shotID);
		if (oneShot.IsActive() == false)continue;

		// 敵の数だけループ
		for (int enemyID = 0; enemyID < ENEMY_NUM; enemyID++)
		{
			// 敵一体の情報を取得し、生存確認
			CEnemy& oneEnemy = enemy.GetEnemy(enemyID);
			if (oneEnemy.IsActive() == false)continue;

			// それぞれの座標と半径取得
			VECTOR shotPos = oneShot.GetCenter();
			float shotRadius = oneShot.GetRadius();
			VECTOR enemyPos = oneEnemy.GetCenter();
			float enemyRadius = oneEnemy.GetRadius();

			// 当たり判定開始
			bool isHit = Collision::ChekHitSphereToSphere(shotPos, enemyPos, shotRadius, enemyRadius);

			if (isHit == true)
			{
				// お互い当たった!!
				oneShot.HitCalc();
				oneEnemy.HitCalc();
			}
		}
	}
}

//プレイヤーの当たり判定と敵の当たり判定
void CCollisionManager::CheckHitPlayerToEnemy(CPlayer& player, CEnemyManager& enemy)
{
	// プレイヤーが死んだら何もしない
	if (player.IsActive() == false)return;

	// 敵の数だけループ
	for (int enemyID = 0; enemyID < ENEMY_NUM; enemyID++)
	{
		// 敵一体の情報を取得し、生存確認
		CEnemy& oneEnemy = enemy.GetEnemy(enemyID);
		if (oneEnemy.IsActive() == false)continue;

		// それぞれの座標と半径取得
		VECTOR playerPos = player.GetCenter();
		float playerRadius = player.GetRadius();
		VECTOR enemyPos = oneEnemy.GetCenter();
		float enemyRadius = oneEnemy.GetRadius();

		// 当たり判定開始
		bool isHit = Collision::ChekHitSphereToSphere(playerPos, enemyPos, playerRadius, enemyRadius);

		if (isHit == true)
		{
			// お互い当たった!!
		    /*player.HitCalc();*/
			oneEnemy.HitCalc();
		}
	}
}