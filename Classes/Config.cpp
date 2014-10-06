#include "Config.h"



Config::Config( ) :
onEffect( true )
, onMusic(true)
, levelNum(0)
, score( 0 ), shipLife( 3 ), status( OFF )
, powers( 2 )
, player_bullet_list( new Vector<Bullet*>( ) )
, enemy_bullet_list( new Vector<Bullet*>( ) )
, enemy_list( new Vector<Enemy*>( ) ){
    
    //int bulletType;// 飞机挂载的子弹类型 0，1，2，3 ...
    //int canHurt;
    //int speedY;
    //std::string picName;   //  子弹挂载的类型--加载精灵
    //int ownType;     //>>（敌机，player ship）子弹
    // //>>子弹挂载的类型（敌机，player ship）
    structBulletList = new std::vector<StructBulletType>( );
    StructBulletType tempBullet = { 0, 10, -900, "Shoot_01.png", BULLEOWN::PLAYER_BULLET };
    structBulletList->push_back( tempBullet );//ship bullet type--> the first
    
    
    //敌机挂载子弹类型   敌机子弹类型1
    //int bulletType;// 飞机挂载的子弹类型 0，1，2，3 ...
    //int canHurt;
    //int speedY;
    //std::string picName;   //  子弹挂载的类型--加载精灵
    //int ownType;     //>>（敌机，player ship）子弹
    tempBullet = { 1, 1, 300, "yellowBall.png", BULLEOWN::ENEMY_BULLET };
    structBulletList->push_back( tempBullet );//ship bullet type
    tempBullet = { 2, 2, 300, "silverBall.png", BULLEOWN::ENEMY_BULLET };
    structBulletList->push_back( tempBullet );//ship bullet type
    tempBullet = { 3, 3, 300, "yellowBall.png", BULLEOWN::ENEMY_BULLET };
    structBulletList->push_back( tempBullet );//ship bullet type
    tempBullet = { 4, 4, 300, "orangeCircle.png", BULLEOWN::ENEMY_BULLET };
    structBulletList->push_back( tempBullet );//ship bullet type
    tempBullet = { 5, 5, 300, "orangeCircle.png", BULLEOWN::ENEMY_BULLET };
    structBulletList->push_back( tempBullet );//ship bullet type
    tempBullet = { 6, 6, 300, "yellowBall.png", BULLEOWN::ENEMY_BULLET };
    structBulletList->push_back( tempBullet );//ship bullet type
    tempBullet = { 7, 7, 300, "yellowBall.png", BULLEOWN::ENEMY_BULLET };
    structBulletList->push_back( tempBullet );//ship bullet type
    tempBullet = { 8, 8, 300, "yellowBall.png", BULLEOWN::ENEMY_BULLET };
    structBulletList->push_back( tempBullet );//ship bullet type
    
    
    
    //敌机类型 3 种类型
    //int bulletType;//飞机挂载的子弹类型  0，1，2，3 ...
    //std::string enemyPicName;//敌机精灵类型   关卡分类   1 ，2，3
    //int hp;
    structEnemyList = new std::vector<StructEnemyType>( );
    StructEnemyType tempEnemy = { 1, "Plane1_0.png", 10 ,100,1};//敌机类型
    structEnemyList->push_back( tempEnemy );//add enemy obj 0
    tempEnemy = { 2, "Plane1_1.png", 10, 100,2 };//敌机类型      1
    structEnemyList->push_back( tempEnemy );
    
    
    tempEnemy = { 3, "Plane2_0.png", 15, 150,1 };//敌机类型  2
    structEnemyList->push_back( tempEnemy );
    tempEnemy = { 4, "Plane2_1.png", 15, 150 ,2};//敌机类型  3
    structEnemyList->push_back( tempEnemy );
    
    
    tempEnemy = { 5, "Plane3_0.png", 20 ,200,1};//敌机类型  4
    structEnemyList->push_back( tempEnemy );
    tempEnemy = { 6, "Plane3_1.png", 20,200 ,2};//敌机类型  5
    structEnemyList->push_back( tempEnemy );
    
    
    //boos
    tempEnemy = { 7, "Boss0_0.png", 300,500 ,2};//敌机类型  6
    structEnemyList->push_back( tempEnemy );
    
    tempEnemy = { 8, "Boss1_0.png", 350, 700 ,2};//敌机类型  7
    structEnemyList->push_back( tempEnemy );
    
    tempEnemy = { 8, "Boss2_0.png", 500, 1000 ,2};//敌机类型  8
    structEnemyList->push_back( tempEnemy );
    
}


Config::~Config( )
{
    player_bullet_list->clear( );
    delete player_bullet_list;
    player_bullet_list = nullptr;
    enemy_bullet_list->clear( );
    delete enemy_bullet_list;
    enemy_bullet_list = nullptr;
    structBulletList->clear( );
    delete structBulletList;
    structBulletList = nullptr;
}

StructBulletType Config::getBulletByType( int ship_bulletType )
{
    StructBulletType temp;
    for(auto s_bulletType : *structBulletList)
    {
        if(s_bulletType.bulletType == ship_bulletType)
        {
            return s_bulletType;
        }
    }
    return temp;//  not find  ,return a un init object
}