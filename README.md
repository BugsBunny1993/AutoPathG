AutoPathG
=========

BFS for cocos2dx  By Kowalski QQ:547098469

这次不写英文了。

科沃斯基是动画片《马达加斯加》里个子最高，最聪明的企鹅了。 但是有一天，它被一个看起来很龌龊的迷宫拦住了。
于是它决定写个广度优先的算法，最终在这个算法的帮助下它走出了迷宫。


＝＝＝＝＝注意＝＝＝＝
这个演示程序只能在MacOS-64bit上运行，其他平台， 得把代码里分辨率改为1136*640
运行时放到cocos2dx的project目录下


API用法如下

导入头文件：
 #include AutoPathG.h
 
 实现delegate里的方法,程序会通过delegate询问你地图上的某个点是否可用，以及告诉你结果
 class MyClass :public AutoPathGDelegate{...}
 
 初始化寻道器
 AutoPathG *path_finder;
    path_finder=AutoPathG::alloc();
    path_finder->retain();
    
    设置地图大小和delegate
    path_finder->init(CCTMXTidleMap->getMapSize...., this);
    
   设置起点和终点
    path_finder->setFindPoints(ccp(2,8),ccp(7,6));
    
 处理获得的结果，
 
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
 
 
 
 By Kowalski QQ:547098469
