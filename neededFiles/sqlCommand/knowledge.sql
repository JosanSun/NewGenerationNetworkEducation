/*
Navicat MySQL Data Transfer

Source Server         : test
Source Server Version : 50610
Source Host           : localhost:3306
Source Database       : knowledge

Target Server Type    : MYSQL
Target Server Version : 50610
File Encoding         : 65001

Date: 2017-08-16 21:06:27
*/

SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for about
-- ----------------------------
DROP TABLE IF EXISTS `about`;
CREATE TABLE `about` (
  `kid` varchar(20) NOT NULL,
  `pors` tinyint(1) NOT NULL DEFAULT '0',
  `kids` text,
  PRIMARY KEY (`kid`,`pors`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of about
-- ----------------------------
INSERT INTO `about` VALUES ('B001', '1', 'B002,B003,B004,B013');
INSERT INTO `about` VALUES ('B002', '0', 'B001');
INSERT INTO `about` VALUES ('B002', '1', 'B004,B005,B006,B007,B010');
INSERT INTO `about` VALUES ('B003', '0', 'B001');
INSERT INTO `about` VALUES ('B003', '1', 'P001');
INSERT INTO `about` VALUES ('B004', '0', 'B001B002');
INSERT INTO `about` VALUES ('B004', '1', 'B008,P001');
INSERT INTO `about` VALUES ('B005', '0', 'B002');
INSERT INTO `about` VALUES ('B005', '1', 'B008,B009,B011,B012,P001');
INSERT INTO `about` VALUES ('B006', '0', 'B002');
INSERT INTO `about` VALUES ('B006', '1', 'B009,B011');
INSERT INTO `about` VALUES ('B007', '0', 'B002');
INSERT INTO `about` VALUES ('B007', '1', 'B010,B013');
INSERT INTO `about` VALUES ('B008', '0', 'B004B005');
INSERT INTO `about` VALUES ('B008', '1', 'P001');
INSERT INTO `about` VALUES ('B009', '0', 'B005B006');
INSERT INTO `about` VALUES ('B009', '1', 'P002');
INSERT INTO `about` VALUES ('B010', '0', 'B002B007');
INSERT INTO `about` VALUES ('B010', '1', 'P003');
INSERT INTO `about` VALUES ('B011', '0', 'B005B006');
INSERT INTO `about` VALUES ('B011', '1', 'P001,P002');
INSERT INTO `about` VALUES ('B012', '0', 'B005');
INSERT INTO `about` VALUES ('B012', '1', 'P001');
INSERT INTO `about` VALUES ('B013', '0', 'B001B007');
INSERT INTO `about` VALUES ('B013', '1', 'P003');
INSERT INTO `about` VALUES ('P001', '0', 'B003,B004,B005,B008,B011,B012');
INSERT INTO `about` VALUES ('P002', '0', 'B009,B011');
INSERT INTO `about` VALUES ('P003', '0', 'B010,B013');

-- ----------------------------
-- Table structure for behavior
-- ----------------------------
DROP TABLE IF EXISTS `behavior`;
CREATE TABLE `behavior` (
  `sid` int(11) NOT NULL,
  `kid` varchar(20) NOT NULL,
  `cid` varchar(20) NOT NULL,
  `begin` datetime NOT NULL,
  `end` datetime DEFAULT NULL,
  `pass` tinyint(1) DEFAULT NULL,
  `note` text,
  PRIMARY KEY (`sid`,`kid`,`cid`,`begin`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of behavior
-- ----------------------------
INSERT INTO `behavior` VALUES ('6', 'B002', 'U003.html', '2017-03-25 08:25:32', '2017-04-08 15:43:12', '0', '');
INSERT INTO `behavior` VALUES ('6', 'B002', 'U003.html', '2017-04-08 15:43:04', '2017-04-08 15:43:12', '1', '');
INSERT INTO `behavior` VALUES ('6', 'B003', 'U003.html', '2017-04-08 20:30:52', '2017-04-09 23:08:09', '0', '');
INSERT INTO `behavior` VALUES ('6', 'B003', 'U003.html', '2017-04-09 23:07:21', '2017-04-09 23:08:09', '0', '');
INSERT INTO `behavior` VALUES ('6', 'B003', 'U004.txt', '2017-04-09 23:11:34', '2017-04-09 23:11:54', '0', '');
INSERT INTO `behavior` VALUES ('6', 'B003', 'U008.swf', '2017-04-09 23:08:16', '2017-04-09 23:11:34', '0', '');
INSERT INTO `behavior` VALUES ('6', 'B003', 'U008.swf', '2017-04-09 23:11:29', '2017-04-09 23:11:34', '1', '');
INSERT INTO `behavior` VALUES ('6', 'B004', 'U005.ppt', '2017-04-11 21:20:11', '2017-04-11 21:20:45', '1', null);
INSERT INTO `behavior` VALUES ('6', 'B005', 'U002.ppt', '2017-04-11 21:22:38', '2017-04-11 21:33:31', '1', null);
INSERT INTO `behavior` VALUES ('6', 'P001', 'U002.ppt', '2017-04-10 20:27:27', '2017-04-20 22:06:07', '0', null);
INSERT INTO `behavior` VALUES ('6', 'P001', 'U002.ppt', '2017-04-20 22:02:46', '2017-04-20 22:06:07', '0', null);
INSERT INTO `behavior` VALUES ('6', 'P001', 'U005.ppt', '2017-04-11 20:52:35', '2017-05-21 10:04:20', '0', '');
INSERT INTO `behavior` VALUES ('6', 'P001', 'U005.ppt', '2017-05-21 10:02:42', '2017-05-21 10:04:20', '0', '');
INSERT INTO `behavior` VALUES ('6', 'P001', 'U005.ppt', '2017-05-21 10:04:04', '2017-05-21 10:04:20', '0', '');
INSERT INTO `behavior` VALUES ('6', 'P001', 'U008.swf', '2017-04-10 20:27:49', '2017-05-25 19:40:24', '0', '');
INSERT INTO `behavior` VALUES ('6', 'P001', 'U008.swf', '2017-04-24 23:00:30', '2017-05-25 19:40:24', '0', '');
INSERT INTO `behavior` VALUES ('6', 'P001', 'U008.swf', '2017-05-21 10:02:33', '2017-05-25 19:40:24', '0', '');
INSERT INTO `behavior` VALUES ('6', 'P001', 'U008.swf', '2017-05-25 19:37:11', '2017-05-25 19:40:24', '0', '');

-- ----------------------------
-- Table structure for bk
-- ----------------------------
DROP TABLE IF EXISTS `bk`;
CREATE TABLE `bk` (
  `bid` varchar(20) NOT NULL,
  `title` text,
  `domain` text,
  `description` text,
  PRIMARY KEY (`bid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of bk
-- ----------------------------
INSERT INTO `bk` VALUES ('B001', '常量', '数据表示,C++', './knowledge/description/常量.txt');
INSERT INTO `bk` VALUES ('B002', '变量', '数据表示,C++', './knowledge/description/变量.txt');
INSERT INTO `bk` VALUES ('B003', '枚举', '数据结构,C++', './knowledge/description/枚举.txt');
INSERT INTO `bk` VALUES ('B004', '结构体', '数据结构,C++', './knowledge/description/结构体.txt');
INSERT INTO `bk` VALUES ('B005', '数组', '数据结构,C++', './knowledge/description/数组.txt');
INSERT INTO `bk` VALUES ('B006', '指针', '数据表示,C++', './knowledge/description/指针.txt');
INSERT INTO `bk` VALUES ('B007', '引用', '数据表示,C++', './knowledge/description/引用.txt');
INSERT INTO `bk` VALUES ('B008', '结构体数组', '数据结构,C++', './knowledge/description/结构体数组.txt');
INSERT INTO `bk` VALUES ('B009', '数组指针', '数据表示,C++', './knowledge/description/数组指针.txt');
INSERT INTO `bk` VALUES ('B010', '变量引用', '数据表示,C++', './knowledge/description/变量引用.txt');
INSERT INTO `bk` VALUES ('B011', '指针数组', '数据结构,C++', './knowledge/description/指针数组.txt');
INSERT INTO `bk` VALUES ('B012', '多维数组', '数据结构,C++', './knowledge/description/多维数组.txt');
INSERT INTO `bk` VALUES ('B013', '常引用', '数据表示,C++', './knowledge/description/常引用.txt');

-- ----------------------------
-- Table structure for path
-- ----------------------------
DROP TABLE IF EXISTS `path`;
CREATE TABLE `path` (
  `sid` int(11) NOT NULL,
  `domain` text,
  `kid` varchar(20) NOT NULL,
  `begintime` datetime NOT NULL,
  `score` int(11) DEFAULT NULL,
  PRIMARY KEY (`sid`,`kid`,`begintime`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of path
-- ----------------------------
INSERT INTO `path` VALUES ('6', '数据表示,C++', 'B001', '2017-03-19 09:11:12', '100');
INSERT INTO `path` VALUES ('6', '数据表示,C++', 'B002', '2017-03-19 10:12:45', '70');
INSERT INTO `path` VALUES ('6', '数据结构,C++', 'B003', '2017-05-21 10:27:33', '90');

-- ----------------------------
-- Table structure for pk
-- ----------------------------
DROP TABLE IF EXISTS `pk`;
CREATE TABLE `pk` (
  `pid` varchar(20) NOT NULL,
  `title` text,
  `domain` text,
  `pattern` text,
  PRIMARY KEY (`pid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of pk
-- ----------------------------
INSERT INTO `pk` VALUES ('P001', '堆叠模式', '数据表示,C++', './knowledge/pattern/堆叠模式.xml');
INSERT INTO `pk` VALUES ('P002', '指向模式', '数据表示,C++', './knowledge/pattern/指向模式.xml');
INSERT INTO `pk` VALUES ('P003', '绑定模式', '数据表示,C++', './knowledge/pattern/绑定模式.xml');

-- ----------------------------
-- Table structure for recpath
-- ----------------------------
DROP TABLE IF EXISTS `recpath`;
CREATE TABLE `recpath` (
  `sid` int(11) NOT NULL DEFAULT '0',
  `domain` text,
  `kid` varchar(20) NOT NULL,
  `orders` int(11) DEFAULT NULL,
  `state` tinyint(1) DEFAULT NULL,
  PRIMARY KEY (`sid`,`kid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of recpath
-- ----------------------------
INSERT INTO `recpath` VALUES ('6', '数据表示,C++', 'B001', '1', '1');
INSERT INTO `recpath` VALUES ('6', '数据表示,C++', 'B002', '2', '1');
INSERT INTO `recpath` VALUES ('6', '数据结构,C++', 'B003', '3', '1');
INSERT INTO `recpath` VALUES ('6', '数据结构,C++', 'B004', '5', '1');
INSERT INTO `recpath` VALUES ('6', '数据结构,C++', 'B005', '6', '1');
INSERT INTO `recpath` VALUES ('6', '数据表示,C++', 'B006', '9', '0');
INSERT INTO `recpath` VALUES ('6', '数据表示,C++', 'B007', '13', '0');
INSERT INTO `recpath` VALUES ('6', '数据结构,C++', 'B008', '7', '0');
INSERT INTO `recpath` VALUES ('6', '数据表示,C++', 'B009', '10', '0');
INSERT INTO `recpath` VALUES ('6', '数据表示,C++', 'B010', '14', '0');
INSERT INTO `recpath` VALUES ('6', '数据结构,C++', 'B011', '12', '0');
INSERT INTO `recpath` VALUES ('6', '数据结构,C++', 'B012', '8', '0');
INSERT INTO `recpath` VALUES ('6', '数据表示,C++', 'B013', '16', '0');
INSERT INTO `recpath` VALUES ('6', '数据表示,C++', 'P001', '4', '1');
INSERT INTO `recpath` VALUES ('6', '数据表示,C++', 'P002', '11', '0');
INSERT INTO `recpath` VALUES ('6', '数据表示,C++', 'P003', '15', '0');

-- ----------------------------
-- Table structure for student
-- ----------------------------
DROP TABLE IF EXISTS `student`;
CREATE TABLE `student` (
  `sid` int(11) NOT NULL AUTO_INCREMENT,
  `name` text,
  `password` text,
  `sex` text,
  `age` int(11) DEFAULT NULL,
  `education` text,
  `cogform` text,
  `strategy` text,
  `cogstyle` text,
  `cogstructure` text,
  PRIMARY KEY (`sid`)
) ENGINE=InnoDB AUTO_INCREMENT=8 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of student
-- ----------------------------
INSERT INTO `student` VALUES ('1', 'admin', 'admin', null, null, null, null, null, null, null);
INSERT INTO `student` VALUES ('2', '小明', '123456', '女', '25', '硕士', null, null, null, null);
INSERT INTO `student` VALUES ('3', '小良', '199109', '男', '26', '硕士', null, null, null, null);
INSERT INTO `student` VALUES ('4', '小逸', '199004', '男', '27', '硕士', null, null, null, null);
INSERT INTO `student` VALUES ('5', '小红', '196510', '女', '52', '高中', null, null, null, null);
INSERT INTO `student` VALUES ('6', 'xiaoming', 'xiaoming', '男', '21', '本科', null, null, null, null);
INSERT INTO `student` VALUES ('7', 'xiaoding', 'xiaoding', '女', '25', '本科', null, null, null, null);

-- ----------------------------
-- Table structure for teach
-- ----------------------------
DROP TABLE IF EXISTS `teach`;
CREATE TABLE `teach` (
  `kid` varchar(20) NOT NULL,
  `cid` varchar(20) NOT NULL,
  `location` text,
  PRIMARY KEY (`kid`,`cid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of teach
-- ----------------------------
INSERT INTO `teach` VALUES ('B001', 'U001.ppt', './knowledge/usecase/U001.ppsx');
INSERT INTO `teach` VALUES ('B002', 'U001.ppt', './knowledge/usecase/U001.ppsx');
INSERT INTO `teach` VALUES ('B003', 'U003.html', './knowledge/usecase/U003.html');
INSERT INTO `teach` VALUES ('B003', 'U004.txt', './knowledge/usecase/U004.txt');
INSERT INTO `teach` VALUES ('B003', 'U005.ppt', './knowledge/usecase/U005.ppsx');
INSERT INTO `teach` VALUES ('B003', 'U008.swf', './knowledge/usecase/U008.swf');
INSERT INTO `teach` VALUES ('B004', 'U005.ppt', './knowledge/usecase/U005.ppsx');
INSERT INTO `teach` VALUES ('B005', 'U002.ppt', './knowledge/usecase/U002.ppsx');
INSERT INTO `teach` VALUES ('B005', 'U006.ppt', './knowledge/usecase/U006.ppsx');
INSERT INTO `teach` VALUES ('B006', 'U006.ppt', './knowledge/usecase/U006.ppsx');
INSERT INTO `teach` VALUES ('B007', 'U007.ppt', './knowledge/usecase/U007.ppsx');
INSERT INTO `teach` VALUES ('B008', 'U005.ppt', './knowledge/usecase/U005.ppsx');
INSERT INTO `teach` VALUES ('B009', 'U006.ppt', './knowledge/usecase/U006.ppsx');
INSERT INTO `teach` VALUES ('B010', 'U007.ppt', './knowledge/usecase/U007.ppsx');
INSERT INTO `teach` VALUES ('B011', 'U006.ppt', './knowledge/usecase/U006.ppsx');
INSERT INTO `teach` VALUES ('B012', 'U002.ppt', './knowledge/usecase/U002.ppsx');
INSERT INTO `teach` VALUES ('B013', 'U007.ppt', './knowledge/usecase/U007.ppsx');
INSERT INTO `teach` VALUES ('P001', 'U002.ppt', './knowledge/usecase/U002.ppsx');
INSERT INTO `teach` VALUES ('P001', 'U005.ppt', './knowledge/usecase/U005.ppsx');
INSERT INTO `teach` VALUES ('P001', 'U008.swf', './knowledge/usecase/U008.swf');
INSERT INTO `teach` VALUES ('P002', 'U006.ppt', './knowledge/usecase/U006.ppsx');
INSERT INTO `teach` VALUES ('P002', 'U008.swf', './knowledge/usecase/U008.swf');
INSERT INTO `teach` VALUES ('P003', 'U007.ppt', './knowledge/usecase/U007.ppsx');
INSERT INTO `teach` VALUES ('P003', 'U008.swf', './knowledge/usecase/U008.swf');

-- ----------------------------
-- Table structure for test
-- ----------------------------
DROP TABLE IF EXISTS `test`;
CREATE TABLE `test` (
  `kid` varchar(20) NOT NULL,
  `tid` varchar(20) NOT NULL,
  `testhour` int(11) DEFAULT NULL,
  `testminute` int(11) DEFAULT NULL,
  `limitscore` int(11) DEFAULT NULL,
  PRIMARY KEY (`kid`,`tid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of test
-- ----------------------------
INSERT INTO `test` VALUES ('B001', 'T001', '0', '20', '60');
INSERT INTO `test` VALUES ('B002', 'T002', '0', '15', '60');
INSERT INTO `test` VALUES ('B003', 'T003', '0', '15', '60');
INSERT INTO `test` VALUES ('B004', 'T004', '0', '30', '60');
INSERT INTO `test` VALUES ('B005', 'T006', '0', '45', '60');
INSERT INTO `test` VALUES ('B006', 'T011', '0', '45', '60');
INSERT INTO `test` VALUES ('B008', 'T007', '0', '45', '60');
INSERT INTO `test` VALUES ('B012', 'T008', '0', '45', '60');
INSERT INTO `test` VALUES ('P001', 'T007', '0', '45', '60');

-- ----------------------------
-- Table structure for testcase
-- ----------------------------
DROP TABLE IF EXISTS `testcase`;
CREATE TABLE `testcase` (
  `tid` varchar(20) NOT NULL,
  `qid` int(11) NOT NULL,
  `content` text,
  `answer` text,
  `a` text,
  `b` text,
  `c` text,
  `d` text,
  `score` int(11) DEFAULT NULL,
  PRIMARY KEY (`tid`,`qid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of testcase
-- ----------------------------
INSERT INTO `testcase` VALUES ('T001', '1', '可替换#define PI 3.1415926的语句是', 'B', 'float PI 3.1415926;', 'const float PI=3.1415926;', 'const PI(3.1415926);', 'const 3.1415926;', '25');
INSERT INTO `testcase` VALUES ('T001', '2', '下列不是C++语言的基本数据类型的是', 'D', '字符类型', '整数类型', '逻辑类型', '枚举类型', '25');
INSERT INTO `testcase` VALUES ('T001', '3', '设函数void inc(int)将形参加1，如有整型变量int i=10；则执行inc(i)；后，i的值为', 'B', '9', '10', '11', '未知', '25');
INSERT INTO `testcase` VALUES ('T001', '4', '设int &max(int ＆，int &)返回两参数中较大者，如有两整型变量int a=10；int b=15；在执行max(a，b)++后，a，b值分别为', 'C', '10,15', '11,15', '10,16', '1l,16', '25');
INSERT INTO `testcase` VALUES ('T002', '1', '下列符号中，不属于分隔符的是', 'B', ',', '/', ';', '{}', '30');
INSERT INTO `testcase` VALUES ('T002', '2', '在C++中，头文件扩展名为', 'B', '.cpp', '.h', '.lib', '.obj', '30');
INSERT INTO `testcase` VALUES ('T002', '3', '布尔类型标识符是', 'D', 'void', 'short', 'long', 'bool', '40');
INSERT INTO `testcase` VALUES ('T003', '1', '下列枚举类型的定义中，包含枚举值3的是', 'A', 'enum test {RED, YELLOW, BLUE, BLACK};', 'enum test {RED, YELLOW=4, BLUE, BLACK};', 'enum test {RED=-1, YELLOW,BLUE, BLACK};', 'enum test {RED, YELLOW=6, BLUE, BLACK};', '30');
INSERT INTO `testcase` VALUES ('T003', '2', '下列不是C++语言的基本数据类型的是', 'D', '字符类型', '整数类型', '逻辑类型', '枚举类型', '30');
INSERT INTO `testcase` VALUES ('T003', '3', '枚举类型中的每个枚举常量的值都是一个', 'A', '整数', '浮点数', '字符', '逻辑值', '40');
INSERT INTO `testcase` VALUES ('T004', '1', '下列哪种默认参数的声明是不正确的', 'C', ' int max(int a，int b，int c，int d=0);', ' int max(int a，int b，int c=0，int d=0);', ' int max(int a=0，int b，int c=0，int d=0);', ' int max(int a，int b=0，int c=0，int d=0);', '25');
INSERT INTO `testcase` VALUES ('T004', '2', '包含哪种语句的函数不能声明为内联函数', 'A', '循环', '变量自增自减', 'if...else...', '变量声明', '25');
INSERT INTO `testcase` VALUES ('T004', '3', '定义函数模板中使用的参数类型标识符需使用下列哪组符号括起来', 'A', '<>', '\"\"', '()', '{}', '25');
INSERT INTO `testcase` VALUES ('T004', '4', '一个类拥有多个构造函数，则这些构造函数间为', 'A', '重载关系', '重复关系', '拷贝关系', '无关系', '25');
INSERT INTO `testcase` VALUES ('T005', '1', '对于拷贝构造函数point：：point(point& p)，下列说明正确的是', 'C', '该函数只能访问P的私有成员', '该函数不能访问P的公有成员', '该函数可以访问P的私有和公有成员', '该函数不能访问P的成员', '10');
INSERT INTO `testcase` VALUES ('T005', '2', '设类Test中存在成员static int x，则下列哪种初始化方式是正确的', 'C', 'Test：：int x=25；', 'int x=25；', 'int Test：：x=25；', 'int Test x=25；', '10');
INSERT INTO `testcase` VALUES ('T005', '3', '下列关于友元的描述错误的是', 'A', '成员函数不可作友元', '类可以作友元', '普通函数可以作友元', '静态函数可以作友元', '10');
INSERT INTO `testcase` VALUES ('T005', '4', '在继承中，派生类拥有的基类个数为', 'D', '0个', '1个', '多个', '至少1个', '10');
INSERT INTO `testcase` VALUES ('T005', '7', '下列程序段中循环体执行的次数为for(n=1;n<4;n++);', 'C', '2', '3', '4', '5', '10');
INSERT INTO `testcase` VALUES ('T005', '8', '设a,b,c,d,m,n均为整型变量，且a=7,b=5,c=3,d=8,m=2,n=2，则逻辑表达式(m=a>b)&&(n=c>d)运算后，n的值为', 'B', '0', '1', '2', '3', '10');
INSERT INTO `testcase` VALUES ('T005', '9', '设inta=12;，则执行完语句a+=a*a后，a的值是', 'D', '12', '144', '156', '288', '10');
INSERT INTO `testcase` VALUES ('T005', '10', '在C++语言中，要求参加运算的数必须是整数的运算符是', 'D', '/', '%', '*', '&&', '10');
INSERT INTO `testcase` VALUES ('T006', '1', '以下正确的定义语句是', 'C', 'int a[1][4]={1,2,3,4,5};', 'float x[3][]={{1},{2},{3}};', 'long b[2][3]={{1},{1,2},{1,2,3}};', 'double y[][3]={0};', '30');
INSERT INTO `testcase` VALUES ('T006', '2', '以下各组选项中，均能正确定义二维实型数组a的选项是', 'C', 'float a[3][4];  float a[ ][4];     float a[3][ ]={{1},{0}}; ', 'float a(3,4);   float a[3][4];    float a[ ][ ]={{0},{0}};', 'float a[3][4]; static float a[ ][4]={{0},{0}};  auto float a[ ][4]={{0},{0},{0}};', 'float a[3][4]; float a[3][ ];     float a[ ][4];', '30');
INSERT INTO `testcase` VALUES ('T006', '3', '有下面的程序段，则（  ）             char a[3],b[]=\"china\";             a=b; \n            printf(\"%s\",a);', 'C', '运行后将输出China', '运行后将输出Ch', '运行后将输出Chi', '编译出错', '40');
INSERT INTO `testcase` VALUES ('T007', '1', '在C++语言中，引用数组元素时，其数组下标的数据类型不允许是', 'D', '整型常量', '整型常量或整型表达式', '整型表达式', '变量', '25');
INSERT INTO `testcase` VALUES ('T007', '2', '若有说明:inta[3][4]，则对a数组元素的正确引用是', 'B', 'a[1+1][0]', 'a[3][4]', 'a[1,3]', 'a(2)(1)', '25');
INSERT INTO `testcase` VALUES ('T007', '3', '枚举类型中的每个枚举常量的值都是一个', 'C', '整数', '浮点数', '字符', '逻辑值', '25');
INSERT INTO `testcase` VALUES ('T007', '4', '下列枚举类型的定义中，包含枚举值3的是', 'D', 'enum test {RED, YELLOW, BLUE, BLACK};', 'enum test {RED, YELLOW=4, BLUE, BLACK};', 'enum test {RED=-1, YELLOW,BLUE, BLACK};', 'enum test {RED, YELLOW=6, BLUE, BLACK};', '25');
INSERT INTO `testcase` VALUES ('T007', '5', '以下不正确的定义语句是', 'C', 'double x[5]={2.0,4.0,6.0,8.0,10.0};', 'int y[5]={0,1,3,5,7,9}; ', 'char c1[]={′1′,′2′,′3′,′4′,′5′};', 'char c2[]={′\\x10′,′\\xa′,′\\x8′};', '10');
INSERT INTO `testcase` VALUES ('T007', '6', '若有说明：int a[ ][4]={0,0};下面不正确的叙述是', 'A', '数组a的每个元素都可得到初值0 ', '二维数组a的第一维大小为1', '当初值的个数能被第二维的常量表达式的值除尽时，所得商数就是第一维的大小', '只有元素a[0][0]和a[0][1]可得到初值，其余元素均得不到确定的初值', '10');
INSERT INTO `testcase` VALUES ('T008', '1', '已有定义intk=2；int*p1，*p2；且p1和p2均已指向变量k，下面能正确执行的赋值语句是', 'B', 'k=*p1+*p2;', 'p2=k;', 'p1=*p2;', '*p1=p2;', '20');
INSERT INTO `testcase` VALUES ('T008', '2', '已知以下程序段：\nvoidfunc(){intn=5;}intmain(){intn=4;\nfunc();\ncout<<n<<endl;return0;}\n则程序的输出结果是', 'A', '4', '5', '0', '1', '20');
INSERT INTO `testcase` VALUES ('T008', '3', '已知以下程序段：\nintfunc(intx,inty){returnx*y;}intmain(){\nintj=5;\nintm=func(j,2);intk=func(j,3);return0;}\n则程序中变量m和k的值分别为', 'B', '15,10', '10,15', '10,10', '15,15', '20');
INSERT INTO `testcase` VALUES ('T008', '4', '下面for语句结束后，i的值是下面for语句结束后，i的值是for(i=0;i<100;i++);', 'A', '99', '100', '101', '102', '20');
INSERT INTO `testcase` VALUES ('T008', '5', '设有程序段:\nintk=10;while(k=0)\nk=k-1;则下面描述中正确的是', 'D', '循环是无限循环', '循环体语句一次也不执行', 'while语句执行10次', '循环体语句执行一次', '20');
INSERT INTO `testcase` VALUES ('T011', '1', '用来求字符串复制的函数是', 'C', 'strcat()', 'strcmp()', 'strcpy()', 'strlen()', '25');
INSERT INTO `testcase` VALUES ('T011', '2', '写出下列代码段中变量c的值inta=2,b=5;intc=a+b;', 'B', '7', '8', '9', '10', '25');
INSERT INTO `testcase` VALUES ('T011', '3', '写出下列表达式的值a=3*5,a=b=3*2;', 'C', '15', '5', '6', '3', '25');
INSERT INTO `testcase` VALUES ('T011', '4', '设inta=8,b=4;则条件表达式8<4?a:b的值为', null, '0', '1', '4', '8', '25');

-- ----------------------------
-- Table structure for testresult
-- ----------------------------
DROP TABLE IF EXISTS `testresult`;
CREATE TABLE `testresult` (
  `sid` int(11) NOT NULL,
  `kid` varchar(20) NOT NULL,
  `tid` varchar(20) NOT NULL,
  `score` int(11) DEFAULT NULL,
  PRIMARY KEY (`sid`,`kid`,`tid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of testresult
-- ----------------------------
INSERT INTO `testresult` VALUES ('6', 'B002', 'T002', '70');
INSERT INTO `testresult` VALUES ('6', 'B003', 'T003', '0');
INSERT INTO `testresult` VALUES ('6', 'B004', 'T004', '25');
INSERT INTO `testresult` VALUES ('6', 'B005', '', '0');
INSERT INTO `testresult` VALUES ('6', 'B005', 'T006', '70');
INSERT INTO `testresult` VALUES ('6', 'B006', '', '0');
INSERT INTO `testresult` VALUES ('6', 'B007', '', '0');
INSERT INTO `testresult` VALUES ('6', 'B008', 'T007', '25');
INSERT INTO `testresult` VALUES ('6', 'P001', 'T005', '0');
INSERT INTO `testresult` VALUES ('6', 'P001', 'T007', '35');

-- ----------------------------
-- Table structure for usecase
-- ----------------------------
DROP TABLE IF EXISTS `usecase`;
CREATE TABLE `usecase` (
  `cid` varchar(20) NOT NULL,
  `cogtype` text,
  `rectype` text,
  `teatemplate` text,
  `casetype` text,
  `teamode` text,
  PRIMARY KEY (`cid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of usecase
-- ----------------------------
