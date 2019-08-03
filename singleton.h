#ifndef __SINGLETON__
#define __SINGLETON__

#include <assert.h>
#include <pthread.h>
#include <stdlib.h> // atexit
#include <boost/noncopyable.hpp>

namespace Detail
{
template<typename T>
struct HasNoDestory
{
	//This doesn't detect inherited member functions!
	//http://stackoverflow.com/questions/1966362/sfinae-to-check-for-inherited-member-functions
	template <typename C> static char test(decltype(&C::no_destroy));
	template <typename C> static int32_t test(...);
	const static bool value = sizeof(test<T>(0)) == 1;
};
}


template<typename T>
class Singleton : boost::noncopyable
{
public:
	static T& Instance()
	{
		pthread_once(&ponce_, &Singleton::Init);
		assert(instance_);
		return *instance_;
	}

private:
	Singleton() = delete;
	~Singleton() = delete;

	static void Init()
	{
		instance_ = new T;
		if (!Detail::HasNoDestory<T>::value)
		{
			::atexit(Singleton::Destory);
		}
	}

	static void Destory()
	{
		typedef char T_must_be_compelete_type[sizeof(T) == 0 ? -1 : 1];
		delete instance_;
		instance_ = nullptr;
	}

private:
	static T* instance_;
	static pthread_once_t ponce_;
};

template<typename T> 
T* Singleton<T>::instance_ = nullptr;

template<typename T> 
pthread_once_t Singleton<T>::ponce_ = PTHREAD_ONCE_INIT;


#endif //__SINGLETON__
