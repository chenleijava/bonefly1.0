#ifndef _GAME_OVER_LAYER__
#define _GAME_OVER_LAYER__

#include "Kit.h"
#include "res.h"
#include "StartLayer.h"

class GameOverLayer:public Layer
{
public:
	GameOverLayer( );
	~GameOverLayer( );

	virtual bool init( );

	virtual void onExit( );

	CREATE_FUNC(GameOverLayer);
	static Scene* createScene( );
};
#endif

