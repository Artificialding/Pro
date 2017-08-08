/*
* Copyright(c)Ziyi.Gao
* 文 件 名：lotlink.h
* 描    述：声明结构体变量,声明操作链表函数,人机交互字符串宏定义
* 作    者：Ziyi.Gao
* 创建日期：2017-8-5
* 完成日期：2017-8-5
* 当前版本：1.0
*/

#ifndef _LOTLINK_H_
#define _LOTLINK_H_

#define BUYER_HEAD_IS_NULL "彩民链表头节点为空！\n"
#define PUB_HEAD_IS_NULL "发行链表头节点为空！\n"
#define BUY_HEAD_IS_NULL "购买信息链表头节点为空！\n"

/***************彩民信息链表********************/
typedef struct buyer{
	int id;           //id
	char cardId[19];  //身份证号码
	char name[20];    //用户名
	char telNum[12];  //手机号码
	char passwd[10];  //密码
	double balance;   //账户余额
	int flag;         //冻结的标记(默认)0:激活状态 1:被冻结
}Buyer;

typedef struct buyerLink
{
	Buyer data;
	struct buyerLink *next;
}BuyerLink;

/***************发行信息链表********************/
typedef struct publish{
	int issue;        //发行期号	
	double price;     //每注单价
	int num;          //中奖号码
	int state;        //1:已开奖0：未开奖
	int sellCount;    //卖出注数
	double totalMoney;//奖池金额
}Pub;

typedef struct publishLink{
	Pub data;
	struct publishLink *next;
}PubLink;

/***************购买信息链表********************/
typedef struct buy{
	int issue;        //购买期号
	char id[10];      //单张彩票唯一标识
	int buyNum[5];    //4白1红
	int buyCount;     //购买注数
	Buyer data;       //购买者信息
	int state;        //1:已兑奖0：未兑奖
	double money;     //单张彩票代表金额		
}Buy;

typedef struct buyLink{
	Buy data;
	struct buyLink *next;
}BuyLink;

/*******************************操作彩民链表函数*********************/
int loadData(BuyerLink *buyerHead);                         //加载文件彩民信息到链表
int saveData(BuyerLink *buyerHead);                         //保存彩民信息链表到文件
int freeBuyerLinkAllNode(BuyerLink *buyerHead);             //释放所有彩民节点
BuyerLink *createBuyerNode(Buyer *buyer);                   //创建彩民节点
int insertAfterBuyerLink(BuyerLink *buyerHead,Buyer *buyer);//后插彩民节点
BuyerLink *getPreNodePoint(BuyerLink *buyHead,char *name);  //获取彩民前驱节点
//void delete_node(void);//删除指定节点
//void sort_node(void);//排序


#endif
