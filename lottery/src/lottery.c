/*
* Copyright(c)Ziyi.Gao
* 文 件 名：lottery.c
* 描    述：实现Model层函数，对外提供：
* 作    者：Ziyi.Gao
* 创建日期：2017-8-7
* 完成日期：
* 当前版本：1.0
*/

#include "lottery.h"
#include "lotlink.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/***********************************Model层函数具体实现************************************/
/**************彩民********************************/
/**************识别身份证号码**************/
int identifyCardId(char *str)
{
	int len = 0;
	int i = 0;
	len = strlen(str);
	if(len < 18)//少于18位
	{
		return 0;
	}
	else
	{
		for(i = 0;i < 17;++i)
		{
			if(str[i] < '0' || str[i] > '9')//前17位出现非数字
			{	
				printf("您输入的身份证号码格式有误！\n");
				return 0;
			}
		}
		if(!(str[17] == 'X' || (str[17] >= '0' && str[17] <= '9')))//最后一位
		{
			printf("您输入的身份证号码格式有误！\n");
			return 0;
		}
		else//是个有效的身份证号码//321324 1995 1004485X
		{
			char strYear[5] = {0};
			strYear[0] = str[6];
			strYear[1] = str[7];
			strYear[2] = str[8];
			strYear[3] = str[9];
			int year = atoi(strYear);
			if(2017 - year < 18)//未满18周岁
			{
				printf("对不起！您未满18周岁，\
				根据《中华人民共和国未成年人保护法》相关规定，禁止未成年人购买彩票！");
				return 0;
			}
		}		
	}
	return 1;
}

int checkName(char *str)
{
	return 1;
}
int checkTelNum(char *str)
{
	int len = strlen(str);
	if(len != 12)
	{
		printf("手机号码长度不够！\n");
		return 0;
	}
	else
	{
		int i = 0;
		for(i = 0;i < 12;++i)
		{
			if(str[i] < '0' || str[i] > '9')
			{
				printf("手机格式有误！\n");
				return 0;
			}
		}
		return 1;
	}
}

/*******************处理密码********************/
int changePasswd(char *str)
{
	int i = 0;
	for(i = 0;i< 3;++i)
	{
		char strPasswd[10] = "";
		char strPasswdConfirm[10] = "";;
		printf("请输入密码:");
		scanf("%s",strPasswd);
		printf("请再次输入密码:");
		scanf("%s",strPasswdConfirm);
		if(0 != strcmp(strPasswd,strPasswdConfirm))
		{	
			printf("两侧密码不一致，请重新输入!\n");
			printf("你还有%d次输入机会！\n",2 - i);
			continue;
		}
		else
		{
			strcpy(str,strPasswdConfirm);			
			return 1;
		}
	}
	return 0;	
}

int buyerRegist(BuyerLink *buyerHead)
{
	
	Buyer buyer = {0}; 
	memset(&buyer,0,sizeof(Buyer));
	/****************身份证号码*********************/
	char cardId[19]= "";
	printf("请输入您的身份证号码:");
	scanf("%s",cardId);
	if(0 ==  identifyCardId(cardId))
	{
		printf("注册失败!\n");
		return 0;
	}
	strcpy(buyer.cardId,cardId);	
	
	/***************账户名**************************/
	char name[20] = "";
	printf("请输入账户名:");
	scanf("%s",name);
	if(0 == checkName(name))
	{
		printf("注册失败！\n");
		return 0;
	}
	strcpy(buyer.name,name);

	/***************手机号码***********************/
	char telNum[12] = "";
	printf("请输入您的手机号码:");
	scanf("%s",telNum);
	if(0 == checkTelNum(telNum))
	{
		printf("注册失败！\n");
		return 0;
	}
	strcpy(buyer.telNum,telNum);
	/**************修改密码************/
	char newPasswd[10] = "";
	if(0 == changePasswd(newPasswd))
	{
		printf("注册失败!\n");
		return 0;
	}
	strcpy(buyer.passwd,newPasswd);





/******************后插彩民节点********************/
	insertAfterBuyerLink(buyerHead,&buyer);
	return 1;
}




