#ifndef _START_LAYER_
#define _START_LAYER_

#include "Kit.h"
#include "res.h"
#include "OptionLayer.h"
#include "GameOverLayer.h"
#include "AboutLayer.h"
#include "GameLevelLayer.h"
#include "GameScene.h"
#include "VisibleRect.h"
#include "ListViewLayerTest.h"

class StartLayer:public Layer
{
public:
	StartLayer( );
	~StartLayer( );
	virtual bool init( );//
	CREATE_FUNC( StartLayer );//
    /**
    *
    *
    */
	static Scene *createScene( );

	virtual void onExit();

private:
	Widget *start_ui;// start  ui


	//typedef std::function<void(Ref*,Widget::TouchEventType)> ccWidgetTouchCallback;
	Widget::ccWidgetTouchCallback ui_start_call;
	Widget::ccWidgetTouchCallback ui_option_call;
	Widget::ccWidgetTouchCallback ui_exit_call;

	void releaseResource( );

};
#endif
