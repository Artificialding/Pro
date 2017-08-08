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
void mainMenuControl(BuyerLink *buyerHead)
{
	system("clear");
	if(NULL == buyerHead)
	{
		printf(BUYER_HEAD_IS_NULL);
		return;
	}
	loadData(buyerHead);
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
				loginSystem(buyerHead);
				break;
			case 2://用户注册
				buyerRegist(buyerHead);
				break;
			case 0://退出系统
				saveData(buyerHead);
				freeBuyerLinkAllNode(buyerHead);
				printf("退出成功\n");
				return;
			default:
				printf("请选择菜单中有的选项\n");
				break;
		}
	}
}

void buyerMenuControl(BuyerLink *buyerHead,char *name)
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
				break;
			case 3://历史记录
				break;
			case 4://账户充值
				break;
			case 5://修改密码
				break;
			case 6://注销账户
				break;
			case 0://退出登录
				return;
			default:
				printf("请选择菜单中有的选项！\n");
				break;
		}
	}
}

void adminMenuControl(void)
{
	system("clear");
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
				break;
			case 2://所有彩民信息
				break;
			case 3://查找彩民
				break;
			case 4://排序
				break;
			case 0://退出登录
				return;
			default:
				printf("情选择菜单中有的选项！\n");
				break;
		}
	}
}

void notaryMenuControl(void)
{
	system("clear");
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
			case 1://开奖
				break;
			case 2://查看历史发行记录
				break;
			case 0://退出登录
				return;
			default:
				printf("请选择菜单中有的选项！\n");
				break;
		}
	}
}
