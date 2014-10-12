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

    /**
     @Author 石头哥哥, 14-10-09 20:10:26
     
     @brief  销毁ship
     
     @param  description
     
     @since version number
     */
	virtual void destory( );
	
    /**
     @Author 石头哥哥 14-10-09 20:10:03
     
     @brief  <#Description#>
     
     @param _canHurt <#_canHurt description#>
     
     @return <#return value description#>
     
     @since <#version number#>
     */
	virtual int hurt( int &_canHurt );


    /**
     @Author 石头哥哥, 14-10-09 20:10:36
     
     @brief  ship fire
     
     @param dt dt time
     
     @since <#version number#>
     */
	void fire( float dt );

    /**
     @Author 石头哥哥, 14-10-09 20:10:09
     
     @brief  碰撞矩形区域
     
     @param  <# description#>
     
     @return <#return value description#>
     
     @since <#version number#>
     */

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