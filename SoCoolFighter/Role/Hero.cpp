#include "stdafx.h"
#include "hero.h"
#include "GameMap/GameMap.h"

Hero& Hero::instance()
{
	static Hero* s_hero = NULL;
	if (s_hero == NULL) {
		s_hero = new Hero;
		s_hero->autorelease();
	}

	return *s_hero;
}

void Hero::setPosition(const CCPoint& point)
{
	CCSize sizeMap = GameMap::instance().getMapSize();
	CCSize sizeSprite = m_sprite->getTextureRect().size;
	float leftBound = sizeSprite.width / 2;
	float rightBound = sizeMap.width - sizeSprite.width / 2;
	float topBound = sizeMap.height - sizeSprite.height;
	float bottomBound = 0;
	CCPoint destPos = point;
	if (destPos.x < leftBound) {
		destPos.x = leftBound;
	}

	if (destPos.x > rightBound) {
		destPos.x = rightBound;
	}

	if (destPos.y < bottomBound) {
		destPos.y = bottomBound;
	}

	if (destPos.y > topBound) {
		destPos.y = topBound;
	}

	Role::setPosition(destPos);
}
