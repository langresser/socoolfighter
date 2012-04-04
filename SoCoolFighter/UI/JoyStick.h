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
	// ͨ�������ҡ�˰뾶��ʼ��һ��ҡ��
    static JoyStick*  joyStickWithCenter(CCPoint center ,int radius);
	JoyStick(CCPoint center, int radius);

	// ͨ����������������ҡ����ͼԪ��
	void setBallSprite(const char* imageName, const char* imageHighLight);
	void setStickSprite(const char* imageName, const char* imageHighLight);
	void setDockSprite(const char* imageName, const char* imageHighLight);

	// ����ҡ������
	void setHitAreaRadius(int radius);
	void setHitAreaRect(CCRect rect);
	void setBallRadius(int radius);
	void setTimerInterval(float time);

	// ���ûص�����
	void setEventHandler(CCObject* target, SEL_EventHandler handler);
public:
	// cclayer��д���麯��
	virtual void onEnter();
	virtual void onExit();

	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
private:
	bool m_isFollowTouch;	// ҡ�˸��津��
	bool m_isEnable;		// ҡ���Ƿ����
	bool m_isAutoHide;		// �Ƿ��Զ�����

	int m_moveAreaRadius;	// ҡ�˰뾶
	int m_ballRadius;		// ��İ뾶
	float m_timerInterval;	// ���º󴥷��¼��ļ����Ĭ��Ϊ0.5��

	int m_activeRadius;		// ҡ�˵����÷�Χ���ڴ˷�Χ�ڰ��·��ɴ���ҡ��
	CCRect m_activeRect;	// ͬ�ϣ�������������˰뾶�������жϰ뾶

	bool m_isTouched;			// �Ƿ���ҡ�ˣ����º�����Գ��������¼�

	float m_power;			// ҡ�˷�����Ϣ
	CCPoint m_direction;
	float m_angle;

	CCNode* m_spriteBall;	// ҡ����ͼ���������Ҫ���Բ�����
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