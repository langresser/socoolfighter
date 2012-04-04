#pragma once

template <class T>
class Singleton
{
public:
	static T& instance()
	{
		static T s_instance;
		return s_instance;
	}

protected:
	Singleton(){};
	virtual ~Singleton() {};

	Singleton(const Singleton<T>&);
	Singleton<T>& operator=(const Singleton<T>&);
};