#include "stdafx.h"

#include "JoyStick.h"
 

JoyStick::JoyStick(CCPoint center, int radius)
{
	setPosition(center);

	m_ballRadius = 10;
	m_moveAreaRadius = radius;	
	m_isEnable = true;

	m_isAutoHide = false;
	m_isFollowTouch = false;

	m_timerInterval = 0.2f;

	CCSize size = CCDirector::sharedDirector()->getWinSize();
	setHitAreaRect(CCRectMake(0, 0, size.width / 2, size.height / 2));	// 默认左下角为摇杆触摸区域

	m_spriteBall = NULL;
	m_spriteDock = NULL;
	m_spriteStick = NULL;

	m_eventHandler = NULL;

	m_power = 0;
	m_angle = 0;
	m_highLight = false;
}

void JoyStick::setBallRadius(int radius)
{
	m_ballRadius = radius;
}

JoyStick* JoyStick::joyStickWithCenter(CCPoint center ,int radius)
{
	JoyStick* joystick = new JoyStick(center, radius);
	joystick->autorelease();

	return joystick;
}


void JoyStick::onEnter()
{
	CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, 0, true);
	CCLayer::onEnter();
}

void JoyStick::onExit()
{
	CCTouchDispatcher::sharedDispatcher()->removeDelegate(this);
	CCLayer::onExit();
}

bool JoyStick::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	bool shouldActive = false;
	CCPoint touchPoint = pTouch->locationInView();
	touchPoint = CCDirector:: sharedDirector()->convertToGL(touchPoint);
	if (m_activeRadius > 0) {
		// 触点在摇杆半径范围内
		if (ccpDistance(touchPoint, getPosition()) < m_activeRadius) {
			shouldActive = true;
		}
	} else {
		if (m_activeRect.size.width > 0 && m_activeRect.size.height > 0) {
			if (touchPoint.x > m_activeRect.origin.x 
				&& touchPoint.x < m_activeRect.origin.x + m_activeRect.size.width
				&& touchPoint.y > m_activeRect.origin.y
				&& touchPoint.y < m_activeRect.origin.y + m_activeRect.size.height) {
					shouldActive = true;
			}
		}
	}

	if (!shouldActive) {
		return false;
	}

	m_isTouched = true;
	if (m_isAutoHide && m_isEnable) {
		setIsVisible(true);
	}
	
	if (m_isFollowTouch) {
		setPosition(touchPoint);
	}

	if (m_spriteBall) {
		m_spriteBall->stopAllActions();
	}

	updateTouchPoint(touchPoint);

	// 开始触发计时器
	startTimer();

	return true;
}

void JoyStick::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	if (m_isTouched) {
		CCPoint touchPoint = pTouch->locationInView();
		touchPoint = CCDirector:: sharedDirector()->convertToGL(touchPoint);
		updateTouchPoint(touchPoint);
	}
}

void JoyStick::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	if (m_isTouched) {
		if (m_isAutoHide && m_isEnable) {
			setIsVisible(false);
		}

		m_isTouched = false;
		stopTimer();
		resetTexturePosition();
	}
}

void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
}

void JoyStick::updateTouchPoint(CCPoint touchPoint)
{
	CCPoint selfposition = getPosition();
	CCPoint currentPoint;
	if (ccpDistance(touchPoint, selfposition) > m_moveAreaRadius) {
		currentPoint = ccpMult(ccpNormalize(ccp(touchPoint.x-selfposition.x,touchPoint.y-selfposition.y)), m_moveAreaRadius - m_ballRadius);
	} else {
		currentPoint = ccp(touchPoint.x-selfposition.x,touchPoint.y-selfposition.y);
	}

	if (m_spriteBall) {
		m_spriteBall->setPosition(currentPoint);
	}
	
	m_angle = atan2(currentPoint.y, currentPoint.x) / M_PI * 180;
	m_power = ccpDistance(currentPoint, ccp(0, 0)) / (m_moveAreaRadius - m_ballRadius);
	m_direction = ccp(cos(m_angle * M_PI / 180),sin(m_angle * M_PI / 180));
}

void JoyStick::resetTexturePosition()
{
	m_power = 0;
	m_angle = 0;
	if (m_spriteStick) {
		m_spriteStick->setPosition(ccp(0, 0));
		m_spriteStick->setScaleX(0);
	}

	if (m_spriteBall) {
		if (!m_isAutoHide && m_isEnable) {
			m_spriteBall->runAction(
				CCEaseElasticOut::actionWithAction(
				CCMoveTo::actionWithDuration(0.5, ccp(0, 0))));
		} else {
			m_spriteBall->setPosition(ccp(0, 0));
		}
	}
}

