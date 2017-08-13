/*
* Copyright(c)Ziyi.Gao
* 文 件 名：lotlink.c
* 描    述：实现操作链表的函数，对外提供：文件读取保存、后插节点\
			返回前驱节点地址、	删除节点、释放所有节点、链表排序
* 作    者：Ziyi.Gao
* 创建日期：2017-8-5
* 完成日期：
* 当前版本：1.0
*/
#include "lotlink.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
* #include "lotlink.h"
* 声 明：
* 功 能：
* 接 收：
* 返 回：
*/
int loadData(BuyerLink *buyerHead)
{
	/*********加载彩民数据***********/
	if(NULL == buyerHead)
	{
		printf("BUYER_HEAD_IS_NULL");
		return 0;
	}
	FILE *fprBuyer = fopen("./file/buyer.bin","rb");
	if(NULL == fprBuyer)
	{
		system("mkdir file");
		system("touch ./file/buyer.bin");
		return 1;
	}
	Buyer buyer = {0};
	memset(&buyer,0,sizeof(Buyer));
	while(0 != fread(&buyer,sizeof(Buyer),1,fprBuyer))
	{
		insertAfterBuyerLink(buyerHead,&buyer);
	}
	fclose(fprBuyer);
	fprBuyer = NULL;
	return 1;
	/***************************************/

}

/*
* #include "lotlink.h"
* 声 明：
* 功 能：保存整条链表节点数据域到文件中
* 接 收：
* 返 回：int(1:保存成功 0:保存失败)
*/
int saveData(BuyerLink *buyerHead)
{
	if(NULL == buyerHead)
	{
		printf(BUYER_HEAD_IS_NULL);
		return 0;
	}
	FILE *fpsBuyer = fopen("./file/buyer.bin","wb");
	if(NULL == fpsBuyer)
	{
		printf("buyer.bin文件写打开失败！\n");
		return 0;
	}
	buyerHead = buyerHead -> next;
	while(NULL != buyerHead)
	{
		fwrite(&buyerHead -> data,sizeof(Buyer),1,fpsBuyer);
		buyerHead = buyerHead -> next;
	}
	fclose(fpsBuyer);
	fpsBuyer = NULL;
	return 1;

}
/*
* #include "lotlink.h"
* 声 明：
* 功 能：释放链表中所有节点空间
* 接 收：头指针
* 返 回：int (1:释放完毕 0:释放失败)
*/
int freeBuyerLinkAllNode(BuyerLink *buyerHead)
{
	if(NULL == buyerHead)
	{
		printf(BUYER_HEAD_IS_NULL);
		return 0;
	}
	BuyerLink *pre = NULL;
	while(NULL != buyerHead)
	{
		pre = buyerHead -> next;
		free(buyerHead);
		buyerHead = pre;
	}
	printf("BuyerLink释放完毕\n");
	return 1;
}
int getBuyerLinkLen(BuyerLink *buyerHead)
{
	if(NULL == buyerHead)
	{
		printf(BUYER_HEAD_IS_NULL);
		return 0;
	}
	if(NULL == buyerHead -> next)
	{
		return 0;
	}
	buyerHead = buyerHead -> next;
	return getBuyerLinkLen(buyerHead) + 1;
}

