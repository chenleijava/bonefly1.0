#ifndef _SHIP_H_
#define _SHIP_H_


#include "BaseSprite.h"
#include "Config.h"
#include "Bullet.h"
#include "res.h"


class Ship :public BaseSprite
{
public:

	//************************************
	// Method:    Ship
	// FullName:  Ship::Ship
	// Access:    public 
	// Returns:   
	// Qualifier:
	// Parameter: Node * gameStage
	// Parameter: int shipType
	// Parameter: int hp
	//************************************
	Ship(Node *gameStage, int shipType,int hp);

	~Ship( );

	virtual bool init( );
	//Ïú»Ù
	virtual void destory( );
	
	virtual int hurt( int &_canHurt );

	//ship fire
	void fire( float dt );


	virtual Rect rect( );


	void stopFire( );

	int Hp( ) const {
		return hp;
	}

	 //************************************
	 // Method:    creatShip
	 // FullName:  Ship::creatShip
	 // Access:    public static 
	 // Returns:   Ship *
	 // Qualifier:
	 // Parameter: Node * gameStage
	 // Parameter: int shipType
	 // Parameter: int hp
	 //************************************
	static Ship * creatShip( Node *gameStage, int shipType, int hp );

private:
	Node *gameStage;
	int shipType;
	int hp;

	int shoot_effect_id;

};
#endif