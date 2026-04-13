#include "EnemyManager.h"
#include "SoundManager.h"
#include <math.h>

//定義関連
static const char ENEMY_PATH[] = "data/model/enemy/ghost.mv1";
static const int WAIT_TIME = 10;

CEnemyManager::CEnemyManager()
{
	m_waitCount = 0;
}

CEnemyManager::~CEnemyManager()
{
	Exit();
}

void CEnemyManager::Init()
{
	for (int i = 0;i < ENEMY_NUM;i++)
	{
		c_E[i].Init();
	}
	m_waitCount = 0;
}

void CEnemyManager::Load()
{
	int hndl = MV1LoadModel(ENEMY_PATH);

	for (int i = 0;i < ENEMY_NUM;i++)
	{
		c_E[i].Load(hndl);
	}
	MV1DeleteModel(hndl);
}

void CEnemyManager::Step(VECTOR targetpos)
{
	int enemyNum = 0;
	for (int i = 0;i < ENEMY_NUM;i++)
	{
		c_E[i].Step();
		if (c_E[i].IsActive() == true)
		{
			enemyNum++;
		}
		c_E[i].ChaceTarget(targetpos);
	}

	m_waitCount++;
	if (m_waitCount > WAIT_TIME || enemyNum == 0)
	{
		Request();
		/*CSoundManager::Play(CSoundManager::VOICE_ENEMY);*/
		m_waitCount = 0;
	}
}

void CEnemyManager::Update()
{
	for (int i = 0;i < ENEMY_NUM;i++)
	{
		c_E[i].Update();
	}
}

void CEnemyManager::Draw()
{
	for (int i = 0;i < ENEMY_NUM;i++)
	{
		c_E[i].Draw();
	}
}

void CEnemyManager::Exit()
{
	for (int i = 0;i < ENEMY_NUM;i++)
	{
		c_E[i].Exit();
	}
}

//エネミーの数分の生存判定を消す
void CEnemyManager::AllIsActive()
{
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		c_E[i].SetActive(false);
	}
}

void CEnemyManager::Request()
{
	VECTOR pos = { (float)GetRand(70.0f) - 70.0f,(float)GetRand(30) + 20.0f,(float)GetRand(60) - 0.0f };
	//VECTOR speed = { 0.0f,0.0f,-0.5f };
	for (int i = 0;i < ENEMY_NUM;i++)
	{
		if (c_E[i].Request(pos /*,speed*/) == true)
		{
			break;
		}
	}
}