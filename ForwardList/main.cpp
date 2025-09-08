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
	ForwardList(int size) :ForwardList()
	{
		while (size--)push_front(0);
		cout << "FLSizeConstructor:\t" << this << endl;
	}

	ForwardList(ForwardList&& other) :ForwardList()
	{
		*this = std::move(other);
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
			push_front(Temp->Data);
		}
		reverse();
		cout << "FLCopyAssignment:\t" << this << endl;
		return *this;
	}

	ForwardList& operator=(ForwardList&& other)
	{
		if (this == &other)return *this;
		while (Head)pop_front();
		this->Head = other.Head;
		this->size = other.size;
		other.Head = nullptr;
		other.size = 0;
		cout << "FLMoveAssognment:\t" << this << endl;
		return *this;
	}

	int operator[](int index)const
	{
		Element* Temp = Head;
		for (int i = 0; i < index; i++)Temp = Temp->pNext;
		return Temp->Data;
	}
	int& operator[](int index)
	{
		Element* Temp = Head;
		for (int i = 0; i < index; i++)Temp = Temp->pNext;
		return Temp->Data;
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
			return push_front(Data);
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

	void reverse()
	{
		ForwardList reverse;				   //будет хранить задом на перед
		while (Head)				       //пока список содержит элементы
		{
			reverse.push_front(Head->Data); //добавляем голову элемент
			pop_front();				   //и удаляем начальный элемент списка
		}
		*this = std::move(reverse);
		/*Head = reverse.Head;*/				   //подменяем наш список Реверсным
		/*size = reverse.size;*/
		reverse.Head = nullptr;			   //поскольку Реверсный список является локальной переменной для него будет вызван деструктор
	}									   //который полностью его очистит, а он указывает на ту же паямть что и наш основной список

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
		fusion.push_front(Temp->Data);
	}
	for (Element* Temp = right.Head; Temp; Temp = Temp->pNext)
	{
		fusion.push_front(Temp->Data);
	}
	fusion.reverse();
	return fusion;
}

//#define BASE_CHECK
//#define OPERATOR_PLUS_CHECK
//#define PERFORMANCE_CHECK
//#define SUBSCRIPT_OPERATOR_CHECK
//#define COPY_SEMANTIC_PERFORMANS_CHECK
#define MOVE_SEMANTIC_CHECK

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
	for (int i = 0; i < list1.get_size(); i++)
	{
		cout << list1[i] << tab;
	}
	cout << endl;

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
	for (int i = 0; i < list2.get_size(); i++)
	{
		cout << list2[i] << tab;
	}
	cout << endl;

	cout << string << endl;
	ForwardList list3;
	cout << string << endl;
	list3 = list1 + list2;
	cout << string << endl;

	//list3.print();

	for (int i = 0; i < list3.get_size(); i++)
	{
		cout << list3[i] << tab;
	}
	cout << endl;

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
	cout << "ForwardList filled for " << double(end - start) / CLOCKS_PER_SEC << " second " << endl;
	system("PAUSE");

#endif 

#ifdef SUBSCRIPT_OPERATOR_CHECK
	int n;
	cout << "Go to size: "; cin >> n;

	clock_t start;
	clock_t end;

	ForwardList list(n);
	start = clock();
	for (int i = 0; i < list.get_size(); i++)
	{
		list[i] = rand() % 100;
	}
	end = clock();
	cout << "List filed " << double(end - start) / CLOCKS_PER_SEC << " second" << endl;
	system("PAUSE");
	for (int i = 0; i < list.get_size(); i++)
	{
		cout << list[i] << tab;
	}
	cout << endl;
#endif

#ifdef COPY_SEMANTIC_PERFORMANS_CHECK

	int n;
	cout << "Go to size: "; cin >> n;

	clock_t start;
	clock_t end;

	ForwardList list1;

	start = clock();
	for (int i = 0; i < n; i++)
	{
		list1.push_front(rand() % 100);
	}
	end = clock();
	cout << "List filed: " << double(end - start) / CLOCKS_PER_SEC << " second" << endl;
	system("PAUSE");
	start = clock();
	ForwardList list2 = list1;
	end = clock();
	cout << "Copying complete for " << double(end - start) / CLOCKS_PER_SEC << " second" << endl;

	for (int i = 0; i < list1.get_size(); i++)cout << list1[i] << tab; cout << endl;
	for (int i = 0; i < list2.get_size(); i++)cout << list2[i] << tab; cout << endl;
#endif

#ifdef MOVE_SEMANTIC_CHECK

	clock_t start, end;
	ForwardList list1;
	ForwardList list2;

	start = clock();
	for (int i = 0; i < 1000000; i++)list1.push_front(rand());
	for (int i = 0; i < 1000000; i++)list2.push_front(rand());
	end = clock();

	cout << "Lists filed for " << double(end - start) / CLOCKS_PER_SEC << " seconds" << endl;
	system("PAUSE");

	start = clock();
	ForwardList list3 = list1 + list2;
	end = clock();

	cout << "Lists concatenated for " << double(end - start) / CLOCKS_PER_SEC << " seconds" << endl;

#endif
}