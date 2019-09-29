#include<iostream>

using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimiter "\n----------------------------------------------------\n"

//#define BASE_CHECK
//#define DESTRUCTOR_CHECK
//#define INDEX_OPERATOR_CHECK
//#define INITIALIZER_LIST_CONSTRUCTOR_CHECK
//#define CONSTRUCTORS_CHECK
//#define OPERATORS_CHECK
//#define RANGED_BASED_FOR
//#define ITERATOR_CHECK



template<typename T> class ForwardList
{

	template<typename T>
	class Element
	{
		T Data;
		Element<T>* pNext;
		//static int count;
	public:
		Element(T Data, Element<T>* pNext = nullptr)
		{
			this->Data = Data;
			this->pNext = pNext;
			//count++;
#ifdef DEBUG
			cout << "EConstructor:\t" << this << endl;
#endif // DEBUG


		}
		~Element()
		{
			//count--;
#ifdef DEBUG
			cout << "EDestructor:\t" << this << endl;
#endif // DEBUG

		}
		operator T&()
		{
			return this->Data;
		}

		friend class ForwardList;
		//friend ForwardList operator+(const ForwardList& left, const ForwardList& right);
	};
private:
	Element<T>* Head;
	int size;

public:
	class Iterator
	{

		Element<T>* Temp;
	public:
		Iterator(Element<T>* Temp) :Temp(Temp)
		{
			//this->it = it;
#ifdef DEBUG
			cout << "ItConstructor:\t" << this << endl;
#endif // DEBUG

		}
		~Iterator()
		{
#ifdef DEBUG
			cout << "ITDestructor:\t" << this << endl;
#endif // DEBUG

		}

		Iterator& operator++()
		{
			Temp = Temp->pNext;
			return *this;
		}

		Iterator operator++(int)
		{
			Element<T>* old = Temp;
			Temp = Temp->pNext;
			return old;
		}

		T& operator*()
		{
			return Temp->Data;
		}

		bool operator==(const Iterator& other)
		{
			return this->Temp = other.Temp;
		}

		bool operator!=(const Iterator& other)
		{
			return this->Temp != other.Temp;
		}

	};
	Iterator begin()
	{
		return Head;
	}

	Iterator end()
	{
		return nullptr;
	}

	Iterator begin() const
	{
		return Head;
	}

	Iterator end() const
	{
		return nullptr;
	}




public:
	const int get_size() const
	{
		return this->size;
	}
	ForwardList()
	{
		this->Head = nullptr;
		this->size = 0;
		//Èçíà÷àëüíî ñîçäàåì ïóñòîé ñïèñîê.
		cout << "FLConstructor:\t" << this << endl;
	}
	ForwardList(int size) :ForwardList()
	{
		/*this->Head = nullptr;
		this->size = 0;*/
		while (size--)push_front(T());
	}
	ForwardList(std::initializer_list<T> il) :ForwardList()
	{
		//std::cout << typeid(il.begin()).name() << std::endl;
		for (T const* it = il.begin(); it != il.end(); it++)
		{
			//it - iterator;
			//begin() - âîçâðàùàåò àäðåñ íà÷àëà êîíòåéíåðà il;
			//end()   - âîçâðàùàåò àäðåñ êîíöà êîíòåéíåðà il;
			push_back(*it);
		}
	}

	ForwardList(const ForwardList<T>& other)
	{
		this->Head = nullptr;
		this->size = 0;
		//Element* Temp = other.Head; // Итератор нужен для того что бы перемещаться по ДРУГОМУ списку
		//while (Temp)
		//{
		// push_back(Temp->Data);
		// Temp = Temp->pNext;
		//}
		//for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)push_back(Temp->Data);
		for (Iterator Temp = other.Head; Temp != nullptr; Temp++)push_back(*Temp);
		cout << "FLCopyConstructor:\t" << this << endl;

	}

	ForwardList(ForwardList<T>&& other)
	{
		this->Head = other.Head;
		this->size = other.size;
		other.Head = nullptr;
		cout << "FLMoveconstructor:\t" << this << endl;
	}

	~ForwardList()
	{
		while (Head != nullptr)pop_front();
		cout << "FLDestructor:\t" << this << endl;
	}

	// Operators:
	T& operator[](int Index)
	{
		Element* Temp = Head;
		for (int i = 0; i < Index; i++)Temp = Temp->pNext;
		return Temp->Data;
	}

	ForwardList& operator=(const ForwardList<T>& other)
	{
		if (this == &other)return *this;
		while (Head)pop_front();
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)push_back(Temp->Data);
		cout << "FLAssigment:\t" << this << endl;
		return *this;
	}
	ForwardList& operator=(ForwardList<T>&& other)
	{
		this->Head = other.Head;
		this->size = other.size;
		other.Head = nullptr;
		cout << "FLMoveassigment:\t" << this << endl;
		return*this;
	}

	ForwardList operator+=(const ForwardList<T>* other)
	{


	}


	// Adding elements:
	void push_front(T Data)
	{
		////Äîáàâëÿåò çíà÷åíèå â íà÷àëî ñïèñêà.
		////1)Ñîçäàåì ýëåìåíò, â êîòîðûé áóäåò ïîìåùåíî äîáàâëÿåìîå çíà÷åíèå (Data).
		//Element* New = new Element(Data);
		////2)"Ïðèñòûêîâûâàåì" íîâûé ýëåìåíò ê íà÷àëó ñïèñêà:
		//New->pNext = Head;
		//Head = New;

		Head = new Element<T>(Data, Head);
		size++;
	}
	void push_back(T Data)
	{
		if (Head == nullptr)
		{
			push_front(Data);
			return;
		}
		Element<T>* Temp = Head;
		while (Temp->pNext != nullptr)
		{
			Temp = Temp->pNext;
		}
		Temp->pNext = new Element<T>(Data);
		size++;
	}

	void insert(int Index, T Data)
	{
		if (Index == 0)
		{
			push_front(Data);
			return;
		}
		if (Head == nullptr)
		{
			push_front(Data);
			return;
		}
		Element<T>* Temp = Head;
		for (int i = 0; i < Index - 1; i++)
		{
			if (Temp->pNext == nullptr)break;
			Temp = Temp->pNext;
		}
		/*Element* New = new Element(Data);
		New->pNext = Temp->pNext;
		Temp->pNext = New;*/
		Temp->pNext = new Element<T>(Data, Temp->pNext);
		size++;
	}

	// deleting elements:
	void pop_front()
	{
		Element<T>* Temp = Head;//çàïîìèíàåì àäðåñ óäàëÿåìîãî ýëåìåíòà.
		Head = Head->pNext; //èñêëþ÷àåì ýëåìåíò èç ñïèñêà.
		delete Temp; //óäàëÿåì ýëåìåíò èç ïàìÿòè.
		size--;
	}

	void pop_back()
	{
		if (Head == nullptr)return;
		if (Head->pNext == nullptr)
		{
			pop_front();
			return;
		}
		Element<T>* Temp = Head;
		while (Temp->pNext->pNext)
		{
			Temp = Temp->pNext;
		}
		delete Temp->pNext;
		Temp->pNext = nullptr;
		size--;
	}

	void erase(int Index)
	{
		if (Index == 0)
		{
			pop_front();
			return;
		}
		if (Index >= Element::count)
		{
			return;
		}
		Element<T>* Temp = Head;
		for (int i = 0; i < Index - 1; i++)
		{
			if (Temp->pNext == nullptr)break;
			Temp = Temp->pNext;
		}
		Element<T>* toDel = Temp->pNext;
		Temp->pNext = Temp->pNext->pNext;
		delete toDel;
		size--;
	}

	void print()
	{
		//Element* Temp = Head; //Temp - ýòî èòåðàòîð.
		//Èòåðàòîð - ýòî ÓÊÀÇÀÒÅËÜ, ïðè ïîìîùè êîòîðîãî
		//ìîæíî ïîëó÷èòü äîñòóï ê ýëåìåíòàì ñòðóêòóðû äàííûõ.
		/*while (Temp != nullptr)
		{
		cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		Temp = Temp->pNext; //Ïåðåõîäèì íà ñëåäóþùèé ýëåìåíò.
		}*/
		for (Element<T>* Temp = Head; Temp; Temp = Temp->pNext)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		}
		cout << "Кол-во эл в списке: " << size << endl;
	}

	//friend ForwardList operator+(const ForwardList& left, const ForwardList& right);
	//template<typename T>
	//int ForwardList<T>::Element<T>::count = 0;

	//template<typename T>
	friend ForwardList<T> operator+(const ForwardList<T>& left, const ForwardList<T>& right)
	{
		ForwardList<T> result = left;
		/*for (ForwardList::Element* Temp = right.Head; Temp; Temp = Temp->pNext)
		{
		result.push_back(Temp->Data);
		}*/
		for (ForwardList<T>::Iterator it = right.begin(); it != right.end(); it++)
		{
			result.push_back(*it);
		}


		return result;

	}
};

