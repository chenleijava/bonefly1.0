#ifndef _GAME_LEVEL_LAYER_H
#define _GAME_LEVEL_LAYER_H
#include "Kit.h"
#include "res.h"
#include "StartLayer.h"
#include "Config.h"
#include "GameScene.h"

//enum game map ,in order to create game scene
enum  GAMEMAP{
	NONE,
	GAMEMAP1 = 0,
	GAMEMAP2,
	GAMEMAP3,
	GAMEMAP4
};
class GameScene;

class GameLevelLayer:public Layer
{
public:
	GameLevelLayer();

	~GameLevelLayer( );
	
	virtual bool init( );

	virtual void  onExit( );

	CREATE_FUNC(GameLevelLayer );

	static Scene* creatScene( );

};
#endif
