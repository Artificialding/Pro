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
#if 0
/*
* #include "lotlink.h"
* 声 明：
* 功 能：从链表中删除***的节点
* 接 收：
* 返 回：int（1:删除成功 0:删除失败）
*/
void delete_node(BuyLink *head)
{
	if(NULL == head)
	{
		printf("头节点为空\n");
		return;
	}
	BuyLink *pre = select_front_node(head);
	if(NULL == pre)
	{
		printf("不存在\n");
		return;
	}
	BuyerLink *del = pre -> next;
	pre -> next = del -> next;
	free(del);
	del = NULL;
	printf("删除成功\n");
}


/*
* #include "lotlink.h"
* 声 明：
* 功 能：根据**对链表中的数据域进行排序
* 接 收：头指针
* 返 回：int (1:排序成功 0:排序失败)
*/
void sort_node(BuyerLink *head)
{
	if(NULL == head)
	{
		printf("头节点为空\n");
	}
	int length = 0;
	int i = 0,j = 0;
	BuyerLink *save = head;
	head = head -> next;
	while(NULL != head)
	{
		++length;
		head = head -> next;
	}
	for(i = 0;i < length - 1;++i)
	{
		head = head -> next;
		for(j = 0;j < length - 1 - i;++j)
		{
			//排序条件
			head = head -> next;
		}
	}
	printf("排序成功,请前往查看\n");
}
#endif

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
		printf("id = %d   state = %d\n",pubHead -> data.issue,pubHead -> data.state);
	}
	while(0 != fread(&pub,sizeof(Pub),1,fprPub))
	{
		printf("id = %d   state = %d\n",pub.issue,pub.state);
		memset(&pub,0,sizeof(Pub));
		insertAfterPubLink(pubHead,&pub);
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
		printf("state = %d  id = %d\n",pubHead -> data.state,pubHead -> data.issue);
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
