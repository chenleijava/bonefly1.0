#include "GameLevelLayer.h"

GameLevelLayer::GameLevelLayer( ) 
{
}


GameLevelLayer::~GameLevelLayer( )
{
}

bool GameLevelLayer::init( )
{
	if(!Layer::init( ))return false;


	log( "page turning and  page index:%ld", Config::getInstance()->LevelNum() );

    /*auto node=SceneReader::getInstance( )->createNodeWithSceneFile( ui_level_res );
     this->addChild(node);*/


	auto ui_level = Kit::createWithJsonFileInMac( ui_level_res );

    
    this->addChild( ui_level );

	//register  level btn ,and run scene of  game  
	auto beginGame = (Button*)Helper::seekWidgetByName( ui_level, "beginGame" );

	beginGame->addTouchEventListener( [&]( Ref * btn, Widget::TouchEventType eventType ){
		if(eventType == Widget::TouchEventType::ENDED)
		{
			log( "begain to channel level %ld ... ...", Config::getInstance( )->LevelNum( ) );
			if(Config::getInstance( )->geteffectState( ))
			{
				SimpleAudioEngine::getInstance( )->playEffect( btn_effect1 );
			}
            
            if (Config::getInstance( )->getmusicState()) SimpleAudioEngine::getInstance()->stopBackgroundMusic(main_bg_stage1);
            
			Director::getInstance( )->replaceScene( TransitionFade::create( 1.2f, GameScene::createScene( Config::getInstance( )->LevelNum( ) ) ) );
		}
	} );



	//return to startLayer and run scene
	auto ui_back_start_call = [&]( Ref *, Widget::TouchEventType type ){
		if(type == Widget::TouchEventType::BEGAN)
		{
            auto config=Config::getInstance();
			if(config->geteffectState( ))
			{
				SimpleAudioEngine::getInstance( )->playEffect( btn_effect1 );
			}
          
            
			log( "return to startLayer and run scene ... ..." );
			Director::getInstance( )->replaceScene( TransitionFade::create( 1.2f, StartLayer::createScene( ) ) );
		}
	};
	auto btn_back_start = (Button*)Helper::seekWidgetByName( ui_level, "btn_back" );
	btn_back_start->addTouchEventListener( ui_back_start_call );


	//get page view
	auto levelpageviews = (PageView*)Helper::seekWidgetByName( ui_level, "level_page" );
	
	
    levelpageviews->scrollToPage(Config::getInstance( )->LevelNum( ) );
    
    levelpageviews->setTouchEnabled(true);

	//滑动关卡
	levelpageviews->addEventListener( [&]( Ref* levelpageviews, PageView::EventType pageType ){
		if(pageType == PageView::EventType::TURNING)
		{
			auto pageVies = (PageView*)levelpageviews;
			Config::getInstance( )->LevelNum( pageVies->getCurPageIndex( ) );
			log( "page turning and  page index:%ld", Config::getInstance( )->LevelNum() );
		}
	}
	);


	Kit::addParticle(galaxy_plist, this, VisibleRect::leftTop());

	return true;

}

Scene* GameLevelLayer::creatScene( )
{
	auto _scene = Scene::create( );
	_scene->addChild( GameLevelLayer::create( ) );
	return _scene;
}


void GameLevelLayer::onExit( )
{
	Layer::onExit( );
	this->removeAllChildrenWithCleanup( true);
	GUIReader::destroyInstance( );
}
