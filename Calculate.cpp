#include <iostream>
#include <sstream>
#include <stack>
#include <windows.h>
#include <conio.h>
#include <math.h>

using namespace std;
const float VERSION = 0.1f;

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

Mode Select_Mode(Mode &selected)
{
	if (selected == NULL) {
		
	}
	selected = Standart;
	return selected; // Выбранный пользователем режим.
}

double Standart_Math()
{
	char ch;
	double a, b, value;
	double static _result;

	stack <Token> stack_numbers;
	stack <Token> stack_operands;
	Token item;

	string str;
	getline(std::cin, str);
	stringstream sstr{ str };

	while (true) {
		ch = sstr.peek();
		if (ch == '\377') { break; }
		if (ch == ' ') { sstr.ignore(); continue; }
		if (ch >= '0' && ch <= '9') {
			sstr >> value;
			item.symbol = '0';
			item.value = value;
			stack_numbers.push(item);
			continue;
		}
		if (ch == '^' || ch == '*' || ch == '/' || ch == '+' || ch == '-') {
			item.symbol = ch;
			item.value = 0;
			stack_operands.push(item);
			sstr.ignore();
			continue;
		}
		else { cerr << endl << "Некорректный ввод."; }
	}

	while (stack_operands.size() != 0) {

		a = stack_numbers.top().value;
		stack_numbers.pop();
		b = stack_numbers.top().value;

		switch (stack_operands.top().symbol) {
		case '^':
			return 0.0;
		case '*':
			_result = a * b;
			break;
		case '/':
			if (a == 0) { cerr << endl << "Деление на нуль."; }
			_result = b / a;
			break;
		case '+':
			_result = a + b;
			break;
		case '-':
			_result = b - a;
			break;
		}
		item.symbol = '0';
		item.value = _result;
		stack_numbers.push(item);
		stack_operands.pop();
	}
	return _result;
}

double Sqrt_Math()
{
	double result_value = 0.0;
	return result_value;
}

int main()
{
	setlocale(LC_ALL, "Russian");

	double static result;
	Mode selected_mode;
	bool end = false;

	Select_Mode(selected_mode);

	while (end != true)
	{
		cout << "   Калькулятор v" << VERSION << endl;
		switch (selected_mode) {
		case Standart:
			cout << "   Введите выражение: ";
			result = Standart_Math();
			break;
		case Sqrt:
			result = Sqrt_Math();
			break;
		default:
			cerr << endl << "Неизвестный режим.";
		}
		cout << endl << "   Результат равен: " << result << endl;
		system("pause");

		cout << "\033[2J\033[1;1H";
		Select_Mode(selected_mode);
	}
	return 0;
}