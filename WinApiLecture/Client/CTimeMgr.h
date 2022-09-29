#pragma once

class CTimeMgr
{
	SINGLE(CTimeMgr);
private:

	LARGE_INTEGER m_llCurCount;
	LARGE_INTEGER m_llPrevCount;
	LARGE_INTEGER m_llFrequency;

	double		  m_dDT;// ������ ���� �ð���
	double		  m_dACC; // 1�� üũ�� ���� ���� �ð�
	UINT		  m_iCallCount; //�Լ� ȣ�� ȸ�� üũ
	UINT		  m_iFPS;  // �ʴ� ȣ��Ƚ��
	
	// FPS (Frame Per Sec)
	// 1 �����Ӵ� �ð� Delta Time

public:
	void init();
	void update();


public:
	double	GetDT() { return m_dDT; }
	float	GetfDT() { return (float)m_dDT; }
	double	GetDAcc() { return m_dACC; }
	int		GetCallCount() { return m_iCallCount; }

};

