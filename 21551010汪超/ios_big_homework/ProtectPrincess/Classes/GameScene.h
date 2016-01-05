#ifndef _GAMESCENE_H_
#define _GAMESCENE_H_
#include"MonsterData.h"
#include"TurretData.h"
#include"Monster.h"
#include"PointDelegate.h"
#include"cocos2d.h"
#include"GameOver.h"
#include"SimpleAudioEngine.h"
//#include"SoundManager.h"
#include"Turret.h"
#include"Bullet.h"
#include"Monster.h"
#include<cocos-ext.h>
USING_NS_CC;
using namespace CocosDenshion;
class GameScene :public Layer
{
protected:
	TMXTiledMap* _tileMap;//��ͼ
	TMXLayer* _collidable;//�ϰ���
	std::string _tileName;//�ؿ�����
	int _number;//����Ĳ���
	int _currentCount;//��ǰ���ֵĹ��������
	int _currNum;//��ǰ����Ĳ���
	int _goldValue;//��ҵ�ǰ�Ľ��ֵ
	Sprite* _princess;//����
	int _visibleWidth;//��Ļ��
	int _visibleHeight;//��Ļ��
	int _count;//֡��
	int _delivery;//���ֹ���ȡģ����
	float m_fScore;//��Ǯ��
	Vector<MonsterData* >_monsterDatas;
	Vector<TurretData* >_turretDatas;
	Vector<PointDelegate* >_pathPoints;
	Label* _label1;
	Label* _label2;
	Label* _label3;
	Label* _numberLabel;//����Ĳ���
	Label* _currNumLabel;//��ǰ�Ĳ���
	Label* _goldLabel;//��ǰ�Ľ�Ǯ��
	bool _touchButton;
protected:
	Vector<Monster*>_monsterVector;
	bool _isFinish = false;//�ж��Ƿ���Գ��ֹ���
	Monster* _monster;
	Monster* monster;
	Sprite* _transparentTurret;
	Sprite* option_box;
	int princessX;//������x����λ��
	int princessY;//������y����λ��
	Vec2 princessLocation;
	bool _isSelect = false;
	Vector<Bullet* >_bulletVector;
	std::string animationName;
	int initMoney;
	//Sound* _sound;
	bool _isShoot;//�ж�����û�з����ӵ�
	float _degree;
	Vector<Turret* >_turretVector;//����Ѿ���������Ļ�ϵ���
public:
	static Scene* createSceneWithLevel(int selectLevel);
	virtual bool init(); 
	Vec2 locationForTilePos(Vec2 pos);
	Vec2 tileCoordForPosition(Vec2 position); 
	CREATE_FUNC(GameScene);
	GameScene();
	~GameScene();
	void onEnterTransitionDidFinish();
	void update(float dt);
	void LoadData();
public:
	Animate* getAnimateByName(std::string animName,float delay,int animNum);
	void monsterMoveWithWayPoints(Vector<PointDelegate*>pathVector,Monster* monster);
	void updateHUD(float dt);
	bool getCollidable(Vec2 position);
	void updateMonster(float delta);
	void updateDistance(float dt);
	bool calDistance(Vec2, Vec2, float & _degree);
	void isCollision(float dt);
};
#endif