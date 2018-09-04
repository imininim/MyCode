#ifndef __global_timer_h__
#define __global_timer_h__

#include <timer.h>

class GlobalTimer {
public:
	static TimerManager* GetTimer() {
		if (m_tm == nullptr) {
			tm = new TimerManager();
			tm->Loop();
		}
		return m_tm;
	}
private:
	GlobalTimer():m_tm(nullptr) {}
	TimerManager *m_tm;
};

#endif
