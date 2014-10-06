#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "BaseSprite.h"
#include "Bullet.h"
#include "Config.h"
#include "res.h"

struct StructEnemyType;

class Enemy :public BaseSprite
{
public:

	Enemy(Node *gameStage, StructEnemyType &enemyType );

	~Enemy( );
	
	virtual bool init( );

	
	virtual void destory( );


	virtual int hurt( int &canHurt );
	
	//enemy  fire
	void fire( float dt );


	virtual cocos2d::Rect rect( );

	//对应的资源
    void stopFire( );

	// create enemy
	static Enemy * creatEnemy( Node *gameStage, StructEnemyType &enemyType );


	//************************************
	// Method:    boneDestory
	// FullName:  Enemy::boneDestory
	// Access:    public 
	// Returns:   void
	// Qualifier:   对象销毁
	//************************************
	void  boneDestory(Node *node);

public:
	// hp
	int Hp( ) const {
		return hp;
	}

	// score
	int Score( ) const {
		return score;
	}

private:
	Node *gameStage;
	StructEnemyType   &enemyType; //
	int   hp;
	int score;
	int powers;//
};
#endif