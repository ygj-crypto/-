#include "HuSplitTbl.h"
#include "HuDefine.h"

#define MAX_KEY_LEN 1024

using namespace std;

namespace NHuSplit
{

HuSplitTbl::HuSplitTbl()
{
	m_huEyeTbl.clear();
	m_huTbl.clear();
}

HuSplitTbl::~HuSplitTbl()
{
	m_huEyeTbl.clear();
	m_huTbl.clear();
}

void HuSplitTbl::initTable( const string& path , const bool is_eye)
{
	char szKey[MAX_KEY_LEN] = {0};
	FILE *fp = fopen( path.c_str(), "r");
	if( fp == NULL ){

		printf("failed top open %s\n" , path.c_str());
		return;
	}

	while(!feof(fp)){

		memset(szKey, 0, sizeof(szKey));
		fgets(szKey, sizeof(szKey)-1, fp );
		if(is_eye)
		{
			m_huEyeTbl[stoi(szKey)] = true;
		}
		else
		{
			m_huTbl[stoi(szKey)] = true;
		}
	}

	fclose(fp);
}

uint32_t HuSplitTbl::CheckTable( const uint32_t key , const bool is_eye)
{
	uint32_t value = 0;
	if(is_eye)
	{
		auto it = m_huEyeTbl.find(key);
		if( it != m_huEyeTbl.end() ) value = it->second;
	}
	else
	{
		auto it = m_huTbl.find(key);
		if( it != m_huTbl.end() ) value = it->second;
	}

	return value;
}

};