#pragma once

#include <vector>
#include "HuSplitTbl.h"
#include "HuDefine.h"

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
