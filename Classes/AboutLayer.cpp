#include "AboutLayer.h"


AboutLayer::AboutLayer( )
{
}


AboutLayer::~AboutLayer( )
{

}

bool AboutLayer::init( )
{
	if (!Layer::init())
	{
		return false;
	}



	//����ui��Դ
	auto ui_about = GUIReader::getInstance( )->widgetFromJsonFile(ui_about_res);
	this->addChild( ui_about);

	//�ı� about
	auto about_text = (Text*)Helper::seekWidgetByName( ui_about, "about_text" );
	about_text->runAction(Kit::creatEaseSineInOut(200,255));



	//go back btn
	auto btn_back = (Button*)Helper::seekWidgetByName( ui_about, "btn_back" );
	btn_back->addTouchEventListener( [&]( Ref* btn, Widget::TouchEventType eventType ){
		if(eventType == Widget::TouchEventType::ENDED){
			if (Config::getInstance()->geteffectState())
			{
				SimpleAudioEngine::getInstance( )->playEffect(btn_effect1);
			}
			Director::getInstance( )->replaceScene( TransitionFade::create( 1.2f, StartLayer::creatScene( ) ) );
		}
	});

	Kit::addParticle(galaxy_plist, this, VisibleRect::rightBottom());


	return true;
}

Scene* AboutLayer::creatScene( )
{
	auto _scene = Scene::create( );
	_scene->addChild(AboutLayer::create());
	return _scene;
}

void AboutLayer::onExit( )
{
	Layer::onExit();
	this->removeAllChildrenWithCleanup( true );
	GUIReader::destroyInstance( );
}
