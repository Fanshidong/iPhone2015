#include "Mage.h"
#include "cocos2d.h"
#define PLAYER_HEIGHT 0

void Mage::changeStateOnceOrRepeat(int state, int startFrame, int endFrame,int flag)
{
	if (_state != state)
	{
		_state = state;
		auto animation = Animation3D::create(_modelPath);
		if (animation)
		{
			auto animate = Animate3D::createWithFrames(animation, startFrame, endFrame, FRAME_RATE);
			this->stopAllActions();
			if (flag != 1)
			{
				this->runAction(RepeatForever::create(animate));
			}
			else
			{
				this->runAction(animate);
				this->_frameNum = startFrame;
			}
		}
	}
}

void Mage::animateByState(int state)
{
	switch (state)
	{
	case MAGE_IDLE:
		this->changeStateOnceOrRepeat(MAGE_IDLE, MAGE_IDLE_START, MAGE_IDLE_END, 2);
		break;
	case MAGE_ATTACK:
		this->changeStateOnceOrRepeat(MAGE_ATTACK, MAGE_ATTACK_START, MAGE_ATTACK_END, 1);
		break;
	case MAGE_DEAD:
		this->changeStateOnceOrRepeat(MAGE_DEAD, MAGE_DEAD_START, MAGE_DEAD_END, 1);
		break;
	case MAGE_DEFEND:
		this->changeStateOnceOrRepeat(MAGE_DEFEND, MAGE_DEFEND_START, MAGE_DEFEND_END, 1);
		break;
	case MAGE_FORWARD:
		this->changeStateOnceOrRepeat(MAGE_FORWARD, MAGE_FORWARD_START, MAGE_FORWARD_END, 2);
		break;
	case MAGE_KNOCKED:
		this->changeStateOnceOrRepeat(MAGE_KNOCKED, MAGE_KNOCKED_START, MAGE_KNOCKED_END, 1);
		break;
	case MAGE_SPATTACK:
		this->changeStateOnceOrRepeat(MAGE_SPATTACK, MAGE_SPATTACK_START, MAGE_SPATTACK_END, 1);
		break;
	default:
		break;
	}
}

void Mage::update(float dt)
{
	switch (_state)
	{
	case MAGE_IDLE:
		break;
	case MAGE_FORWARD:
	{
		 Vec3 curPos = this->getPosition3D();
		 Vec3 newFaceDir = _targetPos - curPos;//�µ�������ΪĿ������-��ǰ���꣬�ӳ�����OnTouchEnded���
	     newFaceDir.y = 0.0f;//ֻ����xzƽ����������ı仯
		 newFaceDir.normalize();
		 Vec3 offset = newFaceDir*MAGE_FORWARD_SPEED*dt;//�����ĳ���ÿ��λ��n����λ
		 curPos = curPos + offset;
		 this->setPosition3D(curPos);
	}
		break;
	case MAGE_KNOCKED:
		break;
	case MAGE_ATTACK:
		break;
	case MAGE_SPATTACK:
		break;
	case MAGE_DEAD:
		break;
	default:
		break;
	}
	// transform player position to world coord
	auto playerPos = this->getPosition3D();//��������ڸ��ڵ�(��)�еĿռ���ά����
	auto playerModelMat = this->getParent()->getNodeToWorldTransform();//�õ��������ڸ��ڵ�(��)����������������ת���ľ���
	playerModelMat.transformPoint(&playerPos);//���������ڵ����ת��
	Vec3 Normal;
	float player_h = 0;//���ݽ�ɫ��x��z�����ø߶�
	if (Normal.isZero())//check the player whether is out of the terrain
	{
		player_h = playerPos.y;
	}
	else
	{
		player_h += PLAYER_HEIGHT;
	}
	this->setPositionY(player_h);

	Quaternion q2;
	q2.createFromAxisAngle(Vec3(0, 1, 0), (float)-M_PI, &q2);//����Ԫ����ʾ��y��ת��180�ȣ������ɫת��

	Quaternion headingQ;
	headingQ.createFromAxisAngle(_headingAxis, _headingAngle, &headingQ);
	this->setRotationQuat(headingQ*q2);
	_camera->setPosition3D(this->getPosition3D() + _cameraOffset);
	_camera->lookAt(this->getPosition3D(), Vec3(0, 1, 0));
	this->updateState();
}

void Mage::updateState()
{
	switch (_state)
	{
	case MAGE_FORWARD:
	{
		//����ɫλ���ѵ�Ŀ��λ�ã����л�����״̬
		Vec2 player_pos = Vec2(this->getPositionX(), this->getPositionZ());
		Vec2 targetPos = Vec2(_targetPos.x, _targetPos.z);
		auto dist = player_pos.distance(targetPos);
		if (dist < 1)
		{
			this->animateByState(MAGE_IDLE);
		}
	}
	    break;
	case MAGE_KNOCKED:
	{
		this->_frameNum++;
		if (this->_frameNum >= MAGE_KNOCKED_START + (60 / FRAME_RATE)*(MAGE_KNOCKED_END - MAGE_KNOCKED_START))
		{
			this->animateByState(MAGE_IDLE);
		}
	}
		break;
	case MAGE_ATTACK:
	{
		this->_frameNum++;
		if (this->_frameNum >= MAGE_ATTACK_START + (60 / FRAME_RATE)*(MAGE_ATTACK_END - MAGE_ATTACK_START))//������ϷĬ��60֡������Ĭ��30֡�������轫֡�����һ����
		{
			this->animateByState(MAGE_IDLE);
		}
	}
		break;
	case MAGE_SPATTACK:
	{
		this->_frameNum++;
		if (this->_frameNum >= MAGE_SPATTACK_START + (60 / FRAME_RATE)*(MAGE_SPATTACK_END - MAGE_SPATTACK_START))//������ϷĬ��60֡������Ĭ��30֡�������轫֡�����һ����
		{
			this->animateByState(MAGE_IDLE);
		}
	}
		break;
	case MAGE_DEFEND:
	{
		this->_frameNum++;
		if (this->_frameNum >= MAGE_DEFEND_START + (60 / FRAME_RATE)*(MAGE_DEFEND_END - MAGE_DEFEND_START))
		{
			this->animateByState(MAGE_IDLE);
		}
	}
		break;
	case MAGE_DEAD:
	{
		this->_frameNum++;
		if (this->_frameNum >= MAGE_DEAD_START + (60 / FRAME_RATE)*(MAGE_DEAD_END - MAGE_DEAD_START))
		{
			this->animateByState(MAGE_IDLE);
		}
	}
		break;
	default:
		break;
	}
}

Mage*  Mage::create(std::string modelPath, Camera * cam)
{
	auto sprite = new (std::nothrow) Mage();
	if (sprite && sprite->initWithFile(modelPath))
	{
		sprite->_cameraOffset = Vec3(0, CAMERA_DISTANCE + 10, CAMERA_DISTANCE);
		sprite->_headingAngle = 0;
		sprite->_camera = cam;
		sprite->_modelPath = modelPath;
		sprite->animateByState(MAGE_IDLE);
		sprite->autorelease();
		sprite->scheduleUpdate();
		return sprite;
	}
	delete sprite;
	sprite = nullptr;
	return nullptr;
}                                              


