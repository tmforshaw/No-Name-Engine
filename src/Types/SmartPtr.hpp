#pragma once

template<typename T>
class SmartPtr
{
private:
	T* data;

public:
	SmartPtr()
	{
		// Allocate the memory
		data = (T*)malloc( sizeof( T ) );
	}

	SmartPtr( const T& value )
	{
		// Set the value of data
		data = new T( value );
	}

	~SmartPtr()
	{
		delete data;
	}

	void operator=( const T& value )
	{
		// Set the value of data
		*data = value;
	}

	inline T Data()
	{
		return *data;
	}
};