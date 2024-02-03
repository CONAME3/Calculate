#include <iostream>
#include <sstream>
#include <stack>

using namespace std;
const float VERSION = 0.2f;

enum Mode
{
	Standart,
	Sqrt,
};

struct Token
{
	char symbol;
	double value;
};

Mode Select_Mode(Mode& selected)
{
	selected = Standart;
	return selected;
}

int Check_Priority(char ch)
{
	if (ch == '^') { return 3; }
	else if (ch == '*' || ch == '/') { return 2; }
	else if (ch == '+' || ch == '-') { return 1; }
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

	while (true) {
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
		if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^') {

			item.symbol = ch;
			item.value = 0;
			if (stack_op.size() == 0) {
				stack_op.push(item);
				sstr.ignore();
				continue;
			}
			if (stack_op.size() != 0 && Check_Priority(ch) > Check_Priority(stack_op.top().symbol)) {
				stack_op.push(item);
				sstr.ignore();
				continue;
			}
			else { Standart_Math(stack_nums, stack_op, item); continue; }
		}
		if (ch == '(') {
			item.symbol = ch;
			item.value = 0;
			stack_op.push(item);
			sstr.ignore();
			continue;
		}
		if (ch == ')') {
			while (stack_op.top().symbol != '(') { Standart_Math(stack_nums, stack_op, item); }
			item.symbol = ch;
			item.value = 0;
			stack_op.pop();
			sstr.ignore();
			continue;
		}
		else { cerr << endl << "Некорректный ввод."; system("pause"); exit(1); } // Добавить обработку ошибок (безусловный переход)
	}
	while (stack_op.size() != 0) { Standart_Math(stack_nums, stack_op, item); }

	return stack_nums.top().value;
}

double Sqrt_Math()
{
	double result = 0.0;
	return result;
}

int main()
{
	setlocale(LC_ALL, "Russian");
	Mode selected_mode = Standart;
	double output;
	bool end = false;

	while (end != true)
	{
		Select_Mode(selected_mode);
		cout << "   Калькулятор v" << VERSION << endl;

		switch (selected_mode) {
		case Standart:
			cout << "   Введите выражение: ";
			output = Standart_Calculate();
			break;
		case Sqrt:
			output = Sqrt_Math();
			break;
		default:
			cerr << endl << "Неизвестный режим.";
			system("pause");
			exit(1);
		}
		cout << endl << "   Результат равен: " << output << endl;
		system("pause");


		cout << "\033[2J\033[1;1H";
	}
	return 0;
}