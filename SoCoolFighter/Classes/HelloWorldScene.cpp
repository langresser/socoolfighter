#include "stdafx.h"

#include "HelloWorldScene.h"

CCScene* HelloWorld::scene()
{
    CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::node();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
        HelloWorld *layer = HelloWorld::node();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    bool bRet = false;
    do 
    {
        //////////////////////////////////////////////////////////////////////////
        // super init first
        //////////////////////////////////////////////////////////////////////////

        CC_BREAK_IF(! CCLayer::init());

        //////////////////////////////////////////////////////////////////////////
        // add your codes below...
        //////////////////////////////////////////////////////////////////////////

        // 1. Add a menu item with "X" image, which is clicked to quit the program.

        // Create a "close" menu item with close icon, it's an auto release object.
        CCMenuItemImage *pCloseItem = CCMenuItemImage::itemFromNormalImage(
            "CloseNormal.png",
            "CloseSelected.png",
            this,
            menu_selector(HelloWorld::menuCloseCallback));
        CC_BREAK_IF(! pCloseItem);

        // Place the menu item bottom-right conner.
        pCloseItem->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20));

        // Create a menu with the "close" menu item, it's an auto release object.
        CCMenu* pMenu = CCMenu::menuWithItems(pCloseItem, NULL);
        pMenu->setPosition(CCPointZero);
        CC_BREAK_IF(! pMenu);

        // Add the menu to HelloWorld layer as a child layer.
        this->addChild(pMenu, 1);

        m_gameLayer = GameLayer::node();
        this->addChild(m_gameLayer, 0);

		m_joystick = JoyStick::joyStickWithCenter(ccp(80, 80), 50);
		m_joystick->setBallSprite("Ball.png", "Ball_hl.png");
		m_joystick->setDockSprite("Dock.png", "Dock_hl.png");
		m_joystick->setEventHandler(this, event_selector(HelloWorld::joyStickHandler));
		m_joystick->setBallRadius(15);
		m_joystick->setTimerInterval(0.1f);
		addChild(m_joystick);

        bRet = true;
    } while (0);

    return bRet;
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    // "close" menu item clicked
    CCDirector::sharedDirector()->end();
}

void HelloWorld::joyStickHandler(CCEvent* event)
{
	JoyStickEvent* je = (JoyStickEvent*)event;
	if (!je) {
		return;
	}

//	CCLOG("joyStickHandler:angle:%f  power:%f", je->angle, je->power);
	if (je->type == JS_EVENT_BEGIN) {
		Hero::instance().setMovePower(true, je->angle, je->power);
		Hero::instance().walk(je->angle, je->power);
	} else if (je->type == JS_EVENT_END) {
		Hero::instance().setMovePower(false, 0, 0);
		Hero::instance().idle();
	} else {
		Hero::instance().setMovePower(true, je->angle, je->power);
		Hero::instance().walk(je->angle, je->power);
	}
}