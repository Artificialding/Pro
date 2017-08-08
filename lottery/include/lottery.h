/*
* Copyright(c)Ziyi.Gao
* 文 件 名：lottery.h
* 描    述：Model层逻辑函数声明
* 作    者：Ziyi.Gao
* 创建日期：2017-8-7
* 完成日期：
* 当前版本：1.0
*/

#ifndef _LOTTERY_H_
#define _LOTTERY_H_

#include "lotlink.h"
/**************Model层*主菜单*逻辑函数声明*********************/
int identifyCardId(char *cardId);              //识别身份证号码
int identityTelNum(char *telNum);              //识别手机号码
int changePasswd(char *newPasswd);             //修改密码
int buyerRegist(BuyerLink *buyerHead);         //彩民注册
int loginSystem(BuyerLink *buyerHead);         //登录

/**************Model层*彩民菜单*逻辑函数声明*********************/
int printOneMessage(BuyerLink *buyerHead,char *name);//个人信息
//void buyLottery();                           //购买彩票
//void printOneRecord();                       //够彩记录
//void rechargeAccount();                      //账户充值
//void changePasswd();                         //修改密码
//void logOffAccount();                        //注销账户

/**************Model层*管理员菜单*逻辑函数声明*********************/
//void publishLottery();                       //发行彩票
//void printAllBuyerMessage();                 //所有彩民信息
//void selectBuyer();                          //查找彩民
//void sort();                                 //排序

/**************Model层*公正员菜单*逻辑函数声明*********************/
//void drawLottery();                          //开奖
//void printdrawRecord();                      //查看发行记录


#endif
