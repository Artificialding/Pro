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
				printf("对不起！您未满18周岁\n根据《中华人民共和国未成年人保护法》相关规定，禁止未成年人购买彩票！\n");
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
	/**************初始化id*账户余额*flag*state*************/
	buyer.id = getCurrentMaxId(buyerHead) + 1;
	buyer.balance = 0.00;
	buyer.flag = 0;
	strcpy(buyer.state,"激活");
	/******************后插彩民节点********************/
	if(0 == insertAfterBuyerLink(buyerHead,&buyer))
	{
		printf("注册失败！\n");
		return 0;
	}
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
		scanf("%s",passwd);
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
		scanf("%s",passwd);
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
			scanf("%s",passwd);
			if(0 == strcmp(passwd,pre -> next ->data.passwd))
			{
				buyerMenuControl(buyerHead,name,pubHead,buyHead);//进入彩民菜单界面
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
		printf("\033[7m账户ID    唯一帐户名       个人注册身份证号码        注册手机号码      账户余额\033[0m\n");
		printf("%07d%12s%26s%19s%14.2lf\n",\
				buyer.id,\
				buyer.name,\
				buyer.cardId,\
				buyer.telNum,\
				buyer.balance);
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
		printf("对不起您的账号被冻结，请联系管理员！\n");
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
	return 1;
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
			printf("发行OK\n");
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
			sortBuyerByName(buyerHead);
			break;
		case 2://按id排序
			sortBuyerById(buyerHead);
			break;
		case 3://按于余额排序
			sortBuyerByBalance(buyerHead);
			break;
		default:
			printf("输入有误！\n");
			return 0;
	}
	printAllBuyerMessage(buyerHead);
	return 1;
}
int authorization(PubLink *pubHead)
{
	if(NULL == pubHead)
	{
		printf(PUB_HEAD_IS_NULL);
		return 0;
	}
	printf("是否授权发行彩票？\n");
	printf("「授权」Y/y    「不授权」N/n:");
	char ch = getchar();
	if(ch == 'Y' || ch == 'y')
	{
		pubHead -> data.state = 1;
		savePubData(pubHead);
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
	printf("「机器摇号」请按1  「人工定号」请按2：\n");
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
		int num[7] = {0};
		if(1 == machineCreate(pubHead,num))
		{
			printf("机器摇号完成！\n");
			printf("出球号码是:\033[31m%02d %02d %02d %02d %02d %02d \033[0m%02d\n",\
			num[0],\
			num[1],\
			num[2],\
			num[3],\
			num[4],\
			num[5],\
			num[6],\
			);
		}
	}
	else if(2 == choose)
	{
		
		if(1 == notaryCreate(pubHead))
		{
			printf("人工摇号成功！\n");
			printf("出球号码是:\033[31m%02d %02d %02d %02d %02d %02d \033[0m%02d\n",\
			num[0],\
			num[1],\
			num[2],\
			num[3],\
			num[4],\
			num[5],\
			num[6],\
			);
		}
	}
	else
	{
		printf("选择有误！\n");
		return 0;
	}
	printf("公正员确定开奖？\n");
	printf("「确定」回车  「取消」ESC:");
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
		strcpy(last -> data.strState,"开奖");
		savePubData(pubHead);
		printf("开奖成功！\n");
		savePubData(pubHead);
		awardBuyer(pubHead,buyHead);
		saveBuyData(buyHead);
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
int machineCreate(Pub *pub)
{
	int num[7] = {0};
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
	for(i = 0;i < 7;++i)
	{
		pub.num[i] = num[i];		
	}
	return 1;
}
int notaryCreate(Pub *pub)
{
	int i = 0;
	int num[7] = {0};
	for(i = 0;i < 6;++i)
	{
		printf("请输入第%d个红球出球号码(1 ~ 33):");
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

int awardBuyer(PubLink *pubHead,BuyLink *buyHead)
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
	PubLink *pub = getLastPubNodePoint(pubHead);
	int issue = pub -> data.issue;
	int i = 0;
	int num[7] = {0};
	int level = 0;
	for(i = 0;i < 7;++i)
	{
		num[i] = pub -> data.num[i];	
	}
	BuyLink *cursor = getProBuyNodePoint(buyHead,issue) -> next;
	if(NULL == cursor)
	{
		printf("目前还没有彩民购买彩票！\n");
		return 0;
	}
	Buy buy;
	memset(&buy,0,sizeof(Buy));
	while(NULL != cursor)
	{
		buy = cursor -> data;
		level = getLevel(num,buy.buyNum);
		printf("中奖信息公布:\n");
		switch(level)
		{
			case 1://一等奖
				buy.buyData.balance += 10000 * buy.buyCount;
				buy
				printAwardBuyerMessage(buy);
				break;
			case 2://二等奖
				buy.buyData.balance += 5000 * buy.buyCount;
				break;	
			case 3://三等奖
				buy.buyData.balance += 3000 * buy.buyCount;
				break;
			case 4://四等奖
				buy.buyData.balance += 200 * buy.buyCount;
				break;
			case 5://五等降
				buy.buyData.balance += 10 * buy.buyCount;
				break;
			case 6://六等奖
				buy.buyData.balance += 5 * buy.buyCount;
				break;
			case 0://没中奖
				buy.buyData.balance += 0;
			default:
				printf("error\n");
				return 0;
		}
	}
	return 1;
}
int printAwardBuyerMessage(Buy *buy)
{
		
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
			buyerSelect(buyerHead,pubHead,buyHead,name);
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
		buy.buyerData = getPreNodePoint(buyerHead,name) -> next ->data;
		printf("yes0\n");
		buy.state = 0;
		strcpy(buy.strState,"未兑奖");
		buy.money = 0.00;
		insertAfterBuyLink(buyHead,&buy);
		saveBuyData(buyHead);
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
	}
	printf("请输入蓝球号码:");
	scanf("%d",&num[6]);
	if(getchar() != '\n')
	{
		while(getchar() != '\n');
		printf("格式错误！\n");
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
		buy.buyerData = getPreNodePoint(buyerHead,name) -> next ->data;
		buy.state = 0;
		strcpy(buy.strState,"未兑奖");
		buy.money = 0.00;
		insertAfterBuyLink(buyHead,&buy);
		saveBuyData(buyHead);
		return 1;
	}
}
int printBuyRecord(BuyerLink *buyerHead,PubLink *pubHead,BuyLink *buyHead,char *name)
{
	buyHead = buyHead -> next;
	printf("购买期号 彩票编号 购买号码\t\t开奖号码\t\t选号方式 购买注数 获奖金额 开奖状态 兑奖状态\n");	
	while(NULL !=buyHead)
	{		
		if(0 == strcmp(name,buyHead -> data.buyerData.name))
		{
			Pub pub = getPrePubNodePoint(pubHead,buyHead -> data.issue) -> next -> data;
			printf("%08d %08d \033[31m%02d %02d %02d %02d %02d %02d\033[0m \033[34m%02d\033[0m  \033[31m%02d %02d %02d %02d %02d %02d\033[0m \033[34m%02d\033[0m    %s\t %d\t  %.2lf\t   %s   %s\n",\
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
	return 1;
}