int sortBuyerByName(BuyerLink *buyerHead)
{
	if(NULL == buyerHead)
	{
		printf(BUYER_HEAD_IS_NULL);
		return 0;
	}
	printf("1.按升序排列\n");
	printf("2.按降序排列\n");
	int choose = 0;
	scanf("%d",&choose);
	if(getchar() != '\n')
	{
		while(getchar() != '\n');
		printf("格式有误！\n");
		return 0;
	}
	BuyerLink *i = buyerHead -> next;
	BuyerLink *j = NULL;
	BuyerLink *cursorMin = NULL;
	BuyerLink *cursorMax = NULL;
	if(1 == choose)
	{
		while(NULL != i)//改进选择排序
		{
			cursorMin = i;
			j = i -> next;
			while(NULL != j)
			{
				if(strcmp(i -> data.name,j -> data.name) <= 0)
				{
					cursorMin = i;
				}
				else
				{
					cursorMin = j;
				}
				j = j -> next;
			}
			Buyer temp = i -> data;
			i -> data = cursorMin -> data;
			cursorMin -> data = temp;
			i = i -> next;
		}
		saveData(buyerHead);
		return 1;
	}
	else if(2 == choose)
	{
		while(NULL != i)//改进选择排序
		{
			cursorMax = i;
			j = i -> next;
			while(NULL != j)
			{
				if(strcmp(i -> data.name,j -> data.name) == 1)
				{
					cursorMax = i;
				}
				else
				{
					cursorMax = j;
				}
				j = j -> next;
			}
			Buyer temp = i -> data;
			i -> data = cursorMax -> data;
			cursorMax -> data = temp;
			i = i -> next;
		}
		saveData(buyerHead);
		return 1;
	}
	else
	{
		printf("输入有误！\n");
		return 0;
	}
}
int sortBuyerById(BuyerLink *buyerHead)
{
	if(NULL == buyerHead)
	{
		printf(BUYER_HEAD_IS_NULL);
		return 0;
	}
	BuyerLink *i = buyerHead -> next;
	BuyerLink *j = NULL;
	printf("1.按升序排列\n");
	printf("2.按降序排列\n");
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
		while(NULL != i -> next)//选择排序
		{
			j = i -> next;
			while(NULL != j)
			{
				if(i -> data.id > j -> data.id)
				{
					Buyer temp = i -> data;
					i -> data = j -> data;
					j -> data = temp;
				}
				j = j -> next;
			}
			i = i -> next;
		}
		saveData(buyerHead);
		return 1;
	}
	else if(2 == choose)
	{
		while(NULL != i -> next)//选择排序
		{
			j = i -> next;
			while(NULL != j)
			{
				if(i -> data.id < j -> data.id)
				{
					Buyer temp = i -> data;
					i -> data = j -> data;
					j -> data = temp;
				}
				j = j -> next;
			}
			i = i -> next;
		}
		saveData(buyerHead);
		return 1;		
	}
	else
	{
		printf("输入有误！\n");
		return 0;
	}
}
int sortBuyerByBalance(BuyerLink *buyerHead)
{
	if(NULL == buyerHead)
	{
		printf(BUYER_HEAD_IS_NULL);
		return 0;
	}
	int len = getBuyerLinkLen(buyerHead);
	int i = 0,j = 0;
	BuyerLink *cursor = buyerHead -> next;
	printf("1.按升序排列\n");
	printf("2.按降序排列\n");
	int choose = 0;
	scanf("%d",&choose);
	if(getchar() != '\n')
	{
		printf("格式有误！\n");
		return 0;
	}
	if(1 == choose)
	{
		for(i = 0;i < len -1;++i)//冒泡排序升序
		{
			for(j = 0;j < len - 1 - i;++j)
			{
				if(cursor -> data.balance > cursor -> next -> data.balance)
				{
					Buyer temp = cursor -> data;
					cursor -> data = cursor -> next -> data;
					cursor -> next -> data = temp;
				}
				cursor = cursor -> next;		
			}	
			cursor = buyerHead -> next;
		}
		saveData(buyerHead);
		return 1;	
	}
	else if(2 == choose)
	{
		for(i = 0;i < len - 1;++i)//冒泡排序降序
		{
			for(j = 0;j < len - 1 - i;++j)
			{
				if(cursor -> data.balance < cursor -> next -> data.balance)
				{
					Buyer temp = cursor -> data;
					cursor -> data = cursor -> next -> data;
					cursor -> next -> data = temp;
				}
				cursor = cursor -> next;		
			}	
			cursor = buyerHead -> next;
		}
		saveData(buyerHead);
		return 1;
	}
	else
	{
		printf("输入有误！\n");
		return 0;
	}
}


