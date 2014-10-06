#include "OptionLayer.h"


OptionLayer::OptionLayer( ) :ui_option(NULL)
{
}

OptionLayer::~OptionLayer( )
{
	
}

bool OptionLayer::init( )
{
	if (!Layer::init())
	{
		return false;
	}
	//��ʼ��ui
	ui_option = GUIReader::getInstance( )->widgetFromJsonFile(ui_option_res);
	this->addChild(ui_option );

	//init call back fun and  register touch event lister
	ui_music_call = [&](Ref * btn,Widget::TouchEventType type ){
		if(type == Widget::TouchEventType::ENDED)
		{
			auto _btn = static_cast<Button*>(btn);
			log( "chage muscis option... ..." );
			if(_btn->isBright( ) && Config::getInstance( )->getmusicState())
			{
				_btn->setBright( false );
				SimpleAudioEngine::getInstance( )->pauseBackgroundMusic( );
				Config::getInstance( )->setmusicState(false);
			}else{
				Config::getInstance( )->setmusicState( true );
				_btn->setBright( true );
				SimpleAudioEngine::getInstance( )->resumeBackgroundMusic( );
			}

		}
	};
	auto btn_music = (Button*)Helper::seekWidgetByName( ui_option, "btn_music" );
	btn_music->addTouchEventListener(ui_music_call );
	//music not play
	if (!Config::getInstance()->getmusicState())
	{
		btn_music->setBright( false );
	}


	ui_effect_call = [&]( Ref *btn, Widget::TouchEventType type ){
		if(type == Widget::TouchEventType::ENDED)
		{
			log( "chage effect option... ..." );
			auto _btn = static_cast<Button*>(btn);
			if(_btn->isBright( )&&Config::getInstance()->geteffectState())
			{
				_btn->setBright( false );
				SimpleAudioEngine::getInstance( )->pauseAllEffects( );
				Config::getInstance( )->seteffectState( false );
			}
			else{
				_btn->setBright( true );
				SimpleAudioEngine::getInstance( )->resumeAllEffects( );
				Config::getInstance( )->seteffectState( true );
			}
		}
	};
	auto btn_effect = (Button*)Helper::seekWidgetByName( ui_option, "btn_effect" );
	btn_effect->addTouchEventListener( ui_effect_call );
	//effect is forbide
	if (!Config::getInstance()->geteffectState())
	{
		btn_effect->setBright( false );
	}


	//return to startLayer and run scene
	ui_back_start_call = [&]( Ref *, Widget::TouchEventType type ){
		if(type == Widget::TouchEventType::ENDED)
		{
			if(Config::getInstance( )->geteffectState( ))
			{
				SimpleAudioEngine::getInstance( )->playEffect( btn_effect1 );
			}
			log( "return to startLayer and run scene ... ..." );
			Director::getInstance( )->replaceScene( TransitionFade::create( 1.2f, StartLayer::creatScene( ) ) );
		}
	};
	auto btn_back_start = (Button*)Helper::seekWidgetByName( ui_option, "btn_back" );
	btn_back_start->addTouchEventListener( ui_back_start_call );

	//add particle
	Kit::addParticle(galaxy_plist, this, VisibleRect::rightBottom());

	return  true;

}

Scene * OptionLayer::creatScene( )
{
	auto _scene = Scene::create( );
	_scene->addChild(OptionLayer::create() );
	return _scene;
}

void OptionLayer::onExit()
{
	Layer::onExit();
	this->removeAllChildrenWithCleanup(true);
	GUIReader::destroyInstance();
}