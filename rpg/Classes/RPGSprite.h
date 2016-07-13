//
//  RPGSprite.h
//  rpg
//
//  Created by Shyamal  Upadhyaya on 12/07/16.
//
//

#include <stdio.h>
#include <unordered_map>
#include "cocos2d.h"
#include "editor-support/cocostudio/CocoStudio.h"
#include "editor-support/cocostudio/ActionTimeline/CCSkeletonNode.h"
#include "editor-support/cocostudio/ActionTimeline/CCActionTimeline.h"
#include "RPGConfig.h"
#include "StateMachine.h"

#ifndef RPGSprite_h
#define RPGSprite_h

class SkeletonCharacter;

class RPGSprite : public cocos2d::Node {

public:
    RPGSprite();
    
    virtual ~RPGSprite();
    
    static RPGSprite* create(cocos2d::Sprite* sprite, std::unordered_map<std::string, std::string> attributes);
    
    virtual bool initialize(cocos2d::Sprite* sprite, std::unordered_map<std::string, std::string> attributes);
    
    virtual cocos2d::Sprite* getSprite();
    
    virtual void setAttributes(std::unordered_map<std::string, std::string> attributes);
    
    virtual std::unordered_map<std::string, std::string> getAttributes();
    
    CC_SYNTHESIZE(std::string, transitionToChild, TransitionToChild);
    
    CC_SYNTHESIZE(std::string, transitionToParent, TransitionToParent);
    
    CC_SYNTHESIZE(std::string, nextScene, NextScene);
    
    CC_SYNTHESIZE(std::string, clickable, Clickable);
    
    CC_SYNTHESIZE(std::string, fileName, FileName);
    
    CC_SYNTHESIZE(std::string, canSpeak, CanSpeak);
    
    CC_SYNTHESIZE(std::string, defaultAnimationName, DefaultAnimationName);
    
    CC_SYNTHESIZE(std::string, key, Key);
    
    CC_SYNTHESIZE(bool, vicinityToMainCharacter, VicinityToMainCharacter);
    
    virtual void update(float dt);
        
    virtual bool checkVicinityToMainSkeleton(SkeletonCharacter* skeletonCharacter);
    
    virtual SkeletonCharacter* getMainSkeleton();
    
protected:
    cocos2d::Sprite* sprite;
    std::unordered_map<std::string, std::string> attributes;
    SkeletonCharacter* mainSkeleton;
    
};

#endif /* RPGSprite_h */
