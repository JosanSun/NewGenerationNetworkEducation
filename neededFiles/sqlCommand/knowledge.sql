/*
Navicat MySQL Data Transfer

Source Server         : 1111
Source Server Version : 50610
Source Host           : localhost:3306
Source Database       : knowledge

Target Server Type    : MYSQL
Target Server Version : 50610
File Encoding         : 65001

Date: 2018-05-31 22:03:58
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
INSERT INTO `behavior` VALUES ('6', 'B008', '', '2018-04-23 20:23:10', '2018-05-29 20:27:24', '0', null);
INSERT INTO `behavior` VALUES ('6', 'B008', 'U005.ppt', '2018-04-23 20:23:24', '2018-04-23 20:23:58', '0', null);
INSERT INTO `behavior` VALUES ('6', 'B008', 'U005.ppt', '2018-04-23 20:23:52', '2018-04-23 20:23:58', '0', null);
INSERT INTO `behavior` VALUES ('6', 'B008', 'U005.ppt', '2018-04-23 20:23:55', '2018-04-23 20:23:58', '0', null);
INSERT INTO `behavior` VALUES ('6', 'B008', 'U005.ppt', '2018-04-23 20:23:58', null, '0', null);
INSERT INTO `behavior` VALUES ('6', 'P001', '', '2018-04-23 20:33:14', '2018-05-29 20:35:18', '0', null);
INSERT INTO `behavior` VALUES ('6', 'P001', 'U001.ppt', '2018-05-30 09:57:54', null, null, null);
INSERT INTO `behavior` VALUES ('6', 'P001', 'U002.ppt', '2017-04-10 20:27:27', '2017-04-20 22:06:07', '0', null);
INSERT INTO `behavior` VALUES ('6', 'P001', 'U002.ppt', '2017-04-20 22:02:46', '2017-04-20 22:06:07', '0', null);
INSERT INTO `behavior` VALUES ('6', 'P001', 'U002.ppt', '2018-04-23 17:02:16', null, null, null);
INSERT INTO `behavior` VALUES ('6', 'P001', 'U002.ppt', '2018-04-23 17:02:39', null, null, null);
INSERT INTO `behavior` VALUES ('6', 'P001', 'U002.ppt', '2018-04-23 20:33:18', null, null, null);
INSERT INTO `behavior` VALUES ('6', 'P001', 'U002.ppt', '2018-04-24 11:58:01', null, null, null);
INSERT INTO `behavior` VALUES ('6', 'P001', 'U002.ppt', '2018-04-24 11:58:04', null, null, null);
INSERT INTO `behavior` VALUES ('6', 'P001', 'U002.ppt', '2018-04-24 11:58:05', null, null, null);
INSERT INTO `behavior` VALUES ('6', 'P001', 'U002.ppt', '2018-04-24 11:58:06', null, null, null);
INSERT INTO `behavior` VALUES ('6', 'P001', 'U002.ppt', '2018-04-24 20:50:12', null, null, null);
INSERT INTO `behavior` VALUES ('6', 'P001', 'U002.ppt', '2018-04-24 20:50:14', null, null, null);
INSERT INTO `behavior` VALUES ('6', 'P001', 'U002.ppt', '2018-04-24 21:05:25', null, null, null);
INSERT INTO `behavior` VALUES ('6', 'P001', 'U002.ppt', '2018-04-26 13:50:15', null, null, null);
INSERT INTO `behavior` VALUES ('6', 'P001', 'U002.ppt', '2018-05-27 16:25:13', null, null, null);
INSERT INTO `behavior` VALUES ('6', 'P001', 'U002.ppt', '2018-05-28 10:50:38', null, null, null);
INSERT INTO `behavior` VALUES ('6', 'P001', 'U002.ppt', '2018-05-28 10:50:41', null, null, null);
INSERT INTO `behavior` VALUES ('6', 'P001', 'U002.ppt', '2018-05-28 10:50:42', null, null, null);
INSERT INTO `behavior` VALUES ('6', 'P001', 'U002.ppt', '2018-05-28 10:50:43', null, null, null);
INSERT INTO `behavior` VALUES ('6', 'P001', 'U002.ppt', '2018-05-28 10:51:00', null, null, null);
INSERT INTO `behavior` VALUES ('6', 'P001', 'U002.ppt', '2018-05-28 10:51:02', null, null, null);
INSERT INTO `behavior` VALUES ('6', 'P001', 'U002.ppt', '2018-05-28 10:51:07', null, null, null);
INSERT INTO `behavior` VALUES ('6', 'P001', 'U002.ppt', '2018-05-28 10:51:58', null, null, null);
INSERT INTO `behavior` VALUES ('6', 'P001', 'U002.ppt', '2018-05-28 10:51:59', null, null, null);
INSERT INTO `behavior` VALUES ('6', 'P001', 'U002.ppt', '2018-05-28 10:53:01', null, null, null);
INSERT INTO `behavior` VALUES ('6', 'P001', 'U002.ppt', '2018-05-28 10:53:38', null, null, null);
INSERT INTO `behavior` VALUES ('6', 'P001', 'U002.ppt', '2018-05-30 09:26:24', null, null, null);
INSERT INTO `behavior` VALUES ('6', 'P001', 'U002.ppt', '2018-05-30 09:26:45', null, null, null);
INSERT INTO `behavior` VALUES ('6', 'P001', 'U002.ppt', '2018-05-30 09:58:04', null, null, null);
INSERT INTO `behavior` VALUES ('6', 'P001', 'U003.html', '2018-04-26 13:37:27', '2018-05-30 09:55:58', '0', '开始测试');
INSERT INTO `behavior` VALUES ('6', 'P001', 'U003.html', '2018-04-26 13:50:10', '2018-05-30 09:55:58', '0', '开始测试');
INSERT INTO `behavior` VALUES ('6', 'P001', 'U003.html', '2018-04-26 13:52:43', '2018-05-30 09:55:58', '0', '开始测试');
INSERT INTO `behavior` VALUES ('6', 'P001', 'U003.html', '2018-05-28 10:50:55', '2018-05-30 09:55:58', '0', '开始测试');
INSERT INTO `behavior` VALUES ('6', 'P001', 'U003.html', '2018-05-28 10:51:03', '2018-05-30 09:55:58', '0', '开始测试');
INSERT INTO `behavior` VALUES ('6', 'P001', 'U003.html', '2018-05-28 10:52:00', '2018-05-30 09:55:58', '0', '开始测试');
INSERT INTO `behavior` VALUES ('6', 'P001', 'U003.html', '2018-05-28 10:53:49', '2018-05-30 09:55:58', '0', '开始测试');
INSERT INTO `behavior` VALUES ('6', 'P001', 'U003.html', '2018-05-30 09:54:41', '2018-05-30 09:55:58', '0', '开始测试');
INSERT INTO `behavior` VALUES ('6', 'P001', 'U003.html', '2018-05-30 09:55:53', '2018-05-30 09:55:58', '0', '开始测试');
INSERT INTO `behavior` VALUES ('6', 'P001', 'U005.ppt', '2017-04-11 20:52:35', '2017-05-21 10:04:20', '0', '');
INSERT INTO `behavior` VALUES ('6', 'P001', 'U005.ppt', '2017-05-21 10:02:42', '2017-05-21 10:04:20', '0', '');
INSERT INTO `behavior` VALUES ('6', 'P001', 'U005.ppt', '2017-05-21 10:04:04', '2017-05-21 10:04:20', '0', '');
INSERT INTO `behavior` VALUES ('6', 'P001', 'U005.ppt', '2018-04-23 17:02:32', null, null, null);
INSERT INTO `behavior` VALUES ('6', 'P001', 'U005.ppt', '2018-04-24 20:50:15', null, null, null);
INSERT INTO `behavior` VALUES ('6', 'P001', 'U005.ppt', '2018-04-24 21:05:33', null, null, null);
INSERT INTO `behavior` VALUES ('6', 'P001', 'U005.ppt', '2018-05-28 10:50:43', null, null, null);
INSERT INTO `behavior` VALUES ('6', 'P001', 'U005.ppt', '2018-05-28 10:50:54', null, null, null);
INSERT INTO `behavior` VALUES ('6', 'P001', 'U008.swf', '2017-04-10 20:27:49', '2018-05-28 10:53:47', '0', '开始测试');
INSERT INTO `behavior` VALUES ('6', 'P001', 'U008.swf', '2017-04-24 23:00:30', '2018-05-28 10:53:47', '0', '开始测试');
INSERT INTO `behavior` VALUES ('6', 'P001', 'U008.swf', '2017-05-21 10:02:33', '2018-05-28 10:53:47', '0', '开始测试');
INSERT INTO `behavior` VALUES ('6', 'P001', 'U008.swf', '2017-05-25 19:37:11', '2018-05-28 10:53:47', '0', '开始测试');
INSERT INTO `behavior` VALUES ('6', 'P001', 'U008.swf', '2018-04-23 09:32:11', '2018-05-28 10:53:47', '0', '开始测试');
INSERT INTO `behavior` VALUES ('6', 'P001', 'U008.swf', '2018-04-23 17:02:45', '2018-05-28 10:53:47', '0', '开始测试');
INSERT INTO `behavior` VALUES ('6', 'P001', 'U008.swf', '2018-04-24 20:50:15', '2018-05-28 10:53:47', '0', '开始测试');
INSERT INTO `behavior` VALUES ('6', 'P001', 'U008.swf', '2018-04-24 21:05:39', '2018-05-28 10:53:47', '0', '开始测试');
INSERT INTO `behavior` VALUES ('6', 'P001', 'U008.swf', '2018-04-24 21:05:47', '2018-05-28 10:53:47', '0', '开始测试');
INSERT INTO `behavior` VALUES ('6', 'P001', 'U008.swf', '2018-04-26 13:50:03', '2018-05-28 10:53:47', '0', '开始测试');
INSERT INTO `behavior` VALUES ('6', 'P001', 'U008.swf', '2018-04-26 13:52:50', '2018-05-28 10:53:47', '0', '开始测试');
INSERT INTO `behavior` VALUES ('6', 'P001', 'U008.swf', '2018-05-28 10:50:44', '2018-05-28 10:53:47', '0', '开始测试');
INSERT INTO `behavior` VALUES ('6', 'P001', 'U008.swf', '2018-05-28 10:50:51', '2018-05-28 10:53:47', '0', '开始测试');
INSERT INTO `behavior` VALUES ('6', 'P001', 'U008.swf', '2018-05-28 10:53:43', '2018-05-28 10:53:47', '0', '开始测试');
INSERT INTO `behavior` VALUES ('6', 'P001', 'U009.html', '2018-05-30 09:58:46', '2018-05-30 09:59:03', '0', '开始测试');
INSERT INTO `behavior` VALUES ('6', 'P001', 'U009.html', '2018-05-30 09:58:50', '2018-05-30 09:59:03', '0', '开始测试');
INSERT INTO `behavior` VALUES ('6', 'P001', 'U009.html', '2018-05-30 09:59:02', '2018-05-30 09:59:03', '0', '开始测试');
INSERT INTO `behavior` VALUES ('6', 'P001', 'U026.html', '2018-05-30 09:55:28', '2018-05-30 09:56:00', '0', '开始测试');
INSERT INTO `behavior` VALUES ('6', 'P001', 'U026.html', '2018-05-30 09:55:51', '2018-05-30 09:56:00', '0', '开始测试');
INSERT INTO `behavior` VALUES ('6', 'P001', 'U026.html', '2018-05-30 09:55:59', '2018-05-30 09:56:00', '0', '开始测试');
INSERT INTO `behavior` VALUES ('6', 'P001', 'U027.html', '2018-05-30 09:56:41', '2018-05-30 09:56:50', '0', '开始测试');
INSERT INTO `behavior` VALUES ('8', 'P001', 'U003.html', '2018-05-28 12:18:01', '2018-05-28 12:18:42', '0', '开始测试');
INSERT INTO `behavior` VALUES ('8', 'P001', 'U003.html', '2018-05-28 12:18:30', '2018-05-28 12:18:42', '0', '开始测试');
INSERT INTO `behavior` VALUES ('8', 'P001', 'U004.txt', '2018-05-28 12:28:18', '2018-05-28 12:28:25', '0', '开始测试');

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
INSERT INTO `path` VALUES ('1', '数据表示,C++', 'B001', '2017-03-19 09:41:12', '100');
INSERT INTO `path` VALUES ('1', '数据表示,C++', 'B002', '2017-03-19 10:12:45', '70');
INSERT INTO `path` VALUES ('1', '数据结构,C++', 'B003', '2017-03-21 10:27:33', '90');
INSERT INTO `path` VALUES ('1', '数据结构,C++', 'B004', '2017-03-21 09:11:12', '91');
INSERT INTO `path` VALUES ('1', '数据结构,C++', 'B005', '2017-03-22 10:24:45', '75');
INSERT INTO `path` VALUES ('1', '数据表示,C++', 'B006', '2017-03-22 10:35:33', '80');
INSERT INTO `path` VALUES ('1', '数据表示,C++', 'B007', '2017-03-22 11:11:12', '90');
INSERT INTO `path` VALUES ('1', '数据结构,C++', 'B008', '2017-03-22 12:12:45', '93');
INSERT INTO `path` VALUES ('1', '数据表示,C++', 'B009', '2017-03-22 12:27:33', '86');
INSERT INTO `path` VALUES ('1', '数据结构,C++', 'B010', '2017-03-23 08:59:12', '100');
INSERT INTO `path` VALUES ('1', '数据结构,C++', 'B011', '2017-03-23 09:12:48', '90');
INSERT INTO `path` VALUES ('1', '数据结构,C++', 'B012', '2017-03-23 10:25:33', '75');
INSERT INTO `path` VALUES ('1', '数据表示,C++', 'B013', '2017-03-23 11:23:45', '80');
INSERT INTO `path` VALUES ('1', '数据表示,C++', 'P001', '2017-03-23 11:38:45', '84');
INSERT INTO `path` VALUES ('1', '数据表示,C++', 'P002', '2017-03-23 12:08:33', '91');
INSERT INTO `path` VALUES ('1', '数据表示,C++', 'P003', '2017-03-23 12:47:32', '86');
INSERT INTO `path` VALUES ('2', '数据表示,C++', 'B001', '2017-03-19 09:41:12', '84');
INSERT INTO `path` VALUES ('2', '数据表示,C++', 'B002', '2017-03-19 10:12:45', '90');
INSERT INTO `path` VALUES ('2', '数据结构,C++', 'B003', '2017-03-21 10:27:33', '100');
INSERT INTO `path` VALUES ('2', '数据结构,C++', 'B004', '2017-03-21 09:11:12', '70');
INSERT INTO `path` VALUES ('2', '数据结构,C++', 'B005', '2017-03-22 10:24:45', '90');
INSERT INTO `path` VALUES ('2', '数据表示,C++', 'B006', '2017-03-22 10:35:33', '100');
INSERT INTO `path` VALUES ('2', '数据表示,C++', 'B007', '2017-03-22 11:11:12', '100');
INSERT INTO `path` VALUES ('2', '数据结构,C++', 'B008', '2017-03-22 12:12:45', '84');
INSERT INTO `path` VALUES ('2', '数据表示,C++', 'B009', '2017-03-22 12:27:33', '80');
INSERT INTO `path` VALUES ('2', '数据结构,C++', 'B010', '2017-03-23 08:59:12', '90');
INSERT INTO `path` VALUES ('2', '数据结构,C++', 'B011', '2017-03-23 09:12:48', '93');
INSERT INTO `path` VALUES ('2', '数据结构,C++', 'B012', '2017-03-23 10:25:33', '86');
INSERT INTO `path` VALUES ('2', '数据表示,C++', 'B013', '2017-03-23 11:23:45', '100');
INSERT INTO `path` VALUES ('2', '数据表示,C++', 'P001', '2017-03-23 11:38:45', '86');
INSERT INTO `path` VALUES ('2', '数据表示,C++', 'P002', '2017-03-23 12:08:33', '100');
INSERT INTO `path` VALUES ('2', '数据表示,C++', 'P003', '2017-03-23 12:47:32', '70');
INSERT INTO `path` VALUES ('3', '数据表示,C++', 'B001', '2017-03-19 09:41:12', '90');
INSERT INTO `path` VALUES ('3', '数据表示,C++', 'B002', '2017-03-19 10:12:45', '100');
INSERT INTO `path` VALUES ('3', '数据表示,C++', 'B003', '2017-03-21 10:27:33', '100');
INSERT INTO `path` VALUES ('3', '数据表示,C++', 'B004', '2017-03-21 09:11:12', '86');
INSERT INTO `path` VALUES ('3', '数据表示,C++', 'B005', '2017-03-22 10:24:45', '100');
INSERT INTO `path` VALUES ('3', '数据表示,C++', 'B006', '2017-03-22 10:35:33', '86');
INSERT INTO `path` VALUES ('3', '数据表示,C++', 'B007', '2017-03-22 11:11:12', '100');
INSERT INTO `path` VALUES ('3', '数据表示,C++', 'B008', '2017-03-22 12:12:45', '80');
INSERT INTO `path` VALUES ('3', '数据表示,C++', 'B009', '2017-03-22 12:27:33', '90');
INSERT INTO `path` VALUES ('3', '数据表示,C++', 'B010', '2017-03-23 08:59:12', '93');
INSERT INTO `path` VALUES ('3', '数据表示,C++', 'B011', '2017-03-23 09:12:48', '86');
INSERT INTO `path` VALUES ('3', '数据表示,C++', 'B012', '2017-03-23 10:25:33', '100');
INSERT INTO `path` VALUES ('3', '数据表示,C++', 'B013', '2017-03-23 11:23:45', '100');
INSERT INTO `path` VALUES ('3', '数据表示,C++', 'P001', '2017-03-23 11:38:45', '90');
INSERT INTO `path` VALUES ('3', '数据表示,C++', 'P002', '2017-03-23 12:08:33', '75');
INSERT INTO `path` VALUES ('3', '数据表示,C++', 'P003', '2017-03-23 12:47:32', '80');
INSERT INTO `path` VALUES ('4', '数据表示,C++', 'B001', '2017-03-19 09:41:12', '84');
INSERT INTO `path` VALUES ('4', '数据表示,C++', 'B002', '2017-03-19 10:12:45', '86');
INSERT INTO `path` VALUES ('4', '数据结构,C++', 'B003', '2017-03-21 10:27:33', '80');
INSERT INTO `path` VALUES ('4', '数据结构,C++', 'B004', '2017-03-21 09:11:12', '90');
INSERT INTO `path` VALUES ('4', '数据结构,C++', 'B005', '2017-03-22 10:24:45', '93');
INSERT INTO `path` VALUES ('4', '数据表示,C++', 'B006', '2017-03-22 10:35:33', '86');
INSERT INTO `path` VALUES ('4', '数据表示,C++', 'B007', '2017-03-22 11:11:12', '100');
INSERT INTO `path` VALUES ('4', '数据结构,C++', 'B008', '2017-03-22 12:12:45', '75');
INSERT INTO `path` VALUES ('4', '数据表示,C++', 'B009', '2017-03-22 12:27:33', '93');
INSERT INTO `path` VALUES ('4', '数据结构,C++', 'B010', '2017-03-23 08:59:12', '91');
INSERT INTO `path` VALUES ('4', '数据结构,C++', 'B011', '2017-03-23 09:12:48', '100');
INSERT INTO `path` VALUES ('4', '数据结构,C++', 'B012', '2017-03-23 10:25:33', '70');
INSERT INTO `path` VALUES ('4', '数据表示,C++', 'B013', '2017-03-23 11:23:45', '90');
INSERT INTO `path` VALUES ('4', '数据表示,C++', 'P001', '2017-03-23 11:38:45', '100');
INSERT INTO `path` VALUES ('4', '数据表示,C++', 'P002', '2017-03-23 12:08:33', '100');
INSERT INTO `path` VALUES ('4', '数据表示,C++', 'P003', '2017-03-23 12:47:32', '86');
INSERT INTO `path` VALUES ('5', '数据表示,C++', 'B001', '2017-03-19 09:41:12', '80');
INSERT INTO `path` VALUES ('5', '数据表示,C++', 'B002', '2017-03-19 10:12:45', '90');
INSERT INTO `path` VALUES ('5', '数据结构,C++', 'B003', '2017-03-21 10:27:33', '93');
INSERT INTO `path` VALUES ('5', '数据结构,C++', 'B004', '2017-03-21 09:11:12', '86');
INSERT INTO `path` VALUES ('5', '数据结构,C++', 'B005', '2017-03-22 10:24:45', '100');
INSERT INTO `path` VALUES ('5', '数据表示,C++', 'B006', '2017-03-23 12:08:33', '90');
INSERT INTO `path` VALUES ('5', '数据表示,C++', 'B007', '2017-03-23 12:47:32', '93');
INSERT INTO `path` VALUES ('5', '数据结构,C++', 'B008', '2017-03-22 10:35:33', '100');
INSERT INTO `path` VALUES ('5', '数据表示,C++', 'B009', '2017-03-22 11:11:12', '90');
INSERT INTO `path` VALUES ('5', '数据结构,C++', 'B010', '2017-03-22 12:12:45', '75');
INSERT INTO `path` VALUES ('5', '数据结构,C++', 'B011', '2017-03-22 12:27:33', '80');
INSERT INTO `path` VALUES ('5', '数据结构,C++', 'B012', '2017-03-23 08:59:12', '84');
INSERT INTO `path` VALUES ('5', '数据表示,C++', 'B013', '2017-03-23 09:12:48', '72');
INSERT INTO `path` VALUES ('5', '数据表示,C++', 'P001', '2017-03-23 10:25:33', '80');
INSERT INTO `path` VALUES ('5', '数据表示,C++', 'P002', '2017-03-23 11:23:45', '70');
INSERT INTO `path` VALUES ('5', '数据表示,C++', 'P003', '2017-03-23 11:38:45', '75');
INSERT INTO `path` VALUES ('6', '数据表示,C++', 'B001', '2017-03-19 09:11:12', '100');
INSERT INTO `path` VALUES ('6', '数据表示,C++', 'B002', '2017-03-19 10:12:45', '70');
INSERT INTO `path` VALUES ('6', '数据结构,C++', 'B003', '2017-05-21 10:27:33', '90');
INSERT INTO `path` VALUES ('6', '数据结构,C++', 'B008', '2018-04-23 20:23:58', '100');
INSERT INTO `path` VALUES ('6', '数据表示,C++', 'P001', '2018-05-28 10:53:43', '100');
INSERT INTO `path` VALUES ('7', '数据表示,C++', 'B001', '2017-03-19 09:41:12', '100');
INSERT INTO `path` VALUES ('7', '数据表示,C++', 'B002', '2017-03-19 10:12:45', '100');
INSERT INTO `path` VALUES ('7', '数据结构,C++', 'B003', '2017-03-21 10:27:33', '91');
INSERT INTO `path` VALUES ('7', '数据结构,C++', 'B004', '2017-03-21 09:11:12', '72');
INSERT INTO `path` VALUES ('7', '数据结构,C++', 'B005', '2017-03-22 10:24:45', '70');
INSERT INTO `path` VALUES ('7', '数据表示,C++', 'B006', '2017-03-22 10:35:33', '80');
INSERT INTO `path` VALUES ('7', '数据表示,C++', 'B007', '2017-03-22 11:11:12', '90');
INSERT INTO `path` VALUES ('7', '数据结构,C++', 'B008', '2017-03-22 12:12:45', '93');
INSERT INTO `path` VALUES ('7', '数据表示,C++', 'B009', '2017-03-22 12:27:33', '86');
INSERT INTO `path` VALUES ('7', '数据结构,C++', 'B010', '2017-03-23 08:59:12', '100');
INSERT INTO `path` VALUES ('7', '数据结构,C++', 'B011', '2017-03-23 09:12:48', '100');
INSERT INTO `path` VALUES ('7', '数据结构,C++', 'B012', '2017-03-23 10:25:33', '90');
INSERT INTO `path` VALUES ('7', '数据表示,C++', 'B013', '2017-03-23 11:23:45', '75');
INSERT INTO `path` VALUES ('7', '数据表示,C++', 'P001', '2017-03-23 11:38:45', '80');
INSERT INTO `path` VALUES ('7', '数据表示,C++', 'P002', '2017-03-23 12:08:33', '84');
INSERT INTO `path` VALUES ('7', '数据表示,C++', 'P003', '2017-03-23 12:47:32', '70');
INSERT INTO `path` VALUES ('8', '数据表示,C++', 'B001', '2017-03-19 09:41:12', '80');
INSERT INTO `path` VALUES ('8', '数据表示,C++', 'B002', '2017-03-19 10:12:45', '72');
INSERT INTO `path` VALUES ('8', '数据表示,C++', 'B003', '2017-03-21 10:27:33', '60');
INSERT INTO `path` VALUES ('8', '数据表示,C++', 'B004', '2017-03-21 09:11:12', '80');
INSERT INTO `path` VALUES ('8', '数据表示,C++', 'B005', '2017-03-22 10:24:45', '90');
INSERT INTO `path` VALUES ('8', '数据表示,C++', 'B006', '2017-03-22 10:35:33', '93');
INSERT INTO `path` VALUES ('8', '数据表示,C++', 'B007', '2017-03-22 11:11:12', '86');
INSERT INTO `path` VALUES ('8', '数据表示,C++', 'B008', '2017-03-22 12:12:45', '100');
INSERT INTO `path` VALUES ('8', '数据表示,C++', 'B009', '2017-03-22 12:27:33', '91');
INSERT INTO `path` VALUES ('8', '数据表示,C++', 'B010', '2017-03-23 08:59:12', '100');
INSERT INTO `path` VALUES ('8', '数据表示,C++', 'B011', '2017-03-23 09:12:48', '90');
INSERT INTO `path` VALUES ('8', '数据表示,C++', 'B012', '2017-03-23 10:25:33', '75');
INSERT INTO `path` VALUES ('8', '数据表示,C++', 'B013', '2017-03-23 11:23:45', '80');
INSERT INTO `path` VALUES ('8', '数据表示,C++', 'P001', '2017-03-23 11:38:45', '84');
INSERT INTO `path` VALUES ('8', '数据表示,C++', 'P002', '2017-03-23 12:08:33', '70');
INSERT INTO `path` VALUES ('8', '数据表示,C++', 'P003', '2017-03-23 12:47:32', '90');
INSERT INTO `path` VALUES ('9', '数据表示,C++', 'B001', '2017-03-19 09:41:12', '100');
INSERT INTO `path` VALUES ('9', '数据表示,C++', 'B002', '2017-03-19 10:12:45', '100');
INSERT INTO `path` VALUES ('9', '数据结构,C++', 'B003', '2017-03-21 10:27:33', '91');
INSERT INTO `path` VALUES ('9', '数据结构,C++', 'B004', '2017-03-21 09:11:12', '93');
INSERT INTO `path` VALUES ('9', '数据结构,C++', 'B005', '2017-03-22 10:24:45', '72');
INSERT INTO `path` VALUES ('9', '数据表示,C++', 'B006', '2017-03-22 10:35:33', '90');
INSERT INTO `path` VALUES ('9', '数据表示,C++', 'B007', '2017-03-22 11:11:12', '80');
INSERT INTO `path` VALUES ('9', '数据结构,C++', 'B008', '2017-03-22 12:12:45', '90');
INSERT INTO `path` VALUES ('9', '数据表示,C++', 'B009', '2017-03-22 12:27:33', '93');
INSERT INTO `path` VALUES ('9', '数据结构,C++', 'B010', '2017-03-23 08:59:12', '86');
INSERT INTO `path` VALUES ('9', '数据结构,C++', 'B011', '2017-03-23 09:12:48', '100');
INSERT INTO `path` VALUES ('9', '数据结构,C++', 'B012', '2017-03-23 10:25:33', '72');
INSERT INTO `path` VALUES ('9', '数据表示,C++', 'B013', '2017-03-23 11:23:45', '90');
INSERT INTO `path` VALUES ('9', '数据表示,C++', 'P001', '2017-03-23 11:38:45', '93');
INSERT INTO `path` VALUES ('9', '数据表示,C++', 'P002', '2017-03-23 12:08:33', '86');
INSERT INTO `path` VALUES ('9', '数据表示,C++', 'P003', '2017-03-23 12:47:32', '100');
INSERT INTO `path` VALUES ('10', '数据表示,C++', 'B001', '2017-03-19 09:41:12', '72');
INSERT INTO `path` VALUES ('10', '数据表示,C++', 'B002', '2017-03-19 10:12:45', '80');
INSERT INTO `path` VALUES ('10', '数据表示,C++', 'B003', '2017-03-21 10:27:33', '90');
INSERT INTO `path` VALUES ('10', '数据表示,C++', 'B004', '2017-03-21 09:11:12', '93');
INSERT INTO `path` VALUES ('10', '数据表示,C++', 'B005', '2017-03-22 10:24:45', '86');
INSERT INTO `path` VALUES ('10', '数据表示,C++', 'B006', '2017-03-22 10:35:33', '100');
INSERT INTO `path` VALUES ('10', '数据表示,C++', 'B007', '2017-03-22 11:11:12', '72');
INSERT INTO `path` VALUES ('10', '数据表示,C++', 'B008', '2017-03-22 12:12:45', '91');
INSERT INTO `path` VALUES ('10', '数据表示,C++', 'B009', '2017-03-22 12:27:33', '100');
INSERT INTO `path` VALUES ('10', '数据表示,C++', 'B010', '2017-03-23 08:59:12', '70');
INSERT INTO `path` VALUES ('10', '数据表示,C++', 'B011', '2017-03-23 09:12:48', '90');
INSERT INTO `path` VALUES ('10', '数据表示,C++', 'B012', '2017-03-23 10:25:33', '100');
INSERT INTO `path` VALUES ('10', '数据表示,C++', 'B013', '2017-03-23 11:23:45', '100');
INSERT INTO `path` VALUES ('10', '数据表示,C++', 'P001', '2017-03-23 11:38:45', '72');
INSERT INTO `path` VALUES ('10', '数据表示,C++', 'P002', '2017-03-23 12:08:33', '72');
INSERT INTO `path` VALUES ('10', '数据表示,C++', 'P003', '2017-03-23 12:47:32', '80');

-- ----------------------------
-- Table structure for patterntest
-- ----------------------------
DROP TABLE IF EXISTS `patterntest`;
CREATE TABLE `patterntest` (
  `qid` int(255) NOT NULL AUTO_INCREMENT,
  `content` varchar(255) NOT NULL,
  `a` varchar(255) NOT NULL,
  `b` varchar(255) NOT NULL,
  PRIMARY KEY (`qid`)
) ENGINE=InnoDB AUTO_INCREMENT=45 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of patterntest
-- ----------------------------
INSERT INTO `patterntest` VALUES ('1', '为了较好地理解某些事物，我首先', '试试看', '深思熟虑');
INSERT INTO `patterntest` VALUES ('2', '我办事喜欢', '讲究实际', '标新立异');
INSERT INTO `patterntest` VALUES ('3', '当我回想以前做过的事，我的脑海中大多会出现', '一幅画面', '一些话语');
INSERT INTO `patterntest` VALUES ('4', '我往往会', '明了事物的细节但不明其总体结构', '明了事物的总体结构但不明其细节');
INSERT INTO `patterntest` VALUES ('5', '在学习某些东西时, 我不禁会', '谈论它', '思考它');
INSERT INTO `patterntest` VALUES ('6', '如果我是一名教师，我比较喜欢教', '关于事实和实际情况的课程关于思想和理论方面的课程关于事实和实际情况的课程', '关于思想和理论方面的课程');
INSERT INTO `patterntest` VALUES ('7', '我比较偏爱的获取新信息的媒体是', '图画、图解、图形及图象', '书面指导和言语信息');
INSERT INTO `patterntest` VALUES ('8', '一旦我了解了', '事物的所有部分, 我就能把握其整体', '事物的整体，我就知道其构成部分');
INSERT INTO `patterntest` VALUES ('9', '在学习小组中遇到难题时，我通常会', '挺身而出，畅所欲言', '往后退让，倾听意见');
INSERT INTO `patterntest` VALUES ('10', '我发现比较容易学习的是', '事实性内容', '概念性内容');
INSERT INTO `patterntest` VALUES ('11', '在阅读一本带有许多插图的书时，我一般会', '仔细观察插图', '集中注意文字');
INSERT INTO `patterntest` VALUES ('12', '当我解决数学题时，我常常', '思考如何一步一步求解', '先看解答，然后设法得出解题步骤');
INSERT INTO `patterntest` VALUES ('13', '在我修课的班级中，', '我通常结识许多同学', '我认识的同学寥寥无几');
INSERT INTO `patterntest` VALUES ('14', '在阅读非小说类作品时，我偏爱', '那些能告诉我新事实和教我怎么做的东西', '那些能启发我思考的东西');
INSERT INTO `patterntest` VALUES ('15', '我喜欢的教师是', '在黑板上画许多图解的人', '花许多时间讲解的人');
INSERT INTO `patterntest` VALUES ('16', '当我在分析故事或小说时，', '我想到各种情节并试图把他们结合起来去构想主题', '当我读完时只知道主题是什么，然后我得回头去寻找有关情节');
INSERT INTO `patterntest` VALUES ('17', '当我做家庭作业时，我比较喜欢', '一开始就立即做解答', '首先设法理解题意');
INSERT INTO `patterntest` VALUES ('18', '我记得最牢是', '看到的东西', '听到的东西');
INSERT INTO `patterntest` VALUES ('19', '我比较喜欢', '确定性的想法', '推论性的想法');
INSERT INTO `patterntest` VALUES ('20', '我特别喜欢教师', '向我条理分明地呈示材料', '先给我一个概貌，再将材料与其他论题相联系');
INSERT INTO `patterntest` VALUES ('21', '我喜欢', '在小组中学习', '独自学习');
INSERT INTO `patterntest` VALUES ('22', '我更喜欢被认为是：', '对工作细节很仔细', '对工作很有创造力');
INSERT INTO `patterntest` VALUES ('23', '当要我到一个新的地方去时，我喜欢', '要一幅地图', '要书面指南');
INSERT INTO `patterntest` VALUES ('24', '我学习时', '总是按部就班，我相信只要努力，终有所得', '我有时完全糊涂，然后恍然大悟');
INSERT INTO `patterntest` VALUES ('25', '我办事时喜欢', '试试看', '想好再做');
INSERT INTO `patterntest` VALUES ('26', '当我阅读趣闻时, 我喜欢作者', '以开门见山的方式叙述', '以新颖有趣的方式叙述');
INSERT INTO `patterntest` VALUES ('27', '当我在上课时看到一幅图, 我通常会清晰地记着', '那幅图', '教师对那幅图的解说');
INSERT INTO `patterntest` VALUES ('28', '当我思考一大段信息资料时，我通常', '注意细节而忽视概貌', '先了解概貌而后深入细节');
INSERT INTO `patterntest` VALUES ('29', '我最容易记住', '我做过的事', '我想过的许多事');
INSERT INTO `patterntest` VALUES ('30', '当我执行一项任务是，我喜欢', '掌握一种方法', '想出多种方法');
INSERT INTO `patterntest` VALUES ('31', '当有人向我展示资料时，我喜欢', '图表', '概括其结果的文字');
INSERT INTO `patterntest` VALUES ('32', '当我写文章时，我通常', '先思考和着手写文章的开头，然后循序渐进。', '先思考和写作文章的不同部分，然后加以整理');
INSERT INTO `patterntest` VALUES ('33', '当我必须参加小组合作课题时，我要', '大家首先“集思广益”，人人贡献主意', '各人分头思考，然后集中起来比较各种想法');
INSERT INTO `patterntest` VALUES ('34', '当我要赞扬他人时，我说他是', '很敏感的', '想象力丰富的');
INSERT INTO `patterntest` VALUES ('35', '当我在聚会时与人见过面，我通常会记得', '他们的模样', '他们的自我介绍');
INSERT INTO `patterntest` VALUES ('36', '当我学习新的科目时, 我喜欢', '全力以赴，尽量学得多学得好', '试图建立该科目与其他有关科目的联系');
INSERT INTO `patterntest` VALUES ('37', '我通常被他人认为是', '外向的', '保守的');
INSERT INTO `patterntest` VALUES ('38', '我喜欢的课程内容主要是', '具体材料（事实、数据）', '抽象材料 (概念、理论)');
INSERT INTO `patterntest` VALUES ('39', '在娱乐方面，我喜欢', '看电视', '看书');
INSERT INTO `patterntest` VALUES ('40', '有些教师讲课时先给出一个提纲，这种提纲对我', '有所帮助', '很有帮助');
INSERT INTO `patterntest` VALUES ('41', '我认为只给合作的群体打一个分数的想法', '吸引我', '不吸引我');
INSERT INTO `patterntest` VALUES ('42', '当我长时间地从事计算工作时', '我喜欢重复我的步骤并仔细地检查我的工作', '我认为检查工作非常无聊，我是在逼迫自己这么干');
INSERT INTO `patterntest` VALUES ('43', '我能画下我去过的地方', '很容易且相当精确', '很困难且没有许多细节');
INSERT INTO `patterntest` VALUES ('44', '当在小组中解决问题时，我更可能是', '思考解决问题的步骤', '思考可能的结果及其在更广泛的领域内的应用');

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
INSERT INTO `recpath` VALUES ('1', '数据表示,C++', 'B001', '1', '0');
INSERT INTO `recpath` VALUES ('1', '数据表示,C++', 'B002', '2', '0');
INSERT INTO `recpath` VALUES ('1', '数据结构,C++', 'B003', '5', '0');
INSERT INTO `recpath` VALUES ('1', '数据结构,C++', 'B004', '3', '0');
INSERT INTO `recpath` VALUES ('1', '数据结构,C++', 'B005', '6', '0');
INSERT INTO `recpath` VALUES ('1', '数据表示,C++', 'B006', '9', '0');
INSERT INTO `recpath` VALUES ('1', '数据表示,C++', 'B007', '13', '0');
INSERT INTO `recpath` VALUES ('1', '数据结构,C++', 'B008', '7', '0');
INSERT INTO `recpath` VALUES ('1', '数据表示,C++', 'B009', '10', '0');
INSERT INTO `recpath` VALUES ('1', '数据结构,C++', 'B010', '14', '0');
INSERT INTO `recpath` VALUES ('1', '数据结构,C++', 'B011', '12', '0');
INSERT INTO `recpath` VALUES ('1', '数据结构,C++', 'B012', '8', '0');
INSERT INTO `recpath` VALUES ('1', '数据表示,C++', 'B013', '16', '0');
INSERT INTO `recpath` VALUES ('1', '数据表示,C++', 'P001', '4', '0');
INSERT INTO `recpath` VALUES ('1', '数据表示,C++', 'P002', '11', '0');
INSERT INTO `recpath` VALUES ('1', '数据表示,C++', 'P003', '15', '0');
INSERT INTO `recpath` VALUES ('2', '数据表示,C++', 'B001', '1', '0');
INSERT INTO `recpath` VALUES ('2', '数据表示,C++', 'B002', '2', '0');
INSERT INTO `recpath` VALUES ('2', '数据结构,C++', 'B003', '3', '0');
INSERT INTO `recpath` VALUES ('2', '数据结构,C++', 'B004', '4', '0');
INSERT INTO `recpath` VALUES ('2', '数据结构,C++', 'B005', '5', '0');
INSERT INTO `recpath` VALUES ('2', '数据表示,C++', 'B006', '9', '0');
INSERT INTO `recpath` VALUES ('2', '数据表示,C++', 'B007', '13', '0');
INSERT INTO `recpath` VALUES ('2', '数据结构,C++', 'B008', '6', '0');
INSERT INTO `recpath` VALUES ('2', '数据表示,C++', 'B009', '12', '0');
INSERT INTO `recpath` VALUES ('2', '数据结构,C++', 'B010', '16', '0');
INSERT INTO `recpath` VALUES ('2', '数据结构,C++', 'B011', '10', '0');
INSERT INTO `recpath` VALUES ('2', '数据结构,C++', 'B012', '8', '0');
INSERT INTO `recpath` VALUES ('2', '数据表示,C++', 'B013', '14', '0');
INSERT INTO `recpath` VALUES ('2', '数据表示,C++', 'P001', '7', '0');
INSERT INTO `recpath` VALUES ('2', '数据表示,C++', 'P002', '11', '0');
INSERT INTO `recpath` VALUES ('2', '数据表示,C++', 'P003', '15', '0');
INSERT INTO `recpath` VALUES ('3', '数据表示,C++', 'B001', '1', '0');
INSERT INTO `recpath` VALUES ('3', '数据表示,C++', 'B002', '2', '0');
INSERT INTO `recpath` VALUES ('3', '数据表示,C++', 'B003', '3', '0');
INSERT INTO `recpath` VALUES ('3', '数据表示,C++', 'B004', '4', '0');
INSERT INTO `recpath` VALUES ('3', '数据表示,C++', 'B005', '5', '0');
INSERT INTO `recpath` VALUES ('3', '数据表示,C++', 'B006', '7', '0');
INSERT INTO `recpath` VALUES ('3', '数据表示,C++', 'B007', '11', '0');
INSERT INTO `recpath` VALUES ('3', '数据表示,C++', 'B008', '12', '0');
INSERT INTO `recpath` VALUES ('3', '数据表示,C++', 'B009', '8', '0');
INSERT INTO `recpath` VALUES ('3', '数据表示,C++', 'B010', '13', '0');
INSERT INTO `recpath` VALUES ('3', '数据表示,C++', 'B011', '10', '0');
INSERT INTO `recpath` VALUES ('3', '数据表示,C++', 'B012', '16', '0');
INSERT INTO `recpath` VALUES ('3', '数据表示,C++', 'B013', '15', '0');
INSERT INTO `recpath` VALUES ('3', '数据表示,C++', 'P001', '6', '0');
INSERT INTO `recpath` VALUES ('3', '数据表示,C++', 'P002', '9', '0');
INSERT INTO `recpath` VALUES ('3', '数据表示,C++', 'P003', '14', '0');
INSERT INTO `recpath` VALUES ('4', '数据表示,C++', 'B001', '1', '0');
INSERT INTO `recpath` VALUES ('4', '数据表示,C++', 'B002', '2', '0');
INSERT INTO `recpath` VALUES ('4', '数据结构,C++', 'B003', '3', '0');
INSERT INTO `recpath` VALUES ('4', '数据结构,C++', 'B004', '5', '0');
INSERT INTO `recpath` VALUES ('4', '数据结构,C++', 'B005', '6', '0');
INSERT INTO `recpath` VALUES ('4', '数据表示,C++', 'B006', '9', '0');
INSERT INTO `recpath` VALUES ('4', '数据表示,C++', 'B007', '13', '0');
INSERT INTO `recpath` VALUES ('4', '数据结构,C++', 'B008', '7', '0');
INSERT INTO `recpath` VALUES ('4', '数据表示,C++', 'B009', '10', '0');
INSERT INTO `recpath` VALUES ('4', '数据结构,C++', 'B010', '14', '0');
INSERT INTO `recpath` VALUES ('4', '数据结构,C++', 'B011', '12', '0');
INSERT INTO `recpath` VALUES ('4', '数据结构,C++', 'B012', '8', '0');
INSERT INTO `recpath` VALUES ('4', '数据表示,C++', 'B013', '16', '0');
INSERT INTO `recpath` VALUES ('4', '数据表示,C++', 'P001', '4', '0');
INSERT INTO `recpath` VALUES ('4', '数据表示,C++', 'P002', '11', '0');
INSERT INTO `recpath` VALUES ('4', '数据表示,C++', 'P003', '15', '0');
INSERT INTO `recpath` VALUES ('5', '数据表示,C++', 'B001', '1', '0');
INSERT INTO `recpath` VALUES ('5', '数据表示,C++', 'B002', '2', '0');
INSERT INTO `recpath` VALUES ('5', '数据结构,C++', 'B003', '5', '0');
INSERT INTO `recpath` VALUES ('5', '数据结构,C++', 'B004', '3', '0');
INSERT INTO `recpath` VALUES ('5', '数据结构,C++', 'B005', '6', '0');
INSERT INTO `recpath` VALUES ('5', '数据表示,C++', 'B006', '9', '0');
INSERT INTO `recpath` VALUES ('5', '数据表示,C++', 'B007', '13', '0');
INSERT INTO `recpath` VALUES ('5', '数据结构,C++', 'B008', '7', '0');
INSERT INTO `recpath` VALUES ('5', '数据表示,C++', 'B009', '10', '0');
INSERT INTO `recpath` VALUES ('5', '数据结构,C++', 'B010', '14', '0');
INSERT INTO `recpath` VALUES ('5', '数据结构,C++', 'B011', '12', '0');
INSERT INTO `recpath` VALUES ('5', '数据结构,C++', 'B012', '8', '0');
INSERT INTO `recpath` VALUES ('5', '数据表示,C++', 'B013', '16', '0');
INSERT INTO `recpath` VALUES ('5', '数据表示,C++', 'P001', '4', '0');
INSERT INTO `recpath` VALUES ('5', '数据表示,C++', 'P002', '11', '0');
INSERT INTO `recpath` VALUES ('5', '数据表示,C++', 'P003', '15', '0');
INSERT INTO `recpath` VALUES ('6', '数据表示,C++', 'B001', '1', '1');
INSERT INTO `recpath` VALUES ('6', '数据表示,C++', 'B002', '2', '1');
INSERT INTO `recpath` VALUES ('6', '数据结构,C++', 'B003', '3', '1');
INSERT INTO `recpath` VALUES ('6', '数据结构,C++', 'B004', '5', '1');
INSERT INTO `recpath` VALUES ('6', '数据结构,C++', 'B005', '6', '1');
INSERT INTO `recpath` VALUES ('6', '数据表示,C++', 'B006', '9', '0');
INSERT INTO `recpath` VALUES ('6', '数据表示,C++', 'B007', '13', '0');
INSERT INTO `recpath` VALUES ('6', '数据结构,C++', 'B008', '7', '1');
INSERT INTO `recpath` VALUES ('6', '数据表示,C++', 'B009', '10', '0');
INSERT INTO `recpath` VALUES ('6', '数据结构,C++', 'B010', '14', '0');
INSERT INTO `recpath` VALUES ('6', '数据结构,C++', 'B011', '12', '0');
INSERT INTO `recpath` VALUES ('6', '数据结构,C++', 'B012', '8', '1');
INSERT INTO `recpath` VALUES ('6', '数据表示,C++', 'B013', '16', '0');
INSERT INTO `recpath` VALUES ('6', '数据表示,C++', 'P001', '4', '0');
INSERT INTO `recpath` VALUES ('6', '数据表示,C++', 'P002', '11', '0');
INSERT INTO `recpath` VALUES ('6', '数据表示,C++', 'P003', '15', '0');
INSERT INTO `recpath` VALUES ('7', '数据表示,C++', 'B001', '1', '0');
INSERT INTO `recpath` VALUES ('7', '数据表示,C++', 'B002', '2', '0');
INSERT INTO `recpath` VALUES ('7', '数据结构,C++', 'B003', '5', '0');
INSERT INTO `recpath` VALUES ('7', '数据结构,C++', 'B004', '3', '0');
INSERT INTO `recpath` VALUES ('7', '数据结构,C++', 'B005', '6', '0');
INSERT INTO `recpath` VALUES ('7', '数据表示,C++', 'B006', '9', '0');
INSERT INTO `recpath` VALUES ('7', '数据表示,C++', 'B007', '13', '0');
INSERT INTO `recpath` VALUES ('7', '数据结构,C++', 'B008', '7', '0');
INSERT INTO `recpath` VALUES ('7', '数据表示,C++', 'B009', '10', '0');
INSERT INTO `recpath` VALUES ('7', '数据结构,C++', 'B010', '14', '0');
INSERT INTO `recpath` VALUES ('7', '数据结构,C++', 'B011', '12', '0');
INSERT INTO `recpath` VALUES ('7', '数据结构,C++', 'B012', '8', '0');
INSERT INTO `recpath` VALUES ('7', '数据表示,C++', 'B013', '16', '0');
INSERT INTO `recpath` VALUES ('7', '数据表示,C++', 'P001', '4', '0');
INSERT INTO `recpath` VALUES ('7', '数据表示,C++', 'P002', '11', '0');
INSERT INTO `recpath` VALUES ('7', '数据表示,C++', 'P003', '15', '0');
INSERT INTO `recpath` VALUES ('8', '数据表示,C++', 'B001', '1', '0');
INSERT INTO `recpath` VALUES ('8', '数据表示,C++', 'B002', '2', '0');
INSERT INTO `recpath` VALUES ('8', '数据表示,C++', 'B003', '3', '0');
INSERT INTO `recpath` VALUES ('8', '数据表示,C++', 'B004', '4', '0');
INSERT INTO `recpath` VALUES ('8', '数据表示,C++', 'B005', '5', '0');
INSERT INTO `recpath` VALUES ('8', '数据表示,C++', 'B006', '7', '0');
INSERT INTO `recpath` VALUES ('8', '数据表示,C++', 'B007', '11', '0');
INSERT INTO `recpath` VALUES ('8', '数据表示,C++', 'B008', '12', '0');
INSERT INTO `recpath` VALUES ('8', '数据表示,C++', 'B009', '8', '0');
INSERT INTO `recpath` VALUES ('8', '数据表示,C++', 'B010', '13', '0');
INSERT INTO `recpath` VALUES ('8', '数据表示,C++', 'B011', '10', '0');
INSERT INTO `recpath` VALUES ('8', '数据表示,C++', 'B012', '16', '0');
INSERT INTO `recpath` VALUES ('8', '数据表示,C++', 'B013', '15', '0');
INSERT INTO `recpath` VALUES ('8', '数据表示,C++', 'P001', '6', '0');
INSERT INTO `recpath` VALUES ('8', '数据表示,C++', 'P002', '9', '0');
INSERT INTO `recpath` VALUES ('8', '数据表示,C++', 'P003', '14', '0');
INSERT INTO `recpath` VALUES ('9', '数据表示,C++', 'B001', '1', '0');
INSERT INTO `recpath` VALUES ('9', '数据表示,C++', 'B002', '2', '0');
INSERT INTO `recpath` VALUES ('9', '数据结构,C++', 'B003', '3', '0');
INSERT INTO `recpath` VALUES ('9', '数据结构,C++', 'B004', '5', '0');
INSERT INTO `recpath` VALUES ('9', '数据结构,C++', 'B005', '6', '0');
INSERT INTO `recpath` VALUES ('9', '数据表示,C++', 'B006', '9', '0');
INSERT INTO `recpath` VALUES ('9', '数据表示,C++', 'B007', '13', '0');
INSERT INTO `recpath` VALUES ('9', '数据结构,C++', 'B008', '7', '0');
INSERT INTO `recpath` VALUES ('9', '数据表示,C++', 'B009', '10', '0');
INSERT INTO `recpath` VALUES ('9', '数据结构,C++', 'B010', '14', '0');
INSERT INTO `recpath` VALUES ('9', '数据结构,C++', 'B011', '12', '0');
INSERT INTO `recpath` VALUES ('9', '数据结构,C++', 'B012', '8', '0');
INSERT INTO `recpath` VALUES ('9', '数据表示,C++', 'B013', '16', '0');
INSERT INTO `recpath` VALUES ('9', '数据表示,C++', 'P001', '4', '0');
INSERT INTO `recpath` VALUES ('9', '数据表示,C++', 'P002', '11', '0');
INSERT INTO `recpath` VALUES ('9', '数据表示,C++', 'P003', '15', '0');
INSERT INTO `recpath` VALUES ('10', '数据表示,C++', 'B001', '1', '0');
INSERT INTO `recpath` VALUES ('10', '数据表示,C++', 'B002', '2', '0');
INSERT INTO `recpath` VALUES ('10', '数据表示,C++', 'B003', '3', '0');
INSERT INTO `recpath` VALUES ('10', '数据表示,C++', 'B004', '4', '0');
INSERT INTO `recpath` VALUES ('10', '数据表示,C++', 'B005', '5', '0');
INSERT INTO `recpath` VALUES ('10', '数据表示,C++', 'B006', '7', '0');
INSERT INTO `recpath` VALUES ('10', '数据表示,C++', 'B007', '11', '0');
INSERT INTO `recpath` VALUES ('10', '数据表示,C++', 'B008', '12', '0');
INSERT INTO `recpath` VALUES ('10', '数据表示,C++', 'B009', '8', '0');
INSERT INTO `recpath` VALUES ('10', '数据表示,C++', 'B010', '13', '0');
INSERT INTO `recpath` VALUES ('10', '数据表示,C++', 'B011', '10', '0');
INSERT INTO `recpath` VALUES ('10', '数据表示,C++', 'B012', '16', '0');
INSERT INTO `recpath` VALUES ('10', '数据表示,C++', 'B013', '15', '0');
INSERT INTO `recpath` VALUES ('10', '数据表示,C++', 'P001', '6', '0');
INSERT INTO `recpath` VALUES ('10', '数据表示,C++', 'P002', '9', '0');
INSERT INTO `recpath` VALUES ('10', '数据表示,C++', 'P003', '14', '0');

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
  `cogApproach` text,
  `cogStrategy` text,
  `cogExperience` text,
  `metaCogAbility` text,
  `interactfeature` text,
  `emotionfeature` text,
  `perceptionfeature` text,
  `knowledgebasis` float(11,0) DEFAULT '6' COMMENT '为学生的已有知识基础，值为过往测试平均分//10取整',
  PRIMARY KEY (`sid`)
) ENGINE=InnoDB AUTO_INCREMENT=11 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of student
-- ----------------------------
INSERT INTO `student` VALUES ('1', 'admin', 'admin', '女', '26', '硕士', '活跃型', '复述策略', '[1,0.83,64.32,0.39],[2,0.43,65.2,0.08],[3,0.28,68.12,0.16]', '[1,1,85,0.2,0.33],[2,1,88.96,0.83,0.33]', '0.5,0.5', '0.33,0.33,0.33', '0.25,0.25,0.25,0.25', '6');
INSERT INTO `student` VALUES ('2', '小明', '123456', '女', '25', '硕士', '陈思型', '精加工策略', '[1,0.33,74.16,0.09]', '[1,1,65,0.12,0.33]', '0.3,0.7', '0,0.5,0.5', '0.25,0,0.75,0', '6');
INSERT INTO `student` VALUES ('3', '小良', '199109', '男', '26', '硕士', '感悟型', '组织策略', '[1,0.62,69.88,0.31],[2,0.48,88.2,0.48]', '[1,1,56.86,0.23,0.33],[2,1,59.23,0.45,0.33]', '0.4,0.6', '0.33,0,0.67', '0.25,0.25,0.5', '5');
INSERT INTO `student` VALUES ('4', '小逸', '199004', '男', '27', '硕士', '直觉型', '组织策略', '[1,0.53,64.32,0.39],[3,0.68,68.12,0.19]', '[1,1,75.69,0.15,0.33],[3,1,78.56,0.22,0.33]', '0.5,0.5', '0.33,0.33,0.33', '0,0,0.5,0.5', '7');
INSERT INTO `student` VALUES ('5', '小红', '196510', '女', '52', '高中', '序列型', '精加工策略', '[1,0.53,72.13,0.39],[2,0.48,65.2,0.08],[3,0.18,68.5,0.52]', '[1,1,81.23,0.08,0.33],[2,1,89.22,0.09,0.33]', '0.5,0.5', '0.33,0.67,0', '0.25,0.25,0,0.5', '5');
INSERT INTO `student` VALUES ('6', 'xiaoming', 'xiaoming', '男', '21', '本科', '综合型', '复述策略', '[1,0.83,76.22,0.39],[2,0.62,69.42,0.08],[3,0.28,67.29,0.23]', '[1,1,85,0.18,0.33],[2,1,76.23,0.17,0.33],[3,1,68.78,0.22,0.33]', '0.8,0.2', '0.5,0.5,0', '0.25,0.25,0.25,0.25', '6');
INSERT INTO `student` VALUES ('7', 'xiaoding', 'xiaoding', '女', '25', '本科', '视觉型', '精加工策略', '[1,0.53,81.5,0.39],[2,0.43,65.2,0.19]', '[1,1,87,0.38,0.33]', '0.6,0.4', '0.67,0.33,0', '0.5,0.25,0.25,0', '4');
INSERT INTO `student` VALUES ('8', 'hyptooth', '123456', '女', '25', '硕士', '言语型', '复述策略', '[1,0.62,64.8,0.39]', '[1,1,88.29,0.35,0.33]', '0.5,0.5', '0.67,0,0.33', '0.25,0.5,0,0.25', '6');
INSERT INTO `student` VALUES ('9', '小黄', '123456', '女', '25', '本科', '活跃型', '复述策略', '[1,0.83,79.5,0.39],[2,0.48,88.2,0.48]', '[1,1,82.5,0.19,0.33]', '0.3,0.7', '0.33,0,0.67', '0,0,0.5,0.5', '7');
INSERT INTO `student` VALUES ('10', '小孙', '123456', '男', '25', '硕士', '陈思型', '精加工策略', '[1,0.53,82.46,0.39]', '[1,1,91.5,0.19,0.33]', '0.6,0.4', '0.33,0.67,0', '0.25,0.25,0.5', '8');

-- ----------------------------
-- Table structure for studyfeaturetest
-- ----------------------------
DROP TABLE IF EXISTS `studyfeaturetest`;
CREATE TABLE `studyfeaturetest` (
  `fid` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `fquestion` varchar(255) NOT NULL,
  `A` varchar(255) NOT NULL,
  `B` varchar(255) NOT NULL,
  `C` varchar(255) NOT NULL,
  `D` varchar(255) NOT NULL,
  `E` varchar(255) NOT NULL,
  PRIMARY KEY (`fid`)
) ENGINE=InnoDB AUTO_INCREMENT=13 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of studyfeaturetest
-- ----------------------------
INSERT INTO `studyfeaturetest` VALUES ('1', '在餐馆点菜时，我更喜欢看别人正在吃什么或看菜单上的图片。', '完全符合', '部分符合', '不确定', '不太符合', '完全不符合');
INSERT INTO `studyfeaturetest` VALUES ('2', '当我不能确定一个单词是“dependent”还是“dependant”，我喜欢在脑海中读出单词，凭读音来选择比较像的那个。', '完全符合', '部分符合', '不确定不太符合', '不太符合', '完全不符合');
INSERT INTO `studyfeaturetest` VALUES ('3', '阅读学习材料时，我喜欢用手或笔指着文字逐字阅读。', '完全符合', '部分符合', '不确定', '不太符合', '完全不符合');
INSERT INTO `studyfeaturetest` VALUES ('4', '我很容易记住听到的电话号码。', '完全符合', '部分符合', '不确定', '不太符合', '完全不符合');
INSERT INTO `studyfeaturetest` VALUES ('5', '当我不能确定一个单词是“dependent”还是“dependant”，我会将两个单词都写下来，然后选择一个。', '完全符合', '部分符合', '不确定', '不太符合', '完全不符合');
INSERT INTO `studyfeaturetest` VALUES ('6', '学习新软件时，我喜欢直接在电脑上操作试用。', '完全符合', '部分符合', '不确定', '不太符合', '完全不符合');
INSERT INTO `studyfeaturetest` VALUES ('7', '在餐馆点菜时，我更喜欢选择以前在这里吃过的。', '完全符合', '部分符合', '不确定', '不太符合', '完全不符合');
INSERT INTO `studyfeaturetest` VALUES ('8', '学习新软件时，我喜欢先看书上的图解。', '完全符合', '部分符合', '不确定', '不太符合', '完全不符合');
INSERT INTO `studyfeaturetest` VALUES ('9', '阅读学习材料时，我喜欢读出声来。', '完全符合', '部分符合', '不确定', '不太符合', '完全不符合');
INSERT INTO `studyfeaturetest` VALUES ('10', '我更喜欢网络学习包含实践活动或操作。', '完全符合', '部分符合', '不确定', '不太符合', '完全不符合');
INSERT INTO `studyfeaturetest` VALUES ('11', '我必须把电话号码写下来才能记住。', '完全符合', '部分符合', '不确定', '不太符合', '完全不符合');
INSERT INTO `studyfeaturetest` VALUES ('12', '我更喜欢网站中的文字材料有下划线、区分颜色和强调效果。', '完全符合', '部分符合', '不确定', '不太符合', '完全不符合');

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
INSERT INTO `teach` VALUES ('B001', 'U009.html', './knowledge/usecase/U009.html');
INSERT INTO `teach` VALUES ('B001', 'U010.html', './knowledge/usecase/U010.html');
INSERT INTO `teach` VALUES ('B002', 'U001.ppt', './knowledge/usecase/U001.ppsx');
INSERT INTO `teach` VALUES ('B002', 'U011.html', './knowledge/usecase/U011.html');
INSERT INTO `teach` VALUES ('B002', 'U012.html', './knowledge/usecase/U012.html');
INSERT INTO `teach` VALUES ('B003', 'U003.html', './knowledge/usecase/U003.html');
INSERT INTO `teach` VALUES ('B003', 'U004.txt', './knowledge/usecase/U004.txt');
INSERT INTO `teach` VALUES ('B003', 'U005.ppt', './knowledge/usecase/U005.ppsx');
INSERT INTO `teach` VALUES ('B003', 'U008.swf', './knowledge/usecase/U008.swf');
INSERT INTO `teach` VALUES ('B003', 'U013.html', './knowledge/usecase/U013.html');
INSERT INTO `teach` VALUES ('B004', 'U005.ppt', './knowledge/usecase/U005.ppsx');
INSERT INTO `teach` VALUES ('B004', 'U014.html', './knowledge/usecase/U014.html');
INSERT INTO `teach` VALUES ('B004', 'U015.ppt', './knowledge/usecase/U015.ppt');
INSERT INTO `teach` VALUES ('B005', 'U002.ppt', './knowledge/usecase/U002.ppsx');
INSERT INTO `teach` VALUES ('B005', 'U006.ppt', './knowledge/usecase/U006.ppsx');
INSERT INTO `teach` VALUES ('B005', 'U016.html', './knowledge/usecase/U016.html');
INSERT INTO `teach` VALUES ('B006', 'U006.ppt', './knowledge/usecase/U006.ppsx');
INSERT INTO `teach` VALUES ('B006', 'U017.html', './knowledge/usecase/U017.html');
INSERT INTO `teach` VALUES ('B006', 'U018.html', './knowledge/usecase/U018.html');
INSERT INTO `teach` VALUES ('B007', 'U007.ppt', './knowledge/usecase/U007.ppsx');
INSERT INTO `teach` VALUES ('B007', 'U019.html', './knowledge/usecase/U019.html');
INSERT INTO `teach` VALUES ('B007', 'U021.html', './knowledge/usecase/U021.html');
INSERT INTO `teach` VALUES ('B007', 'U028.html', './knowledge/usecase/U028.html');
INSERT INTO `teach` VALUES ('B008', 'U005.ppt', './knowledge/usecase/U005.ppsx');
INSERT INTO `teach` VALUES ('B008', 'U020.html', './knowledge/usecase/U020.html');
INSERT INTO `teach` VALUES ('B009', 'U006.ppt', './knowledge/usecase/U006.ppsx');
INSERT INTO `teach` VALUES ('B009', 'U022.html', './knowledge/usecase/U022.html');
INSERT INTO `teach` VALUES ('B009', 'U023.html', './knowledge/usecase/U023.html');
INSERT INTO `teach` VALUES ('B010', 'U007.ppt', './knowledge/usecase/U007.ppsx');
INSERT INTO `teach` VALUES ('B010', 'U025.html', './knowledge/usecase/U025.html');
INSERT INTO `teach` VALUES ('B011', 'U006.ppt', './knowledge/usecase/U006.ppsx');
INSERT INTO `teach` VALUES ('B011', 'U022.html', './knowledge/usecase/U022.html');
INSERT INTO `teach` VALUES ('B011', 'U024.html', './knowledge/usecase/U024.html');
INSERT INTO `teach` VALUES ('B012', 'U002.ppt', './knowledge/usecase/U002.ppsx');
INSERT INTO `teach` VALUES ('B012', 'U026.html', './knowledge/usecase/U026.html');
INSERT INTO `teach` VALUES ('B012', 'U027.html', './knowledge/usecase/U027.html');
INSERT INTO `teach` VALUES ('B013', 'U007.ppt', './knowledge/usecase/U007.ppsx');
INSERT INTO `teach` VALUES ('B013', 'U028.html', './knowledge/usecase/U028.html');
INSERT INTO `teach` VALUES ('B013', 'U029.html', './knowledge/usecase/U029.html');
INSERT INTO `teach` VALUES ('P001', 'U002.ppt', './knowledge/usecase/U002.ppsx');
INSERT INTO `teach` VALUES ('P001', 'U003.html', './knowledge/usecase/U003.html');
INSERT INTO `teach` VALUES ('P001', 'U005.ppt', './knowledge/usecase/U005.ppsx');
INSERT INTO `teach` VALUES ('P001', 'U008.swf', './knowledge/usecase/U008.swf');
INSERT INTO `teach` VALUES ('P002', 'U006.ppt', './knowledge/usecase/U006.ppsx');
INSERT INTO `teach` VALUES ('P002', 'U008.swf', './knowledge/usecase/U008.swf');
INSERT INTO `teach` VALUES ('P002', 'U022.html', './knowledge/usecase/U022.html');
INSERT INTO `teach` VALUES ('P003', 'U007.ppt', './knowledge/usecase/U007.ppsx');
INSERT INTO `teach` VALUES ('P003', 'U008.swf', './knowledge/usecase/U008.swf');
INSERT INTO `teach` VALUES ('P003', 'U025.html', './knowledge/usecase/U025.html');
INSERT INTO `teach` VALUES ('P003', 'U029.html', './knowledge/usecase/U029.html');

-- ----------------------------
-- Table structure for test
-- ----------------------------
DROP TABLE IF EXISTS `test`;
CREATE TABLE `test` (
  `kid` varchar(20) NOT NULL,
  `tid` varchar(20) NOT NULL,
  `testhour` int(11) DEFAULT '0',
  `testminute` int(11) DEFAULT '45',
  `limitscore` int(11) DEFAULT '60',
  PRIMARY KEY (`kid`,`tid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of test
-- ----------------------------
INSERT INTO `test` VALUES ('B001', 'T001', '0', '45', '60');
INSERT INTO `test` VALUES ('B002', 'T002', '0', '45', '60');
INSERT INTO `test` VALUES ('B003', 'T003', '0', '45', '60');
INSERT INTO `test` VALUES ('B004', 'T004', '0', '45', '60');
INSERT INTO `test` VALUES ('B005', 'T005', '0', '45', '60');
INSERT INTO `test` VALUES ('B006', 'T006', '0', '45', '60');
INSERT INTO `test` VALUES ('B007', 'T007', '0', '45', '60');
INSERT INTO `test` VALUES ('B008', 'T005', '0', '45', '60');
INSERT INTO `test` VALUES ('B009', 'T006', '0', '45', '60');
INSERT INTO `test` VALUES ('B010', 'T007', '0', '45', '60');
INSERT INTO `test` VALUES ('B011', 'T005', '0', '45', '60');
INSERT INTO `test` VALUES ('B012', 'T005', '0', '45', '60');
INSERT INTO `test` VALUES ('B013', 'T007', '0', '45', '60');
INSERT INTO `test` VALUES ('P001', 'T008', '0', '45', '60');
INSERT INTO `test` VALUES ('P002', 'T009', '0', '45', '60');
INSERT INTO `test` VALUES ('P002', 'T010', '0', '45', '60');

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
INSERT INTO `testcase` VALUES ('T001', '1', '可替换#define PI 3.1415926的语句是', 'B', 'float PI 3.1415926;', 'const float PI=3.1415926;', 'const PI(3.1415926);', 'const 3.1415926;', '20');
INSERT INTO `testcase` VALUES ('T001', '2', '下列不是C++语言的基本数据类型的是', 'D', '字符类型', '整数类型', '逻辑类型', '枚举类型', '20');
INSERT INTO `testcase` VALUES ('T001', '3', '在C++语言中，要求参加运算的数必须是整数的运算符是', 'D', '/', '%', '*', '&&', '20');
INSERT INTO `testcase` VALUES ('T001', '4', 'C++中声明常量的关键字是', 'A', 'const', 'extern', 'public', 'enum', '20');
INSERT INTO `testcase` VALUES ('T001', '5', '下列关于C++标识符的命名不合法的是', 'C', 'Pad', 'name', 'A#be', '_a12', '20');
INSERT INTO `testcase` VALUES ('T002', '1', '下列哪种默认参数的声明是不正确的', 'C', ' int max(int a，int b，int c，int d=0);', ' int max(int a，int b，int c=0，int d=0);', ' int max(int a=0，int b，int c=0，int d=0);', ' int max(int a，int b=0，int c=0，int d=0);', '7');
INSERT INTO `testcase` VALUES ('T002', '2', '设函数void inc(int)将形参加1，如有整型变量int i=10；则执行inc(i)；后，i的值为', 'B', '9', '10', '11', '未知', '7');
INSERT INTO `testcase` VALUES ('T002', '3', '设int &max(int ＆，int &)返回两参数中较大者，如有两整型变量int a=10；int b=15；在执行max(a，b)++后，a，b值分别为', 'C', '10,15', '11,15', '10,16', '1l,16', '7');
INSERT INTO `testcase` VALUES ('T002', '4', '设类Test中存在成员static int x，则下列哪种初始化方式是正确的', 'C', 'Test：：int x=25；', 'int x=25；', 'int Test：：x=25；', 'int Test x=25；', '7');
INSERT INTO `testcase` VALUES ('T002', '5', '设a,b,c,d,m,n均为整型变量，且a=7,b=5,c=3,d=8,m=2,n=2，则逻辑表达式(m=a>b)&&(n=c>d)运算后，n的值为', 'A', '0', '1', '2', '3', '7');
INSERT INTO `testcase` VALUES ('T002', '6', '设inta=12;，则执行完语句a+=a*a后，a的值是', 'C', '12', '144', '156', '288', '7');
INSERT INTO `testcase` VALUES ('T002', '7', '以下正确的定义语句是', 'C', 'int a[1][4]={1,2,3,4,5};', 'float x[3][]={{1},{2},{3}};', 'long b[2][3]={{1},{1,2},{1,2,3}};', 'double y[][3]={0};', '7');
INSERT INTO `testcase` VALUES ('T002', '8', '以下不正确的定义语句是', 'C', 'double x[5]={2.0,4.0,6.0,8.0,10.0};', 'int y[5]={0,1,3,5,7,9}; ', 'char c1[]={′1′,′2′,′3′,′4′,′5′};', 'char c2[]={′\\x10′,′\\xa′,′\\x8′};', '7');
INSERT INTO `testcase` VALUES ('T002', '9', '已有定义int k=2；int *p1，*p2；且p1和p2均已指向变量k，下面能正确执行的赋值语句是', 'A', 'k=*p1+*p2;', 'p2=k;', 'p1=*p2;', '*p1=p2;', '7');
INSERT INTO `testcase` VALUES ('T002', '10', '已知以下程序段：\r\nint func(int x, int y)  \r\n{	return x*y;   }\r\nint main()\r\n{\r\n	int j=5;\r\n	int m=func ( j , 2);\r\n	int k=func ( j, 3) ;\r\n	return 0;\r\n}\r\n则程序中变量m和k的值分别为（ ）\r\n', 'B', '15，10', '10，15', '10，10', '15，15', '7');
INSERT INTO `testcase` VALUES ('T002', '11', '下面for语句结束后，i的值是for(i=0;i<100;i++);', 'B', '99', '100', '101', '102', '7');
INSERT INTO `testcase` VALUES ('T002', '12', '写出下列代码段中变量c的值int a=2,b=5; int c=a+b;', 'A', '7', '8', '9', '10', '7');
INSERT INTO `testcase` VALUES ('T002', '13', '写出下列表达式的值a=3*5,a=b=3*2;', 'C', '15', '5', '6', '3', '7');
INSERT INTO `testcase` VALUES ('T002', '14', '设int a=8,b=4;则条件表达式8<4?a:b的值为', 'C', '0', '1', '4', '8', '9');
INSERT INTO `testcase` VALUES ('T003', '1', '下列枚举类型的定义中，包含枚举值3的是', 'A', 'enum test {RED, YELLOW, BLUE, BLACK};', 'enum test {RED, YELLOW=4, BLUE, BLACK};', 'enum test {RED=-1, YELLOW,BLUE, BLACK};', 'enum test {RED, YELLOW=6, BLUE, BLACK};', '25');
INSERT INTO `testcase` VALUES ('T003', '2', '下列不是C++语言的基本数据类型的是', 'D', '字符类型', '整数类型', '逻辑类型', '枚举类型', '25');
INSERT INTO `testcase` VALUES ('T003', '3', '枚举类型中的每个枚举常量的值都是一个', 'A', '整数', '浮点数', '字符', '逻辑值', '25');
INSERT INTO `testcase` VALUES ('T003', '4', '下列枚举类型的定义中，包含枚举值5的是', 'B', 'enum test {RED, YELLOW, BLUE, BLACK};', 'enum test {RED, YELLOW=4, BLUE, BLACK};', 'enum test {RED=-1, YELLOW,BLUE, BLACK};', 'enum test {RED, YELLOW=6, BLUE, BLACK};', '25');
INSERT INTO `testcase` VALUES ('T004', '1', '下面结构体的定义语句中，错误的是', 'B', 'struct ord {int x;int y;int z;}; struct ord a; ', 'struct ord {int x;int y;int z;} struct ord a;', 'struct ord {int x;int y;int z;} a;', 'struct {int x;int y;int z;} a;', '50');
INSERT INTO `testcase` VALUES ('T004', '2', '设有定义： struct complex { int real，unreal；} data1＝{1,8}，data2； 则以下赋值语句中错误的是( )。', 'A', 'data2＝(2,6)；', 'data2＝data1；', 'data2.real＝data1.real；', 'data2.unreal＝data1.unreal；', '50');
INSERT INTO `testcase` VALUES ('T005', '1', '以下各组选项中，均能正确定义二维实型数组a的选项是', 'C', 'float a[3][4];  float a[ ][4];     float a[3][ ]={{1},{0}}; ', 'float a(3,4);   float a[3][4];    float a[ ][ ]={{0},{0}};', 'float a[3][4]; static float a[ ][4]={{0},{0}};  auto float a[ ][4]={{0},{0},{0}};', 'float a[3][4]; float a[3][ ];     float a[ ][4];', '16');
INSERT INTO `testcase` VALUES ('T005', '2', '在C++语言中，引用数组元素时，其数组下标的数据类型不允许是', 'D', '整型常量', '整型常量或整型表达式', '整型表达式', '变量', '16');
INSERT INTO `testcase` VALUES ('T005', '3', '若有说明: int a[3][4]，则对a数组元素的正确引用是', 'B', 'a[1+1][0]', 'a[1][2]', 'a[1,3]', 'a(2)(1)', '16');
INSERT INTO `testcase` VALUES ('T005', '4', '若有说明：int a[ ][4]={0,0};下面不正确的叙述是', 'A', '数组a的每个元素都可得到初值0 ', '二维数组a的第一维大小为1', '当初值的个数能被第二维的常量表达式的值除尽时，所得商数就是第一维的大小', '只有元素a[0][0]和a[0][1]可得到初值，其余元素均得不到确定的初值', '16');
INSERT INTO `testcase` VALUES ('T005', '5', '以下能正确定义数组并正确赋初值的语句是', 'D', 'int N=5,b[N] [N];', 'int a[2]={ {1}, {3}, {4}, {5} };', 'int c[2] []={ {1,2}, {3,4} };', 'int d[3] [2]={ {1,2},{3,4} };', '16');
INSERT INTO `testcase` VALUES ('T005', '6', '若有以下定义，则对a数组元素的正确引用是（ ）。 int a[5],*p=a; ', 'D', '*&a[5]', 'a+2', '*(p+5)', '*(a+2)', '20');
INSERT INTO `testcase` VALUES ('T006', '1', '通常拷贝构造函数的参数是', 'C', '某个对象名', '某个对象的成员名', '某个对象的引用名', '某个对象的指针名', '14');
INSERT INTO `testcase` VALUES ('T006', '2', '有关内存分配的说法中，是错误是：', 'C', '指针变量可以保存动态分配的存储空间', '用new为指针变量分配的存储空间在堆区', '数据元素存储在堆区的数组在建立时就被初始化(清零)', '指向静态变量的指针不必用delete释放', '14');
INSERT INTO `testcase` VALUES ('T006', '3', '设有如下定义：int num=20406； int * np；float * mp；则以下正确的是：', 'A', 'np=&num', '*np=&num', 'mp=&np', 'mp=float np', '14');
INSERT INTO `testcase` VALUES ('T006', '4', '同一种数据类型的数组名和指针变量的内容都表示地址，它们之间的差别是:', 'A', '数组名代表的地址值不变，指针变量存放的地址可变', '数组名代表的存储空间长度不变，指针变量指向的存储空间长度可变', 'A和B均正确', '没有差别', '14');
INSERT INTO `testcase` VALUES ('T006', '5', '为指针变量赋值，以下语句中不正确的是', 'C', 'int *p=0；', 'float *p=(float*)50；', 'int *p=new 50；', 'float *p=new float[50]；', '14');
INSERT INTO `testcase` VALUES ('T006', '6', '设有说明：char s1[10],*s2=s1;则以下正确的语句是', 'C', 's1[]=”computer”', 's1[10]=”computer”', 's2=”computer”', '*s2=”computer”', '14');
INSERT INTO `testcase` VALUES ('T006', '7', '设有说明：int a[][4]={1,2,3,4,5,6,7,8,9,10},*p=*(a+1);以下可得数值为9 的表达式是', 'B', ' p+=3,*p++', ' p+=4,*(p++)', ' p+=4,*++p', 'p+=4,++*p', '16');
INSERT INTO `testcase` VALUES ('T007', '1', '通常拷贝构造函数的参数是', 'C', '某个对象名', '某个对象的成员名', '某个对象的引用名', '某个对象的指针名', '25');
INSERT INTO `testcase` VALUES ('T007', '2', '从程序片断:char name[] = \"C++\"; course(name);可判断函数 course 的调用采用的是', 'D', '传值调用', '带缺省参数值的函数调用', '引用调用', '传址调用', '25');
INSERT INTO `testcase` VALUES ('T007', '3', '数组元素地址的正确引用是', 'D', 'p+5 ', 'c++ ', '&c+1', '&c[0]', '25');
INSERT INTO `testcase` VALUES ('T007', '4', '若有以下定义，则对a数组元素的正确引用是（ ）。 int a[5],*p=a; ', 'D', '*&a[5] ', 'a+2', '*(p+5)', '*(a+2)', '25');
INSERT INTO `testcase` VALUES ('T008', '1', '下列枚举类型的定义中，包含枚举值3的是', 'A', 'enum test {RED, YELLOW, BLUE, BLACK};', 'enum test {RED, YELLOW=4, BLUE, BLACK};', 'enum test {RED=-1, YELLOW,BLUE, BLACK};', 'enum test {RED, YELLOW=6, BLUE, BLACK};', '10');
INSERT INTO `testcase` VALUES ('T008', '2', '下列不是C++语言的基本数据类型的是', 'D', '字符类型', '整数类型', '逻辑类型', '枚举类型', '10');
INSERT INTO `testcase` VALUES ('T008', '3', '枚举类型中的每个枚举常量的值都是一个', 'A', '整数', '浮点数', '字符', '逻辑值', '10');
INSERT INTO `testcase` VALUES ('T008', '4', '若有说明: int a[3][4]，则对a数组元素的正确引用是', 'B', 'a[1+1][0]', 'a[1][2]', 'a[1,3]', 'a(2)(1)', '20');
INSERT INTO `testcase` VALUES ('T008', '5', '下面结构体的定义语句中，错误的是', 'B', 'struct ord {int x;int y;int z;}; struct ord a; ', 'struct ord {int x;int y;int z;} struct ord a;', 'struct ord {int x;int y;int z;} a;', 'struct {int x;int y;int z;} a;', '10');
INSERT INTO `testcase` VALUES ('T008', '6', '在C++语言中，引用数组元素时，其数组下标的数据类型不允许是', 'D', '整型常量', '整型常量或整型表达式', '整型表达式', '变量', '10');
INSERT INTO `testcase` VALUES ('T008', '7', '设有定义： struct complex { int real，unreal；} data1＝{1,8}，data2； 则以下赋值语句中错误的是( )。', 'A', 'data2＝(2,6)；', 'data2＝data1；', 'data2.real＝data1.real；', 'data2.unreal＝data1.unreal；', '20');
INSERT INTO `testcase` VALUES ('T008', '8', '以下各组选项中，均能正确定义二维实型数组a的选项是', 'C', 'float a[3][4];  float a[ ][4];     float a[3][ ]={{1},{0}}; ', 'float a(3,4);   float a[3][4];    float a[ ][ ]={{0},{0}};', 'float a[3][4]; static float a[ ][4]={{0},{0}};  auto float a[ ][4]={{0},{0},{0}};', 'float a[3][4]; float a[3][ ];     float a[ ][4];', '10');
INSERT INTO `testcase` VALUES ('T009', '1', '通常拷贝构造函数的参数是', 'C', '某个对象名', '某个对象的成员名', '某个对象的引用名', '某个对象的指针名', '14');
INSERT INTO `testcase` VALUES ('T009', '2', '有关内存分配的说法中，是错误是：', 'C', '指针变量可以保存动态分配的存储空间', '用new为指针变量分配的存储空间在堆区', '数据元素存储在堆区的数组在建立时就被初始化(清零)', '指向静态变量的指针不必用delete释放', '14');
INSERT INTO `testcase` VALUES ('T009', '3', '设有如下定义：int num=20406； int * np；float * mp；则以下正确的是：\r\n设有如下定义：int num=20406； int * np；float * mp；则以下正确的是：\r\n设有如下定义：int num=20406； int * np；float * mp；则以下正确的是：\r\n设有如下定义：int num=20406； int * np；float * mp；则以下正确的是：\r\n', 'A', 'np=&num', '*np=&num', 'mp=&np', 'mp=float np', '14');
INSERT INTO `testcase` VALUES ('T009', '4', '同一种数据类型的数组名和指针变量的内容都表示地址，它们之间的差别是:', 'A', '数组名代表的地址值不变，指针变量存放的地址可变', '数组名代表的存储空间长度不变，指针变量指向的存储空间长度可变', 'A和B均正确', '没有差别', '14');
INSERT INTO `testcase` VALUES ('T009', '5', '为指针变量赋值，以下语句中不正确的是', 'C', 'int *p=0；', 'float *p=(float*)50；', 'int *p=new 50；', 'float *p=new float[50]；', '14');
INSERT INTO `testcase` VALUES ('T009', '6', '设有说明：char s1[10],*s2=s1;则以下正确的语句是', 'C', 's1[]=”computer”', 's1[10]=”computer”', 's2=”computer”', '*s2=”computer”', '14');
INSERT INTO `testcase` VALUES ('T009', '7', '设有说明：int a[][4]={1,2,3,4,5,6,7,8,9,10},*p=*(a+1);以下可得数值为9 的表达式是', 'B', ' p+=3,*p++', ' p+=4,*(p++)', ' p+=4,*++p', 'p+=4,++*p', '16');
INSERT INTO `testcase` VALUES ('T010', '1', '通常拷贝构造函数的参数是', 'C', '某个对象名', '某个对象的成员名', '某个对象的引用名', '某个对象的指针名', '25');
INSERT INTO `testcase` VALUES ('T010', '2', '从程序片断:char name[] = \"C++\"; course(name);可判断函数 course 的调用采用的是', 'D', '传值调用', '带缺省参数值的函数调用', '引用调用', '传址调用', '25');
INSERT INTO `testcase` VALUES ('T010', '3', '数组元素地址的正确引用是', 'D', 'p+5 ', 'c++ ', '&c+1', '&c[0]', '25');
INSERT INTO `testcase` VALUES ('T010', '4', '若有以下定义，则对a数组元素的正确引用是（ ）。 int a[5],*p=a; ', 'D', '*&a[5] ', 'a+2', '*(p+5)', '*(a+2)', '25');

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
INSERT INTO `testresult` VALUES ('6', 'B012', 'T008', '100');
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
  `hardlevel` int(20) DEFAULT NULL COMMENT '代表用例的难度，范围在1-10之间',
  PRIMARY KEY (`cid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of usecase
-- ----------------------------
INSERT INTO `usecase` VALUES ('U001.ppt', '0.2,0.3,0.5', '0.5,0.5,0,0', '1,0,0,0', '1,0', '1,0,0,0,0', '5');
INSERT INTO `usecase` VALUES ('U002.ppt', '0.5,0,0.5', '0.5,0.5,0,0', '1,0,0,0', '1,0', '1,0,0,0,0', '7');
INSERT INTO `usecase` VALUES ('U003.html', '0.4,0.1,0.5', '0.6,0.4,0,0', '0,1,0,0', '1,0', '1,0,0,0,0', '6');
INSERT INTO `usecase` VALUES ('U004.txt', '0.3,0.3,0.4', '1,0,0,0', '0,0,0,1', '1,0', '1,0,0,0,0', '5');
INSERT INTO `usecase` VALUES ('U005.ppt', '0.4,0.3,0.3', '0.5,0.5,0,0', '1,0,0,0', '1,0', '1,0,0,0,0', '5');
INSERT INTO `usecase` VALUES ('U006.ppt', '0.5,0,0.5', '0.5,0.5,0,0', '1,0,0,0', '1,0', '1,0,0,0,0', '6');
INSERT INTO `usecase` VALUES ('U007.ppt', '0.4,0.1,0.5', '0.5,0.5,0,0', '1,0,0,0', '1,0', '1,0,0,0,0', '7');
INSERT INTO `usecase` VALUES ('U008.swf', '0.4,0.3,0.3', '0,0,0,1', '0,0,1,0', '1,0', '1,0,0,0,0', '5');
INSERT INTO `usecase` VALUES ('U009.html', '0.2,0.3,0.5', '0.6,0.4,0,0', '0,1,0,0', '1,0', '1,0,0,0,0', '5');
INSERT INTO `usecase` VALUES ('U010.html', '0.4,0.3,0.3', '0.6,0.4,0,0', '0,1,0,0', '1,0', '1,0,0,0,0', '5');
INSERT INTO `usecase` VALUES ('U011.html', '0.3,0.3,0.4', '0.6,0.4,0,0', '0,1,0,0', '1,0', '1,0,0,0,0', '4');
INSERT INTO `usecase` VALUES ('U012.html', '0.5,0,0.5', '0.6,0.4,0,0', '0,1,0,0', '1,0', '1,0,0,0,0', '6');
INSERT INTO `usecase` VALUES ('U013.html', '0.4,0.3,0.3', '0.6,0.4,0,0', '0,1,0,0', '1,0', '1,0,0,0,0', '7');
INSERT INTO `usecase` VALUES ('U014.html', '0.4,0.3,0.3', '0.6,0.4,0,0', '0,1,0,0', '1,0', '1,0,0,0,0', '7');
INSERT INTO `usecase` VALUES ('U015.ppt', '0.2,0.3,0.5', '0.5,0.5,0,0', '1,0,0,0', '1,0', '1,0,0,0,0', '5');
INSERT INTO `usecase` VALUES ('U016.html', '0.4,0.3,0.3', '0.6,0.4,0,0', '0,1,0,0', '1,0', '1,0,0,0,0', '7');
INSERT INTO `usecase` VALUES ('U017.html', '0.3,0.3,0.4', '0.6,0.4,0,0', '0,1,0,0', '1,0', '1,0,0,0,0', '6');
INSERT INTO `usecase` VALUES ('U018.html', '0.4,0.1,0.5', '0.6,0.4,0,0', '0,1,0,0', '1,0', '1,0,0,0,0', '5');
INSERT INTO `usecase` VALUES ('U019.html', '0.5,0,0.5', '0.6,0.4,0,0', '0,1,0,0', '1,0', '1,0,0,0,0', '8');
INSERT INTO `usecase` VALUES ('U020.html', '0.3,0.3,0.4', '0.6,0.4,0,0', '0,1,0,0', '1,0', '1,0,0,0,0', '8');
INSERT INTO `usecase` VALUES ('U021.html', '0.4,0.1,0.5', '0.6,0.4,0,0', '0,1,0,0', '1,0', '1,0,0,0,0', '4');
INSERT INTO `usecase` VALUES ('U022.html', '0.5,0,0.5', '0.6,0.4,0,0', '0,1,0,0', '1,0', '1,0,0,0,0', '5');
INSERT INTO `usecase` VALUES ('U023.html', '0.3,0.3,0.4', '0.6,0.4,0,0', '0,1,0,0', '1,0', '1,0,0,0,0', '7');
INSERT INTO `usecase` VALUES ('U024.html', '0.2,0.3,0.5', '0.6,0.4,0,0', '0,1,0,0', '1,0', '1,0,0,0,0', '5');
INSERT INTO `usecase` VALUES ('U025.html', '0.4,0.1,0.5', '0.6,0.4,0,0', '0,1,0,0', '1,0', '1,0,0,0,0', '5');
INSERT INTO `usecase` VALUES ('U026.html', '0.4,0.1,0.5', '0.6,0.4,0,0', '0,1,0,0', '1,0', '1,0,0,0,0', '4');
INSERT INTO `usecase` VALUES ('U027.html', '0.5,0,0.5', '0.6,0.4,0,0', '0,1,0,0', '1,0', '1,0,0,0,0', '8');
INSERT INTO `usecase` VALUES ('U028.html', '0.5,0,0.5', '0.6,0.4,0,0', '0,1,0,0', '1,0', '1,0,0,0,0', '8');
INSERT INTO `usecase` VALUES ('U029.html', '0.4,0.3,0.3', '0.6,0.4,0,0', '0,1,0,0', '1,0', '1,0,0,0,0', '5');
