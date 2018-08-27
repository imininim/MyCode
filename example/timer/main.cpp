#include "timer.h"
#include <iostream>
using namespace std;

void func1(void *) {
	cerr << "1111111" << endl;
}

void func2(void *) {
	cerr << "2222222" << endl;
}

int main() {
	TimerManager tm;
	Timer t(&tm);
	t.Start(func1, 2000, Timer::TimerType::ONCE);
	Timer t2(&tm);
	t2.Start(func2, 1000, Timer::TimerType::CIRCLE);

	tm.Loop();
	return 0;
}
