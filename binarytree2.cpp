#include <iostream>
#include <string>
using namespace std;

int tabs = 0; 
int kol_vo = 0;

class Bus 
{
	string number; //номер автобуса (кт042)
	string surname; // фамилия водителя
	string name; // имя водителя
	int nummarshrut;// номер маршрута
	int mesta; // кол-во мест в автобусе

public:
	Bus() { number = "none"; surname = "empty"; name = "empty"; nummarshrut = 0; mesta = 0; }
	Bus(string anumber, string asurname, string aname, int anummarshrut,int amesta ) 
	{
		number = anumber;
		surname = asurname;
		name = aname;
		nummarshrut = anummarshrut; 
		mesta = amesta; 
	}
	int Get_number()
	{
		string a = this->number.substr(2, 3);
		return  stoi(a); /* номер автобуса(только его числовая часть)*/;
	}
	void Printinfo()
	{
		cout << "Surname: " << surname << endl;
		cout << "Name: " << name << endl;
		cout << "Reg_number: " << number << endl;
		cout << "Marshrut: " << nummarshrut << endl;
		cout << "Mest: " << mesta << endl;
	}
	string Get_fullnumber()
	{

		return  number;
	}


};


struct Branch
{
	Bus avtobus; 
	Branch* LeftBranch; 
	Branch* RightBranch;
};


void Add(Bus abus, Branch*& aBranch)
{
	if (!aBranch)
	{ 
		aBranch = new Branch;
		aBranch->avtobus = abus;
		aBranch->LeftBranch = 0;
		aBranch->RightBranch = 0;
		return;
	}
	else 
		if (aBranch->avtobus.Get_number() < abus.Get_number())
		{ 
			Add(abus, aBranch->LeftBranch);
		}
		else
		{ 
			Add(abus, aBranch->RightBranch);
		};
}


void print(Branch* aBranch)
{
	if (!aBranch) return; 
	tabs += 5; //Иначе увеличим счетчик рекурсивно вызванных процедур
	//Который будет считать нам отступы для красивого вывода

	print(aBranch->LeftBranch); //Выведем ветку и ее подветки слева

	for (int i = 0; i < tabs; i++) cout << " "; //Потом отступы
	aBranch->avtobus.Printinfo(); //Данные этой ветки


	print(aBranch->RightBranch);//И ветки, что справа

	tabs -= 5; //После уменьшим кол-во отступов
	return;
}

void pr_obh(Branch*& aBranch)
{
	if (NULL == aBranch)    return;    //Если дерева нет, выходим

	aBranch->avtobus.Printinfo(); //Посетили узел
	pr_obh(aBranch->LeftBranch); //Обошли левое поддерево   
	pr_obh(aBranch->RightBranch); //Обошли правое поддерево
}

void add_elem(Bus abus, Branch*& aBranch)
{
	if (!aBranch)
	{
		aBranch = new Branch;
		aBranch->avtobus = abus;
		aBranch->LeftBranch = 0;
		aBranch->RightBranch = 0;
		return;
	}
	else
	{
		if (abus.Get_number() < aBranch->avtobus.Get_number()) {
			add_elem(abus, aBranch->LeftBranch);
		}
		else if (abus.Get_number() > aBranch->avtobus.Get_number()) {
			add_elem(abus, aBranch->RightBranch);
		}
	}
}

void is_Empty(Branch*& aBranch)
{
	if (!aBranch)
	{
		cout << "Дерево пустое...";
	}
	else
	{
		cout << "Дерево не пустое...";
	}
}

void FreeTree(Branch* aBranch)
{
	if (!aBranch) return;
	FreeTree(aBranch->LeftBranch);
	FreeTree(aBranch->RightBranch);
	delete aBranch;
	return;
}

Branch* del_elem(Branch*& aBranch, string abus) {
	if (aBranch == NULL)
		return aBranch;

	if (abus == aBranch->avtobus.Get_fullnumber()) {

		Branch* tmp;
		if (aBranch->RightBranch == NULL)
			tmp = aBranch->LeftBranch;
		else {

			Branch* ptr = aBranch->RightBranch;
			if (ptr->LeftBranch == NULL) {
				ptr->LeftBranch = aBranch->LeftBranch;
				tmp = ptr;
			}
			else {

				Branch* pmin = ptr->LeftBranch;
				while (pmin->LeftBranch != NULL) {
					ptr = pmin;
					pmin = ptr->LeftBranch;
				}
				ptr->LeftBranch = pmin->RightBranch;
				pmin->LeftBranch = aBranch->LeftBranch;
				pmin->RightBranch = aBranch->RightBranch;
				tmp = pmin;
			}
		}

		delete aBranch;
		return tmp;
	}
	else if (stoi(abus.substr(2,3)) < aBranch->avtobus.Get_number())
		aBranch->LeftBranch = del_elem(aBranch->LeftBranch, abus);
	else
		aBranch->RightBranch = del_elem(aBranch->RightBranch, abus);
	return aBranch;
}

int main()
{
	setlocale(LC_ALL, "rus");
	Branch* Root = 0;
	int vel;

	cout << "Введите кол-во элементов для будущего дерева: ";
	cin >> vel;
	cout << endl;

	cout << "Проверим дерево на пустоту до его заполнения: " << endl;
	is_Empty(Root);
	cout << endl;

	for (int i = 0; i < vel; i++)
	{
		cout << "Surname: " << endl;
		string sname;
		cin >> sname;
		cout << "Name: " << endl;
		string name;
		cin >> name;
		cout << "Reg_number: " << endl;
		string rn;
		cin >> rn;
		cout << "Marshrut: " << endl;
		int mt;
		cin >> mt;
		cout << "Mest: " <<endl;
		int side;
		cin >> side;
		Bus nbus(rn,sname,name,mt,side);
		/* заполнить объек Автобус*/
		Add(nbus, Root);
	}

	cout << "Проверим дерево на пустоту после его заполнения: " << endl;
	is_Empty(Root);
	cout << endl;

	cout << "Вывод бинарного дерева: " << endl;
	print(Root);
	cout << endl;

	cout << "Прямой обход бинарного дерева: " << endl;
	pr_obh(Root);
	cout << endl;

	cout << "Добавим новый элемент в бинарное дерево:" << endl;
	cout << "Введите новый элемент: ";
	cout << "Surname: " << endl;
	string sname;
	cin >> sname;
	cout << "Name: " << endl;
	string name;
	cin >> name;
	cout << "Reg_number: " << endl;
	string rn;
	cin >> rn;
	cout << "Marshrut: " << endl;
	int mt;
	cin >> mt;
	cout << "Mest: " << endl;
	int side;
	cin >> side;
	Bus nbus(rn, sname, name, mt, side);
	add_elem(nbus, Root);

	cout << "Вывод бинарного дерева: " << endl;
	print(Root);
	cout << endl;

	cout << "Удалим элемент из бинарного дерева:" << endl;
	cout << "Введите элемент: ";
	string num;
	cin >> num;
	del_elem(Root, num);

	cout << "Вывод бинарного дерева: " << endl;
	print(Root);
	cout << endl;


	FreeTree(Root);
	cout << "Вся динамическая память очищена..." << endl;

	return 0;
}