void main()
{
	setlocale(LC_ALL, "");
	//int n; //Êîëè÷åñòâî ýëåìåíòîâ ñïèñêà.
	//std::cout << "Введите количество эл списка: "; std::cin >> n;
#ifdef BASE_CHECK
	ForwardList fl; //Ñîçäàåì ïóñòîé ñïèñîê.
	for (int i = 0; i < n; i++)
	{
		fl.push_back(rand() % 100);
	}
	fl.push_back(123);
	fl.print();
	cout << delimiter << endl;
	fl.pop_back();
	fl.print();
	cout << delimiter << endl;
	int Index;
	int Data;
	cout << "Ââåäèòå èíäåêñ äîáàâëÿåìîãî ýëåìåíòà: "; cin >> Index;
	//cout << "Ââåäèòå çíà÷åíèå äîáàâëÿåìîãî ýëåìåíòà: "; cin >> Data;
	//fl.insert(Index, Data);
	fl.erase(Index);
	fl.print();
	//delete new Element(666);
	//cout << int() << endl;

	/*ForwardList fl1;
	cout << "Ââåäèòå êîëè÷åñòâî ýëåìåíòîâ: "; cin >> n;
	for (int i = 0; i < n; i++)
	{
	fl1.push_back(rand() % 100);
	}
	fl1.print();*/
#endif // BASE_CHECK

#ifdef DESTRUCTOR_CHECK
	ForwardList chain;
	for (int i = 0; i < n; i++)
	{
		chain.push_back(rand() % 100);
	}
	//chain.print();
	cout << "List full" << endl;
#endif

#ifdef INDEX_OPERATOR_CHECK
	ForwardList fl(n);
	fl.print();
	for (int i = 0; i < fl.get_size(); i++)
	{
		fl[i] = rand() % 100;
	}
	for (int i = 0; i < fl.get_size(); i++)
	{
		std::cout << fl[i] << "\t";
	}
	std::cout << std::endl;
#endif // INDEX_OPERATOR_CHECK

#ifdef CONSTRUCTORS_CHECK
	ForwardList fl1 = { 3, 5, 8, 13, 21 }; //initializer_list constructor
	for (int i = 0; i < fl1.get_size(); i++)
		cout << fl1[i] << tab;
	cout << endl;
	ForwardList fl2 = fl1; //Copy constructor
	fl2.print();
#endif // CONSTRUCTORS_CHECK

#ifdef OPERATORS_CHECK
	ForwardList fl1 = { 3, 5, 8, 13, 21 };
	ForwardList fl2 = { 34, 55, 89 };
	for (int i = 0; i < fl1.get_size(); i++)
	{
		cout << fl1[i] << tab;
	}
	cout << endl;
	for (int i = 0; i < fl2.get_size(); i++)
	{
		cout << fl2[i] << tab;
	}
	cout << endl;

	ForwardList fl3;
	fl3 = fl1 + fl2;

	fl3.print();
#endif
#ifdef ITERATOR_CHECK

	/*int Arr[] = { 3,5,8,13,21 };

	for (int i = 0; i < sizeof(Arr)/sizeof(int); i++)
	{
	cout << Arr[i] << "\t" << endl;

	}
	cout << endl;

	for (int i : Arr)
	{
	cout << i << "\t";
	}
	cout << endl;

	cout << sizeof(Arr);*/

	ForwardList<int> fl = { 3,5,8,15,21 };
	for (int i : fl)
	{

		cout << i << "\t";

	}
	cout << endl;

	/*for (ForwardList::Iterator it = fl.begin(); it != fl.end(); it++)
	{
	cout << *it << "\t";
	}*/

	ForwardList<double> lfd = { 2.3, 2.15, 5.5 };
	lfd.print();
	for (double i : lfd)
	{
		cout << i << tab;
	}
	cout << endl;

	for (ForwardList<double>::Iterator it = lfd.begin(); it != lfd.end(); it++)
	{
		cout << *it << tab;
	}
	cout << endl;
#endif // ITERATOR_CHECK

	ForwardList<int> fl1 = { 3,5,8,12 };
	ForwardList<int> fl2 = { 21, 34, 55, 89 };
	for (ForwardList<int>::Iterator it = fl1.begin(); it != fl1.end(); it++)
	{
		cout << *it << tab;
	}
	cout << endl;

	for (ForwardList<int>::Iterator it = fl2.begin(); it != fl2.end(); it++)
	{
		cout << *it << tab;
	}
	cout << endl;

	ForwardList<int> lsd = fl1 + fl2;
	lsd.print();
}