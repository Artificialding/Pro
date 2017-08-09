/*
* Copyright(c)Ziyi.Gao
* 文 件 名：lotcontrol.h
* 描    述：Control层 菜单控制函数声明
* 作    者：ziyi.Gao
* 创建日期：2017-8-5
* 完成日期：2017-8-5
* 当前版本：1.0
*/

#ifndef _LOTCONTROL_H_
#define _LOTCONTROL_H_
#include "lotlink.h"
void mainMenuControl(BuyerLink *buyerHead,PubLink *pubHead,BuyLink *buyHead);//主菜单控制函数声明
void buyerMenuControl(BuyerLink *buyerHead,char *name,PubLink *pubHead,BuyLink *buyHead);//彩民菜单函数
int adminMenuControl(BuyerLink *buyerHead,PubLink *pubHead,BuyLink *buyHead);//管理员菜单控制函数声明
int notaryMenuControl(BuyerLink *buyerHead,PubLink *pubHead,BuyLink *buyHead);//公正员菜单控制函数声明


#endif
