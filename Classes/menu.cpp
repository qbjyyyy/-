#include "valleybegin.h"
#include"cocostudio/CocoStudio.h"
#include"ui/CocosGUI.h"
#include "cocos2d.h"
#include "menu.h"

using namespace cocos2d;
using namespace ui;

USING_NS_CC;

Scene* menu::createmenuScene()
{
    auto scene = Scene::create();
    auto layer = menu::create();
    scene->addChild(layer);
    return scene;
}



bool menu::init()
{
    if (!Layer::init())
    {
        return false;
    }
    //���ÿ�ʼ����
    auto spriteback = Sprite::create("picture/menu.png");
    spriteback->setAnchorPoint(Vec2::ZERO);
    spriteback->setPosition(Vec2(0, 0));
    this->addChild(spriteback);
    
    auto radioButtonGroup = RadioButtonGroup::create();
    this->addChild(radioButtonGroup);
   
    for (int i = 0; i < 4; ++i) {
        RadioButton* radioButton = RadioButton::create("picture/ch1.png", "picture/picture/ch2.png");
        this->addChild(radioButton);
        radioButton->setPosition(Vec2(100 + i * 100, 100));
        radioButton->setTag(i); // ���� tag���Ա��ڻص���ʶ��
        _radioButtonGroup->addRadioButton(radioButton);
    }

    // ���� RadioButtonGroup �Ļص�����
    _radioButtonGroup->addEventListener(CC_CALLBACK_1(menu::RadioButtonGroupCallback, this));

    return true;
}

void menu::RadioButtonGroupCallback(RadioButton* radioButton)
{
    // ����ѡ�е� RadioButton ִ�в���
    int index = radioButton->getTag();
    CCLOG("RadioButton selected index: %d", index);

    // ������Ը��� index �� radioButton ��һЩ����
}

