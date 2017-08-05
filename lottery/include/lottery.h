/*
* Copyright(c)Ziyi.Gao
* 文 件 名：lottery.h
* 描    述：Model层逻辑函数生命
* 作    者：Ziyi.Gao
* 创建日期：2017-8-7
* 完成日期：
* 当前版本：1.0
*/

#ifndef _LOTTERY_H_
#define _LOTTERY_H_

#include "lotlink.h"
/**************Model层*彩民*逻辑函数声明*********************/
int identifyCardId(char *cardId);              //识别身份证号码
int identityTelNum(char *telNum);              //识别手机号码
int changePasswd(char *newPasswd);             //修改密码
int buyerRegist(BuyerLink *buyerHead);         //彩民注册
int loginSystem(BuyerLink *buyerHead);         //登录

#endif
