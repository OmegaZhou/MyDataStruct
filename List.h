#ifndef LIST_H_
#define LIST_H_
#include <iterator>
#include <iostream>
namespace MyDataStruct
{
	//A node of the list;
	//It includes pre-pointer and next-pointer
	template<class T>
	class ListNode
	{
	public:
		ListNode() :data_(nullptr), prev_(nullptr), next_(nullptr)
		{}
		ListNode(const T& data) :  prev_(nullptr), next_(nullptr){
			data_ = new T(data);
		}
		ListNode(const ListNode<T>& node) : data(node.data_), prev_(node.prev_), next_(node.next_)
		{}
		T* data_;
		ListNode* prev_;
		ListNode* next_;
	};

	template<class T>
	class List;

	//It's the iterator of the class template List;
	//And it can be used like using std::iteartor;
	template<class T>
	class ListIterator : public std::iterator<std::bidirectional_iterator_tag, T>
	{
		friend class List<T>;
	public:
		typedef T* pointer;
		typedef T& reference;
		ListIterator operator++(int);
		ListIterator& operator++();
		ListIterator operator--(int);
		ListIterator& operator--();
		bool operator==(const ListIterator<T>& iter) const;
		bool operator!=(const ListIterator<T>& iter) const;
		ListIterator<T>& operator=(const ListIterator<T>& iter);
		pointer operator->() const;
		reference operator*() const;
		ListIterator(const ListIterator<T>& iter) : node_(iter.node_)
		{}
		ListIterator() : node_(nullptr)
		{}
		ListIterator(ListNode<T>* const node) : node_(node)
		{}
	protected:
		ListNode<T>* node_;
	};

	template<class T>
	inline ListIterator<T> ListIterator<T>::operator++(int)
	{
		ListIterator temp = this;
		++(*this);
		return temp;
	}

	template<class T>
	inline ListIterator<T> & ListIterator<T>::operator++()
	{
		node_ = node_->next_;
		return *this;
	}

	template<class T>
	inline ListIterator<T> ListIterator<T>::operator--(int)
	{
		ListIterator temp = *this;
		--(*this);
		return temp;
	}

	template<class T>
	inline ListIterator<T> & ListIterator<T>::operator--()
	{
		node_ = node_->prev_;
		return *this;
	}

	template<class T>
	inline bool ListIterator<T>::operator==(const ListIterator<T>& iter) const
	{
		return node_ == iter.node_;
	}

	template<class T>
	inline bool ListIterator<T>::operator!=(const ListIterator<T>& iter) const
	{
		return !(iter == *this);
	}

	template<class T>
	inline ListIterator<T>& ListIterator<T>::operator=(const ListIterator<T>& iter)
	{
		node_ = iter.node_;
		return *this;
	}

	template<class T>
	inline typename ListIterator<T>::pointer ListIterator<T>::operator->() const
	{
		return &(operator*());
	}

	template<class T>
	inline typename ListIterator<T>::reference ListIterator<T>::operator*() const
	{
		return *(node_->data_);
	}

	template<class T>
	class ConstListIterator : public ListIterator<T>
	{
		friend class List<T>;
	public:
		typedef const T* pointer;
		typedef const T& reference;
		pointer operator->() const;
		reference operator*() const;
		ConstListIterator(const ConstListIterator<T>& iter) : ListIterator<T>(iter.node_)
		{}
		ConstListIterator() : ListIterator<T>(nullptr)
		{}
		ConstListIterator(ListNode<T>* const node) : ListIterator<T>(node)
		{}
	};

	template<class T>
	inline typename ConstListIterator<T>::pointer ConstListIterator<T>::operator->() const
	{
		return ListIterator<T>::node_->data_;
	}

	template<class T>
	inline typename ConstListIterator<T>::reference ConstListIterator<T>::operator*() const
	{
		return *(ListIterator<T>::node_->data_);
	}

	//The class template is used like stl::list; 
	template<class T>
	class List
	{
	public:
		enum Mode
		{
			SAFE_MODE = 0, EFFICIENCY_MODE = 1
		};
		typedef ListIterator<T> iterator;
		typedef ConstListIterator<T> const_iterator;
		typedef int size_type;
		typedef ListNode<T>* value_type;
		iterator begin();
		iterator end();
		const_iterator begin() const;
		const_iterator end() const;
		iterator insert(iterator position, const T& value, Mode mode = EFFICIENCY_MODE);
		iterator erase(iterator position, Mode mode = EFFICIENCY_MODE);
		void push_back(const T& value);
		size_type size() const;
		const T& front() const;
		const T& back() const;
		T& front();
		T& back();
		void clear();
		iterator find(const T& value) const;
		bool empty() const;
		List();
		List(const iterator& start, const iterator& end);
		List(const List<T>& list);
		List<T>& operator=(const List<T>& list);
		~List();
	private:
		ListNode<T>* node_;
		ListNode<T>* end_;
		size_type len_;
	};


