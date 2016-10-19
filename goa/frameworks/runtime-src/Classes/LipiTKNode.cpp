//
//  LipiTKNode.cpp
//  Hello
//
//  Created by Shyamal.Upadhyaya on 14/10/16.
//
//

#include "LipiTKNode.h"
#include "lang/LangUtil.h"
#include <algorithm>

USING_NS_CC;

LipiTKNode::LipiTKNode():
_canvasWidth(0),
_canvasHeight(0),
_currentStroke(),
_lipiTKInterface(nullptr),
_isTouchEndedOrMovedOut(false)
{
    
}


LipiTKNode::~LipiTKNode() {
    _canvas->release();
    _brush->release();
}


LipiTKNode* LipiTKNode::create(int width, int height, Point position, int opacity)
{
    auto node = new LipiTKNode();
    if (node && node->initialize(width, height, position, opacity)) {
        node->autorelease();
        return node;
    }
    CC_SAFE_DELETE(node);
    return nullptr;
}


Sprite* LipiTKNode::createDrawingAreaWithColor(Vec2 anchorPoint, Vec2 position, float opacity,const Color3B& color) {
    _drawingBoard = Sprite::create();
    _drawingBoard->setName("_drawingBoard");
    _drawingBoard->setTextureRect(Rect(0, 0, _canvasWidth, _canvasHeight));
    _drawingBoard->setAnchorPoint(Vec2(0.5,0.5));
    _drawingBoard->setColor(Color3B::RED);
    _drawingBoard->setOpacity(opacity);
    _drawingBoard->setPosition(position);
    
    return _drawingBoard;
}

Sprite* LipiTKNode::createDrawingAreaUsingFileName(Vec2 anchorPoint, Vec2 position, float opacity, std::string fileName) {
    _drawingBoard = Sprite::create(fileName);
    _drawingBoard->setName("_drawingBoard");
    _drawingBoard->setTextureRect(Rect(0, 0, _canvasWidth, _canvasHeight));
    _drawingBoard->setAnchorPoint(Vec2(0.5,0.5));
    _drawingBoard->setColor(Color3B::RED);
    _drawingBoard->setOpacity(opacity);
    _drawingBoard->setPosition(position);
    
    return _drawingBoard;
}

bool LipiTKNode::initialize(int width, int height, Point position, int opacity) {
    _lipiTKInterface = LipiTKInterface::getInstance("res");
    _canvasWidth = width;
    _canvasHeight = height;
    
    // create a canvas to draw on
    _canvas = RenderTexture::create(_canvasWidth, _canvasHeight, kCCTexture2DPixelFormat_RGBA8888);
    _canvas->retain();
    
    // init the brush tip
    _brush = Sprite::create("largeBrush.png");
    _brush->retain();
    
    _paintingNode = DrawNode::create();
    addChild(_paintingNode);
    
    
    _drawingBoard = createDrawingAreaWithColor(Vec2(0.5,0.5), position, opacity, Color3B::RED);
    addChild(_drawingBoard, 1);
    
    auto listenerTouches = EventListenerTouchOneByOne::create();
    listenerTouches->setSwallowTouches(true);
    listenerTouches->onTouchBegan = CC_CALLBACK_2(LipiTKNode::onTouchBegan, this);
    listenerTouches->onTouchMoved = CC_CALLBACK_2(LipiTKNode::onTouchMoved, this);
    listenerTouches->onTouchEnded = CC_CALLBACK_2(LipiTKNode::touchEnded, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenerTouches, this);

    Vec2 clearButtonPos = Vec2(_drawingBoard->getBoundingBox().size.width - 15,_drawingBoard->getBoundingBox().size.height - 15);
    
    _clearButton = this->createButton("menu/help.png", "menu/help.png", "menu/help.png", clearButtonPos);
    
    return true;
}


cocos2d::ui::Button* LipiTKNode::createButton(const std::string normalImage,
                                                 const std::string selectedImage ,
                                                 const std::string disableImage,
                                              Vec2 position) {
    cocos2d::ui::Button* button = cocos2d::ui::Button::create(normalImage, selectedImage, disableImage, cocos2d::ui::Widget::TextureResType::LOCAL);
    button->setPosition(position);
    _drawingBoard->addChild(button);
    
    button->addTouchEventListener(CC_CALLBACK_2(LipiTKNode::clearDrawing, this));
    
    return button;
}


