#include "Enemy.h"
#include "Effect.h"
#include "ActionForEnemy.h"

Enemy::Enemy( Node *gameStage, StructEnemyType &enemyType ) :gameStage( gameStage ), enemyType(enemyType )
{

}

Enemy::~Enemy( )
{

}

bool Enemy::init( )
{
	if(!Sprite::init( ))
	{
		return false;
	}
	hp = enemyType.hp;
	score = enemyType.score;//得分
	powers = enemyType.powers;
	this->initWithSpriteFrameName(enemyType.enemyPicName);
	//fire
	this->schedule(schedule_selector( Enemy::fire ), 1.5f);
	return true;
}
//************************************
// Method:    creatEnemy   may be like a factory
// FullName:  Enemy::creatEnemy
// Access:    public static 
// Returns:   Enemy *
// Qualifier:
// Parameter: int enemyType
// Parameter: int canHurt
// Parameter: int speedY
// Parameter: int bulletType
// Parameter: int ownType
//************************************
Enemy * Enemy::creatEnemy( Node *gameStage, StructEnemyType &enemyType )
{
	auto enemy = new Enemy(gameStage, enemyType);
	if (enemy&&enemy->init())
	{
		
		enemy->autorelease( );
		return enemy;
	}
	delete enemy;
	enemy = NULL;
	return enemy;
}

void Enemy::destory( )
{

	if(hp <= 0){

		//explosion effect  flame
		auto effect = Effect::CreateEffect( );
		effect->explosion(gameStage, this->getPosition( ));

		//explosion effect of particle


		auto config = Config::getInstance( );
		if(config->geteffectState( ))
		{
			SimpleAudioEngine::getInstance( )->playEffect( ship_explode_effect0 );
		}
	
		config->setScore( config->getScore( ) + score );

		//log("current get score is :%d",config->getScore  () );
	
		this->unschedule(schedule_selector( Enemy::fire ) );
		this->removeFromParent( );
	}
}
int Enemy::hurt( int &_canHurt )
{

	return hp -= _canHurt;
}

Rect Enemy::rect( )
{
	return Kit::getRect( this );
}

//creat  bullet  and fire  -- create  bullet obj ,add to the game stage
void Enemy::fire( float dt )
{
	auto config = Config::getInstance( );

	auto enemyPosition = this->getPosition( );
	auto dx = enemyPosition.x;
	auto dy = enemyPosition.y + 10;
	float offset = 0;
	auto type = config->getInstance()->getBulletByType(enemyType.bulletType);
	for (int i = 0; i != powers;++i)
	{
		//left
		auto bullet = Bullet::createBullet(type.canHurt
			, type.speedY, type.picName, type.ownType);
		bullet->setPosition(Vec2(dx - offset, dy));
		gameStage->addChild(bullet, BULLET_Z_ORDER);
		config->enemy_bullet_list->pushBack(bullet);

		//right
		bullet = Bullet::createBullet(type.canHurt
			, type.speedY, type.picName, type.ownType);
		bullet->setPosition(Vec2(dx + offset, dy));
		gameStage->addChild(bullet, BULLET_Z_ORDER);
		config->enemy_bullet_list->pushBack(bullet);
		offset += 25;
	}
	
}


void Enemy::stopFire( )
{
	this->unschedule( schedule_selector( Enemy::fire ) );
}

void Enemy::boneDestory(Node *node)
{
	//explosion effect  flame
//	auto effect = Effect::CreateEffect();
	//effect->explosion(gameStage, this->getPosition());

	Kit::addParticle(bone_exploding_plist, node, this->getPosition());
	//explosion effect of particle
	auto config = Config::getInstance();
	if (config->geteffectState())
	{
		SimpleAudioEngine::getInstance()->playEffect(ship_explode_effect0);
	}

	this->unschedule(schedule_selector(Enemy::fire));
	this->removeFromParent();
}

