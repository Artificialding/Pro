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
#include <time.h>
#include <sys/stat.h>
#include <unistd.h>
#include <termios.h>
#include <math.h>
int lotteryRole()
{
	printf("\t\t\t双色球玩法\n");
	printf("\t\t\t开奖时间:每周二、四、日的21:30开奖\n");
	printf("\t\t\t玩法规则:6个红球+1个蓝球=1注（2元）\n");
	printf("\t\t\t*********************************************************\n");
	printf("\t\t\t*\t 等级\t   中奖条件     说明\t  奖金\t\t*\n");
	printf("\t\t\t*\t一等奖\t \033[31mO O O O O O\033[0m \033[34mO\033[0m \t6 + 1\t 10%%奖池 \t*\n");
	printf("\t\t\t*\t二等奖\t  \033[31mO O O O O O\033[0m  \t6\t 5%%奖池  \t*\n");
	printf("\t\t\t*\t三等奖\t  \033[31mO O O O O\033[0m \033[34mO\033[0m  \t5 + 1\t 3000  \t\t*\n");
	printf("\t\t\t*\t四等奖\t   \033[31mO O O O O\033[0m   \t5\t 200   \t\t*\n");
	printf("\t\t\t*\t四等奖\t   \033[31mO O O O\033[0m \033[34mO\033[0m   \t4 + 1\t 200   \t\t*\n");
	printf("\t\t\t*\t五等奖\t    \033[31mO O O O\033[0m    \t4\t 10    \t\t*\n");
	printf("\t\t\t*\t五等奖\t    \033[31mO O O\033[0m \033[34mO\033[0m    \t3 + 1\t 10    \t\t*\n");
	printf("\t\t\t*\t六等奖\t     \033[31mO O\033[0m \033[34mO\033[0m     \t2 + 1\t 5     \t\t*\n");
	printf("\t\t\t*\t六等奖\t      \033[31mO\033[0m \033[34mO\033[0m      \t1 + 1\t 5     \t\t*\n");
	printf("\t\t\t*\t六等奖\t       \033[31mO\033[0m       \t1\t 5     \t\t*\n");
	printf("\t\t\t*\t\t\t\t\t\t\t*\n");
	printf("\t\t\t*********************************************************\n");
	getchar();
	return 1;
}
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
			time_t t;
			struct tm *pt;
			time(&t);
			pt = localtime(&t);
			int thisYear = pt -> tm_year + 1900;
			if(thisYear - year < 18)//未满18周岁
			{
				printf("对不起！您未满18周岁\n根据《中华人民共和国未成年人保护法》相关规定，禁止未成年人购买彩票！\n");
				getchar();
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
		}
		return 1;
	}
}

/*******************处理密码********************/
int initPasswd(char *initialPasswd,int chance)
{
	char confirmPasswd[10] = "";
	printf("请再次输入密码:");
	scanf("%s",confirmPasswd);
	if(0 == strcmp(initialPasswd,confirmPasswd))
	{
		return 1;
	}
	else
	{
		if(chance == 1)
		{
			return 0;
		}
		printf("两次不一致！还有%d次机会。\n",--chance);
		return initPasswd(initialPasswd,chance);
	}
}
int getCurrentMaxId(BuyerLink *buyerHead)
{
	if(NULL == buyerHead)
	{
		printf(BUYER_HEAD_IS_NULL);
		return 0;
	}
	int maxId = 0;
	buyerHead = buyerHead -> next;
	while(NULL != buyerHead)
	{
		++maxId;
		buyerHead = buyerHead -> next;
	}
	return maxId;
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
	if(0 == strcmp(name,"admin") || 0 == strcmp(name,"notary"))
	{
		printf("该用户名已被注册！\n");
		return 0;
	}
	else
	{
		if(NULL != getPreNodePoint(buyerHead,name))
		{
			printf("该用户名已被注册！\n");
			return 0;
		}
		strcpy(buyer.name,name);
	}

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
	char initialPasswd[10] = "";
	printf("请输入密码:");
	scanf("%s",initialPasswd);
	if(0 == initPasswd(initialPasswd,3))
	{
		printf("注册失败!\n");
		return 0;
	}
	strcpy(buyer.passwd,initialPasswd);
	printf("密保问题：您最喜欢的水果是:\n");
	char fruit[20] = "";
	scanf("%s",fruit);
	/**************初始化id*账户余额*flag*state*************/
	buyer.id = getCurrentMaxId(buyerHead) + 1;
	buyer.balance = 0.00;
	buyer.flag = 0;
	strcpy(buyer.state,"激活");
	strcpy(buyer.question,fruit);
	/******************后插彩民节点********************/
	if(0 == insertAfterBuyerLink(buyerHead,&buyer))
	{
		printf("注册失败！\n");
		return 0;
	}
	printf("同意遵循彩票管理系统的相关协议！\n");
	getchar();
	getchar();
	saveData(buyerHead);
	printf("注册成功！\n");
	return 1;
}
/******************登录************************/
int loginSystem(BuyerLink *buyerHead,PubLink *pubHead,BuyLink *buyHead)
{
	char name[20] = "";
	char passwd[10] = "";
	printf("请输入用户名:");
	scanf("%s",name);
	if(0 == strcmp("admin",name))
	{
		printf("请输入密码:");
		getchar();
		getPassword(passwd);
		if(0 == strcmp("admin",passwd))
		{
			adminMenuControl(buyerHead,pubHead,buyHead);	//进入管理员菜单界面
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
		getchar();
		getPassword(passwd);
		if(0 == strcmp("notary",passwd))
		{
			notaryMenuControl(buyerHead,pubHead,buyHead);	//进入公正员界面
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
			printf("您输入的账户名不存在！\n");
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
			getchar();
			getPassword(passwd);
			if(0 == strcmp(passwd,pre -> next ->data.passwd))
			{
				if(1 == checkVerificationCode())
				{
					buyerMenuControl(buyerHead,name,pubHead,buyHead);//进入彩民菜单界面
					return 1;
				}
				else
				{
					printf("验证码输入错误！\n");

					return 0;
				}
			}
			else
			{
				printf("你输入的密码有误！\n");
				return 0;
			}
		}
	}
}
int checkVerificationCode()
{
	srand(time(NULL));
	char codeArray[] = "ABCDEFGHIGKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
	char code[5] = "";
	int i = 0,j = 0;
	int num[4] = {0};
	for(i = 0;i < 4;++i)
	{
		num[i] = rand() % 4;
		for(j = 0;j < i;++j)
		{
			if(num[i] == num[j])
			{
				--i;
				break;
			}
		}
	}
	code[num[0]] = codeArray[rand() % 26];
	code[num[1]] = codeArray[rand() % 26 + 26];
	code[num[2]] = codeArray[rand() % 10 + 52];
	code[num[3]] = codeArray[rand() % 10 + 52];
	code[4] = '\0';
	printf("验证码:%s\n",code);
	char codeUserInput[5] = "";
	printf("请输入验证码:");
	scanf("%s",codeUserInput);
	if(0 == strcmp(codeUserInput,code))
	{
		return 1;
	}
	else
	{
		return 0;
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
		printf("\033[7m账户ID    唯一帐户名       个人注册身份证号码        注册手机号码      账户余额\033[0m\n");
		printf("%07d%12s%26s%19s%14.2lf\n",\
				buyer.id,\
				buyer.name,\
				buyer.cardId,\
				buyer.telNum,\
				buyer.balance);
		getchar();
		return 1;
	}
	else
	{
		printf("对不起您的账号被冻结，请联系管理员！\n");
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
		printf("充值%.2lf元成功！\n",charge);
		getchar();
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
		if(1 == identifyPasswd(pre -> data.passwd,chance,name))
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
					saveData(buyerHead);
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
			pre -> data.flag = 1;
			printf("%d次机会用完,冻结！\n",chance);
			saveData(buyerHead);
			return 0;
		}
	}
	else
	{
		printf("对不起您的账号被冻结，请联系管理员！\n");
		return 0;
	}
}

