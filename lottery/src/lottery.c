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
#include "lotcontrol.h"


int identifyCardId(char *cardId)
{
	int len = 0;
	int i = 0;
	len = strlen(cardId);
	if(len < 18)//少于18位
	{
		return 0;
	}
	else
	{
		for(i = 0;i < 17;++i)
		{
			if(cardId[i] < '0' || cardId[i] > '9')//前17位出现非数字
			{	
				printf("您输入的身份证号码格式有误！\n");
				return 0;
			}
		}
		if(!(cardId[17] == 'X' || (cardId[17] >= '0' && cardId[17] <= '9')))//最后一位
		{
			printf("您输入的身份证号码格式有误！\n");
			return 0;
		}
		else//是个有效的身份证号码//321324 1995 1004485X
		{
			char strYear[5] = {0};
			strYear[0] = cardId[6];
			strYear[1] = cardId[7];
			strYear[2] = cardId[8];
			strYear[3] = cardId[9];
			int year = atoi(strYear);
			if(2017 - year < 18)//未满18周岁
			{
				printf("对不起！您未满18周岁\n，\
						根据《中华人民共和国未成年人保护法》\
						相关规定，禁止未成年人购买彩票！");
				return 0;
			}
		}		
	}
	return 1;
}

int identifyTelNum(char *telNum)
{
	int len = strlen(telNum);
	if(len != 11)
	{
		printf("手机号码位数有误！\n");
		return 0;
	}
	else
	{
		int i = 0;
		for(i = 0;i < 11;++i)
		{
			if(telNum[i] < '0' || telNum[i] > '9')
			{
				printf("手机格式有误！\n");
				return 0;
			}
	printf("4.账户充值\n");
		}
		return 1;
	}
}

/*******************处理密码********************/
int initPasswd(char *newPasswd)
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
			strcpy(newPasswd,strPasswdConfirm);			
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
	if(NULL != getPreNodePoint(buyerHead,name))
	{
		printf("该用户名已被注册！\n");
		return 0;
	}
	strcpy(buyer.name,name);

	/***************手机号码***********************/
	char telNum[12] = "";
	printf("请输入您的手机号码:");
	scanf("%s",telNum);
	if(0 == identifyTelNum(telNum))
	{
		printf("注册失败！\n");
		return 0;
	}
	strcpy(buyer.telNum,telNum);
	/**************初始化密码************/
	char newPasswd[10] = "";
	if(0 == initPasswd(newPasswd))
	{
		printf("注册失败!\n");
		return 0;
	}
	strcpy(buyer.passwd,newPasswd);

	/******************后插彩民节点********************/
	if(0 == insertAfterBuyerLink(buyerHead,&buyer))
	{
		printf("注册失败！\n");
		return 0;
	}
	printf("注册成功！\n");
	return 1;
}
/******************登录************************/
int loginSystem(BuyerLink *buyerHead)
{
	char name[20] = "";
	char passwd[10] = "";
	printf("请输入用户名:");
	scanf("%s",name);
	if(0 == strcmp("admin",name))
	{
		printf("请输入密码:");
		scanf("%s",passwd);
		if(0 == strcmp("admin",passwd))
		{
			adminMenuControl();	//进入管理员菜单界面
			return 1;
		}
		else
		{
			printf("你输入的密码有误！\n");
			return 0;
		}
	}
	else if(0 == strcmp("notary",name))
	{
		printf("请输入密码:");
		scanf("%s",passwd);
		if(0 == strcmp("notary",passwd))
		{
			notaryMenuControl();	//进入公正员界面
			return 1;
		}
		else
		{
			printf("你输入的密码有误！\n");
			return 0;
		}
	}
	else
	{
		BuyerLink *pre = getPreNodePoint(buyerHead,name);
		if(NULL == pre)
		{
			printf("您输入的用户名不存在！\n");
			return 0;
		}
		else
		{
			if(1 == pre -> next ->data.flag)
			{
				printf("您的帐号被冻结，请联系管理员！\n");
				return 0;
			}
			printf("请输入密码:");
			scanf("%s",passwd);
			if(0 == strcmp(passwd,pre -> next ->data.passwd))
			{
				buyerMenuControl(buyerHead,name);//进入彩民菜单界面
				return 1;
			}
			else
			{
				printf("你输入的密码有误！\n");
				return 0;
			}
		}
	}
}

