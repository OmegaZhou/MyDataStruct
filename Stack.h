#ifndef STACK_H_
#define STACK_H_

#include "List.h"

namespace MyDataStruct
{
	template<class T>
	class Stack
	{
	public:
		Stack();
		const T& top() const;
		void push(const T& val);
		void pop();
		void clear();
		int size() const;
		bool empty() const;
	private:
		List<T> data_;
	};
	template<class T>
	inline Stack<T>::Stack()
	{}
	template<class T>
	inline const T & Stack<T>::top() const
	{
		return *data_.begin();
	}
	template<class T>
	inline void Stack<T>::push(const T & val)
	{
		data_.insert(data_.begin(), val);
	}
	template<class T>
	inline void Stack<T>::pop()
	{
		data_.erase(data_.begin());
	}
	template<class T>
	inline void Stack<T>::clear()
	{
		data_.clear();
	}
	template<class T>
	inline int Stack<T>::size() const
	{
		return data_.size();
	}
	template<class T>
	inline bool Stack<T>::empty() const
	{
		return data_.empty();
	}
}

#endif // !STACK_H_