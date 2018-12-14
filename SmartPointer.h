#ifndef SMART_POINTER_H_
#define SMART_POINTER_H_

namespace MyDataStruct
{
	template<class T>
	class SmartPointer
	{
	public:
		SmartPointer();
		SmartPointer(const SmartPointer& i);
		SmartPointer(const T& val);
		SmartPointer& operator=(const SmartPointer& i);
		T& operator*();
		const T& operator*() const;
		T* operator->();
		const T* operator->() const;
		~SmartPointer();
	private:
		int* count_;
		T* data_;
	};
	template<class T>
	inline SmartPointer<T>::SmartPointer() : count_(nullptr), data_(nullptr)
	{}
	template<class T>
	inline SmartPointer<T>::SmartPointer(const SmartPointer & i)
	{
		*this = i;
		
	}
	template<class T>
	inline SmartPointer<T>::SmartPointer(const T & val)
	{
		count_ = new int(1);
		data_ = new T(val);
	}
	template<class T>
	inline SmartPointer<T> & SmartPointer<T>::operator=(const SmartPointer & i)
	{
		if (i.data_) {
			++(*(i.count_));
		}
		if (data_) {
			--(*count_);
			if (!(*count_)) {
				delete data_;
				delete count_;
				this->data_ = nullptr;
				this->count_ = nullptr;
			}
		}
		this->data_ = i.data_;
		this->count_ = i.count_;
	}
	template<class T>
	inline T & SmartPointer<T>::operator*()
	{
		return *data_;
	}
	template<class T>
	inline const T & SmartPointer<T>::operator*() const
	{
		return *data_;
	}
	template<class T>
	inline T * SmartPointer<T>::operator->()
	{
		return data_;
	}
	template<class T>
	inline const T * SmartPointer<T>::operator->() const
	{
		return data_;
	}
	template<class T>
	inline SmartPointer<T>::~SmartPointer()
	{
		if (data_) {
			--(*count_);
			if (!(*count_)) {
				delete data_;
				delete count_;
				this->data_ = nullptr;
				this->count_ = nullptr;
			}
		}
	}
}
#endif // !SMART_POINTER_H_
