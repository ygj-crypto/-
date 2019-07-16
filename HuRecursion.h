#pragma once

#define START_FLOWER_INDEX 34  //花牌开始下标
#define START_ZI_INDEX 27  	   //字牌开始下标
#define START_WAN_INDEX 0      //万牌开始下标
#define START_TIAO_INDEX 9     //条牌开始下标
#define START_TONG_INDEX 18    //筒牌开始下标

#define MAX_ONE_CARD_NUM 9     //万，索，筒的个数
#define MAX_GUI_NUM 4          //鬼的最多个数

#define MAX_CARD_TYPE 3		   //万，索，筒三种类型牌

#define MAX_OPT_NUM 3		   //形态长度

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
};

}
