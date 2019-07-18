#pragma once

#include <vector>
#include "HuSplitTbl.h"
#include "HuDefine.h"

struct CardValue
{
	int32_t value;
	int32_t num;
	void clear(){
		value = 0;
		num = 0;
	}
};

//typedef map<uint32_t,uint32_t> TblMap;

typedef vector<CardValue> TblMap;

namespace NHuSplit
{

class HuSplitTbl;

class HuSplit
{
public:
	HuSplit();
	~HuSplit();

public:
	void init(const string &path , const bool is_eye = false);
	bool CheckHu( char *pCard );

private:
	bool splitCard( CardValue *cardValue , uint32_t eye_num );
	uint32_t splitZiCard( );
	void StatisticsCard(char * pCards);

private:
	HuSplitTbl m_splitTbl;
	CardValue m_statisticsData[MAX_CARD_NUM];
	int32_t zi_index;
};
}