	template<class T>
	inline typename List<T>::iterator List<T>::begin()
	{
		return iterator(node_);
	}

	template<class T>
	inline typename List<T>::iterator List<T>::end()
	{
		return iterator(end_);
	}

	template<class T>
	inline typename List<T>::const_iterator List<T>::begin() const
	{
		return const_iterator(node_);
	}

	template<class T>
	inline typename List<T>::const_iterator List<T>::end() const
	{
		return const_iterator(end_);
	}

	template<class T>
	inline typename List<T>::iterator List<T>::insert(List<T>::iterator position, const T & value, List<T>::Mode mode)
	{
		if (mode == SAFE_MODE) {
			for (auto i = begin(); i != end(); ++i) {
				if (position == i) {
					break;
				}
			}
			if (position != end()) {
				std::cout << "The position should be inserted is not existent;" << std::endl;
				return end();
			}
		}
		ListNode<T>* new_node = new ListNode<T>(value);
		if (new_node == nullptr) {
			std::cout << "Memory application is failed" << std::endl;
			exit(1);
		}
		if (position.node_->prev_) {
			position.node_->prev_->next_ = new_node;
		}
		new_node->prev_ = position.node_->prev_;
		new_node->next_ = position.node_;
		position.node_->prev_ = new_node;
		++len_;
		if (position.node_ == node_) {
			node_ = new_node;
		}
		return iterator(new_node);
	}

	template<class T>
	inline typename List<T>::iterator List<T>::erase(List<T>::iterator position, List<T>::Mode mode)
	{
		if (mode == SAFE_MODE) {
			for (auto i = begin(); i != end(); ++i) {
				if (position == i) {
					break;
				}
			}
			std::cout << "The position should be inserted is not existent;" << std::endl;
			return end();
		}
		position.node_->next_->prev_ = position.node_->prev_;
		ListNode<T>* result = position.node_->next_;
		--len_;
		if (position.node_ == node_) {
			node_ = result;
		} else {
			position.node_->prev_->next_ = position.node_->next_;
		}
		delete position.node_;
		return iterator(result);
	}

	template<class T>
	void List<T>::push_back(const T & value)
	{
		insert(end(), value);
	}

	template<class T>
	inline typename List<T>::size_type List<T>::size() const
	{
		return len_;
	}

	//Don't use it when empty;
	template<class T>
	inline const T & List<T>::front() const
	{

		return *begin();

	}

	//Don't use it when empty;
	template<class T>
	inline const T & List<T>::back() const
	{
		return *(--end());
	}

	//Don't use it when empty;
	template<class T>
	inline T & List<T>::front()
	{
		return *begin();
	}

	//Don't use it when empty;
	template<class T>
	inline T & List<T>::back()
	{
		return *(--end());
	}

	template<class T>
	inline void List<T>::clear()
	{
		iterator i = begin();
		ListNode<T>* temp = nullptr;
		while (i != end()) {
			temp = i.node_;
			++i;
			if (temp->data_ != nullptr) {
				delete temp->data_;
				temp->data_ = nullptr;
			}
			delete temp;
		}
		len_ = 0;
		end_->prev_ = nullptr;
		node_ = end_;
		
	}

	template<class T>
	inline typename List<T>::iterator List<T>::find(const T & value) const
	{
		for (auto i = begin(); i != end(); ++i) {
			if (*i == value) {
				return i;
			}
		}
		return end();
	}

	template<class T>
	inline bool List<T>::empty() const
	{
		return (len_ == 0);
	}

	template<class T>
	inline List<T>::List()
	{
		node_ = new ListNode<T>();
		if (node_ == nullptr) {
			std::cout << "Memory application is failed" << std::endl;
			exit(1);
		} else {
			end_ = node_;
			len_ = 0;
		}
	}

	template<class T>
	inline List<T>::List(const iterator & start, const iterator & end)
	{
		node_ = new ListNode<T>(0);
		if (node_ == nullptr) {
			std::cout << "Memory application is failed" << std::endl;
			exit(1);
		} else {
			end_ = node_;
		}
		for (auto i = start; i != end(); ++i) {
			push_back(*i);
		}
	}

	template<class T>
	inline List<T>::List(const List<T>& list)
	{
		node_ = new ListNode<T>();
		if (node_ == nullptr) {
			std::cout << "Memory application is failed" << std::endl;
			exit(1);
		} else {
			end_ = node_;
			len_ = 0;
		}
		*this = list;
	}

	template<class T>
	inline List<T>& List<T>::operator=(const List<T>& list)
	{

		for (auto i = list.begin(); i != list.end(); ++i) {
			auto temp = new T(*i);
			push_back(*i);
		}
		return *this;
	}

	template<class T>
	inline List<T>::~List()
	{
		clear();
		delete end_;
		end_ = nullptr;
		node_ = nullptr;
	}
}

#endif // !LIST_H_

