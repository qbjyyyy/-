#ifndef _MENU_H_
#define _MENU_H_
#include"cocostudio/CocoStudio.h"
#include"ui/CocosGUI.h"
#include "cocos2d.h"
#include "valleybegin.h"

using namespace cocos2d;
using namespace ui;

class menu : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createmenuScene();

    virtual bool init();
    CREATE_FUNC(menu);
    //void Buttoncallback(Ref* ref, Widget::TouchEventType type);
   // void RadioButtonGroupcallback(RadioButton* rb,int index,RadioButtonGroup::TouchEventType type);
    void RadioButtonGroupCallback(RadioButton* radioButton);
private:
    RadioButtonGroup* _radioButtonGroup;
};
#endif // !_HELLOWORLD_SCENE_H_