#include <iostream>
#include <time.h>
#include <algorithm>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimeter "\n-----------------------------------------------\n"
//#define MAX(a,b)a>b?a:b
//#define DEBUG
class Tree
{
protected:
	class Element
	{
		int Data;
		Element* pLeft;
		Element* pRight;
	public:
		Element(int Data, Element* pLeft = nullptr, Element* pRight = nullptr) :Data(Data), pLeft(pLeft), pRight(pRight)
		{
#ifdef DEBUG
			cout << "EConstructor:\t" << this << endl;
#endif // DEBUG

		}
		~Element()
		{
#ifdef DEBUG
			cout << "EDestructor:\t" << this << endl;
#endif // DEBUG

		}
		friend class Tree;
		friend class UniqueTree;
	}*Root;
public:
	Element* getRoot()const
	{
		return Root;
	}
	Tree() :Root(nullptr)
	{
		cout << "TConstructor:\t" << this << endl;
	}
	Tree(const std::initializer_list<int>& il) :Tree()
	{
		for (int const* it = il.begin(); it != il.end(); ++it)
		{
			insert(*it, Root);
		}
		cout << "ILConstructor:\t" << this << endl;
	}
	~Tree()
	{
		Clear();
		cout << "TDestructor:\t" << this << endl;
		cout << delimeter;
	}
	void Clear()
	{
		Clear(Root);
	}
	void insert(int Data)
	{
		insert(Data, Root);
	}
	void Erase(int Data)
	{
		Erase(Data, Root);
	}
	int depth()const
	{
		return depth(Root);
	}
	void balance()
	{
		balance(Root);
	}
	int minValue()const
	{
		return minValue(Root);
	}
	int maxValue()const
	{
		return maxValue(Root);
	}
	int Sum()const
	{
		return Sum(Root);
	}
	int count()const
	{
		return count(Root);
	}
	double Avg()const
	{
		return (double)Sum(Root) / count(Root);
	}

	void depth_print(int depth, int width = 4)const
	{
		depth_print(depth, Root, width);
		cout << endl;
	}
	void tree_print()const
	{
		tree_print(depth(), 4 * depth());
	}
	void print()const
	{
		print(Root);
		cout << endl;
	}

private:
	void Clear(Element*& Root)
	{
		if (Root == nullptr)return;
		Clear(Root->pLeft);
		Clear(Root->pRight);
		delete Root;
		Root = nullptr;
	}
	void insert(int Data, Element* Root)
	{
		if (this->Root == nullptr) this->Root = new Element(Data);
		if (Root == nullptr)return;
		if (Data < Root->Data)
		{
			if (Root->pLeft == nullptr)Root->pLeft = new Element(Data);
			else insert(Data, Root->pLeft);

		}
		else
		{
			if (Root->pRight == nullptr)Root->pRight = new Element(Data);
			else insert(Data, Root->pRight);
		}
	}
	void Erase(int Data, Element*& Root) //�������� �� ������, ����� �������� � ����������, � �� � ������
	{
		if (Root == nullptr)return;
		Erase(Data, Root->pLeft);
		Erase(Data, Root->pRight);
		if (Data == Root->Data)
		{
			if (Root->pLeft == Root->pRight)
			{
				delete Root;
				Root = nullptr;
			}
			else
			{
				//��� ����, ����� ������ ��������������� ��� �������� ���������,
				//����� ��������� ��� ����� ��������:
				if (count(Root->pLeft) > count(Root->pRight))
				{
					//� ���� ����� ����� ������� ��� ������, �� ����� �� ��� ������������ ��������
					//������ ��� ��� ����� ����� � ���������� ��������:
					Root->Data = maxValue(Root->pLeft);
					Erase(maxValue(Root->pLeft), Root->pLeft);
				}
				else
				{
					//� ��������� ������ ����� ����������� �������� �� ������ �����,
					//������ ��� ��� ����� ����� � ���������� ��������
					Root->Data = minValue(Root->pRight);
					Erase(minValue(Root->pRight), Root->pRight);
				}
			}

		}
	}
	int minValue(Element* Root)const
	{
		return Root == nullptr ? INT_MIN : Root->pLeft == nullptr ? Root->Data : minValue(Root->pLeft);
		/*if (Root->pLeft == nullptr)return Root->Data;
		else return minValue(Root->pLeft);*/
	}
	int maxValue(Element* Root)const
	{
		return !Root ? INT_MIN : Root->pRight ? maxValue(Root->pRight) : Root->Data;
		/*if (Root->pRight == nullptr)return Root->Data;
		else return maxValue(Root->pRight);*/
	}
	int count(Element* Root)const
	{
		return !Root ? 0 : count(Root->pLeft) + count(Root->pRight) + 1;
		/*if (Root == nullptr) return 0;
		else return count(Root->pLeft) + count(Root->pRight) + 1;*/
	}
	int Sum(Element* Root)const
	{
		return Root ? Sum(Root->pLeft) + Sum(Root->pRight) + Root->Data : 0;
	}
	int depth(Element* Root)const
	{
		//1
		return Root == nullptr ? 0 : std::max(depth(Root->pLeft) + 1, depth(Root->pRight) + 1);//��� ������� � ������
		//�� �������� ��� ����� ����������
		//2
		/*if (Root == nullptr)return 0;
		int l_depth = depth(Root->pLeft) + 1;
		int r_depth = depth(Root->pRight) + 1;
		return l_depth < r_depth ? r_depth : l_depth;*///��� ������� �� ���� ������� ���������� ����������� �������
		//3
		/*return !Root ? 0 :
			depth(Root->pLeft) + 1 > depth(Root->pRight) + 1 ?
			depth(Root->pLeft) + 1 :
			depth(Root->pRight) + 1;*/ //��� ����� ����� �������
	}
	void balance(Element* Root)
	{
		if (Root == nullptr)return;

		if (abs(count(Root->pLeft) - count(Root->pRight)) < 2)return;

		if (count(Root->pRight) < count(Root->pLeft))
		{
			if (Root->pRight == nullptr)Root->pRight = new Element(Root->Data);
			else insert(Root->Data, Root->pRight);
			Root->Data = maxValue(Root->pLeft);
			Erase(maxValue(Root->pLeft), Root->pLeft);
		}
		if (count(Root->pLeft) < count(Root->pRight))
		{
			if (Root->pLeft == nullptr)Root->pLeft = new Element(Root->Data);
			else insert(Root->Data, Root->pLeft);
			Root->Data = minValue(Root->pRight);
			Erase(minValue(Root->pRight), Root->pRight);
		}
		balance(Root->pLeft);
		balance(Root->pRight);
		balance(Root);
	}
	void depth_print(int depth, Element* Root, int width = 2)const
	{
		if (Root == nullptr)
		{
			return;
		}
		if (depth == 0)
		{
			cout.width(width);
			cout << Root->Data;
		}
		depth_print(depth - 1, Root->pLeft, width);
		depth_print(depth - 1, Root->pRight, width);
	}
	void tree_print(int depth, int width)const
	{
		if (depth == -1)
		{

			return;
		}
		tree_print(depth - 1, width * 1.5);
		depth_print(depth - 1, width / 1.75);
		cout << endl;
		cout << endl;
	}
	void print(Element* Root)const
	{
		if (Root == nullptr)return;
		print(Root->pLeft);
		cout << Root->Data << tab;
		print(Root->pRight);
	}

};

