#pragma once

//Meyer's // thread safe, ��ӹ޴� Manager ��ü�� ������ process�� �����ϱ� ������.
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