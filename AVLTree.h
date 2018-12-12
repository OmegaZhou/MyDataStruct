#ifndef AVL_TREE_H_
#define AVL_TREE_H_

namespace MyDataStruct
{
	template<class T>
	struct AVLTreeNode
	{
		AVLTreeNode(const T& val);
		T val_;
		AVLTreeNode<T>* left_;
		AVLTreeNode<T>* right_;
		int bf_;
	};
	template<class T>
	inline AVLTreeNode<T>::AVLTreeNode(const T& val) : val_(val), left_(nullptr), right_(nullptr), bf_(0)
	{}

	template<class T>
	class AVLIterator
	{
	public:
		T & operator*();
		T* operator->();
		bool operator==(const AVLIterator<T>& i);
		bool operator!=(const AVLIterator<T>& i);
		AVLIterator(AVLTreeNode<T>* const pointer);
	private:
		AVLTreeNode<T>* node_;
	};


	template<class T>
	inline T & AVLIterator<T>::operator*()
	{
		return node_->val_;
	}
	template<class T>
	inline T * AVLIterator<T>::operator->()
	{
		return &(operator*());
	}
	template<class T>
	inline bool AVLIterator<T>::operator==(const AVLIterator<T>& i)
	{
		return i.node_ == node_;
	}
	template<class T>
	inline bool AVLIterator<T>::operator!=(const AVLIterator<T>& i)
	{
		return !(operator==(i));
	}
	template<class T>
	inline AVLIterator<T>::AVLIterator(AVLTreeNode<T>* const pointer) : node_(pointer)
	{}


	template<class T>
	class AVLTree
	{
	public:
		typedef AVLIterator<T> iterator;
		AVLTree();
		~AVLTree();
		void insert(const T& val);
		void erase(iterator iter);
		iterator end() const;
		iterator begin() const;
		T& back() const;
		iterator find(const T& val) const;
		void clear();
		int size() const;
		bool empty() const;
	private:
		AVLTreeNode<T>* root_;
		int size_;
		static void clear(AVLTreeNode<T>* &root);
		bool insert(const T&val, AVLTreeNode<T>* &root);
		bool erase(const T&val, AVLTreeNode<T>* &root);
		static void left_rotate(AVLTreeNode<T>* &root);
		static void right_rotate(AVLTreeNode<T>* &root);
		static void left_then_right_rotate(AVLTreeNode<T>* &root);
		static void right_then_left_rotate(AVLTreeNode<T>* &root);
	};

	template<class T>
	inline AVLTree<T>::AVLTree() : root_(nullptr), size_(0)
	{}

	template<class T>
	AVLTree<T>::~AVLTree()
	{
		clear();
	}

	template<class T>
	inline void AVLTree<T>::insert(const T & val)
	{
		insert(val, root_);
	}

	template<class T>
	inline void AVLTree<T>::erase(iterator iter)
	{
		T val = *iter;
		erase(val, root_);
	}

	template<class T>
	inline typename AVLTree<T>::iterator AVLTree<T>::end() const
	{
		return iterator(nullptr);
	}

	template<class T>
	inline typename AVLTree<T>::iterator AVLTree<T>::begin() const
	{
		AVLTreeNode<T>* temp = root_;
		while (temp&&temp->left_) {
			temp = temp->left_;
		}
		return iterator(temp);
	}

	template<class T>
	inline T & AVLTree<T>::back() const
	{
		AVLTreeNode<T>* temp = root_;
		while (temp->right_) {
			temp = temp->right_;
		}
		return temp->val_;
	}

	template<class T>
	inline typename AVLTree<T>::iterator AVLTree<T>::find(const T & val) const
	{
		AVLTreeNode<T>* re = root_;
		while (re) {
			if (val < re->val_) {
				re = re->left_;
			} else if (re->val_ < val) {
				re = re->right_;
			} else {
				break;
			}
		}
		return iterator(re);
	}

	template<class T>
	inline void AVLTree<T>::clear()
	{
		clear(root_);
		size_ = 0;
	}

	template<class T>
	inline int AVLTree<T>::size() const
	{
		return size_;
	}

	template<class T>
	inline bool AVLTree<T>::empty() const
	{
		return size_ == 0;
	}

	template<class T>
	inline void AVLTree<T>::clear(AVLTreeNode<T>* &root)
	{
		if (!root) {
			return;
		}
		if (root->left_) {
			clear(root->left_);
		}
		if (root->right_) {
			clear(root->right_);
		}
		delete root;
		root = nullptr;
	}

