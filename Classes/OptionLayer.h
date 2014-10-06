#ifndef _OPTION_LAYER_
#define _OPTION_LAYER_
#include "Kit.h"
#include "res.h"
#include "StartLayer.h"
#include "Config.h"
class OptionLayer:public Layer
{
public:
	OptionLayer( );
	~OptionLayer( );


	virtual bool init( );
	static Scene *creatScene( );
	CREATE_FUNC(OptionLayer );

	virtual void onExit();


private:
	Widget * ui_option;//ui

	//using std::function<void(Ref*,Widget::CCTouchEventType *)> cc_touch
	//ui callback func
	Widget::ccWidgetTouchCallback ui_music_call;
	Widget::ccWidgetTouchCallback ui_effect_call;
	Widget::ccWidgetTouchCallback ui_vidio_call;
	Widget::ccWidgetTouchCallback ui_back_start_call;

};
#endif //_OPTION_LAYER_

