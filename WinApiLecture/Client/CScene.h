#pragma once

#include "global.h"
#include "CMonFactory.h"

// ���漱��
class CObject;
class CTexture;

class CScene
{
private:
	vector<CObject*>	m_arrObj[(UINT)GROUP_TYPE::END];// ������Ʈ�� ���� �� ������ ���͸� �׷� ������ŭ ����
	wstring				m_strName; // Scene �̸�

	UINT				m_iTileX; // Ÿ�� ���� ����
	UINT				m_iTileY; // Ÿ�� ���� ����

	CObject*			m_pPlayer;	// Player

public:
	void SetName(const wstring& _strName) { m_strName = _strName; }
	const wstring& GetName() { return m_strName; }

	UINT GetTileX() { return m_iTileX; }
	UINT GetTileY() { return m_iTileY; }
	
	CObject* GetPlayer() { return m_pPlayer; }

	virtual void update();
	virtual void finalupdate();
	virtual void render(HDC _dc);

	void render_tile(HDC _dc);

	virtual void Enter() = 0; // �ش� Scene �� ���� �� ȣ��
	virtual void Exit() = 0;  // �ش� Scene �� Ż�� �� ȣ��
	
public:
	void AddObject(CObject* _pObj, GROUP_TYPE _eType){m_arrObj[(UINT)_eType].push_back(_pObj);}
	void RegisterPlayer(CObject* _pPlayer) { m_pPlayer = _pPlayer; }


	const vector<CObject*>& GetGroupObject(GROUP_TYPE _eType) { return m_arrObj[(UINT)_eType];}
	void DeleteGroup(GROUP_TYPE _eTarget);
	void DeleteAll();
	void CreateTile(UINT _iXCount, UINT _iYCount);
	void LoadTile(const wstring& _strRelativePath);

	vector<CObject*>& GetUIGroup() { return m_arrObj[(UINT)GROUP_TYPE::UI]; }

public:
	CScene();
	virtual ~CScene();
};

