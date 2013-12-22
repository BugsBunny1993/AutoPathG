//
//  AutoPathG.cpp
//  AutoPathG
//
//  Created by Kowalski on 12/22/13.
//
//

#include "AutoPathG.h"

AutoPathG* AutoPathG::alloc(){
    AutoPathG *auto_path_g=new AutoPathG();
    auto_path_g->autorelease();
    return auto_path_g;
}

void AutoPathG::init(CCSize mapSize,AutoPathGDelegate* delegate){
    m_total_size=mapSize;
    m_delegate=delegate;
}

void AutoPathG::setFindPoints(CCPoint start_point,CCPoint end_point){
    m_start_point=start_point;
    m_end_point=end_point;
    CC_SAFE_RELEASE_NULL(m_chunks);
    m_chunks=CCArray::create();
    m_chunks->retain();
    this->start_search();
}

void AutoPathG::start_search(){
    auto first_chunk=new __AutoPathG_chunk();
    first_chunk->autorelease();
    first_chunk->m_state=__AutoPathG_chunk::state_open;
    first_chunk->m_father=NULL;
    first_chunk->m_GID=m_start_point;
    first_chunk->m_step=0;
    m_chunks->addObject(first_chunk);
    this->begin_loop();
}

void AutoPathG::begin_loop(){
    while (true) {
        
        
        if(this->number_of_opend()==0){
            m_delegate->AutoPathGdidFindPath(NULL, false);
            return;
        }
        CCObject *obj;
        CCARRAY_FOREACH(m_chunks, obj){
            //check reach end point
            __AutoPathG_chunk *ch=(__AutoPathG_chunk*)obj;
            if (is_reach_end_point(ch)) {
                process_end(ch);
                return;
            }
            
            if (ch->m_state==__AutoPathG_chunk::state_open) {
                //ask gid if avalble
                //search path offset
                CCPoint offses[]={
                    CCPoint(+0.0f, +1.0f),// 8  1  2
                    CCPoint(+1.0f,+1.0f),//  7  [ ] 3
                    CCPoint(+1.0f,+0.0f),//  6   5  4
                    CCPoint(+1.0f,-1.0f),
                    CCPoint(+0.0f,-1.0f),
                    CCPoint(-1.0f,-1.0f),
                    CCPoint(-1.0f,+0.0f),
                    CCPoint(-1.0f,+1.0f)
                };
                
                for (int i=0; i<8; i++) {
                    CCPoint ask_point=ccpAdd(ch->m_GID, offses[i]);
                    bool valeable=ask_gid(ask_point);
                    if (valeable) {
                        write_chunk(ch, ask_point);
                    }
                }
                ch->m_state=__AutoPathG_chunk::state_close;
            }
            
        }
    }
    
}

bool AutoPathG::ask_gid(CCPoint gid){
    
    //check: is out of map area?
    if (gid.x<0||gid.x>m_total_size.width-1||gid.y<0||gid.y>m_total_size.height-1) {
        return false;
    }
    
    //check: is this place are empty?
    if(m_delegate->AutoPathGIsEmpty(gid)==false){
        return false;
    }
    
    //check: is this place i already checked bedore?
    CCObject *obj;
    CCARRAY_FOREACH(m_chunks, obj){
        __AutoPathG_chunk *ch=(__AutoPathG_chunk*)obj;
        if (ch->m_GID.equals(gid)) {
            return false;
        }
    }
    
    //no problem
    return true;
}
void AutoPathG::write_chunk(__AutoPathG_chunk* father,CCPoint gid){
    auto chunk=new __AutoPathG_chunk();
    chunk->autorelease();
    chunk->m_state=__AutoPathG_chunk::state_open;
    chunk->m_father=father;
    chunk->m_GID=gid;
    chunk->m_step=father->m_step+1;
    m_chunks->addObject(chunk);
}

bool AutoPathG::is_reach_end_point(__AutoPathG_chunk *ch){
    if (ch->m_GID.equals(m_end_point)) {
        return true;
    }
    return false;
}

void AutoPathG::process_end(__AutoPathG_chunk* ch){
    CCArray *final_result=CCArray::create();
    do {
        pathInformation *info=new pathInformation();
        info->autorelease();
        info->m_point=ccp(ch->m_GID.x, ch->m_GID.y);
        final_result->addObject(info);
        CCLog("path:GID:x %0.0f y:%0.0f step:%i",ch->m_GID.x,ch->m_GID.y,ch->m_step);
        ch=ch->m_father;
    } while (ch->m_father!=NULL);
    m_delegate->AutoPathGdidFindPath(final_result, true);
}


int AutoPathG::number_of_opend(){
    int result=0;
    CCObject *obj;
    CCARRAY_FOREACH(m_chunks, obj){
        __AutoPathG_chunk *ch=(__AutoPathG_chunk*)obj;
        if (ch->m_state==__AutoPathG_chunk::state_open) {
            result++;
        }
    }
    return result;
    
}

AutoPathG::~AutoPathG(){
    CC_SAFE_RELEASE_NULL(m_chunks);
}

