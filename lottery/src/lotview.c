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
	printf("\t\t\t>>>>>>>>>>>>>>>>>>>>>>>>>>双色球<<<<<<<<<<<<<<<<<<<<<<<<<\n");
	printf("\t\t\t^\t\t\t\t\t\t\t^\n");
	printf("\t\t\t^\t\t\t1.登录账户\t\t\t^\n");
	printf("\t\t\t^\t\t\t2.注册账户\t\t\t^\n");
	printf("\t\t\t^\t\t\t3.开奖规则\t\t\t^\n");
	printf("\t\t\t^\t\t\t4.找回密码\t\t\t^\n");
	printf("\t\t\t^\t\t\t0.退出系统\t\t\t^\n");
	printf("\t\t\t^\t\t\t\t\t\t\t^\n");
	printf("\t\t\t<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n\n");
}

/***********************彩民菜单*************************/
void buyerMenu(void)
{
	printf("\t\t\t>>>>>>>>>>>>>>>>>>>>>>>>>用户菜单<<<<<<<<<<<<<<<<<<<<<<<<\n");
	printf("\t\t\t^\t\t\t\t\t\t\t^\n");
	printf("\t\t\t^\t\t\t1.个人信息\t\t\t^\n");
	printf("\t\t\t^\t\t\t2.购买彩票\t\t\t^\n");
	printf("\t\t\t^\t\t\t3.彩民评论\t\t\t^\n");
	printf("\t\t\t^\t\t\t4.购买记录\t\t\t^\n");
	printf("\t\t\t^\t\t\t5.账户充值\t\t\t^\n");
	printf("\t\t\t^\t\t\t6.修改密码\t\t\t^\n");
	printf("\t\t\t^\t\t\t7.注销账户\t\t\t^\n");
	printf("\t\t\t^\t\t\t0.退出登录\t\t\t^\n");
	printf("\t\t\t^\t\t\t\t\t\t\t^\n");
	printf("\t\t\t<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n\n");
}


/***********************管理员菜单***********************/
void adminMenu(void)
{
	printf("\t\t\t>>>>>>>>>>>>>>>>>>>>>>>>管理员菜单<<<<<<<<<<<<<<<<<<<<<<<\n");
	printf("\t\t\t^\t\t\t\t\t\t\t^\n");
	printf("\t\t\t^\t\t\t1.发行彩票\t\t\t^\n");
	printf("\t\t\t^\t\t\t2.奖池金额\t\t\t^\n");
	printf("\t\t\t^\t\t\t3.发行记录\t\t\t^\n");
	printf("\t\t\t^\t\t\t4.彩民信息\t\t\t^\n");
	printf("\t\t\t^\t\t\t5.查找彩民\t\t\t^\n");
	printf("\t\t\t^\t\t\t6.彩民排序\t\t\t^\n");
	printf("\t\t\t^\t\t\t7.账户充值\t\t\t^\n");
	printf("\t\t\t^\t\t\t8.账户找回\t\t\t^\n");	
	printf("\t\t\t^\t\t\t0.推出登录\t\t\t^\n");
	printf("\t\t\t^\t\t\t\t\t\t\t^\n");
	printf("\t\t\t<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n\n");
}



/***********************公正员菜单***********************/
void notaryMenu(void)
{
	printf("\t\t\t>>>>>>>>>>>>>>>>>>>>>>>>公正员菜单<<<<<<<<<<<<<<<<<<<<<<<\n");
	printf("\t\t\t^\t\t\t\t\t\t\t^\n");
	printf("\t\t\t^\t\t\t1.发行授权\t\t\t^\n");
	printf("\t\t\t^\t\t\t2.彩票开奖\t\t\t^\n");
	printf("\t\t\t^\t\t\t3.发行记录\t\t\t^\n");
	printf("\t\t\t^\t\t\t0.退出登录\t\t\t^\n");
	printf("\t\t\t^\t\t\t\t\t\t\t^\n");
	printf("\t\t\t<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n\n");
}
