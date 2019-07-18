#pragma once

#include <stdio.h>
#include <string.h>
#include <map>
#include <unordered_map>
#include <iostream>

using namespace std;

typedef unordered_map<uint32_t, uint32_t> HuTblMap;

namespace NHuSplit
{

class HuSplitTbl
{
public:
	HuSplitTbl();
	~HuSplitTbl();
public:
	void initTable( const string& path , const bool is_eye = false );
	uint32_t CheckTable( const uint32_t key ,  const bool is_eye = false );

private:
	HuTblMap m_huTbl;
	HuTblMap m_huEyeTbl;
};

}

