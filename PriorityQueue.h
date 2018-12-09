#ifndef PRIORITY_QUEUE_H_
#define PRIORITY_QUEUE_H_

#include "../generic_component/Sort.h"

namespace MyDataStruct
{
	template<class T>
	class PriorityQueue
	{
	public:
		PriorityQueue();
		~PriorityQueue();
		T& top();
		void push(const T& val);
		void pop();
		int size();
		bool empty();
		void clear();
	private:
		T * mem_;
		int size_;
		int max_size_;
	};
	template<class T>
	inline PriorityQueue<T>::PriorityQueue()
	{
		max_size_ = 16;
		mem_ = new T[16];
		size_ = 0;
	}
	template<class T>
	inline PriorityQueue<T>::~PriorityQueue()
	{
		delete[] mem_;
		mem_ = nullptr;
	}
	template<class T>
	inline T & PriorityQueue<T>::top()
	{
		return mem_[0];
	}
	template<class T>
	inline void PriorityQueue<T>::push(const T & val)
	{
		if (size_ == max_size_) {
			T* temp = new T[2 * max_size_];
			for (int i = 0; i < max_size_; ++i) {
				temp[i] = mem_[i];
			}
			delete[] mem_;
			mem_ = temp;
			max_size_ *= 2;
		}
		mem_[size_] = val;
		int k = size_;
		++size_;
		while (k > 0) {
			if (mem_[k] < mem_[(k - 1) / 2]) {
				swap(mem_[k], mem_[(k - 1) / 2]);
				k = (k - 1) / 2;
			} else {
				break;
			}
		}
	}
	template<class T>
	inline void PriorityQueue<T>::pop()
	{
		--size_;
		swap(mem_[0], mem_[size_]);
		int k = 0;
		while (k < size_) {
			int temp = k;
			if (k * 2 + 1 < size_) {
				if (mem_[2 * k + 1] < mem_[temp]) {
					temp = 2 * k + 1;
				}
			}
			if (k * 2 + 2 < size_) {
				if (mem_[2 * k + 2] < mem_[temp]) {
					temp = 2 * k + 2;
				}
			}
			if (temp == k) {
				break;
			}
			swap(mem_[k], mem_[temp]);
			k = temp;
		}
	}
	template<class T>
	inline int PriorityQueue<T>::size()
	{
		return size_;
	}
	template<class T>
	inline bool PriorityQueue<T>::empty()
	{
		return size_ == 0;
	}
	template<class T>
	inline void PriorityQueue<T>::clear()
	{
		size_ = 0;
	}
}

#endif // !PRIORITY_QUEUE_H_
