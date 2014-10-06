#ifndef _BULLET_H_
#define _BULLET_H_
#include "BaseSprite.h"
#include "Config.h"

#define  BULLET_Z_ORDER 3000


//子弹设计接口：
//子弹 作为武器使用的一部分，fire，额，那么提供外部一个fire的接口；
//子弹具有杀伤力 canHurt  ,导致被攻击到的对象伤害；
// 子弹一旦被创建，那么它将是一个独立的单元；
// 子弹具有速度，不同子弹具有不同的速度，有一个bulletType类型区分；
// 子弹更新位置，同时进行碰撞检测，当然如果超出了游戏可视窗口，那么 我们也可以认为子弹的生命周期结束了；
//以上是我在考虑设计的做的一个构想



class Bullet :public BaseSprite
{

private:
	//canHurt( 1 ), speed( 1 ), bulletType( NONE_TYPE )
	Bullet(int canHurt, int speedY, std::string bulletType, int ownType );

	~Bullet( );

public:

	virtual bool init( );

	//œ˙ªŸ
	virtual void destory( Node *gameStage );

	//◊”µØ‘Ïø…“‘‘Ï≥……À∫¶÷µ
	virtual int hurt( int &canHurt );

	//∂‘œÛæÿ–Œ
    virtual cocos2d::Rect rect( );

	//∏¸–¬◊”µØŒª◊”
	virtual void update(float dt );

	void  boneDestory();

	static Bullet* createBullet( int canHurt, int speed, std::string bulletType, int ownType );


	//bullet status
	CC_SYNTHESIZE_PASS_BY_REF( bool, _active ,Active);

	//”Œœ∑ø… ”¥∞ø⁄œﬁ÷∆  £¨»Áπ˚≥¨π˝¡À £¨±Íº«…æ≥˝
	CC_SYNTHESIZE_PASS_BY_REF( int, outofVisible, OutVisible );

private:
	
	int canHurt;
	int speedY;//◊›œÚÀŸ∂»   
	int speedX;//∫·œÚÀŸ∂»

	std::string bulletType;//  ’Î∂‘≤ªÕ¨¿‡µƒ∑…ª˙  ◊”µØ¿‡–Õ≤ªÕ¨

	int bulletOwn;//◊”µØ Ù”⁄ƒƒ∏ˆ∂‘œÛ∑¢…‰≥ˆ¿¥µƒ  BULLEOWN   0:µ–»À∑…ª˙£ª 1: player∑…ª˙£ª

};
#endif

