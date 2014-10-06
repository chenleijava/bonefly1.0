#include "Bullet.h"
#include "Effect.h"
//NONE -1
Bullet::Bullet( int canHurt, int speedY, std::string bulletType, int ownType ) :canHurt( canHurt ), speedX( 0 ), speedY( speedY ), bulletType( bulletType ), bulletOwn( ownType ), _active( false ), outofVisible( 0 )
{

}

Bullet::~Bullet( ){
	
}


bool Bullet::init( )
{
	if(!Sprite::init( ))
	{
		return false;
	}
	//active bullet
	_active = true;
	if(bulletOwn == BULLEOWN::PLAYER_BULLET)
	{
		// up fire
		outofVisible = Director::getInstance( )->getVisibleSize( ).height + 100;
	}
	if(bulletOwn == BULLEOWN::ENEMY_BULLET)
	{
		//down fire
		outofVisible = -(Director::getInstance( )->getVisibleSize( ).height + 100);
	}
	if(outofVisible == 0)
	{
		log( "init bullet outofVisible error!!! " );
		return false;
	}
	//创建子弹精灵
	this->initWithSpriteFrameName(bulletType);
	return true;
}

//创建游戏中的子弹对象
Bullet* Bullet::createBullet( int canHurt, int speed, std::string bulletType, int ownType )
{
	auto bullet = new Bullet( canHurt, speed, bulletType, ownType );
	if(bullet&&bullet->init( ))
	{
		bullet->autorelease( );//add to release pool
		return bullet;
	}
	delete bullet;
	bullet = NULL;
	return NULL;
}

//外部调用更新
void Bullet::update( float dt ){
	if(_active)
	{
		auto position = this->getPosition( );
		float dx = position.x - speedX*dt;//横向  0
		float dy = position.y - speedY*dt;//纵向射击   
		this->setPosition( Vec2( dx, dy ) );
	}
}

void Bullet::destory( Node *gameStage )
{

	this->_active = false;
	this->removeFromParent();
}

//返回子弹可以造成的伤害
int Bullet::hurt( int &_canHurt ){
	return canHurt;
}

// if peng ,will call back destory
Rect Bullet::rect( )
{
	return Kit::getRect(this );
}

void Bullet::boneDestory()
{
	this->_active = false;
	this->removeFromParent();
}

