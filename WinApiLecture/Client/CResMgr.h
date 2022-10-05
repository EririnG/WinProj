#pragma once
#include"CTexture.h"

class CResMgr
{
	SINGLE(CResMgr);
private:
	map<wstring, CTexture*> m_mapTex; 

public:
	CTexture* LoadTexture(const wstring& _strKey, const wstring& _strRelativePath);
	CTexture* FindTexture(const wstring& _strKey);

};

