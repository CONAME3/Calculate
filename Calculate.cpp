#include <iostream>
#include <sstream>
#include <stack>
#include <conio.h> 
#define M_PI 3.14

using namespace std;
const float VERSION = 0.4f;

enum Mode
{
	Standart = 1,
	Triangle = 2,
	Circle = 3
};

enum Keys
{
	Left = 75,
	Right = 77
};

struct Token
{
	char symbol;
	double value;
};

void Select_Mode(bool& end, Mode& selected)
{
	cout << "   Выберите режим." << endl << "     Выйти     Стандартный     Триугольник     Окружность";
	short key = 0;
	short num_mode = selected;
	if (num_mode == 1) { cout << "\033[3;14H" << "->"; }
	else if (num_mode == 2) { cout << "\033[3;30H" << "->"; }
	else if (num_mode == 3) { cout << "\033[3;46H" << "->"; }

	while (key != 13)
	{
		key = _getch();
		if (key == Left)
		{
			if (num_mode == 0) { continue; }
			else if (num_mode == 1)
			{
				cout << "\033[3;14H" << "  ";
				cout << "\033[3;4H" << "->";
				num_mode -= 1;
			}
			else if (num_mode == 2)
			{
				cout << "\033[3;30H" << "  ";
				cout << "\033[3;14H" << "->";
				num_mode -= 1;
			}
			else if (num_mode == 3)
			{
				cout << "\033[3;46H" << "  ";
				cout << "\033[3;30H" << "->";
				num_mode -= 1;
			}
		}
		if (key == Right)
		{
			if (num_mode == 3) { continue; }
			else if (num_mode == 0)
			{
				cout << "\033[3;4H" << "  ";
				cout << "\033[3;14H" << "->";
				num_mode += 1;
			}
			else if (num_mode == 1)
			{
				cout << "\033[3;14H" << "  ";
				cout << "\033[3;30H" << "->";
				num_mode += 1;
			}
			else if (num_mode == 2)
			{
				cout << "\033[3;30H" << "  ";
				cout << "\033[3;46H" << "->";
				num_mode += 1;
			}
		}
	}
	if (num_mode != 0) selected = Mode(num_mode);
	else { end = true; }
	cout << "\033[2;1H\033[0J";
}

int Check_Priority(char ch)
{
	if (ch == '^') { return 3; }
	else if (ch == '*' || ch == '/') { return 2; }
	else if (ch == '+' || ch == '-') { return 1; }
	else return 0;
}

void Standart_Math(stack <Token>& stack_nums, stack <Token>& stack_op, Token& item)
{
	double a, b;

	a = stack_nums.top().value;
	stack_nums.pop();
	b = stack_nums.top().value;
	stack_nums.pop();
	item.symbol = '0';

	switch (stack_op.top().symbol) {
	case '^':
		item.value = pow(b, a);
		break;
	case '*':
		item.value = a * b;
		break;
	case '/':
		if (a == 0) { cerr << endl << "Деление на нуль."; system("pause"); exit(1); }
		item.value = b / a;
		break;
	case '+':
		item.value = a + b;
		break;
	case '-':
		item.value = b - a;
		break;
	}
	stack_nums.push(item);
	stack_op.pop();
}

double Standart_Calculate()
{
	char ch;
	double a, b, value;

	stack <Token> stack_nums;
	stack <Token> stack_op;
	Token item;

	string str;
	getline(cin, str);
	stringstream sstr{ str };

	while (true)
	{
		ch = sstr.peek();
		if (ch == '\377') { break; }
		if (ch == ' ') { sstr.ignore(); continue; }
		if (ch >= '0' && ch <= '9') {
			sstr >> value;
			item.symbol = '0';
			item.value = value;
			stack_nums.push(item);
			continue;
		}
		else if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^')
		{
			item.symbol = ch;
			item.value = 0;
			if (stack_op.size() == 0)
			{
				stack_op.push(item);
				sstr.ignore();
				continue;
			}
			if (stack_op.size() != 0 && Check_Priority(ch) > Check_Priority(stack_op.top().symbol))
			{
				stack_op.push(item);
				sstr.ignore();
				continue;
			}
			else { Standart_Math(stack_nums, stack_op, item); continue; }
		}
		else if (ch == '(')
		{
			item.symbol = ch;
			item.value = 0;
			stack_op.push(item);
			sstr.ignore();
			continue;
		}
		else if (ch == ')')
		{
			while (stack_op.top().symbol != '(') { Standart_Math(stack_nums, stack_op, item); }
			item.symbol = ch;
			item.value = 0;
			stack_op.pop();
			sstr.ignore();
			continue;
		}
		else { cerr << endl << "Некорректный ввод."; system("pause"); exit(1); }
	}
	while (stack_op.size() != 0) { Standart_Math(stack_nums, stack_op, item); }
	return stack_nums.top().value;
}

void Triangle_Math()
{
	double a, b, y, A, B, C, p, s;
	cin >> A >> B >> C;
	if (A == 0 || B == 0 || C == 0) { cerr << endl << "Введены не все стороны."; system("pause"); exit(1); }

	p = (A + B + C) / 2;
	s = sqrt(p * (p - A) * (p - B) * (p - C));
	if (s <= 0) { cerr << endl << "Триугольник с такими сторонами не может существовать."; system("pause"); exit(1); }

	p = 180 / (A + B + C);
	a = A * p;
	b = B * p;
	y = C * p;

	cout << endl << "   Угол(a) = " << a << "   Угол(b) = " << b << "   Угол(y) = " << y << "   Площадь(s) = " << s << endl;
}

void Circle_Math()
{
	char ch;
	double n, r, d, c, s;
	cin >> ch >> n;

	if (ch == 'r')
	{
		r = n;
		d = r * 2;
		c = d * M_PI;
	}
	else if (ch == 'd')
	{
		d = n;
		r = d / 2;
		c = d * M_PI;
	}
	else if (ch == 'c')
	{
		c = n;
		d = c / M_PI;
		r = d / 2;
	}
	else { cerr << endl << "Некорректный ввод."; system("pause"); exit(1); }

	s = M_PI * pow(r, 2);
	cout << endl << "   Радиус(r) = " << r << "   Диаметр(d) = " << d << "   Длинна(c) = " << c << "   Площадь(s) = " << s << endl;
}

int main()
{
	setlocale(LC_ALL, "Russian");
	Mode selected_mode = Standart;
	double output;
	bool end = false;
	cout << "   Калькулятор v" << VERSION << endl;

	while (true)
	{
		Select_Mode(end, selected_mode);
		if (end == true) { break; }

		switch (selected_mode) {
		case Standart:
			cout << "   Введите выражение: ";
			output = Standart_Calculate();
			cout << endl << "   Результат равен: " << output << endl;
			break;
		case Triangle:
			cout << "   Введите три стороны триугольника через пробел: ";
			Triangle_Math();
			break;
		case Circle:
			cout << "   Введите символ известной величины и его значение через пробел." << endl << "   r - радиус, d - диаметр, c - длина окружности: ";
			Circle_Math();
			break;
		default:
			cerr << endl << "Неизвестный режим."; system("pause"); exit(1);
		}
		system("pause");
		cout << "\033[2;1H\033[0J";
	}
}