#ifndef __ARTIFACT_LEVEL_H__
#define __ARTIFACT_LEVEL_H__


#include "config.h"

class ArtifactLevelTable
{
public:

	struct ArtifactPropData
	{
		PropertyType	type_;
		S32 	value_;
	};

	struct ArtifactLevelData
	{
		S32 id_;
		S32 exp_;
		S32  itemId_;
		JobType professionType_;

		std::vector<ArtifactPropData> propValue_;
	};

public:
	static bool load(char const *fn);
	static bool check();
	static ArtifactLevelData const * getArtifactById(S32 id,JobType job);

public:
	static std::map< S32 , std::vector<ArtifactLevelData*> >  data_;
};

class CrystalTable
{
public:
	struct SingletonData
	{
		U32					propLevel_;
		std::pair<U32,U32>	val_;
		U32					wt_;		//���Եȼ�Ȩ��	
	};
	struct CrystalTableData
	{
		U32					id_;
		U32					weight_;	//����Ȩ��
		PropertyType		type_;
		SingletonData		td_;
	};
public:
	static bool load(char const *fn);
	static bool check();
	static PropertyType randType();
	static void	randresetprop(COM_CrystalProp &cp);
	static void	randupprop(COM_CrystalProp &cp);
public:
	static std::vector< CrystalTableData* >  data_;
};

class CrystalUpTable
{
public:
	struct CrystalUpData
	{
		U32					level_;			//�ȼ�+1ȡֵ��ȡ����Ϊ����
		U32					neednum_;		//�������������
		U32					needgold_;
		U32					prob_;
	};
public:
	static bool load(char const *fn);
	static bool check();
	static CrystalUpData const* getdata(U32 level);
public:
	static std::vector< CrystalUpData* >  data_;
};

#endif