# 新一代网络教育
      
总计：15个h文件   15个cpp文件  9个UI表单文件 
## 文件分析   
### `01-administrate.cpp`  

个人信息管理模块  继承于QWidget
主要干5件事  3个槽函数  
```  
* 打开数据库
* 初始化init()
slots:
	* 更新时间
	* 更改用户信息
	* 保存用户信息
	* 初始化，  
	* 打开数据库，
	* 设置标签属性和状态，
	* 设置用户学习路径表
	* 用户学习记录表
	* 打开数据库
```  
相关文件：initial.h


### `02-attribution.cpp`  
主要干3件事
```
	* init()       初始化       有待改进  
	* openDB()     打开数据库
	* openXml()    读模式知识的特征   解析xml文件   能正常解析，说明文件路径没有问题。但是，有时候解析的过程可能存在延时。
```


### `03-clickablelabel.cpp`

比普通label，增加一个clicked信号
重写了QLabel的虚函数 mousePressEvent()和mouseReleaseEvent()  发出clicked()信号

### `04-cogmodel.cpp`
这里面定义了一个class cogmodel;
都是一些简单的取值跟赋值接口。就是存取用户认知模型信息的accessors

相关头文件：user.h   是用户信息的一部分

### `05-initial.cpp`  难1
全局变量
```
extern user myUser;
QString currentKid;
```

主要干了10件事   6个自定义槽函数
```
* 初始化工作  init()  eg:打开数据库，初始化可点击图片(这部分可以使用提升类，进行优化)，继续初始化myUser;
* 打开数据库
* 显示第一个知识点
----
* 更新时间  
4大模块   4个可点击label图片  
* 进入知识库查看模块 knowledge.h
* 进入教学模块       teach.h
* 进入测试模块       test.h
* 进入个人信息模块   administrate.h
* 更新当前正在学习的知识点的显示
* 关闭系统
```

相关文件：
```
主
knowledge.h
teach.h
test.h
administrate.h

次
clickablelabel.h
user.h  cogmodel.h
```

### `06-knowledge.cpp`  
类knowledge   继承于QWidget

主要干了10件事   1个自定义槽函数
```
在knowledge构造函数，generateNodes()用来生成初始图形 （准备地说是generateNodes->setNodesCoordinate）  具体在什么地方一开始绘图，还存在疑惑
* getSuccessors()         从数据库中获得后继结点关系
* getPredecessors()       从数据库中获得前驱结点关系
* generateNodes()         从数据库中结点信息生成结点
* setNodesCoordinate()    设置结点坐标
* getAttributesFromDB()   从数据库获得属性值
* getAttributeByPosition()  依据位置信息获得属性信息
* 重写两个鼠标事件
* mouseMoveEvent()   鼠标移动事件
* mousePressEvent()  鼠标点击事件
----
* trackLearning()      根据用户学习轨迹变换结点颜色
* getLearningTrack()   获取学生的学习轨迹，赋值给nodesInPic
```
`paintEvent`  
相关文件：node.h   attribution.h

附相关图：
### `07-login.cpp`
类login   继承于QMainWindow

NOTE:
YMM在cpp文件里面定义了一个全局的user myUser;

主要干两件事
```
* 触发登录事件  2个相关slot 
* 触发注册事件  1个相关slot
```

相关头文件  initial.h   registor.h  user.h


### `08-mypushbutton.cpp`  

自定义的pushbutton   主要是为了点击按钮的时候，可以传送按钮的内容
重写了QPushButton的虚函数 mousePressEvent()和mouseReleaseEvent()  
发出clicked(this->text())信号  

相关头文件：teach.h


### `09-node.cpp`
结点类class Node，主要用来画知识点图形的。

都是一些简单的取值跟赋值接口。就是存取结点（知识点）信息的accessors

相关头文件：knowledge.h

### `10-registor.cpp`
主要干两件事

```
* 注册用户
注册时，与数据库有关联。
涉及一些密码正确？用户是否重复？等等问题
* 关闭注册界面  
```

### `11-main.cpp`

主程序  
包含一个登录窗口 login w; w.show();

### `12-teach.cpp`

类knowledge   继承于QWidget
11件事       8个槽函数
```
* 初始化 init()
* openDatabase()
* openXml(QString)   解析模式知识的信息
* -------slots
* timeUpdateSlot()   更新系统时间  
* 重新播放案例  playAgainSlot()
* 更换案例      changeCaseSlot()   似乎有点问题
* 进入讨论区    goToDiscussionSlot()   没有填写
* 进入测试      goToTestSlot()
* 关闭系统
* openUsecaseSlot()    打开教学案例
* showDomainKnowledgesSlot()  展现领域知识信息
* updateBehaviorTableSlot()     usecase关闭的时候，需要更新行为记录表
* updateCurrentKidSlot()     没有调用的函数来调用这个
* testSlot()                 没有调用的函数来调用这个
```
相关的头文件： initial.h   usecase.h

### `13-test.cpp`

主要干8件事   6个槽函数
```
init()初始化
openDatabase()打开数据库
timeUpdateSlot()更新系统时间
restTimeUpdateSlot()剩余时间更新
startTestSlot()开始测试     主要涉及选择题以及选项的排版 
submitTestSlot()提交测试    涉及算分，查询清空之前的选项（没有更好的方法？），通过测试之后的againButton的设计   更新用户测试记录  更新学习行为记录表  更新路径推荐表 等  更新学习路径记录表   等等。。。
nextKnowledgeSlot()下一个知识
againKnowledgeSlot()重新学习当前知识
```

### `14-usecase.cpp`

主要干4个件事   2个槽函数  
```
* 打开数据库
* 初始化
* slots--------
* 更新系统时间
* 进入到测试窗口   bug:貌似有点问题
```

### `15-user.cpp`
 
这里面定义了一个class user;
都是一些简单的取值跟赋值接口。就是存取用户信息的accessors
相关头文件：cogmodel.h

## 欢迎大家提意见，一起找bug。

