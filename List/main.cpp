#include<iostream>
using namespace std;

#define tab "\t"
#define delimeter "\n------------------------------------------------\n"

class List
{
	class Element
	{
		int Data;
		Element* pPrev;
		Element* pNext;
	public:
		Element(int Data, Element* pNext = nullptr, Element* pPrev = nullptr)
			:Data(Data), pNext(pNext), pPrev(pPrev)
		{
			cout << "EConstructor:\t" << this << endl;
		}
		~Element()
		{
			cout << "EDestructor:\t" << this << endl;
		}
		friend class List;
	}*Head,*Tail; //ќюъекты классов и структур и указатели на эти объекты можно объ€вл€ть непосредственно после описани€ классов и структур.
	
	size_t size;

public:
	List()
	{
		Head = Tail = nullptr;
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	~List()
	{
		//while (Head)pop_front();
		while (Tail)pop_back();
		cout << "LDestructor:\t" << this << endl;
	}
	void push_front(int Data)
	{
		Element* New = new Element(Data);
		if (Head == nullptr && Tail == nullptr)
		{
			Head = Tail = New;
		}
		else 
		{
			New->pNext = Head;

			Head->pPrev = New;
			Head = New;
		}
		size++;
	}

	void push_back(int Data)
	{
		Element* New = new Element(Data);
		if (Head == nullptr && Tail == nullptr)
		{
			Head = Tail = New;
		}
		else
		{
			New->pPrev = Tail;
			Tail->pNext = New;
			Tail = New;
		}
		size++;
	}

	void insert(int Data, int Index)
	{
		if (Index < 0)return;
		if (Index >= size)return push_back(Data);
		if (Index == 0 && size == 0)return push_front(Data);
		Element* Temp;
		if (Index < size / 2)
		{
			Temp = Head;
			for (int i = 0; i < Index; i++)Temp = Temp->pNext;
		}
		else
		{
			Temp = Tail;
			for (int i = 0; i < size - Index - 1; i++)Temp = Temp->pPrev;
		}
		Element* New = new Element(Data);
		New->pNext = Temp;
		New->pPrev = Temp->pPrev;
		Temp->pPrev->pNext = New;
		Temp->pPrev = New;

		size++;
	}

	void pop_front()
	{
		if (Head == nullptr && Tail == nullptr)return;
		if (Head == Tail)
		{
			delete Head;
			Head = Tail = nullptr;
		}
		else
		{
			Head = Head->pNext;
			delete Head->pPrev;
			Head->pPrev = nullptr;
		}
		size--;
	}

	void pop_back()
	{
		if (Head == nullptr && Tail == nullptr)return;
		if (Head == Tail)
		{
			delete Tail;
			Head = Tail = nullptr;
		}
		else
		{
			Tail = Tail->pPrev;
			delete Tail->pNext;
			Tail->pNext = nullptr;
		}
		size--;
	}

	void print()const
	{
		cout << delimeter << endl;
		cout << "Head " << Head << endl;
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Tail " << Tail << endl;
		cout << "Count elements of lists: " << size << endl;
		cout << delimeter << endl;
	}
	void reverse_print()const
	{
		cout << delimeter << endl;
		cout << "Head " << Head << endl;
		for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
		{
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		}
		cout << "Tail " << Tail << endl;
		cout << "Count elements of lists: " << size << endl;
		cout << delimeter << endl;		
	}
};

//#define BASE_CHECK
#define HOME_CHECK

void main()
{
	setlocale(LC_ALL, "");
#ifdef BASE_CHECK
	int n;
	cout << "go to size of list: "; cin >> n;
	List list;
	list.pop_front();
	list.print();
	for (int i = 0; i < n; i++)
	{
		list.push_back(rand() % 100);
		//list.push_front(rand() % 100);
	}
	list.print();
	list.reverse_print();

	/*list.pop_back();
	list.print();
	list.reverse_print();*/

	int index, value;
	cout << "go to index: "; cin >> index;
	cout << "go to value: "; cin >> value;
	list.insert(value, index);
	list.print();
	list.reverse_print();
#endif

#ifdef HOME_CHECK
	List list1 = { 3,5,8,13,21 };
	List list2 = { 34,55,89 };
	List list3 = list1 + list2;
	for (int i : list1)cout << i << tab; cout << endl;
	for (int i : list2)cout << i << tab; cout << endl;
	for (int i : list3)cout << i << tab; cout << endl;
#endif

}
