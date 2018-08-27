#include <timer.h>

#include <sys/time.h>

#include <thread>
#include <chrono>

using namespace std;

void Timer::Stop() {
	m_pTm->DeleteTimer(this);
}

void Timer::Start(const Callback &cb, time_type t, TimerType type) {
	m_type = type;
	m_time = t;
	m_cb = cb;
	m_pTm->AddTimer(this);
}

time_type TimerManager::GetCurrentMillisecs() {
	timeval tv;
	::gettimeofday(&tv, 0);
	time_type ret = tv.tv_sec;
	return ret*1000 + tv.tv_usec/1000;
}

void TimerManager::DetectTime() {
	time_type now = GetCurrentMillisecs();
	for (auto it = m_timerList.begin(); it != m_timerList.end();) {
		if ((*it).time < now) {
			(*it).timer->m_cb(nullptr);
			if ((*it).timer->m_type == Timer::TimerType::ONCE) {
				DeleteTimer((*(it++)).timer);
			} else {
				(*it).time = (*it).time + (*it).timer->m_time;
				++it;
			}
		} else {
			++it;
		}
	}
}

void TimerManager::AddTimer(Timer *t) {
	time_type now = GetCurrentMillisecs();
	m_timerList.push_back(ListEntry{((t->m_time)+now), t});
}

void TimerManager::DeleteTimer(Timer *t) {
	for (auto it = m_timerList.begin(); it != m_timerList.end(); ++it) {
		if ((*it).timer == t) {
			m_timerList.erase(it);
			break;
		}
	}
}

void TimerManager::Loop() {
	while(m_alive) {
		DetectTime();
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}
