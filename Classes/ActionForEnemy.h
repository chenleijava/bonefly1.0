#ifndef _ACTION_FOR_ENEMY_HH
#define _ACTION_FOR_ENEMY_HH
#include "Kit.h"

class ActionForEnemy
{
public:

	ActionForEnemy( );
	~ActionForEnemy( );


	//************************************
	// Method:    MoveBy
	// FullName:  ActionForEnemy::MoveBy
	// Access:    public static 
	// Returns:   ActionInterval*
	// Qualifier:
	// Parameter: Vec2 * initPosition   base positon   ship 
	//************************************
	static ActionInterval* randMove( );

	//move x
	//************************************
	// Method:    CreateMoveByOfSequenceX
	// FullName:  ActionForEnemy::CreateMoveByOfSequenceX
	// Access:    public static 
	// Returns:   Sequence*
	// Qualifier:
	// Parameter: Vec2 & vec2  base positon
	//************************************
	static Sequence* CreateMoveByOfSequenceX( Vec2 vec2 );

	//move y
	//************************************
	// Method:    CreateMoveByOfSequenceY
	// FullName:  ActionForEnemy::CreateMoveByOfSequenceY
	// Access:    public static 
	// Returns:   Sequence*
	// Qualifier:
	// Parameter: Vec2 & vec2  base positon
	//************************************
	static Sequence* CreateMoveByOfSequenceY( Vec2 vec2 );



	//************************************
	// Method:    CreateBezier
	// FullName:  ActionForEnemy::CreateBezier
	// Access:    public static 
	// Returns:   Sequence*
	// Qualifier:  ������ƶ�����
	//************************************
	static Sequence*CreateBezierBy();

};
#endif


