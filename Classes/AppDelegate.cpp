#include "AppDelegate.h"
#include "StartLayer.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}
bool AppDelegate::applicationDidFinishLaunching() {
   
    // initialize director
    auto pDirector = Director::getInstance();
    GLView *pEGLView = pDirector->getOpenGLView();
    if(!pEGLView) {
        pEGLView = GLView::create("雷电2014");
        pDirector->setOpenGLView(pEGLView);
    }
    

#if (CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
    
        pEGLView->setFrameSize(720, 1280);
    
#elif(CC_TARGET_PLATFORM==CC_PLATFORM_IOS||CC_TARGET_PLATFORM==CC_PLATFORM_MAC)
        
        pEGLView->setFrameSize(320,480);
#endif


    pEGLView->setDesignResolutionSize(320, 480, ResolutionPolicy::EXACT_FIT);
    
//    auto frameSize = pEGLView->getFrameSize();
//
//    // 设置 LsSize 固定值
//    auto lsSize = cocos2d::Size(320, 480);
//    
//    float scaleX = (float) frameSize.width / lsSize.width;
//    float scaleY = (float) frameSize.height / lsSize.height;
//    
//    // 定义 scale 变量
//    float scale = 0.0f; // MAX(scaleX, scaleY);
//    if (scaleX > scaleY) {
//        // 如果是 X 方向偏大，那么 scaleX 需要除以一个放大系数，放大系数可以由枞方向获取，
//        // 因为此时 FrameSize 和 LsSize 的上下边是重叠的
//        scale = scaleX / (frameSize.height / (float) lsSize.height);
//    } else {
//        scale = scaleY / (frameSize.width / (float) lsSize.width);
//    }
//    
//    log("x: %f; y: %f; scale: %f", scaleX, scaleY, scale);
//    
//    // 根据 LsSize 和屏幕宽高比动态设定 WinSize
//    pEGLView->setDesignResolutionSize(lsSize.width * scale,lsSize.height * scale, ResolutionPolicy::EXACT_FIT);
    
    

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
