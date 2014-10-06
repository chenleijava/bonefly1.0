
#include "GameScene.h"
#include "ActionForEnemy.h"
#define  MAP_Z_ORDER -1000
#define  BTN_BACK_Z_ORDER 1
#define  SHIP_Z_ORDER 2
#define  MAP_Z_TAG_0 3
#define  MAP_Z_TAG_1 4


//地图移动速度
#define MOVE_SPEED 110
#define MOVE_INTERVAL 1.5f


#define  SHIP_FILE_NAME "Plane0_0.png"



//关卡冲击boss最低分数
#define BOOS_LEVEL1 1000
#define BOOS_LEVEL2 2000
#define BOOS_LEVEL3 3000
#define BOOS_LEVEL4 4000


//ship life
#define  SHIP_LIFES 3
#define  SHIP_LIFE_VALUE 100

GameScene::GameScene(int levelNum) :levelNum(levelNum)
, ship(NULL), mapSprite(NULL)
, tempMapSprite(NULL)
, mapfilenames("")
{
}

GameScene::~GameScene()
{
    
}

bool GameScene::init()
{
    if (!Layer::init())return false;
    
    
    initPlist();
    initEffect();
    
    this->setTouchEnabled(true);
    //set game status
    Config::getInstance()->setGameSatus(ING);
    Config::getInstance()->setScore(0);//rest score
    
    //loding effect
    auto _SimpleAudioEngine = SimpleAudioEngine::getInstance();
    _SimpleAudioEngine->preloadEffect(air_shoot_effect1);
    _SimpleAudioEngine->preloadEffect(ship_explode_effect0);
    
    //init game map
    //init enemy type
    switch (levelNum)
    {
        case GAMEMAP1://0
            if (Config::getInstance()->getmusicState())
            {
                auto simpleAudio = SimpleAudioEngine::getInstance();
                simpleAudio->preloadBackgroundMusic(battle_bg_stage0);
                simpleAudio->setBackgroundMusicVolume(1.0f);
                simpleAudio->playBackgroundMusic(battle_bg_stage0, true);
            }
            addMap("Map1.png");
            levelScore = BOOS_LEVEL1;
            break;
        case GAMEMAP2://1
            if (Config::getInstance()->getmusicState())
            {
                auto simpleAudio = SimpleAudioEngine::getInstance();
                simpleAudio->preloadBackgroundMusic(battle_bg_stage1);
                simpleAudio->setBackgroundMusicVolume(1.0f);
                simpleAudio->playBackgroundMusic(battle_bg_stage1, true);
            }
            addMap("Map2.png");
            levelScore = BOOS_LEVEL2;
            //add particle
            Kit::addParticle(snow_plist, this, VisibleRect::top());
            break;
        case GAMEMAP3://2
            if (Config::getInstance()->getmusicState())
            {
                auto simpleAudio = SimpleAudioEngine::getInstance();
                simpleAudio->preloadBackgroundMusic(battle_bg_stage2);
                simpleAudio->setBackgroundMusicVolume(1.0f);
                simpleAudio->playBackgroundMusic(battle_bg_stage2, true);
            }
            addMap("Map3.png");
            levelScore = BOOS_LEVEL3;
            break;
            
        case GAMEMAP4://3
            if (Config::getInstance()->getmusicState())
            {
                auto simpleAudio = SimpleAudioEngine::getInstance();
                simpleAudio->preloadBackgroundMusic(battle_bg_stage2);
                simpleAudio->setBackgroundMusicVolume(1.0f);
                simpleAudio->playBackgroundMusic(battle_bg_stage2, true);
            }
            addMap("Map4.png");
            levelScore = BOOS_LEVEL4;
            //add fire paticle
            Kit::addParticle(battle_fire_bg_particle_plist, this, VisibleRect::top());
            break;
        default:
            log("there's no game map to do !");
            return false;
            break;
    }
    
    //add logo one top-left
    auto	logoShip = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(SHIP_FILE_NAME));
    float offset = logoShip->getContentSize().width / 2;
    logoShip->setScale(0.8f);
    auto winsize = Director::getInstance()->getWinSize();
    logoShip->setPosition(Vec2(offset, winsize.height - offset));
    this->addChild(logoShip, SHIP_Z_ORDER);
    
    
    
    //set life value  beside of logoShip
    Config::getInstance()->setShipLife(SHIP_LIFES);
    __String life("X");
    life.appendWithFormat("%02d", Config::getInstance()->getShipLife());
    lifeValue = Label::create(life.getCString(), "微软雅黑", 12);
    lifeValue->setPosition(Vec2(offset * 3, winsize.height - offset));
    lifeValue->setColor(Color3B::RED);
    this->addChild(lifeValue, SHIP_Z_ORDER);
    
    
    //add score
    __String tempscore("得分：");
    tempscore.appendWithFormat("%07d", Config::getInstance()->getScore());
    score = Label::create(tempscore.getCString(), "微软雅黑", 12);
    score->setPosition(Vec2(winsize.width - 45, winsize.height - offset));
    score->setColor(Color3B::RED);
    this->addChild(score, SHIP_Z_ORDER);
    
    
    
    
    ship = Ship::creatShip(this, 0, SHIP_LIFE_VALUE);
    auto initPosition = VisibleRect::center();
    ship->setPosition(Vec2(initPosition.x, initPosition.y - 120.0f));
    this->addChild(ship, SHIP_Z_ORDER);
    
    
    //add bone btn
    auto bone_btn_sprite = Sprite::create(btn_bone_res);
    bone_btn_sprite->setScale(0.8f);
    auto bone_btn = MenuItemSprite::create(bone_btn_sprite, nullptr, [&](Ref* _bone_btn){
        auto menuSprite = (MenuItemSprite*)_bone_btn;
        
        //处理炸弹效果
        log("bone released ......");
        
        //can shake
        auto j = JumpBy::create(0.5f, Vec2::ZERO, 5, 5);
        this->runAction(j);
        
        auto config = Config::getInstance();
        //remove enemy and bullet
        for (auto bullet : *config->enemy_bullet_list)
        {
            bullet->boneDestory();
        }
        
        for (auto enemy : *config->enemy_list)
        {
            //effect it
            log("effect it ......");
            enemy->boneDestory(this);
        }
        config->enemy_bullet_list->clear();
        config->enemy_list->clear();
        
    });
    auto menue = Menu::create(bone_btn, NULL);
    menue->setPosition(Vec2(35, 200));
    this->addChild(menue, BTN_BACK_Z_ORDER);
    menue->runAction(Kit::creatEaseSineInOut(100.0f));
    
    
    
    
    //add back btn
    auto btn_sprite = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->addImage(btn_back_res));
    btn_sprite->setColor(Color3B(0, 245, 255));
    auto btn_back = MenuItemSprite::create(btn_sprite, nullptr, [&](Ref* item){
        auto menuSprite = (MenuItemSprite*)item;
        auto scale = ScaleBy::create(0.2f, 1.1);
        auto jumpToGameLevel = CallFunc::create([](){
            
            auto config=Config::getInstance();
            
            if (config->getmusicState()) SimpleAudioEngine::getInstance()->stopBackgroundMusic();// 停止当前背景音乐
            
            if (config->getmusicState())
            {
                SimpleAudioEngine::getInstance()->playBackgroundMusic(main_bg_stage1, true);
            }
          
            
            Director::getInstance()->replaceScene(TransitionFade::create(1.2f, GameLevelLayer::creatScene()));
        });
        
        //call back
        std::function<void()> releaseResources = [&](){
            this->releaseR();
        };
        menuSprite->runAction(Sequence::create(CallFunc::create(releaseResources), scale, scale->reverse(), jumpToGameLevel, NULL));
    });
    
    
    
    
    menue = Menu::create(btn_back, NULL);
    auto btn_back_position = VisibleRect::rightBottom();
    offset = btn_sprite->getContentSize().width / 2;
    menue->setPosition(Vec2(btn_back_position.x - 50, btn_back_position.y + 25));
    this->addChild(menue, BTN_BACK_Z_ORDER);
    menue->runAction(Kit::creatEaseSineInOut(100.0f));
    
    
    
    
    
    
    //添加敌机
    this->schedule(schedule_selector(GameScene::addEnemy), 2.0f, kRepeatForever, 1.2f);
    
    this->scheduleUpdate();
    
    //初始化地图移动
    this->scheduleOnce(schedule_selector(GameScene::initMoveMap), 1.2f);
    
    
    
    
    return true;
}

