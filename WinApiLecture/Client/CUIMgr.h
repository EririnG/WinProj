#pragma once

class CUI;

class CUIMgr
{
	SINGLE(CUIMgr);

public:
	void update();

private:
	CUI* GetTargetedUI(CUI* _pParentUI); // �θ� UI ������ ������ Ÿ���� �� UI�� ã�Ƽ� ��ȯ�Ѵ�.

};

