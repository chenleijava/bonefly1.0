#ifndef   __KIT_HH_
#define   __KIT_HH_
#include "cocos2d.h"
#include <string>
//#if(CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID||CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
//#include "../cocos2d/iconv/include/iconv.h"
//#else
//#include "iconv.h"
//#endif
#include "VisibleRect.h"
using namespace std;
USING_NS_CC;

//UI  studio
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
using namespace cocostudio;
using namespace cocos2d::ui;



//music and effect
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

USING_NS_CC;


class Kit
{
public:
	Kit( );

	~Kit( );
	//http://tool.oschina.net/commons?type=3  RGB ���ձ�

	//************************************
	// Method:    createAnimation
	// FullName:  Kit::createAnimation
	// Access:    public static 
	// Returns:   Animation *
	// Qualifier:  ����״̬�����ķ���
	// Parameter: const char * fmt  ״̬��ͼƬ����ʽ(�鿴pd_sprites.plist							ÿ��״̬��ʽ������hero_idle_xx.png)
	// Parameter: int count ״̬ͼƬ���е�����
	// Parameter: float fps �����Ĳ���֡��
	// %02d ����ʾ���2λ���� ������� 0   00.png
	// %03d ����ʾ���3λ���� ������� 0   000.png
	//************************************
	static Animation *createAnimation( const char *fmt, int count, float fps = 0.0f, std::string animationName = "", bool _cache = false );


	//************************************
	// Method:    createAnimation_1
	// FullName:  Kit::createAnimation_1
	// Access:    public static 
	// Returns:   Animation *
	// Qualifier:
	// Parameter: const char * fmt
	// Parameter: int count
	// Parameter: float fps
	// Parameter: std::string animationName
	// Parameter: bool _cache
	//************************************
	static Animation *createAnimation_1( const char *fmt, int count, float fps = 0.0f, std::string animationName = "", bool _cache = false );


	//************************************
	// Method:    createAnimation
	// FullName:  Kit::createAnimation
	// Access:    public static 
	// Returns:   Animation *
	// Qualifier:
	// Parameter: const char * fmt
	// Parameter: int count
	// Parameter: std::string plist
	// Parameter: float fps
	// Parameter: std::string animationName
	// Parameter: bool _cache
	// %02d ����ʾ���2λ���� ������� 0   00.png
	// %03d ����ʾ���3λ���� ������� 0   000.png
	//************************************
	static Animation *createAnimation( const char *fmt, int count, std::string plist, float fps = 0.0f, std::string animationName = "", bool _cache = false );

	//************************************
	// Method:    createAnimation_1
	// FullName:  Kit::createAnimation_1
	// Access:    public static 
	// Returns:   Animation *
	// Qualifier:
	// Parameter: const char * fmt
	// Parameter: int count
	// Parameter: std::string plist
	// Parameter: float fps
	// Parameter: std::string animationName
	// Parameter: bool _cache
	//************************************
	static Animation *createAnimation_1( const char *fmt, int count, std::string plist, float fps = 0.0f, std::string animationName = "", bool _cache = false );


	//************************************
	// Method:    creatEaseSineInOut
	// FullName:  Kit::creatEaseSineInOut
	// Access:    public static 
	// Returns:   ActionInterval *
	// Qualifier:  ��������������ʾ��Ч������
	//************************************
	static  ActionInterval * creatEaseSineInOut( GLubyte opacity0 = 100, GLubyte opacity1 = 255 );


	//************************************
	// Method:    releaseCaches
	// FullName:  Kit::releaseCaches
	// Access:    public static 
	// Returns:   void
	// Qualifier: �ͷ�cache
	//************************************
	static void releaseCaches( );



	//************************************
	// Method:    getRect
	// FullName:  Kit::getRect
	// Access:    public static 
	// Returns:   Rect
	// Qualifier: ��ȡĳ��node�ľ�������
	// Parameter: Node * node  
	// Parameter: float w   dec w
	// Parameter: float h    dec h
	//************************************
    static cocos2d::Rect getRect( Node *node, float w = 0.0f, float h = 0.0f );


	// ���������ǩ
	//************************************
	// Method:    creatWithTTf
	// FullName:  Kit::creatWithTTf
	// Access:    public static 
	// Returns:   cocos2d::Label
	// Qualifier:
	// Parameter: const char * filePath    ttf path
	// Parameter: int size  ��С
	// Parameter: const std::string & text ��ʾ�ı�
	//************************************
	static Label* creatWithTTf( const char* filePath, int size, const std::string& text );




	//************************************
	// Method:    code_convert
	// FullName:  Kit::code_convert
	// Access:    public static 
	// Returns:   int
	// Qualifier:
	// Parameter: const char * from_charset
	// Parameter: const char * to_charset
	// Parameter: const char * inbuf
	// Parameter: size_t inlen
	// Parameter: char * outbuf
	// Parameter: size_t outlen
	//************************************
	static int code_convert( const char *from_charset, const char *to_charset, const char *inbuf, size_t inlen, char *outbuf, size_t outlen );
//
//	//************************************
//	// Method:    utf2gb
//	// FullName:  Kit::utf2gb
//	// Access:    public static 
//	// Returns:   std::string
//	// Qualifier:
//	// Parameter: const char * inbuf
//	//************************************
//	static string  utf2gb( const char *inbuf );
//
//	//************************************
//	// Method:    gb2utf8
//	// FullName:  Kit::gb2utf8
//	// Access:    public static 
//	// Returns:   std::string
//	// Qualifier:
//	// Parameter: const char * inbuf
//	//************************************
//	static std::string  gb2utf8( const char *inbuf );



	//************************************
	// Method:    getWidget
	// FullName:  Kit::getWidget
	// Access:    public static 
	// Returns:   Widget*
	// Qualifier:
	// Parameter: Widget * root
	// Parameter: std::string & widgetName
	// static_cast<Button*>(getWidget(root,name))
	//************************************
	static Widget* getWidget( Widget *root, std::string &widgetName );


	//�������� ��Ч����
	static SimpleAudioEngine * getAudio( );

	static void preloadMusicAndEffect(char* files,bool music=false);

	static void playMusic( char *music_file_name, bool loop = false );
	static void stopMusic( bool releaseData = false );

	static void playEffect( char *effect_file_name );
	static void stopEffect( int n_soudID );
	static void pauseAllEffect( );


	//������Ч

	//************************************
	// Method:    addParticle
	// FullName:  Kit::addParticle
	// Access:    public static 
	// Returns:   void
	// Qualifier:
	// Parameter: const std::string & filename   particle file
	// Parameter: Node * node     layer
	// Parameter: Vec2 position   particle position
	//************************************
	static void addParticle(const std::string& filename, Node *node, Vec2 position, ActionInterval *action=NULL);


	static int rnd(int min,int max);
};
#endif 