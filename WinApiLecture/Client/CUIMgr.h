#pragma once

class CUI;

class CUIMgr
{
	SINGLE(CUIMgr);
private:
	CUI* m_pFocusedUI;


public:
	void update();

	void SetFocusedUI(CUI* _pUI);
	
private:
	CUI* GetFocusedUI();
	CUI* GetTargetedUI(CUI* _pParentUI); // �θ� UI ������ ������ Ÿ���� �� UI�� ã�Ƽ� ��ȯ�Ѵ�.

};

