#pragma once

//Meyer's // thread safe, 상속받는 Manager 객체의 수명은 process와 동일하기 때문에.
template <typename T> 
class Singleton
{
public:
	Singleton() = default;
	~Singleton() = default; 

public:
	static T& Instance()
	{
		static T p_Instance;
		return p_Instance;
	}



public:
	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;
};