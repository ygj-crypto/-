#pragma once
#include "HuDefine.h"

namespace NHuRecurSion
{

//胡的形态
struct HuType
{
	char num[MAX_OPT_NUM];
	bool eye;
};

class CHuRecursion
{
public:
	CHuRecursion();
	~CHuRecursion();
	
public:
	//检测是否可以胡,如果没有鬼牌 guiIndex，填-1
	bool CheckCanHu(char * pCards , int guiIndex[MAX_GUI_NUM] , int guiIndexNum = 0);
private:
	//pCards牌，HasEyes是否已经有眼，nHunCount癞子个数，nNeedHun需要癞子的个数
	//字牌
	bool CheckZi(char * pCards, bool& HasEyes, int& nGuiCount, int& nNeedGui );

	//万，索，筒
	bool CheckColor(char * pCards, bool& HasEyes, int& nGuiCount, int& nNeedGui );

	//鬼的个数
	int GuiNum(char *pCards , int guiIndex[MAX_GUI_NUM]);

	//@startIndex开始下标
	bool CheckHu( char * pCards, int startIndex, bool& HasEyes, int& nGuiCount);

	//七对
	bool CheckPair(char * pCards, int& nGuiCount, int& nNeedGui );
	//十三幺
	bool CheckThirteen(char * pCards, int& nGuiCount, int& nNeedGui );
	//获取胡形态
	HuType* GetHuType( char cardValue , int &optNum );

	//统计牌值
	void StatisticsCard(char * pCards , char *cardValue);
};

}