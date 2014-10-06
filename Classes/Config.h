#ifndef _CONFIG_HH_
#define _CONFIG_HH_

#ifndef SINGELTON
#define SINGELTON(_CLASS_)\
static _CLASS_ *getInstance( ){\
static _CLASS_  *t = NULL;\
if(!t)t = new _CLASS_( ); \
return t;\
}
#endif // !SINGELTON

#include "Kit.h"
#include "Enemy.h"
#include "Bullet.h"

class Enemy;
class Bullet;


//敌机资源类型 和子弹挂载的类型 可以采用xml进行数据描述，在程序启动的时候，
//加载数据并映射为响应的model，从而进行数据的初始化，这里为了开发的便捷采用结构体来描述
//子弹属于哪个对象发射
enum BULLEOWN
{
    NONE_OWN = -1,
    ENEMY_BULLET = 0,
    PLAYER_BULLET
};

//敌机类型
struct StructEnemyType
{
public:
    int bulletType;//飞机挂载的子弹类型 1，2，3 ...
    std::string enemyPicName;//敌机精灵类型   关卡分类   1 ，2，3
    int score;
    int hp;
    int powers;//子弹数量
};


//子弹类型  飞机类型 决定子弹类型
struct StructBulletType
{
public:
    int bulletType;// 飞机挂载的子弹类型 0，1，2，3 ...
    int canHurt;
    int speedY;
    std::string picName;   //  子弹挂载的类型--加载精灵
    int ownType;     //>>（敌机，player ship）子弹
};


//游戏状态
enum GAMESTATUS
{
    OFF=0, //未进行
    ING//进行中
};



//游戏中配置文件处理
class Config:public Layer
{
public:
    
    Config( );
    
    ~Config( );
    
    //单例
    SINGELTON(Config);
    //get and set  music and effect
    CC_SYNTHESIZE_PASS_BY_REF(bool, onMusic, musicState );
    CC_SYNTHESIZE_PASS_BY_REF(bool, onEffect, effectState );
    CC_SYNTHESIZE_PASS_BY_REF(int,score,Score );//获取玩家得分
    CC_SYNTHESIZE_PASS_BY_REF( int, shipLife, ShipLife );// ship的生命值 默认值 3
    CC_SYNTHESIZE_PASS_BY_REF(int,status,GameSatus);
    
    //ship 子弹数量
    CC_SYNTHESIZE_PASS_BY_REF( int, powers, ShipBulletPower );
    
    Vector<Bullet*> *player_bullet_list;
    Vector<Bullet*> *enemy_bullet_list;
    Vector<Enemy*>  *enemy_list;
    
    
    //子弹类型
private:
    std::vector<StructBulletType> *structBulletList;
    std::vector<StructEnemyType> *structEnemyList;
public:
    
    //************************************
    // Method:    getBulletByType
    // FullName:  Config::getBulletByType
    // Access:    public
    // Returns:   StructBulletType     飞机对应挂载的子弹数据
    // Qualifier:
    // Parameter: int ship_bulletType   飞机挂载子弹类型
    //************************************
    StructBulletType getBulletByType(int ship_bulletType );
    
    
    std::vector<StructEnemyType> * StructEnemyList( ) const {
        return structEnemyList;
    }
    std::vector<StructBulletType> * StructBulletList( ) const {
        return structBulletList;
    }
    
    
    ssize_t LevelNum( ) {
        return levelNum;
    }
    void LevelNum( ssize_t val ) {
        levelNum = val;
    }
    
private:
    int levelNum;//玩家选择的关卡编号
    
};
#endif
