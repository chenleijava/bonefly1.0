#include "ActionForEnemy.h"


#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wincompatible-pointer-types"
ActionForEnemy::ActionForEnemy( )
{
}


ActionForEnemy::~ActionForEnemy( )
{
}


Sequence* ActionForEnemy::CreateMoveByOfSequenceX( Vec2 vec2 )
{
	auto temp = MoveBy::create( 1.2f, Vec2( vec2.x, 0 ) );
	return Sequence::create(temp, temp->reverse( ), NULL );
}

Sequence* ActionForEnemy::CreateMoveByOfSequenceY( Vec2 vec2 )
{
	auto temp = MoveBy::create( 1.2f, Vec2( 0, vec2.y ) );
	return Sequence::create(temp, temp->reverse( ), NULL );
}

ActionInterval* ActionForEnemy::randMove(  )
{
	return MoveBy::create( 1.2f, Vec2( 0, 300 ) );
}

//typedef struct _ccBezierConfig {
//	//! end position of the bezier
//	Vec2 endPosition;
//	//! Bezier control point 1
//	Vec2 controlPoint_1;
//	//! Bezier control point 2
//	Vec2 controlPoint_2;
//} ccBezierConfig;
Sequence* ActionForEnemy::CreateBezierBy()
{
    auto winsize =Director::getInstance()->getWinSize();
	ccBezierConfig bezier;
	bezier.controlPoint_1 = Vec2(0, winsize.height / 2);
	bezier.controlPoint_2 = Vec2(300, -winsize.height / 2);
	bezier.endPosition = Vec2(100,0);

	auto bezierForward = BezierBy::create(5.0f, bezier);//can reverse
	auto bezierBack = bezierForward->reverse();
	return Sequence::create(bezierForward, bezierBack, nullptr);
}

#pragma clang diagnostic pop