/*
* #include "lotlink.h"
* 声 明：
* 功 能：创建新节点
* 接 收：
* 返 回：
*/
BuyerLink *createBuyerNode(Buyer *buyer)
{
	BuyerLink *newNode = (BuyerLink *)calloc(1,sizeof(BuyerLink));
	newNode -> data = *buyer;
	newNode -> next = NULL;
	return newNode;
}

/*
* #include "lotlink.h"
* 声 明：
* 功 能：节点后插
* 接 收：
* 返 回：
*/
int insertAfterBuyerLink(BuyerLink *buyerHead,Buyer *buyer)
{
	if(NULL == buyerHead)
	{
		printf("BUYER_HEAD_IS_NULL\n");
		return 0;
	}
	BuyerLink *newNode = createBuyerNode(buyer);
	while(NULL != buyerHead -> next)
	{
		buyerHead = buyerHead -> next;
	}
	buyerHead -> next = newNode;
	return 1;
}

/*
* #include "lotlink.h"
* 声 明：
* 功 能：返回前驱节点，根据用户名
* 接 收：
* 返 回：
*/
BuyerLink *getPreNodePoint(BuyerLink *buyerHead,char *name)
{
	if(NULL == buyerHead)
	{
		printf(BUYER_HEAD_IS_NULL);
		return 	NULL;
	}
	BuyerLink *pre = buyerHead;
	buyerHead = buyerHead -> next;
	while(NULL != buyerHead)
	{
		if(0 == (strcmp(buyerHead -> data.name,name)))
		{
			return pre;
		}
		pre = buyerHead;
		buyerHead = buyerHead -> next;
	}
	return NULL;	
}

int loadPubData(PubLink *pubHead)
{
	if(NULL == pubHead)
	{
		printf(PUB_HEAD_IS_NULL);
		return 0;
	}
	FILE *fprPub = fopen("./file/pub.bin","rb");
	if(NULL == fprPub)
	{
		system("touch ./file/pub.bin");
		return 1;
	}
	Pub pub = {0};
	memset(&pub,0,sizeof(Pub));
	if(0 != fread(&pub,sizeof(Pub),1,fprPub))
	{
		pubHead -> data = pub;
		memset(&pub,0,sizeof(fprPub));
	}
	while(0 != fread(&pub,sizeof(Pub),1,fprPub))
	{
		insertAfterPubLink(pubHead,&pub);
		memset(&pub,0,sizeof(fprPub));
	}
	fclose(fprPub);
	fprPub = NULL;
	return 1;
}
int savePubData(PubLink *pubHead)
{
	if(NULL == pubHead)
	{
		printf(PUB_HEAD_IS_NULL);
		return 0;
	}
	FILE *fpsPub = fopen("./file/pub.bin","wb");
	if(NULL == fpsPub)
	{	
		printf("pub.bin文件写打开失败！\n");
		return 0;
	}
	while(NULL != pubHead)//PubLink头节点中有授权信息，所以头节点也保存
	{
		fwrite(&pubHead -> data,sizeof(Pub),1,fpsPub);
		pubHead = pubHead -> next;
	}
	fclose(fpsPub);
	fpsPub = NULL;
	return 1;
}
int freePubLinkAllNode(PubLink *pubHead)
{
	if(NULL == pubHead)
	{
		printf(PUB_HEAD_IS_NULL);
		return 0;
	}
	PubLink *pre = NULL;
	while(NULL != pubHead)
	{
		pre = pubHead -> next;
		free(pubHead);
		pubHead = pre;
	}
	printf("PubLink释放完毕！\n");
	return 1;
}

PubLink *createPubNode(Pub *pub)
{
	PubLink *newNode = (PubLink *)calloc(1,sizeof(PubLink));
	newNode -> data = *pub;
	newNode -> next = NULL;
	return newNode;
}

int insertAfterPubLink(PubLink *pubHead,Pub *pub)
{
	if(NULL == pubHead)
	{
		printf(PUB_HEAD_IS_NULL);
		return 0;
	}
	PubLink *newNode = createPubNode(pub);
	while(NULL != pubHead -> next)
	{
		pubHead = pubHead -> next;
	}
	pubHead -> next = newNode;
	return 1;
}

