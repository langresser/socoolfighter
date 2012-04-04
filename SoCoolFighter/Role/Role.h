#pragma once

#include "Common/GlobalConstant.h"

enum {
	kProThief = 10,
	kProSword = 20,
	kProGunner = 30,
	kProMage = 40,
	kProPriest = 50,
};

enum {
	kActionIdle = 1,
	kActionRest1,
	kActionRest2,
	kActionWalk = 100,
	kActionRun = 101,
	kActionAttack1 = 200,
	kActionAttack2,
	kActionAttack3,
	kActionAttack4,
	kActionSkill1 = 300,
	kActionSkill2,
	kActionSkill3,
	kActionSkill4,
	kActionSkill5,
	kActionSkill6,
	kActionSkillMax = 399,
	kActionHitFly = 400,
};

enum {
	kCommandIdle = 1,
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

	int getActionMoveSpeed(int action) const;
	void setMovePower(bool want, float angle, float power);
protected:
	int m_id;
	int m_dir;
	int m_pro;	// ��ɫְҵ

	bool m_wantToMove;
	float m_moveAngle;
	float m_movePower;

	// �������
	int m_actionType;			// �������
	int m_actionFullId;			// ��ǰ���ڲ��ŵĶ���id���������
	int m_currentFrameIndex;	// ��ǰ���ŵ��ڼ�֡
	int m_actionFrameStartIndex;// �����ļ�֡����
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