/*
* Copyright(c)Ziyi.Gao
* 作    者：ziyi.Gao
* 创建日期：2017-8-5
* 完成日期：2017-8-5
* 当前版本：1.0
*/

#include "lotlink.h"
#include "lotcontrol.h"
#include <stdlib.h>
int main(void)
{
	BuyerLink *buyerHead = (BuyerLink *)calloc(1,sizeof(BuyerLink));
	PubLink *pubHead = (PubLink *)calloc(1,sizeof(PubLink));
	BuyLink *buyHead = (BuyLink *)calloc(1,sizeof(BuyLink));
	mainMenuControl(buyerHead,pubHead,buyHead);
	




	return 0;
}
