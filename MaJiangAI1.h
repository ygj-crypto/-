#pragma once

#include "HuDefine.h"

namespace NMaJiangAI
{
	struct SyantenArgs {
		int result;
		int MaxUseTileCount;
		int MinValue;
		SyantenArgs():result(8),MaxUseTileCount(0),MinValue(0){}
	};

	class MaJiangDFSAI
	{
	public:
		MaJiangDFSAI();
		~MaJiangDFSAI();
		
	public:
		int suggest( char *pCard, int nCount, int maxCounts[MAX_SUM_CARD_NUM] );
		const char* getCardAddr(int index);

	private:
		void syanten( char *pCard, int nCount, int &result );
		void normalSyanten(char *pCard, int nCount, int &result) ;
		void normalSyantenCutPair(char *pCard, int nCount, SyantenArgs &args) ;
		void normalSyantenCut3( char* pCard, int curIdx , int remCount, int argsTuple, SyantenArgs &args);
		void normalSyantenCut2( char* pCard, int curIdx , int remCount, int argsTuple, SyantenArgs &args);
	
		bool canSwap(int *maxCounts, int index) ;

	private:
		vector<string> pcarddes;
	};
}
