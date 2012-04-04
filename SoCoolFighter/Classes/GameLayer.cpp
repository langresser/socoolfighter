#include "stdafx.h"

#include "GameLayer.h"

bool GameLayer::init()
{
	GameMap::instance().create(1, "tile0");
	addChild(&GameMap::instance());

	Hero::instance().create(1, "playersprite_female");

	CCSize mapSize = GameMap::instance().getMapSize();
	Hero::instance().setPosition(ccp(0, 0));
	addChild(&Hero::instance());

	setIsTouchEnabled(true);

	m_loopSpeed = 0;

	m_npcSet = CCArray::array();
// 	for (int i = 0; i < m_gameMap->m_npcSet->count(); ++i) {
// 		Role* npc = Role::createNew(i + 100, );
// 	}

	runAction(CCFollow::actionWithTarget(&Hero::instance(), CCRectMake(0, 0, mapSize.width, mapSize.height)));
//	registerWithTouchDispatcher();
	scheduleUpdate();
	return true;
}

void GameLayer::update(ccTime dt)
{
	Hero::instance().process(dt);
}

void GameLayer::moveCameraByCell(CCPoint point, float duration)
{

}

void GameLayer::moveCamera(CCPoint point, float duration)
{

}

void GameLayer::setCameraPos(CCPoint point)
{
	setPosition(point);
}

void GameLayer::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
}

void GameLayer::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
}

void GameLayer::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
}