PubLink *getPrePubNodePoint(PubLink *pubHead,int issue)
{
	if(NULL == pubHead)
	{
		printf(PUB_HEAD_IS_NULL);
		return 0;
	}
	PubLink *pre = pubHead;
	pubHead = pubHead -> next;
	while(NULL != pubHead)
	{
		if(issue == pubHead -> data.issue)
		{
			return pre;
		}
		pre = pubHead;
		pubHead = pubHead -> next;
	}
	return NULL;
}

PubLink *getLastPubNodePoint(PubLink *pubHead)
{
	if(NULL == pubHead)
	{
		printf(PUB_HEAD_IS_NULL);
		return NULL;
	}
	while(NULL != pubHead -> next)
	{
		pubHead = pubHead -> next;
	}
	return pubHead;
}

int loadBuyData(BuyLink *buyHead)
{
	if(NULL == buyHead)
	{
		printf(BUY_HEAD_IS_NULL);
		return 0;
	}
	FILE *fprBuy = fopen("./file/buy.bin","rb");
	if(NULL == fprBuy)
	{
		system("touch ./file/buy.bin");
		return 1;
	}
	Buy buy = {0};
	memset(&buy,0,sizeof(Buy));
	while(0 != fread(&buy,sizeof(Buy),1,fprBuy))
   	{
		insertAfterBuyLink(buyHead,&buy);
		memset(&buy,0,sizeof(Buy));
	}
	fclose(fprBuy);
	fprBuy = NULL;
	return 1;
}

int saveBuyData(BuyLink *buyHead)
{
	if(NULL == buyHead)
	{
		printf(BUY_HEAD_IS_NULL);
		return 0;
	}
	FILE *fpsBuy = fopen("./file/buy.bin","wb");
	if(NULL == fpsBuy)
	{
		printf("buy.bin写打开失败！\n");
		return 0;
	}
	buyHead = buyHead -> next;
	while(NULL != buyHead)
	{
		fwrite(&buyHead -> data,sizeof(Buy),1,fpsBuy);
		buyHead = buyHead -> next;
	}
	fclose(fpsBuy);
	fpsBuy = NULL;
	return 1;
}

int freeBuyLinkAllNode(BuyLink *buyHead)
{
	if(NULL == buyHead)
	{
		printf(BUY_HEAD_IS_NULL);
		return 0;
	}
	BuyLink *pre = NULL;
	while(NULL != buyHead)
	{
		pre = buyHead -> next;
		free(buyHead);
		buyHead = pre;
	}
	printf("BuyLink释放完毕\n");
	return 1;
}

int insertAfterBuyLink(BuyLink *buyHead,Buy *buy)
{
	if(NULL == buyHead)
	{
		printf(BUY_HEAD_IS_NULL);
		return 0;
	}
	BuyLink *newNode = createBuyNode(buy);
	while(NULL != buyHead -> next)
	{
		buyHead = buyHead -> next;
	}
	buyHead -> next = newNode;
	return 1;
}
BuyLink *createBuyNode(Buy *buy)
{
	BuyLink *newNode = (BuyLink *)calloc(1,sizeof(BuyLink));
	newNode -> data = *buy;
	newNode -> next = NULL;
	return newNode;
}
BuyLink *getPreBuyNodePoint(BuyLink *buyHead,int issue)
{
	if(NULL == buyHead)
	{
		printf(BUY_HEAD_IS_NULL);
		return NULL;
	}
	while(NULL != buyHead -> next)
	{
		if(buyHead -> next -> data.issue == issue)
		{
			return buyHead;
		}
		buyHead = buyHead -> next;
	}
	return NULL;
}
BuyLink *getLastBuyNodePoint(BuyLink *buyHead)
{
	if(NULL == buyHead)
	{	
		printf(BUY_HEAD_IS_NULL);
		return NULL;
	}
	while(NULL != buyHead -> next)
	{
		buyHead = buyHead -> next;
	}
	return buyHead;
}

