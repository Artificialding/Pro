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
int initPasswd(char *newPasswd,int chance);    //初始化密码
int getCurrentMaxId(BuyerLink *buyerHead);     //获取当前最大id值
int buyerRegist(BuyerLink *buyerHead);         //彩民注册
int loginSystem(BuyerLink *buyerHeadi,PubLink *pubHead,BuyLink *buyHead);  //登录

/**************Model层*彩民菜单*逻辑函数声明*********************/
int printOneMessage(BuyerLink *buyerHead,char *name);//个人信息
int buyLottery(BuyerLink *buyerHead,PubLink *pubHead,BuyLink *buyHead,char *name);//购买彩票
int machineSelect(BuyerLink *buyerHead,PubLink *pubHead,BuyLink *buyHead,char *name);
int buyerSelect(BuyerLink *buyerHead,PubLink *pubHead,BuyLink *buyHead,char *name);
int printBuyRecord(BuyerLink *buyerHead,PubLink *pubHead,BuyLink *buyHead,char *name); //购彩记录
int rechargeAccount(BuyerLink *buyerHead,char *name);//账户充值
int changePasswd(BuyerLink *buyerHead,char *name);   //修改密码
int identifyPasswd(char *passwd,int chance);         //输入比对原密码
int logOffAccount(BuyerLink *buyerHead,char *name);  //注销账户

/**************Model层*管理员菜单*逻辑函数声明*********************/
int publishLottery(PubLink *pubHead);          //发行彩票
int printPubRecord(PubLink *pubHead);          //发行记录
int printAllBuyerMessage(BuyerLink *buyerHead);//所有彩民信息
//void selectBuyer();                          //查找彩民
int sortBuyerMessage(BuyerLink *buyerHead);           //排序

/**************Model层*公正员菜单*逻辑函数声明*********************/
int authorization(PubLink *pubHead);           //授权发行
int drawLottery(BuyerLink *buyerHead,PubLink *pubHead,BuyLink *buyHead);//彩票开奖
//int yaoHaoAlgorithm();                       //摇号算法


#endif
