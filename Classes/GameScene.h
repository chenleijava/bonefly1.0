#ifndef _GAME_SCENE_HH_
#define  _GAME_SCENE_HH_
#include "Kit.h"
#include "GameLevelLayer.h"
#include "BaseSprite.h"

#include "Bullet.h"
#include "Ship.h"

#include "Enemy.h"

//”Œœ∑≥°÷˜≥°æ∞  
class GameScene:public Layer
{
public:

	GameScene( int levelNum );

	~GameScene( );

	virtual bool init( );

	//初始化资源pilst文件
	void initPlist( );
	//初始化特效
	void initEffect( );

	//app  maps
    void  addMap( const std::string &mapfilename );

	//onEnter move ship sprite
	virtual void onEnter( );

    virtual void onExit( );

	//更新游戏场景
	virtual void update( float dt );

	//
	static Scene* createScene( int levelNum );

	//碰撞检查
	bool isPeng(BaseSprite *a,BaseSprite *b );

	//初始化地图背景移动
	void initMoveMap(float dt );
	//背景地图滚动
	void moveMap( float dt );

	//更新 得分
    void updateScore( float dt );



    
	void checkPeng( float dt);


	//释放资源
	void releaseR( );

	//添加敌机
	void addEnemy(float dt );


    //根据等级获取对应的boos
	int getBoosByLevel( int levelNum);

    //ship是否重生

	void shipReBorn( );

private:

	int levelNum;//

	int levelScore;//

	Ship *ship;//player ship

	Sprite *mapSprite;//

	Sprite *tempMapSprite;//

	Label * lifeValue;//

	Label * score;// 

	std::string mapfilenames;
};
#endif //_GAME_SCENE_HH_