Scene* GameScene::createScene(int levelNum)
{
    auto _scene = Scene::create();
    auto _gameSceneLayer = new GameScene(levelNum);// will init
    if (_gameSceneLayer->init())
    {
        _gameSceneLayer->autorelease();
        _scene->addChild(_gameSceneLayer);
        return _scene;
    }
    delete _gameSceneLayer;
    _gameSceneLayer = NULL;
    return NULL;
}


//************************************
// Method:    initPlist
// FullName:  GameScene::initPlist
// Access:    public
// Returns:   void
// Qualifier:
//************************************
void GameScene::initPlist()
{
    auto sprite_cache = SpriteFrameCache::getInstance();
    sprite_cache->addSpriteFramesWithFile(game_map_plist);
    sprite_cache->addSpriteFramesWithFile(game_planes_plist);
    sprite_cache->addSpriteFramesWithFile(game_bullet_plist);//bullet
    sprite_cache->addSpriteFramesWithFile(game_player_bullet_plist);
}


void GameScene::initEffect()
{
    Kit::createAnimation_1("explosion_%02d.png", 36, ship_explosion_plist, 24, "explosion", true);
}

//主要ship  enemy的 创建 应该封装到相应的类中
//add map  , ship   and so on!
void GameScene::addMap(const std::string &mapfilename)
{
    mapfilenames = mapfilename;
    
    auto origin = Director::getInstance()->getVisibleOrigin();
    
    mapSprite = Sprite::createWithSpriteFrameName(mapfilenames);
    mapSprite->getTexture()->setAliasTexParameters();
    mapSprite->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);//（0.5，0.5）
    mapSprite->setPosition(Vec2::ZERO);
    this->addChild(mapSprite, MAP_Z_ORDER, MAP_Z_TAG_0);
    
    tempMapSprite = Sprite::createWithSpriteFrameName(mapfilenames);
    tempMapSprite->getTexture()->setAliasTexParameters();
    tempMapSprite->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);//（0.5，0.5）
    this->addChild(tempMapSprite, MAP_Z_ORDER, MAP_Z_TAG_1);
    tempMapSprite->setPosition(Vec2(0, mapSprite->getContentSize().height));
    
    
    
    
}
void GameScene::initMoveMap(float dt)
{
    
    mapSprite->runAction(MoveBy::create(MOVE_INTERVAL, Vec2(0, -MOVE_SPEED)));
    tempMapSprite->runAction(MoveBy::create(MOVE_INTERVAL, Vec2(0, -MOVE_SPEED)));
    
    this->schedule(schedule_selector(GameScene::moveMap), MOVE_INTERVAL, kRepeatForever, 0.0f);//1.2f后执行 ，场景转化时间设置的为1.2f ，地图移动的周期为3.0f
}

