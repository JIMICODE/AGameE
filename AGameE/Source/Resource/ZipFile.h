#pragma once
#ifndef ZIPFILE_H_
#define ZIPFILE_H_

#include"..\Common\Utility.h"
#include<zlib.h>

class ZipFile
{
public:
	ZipFile(){}
	virtual ~ZipFile() { m_nEntries = 0; m_pFile = NULL; m_pDirData = NULL; }

	bool Init(const std::wstring &resFileName);
	void End();

	int GetNumFiles()const { return m_nEntries; }
	std::string GetFileName(int i) const;
	int GetFileLen(int i) const;
	bool ReadFile(int i, void *pBuf);

	//Added to show multi_threaded decompression
	bool ReadLargeFile(int i, void *pBuf, void(*progressCallback)(int, bool &));
	std::optional<int> Find(const std::string &path) const;

	//ZipContensMap m_ZipContensMap;
private:
	struct TZipDirHeader;
	struct TZipDirFileHeader;
	struct TZipLocalHeader;

	FILE *m_pFile; //zip file
	char *m_pDirData; //Raw data buffer
	int m_nEntries; //number of entries

	//Pointers to the dir entries in pDirData.
	const TZipDirFileHeader **m_papDir;
};

//Basic types
typedef unsigned long dword;
typedef unsigned short word;
typedef unsigned char byte;

//Zip file structure. Note these have to be packed.

#pragma pakc(1)
struct ZipFile::TZipLocalHeader
{
	enum 
	{
		SIGNATURE = 0x04034b50
	};
	dword sig;
	word version;
	word flag;
	word compresson; //COMP_XXXX
	word modTime;
	word modDate;
	dword crc32;
	dword cSize;
	dword ucSize;
	word fnameLen; //Filename string follows header.
	word xtraLen; //Extra field follows filename;
};

struct ZipFile::TZipDirHeader
{
	enum
	{
		SINGNATURE = 0x06054b50
	};
	dword sig;
	word nDisk;
	word nStartDisk;
	word nDirEntries;
	word totalDirEntries;
	dword disSize;
	dword dirOffset;
	word cmntLen;
};

struct ZipFile::TZipDirFileHeader
{
	enum
	{
		SIGNATURE = 0x02014b50
	};
	dword sig;
	word verMade;
	word verNeeded;
	word flag;
	word compression; //COMP_XXXX
	word modTime;
	word modDate;
	dword crc32;
	dword cSize; //compressed size
	dword ucSize; //Uncompressed size
	word fnameLen; //Filename string follows header.
	word xtraLen; //extra field follows filename.
	word cmnLen; //comment field follows extra field.
	word disStart;
	word intAttr;
	dword extAttr;
	dword hdrOffset;

	char *GetName() const { return (char*)(this + 1); }
	char *GetExtra() const { return GetName() + fnameLen; }
	char *GetComment() const { return GetExtra() + xtraLen; }
};

#pragma pack()

#endif // !ZIPFILE_H_