int identifyPasswd(char *passwd,int chance,char *name)
{
	char inputPasswd[10] = "";
	printf("请输入%s密码:",name);
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
		return identifyPasswd(passwd,chance,name);
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
	if(1 == identifyPasswd(pre -> next -> data.passwd,3,name))
	{
		printf("您确定要注销账户吗？注销后可联系管理员找回帐号。\n");
		printf("「确认」回车     「取消」ESC：");
		char ch = getchar();
	
		if(ch == '\n')
		{
			pre -> next -> data.flag = 1;
			strcpy(pre -> next -> data.state,"冻结");
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
	else
	{
		printf("验证%s密码不正确，不允许注销!\n",name);
		getchar();
		return 0;
	}
}


int printAllBuyerMessage(BuyerLink *buyerHead)
{
	if(NULL == buyerHead)
	{
		printf(BUYER_HEAD_IS_NULL);
		return 0;
	}
	printf("\033[7m账户ID    唯一帐户名       个人注册身份证号码        注册手机号码      账户余额     账户状态\033[0m\n");
	buyerHead = buyerHead -> next;
	while(NULL != buyerHead)
	{
		if(1 == buyerHead -> data.flag)
		{
			printf("\033[7m%07d%12s%26s%19s%14.2lf%16s\033[0m\n",\
					buyerHead -> data.id,\
					buyerHead -> data.name,\
					buyerHead -> data.cardId,\
					buyerHead -> data.telNum,\
					buyerHead -> data.balance,\
					buyerHead -> data.state);				
		}
		else
		{
			printf("%07d%12s%26s%19s%14.2lf%16s\n",\
					buyerHead -> data.id,\
					buyerHead -> data.name,\
					buyerHead -> data.cardId,\
					buyerHead -> data.telNum,\
					buyerHead -> data.balance,\
					buyerHead -> data.state);
		}
		buyerHead = buyerHead -> next;
	}
	getchar();
	return 1;
}
int prizePoolAmount(PubLink *pubHead)
{
	if(NULL == pubHead)
	{
		printf(PUB_HEAD_IS_NULL);
		return 0;
	}
	PubLink *lastPubNodePoint = getLastPubNodePoint(pubHead);
	printf(">1.查看奖池金额\n");
	printf(">2.设置奖池金额\n");
	printf("选择:");
	int choose = 0;
	scanf("%d",&choose);
	if(1 == choose)
	{
		printf("目前奖池金额为:%.2lf\n",lastPubNodePoint -> data.totalMoney);
		getchar();
		getchar();
		return 1;
	}
	else if(2 == choose)
	{
		printf("请输入奖池金额:");
		double poolMoney = 0.00;
		scanf("%lf",&poolMoney);
		if(getchar() != '\n')
		{
			while(getchar() != '\n');
			printf("格式有误！\n");
			return 0;
		}
		if(poolMoney < 0)
		{
			printf("金额不能为负！\n");
			return 0;
		}
		lastPubNodePoint -> data.totalMoney = poolMoney;
		savePubData(pubHead);
		printf("奖池目前的金额是:%.2lf",lastPubNodePoint -> data.totalMoney);
		getchar();
		return 1;
	}
	else
	{
		printf("error\n");
		return 0;
	}
}

int publishLottery(PubLink *pubHead)
{
	if(NULL == pubHead)
	{
		printf("PUB_HEAD_IS_NULL");
		return 0;
	}
	if(0 == pubHead -> data.state)
	{
		printf("彩票还没有获得发行授权，请公证员授权！\n");
		return 0;
	}
	else
	{
		PubLink *last = getLastPubNodePoint(pubHead);
		if(0 == last -> data.state)
		{
			printf("上期没有开奖，无法再发行新期彩票！\n");
			return 0;
		}
		else
		{
			Pub pub;
			memset(&pub,0,sizeof(Pub));
			pub.issue = last -> data.issue + 1;
			pub.price = 2.00;
			int i = 0;
			for(i = 0;i < 7;++i)
			{
				pub.num[i] = 0;
			}
			pub.state = 0;
			strcpy(pub.strState,"未开奖");
			pub.sellCount = 0;
			pub.totalMoney = last -> data.totalMoney;
			insertAfterPubLink(pubHead,&pub);
			printf("第%d期双色球发行成功!\n",pub.issue);
			getchar();
			return 1;
		}
	}
}
int printPubRecord(PubLink *pubHead)
{
	if(NULL == pubHead)
	{
		printf(PUB_HEAD_IS_NULL);
		return 0;
	}
	printf("发行记录：\n");
	printf("发行期号\t中奖号码\t\t每注单价\t卖出注数\t奖池金额\t开奖状态\n");
	pubHead = pubHead -> next;
	Pub pub;
	memset(&pub,0,sizeof(Pub));
	while(NULL != pubHead)
	{
		pub = pubHead -> data;
		printf("%08d\t\033[31m%02d %02d %02d %02d %02d %02d \033[0m\033[34m%02d\033[0m\t%.2lf￥\t\t%08d\t%.2lf\t\t%s\n",\
		pub.issue,\
		pub.num[0],pub.num[1],pub.num[2],pub.num[3],pub.num[4],pub.num[5],pub.num[6],\
		pub.price,\
		pub.sellCount,\
		pub.totalMoney,\
		pub.strState);
		pubHead = pubHead -> next;
		memset(&pub,0,sizeof(Pub));
	}
	getchar();
	return 1;
}
int sortBuyerMessage(BuyerLink *buyerHead)
{
	if(NULL == buyerHead)
	{
		printf(BUYER_HEAD_IS_NULL);
		return 0;
	}
	printf("1.按用户名排序\n");
	printf("2.按id排序\n");
	printf("3.按余额排序\n");
	printf("选择:");
	int choose = 0;
	scanf("%d",&choose);
	if(getchar() != '\n')
	{
		printf("格式有误！\n");
		return 0;
	}
	switch(choose)
	{
		case 1://按用户名排序
			if(0 == sortBuyerByName(buyerHead))
			{
				return 0;
			}
			break;
		case 2://按id排序
			if(0 == sortBuyerById(buyerHead))
			{
				return 0;
			}
			break;
		case 3://按于余额排序
			if(0 == sortBuyerByBalance(buyerHead))
			{
				return 0;
			}
			break;
		default:
			printf("输入有误！\n");
			return 0;
	}
	printAllBuyerMessage(buyerHead);
	return 1;
}

int selectBuyer(BuyerLink *buyerHead)
{
	if(NULL == buyerHead)
	{
		printf(BUYER_HEAD_IS_NULL);
		return 0;
	}
	printf(">1.按账户名查寻\n");
	printf(">2.按账户ID查寻\n");
	printf(">3.按账户余额查寻\n");
	printf("选择:");
	int choose = 0;
	scanf("%d",&choose);
	if(getchar() != '\n')
	{
		while(getchar() != '\n');
		printf("格式错误！\n");
		return 0;
	}
	switch(choose)
	{
		case 1:
			if(0 == printBuyerMessageByName(buyerHead))
			{
				return 0;
			}
			break;
		case 2:
			if(0 == printBuyerMessageById(buyerHead))
			{
				return 0;
			}
			break;
		case 3:
			if(0 == printBuyerMessageByBalance(buyerHead))
			{
				return 0;
			}
			break;
		default:
			printf("输入选择有误！\n");
			return 0;
	}
	return 1;
}
int printBuyerMessageByName(BuyerLink *buyHead)
{
	if(NULL == buyHead)
	{
		printf(BUYER_HEAD_IS_NULL);
		return 0;
	}
	printf("请输入账户名:");
	char buyerName[20] = "";
	scanf("%s",buyerName);
	BuyerLink *cursor = buyHead ->next;
	Buyer buyer;
	memset(&buyer,0,sizeof(Buyer));
	printf("\033[7m账户ID    唯一帐户名       个人注册身份证号码        注册手机号码      账户余额\033[0m\n");
	while(NULL != cursor)
	{
		buyer = cursor -> data;
		if(0 == strcmp(buyerName,buyer.name))
		{
			printf("%07d%12s%26s%19s%14.2lf\n",\
				buyer.id,\
				buyer.name,\
				buyer.cardId,\
				buyer.telNum,\
				buyer.balance);
			break;
		}
		memset(&buyer,0,sizeof(Buyer));
		cursor = cursor -> next;
	}
	getchar();
	getchar();
	return 1;
}
int printBuyerMessageById(BuyerLink *buyerHead)
{
	if(NULL == buyerHead)
	{
		printf(BUYER_HEAD_IS_NULL);
		return 0;
	}
	printf(">1.按ID查询\n");
	printf(">2.按ID区间查询\n");
	printf("选择:");
	int choose = 0;
	scanf("%d",&choose);
	if(getchar() != '\n')
	{
		while(getchar() != '\n');
		printf("格式有误！\n");
		return 0;
	}
	if(1 == choose)
	{
		printf("请输入账户Id:");
		int buyerId = 0;
		scanf("%d",&buyerId);
		if(getchar() != '\n')
		{
			while(getchar() != '\n');
			printf("格式有误！\n");
			return 0;
		}
		BuyerLink *cursor = buyerHead -> next;
		Buyer buyer;
		memset(&buyer,0,sizeof(Buyer));
		printf("\033[7m账户ID    唯一帐户名       个人注册身份证号码        注册手机号码      账户余额\033[0m\n");
		while(NULL != cursor)
		{
			buyer = cursor -> data;
			if(buyerId == buyer.id)
			{
				printf("%07d%12s%26s%19s%14.2lf\n",\
				buyer.id,\
				buyer.name,\
				buyer.cardId,\
				buyer.telNum,\
				buyer.balance);
				break;
			}
			memset(&buyer,0,sizeof(Buyer));
			cursor = cursor -> next;
		}
		getchar();
		return 1;
	}
	else if(2 == choose)
	{
		int beginId = 0;
		int endId = 0;
		printf("请输入起始ID:");
		scanf("%d",&beginId);
		printf("请输入终止ID:");
		scanf("%d",&endId);
		BuyerLink *cursor = buyerHead -> next;
		Buyer buyer;
		memset(&buyer,0,sizeof(Buyer));
		printf("\033[7m账户ID    唯一帐户名       个人注册身份证号码        注册手机号码      账户余额\033[0m\n");
		while(NULL != cursor)
		{
			buyer = cursor -> data;
			if(buyer.id >= beginId && buyer.id <= endId)
			{
				printf("%07d%12s%26s%19s%14.2lf\n",\
				buyer.id,\
				buyer.name,\
				buyer.cardId,\
				buyer.telNum,\
				buyer.balance);				
			}
			memset(&buyer,0,sizeof(Buyer));
			cursor = cursor -> next;
		}
		getchar();
		return 1;
	}
	else
	{
		printf("选择有误!\n");
		return 0;
	}
}
int printBuyerMessageByBalance(BuyerLink *buyerHead)
{
	if(NULL == buyerHead)
	{
		printf(BUYER_HEAD_IS_NULL);
		return 0;
	}
	printf(">1.按余额查询\n");
	printf(">2.按余额区间查询\n");
	printf("选择:");
	int choose = 0;
	scanf("%d",&choose);
	if(1 == choose)
	{
		printf("请输入余额数值：");
		double buyerBalance = 0.00;
		scanf("%lf",&buyerBalance);
		BuyerLink *cursor = buyerHead -> next;
		Buyer buyer;
		memset(&buyer,0,sizeof(Buyer));
		printf("\033[7m账户ID    唯一帐户名       个人注册身份证号码        注册手机号码      账户余额\033[0m\n");
		while(NULL != cursor)
		{
			buyer = cursor -> data;
			if(buyerBalance == buyer.balance)
			{
				printf("%07d%12s%26s%19s%14.2lf\n",\
				buyer.id,\
				buyer.name,\
				buyer.cardId,\
				buyer.telNum,\
				buyer.balance);				
			}
			memset(&buyer,0,sizeof(Buyer));
			cursor = cursor -> next;
		}
		getchar();
		getchar();
		return 1;
	}
	else if(2 == choose)
	{
		double balanceMin = 0.00;
		double balanceMax = 0.00;
		printf("请输入余额最小值:");
		scanf("%lf",&balanceMin);
		printf("请输入余额最大值:");
		scanf("%lf",&balanceMax);
		BuyerLink *cursor = buyerHead -> next;
		Buyer buyer;
		memset(&buyer,0,sizeof(Buyer));
		printf("\033[7m账户ID    唯一帐户名       个人注册身份证号码        注册手机号码      账户余额\033[0m\n");
		while(NULL != cursor)
		{
			buyer = cursor -> data;
			if(buyer.balance >= balanceMin && buyer.balance <= balanceMax)
			{	
				printf("%07d%12s%26s%19s%14.2lf\n",\
				buyer.id,\
				buyer.name,\
				buyer.cardId,\
				buyer.telNum,\
				buyer.balance);
			}
			memset(&buyer,0,sizeof(Buyer));
			cursor = cursor -> next;
		}
		getchar();
		getchar();
		return 1;
	}
	else
	{
		printf("选择有误！\n");
		return 0;
	}
}

int authorization(PubLink *pubHead)
{
	if(NULL == pubHead)
	{
		printf(PUB_HEAD_IS_NULL);
		return 0;
	}
	if(1 == pubHead -> data.state)
	{
		printf("彩票已经授权发行，您要撤回权限吗?\n");
		printf("【确定】回车  【取消】ESC :");
		char ch = 0;
		scanf("%c",&ch);
		if(ch == '\n')
		{
			pubHead -> data.state = 0;
			savePubData(pubHead);
			printf("撤销授权成功！\n");
			return 1;
		}
		else if(ch == 27)
		{
			printf("取消撤销权限成功!\n");
			return 1;
		}
		else
		{
			printf("error！\n");
			return 0;
		}
	}
	printf("是否授权发行彩票？\n");
	printf("【授权】Y/y    【不授权】N/n:");
	char ch = getchar();
	if(ch == 'Y' || ch == 'y')
	{
		pubHead -> data.state = 1;
		savePubData(pubHead);
		printf("授权成功,管理员可以发行彩票！\n");
		return 1;
	}
	else if(ch == 'N' || ch == 'n')
	{
		printf("取消授权成功！\n");
		return 0;
	}
	else
	{
		printf("error\n");
		return 0;
	}
}

int drawLottery(BuyerLink *buyerHead,PubLink *pubHead,BuyLink *buyHead)
{
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
	if(NULL == buyHead)
	{
		printf(BUY_HEAD_IS_NULL);
		return 0;
	}
	if(pubHead -> data.state == 0)
	{
		printf("彩票没有获得发行权限，无法开奖，请公正员先授权！\n");
		getchar();
		return 0;
	}
	PubLink *lastPubNode = getLastPubNodePoint(pubHead);
	if(lastPubNode -> data.issue == 0)
	{
		printf("管理员还没有发行彩票，无法开奖！\n");
		return 0;
	}
	if(lastPubNode -> data.state == 1)
	{
		printf("本期彩票已经开奖，无需重复开奖!\n");
		return 0;
	}
	printf("【机器摇号】请按1  【人工定号】请按2：\n");
	int choose = 0;
	scanf("%d",&choose);
	if(getchar() != '\n')
	{
		while(getchar() != '\n');
		printf("格式有误！\n");
		return 0;
	}
	int num[7] = {0};
	if(1 == choose)
	{
		if(1 == machineCreate(num))
		{
			printf("机器摇号完成！\n");
			printf("出球号码是:\033[31m%02d %02d %02d %02d %02d %02d\033[0m \033[34m%02d\033[0m\n",\
			num[0],\
			num[1],\
			num[2],\
			num[3],\
			num[4],\
			num[5],\
			num[6]
			);
		}
	}
	else if(2 == choose)
	{	
		if(1 == notaryCreate(num))
		{
			printf("人工摇号成功！\n");
			printf("出球号码是:\033[31m%02d %02d %02d %02d %02d %02d\033[0m \033[34m%02d\033[0m\n",\
			num[0],\
			num[1],\
			num[2],\
			num[3],\
			num[4],\
			num[5],\
			num[6]
			);
		}
		else
		{
			printf("手动摇号有误!\n");
			return 0;
		}
	}
	else
	{
		printf("选择有误！\n");
		return 0;
	}
	printf("公正员确定开奖？\n");
	printf("【确定】回车  【取消】ESC:");
	char ch = getchar();
	if(ch == '\n')
	{
		PubLink *last = getLastPubNodePoint(pubHead);
		last -> data.num[0] = num[0];
		last -> data.num[1] = num[1];
		last -> data.num[2] = num[2];
		last -> data.num[3] = num[3];
		last -> data.num[4] = num[4];
		last -> data.num[5] = num[5];
		last -> data.num[6] = num[6];
		last -> data.state = 1;
		strcpy(last -> data.strState,"已开奖");
		savePubData(pubHead);
		printf("开奖成功！\n");
		printf("第%d期双色球开奖号码是:\033[31m%02d %02d %02d %02d %02d %02d\033[0m \033[34m%02d\033[0m\n",\
		last -> data.issue,\
		last -> data.num[0],\
		last -> data.num[1],\
		last -> data.num[2],\
		last -> data.num[3],\
		last -> data.num[4],\
		last -> data.num[5],\
		last -> data.num[6]
		);
		savePubData(pubHead);
		awardBuyer(pubHead,buyHead,buyerHead);//发奖金
		getchar();
		return 1;
	}
	else if(ch == 27)
	{
		printf("取消开奖成功！\n");
		return 0;
	}
	else
	{
		printf("error\n");
		return 0;
	}
}
int machineCreate(int *num)
{
	srand(time(NULL));
	int i = 0;
	for(i = 0;i < 6;++i)
	{
		num[i] = rand() % 33 +1;	
	}
	num[6] = rand() % 16 + 1;
	int j = 0;
	for(i = 0;i < 5;++i)
	{
		for(j = 0;j < 5;++j)
		{
			if(num[j] > num[j + 1])
			{
				int temp = num[j];
				num[j] = num[j + 1];
				num[j + 1] = temp;
			}
		}
	}
	return 1;
}
int notaryCreate(int *num)
{
	int i = 0;
	for(i = 0;i < 6;++i)
	{
		printf("请输入第%d个红球出球号码(1 ~ 33):",i + 1);
		scanf("%d",&num[i]);
		if(getchar() != '\n')
		{
			while(getchar() != '\n');
			printf("格式有误！\n");
			return 0;
		}
		if(num[i] < 1 || num[i] > 33)
		{
			printf("请输入1 ～ 33的整数！\n");
			return 0;
		}
	}
	printf("请输入篮球出球号码(1 ~ 16):");
	scanf("%d",&num[6]);
	if(getchar() != '\n')
	{
		while(getchar() != '\n');
		printf("格式有误！\n");
		return 0;
	}
	if(num[i] < 1 || num[i] > 16)
	{
		printf("请输入1 ～ 16的整数！\n");
		return 0;
	}
	return 1;
}

int awardBuyer(PubLink *pubHead,BuyLink *buyHead,BuyerLink *buyerHead)
{
	if(NULL == pubHead)
	{
		printf(PUB_HEAD_IS_NULL);
		return 0;
	}
	if(NULL == buyHead)
	{
		printf(BUY_HEAD_IS_NULL);
		return 0;
	}
	if(NULL == buyerHead)
	{
		printf(BUYER_HEAD_IS_NULL);
		return 0;
	}
	PubLink *lastPubNode = getLastPubNodePoint(pubHead);
	int issue = lastPubNode -> data.issue;
	int i = 0;
	int num[7] = {0};
	int level = 0;
	for(i = 0;i < 7;++i)
	{
		num[i] = lastPubNode -> data.num[i];	
	}
	BuyLink *cursor = getPreBuyNodePoint(buyHead,issue) -> next;
	if(NULL == cursor)
	{
		printf("目前还没有彩民购买本期彩票！\n");
		return 0;
	}
	printf("中奖信息公布:\n");
	printf("发行期号   彩票序列号    账户名   中奖等级    购买号码\t\t    购买注数    中奖金额\n");
	while(NULL != cursor)
	{
		BuyerLink *buyerNode = getPreNodePoint(buyerHead,cursor -> data.buyerData.name) -> next;
		if(buyerNode -> data.flag == 1)//帐号被冻结不能参加开奖
		{
			continue; 
		}
		level = getLevel(num,cursor -> data.buyNum);
		switch(level)
		{
			case 1://一等奖
				cursor -> data.money = lastPubNode -> data.totalMoney / 10  * cursor -> data.buyCount;
				buyerNode -> data.balance += cursor -> data.money;
				lastPubNode -> data.totalMoney -= cursor -> data.money;
				printAwardBuyerMessage(cursor,level);
				break;
			case 2://二等奖
				cursor -> data.money = lastPubNode -> data.totalMoney / 20 * cursor -> data.buyCount;
				buyerNode -> data.balance += cursor -> data.money;
				lastPubNode -> data.totalMoney -= cursor -> data.money;
				printAwardBuyerMessage(cursor,level);
				break;	
			case 3://三等奖
				cursor -> data.money = 3000 * cursor -> data.buyCount;
				buyerNode -> data.balance += cursor -> data.money;
				lastPubNode -> data.totalMoney -= cursor -> data.money;
				printAwardBuyerMessage(cursor,level);
				break;
			case 4://四等奖
				cursor -> data.money = 200 * cursor -> data.buyCount;
				buyerNode -> data.balance += cursor -> data.money;
				lastPubNode -> data.totalMoney -= cursor -> data.money;
				printAwardBuyerMessage(cursor,level);				
				break;
			case 5://五等奖
				cursor -> data.money = 10 * cursor -> data.buyCount;
				buyerNode -> data.balance += cursor -> data.money;
				lastPubNode -> data.totalMoney -= cursor -> data.money;
				printAwardBuyerMessage(cursor,level);
				break;
			case 6://六等奖
				cursor -> data.money = 5 * cursor -> data.buyCount;
				buyerNode -> data.balance += cursor -> data.money;
				lastPubNode -> data.totalMoney -= cursor -> data.money;
				printAwardBuyerMessage(cursor,level);
				break;
			case 0://没中奖
				break;
			default:
				printf("error\n");
				saveBuyData(buyHead);
				saveData(buyerHead);
				savePubData(pubHead);
				return 0;
		}
		cursor = cursor -> next;
	}
	saveBuyData(buyHead);
	saveData(buyerHead);
	savePubData(pubHead);
	return 1;
}
int printAwardBuyerMessage(BuyLink *cursor,int level)
{
	printf("%08d   %08d  %10s   %d           \033[31m%02d %02d %02d %02d %02d %02d\033[0m \033[34m%02d\033[0m  %d           %.2lf\n",\
	cursor -> data.issue,\
	cursor -> data.id,\
	cursor -> data.buyerData.name,\
	level,\
	cursor -> data.buyNum[0],\
	cursor -> data.buyNum[1],\
	cursor -> data.buyNum[2],\
	cursor -> data.buyNum[3],\
	cursor -> data.buyNum[4],\
	cursor -> data.buyNum[5],\
	cursor -> data.buyNum[6],\
	cursor -> data.buyCount,\
	cursor -> data.money);
	return 1;
}
int getLevel(int *pubNum,int *buyNum)
{
	int i = 0;
	int countRed = 0;
	if(pubNum[6] != buyNum[6])
	{
		for(i = 0;i < 6;++i)
		{
			if(pubNum[i] == buyNum[i])
			{
				++countRed;
			}
		}
		if(6 == countRed)
		{
			return 2;
		}
		else if(5 == countRed)
		{
			return 4;
		}
		else if(4 == countRed)
		{
			return 5;
		}
		else
		{
			return 0;
		}
	}
	else
	{
		for(i = 0;i < 6;++i)
		{
			if(pubNum[i] == buyNum[i])
			{
				++countRed;
			}
		}
		if(6 == countRed)
		{
			return 1;
		}
		else if(5 == countRed)
		{
			return 3;
		}
		else if(4 == countRed)
		{
			return 4;
		}
		else if(3 == countRed)
		{
			return 5;
		}
		else
		{
			return 6;
		}
	}
}


int buyLottery(BuyerLink *buyerHead,PubLink *pubHead,BuyLink *buyHead,char *name)
{
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
	if(NULL == buyHead)
	{
		printf(BUY_HEAD_IS_NULL);
		return 0;
	}
	PubLink *last = getLastPubNodePoint(pubHead);
	if(1 != last -> data.state && last -> data.issue > 0)
	{
		printf("「1.机选」「2.手选」:");
		int choose = 0;
		scanf("%d",&choose);
		if(getchar() != '\n')
		{
			printf("格式错误！\n");
			return 0;
		}
		if(1 == choose)
		{
			machineSelect(buyerHead,pubHead,buyHead,name);
			return 1;
		}
		else if(2 == choose)
		{
			if(0 == buyerSelect(buyerHead,pubHead,buyHead,name))
			{
				printf("手动选号失败！\n");
				return 0;
			}
			return 1;
		}
		else
		{
			printf("error\n");
			return 0;
		}
	}
	else
	{
		printf("新的一期彩票还没有发行，现在无法购买彩票！\n");
		return 0;		
	}
}

int machineSelect(BuyerLink *buyerHead,PubLink *pubHead,BuyLink *buyHead,char *name)
{
	int num[7] = {0};
	srand(time(NULL));
	int i = 0;
	for(i = 0;i < 6;++i)
	{
		num[i] = rand() % 33 + 1;
	}
	num[6] = rand() % 16 + 1;
	int j = 0;
	for(i = 0;i < 5;++i)
	{
		for(j = 0;j < 5 - i;++j)
		{
			if(num[j] > num[j + 1])
			{
				int temp = num[j];
				num[j] = num[j + 1];
				num[j + 1] = temp;
			}
		}
	}
	printf("机选号码为:\033[31m%02d %02d %02d %02d %02d %02d\033[0m \033[34m%02d\033[0m\n",\
			num[0],num[1],num[2],num[3],num[4],num[5],num[6]);
	int buyCount = 0;
	printf("请输入您要购买本张彩票的注数(单张彩票至多购买5注):");
	scanf("%d",&buyCount);
	if(getchar() != '\n')
	{
		while(getchar() != '\n');
		printf("格式错误！购买失败！\n");
		return 0;
	}
	if(buyCount > 5 || buyCount < 0)
	{
		printf("输入的注数有误！购买失败！\n");
		return 0;
	}
	else if(0 == buyCount)
	{
		printf("取消购买成功，欢迎下次购买！\n");
		return 1;
	}
	else
	{
		BuyerLink *buyerNode = getPreNodePoint(buyerHead,name) -> next;
		if(buyerNode -> data.balance - buyCount * 2 < 0)
		{
			printf("余额不足，购买失败，请尽快充值!\n");
			return 0;
		}
		Buy buy;
		memset(&buy,0,sizeof(Buy));
		buy.issue = getLastPubNodePoint(pubHead) -> data.issue;
		buy.id = getLastBuyNodePoint(buyHead) -> data.id + 1;
		int i = 0;
		for(i = 0;i < 7;++i)
		{
			buy.buyNum[i] = num[i];
		}
		buy.flag = 0;
		strcpy(buy.strFlag,"机选");
		buy.buyCount = buyCount;
		buy.buyerData = getPreNodePoint(buyerHead,name) -> next -> data;
		buy.state = 0;
		strcpy(buy.strState,"未兑奖");
		buy.money = 0.00;
		insertAfterBuyLink(buyHead,&buy);
		saveBuyData(buyHead);
		buyerNode -> data.balance -= buyCount * 2;//彩民扣钱
		saveData(buyerHead);
		printf("机选成功！\n");
		PubLink *lastPubNodePoint = getLastPubNodePoint(pubHead);
		lastPubNodePoint -> data.sellCount += buyCount;
		lastPubNodePoint -> data.totalMoney += buyCount * 2;//奖池收钱
		savePubData(pubHead);
		printf("机选购买彩票成功!\n");
		return 1;
	}
}
int buyerSelect(BuyerLink *buyerHead,PubLink *pubHead,BuyLink *buyHead,char *name)
{
	int num[7] = {0};
	int i = 0;
	printf("红球6个号码为1 ~ 33，蓝球1个号码为1 ~ 16\n");
	for(i = 0;i < 6;++i)
	{
		printf("请输入第%d个红球号码:",i + 1);
		scanf("%d",&num[i]);
		if(getchar() != '\n')
		{
			while(getchar() != '\n');
			printf("格式错误！\n");
			return 0;
		}
		if(num[i] > 33 || num[i] < 1)
		{
			return 0;
		}
	}
	printf("请输入蓝球号码:");
	scanf("%d",&num[6]);
	if(getchar() != '\n')
	{
		while(getchar() != '\n');
		printf("格式错误！\n");
		return 0;
	}
	if(num[6] > 17 || num[6] < 1)
	{
		return 0;
	}
	int j = 0;
	for(i = 0;i < 5;++i)
	{
		for(j = 0;j < 5 - i;++j)
		{
			if(num[j] > num[j + 1])
			{
				int temp = num[j];
				num[j] = num[j + 1];
				num[j + 1] = temp;
			}
		}
	}
	printf("您选择的号码为:\033[31m%02d %02d %02d %02d %02d %02d\033[0m \033[34m%02d\033[0m\n",\
			num[0],num[1],num[2],num[3],num[4],num[5],num[6]);
	int buyCount = 0;
	printf("请输入您要购买本张彩票的注数(单张彩票至多购买5注):");
	scanf("%d",&buyCount);
	if(getchar() != '\n')
	{
		while(getchar() != '\n');
		printf("格式错误！购买失败！\n");
		return 0;
	}
	if(buyCount > 5 || buyCount < 0)
	{
		printf("输入的注数有误！购买失败！\n");
		return 0;
	}
	else if(0 == buyCount)
	{
		printf("取消购买成功，欢迎下次购买！\n");
		return 1;
	}
	else
	{
		BuyerLink *buyerNode = getPreNodePoint(buyerHead,name) -> next;
		if(buyerNode -> data.balance - buyCount * 2 < 0)
		{
			printf("余额不足，购买失败，请尽快充值!\n");
			return 0;
		}
		Buy buy;
		memset(&buy,0,sizeof(Buy));
		buy.issue = getLastPubNodePoint(pubHead) -> data.issue;
		buy.id = getLastBuyNodePoint(buyHead) -> data.id + 1;
		int i = 0;
		for(i = 0;i < 7;++i)
		{
			buy.buyNum[i] = num[i];
		}
		buy.flag = 0;
		strcpy(buy.strFlag,"手选");
		buy.buyCount = buyCount;
		buy.buyerData = getPreNodePoint(buyerHead,name) -> next -> data;
		buy.state = 0; 
		strcpy(buy.strState,"未兑奖");
		buy.money = 0.00;
		insertAfterBuyLink(buyHead,&buy);
		saveBuyData(buyHead);
		buyerNode -> data.balance -= buyCount * 2;
		saveData(buyerHead);
		printf("手动选号成功！\n");
		PubLink *lastPubNodePoint = getLastPubNodePoint(pubHead);
		lastPubNodePoint -> data.sellCount += buyCount;
		savePubData(pubHead);
		printf("手动选好购买成功!\n");
		return 1;
	}
}
int printBuyRecord(BuyerLink *buyerHead,PubLink *pubHead,BuyLink *buyHead,char *name)
{
	buyHead = buyHead -> next;
	printf("购买期号 彩票编号 购买号码\t\t开奖号码\t\t选号方式 购买注数 获奖金额    开奖状态 兑奖状态\n");	
	while(NULL !=buyHead)
	{		
		if(0 == strcmp(name,buyHead -> data.buyerData.name))
		{
			Pub pub = getPrePubNodePoint(pubHead,buyHead -> data.issue) -> next -> data;
			printf("%08d %08d \033[31m%02d %02d %02d %02d %02d %02d\033[0m \033[34m%02d\033[0m  \033[31m%02d %02d %02d %02d %02d %02d\033[0m \033[34m%02d\033[0m    %s\t %d\t  %08.2lf    %s   %s\n",\
					buyHead -> data.issue,\
					buyHead -> data.id,\
					buyHead -> data.buyNum[0],\
					buyHead -> data.buyNum[1],\
					buyHead -> data.buyNum[2],\
					buyHead -> data.buyNum[3],\
					buyHead -> data.buyNum[4],\
					buyHead -> data.buyNum[5],\
					buyHead -> data.buyNum[6],\
					pub.num[0],\
					pub.num[1],\
					pub.num[2],\
					pub.num[3],\
					pub.num[4],\
					pub.num[5],\
					pub.num[6],\
					buyHead -> data.strFlag,\
					buyHead -> data.buyCount,\
					buyHead -> data.money,\
					pub.strState,\
					buyHead -> data.strState);
		}
		buyHead = buyHead -> next;
	}
	getchar();
	return 1;
}
int getch()
{
        struct termios tm, tm_old;
        int fd = STDIN_FILENO, c;
        if(tcgetattr(fd, &tm) < 0)	//获取终端属性
        {
            return -1;
        }
        tm_old = tm;
        cfmakeraw(&tm);	//就是将终端设置为原始模式，该模式下所有的输入数据以字节为单位被处理。
        				//在原始模式下，终端是不可回显的，而且所有特定的终端输入/输出模式不可用。
        if(tcsetattr(fd, TCSANOW, &tm) < 0)	//不等数据传输完毕就立即改变属性   成功返回0   失败-1
        {
            return -1;
        }
        c = fgetc(stdin);//
        if(tcsetattr(fd, TCSANOW, &tm_old) < 0)
        {
            return -1;
        }
        return c;
}

void getPassword(char *pcPWD)
{
	int ch=0;
	int i=0;
	for(i=0;i<10;)
	{
		ch=getch();
		if(ch==-1)
		{
			continue;
		}
		if((ch == 127 || ch == 8) && i>0)
		{
			putchar('\b');
			putchar(' ');
			putchar('\b');
			i--;
		}
		else if(ch==10 || ch == 13)
		{
			pcPWD[i]=0;
			putchar('\n');
			return;
		}
		else if(i==0&&(ch==127 ||ch == 8))
		{
			printf("\a");
		}
		else if(i<9)
		{
			pcPWD[i]=(char)ch;
			putchar('*');
			i++;
		}
		else
		{
			printf("\a");
		}
	}
}

int rechargeBuyerAccount(BuyerLink *buyerHead)
{
	if(NULL == buyerHead)
	{
		printf(BUYER_HEAD_IS_NULL);
		return 0;
	}
	printf("请输入账户名:");
	char name[20] = "";
	scanf("%s",name);
	rechargeAccount(buyerHead,name);
	return 1;
}
int repairBuyerAccount(BuyerLink *buyerHead)
{
	if(NULL == buyerHead)
	{
		printf(BUYER_HEAD_IS_NULL);
		return 0;
	}
	printf("请输入账户名:");
	char name[20] = "";
	scanf("%s",name);
	BuyerLink *buyerPreNode = getPreNodePoint(buyerHead,name);
	if(NULL == buyerPreNode)
	{
		printf("您输入的账户名不存在！\n");
		return 0;
	}
	if(buyerPreNode -> next -> data.flag == 0)
	{
		printf("您输入的账户没有被冻结不需要激活！\n");
		return 0;
	}
	buyerPreNode -> next -> data.flag = 0;
	saveData(buyerHead);
	printf("账户激活成功！\n");
	return 1;
}

int retrievalPasswd(BuyerLink *buyerHead)
{
	if(NULL == buyerHead)
	{
		printf(BUYER_HEAD_IS_NULL);
		return 0;
	}
	printf("请输入账户名:");
	char name[20] = "";
	scanf("%s",name);
	BuyerLink *buyerPreNode = getPreNodePoint(buyerHead,name);
	if(NULL == buyerPreNode)
	{
		printf("您输入的账户不存在！\n");
		return 0;
	}
	printf("您最喜欢的水果是:");
	char fruit[20] = "";
	scanf("%s",fruit);
	if(0 == strcmp(buyerPreNode -> next -> data.question,fruit))
	{
		char newPasswd1[10] = "";
		char newPasswd2[10] = "";
		printf("请输入新密码:");
		scanf("%s",newPasswd1);
		printf("请再次输入密码:");
		scanf("%s",newPasswd2);
		if(0 == strcmp(newPasswd1,newPasswd2))
		{
			strcpy(buyerPreNode -> next -> data.passwd,newPasswd2);
			saveData(buyerHead);
			printf("密码重置成功！\n");
			return 1;
		}
		else
		{
			printf("两次输入密码不一致，重置失败！\n");
			return 0;
		}
	}
	else
	{
		printf("密保问题回答错误，不允许重置密码！\n");
		return 0;
	}
}

/*int buyerComment(BuyerLink *buyerHead,char *name,ComLink *comHead)
{
	if(NULL == buyerHead)
	{
		printf(BUEYR_HEAD_IS_NULL);
		return 0;
	}
	if(NULL == comHead)
	{
		printf(COM_HEAD_IS_NULL);
		return 0;
	}
	printf(">1.看评论\n");
	printf(">2.写评论\n");
	printf("选择:");
	int choose == 0;
	scanf("%d",&choose);
	if(getchar() != '\n')
	{
		while(getchar() != '\n');
		printf("格式有误！\n");
		return 0;
	}
	if(1 == choose)
	{

	}
	else if(2 == choose)
	{

	}
	else
	{
		printf("error\n");
		return 0;
	}
		
}*/
int playGame(BuyerLink *buyerHead,char *name)
{
	system("clear");
	printf("\t\t\t\t>>>>>>玩的越多，赚的越多<<<<<<<<\n");
	printf("\t\t\t\t>\t1.汉诺塔游戏\n");
	printf("\t\t\t\t>\t2.猜数游戏\n\n");
	int choose = 0;
	printf("\t\t\t\t选择:");
	scanf("%d",&choose);
	if(getchar() != '\n')
	{
		while(getchar() != '\n');
		printf("格式有误！\n");
		return 0;
	}
	switch(choose)
	{
		case 1:
			hanoiGame(buyerHead,name);
			break;
		case 2:
			guessNumGame(buyerHead,name);
			break;
		default:
			printf("选择有误！\n");
			break;
	}
	return 1;
}

int guessNumGame(BuyerLink *buyerHead,char *name)
{
	system("clear");
	printf("\t\t\t\t***猜数游戏***\n\n");
	printf("\t\t\t\t游戏规则：\n");
	printf("\t\t\t\t根据提示输入猜测的数字，如果在5次之内猜中，奖励2元!\n");
	srand(time(NULL));
	int num = rand() % 100;
	int guessNum = 0;
	int i = 0;
	printf("\t\t\t\t请输入0 ～100内的整数：\n");
	for(i = 0;i < 5;++i)
	{
		printf("\t\t\t\t请输入：");
		scanf("%d",&guessNum);
		if(getchar() != '\n')
		{
			while(getchar() != '\n');
			printf("\t\t\t\t格式有误！\n");
			return 0;
		}
		if(guessNum == num)
		{
			printf("\t\t\t\t恭喜你猜对了!\n");
			BuyerLink *buyerPreNode = getPreNodePoint(buyerHead,name);
			buyerPreNode -> next -> data.balance += 2;
			printf("\t\t\t\t奖金已经发放到您的账户中！");
			saveData(buyerHead);
			return 1;
		}
		else if(guessNum < num)
		{
			printf("\t\t\t\t小了！\n");
		}
		else
		{
			printf("\t\t\t\t大了！\n");
		}
	}
	printf("\t\t\t\t真遗憾，没有猜中！\n");
	printf("\t\t\t\t正确答案是:%d\n",num);
	getchar();
	return 1;
}

int hanoiGame(BuyerLink *buyerHead,char *name)
{
	system("clear");
	printf("\t\t\t\t***汉塔诺游戏***\n\n");
	printf("\t\t\t\t游戏规则：\n");
	printf("\t\t\t\t计算机产生一个10以内的随机数作为汉诺塔的个数，\n\
	\t\t\t\t你能算出最少的移动步数吗？\n\
	\t\t\t\t输入正确答案，奖励10元!\n");
	srand(time(NULL));
	int num = rand() % 9 + 1;
	printf("\t\t\t\t%d个汉诺塔的最少移动步数是：",num);
	int answer = pow(2,num) - 1;
	int input = 0;
	scanf("%d",&input);
	if(getchar() != '\n')
	{
		while(getchar() != '\n');
		printf("\t\t\t\t格式有误！\n");
		return 0;
	}
	if(answer == input)
	{
		BuyerLink *buyerPreNode = getPreNodePoint(buyerHead,name);
		buyerPreNode -> next -> data.balance += 10;
		saveData(buyerHead);
		printf("\t\t\t\t恭喜你答对了，奖金已经发放到你的账户！\n");	
	}
	else
	{
		printf("\t\t\t\t真遗憾，没有答对！\n");
	}
	printf("\t\t\t\t移动过程是：\n");
	int count = 0;
	hanoi(num,1,2,3,&count);
	printf("\t\t\t\t%d个汉诺塔至少需要移动%d次!\n",num,count);
	getchar();	
	return 1;
}
void hanoi(int num,int p1,int p2,int p3,int *count)
{
	if(num == 1)
	{
		printf("\t\t\t\t盘子从 %d 柱移动到 %d 柱\n",p1,p3);
		++(*count);
	}
	else
	{
		hanoi(num - 1 ,p1,p3,p2,count);
		printf("\t\t\t\t盘子从 %d 柱移动到 %d 柱\n",p1,p3);
		++(*count);
		hanoi(num - 1,p2,p1,p3,count);
	}
}

int reviewNum(PubLink *pubHead)
{
	if(NULL == pubHead)
	{
		printf(PUB_HEAD_IS_NULL);
		return 0;
	}
	printf("yes0\n");
	int num[33] = {0};//统计出现次数
	int num_blue[16] = {0};
	PubLink *cursor = pubHead -> next;
	int count = 0;
	if(cursor == NULL)
	{
		printf("还没有开奖记录！\n");
		return 0;
	}
	while(NULL != cursor)
	{
		int i = 0;
		while(i < 6)
		{
			switch(cursor -> data.num[i])
			{
			printf("yes\n");
				case 1:
					++num[0];
					break;
				case 2:
					++num[1];
					break;
				case 3:
					++num[2];
					break;
				case 4:
					++num[3];
					break;
				case 5:
					++num[4];
					break;
				case 6:
					++num[5];
					break;
				case 7:
					++num[6];
					break;
				case 8:
					++num[7];
					break;
				case 9:
					++num[8];
					break;
				case 10:
					++num[9];
					break;
				case 11:
					++num[10];
					break;
				case 12:
					++num[11];
					break;
				case 13:
					++num[12];
					break;
				case 14:
					++num[13];
					break;
				case 15:
					++num[14];
					break;
				case 16:
					++num[15];
					break;
				case 17:
					++num[16];
					break;
				case 18:
					++num[17];
					break;
				case 19:
					++num[18];
					break;
				case 20:
					++num[19];
					break;
				case 21:
					++num[20];
					break;
				case 22:
					++num[21];
					break;
				case 23:
					++num[22];
					break;
				case 24:
					++num[23];
					break;
				case 25:
					++num[24];
					break;
				case 26:
					++num[25];
					break;
				case 27:
					++num[26];
					break;
				case 28:
					++num[27];
					break;
				case 29:
					++num[28];
					break;
				case 30:
					++num[29];
					break;
				case 31:
					++num[30];
					break;
				case 32:
					++num[31];
					break;
				case 33:
					++num[32];
					break;
				default:
					break;
			}
			++i;
		}
		switch(cursor -> data.num[6])
		{
				case 1:
					++num_blue[0];
					break;
				case 2:
					++num_blue[1];
					break;
				case 3:
					++num_blue[2];
					break;
				case 4:
					++num_blue[3];
					break;
				case 5:
					++num_blue[4];
					break;
				case 6:
					++num_blue[5];
					break;
				case 7:
					++num_blue[6];
					break;
				case 8:
					++num_blue[7];
					break;
				case 9:
					++num_blue[8];
					break;
				case 10:
					++num_blue[9];
					break;
				case 11:
					++num_blue[10];
					break;
				case 12:
					++num_blue[11];
					break;
				case 13:
					++num_blue[12];
					break;
				case 14:
					++num_blue[13];
					break;
				case 15:
					++num_blue[14];
					break;
				case 16:
					++num_blue[15];
					break;
				default:
					break;
		}
		++count;
	}
	int countRed = count * 6;
	int countBlue = count * 1;
	double centerRed[33] = {0};
	double centerBlue[16] = {0};
	int i = 0;
	for(i = 0;i < 33;++i)
	{
		centerRed[i] = (double)num[i] / countRed;
	}
	for(i = 0;i < 16;++i)
	{
		centerBlue[i] = (double)num_blue[i] / countBlue;
	}

	printf("\t红球走势：\n");
	for(i = 32;i >= 0;--i)
	{
		printf("\t%d|:%.2lf\n",i+1,centerRed[i]);
	}
	printf("蓝球走势：\n");
	for(i = 15;i >= 0;--i)
	{
		printf("\t%d||:%.2lf\n",i+1,centerBlue[i]);
	}
	return 1;
}
