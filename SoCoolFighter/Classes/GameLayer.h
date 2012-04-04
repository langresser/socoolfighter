#pragma once
#include "Role/Hero.h"
#include "GameMap/GameMap.h"

class GameLayer : public CCLayer
{
public:
    // 初始化场景
	virtual bool init();
    LAYER_NODE_FUNC(GameLayer);

	void update(ccTime dt);

	virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
	virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
	virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
public:
	void moveCameraByCell(CCPoint point, float duration);	// 地图格子增量移动
	void moveCamera(CCPoint point, float duration);	// 像素增量移动
	void setCameraPos(CCPoint point);	// 直接设置摄像机坐标
private:
	CCArray* m_npcSet;
	CCArray* m_monsterArray;

	float m_loopSpeed;
};