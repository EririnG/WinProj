#pragma once
class CTimeMgr
{
	SINGLE(CTimeMgr);
private:

	LARGE_INTEGER m_llCurCount;
	LARGE_INTEGER m_llFrequency;
	// FPS (Frame Per Sec)
	// 1 �����Ӵ� �ð� Delta Time

public:
	void init();

};

