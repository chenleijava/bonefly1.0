#include "GameOverLayer.h"


GameOverLayer::GameOverLayer( )
{
}

GameOverLayer::~GameOverLayer( )
{
}

bool GameOverLayer::init( )
{
	if (!Layer::init())
	{
		return true;
	}

	auto ui_over = Kit::createWithJsonFileInMac( ui_over_res );
	this->addChild( ui_over);

	//back to start scene
	auto btn_back = (Button*)Helper::seekWidgetByName( ui_over, "btn_back" );
	Widget::ccWidgetTouchCallback btn_back_call = [&](Ref* btn,Widget::TouchEventType eventType ){
		if (eventType==Widget::TouchEventType::ENDED)
		{
			if(Config::getInstance( )->geteffectState( ))
			{
				SimpleAudioEngine::getInstance( )->playEffect(btn_effect1);
			}
            
            if (Config::getInstance()->getmusicState()) {
                SimpleAudioEngine::getInstance()->stopBackgroundMusic();
            }
            
			Director::getInstance( )->replaceScene( TransitionFade::create( 1.2f, StartLayer::createScene( ) ) );
		}
	};
	btn_back->addTouchEventListener(btn_back_call);


	


	//retry to play game!!!
	auto btn_play_again = (Button*)Helper::seekWidgetByName( ui_over, "btn_play_again" );
	Widget::ccWidgetTouchCallback btn_play_again_call = [&]( Ref* btn, Widget::TouchEventType eventType ){
		if(eventType == Widget::TouchEventType::ENDED){
			log( "retry to play game!!!" );
			if(Config::getInstance( )->geteffectState( ))
			{
				SimpleAudioEngine::getInstance( )->playEffect( btn_effect1 );
			}
			Director::getInstance( )->replaceScene( TransitionMoveInL::create( 0.5f, GameLevelLayer::creatScene( ) ) );
		}
	};
	btn_play_again->addTouchEventListener( btn_play_again_call );
	


	//获取得分
	__String score="Score:";
	score.appendWithFormat("%03d", Config::getInstance( )->getScore( ) );
	auto _score_label = Label::createWithSystemFont(score.getCString( ),"Arial", 24 );
	auto position = VisibleRect::top( );
	_score_label->setPosition(Vec2(position.x,position.y-250));
	_score_label->setColor(Color3B::WHITE);
	this->addChild(_score_label );
	return true;
}

Scene* GameOverLayer::createScene( )
{
	auto _scene = Scene::create( );
	_scene->addChild(GameOverLayer::create());
	return _scene;

}

void GameOverLayer::onExit( )
{
	Layer::onExit( );
	this->removeAllChildrenWithCleanup( true );
	GUIReader::destroyInstance( );
}
