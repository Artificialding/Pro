/*
* Copyright(c)Ziyi.Gao
* 作    者：ziyi.Gao
* 创建日期：2017-8-5
* 完成日期：2017-8-5
* 当前版本：1.0
*/
#include "lotcontrol.h"
#include "lotview.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "lotlink.h"
#include "lottery.h"
void mainMenuControl(BuyerLink *buyerHead,PubLink *pubHead,BuyLink *buyHead)
{
	system("clear");
	if(NULL == buyerHead)
	{
		printf(BUYER_HEAD_IS_NULL);
		return;
	}
	if(NULL == pubHead)
	{
		printf(PUB_HEAD_IS_NULL);
		return;
	}
	if(NULL == buyHead)
	{
		printf(BUY_HEAD_IS_NULL);
		return;
	}
	loadData(buyerHead);
	loadPubData(pubHead);
	loadBuyData(buyHead);
	int choose = 0;
	while(1)
	{
		sleep(1);
		system("clear");
		mainMenu();
		printf("选择:");
		scanf("%d",&choose);
		if(getchar() != '\n')
		{
			while(getchar() != '\n');
			printf("格式错误,请重新输入！\n");
			continue;
		}
		switch(choose)
		{
			case 1://用户登录
				loginSystem(buyerHead,pubHead,buyHead);
				break;
			case 2://用户注册
				buyerRegist(buyerHead);
				break;
			case 3://开奖规则
				lotteryRole();
				break;
			case 0://退出系统
				saveData(buyerHead);
				savePubData(pubHead);
				saveBuyData(buyHead);
				freeBuyerLinkAllNode(buyerHead);
				freePubLinkAllNode(pubHead);
				freeBuyLinkAllNode(buyHead);
				printf("退出成功\n");
				return;
			default:
				printf("请选择菜单中有的选项\n");
				break;
		}
	}
}

void buyerMenuControl(BuyerLink *buyerHead,char *name,PubLink *pubHead,BuyLink *buyHead)
{
	system("clear");
	if(NULL == buyerHead)
	{
		printf(BUYER_HEAD_IS_NULL);
		return;
	}
	int choose = 0;
	while(1)
	{
		sleep(1);
		system("clear");
		buyerMenu();
		printf("选择:");
		scanf("%d",&choose);
		if(getchar() != '\n')
		{
			while(getchar() != '\n');
			printf("格式错误，请重新输入！\n");
			continue;
		}
		switch(choose)
		{
			case 1://个人信息
				printOneMessage(buyerHead,name);
				break;
			case 2://购买彩票
				buyLottery(buyerHead,pubHead,buyHead,name);
				break;
			case 3://彩民评论
				//buyerComment(buyerHead,commentHead);
				break;
			case 4://历史记录
				printBuyRecord(buyerHead,pubHead,buyHead,name);
				break;
			case 5://账户充值
				rechargeAccount(buyerHead,name);
				break;
			case 6://修改密码
				changePasswd(buyerHead,name);
				return;
			case 7://注销账户
				if(1 == logOffAccount(buyerHead,name))
				{
					return;
				}
				break;
			case 0://退出登录
				return;
			default:
				printf("请选择菜单中有的选项！\n");
				break;
		}
	}
}

int adminMenuControl(BuyerLink *buyerHead,PubLink *pubHead,BuyLink *buyHead)
{
	system("clear");
	if(NULL == buyerHead)
	{
		printf(BUYER_HEAD_IS_NULL);
		return 0;
	}
	int choose = 0;
	while(1)
	{
		sleep(1);
		system("clear");
		adminMenu();
		printf("选择:");
		scanf("%d",&choose);
		if(getchar() != '\n')
		{
			while(getchar() != '\n');
			printf("格式有误！\n");
			continue;
		}
		switch(choose)
		{
			case 1://发行彩票
				publishLottery(pubHead);
				break;
			case 2:
				prizePoolAmount(pubHead);
				break;
			case 3://发行记录
				printPubRecord(pubHead);
				break;
			case 4://所有彩民信息
				printAllBuyerMessage(buyerHead);
				break;
			case 5://查找彩民
				selectBuyer(buyerHead);
				break;
			case 6://排序
				sortBuyerMessage(buyerHead);
				break;
			case 0://退出登录
				return 1;
			default:
				printf("情选择菜单中有的选项！\n");
				break;
		}
	}
}

int notaryMenuControl(BuyerLink *buyerHead,PubLink *pubHead,BuyLink *buyHead)
{
	system("clear");
	if(NULL == buyerHead)
	{
		printf(BUYER_HEAD_IS_NULL);
		return 0;
	}
	if(NULL == pubHead)
	{
		printf(PUB_HEAD_IS_NULL);
		return 0;
	}
	int choose = 0;
	while(1)
	{
		sleep(1);
		system("clear");
		notaryMenu();
		printf("选择:");
		scanf("%d",&choose);
		if(getchar() != '\n')
		{
			while(getchar() != '\n');
			printf("格式有误，请重新输入！\n");
			continue;
		}
		switch(choose)
		{
			case 1://授权发行
				authorization(pubHead);
				break;
			case 2://彩票开奖
				drawLottery(buyerHead,pubHead,buyHead);
				break;
			case 3://查看历史发行记录
				printPubRecord(pubHead);
				break;
			case 0://退出登录
				return 0;
			default:
				printf("请选择菜单中有的选项！\n");
				break;
		}
	}
}
