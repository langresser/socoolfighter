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

// Role是挂接在GameLayer上的一个角色对象的封装。
// 本身不会进行显示（具体显示由其内部的sprite进行），但是会控制坐标旋转等
class Role : public CCNode
{
public:
	static Role* createNew(uint32 roleId, const std::string& spriteName);
	Role();
	virtual ~Role();

	bool create(uint32 roleId, const std::string& spriteName);
	bool load();

	void setDir(int dir);

	// angle为移动角度，水平向右为x正方向，角度为0，向左为180；垂直向上为y正方向，角度为90，向下为-90
	// power为摇杆力度，越大则移动越快
	void run(int dir);
	void walk(float angle, float power);		
	void jump(int dir);
	void idle();

	void setAction(int actionId);
	void processAttack();
	void process(ccTime dt);
	bool processAction();			// 处理当前动作，当一个动作完成后，开始执行下一个动作。返回true表示当前动作执行完毕
	void processCommand();			// 一个或多个action组成一个command
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
	int m_pro;	// 角色职业

	bool m_wantToMove;
	float m_moveAngle;
	float m_movePower;

	// 动作相关
	int m_actionType;			// 动作编号
	int m_actionFullId;			// 当前正在播放的动作id，完整编号
	int m_currentFrameIndex;	// 当前播放到第几帧
	int m_actionFrameStartIndex;// 用于文件帧索引
	int m_actionFrameAmount;	// 总帧数
	int m_actionKeyFrame;		// 关键帧。第几帧进行攻击计算
	float m_actionDuration;	// 动作持续几秒
	CCPoint m_posActionBegin;	// 动作起始坐标
	CCPoint m_posActionEnd;		// 动作结束坐标

	uint32 m_actionStartTime;	// action开始的时间
	uint32 m_actionFrameInterval;	// action的帧间隔
	
	// 贴图动画相关
	std::string m_spriteName;	// 对应资源贴图文件名,决定look

	CCSprite* m_sprite;			// 角色基本模型

	CCSpriteBatchNode* m_spriteSheet;	// 该角色对应贴图文件合集，包含所有动画
};