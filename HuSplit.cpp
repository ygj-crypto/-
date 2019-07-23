#include "HuSplit.h"
#include "HuDefine.h"

namespace NHuSplit
{

HuSplit::HuSplit()
{
}
HuSplit::~HuSplit()
{

}

//初始化表
void HuSplit::init(const string &path , const bool is_eye)
{
	m_splitTbl.initTable(path, is_eye);
}

void HuSplit::StatisticsCard(char * pCards )
{
	uint32_t idx = 0;
	memset( m_statisticsData,  0, sizeof(m_statisticsData));
	m_statisticsData[idx].value = pCards[0];
	zi_index = -1;
	for(uint32_t index = 0 ; index < MAX_CARD_NUM; index++ )
	{
		if( pCards[index] == 0 ) break;

		if(  pCards[index] == m_statisticsData[idx].value )
		{
			m_statisticsData[idx].num++;
		}
		else
		{
			idx++;
			if( idx >= MAX_CARD_NUM ) break;
			m_statisticsData[idx].num = 1;
			m_statisticsData[idx].value = pCards[index];
		}

		if( index >= START_ZI_INDEX && zi_index < 0 )
			zi_index = idx;
	}

}

bool HuSplit::CheckHu( char *pCard )
{
	CardValue cardValue[MAX_CARD_NUM]={0};
	bool isHu = false;
	uint32_t eyeNum = 0;

	StatisticsCard(pCard);
	eyeNum = splitZiCard();
	if( eyeNum > 1 )
	{
		return false;
	}
	
	isHu = splitCard(cardValue,eyeNum);
	if( !isHu ) return false;

	for( uint32_t idx = 0 ; idx < MAX_CARD_NUM; idx++ )
	{
		if(cardValue[idx].value == 0 || cardValue[idx].num == 0 ) break;

		if( cardValue[idx].num%3 == 2 )
		{
			isHu = m_splitTbl.CheckTable( cardValue[idx].value , true);
			eyeNum++;
		}
		else
		{
			isHu = m_splitTbl.CheckTable( cardValue[idx].value , false);
		}

		if( !isHu ) return false;
	}

	if( !(eyeNum == 1 || eyeNum == 7) ) isHu = false;

	return isHu;

}

bool HuSplit::splitCard( CardValue *cardValue , uint32_t eye_num )
{
	char prvValue = 0;
	uint32_t remain = 0;
	uint32_t idx = 0;
	uint32_t max_index = zi_index > 0?zi_index:MAX_CARD_NUM;
	for(uint32_t index = 0 ; index < max_index; index++ )
	{
		if( m_statisticsData[index].num == 0 ) break;

		if(cardValue[idx].value == 0 )
		{
			cardValue[idx].value = m_statisticsData[index].num;
		}
		else if( m_statisticsData[index].value == prvValue + 1 )
		{
			cardValue[idx].value = cardValue[idx].value*10 + m_statisticsData[index].num;	
		}
		else if( cardValue[idx].value > 0 && cardValue[idx].num > 0 )
		{
			remain = cardValue[idx].num%3;
			if( (remain == 0)||(remain == 2 && !eye_num) )
			{
				idx++;
				cardValue[idx].num = 0;
				cardValue[idx].value = m_statisticsData[index].num;
				if( remain == 2 ) eye_num = true;
			}
			else
			{
				return false;
			}
		}

		cardValue[idx].num += m_statisticsData[index].num;
		prvValue = m_statisticsData[index].value;
	}
	return true;
}

//返回值大于1是不能胡的
uint32_t HuSplit::splitZiCard()
{
	uint32_t num = 0;

	if( zi_index < 0 ) return 0;

	for(uint32_t idx = zi_index ; idx < MAX_CARD_NUM; idx++ )
	{
		if( m_statisticsData[idx].num == 0 ) break;

		if(m_statisticsData[idx].num == 1 || m_statisticsData[idx].num == 4 ) return 2;

		if( m_statisticsData[idx].num == 2 ) num++;
	}

	return num;
}
}
