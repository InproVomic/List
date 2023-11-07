#pragma once
#include <iostream>
namespace cbb123
{
	template<class T>
	struct ListNode
	{
		ListNode(const T& val = T())
			:_val(val)
			,_pPre(nullptr)
			,_pNext(nullptr)
		{}
		T _val;
		ListNode<T>* _pPre;
		ListNode<T>* _pNext;
	};
	template<class T,class Ref,class Ptr>
	class ListIterator
	{
	public:
		typedef ListNode<T>* PNode;
		typedef ListIterator<T, Ref, Ptr> Self;

		ListIterator(PNode pNode = nullptr)
			:_pNode(pNode)
		{}

		ListIterator(const Self& l)
			:_pNode(l._pNode)
		{
			std::cout << "构造函数"<<std::endl;
		}

		Ref operator*()
		{
			return _pNode->_val;
		}

		Ptr operator->()
		{
			return &(_pNode->_val);
		}

		Self& operator++()
		{
			_pNode = _pNode->_pNext;
			return *this;
		}

		Self operator++(int)
		{
			Self tmp(*this);
			_pNode = _pNode->_pNext;
			return tmp;
		}

		Self& operator--()
		{
			_pNode = _pNode->_pPre;
			return *this;
		}

		Self& operator--(int)
		{
			Self tmp(*this);
			_pNode = _pNode->_pPre;
			return tmp;
		}

		bool operator!=(const Self& l)
		{
			return _pNode != l._pNode;
		}

		bool operator==(const Self& l)
		{
			return _pNode == l._pNode;
		}

		PNode _pNode;
	};
	// 适配器 -- 复用
	template<class Iterator, class Ref, class Ptr>
	class Reverse_iterator
	{
	public:
		typedef Reverse_iterator<Iterator, Ref, Ptr> Self;
		Reverse_iterator(const Iterator& it)
			:_it(it)
		{};
		Ref operator*()
		{
			return _it._pNode->_val;
		}

		Ptr operator->()
		{
			return &(_it._pNode->_val);
		}

		Self& operator++()
		{
			_it._pNode = _it._pNode->_pPre;
			return *this;
		}

		Self operator++(int)
		{
			Self tmp(*this);
			_it._pNode = _it._pNode->_pPre;
			return tmp;
		}

		Self& operator--()
		{
			_it._pNode = _it._pNode->_pNext;
			return *this;
		}

		Self& operator--(int)
		{
			Self tmp(*this);
			_it._pNode = _it._pNode->_pNext;
			return tmp;
		}

		bool operator!=(const Self& l)
		{
			return _it._pNode != l._it._pNode;
		}

		bool operator==(const Self& l)
		{
			return _it._pNode == l._it._pNode;
		}
	private:
		Iterator _it;
	};
	// vector和list反向迭代器实现
	template<class T>
	class List
	{
		typedef ListNode<T> ListNode;
	public:
		typedef ListIterator<T, T&, T*> iterator;
		typedef ListIterator<T, const T&, const T*> const_iterator;
		typedef Reverse_iterator<iterator, T&, T*> reverse_iterator;

		List()
		{
			CreateHead();
		}

		List(int n, const T& value = T())
		{
			CreateHead();
			for (int i = 0; i < n; ++i)
			{
				push_back(value);
			}
		}

		template <class Iterator>

		List(Iterator first, Iterator last)
		{
			CreateHead();
			while (first != last)
			{
				push_back(*first);
				++first;
			}
		}

		List(const List<T>& l)
		{
			CreateHead();
			List<T> tmp(l.begin(), l.end());
			swap(tmp);
		}

		//List<T>& operator=(const List<T> l)
		//{
		//	List tmp(l);
		//	swap(tmp);
		//	return *this;
		//}

		~List()
		{
			clear();
			delete _pHead;
			_pHead = nullptr;
		}

		iterator rbegin()
		{
			return iterator(_pHead->_pPre);
		}

		iterator rend()
		{
			return iterator(_pHead);
		}

		iterator rbegin()const
		{
			return iterator(_pHead->_pPre);
		}

		iterator rend()const
		{
			return iterator(_pHead);
		}

		iterator begin()
		{
			return iterator(_pHead->_pNext);
		}

		iterator end()
		{
			return iterator(_pHead);
		}

		const_iterator begin() const
		{
			return _pHead->_pNext;
		}

		const_iterator end() const
		{
			return _pHead;
		}
		size_t size()const
		{
			int count = 0;
			ListNode* it = _pHead->_pNext;
			while (it != _pHead)
			{
				it = it->_pNext;
				++count;
			}
			return count;
		}

		bool empty()const
		{
			return _pHead == _pHead->_pNext;
		}
		T& front()
		{
			return _pHead->_pNext->_val;
		}

		const T& front()const
		{
			return _pHead->_pNext->_val;
		}

		T& back()
		{
			return _pHead->_pPre->_val;
		}

		const T& back()const
		{
			return _pHead->_pPre->_val;
		}
		void push_back(const T& val) 
		{ 
			insert(begin(), val); 
		}

		void pop_back() 
		{ 
			erase(--end()); 
		}

		void push_front(const T& val)
		{ 
			insert(begin(), val);
		}

		void pop_front() 
		{ 
			erase(begin());
		}

		// 在pos位置前插入值为val的节点

