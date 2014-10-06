#ifndef _ABOUT_HH__
#define _ABOUT_HH__
#include "Kit.h"
#include "res.h"
#include "StartLayer.h"
#include "Config.h"

class AboutLayer:public Layer
{
public:
	AboutLayer( );
	~AboutLayer( );

	virtual bool init( );

	virtual void onExit( );

	CREATE_FUNC(AboutLayer);

	static Scene* creatScene( );
};
#endif