int printOneMessage(BuyerLink *buyerHead,char *name)
{
	if(NULL == buyerHead)
	{
		printf(BUYER_HEAD_IS_NULL);
		return 0;
	}
	BuyerLink *pre = getPreNodePoint(buyerHead,name);
	if(NULL != pre)
	{
		Buyer buyer;
		memset(&buyer,0,sizeof(Buyer));
		buyer = pre -> next -> data;
		printf("ID\t用户名\t身份证号码\t\t手机号码\t账户余额\n");
		printf("%d\t%s\t%s\t%s\t%.2lf\n",\
				buyer.id,\
				buyer.name,\
				buyer.cardId,\
				buyer.telNum,\
				buyer.balance);
		return 1;
	}
	else
	{
		printf("对不起您的账户被冻结，请联系管理员！\n");
		return 0;
	}
}
int rechargeAccount(BuyerLink *buyerHead,char *name)
{
	if(NULL == buyerHead)
	{
		printf(BUYER_HEAD_IS_NULL);
		return 0;
	}
	BuyerLink *pre = getPreNodePoint(buyerHead,name);
	if(NULL != pre)
	{	
		double charge = 0.00;
		printf("请输入充值金额:");
		scanf("%lf",&charge);
		if(getchar() != '\n')
		{
			while(getchar() != '\n');
			printf("格式有误！\n");
			return 0;
		}
		pre = pre -> next;
		pre -> data.balance += charge;
		return 1;
	}
	else
	{
		printf("对不起你的帐号被冻结，请联系管理员！\n");
		return 0;		
	}
}

int changePasswd(BuyerLink *buyerHead,char *name)
{
	if(NULL == buyerHead)
	{
		printf(BUYER_HEAD_IS_NULL);
		return 0;
	}
	BuyerLink *pre = getPreNodePoint(buyerHead,name);
	if(NULL != pre)
	{
		char newPasswd[10] = "";
		char confirmPasswd[10] = "";
		int chance = 3;
		pre = pre -> next;
		if(1 == identifyPasswd(pre -> data.passwd,chance))
		{
			printf("请输入新密码:");
			scanf("%s",newPasswd);
			if(0 == strcmp(pre -> data.passwd,newPasswd))
			{	
				printf("新密码不能和原密码相同！\n");
				return 0;
			}
			else
			{
				printf("请再次输入新密码:");
				scanf("%s",confirmPasswd);
				if(0 == strcmp(newPasswd,confirmPasswd))
				{
					strcpy(pre -> data.passwd,confirmPasswd);
					printf("密码修改成功,请重新登录！\n");
					return 1;
				}
				else
				{
					printf("两次输入密码不一致，修改失败！\n");
					return 0;
				}
			}
		}
		else
		{
			printf("%d次机会用完,冻结！\n",chance);
			return 0;
		}
	}
	else
	{
		printf("对不起您的账户被冻结，请联系管理员！\n");
		return 0;
	}
}

int identifyPasswd(char *passwd,int chance)
{
	char inputPasswd[10] = "";
	printf("请输入原密码:");
	scanf("%s",inputPasswd);
	if(0 == strcmp(passwd,inputPasswd))
	{
		return 1;
	}
	else
	{
		if(chance == 1)
		{
			return 0;
		}
		printf("错误！还有%d次机会。\n",--chance);
		return identifyPasswd(passwd,chance);
	}
}
int logOffAccount(BuyerLink *buyerHead,char *name)
{
	if(NULL == buyerHead)
	{
		printf(BUYER_HEAD_IS_NULL);
		return 0;
	}
	BuyerLink *pre = getPreNodePoint(buyerHead,name);
	if(NULL == pre)
	{
		printf("用户不存在！\n");
		return 0;
	}
	printf("您确定要注销账户吗？注销后可联系管理员找回帐号。\n");
	printf("「确认」回车     「取消」ESC：");
	char ch = getchar();
	while(getchar() != '\n');
	if(ch == '\n')
	{
		pre -> next -> data.flag = 1;
		printf("注销成功！\n");
		return 1;
	}
	else if(ch == 27)
	{
		printf("取消注销成功！\n");
		return 0;
	}
	else
	{
		printf("error注销失败！\n");
		return 0;
	}
}



