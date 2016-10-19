#include "Talk.h"
#include "editor-support/cocostudio/CocoStudio.h"
#include "../lang/TextGenerator.h"
#include "ui/UIScale9Sprite.h"
#include "../menu/HelpLayer.h"

USING_NS_CC;

Talk::Talk() {
}

Talk::~Talk() {
}

Scene* Talk::createScene()
{
	auto scene = Scene::create();
	auto layer = Talk::create();
	scene->addChild(layer);
    layer->_menuContext = MenuContext::create(layer, Talk::gameName());
    scene->addChild(layer->_menuContext);
	return scene;
}

void Talk::onEnterTransitionDidFinish()
{
	_menuContext->setMaxPoints(8);
	_level = _menuContext->getCurrentLevel();

	if ((_level >= 1 && _level <= 8) || (_level >= 25 && _level <= 32) || (_level >= 49 && _level <= 56))
	{
		sceneName = "talkisland";
	}
	else if ((_level >= 9 && _level <= 16) || (_level >= 33 && _level <= 40) || (_level >= 57 && _level <= 64))
	{
		sceneName = "talkcity";
	}
	else if ((_level >= 17 && _level <= 24) || (_level >= 41 && _level <= 48) || (_level >= 65 && _level <= 72))
	{
		sceneName = "talkjungle";
	}

	if (_level == 1 || _level == 12 || _level == 18 || _level == 26 || _level == 31 || _level == 35 || _level == 40 || _level == 45 || _level == 47 || _level == 52 || _level == 56 || _level == 60 || _level == 64 || _level == 66 || _level == 69)
	{
		_questionType = "VERB";
		_allSentense = TextGenerator::getInstance()->getSentenceWithPOS(TextGenerator::POS::VERB, 5, 1);
	}
	else if (_level == 2 || _level == 16 || _level == 21 || _level == 25 || _level == 29 || _level == 34 || _level == 38 || _level == 41 || _level == 48 || _level == 51 || _level == 55 || _level == 57 || _level == 63 || _level == 67 || _level == 72)
	{
		_questionType = "NOUN";
		_allSentense = TextGenerator::getInstance()->getSentenceWithPOS(TextGenerator::POS::NOUN, 5, 1);
	}
	else if (_level == 3 || _level == 9 || _level == 19 || _level == 28 || _level == 32 || _level == 37 || _level == 39 || _level == 42 || _level == 46 || _level == 49 || _level == 54 || _level == 58 || _level == 62 || _level == 65 || _level == 71)
	{
		_questionType = "PRONOUN";
		_allSentense = TextGenerator::getInstance()->getSentenceWithPOS(TextGenerator::POS::PRONOUN, 5, 1);
	}
	else if (_level == 4 || _level == 13 || _level == 23 || _level == 27 || _level == 43 || _level == 59)
	{
		_questionType = "ADVERB";
		_allSentense = TextGenerator::getInstance()->getSentenceWithPOS(TextGenerator::POS::ADVERB, 5, 1);
	}
	else if (_level == 5 || _level == 10 || _level == 22 || _level == 30 || _level == 33 || _level == 68)
	{
		_questionType = "ADJECTIVE";
		_allSentense = TextGenerator::getInstance()->getSentenceWithPOS(TextGenerator::POS::ADJECTIVE, 5, 1);
	}
	else if (_level == 6 || _level == 15 || _level == 17 || _level == 44 || _level == 53 || _level == 61)
	{
		_questionType = "PREPOSITION";
		_allSentense = TextGenerator::getInstance()->getSentenceWithPOS(TextGenerator::POS::PREPOSITION, 5, 1);
	}
	else if (_level == 7 || _level == 11 || _level == 24)
	{
		_questionType = "CONJUNCTION";
		_allSentense = TextGenerator::getInstance()->getSentenceWithPOS(TextGenerator::POS::PREPOSITION, 5, 1);
	}
	else if (_level == 8 || _level == 14 || _level == 20)
	{
		_questionType = "INTERJECTION";
		_allSentense = TextGenerator::getInstance()->getSentenceWithPOS(TextGenerator::POS::INTERJECTION, 5, 1);
	}
	else if (_level == 70 || _level == 36 || _level == 50)
	{
		_questionType = "ARTICLE";
		_allSentense = TextGenerator::getInstance()->getSentenceWithPOS(TextGenerator::POS::ARTICLE, 5, 1);
	}

	visibleSize = Director::getInstance()->getWinSize();

	_scene = { "talkisland", "talkcity", "talkjungle" };
//	sceneName = _scene.at(rand() % _scene.size());

	if (sceneName == "talkisland")
	{
		_talkBg = (Node *)CSLoader::createNode("talkisland/talkisland.csb");
		for (int i = 0; i < _talkBg->getChildrenCount(); i++)
		{
			for (int j = 0; j < _talkBg->getChildren().at(i)->getChildrenCount(); j++)
			{
				if (_talkBg->getChildren().at(i)->getChildren().at(j)->getName().find("bubble") != std::string::npos)
				{
					auto bubble = CSLoader::createTimeline("talkisland/bubble.csb");
					_talkBg->getChildren().at(i)->getChildren().at(j)->runAction(bubble);
					bubble->play("bubble", true);
				}
			}
		}

		_heroChar = CSLoader::createTimeline("talkisland/hero.csb");
		_enemyChar = CSLoader::createTimeline("talkisland/enemy.csb");

		_hbasket = (Sprite*)_talkBg->getChildren().at(1)->getChildByName("hhand");
		_ebasket = (Sprite*)_talkBg->getChildren().at(1)->getChildByName("ehand");
		_hhand = (Sprite*)_talkBg->getChildren().at(1)->getChildren().at(6);
		_ehand = (Sprite*)_talkBg->getChildren().at(1)->getChildren().at(7);
		_hero = (Sprite*)_talkBg->getChildren().at(1)->getChildByName("hero");
		_enemy = (Sprite*)_talkBg->getChildren().at(1)->getChildByName("enemy");
	}
	else if (sceneName == "talkcity")
	{
		_talkBg = (Node *)CSLoader::createNode("talkcity/talkcity.csb");

		_hhand = (Sprite*)_talkBg->getChildByName("h_node");
		_ehand = (Sprite*)_talkBg->getChildByName("e_node");
		_hero = (Sprite*)_talkBg->getChildByName("hero");
		_enemy = (Sprite*)_talkBg->getChildByName("enemy");

		_heroChar = CSLoader::createTimeline("talkcity/hero.csb");
		_enemyChar = CSLoader::createTimeline("talkcity/enemy.csb");

		auto h_tail = CSLoader::createTimeline("talkcity/hero.csb");
		auto h_eye_blinking = CSLoader::createTimeline("talkcity/hero.csb");

		auto e_tail = CSLoader::createTimeline("talkcity/enemy.csb");
		auto e_eye_blinking = CSLoader::createTimeline("talkcity/enemy.csb");

		_talkBg->runAction(h_tail);
		_talkBg->runAction(h_eye_blinking);
		_talkBg->runAction(e_tail);
		_talkBg->runAction(e_eye_blinking);

		_talkBg->runAction(RepeatForever::create(Sequence::create(DelayTime::create(1), CallFunc::create([=]() {
			e_tail->play("e_tail", false);
		}), DelayTime::create(1), CallFunc::create([=]() {
			e_eye_blinking->play("e_eye_blinking", false);
		}), NULL)));

		_talkBg->runAction(RepeatForever::create(Sequence::create(DelayTime::create(1.4), CallFunc::create([=]() {
			h_tail->play("h_tail", false);
		}), DelayTime::create(1), CallFunc::create([=]() {
			h_eye_blinking->play("h_eye_blinking", false);
		}), NULL)));

		_enemy->setScaleX(-1.0f);
		_ehand->setPosition(Vec2(_enemy->getPositionX() + _ehand->getBoundingBox().size.width, _hhand->getPositionY()));
	}
	else if (sceneName == "talkjungle")
	{
		_talkBg = (Node *)CSLoader::createNode("talkjungle/talkjungle.csb");

		_hhand = (Sprite*)_talkBg->getChildByName("h_node");
		_ehand = (Sprite*)_talkBg->getChildren().at(16);
		_hero = (Sprite*)_talkBg->getChildByName("hero");
		_enemy = (Sprite*)_talkBg->getChildByName("enemy");
	}

	_talkBg->setPosition(Vec2(visibleSize.width / 2, 0));
	_talkBg->setAnchorPoint(Vec2(.5, 0));
	this->addChild(_talkBg);

	differntSceneMapping = {

		{ "talkisland",  //anu designs
		{
			{ "enemy", _ehand->getPositionX() },
			{ "hero",  _hhand->getPositionX() }
		} },
		{ "talkcity",  //sonu designs
		{
			{ "enemy", _ehand->getPositionX() },
			{ "hero",  _hhand->getPositionX() }
		} },
		{ "talkjungle",  //deepak design
		{
			{ "enemy", _ehand->getPositionX() },
			{ "hero",  _hhand->getPositionX() }
		} },
	};

	std::vector<std::string> _question = { "NOUN","PRONOUN","ADJECTIVE","VERB","ADVERB","PREPOSITION",
		"CONJUNCTION","INTERJECTION", "ARTICLE" };

	std::ostringstream _question_Name;
//	_questionType = _question.at(rand() % _question.size());
	_question_Name << "SELECT " << _questionType;

	_imgName << sceneName << "/patch_image.png";

	auto _lbl = LabelTTF::create(_question_Name.str(), "Arial", 80);
	_board = cocos2d::ui::Scale9Sprite::createWithSpriteFrameName(_imgName.str());
	_board->setContentSize(Size(_lbl->getBoundingBox().size.width * 1.2, _lbl->getBoundingBox().size.height));
	_board->setPosition(Vec2(visibleSize.width / 2 - _board->getContentSize().width / 2, visibleSize.height * .90));
	_lbl->setPosition(Vec2(_board->getBoundingBox().size.width / 2, 0));
	_lbl->setAnchorPoint(Vec2(.5, 0));
	_board->setAnchorPoint(Vec2(0, .5));
	_board->addChild(_lbl);
	_talkBg->addChild(_board);

	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	_handFlag = 0;
	_helpFlag = 0;
	Talk::displayWord();

	this->scheduleUpdate();
}

