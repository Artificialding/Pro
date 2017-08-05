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
	if(NULL == buyerHead)
	{
		printf(BUYER_HEAD_IS_NULL);
		return;
	}
	system("clear");
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
			printf("格式错误\n");
			return;
		}
		switch(choose)
		{
			case 1:
				
				break;
			case 2:
				buyerRegist(buyerHead);
				break;
			case 0:
				saveData(buyerHead);
				printf("退出成功\n");
				return;
			default:
				printf("error\n");
				break;
		}
	}


}
