#include<iostream>
#include<windows.h>
using namespace std;
using std::cout;
using std::cin;
using std::endl;

#define tab "\t"
#define string cout<<"---------------------------\n"<<endl
//#define BASE_CHECK

class Element
{
	int Data;
	Element* pNext;
public:
	Element(int Data, Element* pNext = nullptr)
	{
		this->Data = Data;
		this->pNext = pNext;
		cout << "EConstructor:\t" << this << endl;
	}
	~Element()
	{
		cout << "EDestructor:\t" << this << endl;
	}
	friend class ForwardList;
};

class ForwardList
{
	Element* Head;
	int size_list;
public:
	ForwardList()
	{
		Head = nullptr;
		size_list = 0;
		cout << "FLConstructor:\t" << this << endl;
	}
	~ForwardList()
	{
		cout << "FLDestructor:\t" << this << endl;
	}

	void push_front(int Data)
	{
		Element* New = new Element(Data);

		New->pNext = Head;
		Head = New;
		size_list++;
	}
	
	void push_back(int Data)
	{
		if (Head == nullptr)
		{
			push_front(Data);
		}
		Element* Temp = Head;
		while (Temp->pNext != nullptr)
		{
			Temp = Temp->pNext;
		}
		Temp->pNext = new Element(Data);
		size_list++;

	}
	void insert(int Data, int index)
	{
		if (index > size_list)
		{
			push_back(Data);
			cout << "Индекс выходит за пределы списка - поставили в конец" << endl;
			return;
		}
		if (index == 0)
		{
			push_front(Data);
			return;
		}

		Element* Previous = Head;
		for (int i = 0; i < index - 1; i++)
		{
			Previous = Previous->pNext;
		}
		Element* New = new Element(Data);
		New->pNext = Previous->pNext;
		Previous->pNext = New;
		size_list++;
	}
	void pop_front()
	{
		while (Head == nullptr)break;
		Element* to_delete = Head;
		Head = Head->pNext;
		delete to_delete;
		size_list--;
	}
	void pop_back()
	{
		while (Head == nullptr)break;
		if (Head->pNext == nullptr)
		{
			pop_front();
		}
		Element* Temp = Head;
		while (Temp->pNext->pNext != nullptr)
		{
			Temp = Temp->pNext;
		}
		delete Temp->pNext;
		Temp->pNext = nullptr;
		size_list--;
	}
	void erase(int index)
	{
		if (index >= size_list)
		{
			cout << "Ошибка: Индекс выходит за пределы списка!" << endl;
		}
		if (index == 0)
		{
			pop_front();
		}

		Element* Previous = Head;
		for (int i = 0; i < index - 1; i++)
		{
			Previous = Previous->pNext;
		}
		
		Element* to_delete = Previous->pNext;
		
		Previous->pNext = to_delete->pNext;
		
		delete to_delete;
		size_list--;
	}

	void print()const
	{
		Element* Temp = Head;
		while (Temp)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp=Temp->pNext;
		}
	}
};

void main()
{
	setlocale(LC_ALL, "");
#ifdef BASE_CHECK	
	int n;
	cout << "Go to size list: "; cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		list.push_front(rand() % 100);
	}
	list.print();

	string;
	cout << "push_back - 30" << endl;
	list.push_back(123);
	list.print();

	string;
	cout << "pop_front" << endl;
	list.pop_front();
	list.print();

	string;
	cout << "pop_back" << endl;
	list.pop_back();
	list.print();

	string;
	cout << "insert - 100/3" << endl;
	list.insert(100, 3);
	list.print();

	string;
	cout << "erase - 1" << endl;
	list.erase(1);
	list.print();
#endif

	ForwardList list1;
	list1.push_back(0);
	list1.push_back(1);
	list1.push_back(1);
	list1.push_back(2);
	list1.print(); 
	
	ForwardList list2;
	list2.push_back(3);
	list2.push_back(5);
	list2.push_back(8);
	list2.push_back(13);
	list2.push_back(21);
	list2.push_back(34);
	list2.push_back(55);
	list2.push_back(89);
	list2.print();

	int index, value;
	cout << "Go to value & index: "; cin >> value >> index;
	list1.insert(value, index);
	list1.print();
}