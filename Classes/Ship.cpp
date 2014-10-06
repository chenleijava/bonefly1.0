#include "Ship.h"
#define  SHIP_FILE_NAME "Plane0_0.png"


Ship::Ship( Node *gameStage, int shipType, int hp ) :gameStage( gameStage ), shipType( shipType ), hp( hp )
{

}


Ship::~Ship( )
{
}

bool Ship::init( )
{

	if(!Sprite::init( ))
	{
		return false;
	}

	this->initWithSpriteFrameName(SHIP_FILE_NAME );

	//fire
	this->schedule(schedule_selector(Ship::fire), 0.1f, kRepeatForever, 1.0f );
	return true;

}


void Ship::destory( )
{
	//��Ч
	if(Config::getInstance( )->geteffectState( ))
	{
		SimpleAudioEngine::getInstance( )->pauseEffect(shoot_effect_id);
		SimpleAudioEngine::getInstance( )->playEffect( ship_explode_effect0 );
	}

	this->unschedule(schedule_selector(Ship::fire));

	this->removeFromParent( );
}
int Ship::hurt( int &_canHurt )
{
	return hp -= _canHurt;
}

Rect Ship::rect( )
{
	return Kit::getRect(this);
}

void Ship::fire(float dt )
{
	auto config = Config::getInstance( );


	auto shipPosition = this->getPosition( );
	auto dx = shipPosition.x;
	auto dy = shipPosition.y + 10;
	float offset = 0;

	auto type=config->getInstance( )->getBulletByType(0);

	// 1~3
	for(int i = 0; i != config->getShipBulletPower(); ++i)
	{
		//left
		auto bullet = Bullet::createBullet( type.canHurt
			, type.speedY,type.picName, type.ownType );
		bullet->setPosition( Vec2( dx -offset, dy ) );
		bullet->setScale( 1.2f );
		gameStage->addChild(bullet, BULLET_Z_ORDER );
		config->player_bullet_list->pushBack(bullet);

		//right
		bullet = Bullet::createBullet( type.canHurt
			, type.speedY, type.picName, type.ownType );
		bullet->setPosition(Vec2(dx +offset, dy));
		bullet->setScale( 1.2f );
		gameStage->addChild( bullet, BULLET_Z_ORDER );
		config->player_bullet_list->pushBack(bullet);
		offset += 10;
	}
}

Ship * Ship::creatShip( Node *gameStage, int shipType, int hp)
{
	auto ship = new Ship(gameStage, shipType, hp );
	if (ship&&ship->init())
	{
		ship->autorelease( );
		return ship;
	}
	delete ship;
	ship = NULL;
	return ship;
}

void Ship::stopFire( )
{
	this->unschedule( schedule_selector( Ship::fire ) );
}

