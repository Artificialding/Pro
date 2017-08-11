/*
* Copyright(c)Ziyi.Gao
* 文 件 名：lotview.c
* 描    述：打印菜单信息
* 作    者：Ziyi.Gao
* 创建日期：2017-8-5
* 完成日期：2017-8-5
* 当前版本：1.0
*/

#include "lotview.h"
#include <stdio.h>

/************************主菜单**************************/
void mainMenu(void)
{
	printf("1.用户登录\n");
	printf("2.用户注册\n");
	printf("0.退出系统\n");
}

/***********************彩民菜单*************************/
void buyerMenu(void)
{
	printf("1.个人信息\n");
	printf("2.购买彩票\n");
	printf("3.历史记录\n");
	printf("4.账户充值\n");
	printf("5.修改密码\n");
	printf("6.注销账户\n");
	printf("0.退出登录\n");
}


/***********************管理员菜单***********************/
void adminMenu(void)
{
	printf("1.发行彩票\n");
	printf("2.发行记录\n");
	printf("3.彩民信息\n");
	printf("4.查找彩民\n");
	printf("5.彩民排序\n");
	printf("0.推出登录\n");
}



/***********************公正员菜单***********************/
void notaryMenu(void)
{
	printf("1.发行授权\n");
	printf("2.彩票开奖\n");
	printf("3.发行记录\n");
	printf("0.退出登录\n");
}
