#include "../generic_component/List.h"
#ifndef QUEUE_H_
#define QUEUE_H_
namespace MyDataStruct
{
	template<class T>
	class Queue
	{
		Queue() = default;
		T top();
		void push(const T& t);
		void pop();
		bool empty();
	private:
		List<T> data_;
	};
	template<class T>
	inline T Queue<T>::top()
	{
		return *data_.begin();
	}
	template<class T>
	inline void Queue<T>::push(const T & t)
	{
		data_.push_back(t);
	}
	template<class T>
	inline void Queue<T>::pop()
	{
		data_.erase(data_.begin());
	}
	template<class T>
	inline bool Queue<T>::empty()
	{
		return data_.empty();
	}
}
#endif // !QUEUE_H_

