//
//  game.h
//  AutoPathG
//
//  Created by Kowalski on 12/21/13.
//
//

#ifndef __AutoPathG__game__
#define __AutoPathG__game__

#include <iostream>
#define res_tmx_map "tmw_desert_spacing.tmx"
#define res_mp3_background "background.mp3"
#define res_plist_frameCache_kowalski "role.plist"
//#define res_png_frameCache_kowalski "role.png"
#include "cocos2d.h"
#include "SimpleAudioEngine.h"

#include "AutoPathG.h"
using namespace CocosDenshion;
USING_NS_CC;
class game:public CCLayer,public AutoPathGDelegate{
public:
    CREATE_FUNC(game);
    virtual bool init();
    static CCScene* scene();
    
    //functions####====----
    enum{
        tag_map=1,
        tag_kowalski=2
    };
    
    CCTMXLayer *labyrinth;
    void load_background_music();
    void load_map();
    void load_animation_kowalski();
    
    virtual bool AutoPathGIsEmpty(CCPoint grid_point);
    virtual void AutoPathGdidFindPath(CCArray* path,bool secussed);
    
};

#endif /* defined(__AutoPathG__game__) */
