#ifndef _GAME_SCENE_HH_
#define  _GAME_SCENE_HH_
#include "Kit.h"
#include "GameLevelLayer.h"
#include "BaseSprite.h"

#include "Bullet.h"
#include "Ship.h"

#include "Enemy.h"

//游戏场主场景  
class GameScene:public Layer
{
public:

	GameScene( int levelNum );

	~GameScene( );

	virtual bool init( );

	//初始化游戏资源
	void initPlist( );
	//初始化特效资源 爆炸 闪光 特效
	void initEffect( );

	//添加游戏场景
    void  addMap( const std::string &mapfilename );

	//onEnter move ship sprite
	virtual void onEnter( );

    virtual void onExit( );

	//游戏中刷新场景定时器
	virtual void update( float dt );

	//创建游戏场景
	static Scene* createScene( int levelNum );

	//检查对象是否碰撞
	bool isPeng(BaseSprite *a,BaseSprite *b );

	//初始化移动地图
	void initMoveMap(float dt );
	//移动地图
	void moveMap( float dt );

	//更新分数 
	void updateScore( float dt );


	//************************************
	// Method:    checkPeng
	// FullName:  GameScene::checkPeng
	// Access:    public 
	// Returns:   void
	// Qualifier:  检查碰撞  更新状态
	// Parameter: float dt
	//************************************
	void checkPeng( float dt);


	//清理当前层中的资源
	void releaseR( );

	//根据关卡类型添加相应的敌机
	void addEnemy(float dt );


	int getBoosByLevel( int levelNum);


	void shipReBorn( );

private:

	int levelNum;//关卡编号

	int levelScore;//关卡要求BOOS的分数

	Ship *ship;//player ship

	Sprite *mapSprite;//游戏地图  用于滚动加载

	Sprite *tempMapSprite;//游戏地图  用于滚动加载

	Label * lifeValue;//player生命值

	Label * score;//玩家得分  

	std::string mapfilenames;
};
#endif //_GAME_SCENE_HH_


