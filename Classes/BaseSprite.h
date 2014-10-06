#ifndef BASE_SPRITE_H
#define  BASE_SPRITE_H

#include "Kit.h"



class BaseSprite :public Sprite
{
public:
	BaseSprite( );

	~BaseSprite( );

    //destory ship
	virtual void destory( ){};
    
    //碰撞 伤害
	virtual int hurt( int &canHurt ) = 0;
    

    //获取精灵的碰撞区域（矩形）
    virtual cocos2d::Rect rect( )=0;
};
#endif