		iterator insert(iterator pos, const T& val)
		{
			ListNode* cur = pos._pNode;
			ListNode* pre = cur->_pPre;

			ListNode* newnode = new ListNode(val);
			newnode->_pNext = cur;
			cur->_pPre = newnode;
			newnode->_pPre = pre;
			pre->_pNext = newnode;
			
			return iterator(newnode);
		}

		// 删除pos位置的节点，返回该节点的下一个位置

		iterator erase(iterator pos)
		{
			ListNode* pre = pos._pNode->_pPre;
			ListNode* next = pos._pNode->_pNext;

			pre->_pNext = next;
			next->_pPre = pre;
			
			delete pos._pNode;

			return iterator(next);
		}

		void clear()
		{
			iterator it = begin();
			while(it != end())
			{
				erase(it++);
			}
		}

		void swap(List<T>& l)
		{
			std::swap(_pHead, l._pHead);
		}
	private:

		void CreateHead()
		{
			_pHead = new ListNode;
			_pHead->_pNext = _pHead;
			_pHead->_pPre = _pHead;
		}

		ListNode* _pHead;

	};
	
	void print_list(const List<int>& lt)
	{
		List<int>::const_iterator it = lt.begin();
		while (it != lt.end())
		{
			//(*it) *= 2;
			std::cout << *it << " ";
			++it;
		}
		std::cout << std::endl;
	}

	void test_list1()
	{
		const List<int> lt1;
		const int n = 10;
		//n = 11;

		List<int> lt;
		lt.push_back(1);
		lt.push_back(2);
		lt.push_back(3);
		lt.push_back(4);

		// int*
		List<int>::iterator it = lt.begin();
		while (it != lt.end())	
		{
			*it = (*it) * 2;
			std::cout << *it << " ";
			++it;
		}
		std::cout << std::endl;

		for (auto e : lt)
		{
			std::cout << e << " ";
		}
		std::cout << std::endl;

		print_list(lt);
	}

	struct AA
	{
		int _a1;
		int _a2;

		AA(int a1 = 0, int a2 = 0)
			:_a1(a1)
			, _a2(a2)
		{}
	};

	void test_list2()
	{
		List<AA> lt;
		lt.push_back(AA(1, 1));
		lt.push_back(AA(2, 2));
		lt.push_back(AA(3, 3));

		// AA* ptr
		List<AA>::iterator it = lt.begin();
		while (it != lt.end())
		{
			//std::cout << (*it)._a1 << ":" << (*it)._a2 << std::endl;		
			std::cout << it->_a1 << ":" << it->_a2 << std::endl;
			//std::cout << it.operator->()->_a1 << ":" << it.operator->()->_a1 << std::endl;
			++it;
		}
		std::cout << std::endl;
	}

	void test_list3()
	{
		List<int> lt;
		lt.push_back(1);
		lt.push_back(2);
		lt.push_back(3);
		lt.push_back(4);

		for (auto e : lt)
		{
			std::cout << e << " ";
		}
		std::cout << std::endl;

		auto pos = lt.begin();
		++pos;
		lt.insert(pos, 20);

		for (auto e : lt)
		{
			std::cout << e << " ";
		}
		std::cout << std::endl;

		lt.push_back(100);
		lt.push_front(1000);

		for (auto e : lt)
		{
			std::cout << e << " ";
		}
		std::cout << std::endl;

		lt.pop_back();
		lt.pop_front();

		for (auto e : lt)
		{
			std::cout << e << " ";
		}
		std::cout << std::endl;
	}

	void test_list4()
	{
		List<int> lt;
		lt.push_back(1);
		lt.push_back(2);
		lt.push_back(3);
		lt.push_back(4);

		for (auto e : lt)
		{
			std::cout << e << " ";
		}
		std::cout << std::endl;

		lt.clear();

		for (auto e : lt)
		{
			std::cout << e << " ";
		}
		std::cout << std::endl;

		lt.push_back(10);
		lt.push_back(2);
		lt.push_back(3);
		lt.push_back(40);

		for (auto e : lt)
		{
			std::cout << e << " ";
		}
		std::cout << std::endl;
	}

	void test_list5()
	{
		List<int> lt;
		lt.push_back(1);
		lt.push_back(2);
		lt.push_back(3);
		lt.push_back(4);
		lt.push_back(5);

		for (auto e : lt)
		{
			std::cout << e << " ";
		}
		std::cout << std::endl;

		List<int> lt2(lt);

		for (auto e : lt2)
		{
			std::cout << e << " ";
		}
		std::cout << std::endl;

		List<int> lt3;
		lt3.push_back(10);
		lt3.push_back(20);
		lt3.push_back(30);

		for (auto e : lt3)
		{
			std::cout << e << " ";
		}
		std::cout << std::endl;

		lt2 = lt3;

		for (auto e : lt2)
		{
			std::cout << e << " ";
		}
		std::cout << std::endl;

		for (auto e : lt3)
		{
			std::cout << e << " ";
		}
		std::cout << std::endl;
	}

	void test_list6()
	{
		List<int> lt;
		lt.push_back(1);
		lt.push_back(2);
		lt.push_back(3);
		lt.push_back(4);

		List<int>::iterator it = lt.begin();
		while (it != lt.end())
		{
			(*it) *= 2;
			std::cout << *it << " ";
			++it;
		}
		std::cout << std::endl;

		List<int>::reverse_iterator rit = lt.rbegin();
		while (rit != lt.rend())
		{
			std::cout << *rit << " ";
			++rit;
		}
		std::cout << std::endl;
	}
}

