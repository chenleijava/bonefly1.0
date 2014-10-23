#include "StartLayer.h"

#ifndef DEV 
#define DEV 1
#endif

StartLayer::StartLayer( ) :start_ui(NULL)
{
}

StartLayer::~StartLayer( )
{

}

bool StartLayer::init( )
{
	if (!Layer::init())
	{
		return false;
	}

	//init ui
    start_ui = Kit::createWithJsonFileInMac( ui_start_res );
	this->addChild(start_ui);

   
    
	//get btn and init call back fun, and then  register it
	ui_start_call = [&]( Ref*, Widget::TouchEventType event_type){
		if(event_type==Widget::TouchEventType::ENDED)
		{
			if (Config::getInstance()->geteffectState())
			{
				SimpleAudioEngine::getInstance( )->playEffect( btn_effect1 );
			}

			log( "call back start button..." );
			Director::getInstance( )->replaceScene( TransitionFade::create( 1.2f, GameLevelLayer::creatScene( ) ) );
		}
		
	};
	auto btn_start = static_cast<Button*>(Helper::seekWidgetByName(start_ui,"btn_start"));
	btn_start->addTouchEventListener(ui_start_call );


	//setting btn and call func
	ui_option_call = [&]( Ref*, Widget::TouchEventType event_type ){
		if(event_type == Widget::TouchEventType::ENDED)
		{
			if(Config::getInstance( )->geteffectState( ))
			{
				SimpleAudioEngine::getInstance( )->playEffect( btn_effect1 );
			}
			log( "call back option button..." );
			Director::getInstance( )->replaceScene( TransitionFade::create( 1.2f, OptionLayer::createScene() ) );
		}
	};
	auto btn_option = static_cast<Button*>(Helper::seekWidgetByName( start_ui, "btn_option" ));
	btn_option->addTouchEventListener( ui_option_call );

	
	//exit btn
	ui_exit_call = [&]( Ref*, Widget::TouchEventType event_type  ){
		if(event_type == Widget::TouchEventType::ENDED)
		{
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
			exit(0);	
#endif
#if DEV
            Director::getInstance( )->replaceScene( TransitionFade::create( 1.2f, ListViewLayerTest::creatScene() ) );
#else
			Director::getInstance( )->end( );
#endif

		}
	};
	auto btn_exit = static_cast<Button*>(Helper::seekWidgetByName( start_ui, "btn_exit" ));
	btn_exit->addTouchEventListener( ui_exit_call );

    
    

    //关于
	auto text_about = static_cast<TextField*>(Helper::seekWidgetByName( start_ui, "text_about" ));
	text_about->addTouchEventListener( [&]( Ref*, Widget::TouchEventType event_type ){
		if (event_type==Widget::TouchEventType::ENDED)
		{
			log("about ....." );
			if(Config::getInstance( )->geteffectState( ))
			{
				SimpleAudioEngine::getInstance( )->playEffect( btn_effect1 );
			}
			Director::getInstance( )->replaceScene(TransitionFade::create(1.2f,AboutLayer::creatScene()) );
		}
	} );




	Kit::addParticle(snow_plist, this, VisibleRect::top());

	Kit::addParticle(ship_tail_particle_plist, this, Vec2(55,3));

	return true;
}

Scene * StartLayer::createScene( )
{
	auto _scene = Scene::create( );
	auto _start_layer = StartLayer::create( );
	_scene->addChild(_start_layer );
	return _scene;
}

void StartLayer::releaseResource( )
{
	this->removeChild(start_ui);

}

void StartLayer::onExit()
{
	Layer::onExit();
	this->removeAllChildrenWithCleanup(true);
	GUIReader::destroyInstance();
}


