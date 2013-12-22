AutoPathG
=========

BFS for cocos2dx  By Kowalski QQ:547098469

这次不写英文了。

科沃斯基是动画片《马达加斯加》里个子最高，最聪明的企鹅了。 但是有一天，它被一个看起来很龌龊的迷宫拦住了。
于是它决定写个广度优先的算法，最终在这个算法的帮助下它走出了迷宫。

 A*速度快内存占用小，可以绕开地图上的一般障碍物，但是当障碍物变得复杂，
呈U型，甚至干脆是一个迷宫，这时A*算法将无法保证最短路径，甚至求不出路径。这时候BFS就可派上用场了。

而BFS是通过遍历所有的叶子节点来判断路径，所以，速度比A*慢一点，然后比A*更吃内存。但是能够保证路径是最短的，而且不管有多复杂

实际使用来看，虽然消耗更多CPU，但CPU很快，所以并没感觉到怎么个慢法。 虽然消耗大量的内存，但是比起你的贴图来，那真是小巫见大巫了

所以，根据自己实际情况来选择那一种算法。

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
