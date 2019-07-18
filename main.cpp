#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <time.h>
#include <iostream>
#include "HuRecursion.h"
#include "HuSplit.h"

using namespace std;
using namespace NHuRecurSion;
using namespace NHuSplit;

/*
static const BYTE s_HuCardType[] =
{
	0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09,				//万
	0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19,				//饼
	0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29,				//条
	0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37                            //东南西北中发白
};
*/
int main(int argc, char* argv[])
{
	//char cardValue[] ={0x02,0x02,0x04,0x05,0x06,0x09,0x09,0x09,0x25,0x25,0x25,0x26,0x26,0x27};
	//char cardValue[] ={0x02,0x02,0x04,0x05,0x06,0x25,0x25,0x26,0x26,0x27,0x27,0x29,0x29,0x29};
	char cardValue[] ={0x02,0x02,0x02,0x03,0x04,0x15,0x15,0x15,0x21,0x22,0x23,0x32,0x32,0x32};

	CHuRecursion  hu;
	int guiIndex[MAX_GUI_NUM] = {0};
	int guiIndexNum = 0;
	int total =5000000;
	clock_t  dwTimeBegin;
	clock_t  endBegin;


	HuSplit Hplit;
	Hplit.init("Hutbl.txt",false);
	Hplit.init("HutEyebl.txt",true);

	dwTimeBegin = clock() * 1000 / CLOCKS_PER_SEC;
	for(int n = 0 ; n < total ; n++)
	{
		int ret = Hplit.CheckHu(cardValue);
		if(!ret) cout <<ret<<"\n";
	}
	endBegin = clock() * 1000 / CLOCKS_PER_SEC;
	cout << "总数:" << total / 10000 << "万次, time:" << (endBegin - dwTimeBegin)/1000.0<< "s" << endl;

	dwTimeBegin = clock() * 1000 / CLOCKS_PER_SEC;
	for(int n = 0 ; n < total ; n++)
	{
		//cards[13] = 2;
		int ret = hu.CheckCanHu(cardValue, guiIndex, guiIndexNum);
		if(!ret) cout <<ret<<"\n";
	}
	endBegin = clock() * 1000 / CLOCKS_PER_SEC;
	cout << "总数:" << total / 10000 << "万次, time:" << (endBegin - dwTimeBegin)/1000.0<< "s" << endl;
	

	return 0;
}

