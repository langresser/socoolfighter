#include "stdafx.h"
#include "Role.h"

#include "RoleManager.h"

Role::Role()
{
	m_pro = kProThief;
	m_wantToMove = false;
}

Role::~Role()
{
	m_sprite = NULL;
	m_spriteSheet = NULL;
}

bool Role::load()
{
	// 将该角色贴图加入缓存以提高效率
	char szTemp[256] = {0};
	snprintf(szTemp, sizeof(szTemp) - 1, "%s.plist", m_spriteName.c_str());
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(szTemp);
	
	// 创建本角色的缓存
	snprintf(szTemp, sizeof(szTemp) - 1, "%s.png", m_spriteName.c_str());
	m_spriteSheet = CCSpriteBatchNode::batchNodeWithFile(szTemp);

	m_sprite = CCSprite::spriteWithSpriteFrameName("0.png");
	m_spriteSheet->addChild(m_sprite);

	// 设置角色左下角为锚点
	m_sprite->setAnchorPoint(ccp(0, 0));
	addChild(m_spriteSheet);

	return true;
}


void Role::setDir(int dir)
{
	std::string currentFrame;
	switch (dir)
	{
	case kDirUp:
		break;
	case kDirDown:
		break;
	case kDirLeft:
		break;
	case kDirRight:
		break;
	}

// 	m_sprite->setDisplayFrame(
// 		CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(currentFrame.c_str()));
	m_dir = dir;
}

void Role::process(ccTime dt)
{
	if (processAction()) {
		// 前一个动作执行完毕，执行下一个动作
		// 如果一直按着摇杆，那么持续走动
		if (m_wantToMove) {
			walk(m_moveAngle, m_movePower);
		} else {
			idle();
		}
	}
}

Role* Role::createNew(uint32 roleId, const std::string& spriteName)
{
	Role* role = new Role();
	role->create(roleId, spriteName);
	role->autorelease();
	return role;
}

CCSpriteBatchNode* Role::getSpriteSheet()
{
	return m_spriteSheet;
}

void Role::setAction(int actionId)
{
	m_actionType = actionId;
	m_actionStartTime = getCurrentTime();
	m_posActionBegin = getPosition();

	m_currentFrameIndex = 0;
	ActionInfo info = RoleManager::instance().getActionInfo(m_pro, actionId, 0);
	m_actionFrameStartIndex = info.frameStartIndex;
	m_actionFrameAmount = info.frameAmount;
	m_actionFrameInterval = info.frameInterval;
	m_actionFullId = info.actionId;
}

int Role::getActionMoveSpeed(int action) const
{
	if (action == kActionWalk) {
		return 80;
	} else if (action == kActionRun) {
		return 150;
	}

	return 0;
}

void Role::run(int dir)
{
	setDir(dir);
}

void Role::walk(float angle, float power)
{
	int dir = m_dir;

	// 正好为90或者-90的时候，不改变当前方向
	if (angle > - 90 && angle < 90) {
		m_dir = kDirRight;
	} else if (angle > 90 && angle <= 180 || angle < -90 && angle >= -180) {
		m_dir = kDirLeft;
	}

	int actionId = kActionWalk;
	if (power >= 0.5f) {
		actionId = kActionRun;
	}
	
	// 当前正在做此动作
	if (m_actionType == actionId && dir == m_dir && m_currentFrameIndex < m_actionFrameAmount) {
		return;
	}

	int moveDistanceX = getActionMoveSpeed(actionId);
	int moveDistanceY = moveDistanceX / 2;
	float deltaY = 1.0f * moveDistanceY * sin(angle * M_PI / 180) * power;
	float deltaX = 1.0f * moveDistanceX * cos(angle * M_PI / 180) * power;

	m_posActionBegin = getPosition();
	m_posActionEnd = ccp(m_posActionBegin.x + deltaX, m_posActionBegin.y + deltaY);

	setAction(actionId);
}

void Role::jump(int dir)
{
	setDir(dir);
}

bool Role::processAction()
{
	uint32 currentTime = getCurrentTime();
	m_currentFrameIndex = (currentTime - m_actionStartTime + m_actionFrameInterval / 2) / m_actionFrameInterval;

	// 动画结束，动作执行完毕
	if (m_currentFrameIndex >= m_actionFrameAmount) {
		// 修正位移到目的地（可能移动过程有微小偏移）
		CCPoint currentPoint = getPosition();
		int deltaX = m_posActionEnd.x - currentPoint.x;
		int deltaY = m_posActionEnd.y - currentPoint.y;
		if (deltaX != 0 && deltaY != 0) {
			setPosition(m_posActionEnd);
		}

		if (kActionWalk == m_actionType) {
			CCLOG("action over: %d   %d", m_currentFrameIndex, currentTime - m_actionStartTime);
		}

		return true;
	}

	// 位移调整（默认是根据时间间隔均分位移，此处可以进行处理，使动作执行中某几帧分配更多位移）
	if (m_currentFrameIndex < m_actionFrameAmount) {
		int deltaX = m_posActionEnd.x - m_posActionBegin.x;
		int deltaY = m_posActionEnd.y - m_posActionBegin.y;

		// 有位移
		if (deltaX != 0 || deltaY != 0) {
			uint32 timeCost = __max(1, m_actionFrameInterval * m_actionFrameAmount);
			uint32 timePass = __min(timeCost, currentTime - m_actionStartTime);

			float currentDeltaX = 1.0f * deltaX * timePass / timeCost;
			float currentDeltaY = 1.0f * deltaY * timePass / timeCost;

			CCPoint pos;
			pos.x = m_posActionBegin.x + (int)(currentDeltaX + 0.5f);
			pos.y = m_posActionBegin.y + (int)(currentDeltaY + 0.5f);

			setPosition(pos);
		}
	}

	char szTemp[256] = {0};
	snprintf(szTemp, sizeof(szTemp) - 1, "%d.png", m_actionFrameStartIndex + m_currentFrameIndex);

	// 修改当前帧
	CCSpriteFrame* frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(szTemp);
	if (frame && !m_sprite->isFrameDisplayed(frame)) {
		if (kActionWalk == m_actionType) {
			CCLOG("current frame: %d   %d", m_currentFrameIndex, getCurrentTime() - m_actionStartTime);
		}

		m_sprite->setDisplayFrame(frame);

		if (m_dir == kDirLeft) {
			// 向左方向，所有图片翻转
			m_sprite->setFlipX(true);
		} else {
			// 向右方向不用处理
			m_sprite->setFlipX(false);
		}

		ActionFrameInfo info = RoleManager::instance().getActionFrameInfo(m_actionFullId, m_currentFrameIndex + m_actionFrameStartIndex);
		if (info.offsetX != 0 || info.offsetY != 0) {
			m_sprite->setPosition(ccp(info.offsetX, info.offsetY));
		} else {
			m_sprite->setPosition(ccp(0, 0));
		}
	}

	return false;
}

void Role::idle()
{
	setAction(kActionIdle);
	m_posActionEnd = m_posActionBegin;
}

bool Role::create(uint32 roleId, const std::string& spriteName)
{
	m_id = roleId;
	m_spriteName = spriteName;
	m_dir = kDirRight;

	m_actionType = kActionIdle;

	return load();
}

void Role::setMovePower(bool want, float angle, float power)
{
	m_wantToMove = want;
	m_moveAngle = angle;
	m_movePower = power;
}
