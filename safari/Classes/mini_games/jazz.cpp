#include "jazz.h"
#include "editor-support/cocostudio/CocoStudio.h"


USING_NS_CC;

Scene* jazz::createScene() {
	auto layer = jazz::create();
	auto scene = GameScene::createWithChild(layer, "jazz");
	layer->_menuContext = scene->getMenuContext();
	return scene;
}

Node* jazz::loadNode() {
	auto node = CSLoader::createNode("jazz/MainScene.csb");
	Size visibleSize = Director::getInstance()->getVisibleSize();

	if (visibleSize.width > 2560) {
		auto myGameWidth = (visibleSize.width - 2560) / 2;
		node->setPositionX(myGameWidth);
	}
	return node;
}

void jazz::createChoice() {

	float wid = Director::getInstance()->getVisibleSize().width;
	float hei = Director::getInstance()->getVisibleSize().height;

	_choice = Node::create();
	//	_choice->setPosition(Vec2(500, 900));
	_choice->setPosition(Vec2(0, 900));

	addChild(_choice);
	const float squareWidth = Director::getInstance()->getVisibleSize().width / _numGraphemes;

	for (int i = 0; i < _numGraphemes; i++) {
		auto choiceNode = Sprite::createWithSpriteFrameName("jazz/drum.png");
		choiceNode->setAnchorPoint(Vec2(0.5, 0.7));
		//	choiceNode->setPosition(Vec2(i * 400, 0));
		choiceNode->setPosition(Vec2((i + 1.1) * (squareWidth - 120), 100));
		_animate = CSLoader::createNode("jazz/gorilla.csb");
		_animate->setPosition(Vec2((i + 1.1) * (squareWidth - 120), 100));
		_gorilla.push_back(_animate);
		_choice->addChild(_animate);
		auto animation = CSLoader::createTimeline("jazz/gorilla.csb");
		_animate->runAction(animation);
		animation->play("jumping", true);
	//	blinking("blinking", true);
		auto blinkAction = CallFunc::create(CC_CALLBACK_0(jazz::blinking, this, "blinking", false));
	  _animate->runAction(RepeatForever::create(Sequence::create(DelayTime::create(5 + (rand() % 60) / 30.0), blinkAction, NULL)));
		addChoice(choiceNode);
	}
	
}
void jazz::blinking(std::string animationName, bool loop)
{
	
	_blinkAnimation = CSLoader::createTimeline("jazz/gorilla.csb");
	_animate->runAction(_blinkAnimation);
	_blinkAnimation->play(animationName, loop);

}
void jazz::gameOver(bool correct) {
	if (correct) {
		//_menuContext->showScore();
		for (auto item = _gorilla.rbegin(); item != _gorilla.rend(); ++item)
		{
			Node * gorilla = *item;
			auto animation = CSLoader::createTimeline("jazz/gorilla.csb");
			gorilla->runAction(animation);
			animation->play("druming", true);
			
	}
		
		//auto sprite = animate->getChildByName("gorilla");
		//sprite->setPosition();
	//	this->addChild(sprite);
		//cocostudio::timeline::ActionTimeline *timeLine = CSLoader::createTimeline("TutorialAnim.csb");
		//sprite->runAction(timeLine);
	//	timeLine->play("druming", true);
	}
}


std::string jazz::getGridBackground() {
	return "jazz/drum_below.png";
}

jazz* jazz::create() {
	jazz* word = new (std::nothrow) jazz();
	if (word && word->init())
	{
		word->autorelease();
		return word;
	}
	CC_SAFE_DELETE(word);
	return nullptr;
}