#include "Kit.h"

Kit::Kit(){}


Kit::~Kit(){}




/*
 加载cocosstudio 导出的 json文件
 NodeReader::getInstance()
 
 */
Widget* Kit::createWithJsonFileInMac(const std::string& filename){
     return (Widget*)NodeReader::getInstance()->createNode(filename);
}

/**
 加载cocosstudio 导出的 json文件
 GUIReader::getInstance()
 */
Widget* Kit::createWithJsonFile(const std::string& filename){
    return (Widget*)GUIReader::getInstance()->widgetFromBinaryFile(filename.c_str());
}


Animation * Kit::createAnimation_1(const char *fmt, int count, std::string plist, float fps /*= 0.0f*/, std::string animationName /*= ""*/, bool _cache /*= false */)
{
    //cocos vector
    Vector<SpriteFrame*> _vectorArray;
    char png[100] = { 0 };
    auto _SpriteFrameCache = SpriteFrameCache::getInstance();
    if (!plist.empty())
	{
		_SpriteFrameCache->addSpriteFramesWithFile(plist);
	}
	for (int i = 1; i != count; ++i)
	{
		sprintf(png, fmt, i);
		log("%s", png);
		auto _spriteFrame = _SpriteFrameCache->getSpriteFrameByName(png);
		_vectorArray.pushBack(_spriteFrame);//push back  ,retain
	}

	auto _animation = Animation::createWithSpriteFrames(_vectorArray, 1 / fps);
	_vectorArray.clear();
	if (_cache&&!animationName.empty())
	{
		AnimationCache::getInstance()->addAnimation(_animation, animationName);
	}
	return _animation;
}
//************************************
// Method:    createAnimation
// FullName:  Kit::createAnimation
// Access:    public static 
// Returns:   Animation *
// Qualifier:
// Parameter: const char * fmt
// Parameter: int count
// Parameter: float fps
// Parameter: std::string animationName
// Parameter: bool _cache
//************************************
Animation * Kit::createAnimation(const char *fmt, int count, std::string plist, float fps /*= 0.0f*/, std::string animationName /*= ""*/, bool _cache /*= false */)
{

	//cocos vector
	Vector<SpriteFrame*> _vectorArray;
	char png[100] = { 0 };
	auto _SpriteFrameCache = SpriteFrameCache::getInstance();
	if (!plist.empty())
	{
		_SpriteFrameCache->addSpriteFramesWithFile(plist);
	}

	for (int i = 0; i != count; ++i)
	{
		sprintf(png, fmt, i);
		//png = String::createWithFormat( fmt, i )->getCString( );
		log("%s", png);
		auto _spriteFrame = _SpriteFrameCache->getSpriteFrameByName(png);
		_vectorArray.pushBack(_spriteFrame);//push back  ,retain
	}

	auto _animation = Animation::createWithSpriteFrames(_vectorArray, 1 / fps);
	_vectorArray.clear();
	if (_cache&&!animationName.empty())
	{
		AnimationCache::getInstance()->addAnimation(_animation, animationName);
	}
	return _animation;


}
Animation * Kit::createAnimation_1(const char *fmt, int count, float fps /*= 0.0f*/, std::string animationName /*= ""*/, bool _cache /*= false */)
{
	//cocos vector
	Vector<SpriteFrame*> _vectorArray;
	//const char* png;
	auto _SpriteFrameCache = SpriteFrameCache::getInstance();
	char png[100] = { 0 };
	for (int i = 1; i != count; ++i)
	{
		sprintf(png, fmt, i);
		//png = String::createWithFormat(fmt, i )->getCString( );
		log("%s", png);
		auto _spriteFrame = _SpriteFrameCache->getSpriteFrameByName(png);
		_vectorArray.pushBack(_spriteFrame);//push back  ,retain
	}

	auto _animation = Animation::createWithSpriteFrames(_vectorArray, 1 / fps);
	_vectorArray.clear();
	if (_cache&&!animationName.empty())
	{
		AnimationCache::getInstance()->addAnimation(_animation, animationName);
	}
	return _animation;
}

//************************************
// Method:    createAnimation
// FullName:  Kit::createAnimation
// Access:    public static 
// Returns:   Animation *
// Qualifier:
// Parameter: const char * fmt
// Parameter: int count
// Parameter: float fps
// Parameter: std::string animationName
// Parameter: bool _cache
//************************************
Animation * Kit::createAnimation(const char *fmt, int count, float fps /*= 0.0f*/, std::string animationName /*= ""*/, bool _cache /*= false */)
{
	//cocos vector
	Vector<SpriteFrame*> _vectorArray;
	char png[100] = { 0 };
	auto _SpriteFrameCache = SpriteFrameCache::getInstance();

	for (int i = 0; i != count; ++i)
	{
		sprintf(png, fmt, i);
		//png = String::createWithFormat( fmt, i )->getCString( );
		log("%s", png);
		auto _spriteFrame = _SpriteFrameCache->getSpriteFrameByName(png);
		_vectorArray.pushBack(_spriteFrame);//push back  ,retain
	}

	auto _animation = Animation::createWithSpriteFrames(_vectorArray, 1 / fps);
	_animation->setRestoreOriginalFrame(true);//Return to the 1st frame after the (count-1) th frame is played. 
	_vectorArray.clear();
	if (_cache&&!animationName.empty())
	{
		AnimationCache::getInstance()->addAnimation(_animation, animationName);
	}
	return _animation;
}



