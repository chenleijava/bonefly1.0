#include "AppDelegate.h"
#include "StartLayer.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

//cocos2d-x 屏幕适配方案 ：
//http://www.tairan.com/archives/4809
bool AppDelegate::applicationDidFinishLaunching() {
   
    // initialize director
    auto pDirector = Director::getInstance();
    GLView *pEGLView = pDirector->getOpenGLView();
    if(!pEGLView) {
        pEGLView = GLView::create("雷电2014");
        pDirector->setOpenGLView(pEGLView);
    }
    

#if (CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
        //pEGLView->setFrameSize(720, 1280);
#elif(CC_TARGET_PLATFORM==CC_PLATFORM_MAC)
        //    debug
        pEGLView->setFrameSize(320.0f, 480.0f);
#endif

    
    /*
     Resources width 以下简写为RW，Resources height 以下简写为RH
     
     Design width 以下简写为DW，Design height 以下简写为DH
     
     Screen width 以下简写为SW，Screen height 以下简写为SH
     
     
     setContentScaleFactor()通常有两个方式来设置参数。
     RH/DH或RW/DW，不同的因子选择有不同的缩放负作用。
     用高度比作为内容缩放因子，保证了背景资源的垂直方向在设计分辨率范围内的全部显示。
     用宽度比作为内容缩放因子，保证了背景资源的水平方向在设计分辨率范围内的全部显示。
     
     
     //设计分辨率宽，设计分辨率高，分辨率策略。
     setDesignResolutionSize(DW, DH, resolutionPolicy)
     
     
     
     
     
     */
    //void GLViewProtocol::updateDesignResolutionSize()
    //DW ,DH, 分辨率策略-->SW/DW  SH/DH
    pEGLView->setDesignResolutionSize(320,480, ResolutionPolicy::NO_BORDER);
    
    

	// turn off display FPS
	pDirector->setDisplayStats( true );

	// set FPS. the default value is 1.0/60 if you don't call this
	pDirector->setAnimationInterval( 1.0 / 60 );

	pDirector->setProjection( Director::Projection::_2D );


	//loading music and btn effect
	auto simpla_audio = SimpleAudioEngine::getInstance( );
	simpla_audio->preloadBackgroundMusic( main_bg_stage1 );

	//btn effect
	simpla_audio->preloadEffect( btn_effect1 );

	simpla_audio->setBackgroundMusicVolume( 1.0f );
	simpla_audio->setEffectsVolume( 0.5f );
    

	if(Config::getInstance( )->getmusicState( ))
	{
		simpla_audio->playBackgroundMusic( main_bg_stage1, true );
	}

    /**
     预处理加载音效 背景音乐等
     */
    

	// create a scene. it's an autorelease object
	//auto pScene = StartMenu::scene( );
	auto pScene = StartLayer::creatScene( );

	// run
	pDirector->runWithScene( pScene );

	return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
//if  music or effect is on status will take action ;
void AppDelegate::applicationDidEnterBackground( ) {
	Director::getInstance( )->stopAnimation( );
	auto _simple = SimpleAudioEngine::getInstance( );
	if (Config::getInstance()->getmusicState())//status on,play  will stop
		_simple->pauseBackgroundMusic( );
	if(Config::getInstance( )->geteffectState( ))_simple->pauseAllEffects( );
}

// this function will be called when the app is active again
//if  music or effect is on status will take action ;
void AppDelegate::applicationWillEnterForeground( ) {
	Director::getInstance( )->startAnimation( );
	auto _simple = SimpleAudioEngine::getInstance( );
	if(Config::getInstance( )->getmusicState( ))_simple->resumeBackgroundMusic( );//playe status ,wiil resume it
	if(Config::getInstance( )->geteffectState( ))_simple->resumeAllEffects( );//playe status ,wiil resume it
		
}
