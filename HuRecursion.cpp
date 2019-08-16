#include<string.h>
#include "HuRecursion.h"
#include "HuDefine.h"

namespace NHuRecurSion
{

HuType huType1[]={//第一个是1牌
	{1,1,1,false} ,
	{2,0,0,true},
};

HuType huType2[]={//第一个是2牌
	{2,0,0,true},
	{2,2,2,false},
	{3,0,0,false},
	
};


HuType huType3[]={//第一个是3牌
	{3,0,0,false}, 
	{3,1,1,true},  
};


HuType huType4[]={//第一个是4牌
	{4,1,1,false},  
	{4,2,2,false},  
	{5,0,0,true},  
};

CHuRecursion::CHuRecursion()
{

}

CHuRecursion::~CHuRecursion()
{

}
	
void CHuRecursion::StatisticsCard(char * pCards , char *cardValue)
{
	int idx = 0;
	for(uint32_t index = 0 ; index < MAX_CARD_NUM; index++ )
	{
		if( pCards[index] == 0 ) break;

		idx = ((pCards[index]%0x10) - 1) + (pCards[index]>>4)*MAX_ONE_CARD_NUM;
		cardValue[idx]++;
	}
}

bool CHuRecursion::CheckCanHu(char *pCards, int guiIndex[MAX_GUI_NUM] , int guiIndexNum )
{

	bool HasEyes = false;
	int guiNum = 0;
	int needGuiNum = 0;
	char cards[START_FLOWER_INDEX] = {0};

	StatisticsCard(pCards, cards);
	if( guiIndexNum > 0 )
	{
		guiNum = GuiNum(cards, guiIndex );
	}

	//七对返回
	if( CheckPair(cards,guiNum,needGuiNum) ) return true;

	if(CheckThirteen(cards,guiNum,needGuiNum)) return true;

	if( !CheckZi(cards, HasEyes, guiNum, needGuiNum) ) return false;

	if( !CheckColor(&cards[START_WAN_INDEX], HasEyes, guiNum, needGuiNum) ) return false;

	if( !CheckColor(&cards[START_TIAO_INDEX], HasEyes, guiNum, needGuiNum) ) return false;

	if( !CheckColor(&cards[START_TONG_INDEX], HasEyes, guiNum, needGuiNum) ) return false;

	return true;
}

bool CHuRecursion::CheckPair(char * pCards, int& nGuiCount, int& nNeedGui )
{
	int Count = 0;
	int needGui = 0;
	for(int index = 0 ; index < START_FLOWER_INDEX; index++ )
	{
		char cardValue = pCards[index];
		switch(cardValue)
		{
			case 1:
				needGui++;
				Count++;
				break;
			case 2:
				Count++;
				break;
			case 3:
				needGui++;
				Count+=2;
				break;
			case 4:
				Count+=2;
				break;
			default:
				break;
		}
	}

	nNeedGui = needGui;
	needGui = nGuiCount - nNeedGui;
	if( needGui >=0 )
	{
		Count += needGui/2;
		if(Count == 7 ) return true;
	}

	return false;
}


bool CHuRecursion::CheckThirteen(char * pCards, int& nGuiCount, int& nNeedGui )
{
	int count = 0;
	int needGui = 0;
	int num = 0;
	bool eye = false;
	for( count = 0 ; count < MAX_CARD_TYPE; count++ )
	{
		char cardValue1 = pCards[count*MAX_ONE_CARD_NUM];
		char cardValue2 = pCards[count*MAX_ONE_CARD_NUM+MAX_ONE_CARD_NUM-1];
		if(cardValue1 == 0) 
		{
			needGui++;
		}
		else if( cardValue1 == 2 && !eye )
		{
			eye = true;
		}
		else if(cardValue1 != 1)
		{
			return false;
		}

		if(cardValue2 == 0) 
		{
			needGui++;
		}
		else if( cardValue2 == 2 && !eye )
		{
			eye = true;
		}
		else if(cardValue2 != 1)
		{
			return false;
		}

		num += 2;
	}

	for( count = START_ZI_INDEX ; count < START_FLOWER_INDEX; count++ )
	{
		char cardValue = pCards[count];
		if( cardValue == 0 )
		{
			needGui++;
		}
		else if( cardValue == 2 && !eye )
		{
			eye = true;
		}
		else if( cardValue != 1)
		{
			return false;
		}
		num++;
	}

	nNeedGui = needGui;
	needGui = nGuiCount - nNeedGui;
	num = num + needGui + eye;
	if( num == 14)
	{
		return true;
	}

	return false;
}

bool CHuRecursion::CheckZi(char * pCards, bool& HasEyes, int& nGuiCount, int& nNeedGui )
{
	int needGui = 0;
	int eyeNum = 0;
	nNeedGui = 0;
	for( int index = START_ZI_INDEX ; index < START_FLOWER_INDEX ; index++ )
	{
		if( pCards[index] == 0 ) continue;

		//有赖子可以组成3个和一对
		if( pCards[index] == 1 || pCards[index] == 4 )
		{
			needGui++;
			eyeNum++;
		}
		else if( pCards[index] == 2 )
		{
			eyeNum++;
		}
	}


	if( eyeNum >= 1 )
	{
		if(HasEyes)
		{
			nNeedGui = needGui + eyeNum;
		}
		else
		{
			nNeedGui = needGui + (eyeNum -1);
		}

		HasEyes = true;
	}

	nGuiCount -= nNeedGui;
	if( nGuiCount < 0 ) return false;

	return true;
}

bool CHuRecursion::CheckColor(char * pCards, bool& HasEyes, int& nGuiCount, int& nNeedGui )
{
	int nSumCount = 0;
	int remain = 0;
	int needGui = 0;
	bool isHu = false;

	// 为拆顺子多留两个空间，比如最后一个数1时,不用往回减
	char cards[11] = {0};
	memcpy(cards, pCards, MAX_ONE_CARD_NUM*sizeof(char));

	for(int index = 0 ; index < MAX_ONE_CARD_NUM; index++ )
	{
		nSumCount += cards[index];
	}

	//没有这类牌
	if( nSumCount == 0 ) return true;

	if( nGuiCount == 0 )
	{
		remain = nSumCount%3;
		//没有鬼牌了，如果这类型的牌，要满足3n或者3n+2(已有眼的情况除外)
		if(!((HasEyes&& remain == 0) || (HasEyes&&remain == 2)) ) return false;
	}

	for( int count = 0; count <= nGuiCount; count++ )
	{
		remain = (nSumCount + count)%3;
		if( remain == 1 )continue;

		bool cur_eye = HasEyes;
		if(CheckHu(cards, 0, cur_eye, count))//判胡
		{
			HasEyes = cur_eye;
			needGui = count;
			isHu = true;
			break;
		}
	}

	nNeedGui = needGui;
	nGuiCount -= nNeedGui;
	if( nGuiCount < 0 ) return false;

	return isHu;
}


int CHuRecursion::GuiNum(char *pCards , int guiIndex[MAX_GUI_NUM])
{
	int guiNum = 0;

	for( int i = 0 ; i < MAX_GUI_NUM ; i++ )
	{
		int index = guiIndex[i];
		if(index > 0 && index < START_FLOWER_INDEX )
		{
			guiNum += pCards[index];
			pCards[index] = 0;
		}

	}

	return guiNum;
}

bool CHuRecursion::CheckHu( char * pCards, int startIndex, bool& HasEyes, int& nGuiCount)
{
	if( startIndex >= MAX_ONE_CARD_NUM ) return true;

	char cardValue = pCards[startIndex];
	if( cardValue == 0 ) return CheckHu(pCards, startIndex+1, HasEyes, nGuiCount);

	int optNum = 0;
	HuType *pHu = NULL;
	pHu = GetHuType(cardValue , optNum);
	if( pHu == NULL ) return false;

	for(int index = 0; index < optNum; index++ )
	{
		HuType &huType = pHu[index];
		if( HasEyes && huType.eye ) continue;

		int guiNumTmp = 0;
		int ret = false;
		int num = 0;
		char oldCardValue[MAX_OPT_NUM]={0};
		for(num = 0 ; num < MAX_OPT_NUM; num++ )
		{
			oldCardValue[num] = pCards[startIndex+num];
			pCards[startIndex+num] -= huType.num[num];
			if(pCards[startIndex+num] < 0 )
			{
				guiNumTmp += (-pCards[startIndex+num]);
				pCards[startIndex+num] = 0;
			}
		}

		//还有鬼
		if( guiNumTmp <= nGuiCount )
		{
			int numTmp = nGuiCount-guiNumTmp;
			ret = CheckHu(pCards, startIndex+1, HasEyes, numTmp);
		}

		//还原数据,因为上面不符合
		for(num = 0 ; num < MAX_OPT_NUM; num++ )
		{
			pCards[startIndex+num] = oldCardValue[num];
		}

		//找到可以胡的牌型，如果要寻找所有可以在这里保存数据然后继续循环
		if( ret )
		{
			HasEyes = HasEyes||huType.eye;
			return true;
		}
	}

	return false;
}

HuType* CHuRecursion::GetHuType( char cardValue , int &optNum )
{
	optNum = 0;
	switch(cardValue)
	{
	case 1:
		optNum = sizeof(huType1)/sizeof(HuType);
		return huType1;
	case 2:
		optNum = sizeof(huType2)/sizeof(HuType);
		return huType2;
	case 3:
		optNum = sizeof(huType3)/sizeof(HuType);
		return huType3;
	case 4:
		optNum = sizeof(huType4)/sizeof(HuType);
		return huType4;
	default:
		return NULL;
	}
}
}
