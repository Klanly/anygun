#ifndef __GZIP_H__
#define __GZIP_H__
#ifdef _WIN32
	#include "zlib/zlib.h"
#else
	#include "zlib.h"
#endif 
/* Compress gzip data */
/* data ԭ���� ndata ԭ���ݳ��� zdata ѹ�������� nzdata ѹ���󳤶� */
int gzcompress(Bytef *data, uLong ndata, Bytef *zdata, uLong *nzdata);

/* Uncompress gzip data */
/* zdata ���� nzdata ԭ���ݳ��� data ��ѹ������ ndata ��ѹ�󳤶� */
int gzdecompress(Byte *zdata, uLong nzdata, Byte *data, uLong *ndata);

int isgzcompress(Byte id1, Byte id2);


#endif // __GZIP_H__