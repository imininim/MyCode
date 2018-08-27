#ifndef __timer_h__
#define __timer_h__

#include <functional>
#include <list>

#include <nocopyable.h>

typedef int time_type;
//typedef uint64_t time_type;

class TimerManager;

typedef std::function< void (void*) > Callback;

class Timer {
public:
	enum TimerType { ONCE, CIRCLE };
	Timer(TimerManager *tm):m_pTm(tm) {}
	void Stop();
	void Start(const Callback &cb, time_type t, TimerType type);
private:
	TimerManager *m_pTm;
	time_type m_time;
	TimerType m_type;
	Callback m_cb;

	friend class TimerManager;
};

class TimerManager:public Nocopyable {
public:
	TimerManager():m_alive(true) {}
	static time_type GetCurrentMillisecs();
	void DetectTime();
	void Loop();
	void SetAlive(bool alive) {
		m_alive = alive;
	}
private:
	void AddTimer(Timer *t);
	void DeleteTimer(Timer *t);

	struct ListEntry {
		time_type time;
		Timer *timer;
	};
private:
	bool m_alive;
	std::list<ListEntry> m_timerList;

	friend class Timer;
};

#endif
