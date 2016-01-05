#ifndef _DRAGON_H
#define _DRAGON_H
#include "cocos2d.h"
#include "Mage.h"
#include "physics3d/CCPhysics3D.h"
using namespace cocos2d;

#define GROUND_ABSX 320
#define GROUND_ABSZ 180

#define PATROL_RANGE 80//Ѳ�ߵľ��뷶Χ
#define LEAST_DISTANCE 20//Ѳ�ߵ���̾���
#define AI_SIGHT_RANGE 40//���˵���Ұ��Χ
#define AI_MELEE_RANGE 20//��ս���˵Ĺ�����Χ
#define AI_STATE_IDLE 1
#define AI_STATE_PATROL 2
#define AI_STATE_FIGHT 3

//С������֡����ֹ
/*
idle = createAnimation(file,0,24,0.7),
knocked = createAnimation(file,30,37,0.7),
dead = createAnimation(file,42,80,1),
attack1 = createAnimation(file,85,100,0.7),
attack2 = createAnimation(file,100,115,0.7),
walk = createAnimation(file,120,140,1),
*/

#define DRAGON_IDLE_START 0
#define DRAGON_IDLE_END 24
#define DRAGON_FORWARD_START 120
#define DRAGON_FORWARD_END 140
#define DRAGON_ATTACK_START 85
#define DRAGON_ATTACK_END 115
#define DRAGON_KNOCKED_START 30
#define DRAGON_KNOCKED_END 37
#define DRAGON_DEAD_START 42
#define DRAGON_DEAD_END 80
#define FRAME_RATE 30//�������ŵ�֡��
#define DRAGON_FORWARD_SPEED 20.0f//��ɫÿһ֡�ƶ��ĵ�λ����
//��ɫ�ĸ���״̬
#define DRAGON_IDLE 1
#define DRAGON_FORWARD 2
#define DRAGON_ATTACK 3
#define DRAGON_KNOCKED 4
#define DRAGON_DEAD 5

class Dragon :public cocos2d::PhysicsSprite3D //ԭ��public cocos2d::Sprite3D 
{
public:
	static Dragon* create(std::string modelPath);
	void changeStateOnceOrRepeat(int state, int startFrame, int endFrame, int flag);
	void animateByState(int state);

	void updateState();
	void update(float dt);

	void aiPatrol();
	void aiFight();
	void aiTrack(Mage* player);
	void aiIdle();
	void aiCheckPos(Mage* player);

	int getHitCount();
	void setHitCount(int count);

	bool _isPlayerInSight;
	bool _isPlayerInRange;
	Vec3 _targetPos;
	float _headingAngle;
	Vec3 _headingAxis;

	bool _isAlive;

private:
	int _state;
	int _aiState;
	int _frameNum;
	int _hitCount;
	std::string _modelPath;
};
#endif