void JoyStick::startTimer()
{
	setHighLight(true);
	schedule(schedule_selector(JoyStick::timerUpdate), m_timerInterval);

	if (m_target && m_eventHandler) {
		JoyStickEvent event;
		event.type = JS_EVENT_BEGIN;
		event.power = m_power;
		event.angle = m_angle;
		event.direction = m_direction;

		(m_target->*m_eventHandler)(&event);
	}
}

void JoyStick::stopTimer()
{
	setHighLight(false);
	unschedule(schedule_selector(JoyStick::timerUpdate));

	if (m_target && m_eventHandler) {
		JoyStickEvent event;
		event.type = JS_EVENT_END;
		event.power = 0;
		event.angle = 0;
		event.direction = m_direction;

		(m_target->*m_eventHandler)(&event);
	}
}

void JoyStick::timerUpdate(ccTime dt)
{
	if (m_target && m_eventHandler) {
		JoyStickEvent event;
		event.type = JS_EVENT_UPDATE;
		event.power = m_power;
		event.angle = m_angle;
		event.direction = m_direction;

		(m_target->*m_eventHandler)(&event);
	}
}

void JoyStick::setEventHandler(CCObject* target, SEL_EventHandler handler)
{
	m_eventHandler = handler;
	m_target = target;
}

void JoyStick::setBallSprite(const char* imageName, const char* imageHighLight)
{
	if (m_spriteBall) {
		m_spriteBall->removeAllChildrenWithCleanup(true);
	}

	m_spriteBall = CCNode::node();
	addChild(m_spriteBall, 1);

	CCSprite* sprite = CCSprite::spriteWithFile(imageName);
	m_spriteBall->addChild(sprite);

	m_ballName = imageName;

	if (imageHighLight) {
		m_ballNameHighLight = imageHighLight;
	}
}

void JoyStick::setDockSprite(const char* imageName, const char* imageHighLight)
{
	if (m_spriteDock) {
		m_spriteDock->removeAllChildrenWithCleanup(true);
	}

	m_spriteDock = CCNode::node();
	addChild(m_spriteDock, 0);

	CCSprite* sprite = CCSprite::spriteWithFile(imageName);
	m_spriteDock->addChild(sprite);

	m_dockName = imageName;
	if (imageHighLight) {
		m_dockNameHighLight = imageHighLight;
	}
}

void JoyStick::setStickSprite(const char* imageName, const char* imageHighLight)
{
	if (m_spriteStick) {
		m_spriteStick->removeAllChildrenWithCleanup(true);
	}

	m_spriteStick = CCNode::node();
	addChild(m_spriteStick);

	CCSprite* sprite = CCSprite::spriteWithFile(imageName);
	m_spriteStick->addChild(sprite);

	m_stickName = imageName;
	if (imageHighLight) {
		m_stickNameHighLight = imageHighLight;
	}
}

void JoyStick::setHitAreaRadius(int radius)
{
	m_activeRadius = radius;
	m_activeRect = CCRectMake(0, 0, 0, 0);
}

void JoyStick::setHitAreaRect(CCRect rect)
{
	m_activeRect = rect;
	m_activeRadius = 0;
}

void JoyStick::setHighLight(bool highLight)
{
	if (highLight == m_highLight) {
		return;
	}

	m_highLight = highLight;

	if (m_spriteBall && !m_ballNameHighLight.empty()) {
		m_spriteBall->removeAllChildrenWithCleanup(true);
		m_spriteBall->addChild(CCSprite::spriteWithFile(m_highLight ? m_ballNameHighLight.c_str() : m_ballName.c_str()));
	}

	if (m_spriteDock && !m_dockNameHighLight.empty()) {
		m_spriteDock->removeAllChildrenWithCleanup(true);
		m_spriteDock->addChild(CCSprite::spriteWithFile(m_highLight ? m_dockNameHighLight.c_str() : m_dockName.c_str()));
	}

	if (m_spriteStick && !m_stickNameHighLight.empty()) {
		m_spriteStick->removeAllChildrenWithCleanup(true);
		m_spriteStick->addChild(CCSprite::spriteWithFile(m_highLight ? m_stickNameHighLight.c_str() : m_stickName.c_str()));
	}
}

void JoyStick::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{

}

void JoyStick::setTimerInterval(float time)
{
	m_timerInterval = time;
}