void LipiTKNode::clearDrawing(cocos2d::Ref *pSender, cocos2d::ui::Widget::TouchEventType eEventType) {
    if(eEventType == cocos2d::ui::Widget::TouchEventType::ENDED) {
        _paintingNode->clear();
        _canvas->clear(0, 0, _canvasWidth, _canvasHeight);
        _strokes.clear();
        clearPrintedCharacters();
    }
}


void LipiTKNode::clearPrintedCharacters() {
    EventCustom event("clearPrintedCharacters");
    _eventDispatcher->dispatchEvent(&event);
}


bool LipiTKNode::onTouchBegan(Touch *touch, Event *event)
{
    if(checkTouchOnDrawingBoard(touch, event))
    {
        clearPrintedCharacters();
        Point n = this->convertTouchToNodeSpace(touch);
        _currentStroke = new Stroke();
        CCLOG("touch begin Point x: %f and y %f", n.x, n.y);
        _currentStroke->addPoints(n.x, n.y);
        return true;
    }
    return false;
}

bool LipiTKNode::checkTouchOnDrawingBoard(cocos2d::Touch * touch, cocos2d::Event * event) {
    Point n = this->convertTouchToNodeSpace(touch);
    auto target = event->getCurrentTarget();
    
    auto drawingBoard = target->getChildByName("_drawingBoard");
    
    if(drawingBoard) {
        Rect boundingBoxRectToCheck = drawingBoard->getBoundingBox();
        if(boundingBoxRectToCheck.containsPoint(n)) {
            _isTouchEndedOrMovedOut = true;
            return true;
        }
    }
    
    return false;
}

void LipiTKNode::onTouchMoved(cocos2d::Touch * touch, cocos2d::Event * event)
{
    if(checkTouchOnDrawingBoard(touch, event)) {
        auto curDrawingPoint = touch->getLocation();
        Point n = this->convertTouchToNodeSpace(touch);
        CCLOG("touch move Point x: %f and y %f", n.x, n.y);
        _currentStroke->addPoints(n.x, n.y);
        _paintingNode->drawSegment(touch->getPreviousLocation(), curDrawingPoint, 5, Color4F(14 / 255.0f, 221 / 255.0f, 23 / 255.0f, 1.0f));
    } else {
        if(_isTouchEndedOrMovedOut) {
            processLipiTK();
        }
    }
}

void LipiTKNode::touchEnded(Touch *touch, Event *event)
{
 
    if(checkTouchOnDrawingBoard(touch, event)) {
        Point n = this->convertTouchToNodeSpace(touch);
        CCLOG("touch ended Point x: %f and y %f", n.x, n.y);
        _currentStroke->addPoints(n.x, n.y);
    }
    
    if(_isTouchEndedOrMovedOut) {
        processLipiTK();
    }
}

void LipiTKNode::processLipiTK() {
    _isTouchEndedOrMovedOut = false;
    _strokes.push_back(_currentStroke);
    lipiProcessTask = new LipiTKProcessTask(_lipiTKInterface, _strokes, this);
    lipiProcessTask->execute();
}



void LipiTKNode::broadCastRecognizedChars(std::vector<std::string> results) {
    if(!results.empty() && results.size() > 0)
    {
        std::vector<std::string> copiedResults (results.size());
        std::copy(results.begin(), results.end(), copiedResults.begin());
        
        if(!copiedResults.empty() &&  copiedResults.size() > 0)
        {
            for (std::vector<std::string>::iterator it = copiedResults.begin() ; it != copiedResults.end(); ++it)
            {
                std::string alphabet = *it;
                CCLOG("char %s", alphabet.c_str());
            }
            
            EventCustom event("chars_recognized");
            event.setUserData(static_cast<void*>(&copiedResults));
            _eventDispatcher->dispatchEvent(&event);
            
        }
    }
}
