#ifndef TRCPARSER_H
#define TRCPARSER_H

#include "CVector3f.h"
#include "def.h"
#include <stdio.h>

#ifdef MS_BUILD_ENV
#pragma warning(disable:4996)
#endif

/*
 *@brief TRC File header, call alloc to allocate memory ,dealloc to release.
 **/
struct HTRCHeader
{
	int m_pathFileType;
	char m_XYZ[3];
	char m_fileName[256];
	int m_dataRate;
	int m_camerRate;
	int m_numFrames;
	int m_numMarkers;
	char m_units[256];
	int m_origDataRate;
	int m_origStartFrame;
	int m_origNumFrames;

	int *m_frameSeq;//size m_numFrames
        double *m_timeSeq;//size m_numFrames
        int *m_markerSeq;//size m_numMarkers

	HTRCHeader()
	{
		m_pathFileType = 0;
		m_dataRate = 0;
		m_camerRate = 0;
		m_numFrames = 0;
		m_numMarkers = 0;
		m_origDataRate = 0;
		m_origStartFrame = 0;
		m_origNumFrames = 0;

		//pointer
		m_frameSeq = 0;
		m_timeSeq = 0;
		m_markerSeq = 0;

		m_XYZ[0] = 'X'; m_XYZ[1] = 'Y';m_XYZ[2] = 'Z';
	}
	~HTRCHeader()
	{
		assert(m_frameSeq == 0);
		assert(m_timeSeq == 0);
		assert(m_markerSeq == 0);
	}
	void alloc()
	{
		m_frameSeq = new int[m_numFrames];
                m_timeSeq = new double[m_numFrames];
		m_markerSeq = new int[m_numMarkers];
	}
	void dealloc()
	{
		delete [] m_frameSeq; m_frameSeq = 0;
		delete [] m_timeSeq; m_timeSeq = 0;
		delete [] m_markerSeq; m_markerSeq = 0;
	}
};


class CTRCParser
{
public:
	CTRCParser(void);
	~CTRCParser(void);
	void getTRCHeader(const char *dir,HTRCHeader *pHead);
        void parse(const char *dir,HTRCHeader *pHead,double *mat);
        void resotre(const char *dir,const HTRCHeader *pHead,const double *mat);
};
#endif