#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <time.h>
#include <iostream>
#include "HuRecursion.h"
#include "HuSplit.h"
#include "MaJiangAI1.h"

using namespace std;
using namespace NHuRecurSion;
using namespace NHuSplit;
using namespace NMaJiangAI;

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
	/*char cardValue[] ={0x02,0x02,0x02,0x03,0x04,0x15,0x15,0x15,0x21,0x22,0x23,0x32,0x32,0x32};

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
	
*/
	char cardValue[] ={
	0, 0, 0,0, 0, 0, 0, 0, 0,				//万
	0, 0, 0, 0,0, 0, 0, 0, 0,				//饼
	1, 2, 2, 1, 2, 0, 3,2, 1,				//条
	0, 0, 0, 0, 0, 0, 0                            //东南西北中发白
   };

	int maxCounts[MAX_SUM_CARD_NUM];
	int count = 0;

	int cin_index = 0;
	MaJiangDFSAI ai;
	while(1)
	{
		count = 0;
		for( int index = 0 ; index < MAX_SUM_CARD_NUM; index++ )
		{
			maxCounts[index] = 4;
			if(cardValue[index] != 0 ) count += cardValue[index];
		}

		int ret = ai.suggest( cardValue , count , maxCounts);
		if( ret < 0 ) {
			cout<<"fail "<<ret<<endl;
			break;
		}
		else if( ret == 2 )
		{
			cout<<"胡:";
			for( int index = 0 ; index < MAX_SUM_CARD_NUM; index++ )
			{
				if( cardValue[index] == 0 ) continue;

				char num = cardValue[index];
				cout<<ai.getCardAddr(index)<<"("<<(int)num<<") ";
			}
			cout<<endl;
			break;
		}

		cardValue[ret]--;
		cout <<"打牌:"<<ai.getCardAddr(ret)<<endl;

		cout<<"捉牌:";
		cin>>cin_index;
		if(cin_index < 0 || cin_index >= 34) break;
		cardValue[cin_index]++;
		cout<<ai.getCardAddr(cin_index)<<endl;
	}
	return 0;
}

