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
int lotteryRole();                             //开奖规则
int identifyCardId(char *cardId);              //识别身份证号码
int identityTelNum(char *telNum);              //识别手机号码
int initPasswd(char *newPasswd,int chance);    //初始化密码
int getCurrentMaxId(BuyerLink *buyerHead);     //获取当前最大id值
int buyerRegist(BuyerLink *buyerHead);         //彩民注册
int loginSystem(BuyerLink *buyerHeadi,PubLink *pubHead,BuyLink *buyHead);  //登录
int getch(void);
void getPassword(char *pcPWD);                 //密码隐藏
int checkVerificationCode();                   //生成验证码
int retrievalPasswd(BuyerLink *buyerHead);     //找回密码

/**************Model层*彩民菜单*逻辑函数声明*********************/
int printOneMessage(BuyerLink *buyerHead,char *name);//个人信息
int buyLottery(BuyerLink *buyerHead,PubLink *pubHead,BuyLink *buyHead,char *name);//购买彩票
int machineSelect(BuyerLink *buyerHead,PubLink *pubHead,BuyLink *buyHead,char *name);//机选号码
int buyerSelect(BuyerLink *buyerHead,PubLink *pubHead,BuyLink *buyHead,char *name);//手选号码
int printBuyRecord(BuyerLink *buyerHead,PubLink *pubHead,BuyLink *buyHead,char *name); //购彩记录
int rechargeAccount(BuyerLink *buyerHead,char *name);//账户充值
int changePasswd(BuyerLink *buyerHead,char *name);   //修改密码
int identifyPasswd(char *passwd,int chance,char *name);         //输入比对原密码
int logOffAccount(BuyerLink *buyerHead,char *name);  //注销账户
//int buyerComment(BuyerLink *buyerHead,char *name,ComLink *commentHead);//彩民评论区

/**************Model层*管理员菜单*逻辑函数声明*********************/
int publishLottery(PubLink *pubHead);          //发行彩票
int printPubRecord(PubLink *pubHead);          //发行记录
int printAllBuyerMessage(BuyerLink *buyerHead);//所有彩民信息
int selectBuyer(BuyerLink *buyerHead);         //查找彩民
int printBuyerMessageByName(BuyerLink *buyerHead);//根据账户名
int printBuyerMessageById(BuyerLink *buyerHead);//根据账户id
int printBuyerMessageByBalance(BuyerLink *buyerHead);//根据账户余额
int sortBuyerMessage(BuyerLink *buyerHead);    //排序
int prizePoolAmount(PubLink *pubHead);         //奖池
int rechargeBuyerAccount(BuyerLink *buyerHead);//账户充值
int repairBuyerAccount(BuyerLink *buyerHead);  //激活账户

/**************Model层*公正员菜单*逻辑函数声明*********************/
int authorization(PubLink *pubHead);           //授权发行
int getBuyerLinkLen(BuyerLink *buyHead);                    //获取彩民链表长度
int drawLottery(BuyerLink *buyerHead,PubLink *pubHead,BuyLink *buyHead);//彩票开奖
int machineCreate(int *num);           //机器出球
int notaryCreate(int *num);            //人工出球
int awardBuyer(PubLink *pubHead,BuyLink *buyHead,BuyerLink *buyerHead);//发放奖金
int getLevel(int *pubNum,int *buyNum); //返回中奖等级
int printAwardBuyerMessage(BuyLink *cursor,int level);//列出获奖彩民信息
#endif