class UniqueTree :public Tree
{
public:
	void insert(int Data, Element* Root)
	{
		if (this->Root == nullptr) this->Root = new Element(Data);
		if (Root == nullptr)return;
		if (Data < Root->Data) //���� ������ ��������� �����
		{
			if (Root->pLeft == nullptr)Root->pLeft = new Element(Data);
			else insert(Data, Root->pLeft);

		}
		else if (Data > Root->Data)//���� ������ ��������� ������
		{
			if (Root->pRight == nullptr)Root->pRight = new Element(Data);
			else insert(Data, Root->pRight);
		}
		//���� �����, ������ �� ������, ��� � ��� ����� ��� ������������
	}
public:
	void insert(int Data)
	{
		insert(Data, Root);
	}

};

template<typename T>void measure_performance(const char message[], T(Tree::* function)()const, const Tree& tree)
{
	//int (*function)() - ��������� �� �������, ������� ������ �� ���������, � ���������� �������� ���� 'int'
	clock_t start = clock();
	T result = (tree.*function)();
	clock_t end = clock();
	cout << message << result << ", ��������� �� " << double(end - start) / CLOCKS_PER_SEC << " ������\n";
}
//#define BASE_CHECK
//#define ERASE_CHECK
//#define DEPTH_CHECK
#define BALANCE_CHECK
//#define EFFICIENCY_CHECK
//#define PERFORMANCE_CHECK