//处理地图移动,使用两张图片，做切换 注意是Y轴移动
void GameScene::moveMap(float dt)
{
    
    mapSprite->runAction(MoveBy::create(MOVE_INTERVAL, Vec2(0, -MOVE_SPEED)));
    tempMapSprite->runAction(MoveBy::create(MOVE_INTERVAL, Vec2(0, -MOVE_SPEED)));
    
    
    log("mapSprite y:%f, tempMapSprite y:%f", mapSprite->getPositionY(), tempMapSprite->getPositionY());
    
    auto origin = Director::getInstance()->getVisibleOrigin();
    
    if (mapSprite->getPositionY() + mapSprite->getContentSize().height <= origin.y)
    {
        mapSprite->setPosition(Vec2(0, mapSprite->getContentSize().height + tempMapSprite->getPositionY()));//拼接到tempMapSprite尾部
    }
    if (tempMapSprite->getPositionY() + tempMapSprite->getContentSize().height <= origin.y)
    {
        tempMapSprite->setPosition(Vec2(0, tempMapSprite->getContentSize().height + mapSprite->getPositionY()));//拼接到mapSprite尾部
    }
    
}
//update
//************************************
// Method:    update
// FullName:  GameScene::update
// Access:    public
// Returns:   void
// Qualifier:
// 1. 碰撞检测
// 2. 移除生命周期结束的对象
// 3. 检查player 的ship是否可以再次出现（如果被击毁之后）
// 4. 移动背景图片
// Parameter: float dt
//************************************
void GameScene::update(float dt)
{
    auto config = Config::getInstance();
    if (config->getGameSatus())
    {
        Vector<Bullet *> temp;
        // update player and enemy bullets
        for (auto bullet : *config->player_bullet_list)
        {
            bullet->update(dt);// update bullet  position
            auto posirion = bullet->getPosition();
            if (posirion.y >= bullet->getOutVisible())
            {
                bullet->destory(this);
                this->removeChild(bullet);
                temp.pushBack(bullet);
            }
        }
        
        if (temp.size() != 0)
        {
            for (auto bullet : temp)
            {
                config->player_bullet_list->eraseObject(bullet);
            }
        }
        temp.clear();
        
        for (auto bullet : *config->enemy_bullet_list)
        {
            bullet->update(dt);// update bullet  position
            auto posirion = bullet->getPosition();
            if (posirion.y <= bullet->getOutVisible())
            {
                bullet->destory(this);
                this->removeChild(bullet);
                temp.pushBack(bullet);
            }
        }
        if (temp.size() != 0)
        {
            for (auto bullet : temp)
            {
                config->enemy_bullet_list->eraseObject(bullet);
            }
        }
        temp.clear();
        
        
        this->checkPeng(dt);
        
        //update score
        updateScore(dt);
    }
    
}

