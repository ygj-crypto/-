#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <time.h>
#include <iostream>
#include "HuRecursion.h"

using namespace std;
using namespace NHuRecurSion;
int main(int argc, char* argv[])
{
	char cards[34] = {
	0,0,0,2,3,3,4,1,1,  //万
	0,0,0,0,0,0,0,0,0,	//筒
	0,0,0,0,0,0,0,0,0,  //索
	0,0,0,0,0,0,0       //字牌
	};
	CHuRecursion  hu;
	int guiIndex[MAX_GUI_NUM] = {0};
	int guiIndexNum = 0;
	int total = 5000000;
	clock_t  dwTimeBegin = clock() * 1000 / CLOCKS_PER_SEC;
	for(int n = 0 ; n < total ; n++)
	{
		//cards[13] = 2;
		int ret = hu.CheckCanHu(cards, guiIndex, guiIndexNum);
		if(!ret) cout <<ret<<"\n";
	}
	clock_t  endBegin = clock() * 1000 / CLOCKS_PER_SEC;
	cout << "总数:" << total / 10000 << "万次, time:" << (endBegin - dwTimeBegin)/1000.0<< "s" << endl;
	return 0;
}
