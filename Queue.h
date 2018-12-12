#ifndef QUEUE_H_
#define QUEUE_H_

#include "../generic_component/List.h"

namespace MyDataStruct
{
	template<class T>
	class Queue
	{
		Queue() = default;
		const T& top() const;
		void push(const T& t);
		void pop();
		bool empty() const;
		void clear();
		int size() const;
	private:
		List<T> data_;
	};
	template<class T>
	inline const T& Queue<T>::top() const
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
	inline bool Queue<T>::empty() const
	{
		return data_.empty();
	}
	template<class T>
	inline void Queue<T>::clear()
	{
		data_.clear();
	}
	template<class T>
	inline int Queue<T>::size() const
	{
		return data_.size();
	}
}
#endif // !QUEUE_H_

