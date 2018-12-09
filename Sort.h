#ifndef SORT_H_
#define SORT_H_


namespace MyDataStruct
{
	template <class T>
	void swap(T& i, T& j)
	{
		auto temp = j;
		j = i;
		i = temp;
	}
	
	//1.bubble_sort;
	template<class Iterator>
	void bubble_sort(Iterator begin, Iterator end)
	{
		if (begin == end) {
			return;
		}
		for (auto i = begin; i != end; ++i) {
			for (auto j = begin+1; j != end - (i-begin); ++j) {
				if (*j<*(j-1))
				{
					swap(*(j-1), *j);
				}
			}

		}
	}

	//2.seleced_sort
	template<class Iterator>
	void select_sort(Iterator begin, Iterator end)
	{
		if (begin == end) {
			return;
		}
		Iterator index = begin;
		auto temp = *begin;
		for (auto i = begin; i != end; ++i) {
			index = i;
			for (auto j = i + 1; j != end; ++j) {
				if (!(*index<*j))
				{
					index = j;
				}
			}
			swap(*index, *i);
		}
	}

	//3.insert_sort
	template<class Iterator>
	void insert_sort(Iterator begin, Iterator end)
	{
		if (begin == end) {
			return;
		}
		Iterator index = begin;
		auto temp = *begin;
		for (auto i = begin; i != end; ++i) {
			for (auto j = i; j != begin; --j) {
				if (*j < *(j - 1)) {
					swap(*j, *(j - 1));
				} else {
					break;
				}
			}
		}
	}

	//4.shell_sort
	template<class Iterator>
	void shell_sort(Iterator begin, Iterator end)
	{
		if (begin == end) {
			return;
		}
		int increment = end - begin;

		do {
			increment = increment / 3 + 1;
			for (auto i = begin + increment; i != end; ++i) {
				auto j = i;
				j = begin + (i - begin) % increment;
				for (Iterator k = i; k != j; k = k - increment) {
					if (*k < *(k - increment)) {
						swap(*k, *(k - increment));
					} else {
						break;
					}
				}
			}
			
		} while (increment > 1);
	}
	
	//5.quick_sort
	template<class Iterator>
	void quick_sort(Iterator begin, Iterator end)
	{
		if (begin == end) {
			return;
		}
		int next = 0;
		int left = 0;
		swap(*begin, *(begin + (end - begin) / 2));
		for (Iterator i = begin + 1 ; i != end; ++i) {
			if (*i<*begin) {
				++next;
				++left;
				swap(*(begin + next), *i);
				swap(*(begin + left), *(begin + next));
			} else if (!(*begin < *i)) {
				++next;
				swap(*(begin + next), *i);
			}
		}
		swap(*begin, *(begin + left));

		if (begin != (begin + left)) {
			quick_sort(begin, begin + left);
		}
		if (begin + next + 1 != end) {
			quick_sort(begin + next + 1, end);
		}
		
	}
	
	//6.heap_sort
	template<class Iterator>
	void heap_play(Iterator begin,Iterator end, Iterator position)
	{

		int len = end - begin;
		int k = position - begin;
		auto left = 2 * k + 1;
		auto right = 2 * k + 2;
		int larget_id = k;
		if (left < len&&*(begin + larget_id) < *(begin + left)) {
			larget_id = left;
		}
		if (right < len&&  *(begin + larget_id) < *(begin + right)) {
			larget_id = right;
		}
		if (k == larget_id) {
			return;
		}
		swap(*(begin + k), *(begin + larget_id));
		heap_play(begin, end, begin + larget_id);
	}
	template<class Iterator>
	void heap_sort(Iterator begin, Iterator end)
	{
		if (begin == end) {
			return;
		}
		int len = end - begin;
		for (int i = len / 2 - 1; i >= 0; --i) {
			heap_play(begin, end, begin + i);
		}
		while (len >= 2) {
			swap(*begin, *(begin + len - 1));
			--len;
			heap_play(begin, begin + len, begin);
		}
	}

	//7.merge_sort
	template<class Iterator>
	void merge_sort(Iterator begin, Iterator end)
	{
		if (begin == end) {
			return;
		}
		int len = end - begin;
		if (len == 1) {
			return;
		}
		Iterator mid = begin + len / 2;
		merge_sort(begin, mid);
		merge_sort(mid, end);
		auto type = *begin;
		decltype(type)* temp = new decltype(type)[len];
		Iterator i = begin;
		Iterator j = mid;
		for (int c = 0; c < len; ++c) {
			if ((i!=mid) && (j == end || (*i) < (*j))) {
				temp[c] = *i;
				++i;
			} else {
				temp[c] = *j;
				++j;
			}
		}
		for (int c = 0; c < len; ++c) {
			*(begin + c) = temp[c];
		}
		delete[] temp;
	}

	//8.bucket_sort
	template<class Iterator>
	int bucket_sort(Iterator begin, Iterator end)
	{
		if (begin == end) {
			return 0;
		}
		int num[10] = { 0 };
		int start[10] = { 0 };
		int max_value=0;
		int len = end - begin;
		int* temp = new int[len];
		int c = 0;
		for (Iterator i = begin; i != end; ++i) {
			if (max_value < *i) {
				max_value = *i;
			}
		}
		int k = 1;
		while (max_value) {
			max_value /= 10;
			
			for (int i = 0; i < 10; ++i) {
				num[i] = 0;
				start[i] = 0;
			}
			for (Iterator i = begin; i != end; ++i) {
				++num[*i / k % 10];
			}
			for (int i = 1; i < 10; ++i) {
				start[i] = num[i - 1] + start[i - 1];
			}
			for (Iterator i = begin; i != end; ++i) {
				++c;
				temp[start[*i / k % 10]++] = *i;
			}
			for (int i = 0; i < len; ++i) {
				*(begin + i) = temp[i];
			}
			k *= 10;
		}
		delete[] temp;
		return c;
	}
}
#endif // !SORT_H_