void main()
{
	setlocale(LC_ALL, "");

#ifdef BASE_CHECK
	int n;
	cout << "������� ���������� ���������: "; cin >> n;
	Tree tree;
	cout << "����������� �������� � ������: " << tree.minValue() << endl;
	cout << "������������ �������� � ������: " << tree.maxValue() << endl;
	for (int i = 0; i < n; i++)
	{
		tree.insert(rand() % 100);
	}
	tree.print();
	cout << endl;

	cout << "����������� �������� � ������: " << tree.minValue() << endl;
	cout << "������������ �������� � ������: " << tree.maxValue() << endl;
	cout << "���������� ��������� � ������: " << tree.count() << endl;
	cout << "����� ��������� � ������: " << tree.Sum() << endl;
	cout << "������� �������������� ��������� ������: " << tree.Avg() << endl;

	UniqueTree u_tree;
	for (int i = 0; i < n; i++)
	{
		u_tree.insert(rand() % 100);
	}
	u_tree.print();
	cout << "����������� �������� � ������: " << u_tree.minValue() << endl;
	cout << "������������ �������� � ������: " << u_tree.maxValue() << endl;
	cout << "���������� ��������� � ������: " << u_tree.count() << endl;
	cout << "����� ��������� � ������: " << u_tree.Sum() << endl;
	cout << "������� �������������� ��������� ������: " << u_tree.Avg() << endl;
#endif // BASE_CHECK

#ifdef ERASE_CHECK
	Tree tree =
	{
			50,
		25,		75,
	 16,  32, 58, 85, 91, 98
	};
	tree.print();
	int value;
	//cout << "������� ��������� ��������: "; cin >> value;
	/*tree.Erase(25);
	tree.Erase(32);
	tree.Erase(50);
	tree.Erase(75);*/
	tree.Erase(50);
	tree.print();
	cout << "������� ������: " << tree.depth() << endl;
#endif // ERASE_CHECK


#ifdef DEPTH_CHECK
	Tree tree =
	{
			50,
		25,		75,
	 16,  32, 58, 85, 8 //91, 98, 9, 41, 3
	};
	tree.print();

	cout << "������� ������: " << tree.depth() << endl;
	//tree.depth_print(3);
	tree.tree_print();
#endif // DEPTH_CHECK

#ifdef BALANCE_CHECK
	Tree tree = { 55, 34, 21, 13, 8, 5, 3, 27, 74, 91, 102 };
	tree.tree_print();
	tree.balance();
	tree.tree_print();
	tree.print();
#endif // BALANCE_CHECK


#ifdef EFFICIENCY_CHECK
	int n;
	cout << "������� ���������� ���������: "; cin >> n;
	Tree tree;
	for (int i = 0; i < n; i++)
	{
		tree.insert(rand() % 100);
	}

	clock_t t_start, t_end;
	t_start = clock();
	cout << "����������� �������� � ������: " << tree.minValue();
	t_end = clock();
	cout << " ������� �� " << double(t_end - t_start) / CLOCKS_PER_SEC << " ������" << endl;
	t_start = clock();
	cout << "������������ �������� � ������: " << tree.maxValue();
	t_end = clock();
	cout << " ������� �� " << double(t_end - t_start) / CLOCKS_PER_SEC << " ������" << endl;
	t_start = clock();
	cout << "���������� ��������� � ������: " << tree.count();
	t_end = clock();
	cout << " ������� �� " << double(t_end - t_start) / CLOCKS_PER_SEC << " ������" << endl;
	t_start = clock();
	cout << "����� ��������� � ������: " << tree.Sum();
	t_end = clock();
	cout << " ������� �� " << double(t_end - t_start) / CLOCKS_PER_SEC << " ������" << endl;
	t_start = clock();
	cout << "������� �������������� ��������� ������: " << tree.Avg();
	t_end = clock();
	cout << " ������� �� " << double(t_end - t_start) / CLOCKS_PER_SEC << " ������" << endl;
	int element;
	cout << "������� ������� ��� ��������: "; cin >> element;
	t_start = clock();
	cout << "������� " << element << " ������ �� ";
	tree.Erase(element);
	t_end = clock();
	cout << double(t_end - t_start) / CLOCKS_PER_SEC << " ������" << endl;
	t_start = clock();
	cout << "������� ������: " << tree.depth();
	t_end = clock();
	cout << " ������� �� " << double(t_end - t_start) / CLOCKS_PER_SEC << " ������" << endl;
	t_start = clock();
	tree.Clear();
	t_end = clock();
	cout << "������ ������� ��: " << double(t_end - t_start) / CLOCKS_PER_SEC << " ������" << endl;



#endif // EFFICIENCY_CHECK

#ifdef PERFORMANCE_CHECK
	int n;
	cout << "������� ���������� ���������: "; cin >> n;
	Tree tree;

	for (int i = 0; i < n; i++)
	{
		tree.insert(rand() % 100);
	}
	//tree.print();
	/*cout << "����������� �������� � ������: " << tree.minValue() << endl;
	cout << "������������ �������� � ������: " << tree.maxValue() << endl;
	cout << "���������� ��������� � ������: " << tree.count() << endl;
	cout << "����� ��������� � ������: " << tree.Sum() << endl;
	cout << "������� �������������� ��������� ������: " << tree.Avg() << endl;
	cout << "������� ������: " << tree.depth() << endl;*/

	measure_performance("����������� �������� � ������: ", &Tree::minValue, tree);
	measure_performance("������������ �������� � ������: ", &Tree::maxValue, tree);
	measure_performance("����� ��������� ������: ", &Tree::Sum, tree);
	measure_performance("���������� ��������� ������: ", &Tree::count, tree);
	measure_performance("������� �������������� ��������� ������: ", &Tree::Avg, tree);
	measure_performance("������� ������: ", &Tree::depth, tree);
#endif // PERFORMANCE_CHECK

}