bool Talk::init()
{
	if (!Layer::init())
	{
		return false;
	}
	
	return true;
}

void Talk::displayWord()
{
	if (_allSentense.size() == 0 || _enemyFish.size() == 8 || _heroFish.size() == 8)
	{
		_menuContext->showScore();
		return;
	}

	_textToShow = _allSentense.at((rand() % _allSentense.size()));

	int count = 0;
	for (int i = 0; i < _textToShow.size(); i++)
	{
		if ((_questionType == "NOUN" && _textToShow.at(i).second == TextGenerator::POS::NOUN) ||
			(_questionType == "PRONOUN" && _textToShow.at(i).second == TextGenerator::POS::PRONOUN) ||
			(_questionType == "ADJECTIVE" && _textToShow.at(i).second == TextGenerator::POS::ADJECTIVE) ||
			(_questionType == "VERB" && _textToShow.at(i).second == TextGenerator::POS::VERB) ||
			(_questionType == "ADVERB" && _textToShow.at(i).second == TextGenerator::POS::ADVERB) ||
			(_questionType == "PREPOSITION" && _textToShow.at(i).second == TextGenerator::POS::PREPOSITION) ||
			(_questionType == "CONJUNCTION" && _textToShow.at(i).second == TextGenerator::POS::CONJUNCTION) ||
			(_questionType == "INTERJECTION" && _textToShow.at(i).second == TextGenerator::POS::INTERJECTION) ||
			(_questionType == "ARTICLE" && _textToShow.at(i).second == TextGenerator::POS::ARTICLE))
		{
			count++;
		}
	}

	if (count == 0)
	{
		_allSentense.erase(std::remove(_allSentense.begin(), _allSentense.end(), _textToShow), _allSentense.end());
		Talk::displayWord();
	}
	else
	{
		_handFlag = 0;
		for (int i = 0; i < _labelDetails.size(); i++)
		{
			removeChild(_labelDetails.at(i).sprite);
		}

		_labelDetails.clear();

		if (sceneName == "talkjungle")
		{
			_heroChar = CSLoader::createTimeline("talkjungle/hero.csb");
			_enemyChar = CSLoader::createTimeline("talkjungle/enemy.csb");

			_hero->runAction(_heroChar);
			_enemy->runAction(_enemyChar);

			_heroChar->play("h_idle", true);
			_enemyChar->play("e_idle", true);
		}

		_totalCount = 0;
		_totalAnswer = 0;
		_correctAnswer = 0;

		//	auto drawNode = DrawNode::create();
		//	_talkBg->addChild(drawNode, 2);
		//	Color4F white(1, 1, 1, 1);
		//	drawNode->drawRect(Vec2(_hhand->getBoundingBox().origin.x , _hhand->getBoundingBox().origin.y), Vec2(_hhand->getBoundingBox().origin.x + _hhand->getBoundingBox().size.width, _hhand->getBoundingBox().origin.y + _hhand->getBoundingBox().size.height), white);

		_allSentense.erase(std::remove(_allSentense.begin(), _allSentense.end(), _textToShow), _allSentense.end());


		for (int i = 0; i < _textToShow.size(); i++)
		{
			LabelDetails.label = LabelTTF::create(_textToShow.at(i).first, "Arial", 120);
			LabelDetails.sprite = cocos2d::ui::Scale9Sprite::createWithSpriteFrameName(_imgName.str());
			LabelDetails.sprite->setContentSize(Size(LabelDetails.label->getBoundingBox().size.width * 1.3, LabelDetails.label->getBoundingBox().size.height * 1.2));

			if (i == 0)
			{
				LabelDetails.label->setPosition(Vec2(LabelDetails.sprite->getBoundingBox().size.width / 2, 0));
				LabelDetails.sprite->setPosition(Vec2(visibleSize.width * .10, visibleSize.height * .80));
			}
			else
			{
				cocos2d::ui::Scale9Sprite *lab = _labelDetails.at(i - 1).sprite;
				LabelDetails.sprite->setPosition(Vec2(lab->getPositionX() + lab->getBoundingBox().size.width + 30, lab->getPositionY()));
				LabelDetails.label->setPosition(Vec2(LabelDetails.sprite->getBoundingBox().size.width / 2, 0));
			}

			if (LabelDetails.sprite->getBoundingBox().size.width + LabelDetails.sprite->getPositionX() >= visibleSize.width)
			{
				LabelDetails.sprite->setPosition(Vec2(visibleSize.width * .10, LabelDetails.sprite->getPositionY() - LabelDetails.sprite->getBoundingBox().size.height * 1.5));
			}


			LabelDetails.sprite->setAnchorPoint(Vec2(0, .5));
			LabelDetails.sprite->addChild(LabelDetails.label);
			LabelDetails.sequence = i;
			LabelDetails.id = _textToShow.at(i).first;
			LabelDetails.flag = 0;
			LabelDetails.label->setAnchorPoint(Vec2(.5, 0));

			if ((_questionType == "NOUN" && _textToShow.at(i).second == TextGenerator::POS::NOUN) ||
				(_questionType == "PRONOUN" && _textToShow.at(i).second == TextGenerator::POS::PRONOUN) ||
				(_questionType == "ADJECTIVE" && _textToShow.at(i).second == TextGenerator::POS::ADJECTIVE) ||
				(_questionType == "VERB" && _textToShow.at(i).second == TextGenerator::POS::VERB) ||
				(_questionType == "ADVERB" && _textToShow.at(i).second == TextGenerator::POS::ADVERB) ||
				(_questionType == "PREPOSITION" && _textToShow.at(i).second == TextGenerator::POS::PREPOSITION) ||
				(_questionType == "CONJUNCTION" && _textToShow.at(i).second == TextGenerator::POS::CONJUNCTION) ||
				(_questionType == "INTERJECTION" && _textToShow.at(i).second == TextGenerator::POS::INTERJECTION) ||
				(_questionType == "ARTICLE" && _textToShow.at(i).second == TextGenerator::POS::ARTICLE))
			{
				LabelDetails.answer = 'c';
				_totalAnswer++;

				if (_helpFlag == 0)
				{
					_help = HelpLayer::create(Rect(LabelDetails.sprite->getPositionX() + LabelDetails.sprite->getBoundingBox().size.width/2, LabelDetails.sprite->getPositionY(), LabelDetails.sprite->getBoundingBox().size.width, LabelDetails.sprite->getBoundingBox().size.height), Rect(_board->getPositionX() + _board->getBoundingBox().size.width * .57, _board->getPositionY(), _board->getBoundingBox().size.width * 1.05, _board->getBoundingBox().size.height));
					addChild(_help, 5);
					_help->click(Vec2(LabelDetails.sprite->getPositionX() + LabelDetails.sprite->getBoundingBox().size.width, LabelDetails.sprite->getPositionY()));
					_helpFlag = 1;
				}
			}
			else
			{
				LabelDetails.answer = 'w';
			}

			Talk::addEvents(LabelDetails);
			addChild(LabelDetails.sprite);
			_labelDetails.push_back(LabelDetails);
		}
	}
}

