#ifndef __nocpoyable_h__
#define __nocpoyable_h__

class Nocopyable {
public:
	Nocopyable() {}
private:
	Nocopyable(const Nocopyable &p);
};

#endif