// touch will call
void GameScene::onEnter()
{
    Layer::onEnter();
    log("onEnter game scene ....");
    auto eventListener = EventListenerTouchOneByOne::create();
    eventListener->onTouchBegan = [](Touch*, Event *)->bool{return true; };
    eventListener->onTouchMoved = [&](Touch* touch, Event *event){
        if (!ship)return;
        // returns the delta position between the current location and the previous location in OpenGL coordinates
        auto posiotion = touch->getDelta();//德尔塔值 （差）
        auto shipPosition = ship->getPosition();
        shipPosition.add(posiotion);
        //shipPosition must be in visible
        auto winsize = Director::getInstance()->getWinSize();
        auto offset = ship->getContentSize().width;
        shipPosition.clamp(Vec2(offset, offset), Vec2(winsize.width - offset, winsize.height - offset));
        ship->setPosition(shipPosition);
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(eventListener, this);
}

void GameScene::onExit()
{
    Layer::onExit();
    
    Director::getInstance()->getEventDispatcher()->removeEventListenersForTarget(this, true);
    releaseR();
    log("onExit game scene ....");
}

//************************************
// Method:    isPeng
// FullName:  GameScene::isPeng
// Access:    public
// Returns:   bool
// Qualifier:  碰撞检测
// Parameter: BaseSprite * a
// Parameter: BaseSprite * b
//************************************
bool GameScene::isPeng(BaseSprite *a, BaseSprite *b)
{
    return a->rect().intersectsRect(b->rect());
}



//更新玩家得分
void GameScene::updateScore(float dt)
{
    
    __String tempscore("得分：");
    tempscore.appendWithFormat("%05d", Config::getInstance()->getScore());
    score->setString(tempscore.getCString());
}

//添加敌机
void GameScene::addEnemy(float dt)
{
    log("add enemy ... ...");
    auto config = Config::getInstance();
    
    auto shipSize = config->enemy_list->size();
    log("enemy size:% ld", shipSize);
    if (shipSize >= 5)
    {
        return;
    }
    auto winSize = Director::getInstance()->getWinSize();

    
    //creat  boos
    //if(config->getScore( ) >= levelScore)
    //{
    //	auto boos = Enemy::creatEnemy( this, config->StructEnemyList( )->at( getBoosByLevel( levelNum ) ) );
    //	config->enemy_list->pushBack( boos );
    //	this->addChild( boos, SHIP_Z_ORDER );
    //	//初始化位置  移动位置
    //	auto initPosition = VisibleRect::top( );
    //	boos->setPosition( Vec2( CCRANDOM_0_1( )*initPosition.x*1.5, initPosition.y ) );
    
    //	auto boosPosition = boos->getPosition( );
    
    //	boos->runAction( MoveTo::create( 1.0f, Vec2( CCRANDOM_0_1( )* initPosition.x, 300 ) ) );
    
    //	auto nowPsition = boos->getPosition( );
    //	nowPsition.clamp( Vec2::ZERO, Vec2( winSize.height, winSize.height ) );
    //	boos->runAction( RepeatForever::create( ActionForEnemy::CreateMoveByOfSequenceX( nowPsition ) ) );
    //	//this->unschedule( schedule_selector( GameScene::addEnemy ) );
    //	//移动轨迹
    //	return;
    //}
    
    
    int rnd = CCRANDOM_0_1() * 6;// 0~5 之间随机数
    auto commonEnemy = Enemy::creatEnemy(this, config->StructEnemyList()->at(rnd));
    config->enemy_list->pushBack(commonEnemy);
    this->addChild(commonEnemy, SHIP_Z_ORDER);
    
    auto initPosition = VisibleRect::top();
    commonEnemy->setPosition(Vec2(CCRANDOM_0_1()*initPosition.x*1.5, initPosition.y));
    
    commonEnemy->runAction(MoveTo::create(1.0f, Vec2(CCRANDOM_0_1()* initPosition.x, 300)));
    
    auto nowPsition = commonEnemy->getPosition();
    nowPsition.clamp(Vec2::ZERO, Vec2(winSize.height, winSize.height));
    
    
    int rndAction = Kit::rnd(0, 1);
    log("rnd value :%d", rndAction);
    if (rndAction == 0)
    {
        commonEnemy->runAction(RepeatForever::create(ActionForEnemy::CreateMoveByOfSequenceX(nowPsition)));
    }
    else{
        commonEnemy->runAction(RepeatForever::create(ActionForEnemy::CreateBezierBy()));
    }
    
}


//清除游戏层中的资源
void GameScene::releaseR()
{
    auto config = Config::getInstance();
    this->unscheduleUpdate();
    this->unschedule(schedule_selector(GameScene::moveMap));
    this->unschedule(schedule_selector(GameScene::addEnemy));
    if (ship)ship->stopFire();
    for (auto enemy : *config->enemy_list)
    {
        enemy->stopFire();
    }
    
    //卸载音效
    SimpleAudioEngine::getInstance()->unloadEffect(air_shoot_effect1);
    
    //移除子弹
    for (auto bullet : *config->player_bullet_list)
    {
        this->removeChild(bullet);
    }
    
    for (auto bullet : *config->enemy_bullet_list)
    {
        this->removeChild(bullet);
    }
    
    //clear and realse
    config->player_bullet_list->clear();
    config->enemy_bullet_list->clear();
    config->enemy_list->clear();
    config->setGameSatus(OFF);
    Kit::releaseCaches();
}

int GameScene::getBoosByLevel(int levelNum)
{
    if (levelNum == 1)
    {
        return 6;
    }
    else if (levelNum == 2)
    {
        return 7;
    }
    else
    {
        return 8;
        
    }
}

void GameScene::shipReBorn()
{
    auto config = Config::getInstance();
    auto lifes = config->getShipLife();
    if (lifes != 0)
    {
        //creat a new ship ,may be can add some defeine---
        ship = Ship::creatShip(this, 0, SHIP_LIFE_VALUE);
        auto initPosition = VisibleRect::center();
        ship->setPosition(Vec2(initPosition.x, initPosition.y - 120.0f));
        ship->setScale(1.2f);
        this->addChild(ship, SHIP_Z_ORDER);
        --lifes;
    }
    else
    {
        this->releaseR();
        Director::getInstance()->replaceScene(TransitionFade::create(1.2f, GameOverLayer::createScene()));
        if (Config::getInstance()->getmusicState())
        {
            SimpleAudioEngine::getInstance()->playBackgroundMusic(main_bg_stage1, true);
        }
    }
    config->setShipLife(lifes);
    __String life("X");
    life.appendWithFormat("%02d", lifes);
    lifeValue->setString(life.getCString());
}

void GameScene::checkPeng(float dt)
{
    //check peng !
    /*
     *1.enemy bullet -->player ship
     *2.player bullet -> enemy
     *3.playe ship  and enemy ship
     */
    auto config = Config::getInstance();
    if (config->getGameSatus()){
        Vector<Bullet *> temp;
        int canHurt = 0;
        int last = 0;
        for (auto bullet : *config->enemy_bullet_list)
        {
            
            if (temp.contains(bullet))
            {
                continue;
            }
            if (ship&&isPeng(bullet, ship) && ship->Hp() > 0)
            {
                //播放特效
                canHurt = bullet->hurt(canHurt);
                last = ship->hurt(canHurt);
                canHurt = 0;
                bullet->destory(this);
                temp.pushBack(bullet);//destroy bullet
                if (last <= 0)
                {
                    ship->destory();
                    ship = NULL;
                    shipReBorn();
                    return;
                }
            }
        }
        
        canHurt = 0;
        if (temp.size() != 0)
        {
            for (auto bullet : temp)
            {
                config->enemy_bullet_list->eraseObject(bullet);
            }
        }
        temp.clear();
        
        //检查ship bullet 和敌机碰撞
        Vector<Enemy *> tempEnemy;
        for (auto bullet : *config->player_bullet_list){
            if (temp.contains(bullet))//had destory  !!!
            {
                continue;
            }
            for (auto enemy : *config->enemy_list){
                
                if (tempEnemy.contains(enemy))
                {
                    continue;
                }
                
                if (isPeng(bullet, enemy) && enemy->Hp() > 0)
                {
                    //播放特效
                    canHurt = bullet->hurt(canHurt);
                    last = enemy->hurt(canHurt);
                    temp.pushBack(bullet);//destroy bullet
                    bullet->destory(this);
                    if (last <= 0)
                    {
                        //播放特效
                        enemy->destory();//
                        tempEnemy.pushBack(enemy);
                    }
                }
            }
        }
        if (tempEnemy.size() != 0)
        {
            for (auto enemy : tempEnemy)
            {
                config->enemy_list->eraseObject(enemy);
            }
        }
        tempEnemy.clear();
        if (temp.size() != 0)
        {
            for (auto bullet : temp)
            {
                config->player_bullet_list->eraseObject(bullet);
            }
        }
        temp.clear();
        
        
        //检查敌机和ship相碰撞
        canHurt = 5;//碰撞 固定伤害值 5点
        for (auto enemy : *config->enemy_list)
        {
            
            
            if (tempEnemy.contains(enemy))
            {
                continue;
            }
            if (ship&&isPeng(ship, enemy) && enemy->Hp() > 0 && ship->Hp() > 0)
            {
                
                last = enemy->hurt(canHurt);
                if (last <= 0)
                {
                    //播放特效
                    enemy->destory();
                    tempEnemy.pushBack(enemy);
                }
                
                last = ship->hurt(canHurt);
                if (last <= 0)
                {
                    ship->destory();
                    ship = NULL;
                    shipReBorn();
                    return;
                }
            }
        }
        
        if (tempEnemy.size() != 0)
        {
            for (auto enemy : tempEnemy)
            {
                
                config->enemy_list->eraseObject(enemy);
            }
        }
        tempEnemy.clear();
    }
}
