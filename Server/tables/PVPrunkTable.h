#ifndef __PVPRUNK_TABLE_H__
#define __PVPRUNK_TABLE_H__

#include "config.h"

class PvpRunkTable
{
public:
	struct PvpRunkDate
	{
		U32		runk_;
		U32		gradeMin_;
		U32		gradeMax_;
		U32		dropitem_;		//��
		U32		dropDay_;		//��
		U32		dropQuarter_;	//��
	};

public:
	static bool load(char const *fn);
	static bool check();
	static PvpRunkDate const * getPvpRunkById(U32 id);	//id�Ƕ�λ
public:
	static std::map< S32 , PvpRunkDate*>  data_;
};

class PvRrewardTable
{
public:
	struct PvrrewardData
	{
		U32		dropitem_;		//��
		U32		dropDay_;		//��
		U32		dropQuarter_;	//��	
		std::vector< std::pair<S32,S32> >	ranking_; //��������
	};
public:
	static bool load(char const *fn);
	static bool check();
	static PvrrewardData const * getPvrRunkById(U32 id);	//id������
public:
	static std::vector<PvrrewardData*>	data_;
};

#endif