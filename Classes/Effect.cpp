#include "Effect.h"


Effect::Effect( )
{
}


Effect::~Effect( )
{
}
Effect * Effect::CreateEffect( )
{
	auto effect = new Effect( );
	if(effect&&effect->init( ))
	{
		effect->autorelease( );
		return effect;
	}
	delete effect;
	effect = NULL;
	return effect;
}
void Effect::explosion( Node *gameStage, Vec2 pos, float scale )
{
	m_sprite = Sprite::createWithSpriteFrameName( "explosion_01.png" );
	m_sprite->setPosition( pos );
	gameStage->addChild(m_sprite);
	auto animation = AnimationCache::getInstance( )->getAnimation( "explosion" );
	//remove explosion
	const std::function<void( Node * sprite )> call_func = [&]( Node * sprite ){
		sprite->removeFromParent( );
	};
	animation->setRestoreOriginalFrame( true);
	m_sprite->setScale(scale );
	m_sprite->runAction(Sequence::create( Animate::create( animation ), CallFuncN::create(call_func), NULL ) );
}

void Effect::hit( Node *gameStage, Vec2 pos, float scale /*= 0.2f */ )
{
	m_sprite = Sprite::createWithSpriteFrameName( "explosion_01.png" );
	m_sprite->setPosition( pos );
	gameStage->addChild( m_sprite );
	auto animation = AnimationCache::getInstance( )->getAnimation( "explosion" );
	//remove explosion
	const std::function<void( Node * sprite )> call_func = [&]( Node * sprite ){
		sprite->removeFromParent( );
	};
	animation->setRestoreOriginalFrame( true );
	m_sprite->setScale( scale );
	m_sprite->runAction( Sequence::create( Animate::create( animation ), CallFuncN::create( call_func ), NULL ) );
}
