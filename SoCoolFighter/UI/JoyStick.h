#pragma once

enum {
	JS_EVENT_BEGIN,
	JS_EVENT_UPDATE,
	JS_EVENT_END,
};
class JoyStickEvent : public CCEvent
{
public:
	int type;
	float power;
	float angle;
	CCPoint direction;
};

class JoyStick : public CCLayer {
 
public:
	// 通过坐标和摇杆半径初始化一个摇杆
    static JoyStick*  joyStickWithCenter(CCPoint center ,int radius);
	JoyStick(CCPoint center, int radius);

	// 通过这三个函数设置摇杆贴图元素
	void setBallSprite(const char* imageName, const char* imageHighLight);
	void setStickSprite(const char* imageName, const char* imageHighLight);
	void setDockSprite(const char* imageName, const char* imageHighLight);

	// 设置摇杆属性
	void setHitAreaRadius(int radius);
	void setHitAreaRect(CCRect rect);
	void setBallRadius(int radius);
	void setTimerInterval(float time);

	// 设置回调函数
	void setEventHandler(CCObject* target, SEL_EventHandler handler);
public:
	// cclayer覆写的虚函数
	virtual void onEnter();
	virtual void onExit();

	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
private:
	bool m_isFollowTouch;	// 摇杆跟随触点
	bool m_isEnable;		// 摇杆是否可用
	bool m_isAutoHide;		// 是否自动隐藏

	int m_moveAreaRadius;	// 摇杆半径
	int m_ballRadius;		// 球的半径
	float m_timerInterval;	// 按下后触发事件的间隔，默认为0.5秒

	int m_activeRadius;		// 摇杆的作用范围，在此范围内按下方可触发摇杆
	CCRect m_activeRect;	// 同上，但是如果配置了半径则优先判断半径

	bool m_isTouched;			// 是否按下摇杆，按下后则可以持续触发事件

	float m_power;			// 摇杆反馈信息
	CCPoint m_direction;
	float m_angle;

	CCNode* m_spriteBall;	// 摇杆贴图，如果不需要可以不配置
	CCNode* m_spriteDock;
	CCNode* m_spriteStick;

	bool m_highLight;
	std::string m_ballName;
	std::string m_ballNameHighLight;
	std::string m_dockName;
	std::string m_dockNameHighLight;
	std::string m_stickName;
	std::string m_stickNameHighLight;

	CCObject* m_target;
	SEL_EventHandler m_eventHandler;

	void startTimer();
	void stopTimer();
	void timerUpdate(ccTime dt);
	void resetTexturePosition();
	void updateTouchPoint(CCPoint touchPoint);
	void setHighLight(bool highLight);
};

class JoyStickButton : public CCSprite
{

};