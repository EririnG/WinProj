#pragma once

// 전방선언
class CObject;
class CTexture;

class CScene
{
private:
	vector<CObject*> m_arrObj[(UINT)GROUP_TYPE::END];// 오브젝트를 저장 및 관리할 벡터를 그룹 개수만큼 선언
	wstring			 m_strName; // Scene 이름
	CTexture*		 m_pTex;

public:
	void SetName(const wstring& _strName) { m_strName = _strName; }
	const wstring& GetName() { return m_strName; }

	

	virtual void update();
	virtual void finalupdate();
	virtual void render(HDC _dc);

	void SetScene(CTexture* _cTexture) { m_pTex = _cTexture; }
	CTexture* GetScene(){return m_pTex;}

	virtual void Enter() = 0; // 해당 Scene 에 진입 시 호출
	virtual void Exit() = 0;  // 해당 Scene 을 탈출 시 호출
	
public:
	void AddObject(CObject* _pObj, GROUP_TYPE _eType)
	{
		m_arrObj[(UINT)_eType].push_back(_pObj);
	}

	const vector<CObject*>& GetGroupObject(GROUP_TYPE _eType) { return m_arrObj[(UINT)_eType];}
	void DeleteGroup(GROUP_TYPE _eTarget);
	void DeleteAll();


public:
	CScene();
	virtual ~CScene();
};

