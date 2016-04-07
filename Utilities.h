#pragma once

#include <vector>
#include <ctime>

namespace mvc {

// Simple timer implementation
class Timer {
	clock_t counter;
public:
	Timer(): counter(0) {};

	float tick() {
		clock_t tick = std::clock();
		float elapsed = (tick - counter)/1000.0f;
		counter = tick;
		return elapsed;
	}
};

// Singleton template baseclass
template <class T> class SingletonBase {
public:
	SingletonBase()		{mp = (T*)this;};
	~SingletonBase()	{mp = 0;};
	static T*	get()	{return mp;}

private:
	static T*	mp;
};
template <class T> T* SingletonBase<T>::mp = 0;

// Utility to remove all those indexes from myVector that are equal to myElement
template <class T>
void removeElements(std::vector<T>& myVector, const T& myElement) {
	std::vector<T>::iterator i;

	while (1) {
		i = find(myVector.begin(),myVector.end(),myElement);
		if (i==myVector.end()) break;
		myVector.erase(i);
	}
}

}