std::vector<std::string> Talk::split(std::string s, char delim)
{
	std::vector<std::string> elems;
	std::stringstream ss;
	ss.str(s);
	std::string item;
	while (getline(ss, item, delim)) {
		elems.push_back(item);
	}
	return elems;
}

void Talk::update(float d)
{
	if (_handFlag == 1)
	{
		Rect fish_Rect, hand_rect, fish_Rect_next;

		hand_rect = _hhand->getBoundingBox();
		if (sceneName == "talkcity" || sceneName == "talkjungle")
		{
			fish_Rect = _fish->getBoundingBox();
		}
		else
		{
			fish_Rect = Rect(_fish->getPositionX(), _fish->getPositionY(), _fish->getBoundingBox().size.width, _fish->getBoundingBox().size.height);
		}

		if(sceneName == "talkjungle" || sceneName == "talkisland")
			fish_Rect_next = Rect(_fish->getPositionX(), _fish->getPositionY(), _fish->getBoundingBox().size.width, _fish->getBoundingBox().size.height);
		else
			fish_Rect_next = _fish->getBoundingBox();

		if (fish_Rect.intersectsRect(_hhand->getBoundingBox()) || (_heroFish.size() >= 1 && fish_Rect_next.intersectsRect(_heroFish.at(_heroFish.size() - 1)->getBoundingBox())))
		{
			_fish->stopAction(_action);
			_heroFish.push_back(_fish);

			if (_totalCount == _textToShow.size() || _totalAnswer == _correctAnswer)
			{
				_handFlag = -1;
				if (sceneName == "talkjungle")
				{
					std::ostringstream timeline;
					timeline << sceneName << "/enemy" << ".csb";

					_enemy->stopAction(_enemyChar);
					_enemyChar = CSLoader::createTimeline(timeline.str());
					_enemy->runAction(_enemyChar);
					_enemyChar->play("e_die", false);
					_totalAnswer = -1;
					_enemyChar->setAnimationEndCallFunc("e_die", CC_CALLBACK_0(Talk::gameEnd, this));
				}
				else
				{
					Talk::displayWord();
				}
			}
			else if(_handFlag == 1)
			{
				_handFlag = 0;
			}
		}
		else if (fish_Rect.intersectsRect(_ehand->getBoundingBox()) || (_enemyFish.size() >= 1 && fish_Rect_next.intersectsRect(_enemyFish.at(_enemyFish.size() - 1)->getBoundingBox())))
		{
			_fish->stopAction(_action);
			_enemyFish.push_back(_fish);

			if (_totalCount == _textToShow.size() || _totalAnswer == _correctAnswer)
			{
				_handFlag = -1;
				if (sceneName == "talkjungle" || sceneName == "talkisland")
				{
					if (sceneName == "talkisland")
					{
						_hhand->setVisible(false);
						_hbasket->setVisible(false);
						for (int i = 0; i < _heroFish.size(); i++)
						{
							_talkBg->removeChild(_heroFish.at(i));
						}
					}

					std::ostringstream timeline;
					timeline << sceneName << "/hero" << ".csb";

					_hero->stopAction(_heroChar);
					_heroChar = CSLoader::createTimeline(timeline.str());
					_hero->runAction(_heroChar);
					_heroChar->play("h_die", false);
					_totalAnswer = -1;
					_heroChar->setAnimationEndCallFunc("h_die", CC_CALLBACK_0(Talk::gameEnd, this));
				}
				else
				{
					Talk::displayWord();
				}
			}
			else if (_handFlag == 1)
			{
				_handFlag = 0;
			}
		}
	}

	if (_heroFish.size() == 8)
	{
		_handFlag = -1;
		if (sceneName == "talkisland")
		{
			_ehand->setVisible(false);
			_ebasket->setVisible(false);
			for (int i = 0; i < _enemyFish.size(); i++)
			{
				_talkBg->removeChild(_enemyFish.at(i));
			}

			std::ostringstream timeline;
			timeline << sceneName << "/enemy" << ".csb";

			_enemy->stopAction(_enemyChar);
			_enemyChar = CSLoader::createTimeline(timeline.str());
			_enemy->runAction(_enemyChar);
			_enemyChar->play("e_die", false);
			_totalAnswer = -1;
			_enemyChar->setAnimationEndCallFunc("e_die", CC_CALLBACK_0(Talk::gameEnd, this));
			_heroFish.clear();
			_allSentense.clear();
		}
		else
		{
			_menuContext->showScore();
			this->unscheduleUpdate();
		}
	}
	else if (_enemyFish.size() == 8)
	{
		_handFlag = -1;
		if (sceneName == "talkisland")
		{
			_hhand->setVisible(false);
			_hbasket->setVisible(false);
			for (int i = 0; i < _heroFish.size(); i++)
			{
				_talkBg->removeChild(_heroFish.at(i));
			}

			std::ostringstream timeline;
			timeline << sceneName << "/hero" << ".csb";

			_hero->stopAction(_heroChar);
			_heroChar = CSLoader::createTimeline(timeline.str());
			_hero->runAction(_heroChar);
			_heroChar->play("h_die", false);
			_totalAnswer = -1;
			_heroChar->setAnimationEndCallFunc("h_die", CC_CALLBACK_0(Talk::gameEnd, this));
			_enemyFish.clear();
			_allSentense.clear();
		}
		else
		{
			_menuContext->showScore();
			this->unscheduleUpdate();
		}
	}
}

