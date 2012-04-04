#pragma once

#include "Common/GlobalConstant.h"

enum {
	kActionIdle = 0,
	kActionWalkLeft,
	kActionWalkRight,
	kActionAttack1,
	kActionAttack2,
	kActionAttack3,
	kActionAttack4,
};

enum {
	kDirUp,
	kDirRight,
	kDirDown,
	kDirLeft,
};

enum {
	GOTO_WALK,
	GOTO_RUN,
	GOTO_JUMP,
};

// Role�ǹҽ���GameLayer�ϵ�һ����ɫ����ķ�װ��
// �����������ʾ��������ʾ�����ڲ���sprite���У������ǻ����������ת��
class Role : public CCNode
{
public:
	static Role* createNew(uint32 roleId, const std::string& spriteName);
	Role();
	virtual ~Role();

	bool create(uint32 roleId, const std::string& spriteName);
	bool load();

	void setDir(int dir);

	// angleΪ�ƶ��Ƕȣ�ˮƽ����Ϊx�����򣬽Ƕ�Ϊ0������Ϊ180����ֱ����Ϊy�����򣬽Ƕ�Ϊ90������Ϊ-90
	// powerΪҡ�����ȣ�Խ�����ƶ�Խ��
	void run(int dir);
	void walk(float angle, float power);		
	void jump(int dir);
	void idle();

	void setAction(int actionId);
	void processAttack();
	void process(ccTime dt);
	bool processAction();			// ����ǰ��������һ��������ɺ󣬿�ʼִ����һ������������true��ʾ��ǰ����ִ�����
	void processCommand();			// һ������action���һ��command
	void show();
	void showEffect();
	void showBloodNumber();
	void showFloatWord();

	CCSpriteBatchNode* getSpriteSheet();

	int getActionFrameAmount(int action) const;
	int getActionFrameInterval(int action) const;
	int getActionMoveSpeed(int action) const;
protected:
	int m_id;
	int m_dir;
	float m_moveSpeed;
	float m_animationSpeed;

	// �������
	int m_actionType;			// �������
	int m_currentFrameIndex;	// ��ǰ���ŵ��ڼ�֡
	int m_actionFrameAmount;	// ��֡��
	int m_actionKeyFrame;		// �ؼ�֡���ڼ�֡���й�������
	float m_actionDuration;	// ������������
	CCPoint m_posActionBegin;	// ������ʼ����
	CCPoint m_posActionEnd;		// ������������

	uint32 m_actionStartTime;	// action��ʼ��ʱ��
	uint32 m_actionFrameInterval;	// action��֡���
	
	// ��ͼ�������
	std::string m_spriteName;	// ��Ӧ��Դ��ͼ�ļ���,����look

	CCSprite* m_sprite;			// ��ɫ����ģ��

	CCSpriteBatchNode* m_spriteSheet;	// �ý�ɫ��Ӧ��ͼ�ļ��ϼ����������ж���
};