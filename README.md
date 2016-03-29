######Linux下重写DNS解析函数(getaddrinfo)
- 这段时间发现这个函数getaddrinfo不好用，而且会莫名其妙获取不到的ip地址，因此按照DNS的格式重新写了函数。
- DNS的文件格式可以参考这篇博客（已经找不到原作者了）[http://biancheng.dnbcw.info/win2003/345723.html](http://biancheng.dnbcw.info/win2003/345723.html)
- 期间会用到抓包工具，wireshark，其应用请自行搜索

######说明
- MyDNS.c是主要的实现，MyDNS.h当然是头文件
- Maic中将实现的DNSSend和DNSRecv的应用
- 在linux下运行gcc MyDNS.c Main.c (懒得写Makefile了)然后./a.out 域名（什么域名都可以） 就可以在打印中看到获取到ip地址
- 本代码中发送的DNS服务器是网关192.168.1.1，要是你的网关不是这个，请替换成你自己的网关。或者直接替换至8.8.8.8或114.114.114.114中也可

######抓包说明
- 如下示的Domain数据就是我们要发送的数据。详细请参考代码
![sendbuf.png](http://upload-images.jianshu.io/upload_images/1777184-88cb9d7edb3bcaca.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
- 如下示的Domain数据就是我们要解析的数据。详细请参考代码
![recvbuffer.png](http://upload-images.jianshu.io/upload_images/1777184-4a382c54ee294bb4.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
