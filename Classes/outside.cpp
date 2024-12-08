#include "outside.h"
#include"cocostudio/CocoStudio.h"
#include"ui/CocosGUI.h"
#include "cocos2d.h"
#include "intovalley.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

USING_NS_CC;

Scene* outside::createoutsideScene()
{
    auto scene = Scene::create();
    auto layer = outside::create();
    scene->addChild(layer);
    return scene;
}



bool outside::init()
{
    if (!Layer::init())
    {
        return false;
    }

    std::string file = "tiledmap/new.tmx";
    _tiledmap = TMXTiledMap::create(file);
    _tiledmap->setPosition(Vec2(-700, -700));
    _tiledmap->setScale(1.5);
  
    _background = _tiledmap->getLayer("background");
    this->addChild(_tiledmap, -1);

    _meta = _tiledmap->getLayer("meta");
    _meta->setVisible(false);
    //_foreground = _tiledmap->getLayer("Foreground");

    TMXObjectGroup* objects = _tiledmap->getObjectGroup("objects");
    CCASSERT(NULL != objects, "'objects' object group not found");
    auto spawnPoint = objects->getObject("character");
    int x = spawnPoint["x"].asInt();
    int y = spawnPoint["y"].asInt();

    _player = Sprite::create("picture/one.png");
    _player->setPosition(x, y);
    this->addChild(_player);

    setViewPointCenter(_player->getPosition());

    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = [&](Touch* touch, Event* unused_event)->bool {return true; };
    listener->onTouchEnded = CC_CALLBACK_2(outside::onTouchEnded,this);
    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    return true;
}



void outside::setPlayerPosition(cocos2d::Point position) {
    Point tileCoord = this->tileCoordForPosition(position);
    int tileGid = _meta->getTileGIDAt(tileCoord);
    if (tileGid) {
        auto properties = _tiledmap->getPropertiesForGID(tileGid).asValueMap();
        if (!properties.empty()) {
            auto collision = properties["Collidable"].asString();
            auto collectable = properties["Collectable"].asString();
            if ("True" == collision) {
                return;
            }
            if ("True" == collectable) {
                _meta->removeTileAt(tileCoord);
                _foreground->removeTileAt(tileCoord);

            }
        }
    }
    _player->setPosition(position);
}


void outside::onTouchEnded(Touch* touch, Event* unused_event)
{
    auto touchLocation = touch->getLocation();
    touchLocation = this->convertToNodeSpace(touchLocation);

    auto playerPos = _player->getPosition();
    auto diff = touchLocation - playerPos;
    if (abs(diff.x) > abs(diff.y)) {
        if (diff.x > 0) {
            playerPos.x += _tiledmap->getTileSize().width;
        }
        else {
            playerPos.x -= _tiledmap->getTileSize().width;
        }
    }
    else {
        if (diff.y > 0) {
            playerPos.y += _tiledmap->getTileSize().height;
        }
        else {
            playerPos.y -= _tiledmap->getTileSize().height;
        }
    }

    if (playerPos.x <= (_tiledmap->getMapSize().width * _tiledmap->getMapSize().width) &&
        playerPos.y <= (_tiledmap->getMapSize().height * _tiledmap->getMapSize().height) &&
        playerPos.y >= 0 &&
        playerPos.x >= 0)
    {
        this->setPlayerPosition(playerPos);
    }

    this->setViewPointCenter(_player->getPosition());
}

void outside::setViewPointCenter(Point position) {
    auto winSize = Director::getInstance()->getWinSize();

    int x = MAX(position.x, winSize.width / 2);
    int y = MAX(position.y, winSize.height / 2);

    x = MIN(x, (_tiledmap->getMapSize().width * _tiledmap->getTileSize().width) - winSize.width / 2);
    y = MIN(y, (_tiledmap->getMapSize().height * _tiledmap->getTileSize().height) - winSize.height / 2);
    auto actualPosition = Point(x, y);

    auto centerOfView = Point(winSize.width / 2, winSize.height / 2);
    auto viewPoint = centerOfView - actualPosition;
    this->setPosition(viewPoint);
}


Point outside::tileCoordForPosition(cocos2d::Point position)
{
    int x = position.x / _tiledmap->getTileSize().width;
    int y = ((_tiledmap->getMapSize().height * _tiledmap->getTileSize().height) - position.y) / _tiledmap->getTileSize().height;
    return Point(x, y);
}

