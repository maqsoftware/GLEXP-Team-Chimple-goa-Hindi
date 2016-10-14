//
//  BalloonHero.h
//
//  Created by Jyoti Prakash on 03/10/16.
//
//

#ifndef Balloon_Hero_h
#define Balloon_Hero_h

#include "cocos2d.h"
#include "../menu/MenuContext.h"
#include "../StartMenuScene.h"

class BalloonHero : public cocos2d::Layer {
public:
	static cocos2d::Scene* createScene();
	static BalloonHero *create();


CC_CONSTRUCTOR_ACCESS:
	virtual bool init();
	BalloonHero();
	virtual ~BalloonHero();
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	void startGame();
	void generateObjectsAndMove();
	void setupTouch();
	void update(float);
	void generateRandomNumbers();
	void removeMeteor1Animation();
	void removeMeteor2Animation();
	void removeMeteor3Animation();
	void removeMeteor4Animation();
	static const char* classname() { return BALLONHERO.c_str(); }
protected:
	Node * _balloonHero;
	Node * _foreGround;
	std::vector<int> _randomIndex;
	cocos2d::Sprite * _fireFly;
	Node * _meteor1;
	Node * _meteor2;
	Node * _meteor3;
	Node * _meteor4;
	cocos2d::Sprite * _cloud1;
	cocos2d::Sprite * _cloud2;
	cocos2d::Sprite * _cloud3;
	cocos2d::Sprite * _cloud4;
	cocostudio::timeline::ActionTimeline * _fireTimeline;
	
	MenuContext *_menuContext;

};

#endif /* Balloon_Hero_h */
