
#include "MaJiangAI1.h"

using namespace std;
//https://blog.csdn.net/ywloveb/article/details/88171832
//https://zhuanlan.zhihu.com/p/31000381
//http://blog.sina.com.cn/s/blog_5fd85e4b0101c4ut.html
//http://tenhou.net/2

namespace NMaJiangAI
{

MaJiangDFSAI::MaJiangDFSAI()
{
	pcarddes.push_back("一万");
	pcarddes.push_back("二万");
	pcarddes.push_back("三万");
	pcarddes.push_back("四万");
	pcarddes.push_back("五万");
	pcarddes.push_back("六万");
	pcarddes.push_back("七万");
	pcarddes.push_back("八万");
	pcarddes.push_back("九万");
	pcarddes.push_back("一饼");
	pcarddes.push_back("二饼");
	pcarddes.push_back("三饼");
	pcarddes.push_back("四饼");
	pcarddes.push_back("五饼");
	pcarddes.push_back("六饼");
	pcarddes.push_back("七饼");
	pcarddes.push_back("八饼");
	pcarddes.push_back("九饼");
	pcarddes.push_back("一条");
	pcarddes.push_back("二条");
	pcarddes.push_back("三条");
	pcarddes.push_back("四条");
	pcarddes.push_back("五条");
	pcarddes.push_back("六条");
	pcarddes.push_back("七条");
	pcarddes.push_back("八条");
	pcarddes.push_back("九条");
	pcarddes.push_back("东");
	pcarddes.push_back("南");
	pcarddes.push_back("西");
	pcarddes.push_back("北");
	pcarddes.push_back("中");
	pcarddes.push_back("发");
	pcarddes.push_back("白");
}

MaJiangDFSAI::~MaJiangDFSAI()
{

}

const char* MaJiangDFSAI::getCardAddr(int index)
{
	return pcarddes[index].c_str();
}	

int MaJiangDFSAI::suggest( char *pCard, int nCount, int maxCounts[MAX_SUM_CARD_NUM])
{
	if( nCount%3 != 2 )
	{
		cout<<"牌数量除以3的余数为:"<<nCount%3<<endl;
		return -1;
	}

	string tmp = "手牌:";
	for(int count = 0 ; count < MAX_SUM_CARD_NUM ; count++ )
	{
		maxCounts[count]-= pCard[count];
		if(  pCard[count] != 0 )
		{
			tmp += pcarddes[count];
			tmp += "(";
			tmp += to_string(pCard[count]);
			tmp += "), ";
		}
	}

	cout << tmp<<endl;
	int maxCount = 0;
	int oldIndex = 0;
	int best = nCount - 1;
	syanten(pCard , nCount, best );

	if( best < 0 ) return 2;

	for( int srcIndex = 0 ; srcIndex < MAX_SUM_CARD_NUM; srcIndex++ )
	{
		if( pCard[srcIndex] == 0 ) continue;

		string tmp = "";
		int count = 0;
		for( int dstIndex = 0; dstIndex < MAX_SUM_CARD_NUM; dstIndex++ )
		{
			if( !canSwap(maxCounts,dstIndex) || dstIndex == srcIndex) continue;

			pCard[dstIndex] += 1;
			pCard[srcIndex] -= 1;
			maxCounts[dstIndex] -= 1;
			int result = best;

			syanten(pCard, nCount, result);
			if (result < best) {
				if( tmp == "") 
				{
					tmp += "result:";
					tmp += to_string(result);
					tmp +="  出牌:";
					tmp +=pcarddes[srcIndex];
					tmp += "可以捉的牌：";
				}

				tmp += "  ";
				tmp += pcarddes[dstIndex];
				count++;
			}
			//cout<<result<<endl;

			pCard[dstIndex] -= 1;
			pCard[srcIndex] += 1;
			maxCounts[dstIndex] += 1;
		}

		if( maxCount < count )
		{
			 maxCount = count;
			 oldIndex = srcIndex;
		}

		if( tmp != "" ) cout<<tmp<<endl;
	}

	if( maxCount > 0 && pCard[oldIndex] > 0 )
	{
		return oldIndex;
	}

	return -1;

}


void MaJiangDFSAI::syanten( char *pCard, int nCount, int &result )
{
	int best = 1 - nCount%3;
	if( nCount == 13 || nCount == 14 ) //牌全部在手中要判断特殊牌型，如7对
	{
		if(best == result ) return;
	}

	normalSyanten( pCard, nCount, result );
}

void MaJiangDFSAI::normalSyanten(char *pCard, int nCount, int &result) 
{
	if( nCount%3 == 0 )
	{
		cout<<"牌数量除以3的余数为:"<<nCount%3<<endl;
		return;
	}

	SyantenArgs args;
	args.result = result;
	args.MinValue = 1 -  nCount%3;

	normalSyantenCutPair(pCard, nCount, args);
	result = args.result;
}


void MaJiangDFSAI::normalSyantenCutPair(char *pCard, int nCount, SyantenArgs &args) 
{
	if( args.result == args.MinValue) return;

	for( int idx = 0 ; idx < MAX_SUM_CARD_NUM ; idx++ )
	{
		if(pCard[idx] >= 2 )
		{
			pCard[idx] -= 2;
			normalSyantenCut3( pCard, 0, nCount-2, (nCount/3)|0x01000000, args);
			pCard[idx] += 2;
		}
	}

	normalSyantenCut3( pCard, 0, nCount, nCount/3, args);
}

void MaJiangDFSAI::normalSyantenCut3( char* pCard, int curIdx , int remCount, int argsTuple, SyantenArgs &args)
{
	if( args.result == args.MinValue) return;
	while( curIdx < MAX_SUM_CARD_NUM && pCard[curIdx] == 0 ) curIdx++;

	if( curIdx == MAX_SUM_CARD_NUM )
	{
		normalSyantenCut2(pCard, 0, remCount, argsTuple, args);
		return;
	}

	char &curr = pCard[curIdx];
	if( curr >= 3 )
	{
		curr -= 3;
		normalSyantenCut3( pCard, curIdx, remCount-3, argsTuple + 0x0100, args);
		curr += 3;
	}

	if( curIdx%9 <= 6 && curIdx < 27)
	{
		char &next = pCard[curIdx+1];
		char &nextNext = pCard[curIdx+2];
		if( next > 0 && nextNext > 0 )
		{
			curr--;
			next--;
			nextNext--;
			normalSyantenCut3( pCard, curIdx, remCount-3, argsTuple + 0x0100, args);
			curr++;
			next++;
			nextNext++;
		}
	}

	normalSyantenCut3( pCard, curIdx+1, remCount, argsTuple, args);
}


void MaJiangDFSAI::normalSyantenCut2( char* pCard, int curIdx , int remCount, int argsTuple, SyantenArgs &args)
{
	if( args.result == args.MinValue) return;

	int N = ((char*)&argsTuple)[0];
	int C3 = ((char*)&argsTuple)[1];
	int C2 = ((char*)&argsTuple)[2];
	int P = ((char*)&argsTuple)[3];
	int useTileCount = C3 + (C3 + C2 + P) * 2;

	if (C3 + C2 > N) return;
	if (remCount < args.MaxUseTileCount - useTileCount) return;

	if (remCount == 0) {
		int num = (N - C3) * 2 - C2 - P;
		if (num < args.result) args.result = num;
		if (args.MaxUseTileCount < useTileCount) args.MaxUseTileCount = useTileCount;
		//cout<<"N:"<<N<<"  C3："<<C3<<"  C2:"<<C2<<"  P:"<<P<<"  num:"<<num<<endl;
		return;
	}

	while (pCard[curIdx] == 0) curIdx++;

	char &curr = pCard[curIdx];
	if (curr >= 2) {
		curr -= 2;
		normalSyantenCut2(pCard, curIdx, remCount - 2, argsTuple + 0x010000, args);
		curr += 2;
	}

	if( curIdx < 27 )
	{
		char &next = pCard[curIdx+1];
		char &nextNext = pCard[curIdx+2];
		if( curIdx%9 <= 7  && next > 0 )
		{
			curr--;
			next--;
			normalSyantenCut2(pCard, curIdx, remCount - 2, argsTuple + 0x010000, args);
			next++;
			curr++;
		}

		if (curIdx%9 <= 6 && nextNext > 0 ) 
		{
			curr--;
			nextNext--;
			//cout <<"curIdx:"<<curIdx<<endl;
			normalSyantenCut2(pCard, curIdx, remCount - 2, argsTuple + 0x010000, args);
			nextNext++;
			curr++;
		}
	}

	int tempCurr = curr;
	curr = 0;
	normalSyantenCut2(pCard, curIdx+1, remCount - tempCurr, argsTuple, args);
	curr = tempCurr;

}


bool MaJiangDFSAI::canSwap(int *maxCounts, int index) {

	if (maxCounts[index] == 0) return false;
	return true;
}

}
