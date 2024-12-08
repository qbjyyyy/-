#ifndef _OUTSIDE_H_
#define _OUTSIDE_H_
#include"cocostudio/CocoStudio.h"
#include"ui/CocosGUI.h"
#include "cocos2d.h"

class outside : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createoutsideScene();
    virtual bool init();
    void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);
 
    void setViewPointCenter(cocos2d::Point position);
    void setPlayerPosition(cocos2d::Point position);
    cocos2d::Point tileCoordForPosition(cocos2d::Point position);


    CREATE_FUNC(outside);
private:
    cocos2d::TMXTiledMap* _tiledmap;
    cocos2d::TMXLayer* _background;
    cocos2d::Sprite* _player;
    cocos2d::TMXLayer* _meta;
    cocos2d::TMXLayer* _foreground;
};
#endif // !_HELLOWORLD_SCENE_H_