#include<iostream>
#include<windows.h>
#include<time.h>
using namespace std;
using std::cout;
using std::cin;
using std::endl;

#define tab "\t"
#define string "\n----------------------------------------------------\n"


class Element
{
	int Data;
	Element* pNext;
public:
	Element(int Data, Element* pNext = nullptr)
	{
		this->Data = Data;
		this->pNext = pNext;
		//cout << "EConstructor:\t" << this << endl;
	}
	~Element()
	{
		//cout << "EDestructor:\t" << this << endl;
	}
	friend class ForwardList;
	friend ForwardList operator+(const ForwardList& left, const ForwardList& right);
};

class ForwardList
{
	Element* Head;
	size_t size;

public:
	Element* get_Head()const
	{
		return Head;
	}
	size_t get_size()const
	{
		return size;
	}
	ForwardList()
	{
		Head = nullptr;
		size = 0;
		cout << "FLConstructor:\t" << this << endl;
	}
	ForwardList(const ForwardList& other):ForwardList()
	{
		*this = other;
		cout << "FLCopyConstructor:\t" << this << endl;
	}
	~ForwardList()
	{
		clock_t start = clock();
		while (Head)pop_front();
		clock_t end = clock();
		cout << "FLDestructor:\t" << this <<"\tcomplete for: " <<double(end-start)/CLOCKS_PER_SEC << endl;
	}
	
	ForwardList& operator=(const ForwardList& other)
	{
		if (this == &other)return *this;
		while (Head)pop_front();

		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
		{
			push_back(Temp->Data);
		}
		cout << "FLCopyAssignment:\t" << this << endl;
		return *this;
	}

	void push_front(int Data)
	{
		Head = new Element(Data, Head);
		/*Element* New = new Element(Data);

		New->pNext = Head;
		Head = New;*/
		size++;
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
		size++;

	}
	void insert(int Data, int index)
	{
		if (index > size)
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
		Previous->pNext = new Element(Data, Previous->pNext);
		/*Element* New = new Element(Data);
		New->pNext = Previous->pNext;
		Previous->pNext = New;*/
		size++;
	}
	void pop_front()
	{
		
		while (Head == nullptr)break;
		Element* to_delete = Head;
		Head = Head->pNext;
		delete to_delete;
		size--;
	}
	void pop_back()
	{
		if (!Head||Head->pNext == nullptr)
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
		size--;
	}
	void erase(int index)
	{
		if (index >= size)
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
		size--;
	}

	void print()const
	{
		/*Element* Temp = Head;
		while (Temp)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp=Temp->pNext;
		}*/
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		}
	}
	friend ForwardList operator+(const ForwardList& left, const ForwardList& right);
};
ForwardList operator+(const ForwardList& left, const ForwardList& right)
{
	ForwardList fusion;
	for (Element* Temp = left.get_Head(); Temp; Temp = Temp->pNext)
	{
		fusion.push_back(Temp->Data);
	}
	for (Element* Temp = right.Head; Temp; Temp = Temp->pNext)
	{
		fusion.push_back(Temp->Data);
	}
	return fusion;
}

//#define BASE_CHECK
#define OPERATOR_PLUS_CHECK
//#define PERFORMANCE_CHECK

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

#ifdef OPERATOR_PLUS_CHECK
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

	cout << string << endl;
	ForwardList fusion;
	cout << string << endl;
	fusion = list1 + list2;
	cout << string << endl;

	fusion.print();

	/*int index, value;
	cout << "Go to value & index: "; cin >> value >> index;
	list1.insert(value, index);
	list1.print();*/

#endif
	
#ifdef PERFORMANCE_CHECK
	int n;
	cout << "Go to size list: "; cin >> n;
	ForwardList list;
	clock_t start = clock();
	for (int i = 0; i < n; i++)
	{
		list.push_front(rand() % 100);
	}
	clock_t end = clock();
	cout << "ForwardList filled for "<<double(end-start)/CLOCKS_PER_SEC<<" second "<<endl;
	system("PAUSE");

#endif 



}