ActionInterval * Kit::creatEaseSineInOut(GLubyte opacity0, GLubyte opacity1)
{
	//…Ë÷√Õ∏√˜∂»±‰ªØ  80---255
	auto fadeinlight = FadeTo::create(1.5f, opacity0);
	auto fadeinDepth = FadeTo::create(1.5f, opacity1);
	//¥¥Ω®µ≠Ω¯–ßπ˚
	auto easeIn = EaseSineInOut::create(fadeinlight);
	auto easeOut = EaseSineInOut::create(fadeinDepth);
	return RepeatForever::create(Sequence::create(easeIn, easeOut, NULL));
}

//«Â¿Ì∂Øª≠ª∫¥Ê£¨»ª∫Û«Â¿Ìæ´¡È÷°ª∫¥Ê£¨◊Ó∫Û «Œ∆¿Ìª∫¥Ê°£∞¥’’“˝”√≤„º∂”…∏ﬂµΩµÕ£¨“‘±£÷§ Õ∑≈“˝”√”––ß°£
void Kit::releaseCaches()
{
	AnimationCache::destroyInstance();
	SpriteFrameCache::getInstance()->removeUnusedSpriteFrames();
	Director::getInstance()->getTextureCache()->removeUnusedTextures();
}

//ªÒ»°∂‘œÛµƒŒ∆¿Ìæÿ–Œ«¯”Ú---◊¢“‚√™µ„µƒ”∞œÏ
Rect Kit::getRect(Node *node, float w, float h)
{
	auto sprite_size = node->getContentSize();
	auto sprite_point = node->getPosition();
	auto ap_sprite_point = node->getAnchorPoint();
	return Rect(sprite_point.x - ap_sprite_point.x*sprite_size.width,
		sprite_point.y - ap_sprite_point.y*sprite_size.height, sprite_size.width - w, sprite_size.height - h);
}

cocos2d::Label* Kit::creatWithTTf(const char* filePath, int size, const std::string& text)
{
	TTFConfig ttfConfig(filePath, size);
	return Label::createWithTTF(ttfConfig, text);
}

//icove
//int Kit::code_convert(const char *from_charset, const char *to_charset, const char *inbuf, size_t inlen, char *outbuf, size_t outlen)
//{
//	iconv_t cd;
//	const char *temp = inbuf;
//	const char **pin = &temp;
//	char **pout = &outbuf;
//	memset(outbuf, 0, outlen);
//	cd = iconv_open(to_charset, from_charset);
//	if (cd == 0) return -1;
//	if (iconv(cd, pin, &inlen, pout, &outlen) == -1) return -1;
//	iconv_close(cd);
//	return 0;
//}
//
//
///*UTF8 To GB2312*/
//string  Kit::utf2gb(const char *inbuf)
//{
//	size_t inlen = strlen(inbuf);
//	char * outbuf = new char[inlen * 2 + 2];
//	std::string strRet;
//	if (code_convert("utf-8", "gb2312", inbuf, inlen, outbuf, inlen * 2 + 2) == 0)
//	{
//		strRet = outbuf;
//	}
//	delete[] outbuf;
//	outbuf = NULL;
//	return strRet;
//}
//
//string  Kit::gb2utf8(const char *inbuf)
//{
//	size_t inlen = strlen(inbuf);
//	char * outbuf = new char[inlen * 2 + 2];
//	string strRet;
//	if (code_convert("gb2312", "utf-8", inbuf, inlen, outbuf, inlen * 2 + 2) == 0)
//	{
//		strRet = outbuf;
//	}
//	delete[] outbuf;
//	outbuf = NULL;
//	return strRet;
//}

Widget* Kit::getWidget(Widget *root, std::string &widgetName)
{
	return Helper::seekWidgetByName(root, widgetName);
}

SimpleAudioEngine * Kit::getAudio()
{
	return SimpleAudioEngine::getInstance();
}
void Kit::preloadMusicAndEffect(char* files, bool music)
{
	if (music)
	{
		getAudio()->preloadBackgroundMusic(files);
	}
	else
	{
		getAudio()->preloadEffect(files);
	}
}

void Kit::playMusic(char *music_file_name, bool loop)
{
	getAudio()->playBackgroundMusic(music_file_name, loop);
}

void Kit::stopMusic(bool releaseData)
{
	getAudio()->stopBackgroundMusic(releaseData);
}

void Kit::playEffect(char *effect_file_name)
{
	getAudio()->playEffect(effect_file_name);
}

void Kit::stopEffect(int n_soudID)
{
	getAudio()->stopEffect(n_soudID);
}

void Kit::pauseAllEffect()
{
	getAudio()->pauseAllEffects();
}


void Kit::addParticle(const std::string& filename, Node *node, Vec2 position, ActionInterval *action)
{
	auto paticle = ParticleSystemQuad::create(filename);
	paticle->setPosition(position);//set position
	if (action!=NULL)
	{
		paticle->runAction(RepeatForever::create(action));
	}
	auto particleBatch = ParticleBatchNode::createWithTexture(paticle->getTexture());//loading texture
	particleBatch->addChild(paticle);// add batch node
	node->addChild(particleBatch);//may be can remove it  
}

int Kit::rnd(int min, int max)
{
	return min + rand() % (max + 1);
}






