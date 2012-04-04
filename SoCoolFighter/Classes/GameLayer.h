#pragma once
#include "Role/Hero.h"
#include "GameMap/GameMap.h"

class GameLayer : public CCLayer
{
public:
    // ��ʼ������
	virtual bool init();
    LAYER_NODE_FUNC(GameLayer);

	void update(ccTime dt);

	virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
	virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
	virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
public:
	void moveCameraByCell(CCPoint point, float duration);	// ��ͼ���������ƶ�
	void moveCamera(CCPoint point, float duration);	// ���������ƶ�
	void setCameraPos(CCPoint point);	// ֱ���������������
private:
	CCArray* m_npcSet;
	CCArray* m_monsterArray;

	float m_loopSpeed;
};