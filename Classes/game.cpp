//
//  game.cpp
//  AutoPathG
//
//  Created by Kowalski on 12/21/13.
//
//

#include "game.h"

CCScene* game::scene(){
    CCScene *sc=CCScene::create();
    game *gm=game::create();
    sc->addChild(gm);
    return sc;
}

bool game::init(){
    if (!CCLayer::init()) {
        return false;
    }
    
   
    this->load_animation_kowalski();
     this->load_map();
    this->load_background_music();
    return true;
}

void game::load_background_music(){
    SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(res_mp3_background);
    SimpleAudioEngine::sharedEngine()->playBackgroundMusic(res_mp3_background, true);
}

void game::load_map(){
    CCTMXTiledMap *map=CCTMXTiledMap::create(res_tmx_map);
    this->addChild(map,tag_map,tag_map);

    CCTMXLayer *layer;
    layer=map->layerNamed("object");
    labyrinth=layer;
    
    AutoPathG *path_finder=AutoPathG::alloc();
    path_finder->init(labyrinth->getLayerSize(), this);
    path_finder->setFindPoints(ccp(1, 18), ccp(32, 1));
}

void game::load_animation_kowalski(){
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(res_plist_frameCache_kowalski);
    
    CCAnimation *animation=CCAnimation::create();
    for (int i=1; i<=11; i++) {
        CCString *frame_name;
        CCSpriteFrame *frame;
        frame_name=CCString::createWithFormat("%i.png",i);
        frame=CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(frame_name->getCString());
        animation->addSpriteFrame(frame);
    }
    animation->setDelayPerUnit(0.07f);
    
    CCSprite *kowalski;
    kowalski=CCSprite::create();
    this->addChild(kowalski, tag_kowalski, tag_kowalski);
    kowalski->setAnchorPoint(ccp(.5f, .0f));
    
    CCAnimate *animate;
    animate=CCAnimate::create(animation);
    CCRepeatForever *repat_play_animation;
    repat_play_animation=CCRepeatForever::create(animate);
    
    kowalski->runAction(repat_play_animation);
    kowalski->setPosition(ccp(300, 300));
    
}


bool game::AutoPathGIsEmpty(CCPoint grid_point){
    if (labyrinth->tileGIDAt(grid_point)==0) {
        return true;
    }
    return false;
}

void game::AutoPathGdidFindPath(CCArray* path,bool secussed){
    //CCLog("secussed :%i",secussed?1:0);
    CCArray *arr=CCArray::create();
    CCObject *obj;
    CCARRAY_FOREACH_REVERSE(path, obj){
        pathInformation* info=(pathInformation*)obj;
        CCPoint tile_position=info->getPoint();
        
        CCPoint p=ccp(tile_position.x, labyrinth->getLayerSize().height-tile_position.y);
        p=ccpMult(p, 32);
        p=ccpAdd(p, ccp(+10, -16));
        arr->addObject(CCMoveTo::create(0.25, p));
    }
    CCSequence *seq=CCSequence::create(arr);
    CCRepeatForever *rep=CCRepeatForever::create(seq);
   CCSprite* kowalski=(CCSprite*) this->getChildByTag(tag_kowalski);
    kowalski->runAction(rep);
}
