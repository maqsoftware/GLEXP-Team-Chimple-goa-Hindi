//
//  ScrollableGameMapScene.cpp
//  safari
//
//  Created by Shyamal  Upadhyaya on 11/08/16.
//
//

#include "ScrollableGameMapScene.hpp"
#include "alphamon/SelectAlphamonScene.h"
#include "puzzle/DuelScene.h"
#include "puzzle/WordScene.h"
#include "mini_games/PatchTheWallScene.h"
#include "mini_games/CrossTheBridgeScene.h"
#include "mini_games/SmashTheRockScene.h"
#include "mini_games/EndlessRunner.h"
#include "mini_games/Cannon_Ball_Main.h"
#include "mini_games/Jasmin_Mainfile.h"
#include "mini_games/jazz.h"
#include "mini_games/TraceScene.h"
#include "mini_games/AlphamonFeedScene.h"
#include "StartMenuScene.h"
#include "mini_games/Baja.h"
#include "mini_games/Chain.h"
#include "puzzle/PegWord.h"
#include "puzzle/WordBoard.h"
#include "mini_games/Wembley.h"
#include "mini_games/BajaWordScene.h"
USING_NS_CC;

ScrollableGameMapScene::ScrollableGameMapScene()
{
    
}

ScrollableGameMapScene::~ScrollableGameMapScene() {
    
}

Scene *ScrollableGameMapScene::createScene() {
    auto scene = Scene::create();
    auto layer = ScrollableGameMapScene::create();
    scene->addChild(layer);
    layer->menuContext = MenuContext::create(layer);
    scene->addChild(layer->menuContext);
    return scene;
}


bool ScrollableGameMapScene::init() {
    if(!ScrollView::init())
    {
        return false;
    }
    
    
    std::string ICONS = ICON_FOLDER;
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    _layer = Layer::create();
    
    std::vector<std::string> games = StartMenu::getGameNames();
    const int numRows = NUMBER_OF_BUTTONS_ROWS;
    const int numCols = NUMBER_OF_BUTTONS_COLS;
    
    const int numberOfPages = ceil((float) games.size() / (numRows * numCols));
    
    int index = 0;
    int initialYOffSet = 1;
    
    for(int k = 0; k < numberOfPages; k++) {
        
        for (int i = 0; i < numRows; i++) {
            for (int j = 0; j < numCols; j++) {
                if(index < games.size()) {
                    std::string gameName = games.at(index);
                    
                    std::string buttonNormalIcon = ICONS + "/" + games.at(index)+".png";
                    std::string buttonPressedIcon = ICONS + "/" + games.at(index)+"_pressed.png";
                    cocos2d::ui::Button* button = ui::Button::create(buttonNormalIcon, buttonPressedIcon);
                    button->setName(games.at(index));
                    button->setPosition(Vec2(k * visibleSize.width + (j + 0.5) * visibleSize.width / numCols, visibleSize.height - (2 * i + initialYOffSet) * (visibleSize.height / numCols) - 30));
                    
                    button->addTouchEventListener(CC_CALLBACK_2(ScrollableGameMapScene::gameSelected, this));
                    
                    _layer->addChild(button);
                    
                    
                }
                index++;
            }
        }
    }
    
    _layer->setContentSize(Size(visibleSize.width * numberOfPages, visibleSize.height));
    _layer->setPosition(Vec2(0, 0));
    addChild(_layer);
    setContentSize(visibleSize);
    setDirection(cocos2d::ui::ScrollView::Direction::HORIZONTAL);
    setInnerContainerSize(_layer->getContentSize());
    setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::GRADIENT);
    setBackGroundColor(Color3B(255, 159, 0), Color3B::WHITE);
    return true;
}



void ScrollableGameMapScene::gameSelected(Ref* pSender, ui::Widget::TouchEventType eEventType)
{
    cocos2d::ui::Button* clickedButton = dynamic_cast<cocos2d::ui::Button *>(pSender);
    switch (eEventType) {
        case ui::Widget::TouchEventType::BEGAN:
            break;
        case ui::Widget::TouchEventType::MOVED:
            break;
        case ui::Widget::TouchEventType::ENDED:
        {
            clickedButton->setEnabled(false);
            if(clickedButton->getName() == PATCH_THE_WALL) {
                Director::getInstance()->replaceScene(PegWord::createScene());
            } else if(clickedButton->getName() == CROSS_THE_BRIDGE) {
                //Director::getInstance()->replaceScene(CrossTheBridge::createScene());
                Director::getInstance()->replaceScene(Chain::createScene());
            } else if(clickedButton->getName() == PATCH_THE_WALL) {
                Director::getInstance()->replaceScene(PatchTheWall::createScene());
            } else if(clickedButton->getName() == SMASH_THE_ROCK) {
                Director::getInstance()->replaceScene(jazz::createScene());
            } else if(clickedButton->getName() == CANNON_BALL) {
                Director::getInstance()->replaceScene(Jasmin_Mainfile::createScene());
            } else if(clickedButton->getName() == ENDLESS_RUNNER) {
                Director::getInstance()->replaceScene(BajaWordScene::createScene());
            } else if(clickedButton->getName() == KUNG_FU_ALPHA) {
                //Director::getInstance()->replaceScene(Trace::createScene(0));
                Director::getInstance()->replaceScene(Wembley::createScene());
            } else if(clickedButton->getName() == ALPHAMON_FEED) {
                Director::getInstance()->replaceScene(AlphamonFeed::createScene());
            }
            break;
        }
            
        case ui::Widget::TouchEventType::CANCELED:
            break;
        default:
            break;
    }
    
}
