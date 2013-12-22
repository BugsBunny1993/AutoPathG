//
//  AutoPathG.h
//  AutoPathG
//
//  Created by Kowalski on 12/22/13.
//
//

#ifndef __AutoPathG__AutoPathG__
#define __AutoPathG__AutoPathG__

#include <iostream>
#include "cocos2d.h"
USING_NS_CC;
/*
 #include AutoPathG.h
 
 class MyClass :public AutoPathGDelegate{...}
 
 AutoPathG *path_finder;
    path_finder=AutoPathG::alloc();
    path_finder->retain();
    path_finder->init(CCTMXTidleMap->getMapSize...., this);
    path_finder->setFindPoints(ccp(2,8),ccp(7,6));
    
 get Result to process:
 
 delegate:
 AutoPathGdidFindPath(ccArray* path,bool secussed){
        if(secussed==false){
                dead end....
                return..
        }
        ccsquence......
        CCObject *obj;
        cc_array_for_each(path,obj){
            pathInformation *path_info;
                path_info=(pathInformation*)obj;
                ccsquence..add ccMoveTo(  convertGID to openGL location (path_info->getPoint()  ...
        }
 
        ccsprte -> runAction (ccsequence.....
}
 
 end:.
 
 cc_safr_release_null( path_finder)l
 */
class pathInformation:public CCObject{
    friend class AutoPathG;
    CCPoint m_point;
public:
    CCPoint getPoint(){
        return m_point;
    }
};

class AutoPathGDelegate{
public:
    //ask you is here empty:
    //retuen ture means empty
            //false means here is wall or some thing sort of.
    virtual bool AutoPathGIsEmpty(CCPoint grid_point)
    {CC_UNUSED_PARAM(grid_point);return true;}
    virtual void AutoPathGdidFindPath(CCArray* path,bool secussed)
    {CC_UNUSED_PARAM(path);CC_UNUSED_PARAM(secussed);}
};

//Dot not use this class you self !
class __AutoPathG_chunk:public CCObject{
    friend class AutoPathG;
    friend class AutoPathGDelegate;
    typedef enum{
        state_open,
        state_close
    } state;

    CCPoint m_GID;
    int m_step;
    __AutoPathG_chunk* m_father;
    state m_state;
    
    
};

class AutoPathG:public CCObject{
public:
    static const unsigned int version=0x1;
    static AutoPathG* alloc();
    void init(CCSize mapSize,AutoPathGDelegate* delegate);
    void setFindPoints(CCPoint start_point,CCPoint end_point);
private:
    //AutoPathG();
    CCSize m_total_size;
    AutoPathGDelegate* m_delegate;
    CCPoint m_start_point;
    CCPoint m_end_point;
    CCArray *m_chunks;
    void start_search();
    void begin_loop();
    int number_of_opend();
    bool is_reach_end_point(__AutoPathG_chunk* ch);
    void process_end(__AutoPathG_chunk* ch);
    bool ask_gid(CCPoint gid);
    void write_chunk(__AutoPathG_chunk* father,CCPoint gid);
    ~AutoPathG();
    
};
#endif /* defined(__AutoPathG__AutoPathG__) */