	template<class T>
	inline bool AVLTree<T>::insert(const T & val, AVLTreeNode<T>* &root)
	{
		if (root == nullptr) {
			root = new AVLTreeNode<T>(val);
			++size_;
			return true;
		}
		if (val < root->val_) {
			if (insert(val, root->left_)) {
				root->bf_ -= 1;
				switch (root->bf_) {
				case -1:
					return true;
					break;
				case -2:
					if (root->left_->bf_ == -1) {
						right_rotate(root);
					} else {
						left_then_right_rotate(root);
					}
					break;
				default:
					break;
				}
			}
		} else if (root->val_ < val) {
			if (insert(val, root->right_)) {
				root->bf_ += 1;
				switch (root->bf_) {
				case 1:
					return true;
					break;
				case 2:
					if (root->right_->bf_ == 1) {
						left_rotate(root);
					} else {
						right_then_left_rotate(root);
					}
					break;
				default:
					break;
				}
			}
		}
		return false;
	}

	template<class T>
	inline bool AVLTree<T>::erase(const T & val, AVLTreeNode<T> * &root)
	{
		if (root == nullptr) {
			return false;
		}
		if (val < root->val_) {
			if (erase(val, root->left_)) {
				root->bf_ += 1;
				switch (root->bf_) {
				case 0:
					return true;
					break;
				case 2:
					if (root->right_->bf_ == 0) {
						left_rotate(root);
						root->bf_ = -1;
						root->left_->bf_ = 1;
						return false;
					} else if (root->right_->bf_ == 1) {
						left_rotate(root);
						return true;
					} else {
						right_then_left_rotate(root);
						return true;
					}
					break;
				default:
					break;
				}
			}
		} else {
			if (root->val_ < val) {
				if (erase(val, root->right_)) {
					root->bf_ -= 1;
				}
			} else {
				if (root->left_ == nullptr && root->right_ == nullptr) {
					delete root;
					root = nullptr;
					--size_;
					return true;
				} else if (root->left_ == nullptr) {
					root->val_ = root->right_->val_;
					delete root->right_;
					root->right_ = nullptr;
					root->bf_ = 0;
					--size_;
					return true;
				} else if (root->right_ == nullptr) {
					root->val_ = root->left_->val_;
					delete root->left_;
					root->left_ = nullptr;
					root->bf_ = 0;
					--size_;
					return true;
				} else {
					AVLTreeNode<T>* temp = root->right_;
					while (temp->left_) {
						temp = temp->left_;
					}
					T v = temp->val_;
					root->val_ = v;
					if (erase(v, root->right_)) {
						root->bf_ -= 1;
					}
				}
			}
			switch (root->bf_) {
			case 0:
				return true;
				break;
			case -2:
				if (root->left_->bf_ == 0) {
					right_rotate(root);
					root->bf_ = 1;
					root->right_->bf_ = -1;
					return false;
				} else if (root->left_->bf_ == -1) {
					right_rotate(root);
					return true;
				} else {
					left_then_right_rotate(root);
					return true;
				}
				break;
			default:
				break;
			}

		}
		return false;
	}

	template<class T>
	inline void AVLTree<T>::left_rotate(AVLTreeNode<T>* &root)
	{
		AVLTreeNode<T>* origin_root = root;
		root = root->right_;
		origin_root->right_ = root->left_;
		root->left_ = origin_root;
		root->bf_ = 0;
		origin_root->bf_ = 0;
	}

	template<class T>
	inline void AVLTree<T>::right_rotate(AVLTreeNode<T>* &root)
	{
		AVLTreeNode<T>* origin_root = root;
		root = root->left_;
		origin_root->left_ = root->right_;
		root->right_ = origin_root;
		root->bf_ = 0;
		origin_root->bf_ = 0;
	}

	template<class T>
	inline void AVLTree<T>::left_then_right_rotate(AVLTreeNode<T>* &root)
	{
		AVLTreeNode<T>* origin_root = root;
		AVLTreeNode<T>* origin_left = root->left_;
		root = origin_left->right_;
		origin_left->right_ = root->left_;
		origin_root->left_ = root->right_;
		root->left_ = origin_left;
		root->right_ = origin_root;
		origin_left->bf_ = (((root->bf_) == 1) ? -1 : 0);
		origin_root->bf_ = (((root->bf_) == -1) ? 1 : 0);
		root->bf_ = 0;
	}

	template<class T>
	inline void AVLTree<T>::right_then_left_rotate(AVLTreeNode<T>* &root)
	{
		AVLTreeNode<T>* origin_root = root;
		AVLTreeNode<T>* origin_right = root->right_;
		root = origin_right->left_;
		origin_right->left_ = root->right_;
		origin_root->right_ = root->left_;
		root->right_ = origin_right;
		root->left_ = origin_root;
		origin_right->bf_ = (((root->bf_) == -1) ? 1 : 0);
		origin_root->bf_ = (((root->bf_) == 1) ? -1 : 0);
		root->bf_ = 0;
	}

}

#endif // !AVL_TREE_H_
