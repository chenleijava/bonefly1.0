#ifndef _GAME_SCENE_HH_
#define  _GAME_SCENE_HH_
#include "Kit.h"
#include "GameLevelLayer.h"
#include "BaseSprite.h"

#include "Bullet.h"
#include "Ship.h"

#include "Enemy.h"

//��Ϸ��������  
class GameScene:public Layer
{
public:

	GameScene( int levelNum );

	~GameScene( );

	virtual bool init( );

	//��ʼ����Ϸ��Դ
	void initPlist( );
	//��ʼ����Ч��Դ ��ը ���� ��Ч
	void initEffect( );

	//�����Ϸ����
    void  addMap( const std::string &mapfilename );

	//onEnter move ship sprite
	virtual void onEnter( );

    virtual void onExit( );

	//��Ϸ��ˢ�³�����ʱ��
	virtual void update( float dt );

	//������Ϸ����
	static Scene* createScene( int levelNum );

	//�������Ƿ���ײ
	bool isPeng(BaseSprite *a,BaseSprite *b );

	//��ʼ���ƶ���ͼ
	void initMoveMap(float dt );
	//�ƶ���ͼ
	void moveMap( float dt );

	//���·��� 
	void updateScore( float dt );


	//************************************
	// Method:    checkPeng
	// FullName:  GameScene::checkPeng
	// Access:    public 
	// Returns:   void
	// Qualifier:  �����ײ  ����״̬
	// Parameter: float dt
	//************************************
	void checkPeng( float dt);


	//����ǰ���е���Դ
	void releaseR( );

	//���ݹؿ����������Ӧ�ĵл�
	void addEnemy(float dt );


	int getBoosByLevel( int levelNum);


	void shipReBorn( );

private:

	int levelNum;//�ؿ����

	int levelScore;//�ؿ�Ҫ��BOOS�ķ���

	Ship *ship;//player ship

	Sprite *mapSprite;//��Ϸ��ͼ  ���ڹ�������

	Sprite *tempMapSprite;//��Ϸ��ͼ  ���ڹ�������

	Label * lifeValue;//player����ֵ

	Label * score;//��ҵ÷�  

	std::string mapfilenames;
};
#endif //_GAME_SCENE_HH_