void Talk::gameEnd()
{
	_hero->stopAction(_heroChar);
	_enemy->stopAction(_enemyChar);
	Talk::displayWord();
}

void Talk::addEvents(struct LabelDetails sprite)
{
	auto listener = cocos2d::EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = [=] (cocos2d::Touch *touch, cocos2d::Event *event)
	{
		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		Point locationInNode = target->convertToNodeSpace(touch->getLocation());
		Size size = target->getContentSize();
		Rect rect = Rect(0, 0, size.width, size.height);

		if (rect.containsPoint(locationInNode) && _handFlag == 0)
		{
			if (sceneName == "talkisland" || sceneName == "talkcity" || sceneName == "talkjungle")
			{
				_hero->stopAction(_heroChar);
				_enemy->stopAction(_enemyChar);

				std::ostringstream spriteName, herotime, enemytime;
				if(sceneName == "talkjungle")
					spriteName << sceneName<< "/meat" << (rand() % (6-1) + 1) << ".png";
				else
					spriteName << sceneName << "/fish" << (rand() % (6 - 1) + 1) << ".png";
				herotime << sceneName << "/hero" << ".csb";
				enemytime << sceneName << "/enemy" << ".csb";

				_heroChar = CSLoader::createTimeline(herotime.str());
				_enemyChar = CSLoader::createTimeline(enemytime.str());
				_hero->runAction(_heroChar);
				_enemy->runAction(_enemyChar);
				_fish = Sprite::createWithSpriteFrameName(spriteName.str());
				_talkBg->addChild(_fish);

				int pos = std::find(_scene.begin(), _scene.end(), sceneName) - _scene.begin();
				if (sprite.answer == 'c')
				{
					_fish->setPosition(Vec2(differntSceneMapping.at(_scene.at(pos)).at("hero") , visibleSize.height));
					_heroChar->play("h_correct", true);
					_enemyChar->play("e_wrong", true);
					sprite.label->setColor(Color3B::GREEN);
					_correctAnswer++;

					if (_helpFlag == 1)
					{
						_helpFlag = -1;
						removeChild(_help);
					}
					_menuContext->addPoints(1);
				}
				else
				{
					_fish->setPosition(Vec2(differntSceneMapping.at(_scene.at(pos)).at("enemy"), visibleSize.height));
					_heroChar->play("h_wrong", true);
					_enemyChar->play("e_correct", true);
					sprite.label->setColor(Color3B::RED);
				}
				_action = MoveTo::create(3, Vec2(_fish->getPositionX(), 0));
				_fish->runAction(_action);
				_handFlag = 1;
				_totalCount++;
				cocos2d::Director::getInstance()->getEventDispatcher()->removeEventListenersForTarget(sprite.sprite);
			}
			return true;
		}
		return false;
	};

	cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener->clone(), sprite.sprite);
}
