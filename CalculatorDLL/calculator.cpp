#include "calculator.h"

void Calculator::initOperations() {
	// Init usual operands + * - /
	Operation add(new Addition);
	Operation mult(new Multiplication);
	Operation sub(new Substraction);
	Operation div(new Division);

	// Add to map, accses - O(logn)
	operations[add->toString()] = add;
	operations[mult->toString()] = mult;
	operations[sub->toString()] = sub;
	operations[div->toString()] = div;
}

void Calculator::loadOperations(const std::string& pluginsPath) {
	//Find directory
	if (!std::filesystem::exists(pluginsPath))
		throw std::exception("Error: No such directory");

	//For each .dll
	for (auto plug : std::filesystem::directory_iterator(pluginsPath)) {
		auto dll = LoadLibrary((plug.path().c_str()));
		if (!dll)
			throw std::exception("Error: Wrong file format");

		//Loading operation from .dll
		auto load = (AbstrOper*)GetProcAddress(dll, "LoadOperation");
		if (!load)
			throw std::exception("Error: Invalid dll library");
		Operation oper(load());
		//Add to map
		operations[oper->toString()] = oper;
	}
}

bool Calculator::readExpression() {
	// Read expression - full line
	std::getline(std::cin, expression);

	return !expression.empty();
}

OperType Calculator::getOperationType(const std::string& token) {
	// Try find type of operation
	auto tmp = operations.find(token);

	// Can be possible if token == number
	if (tmp == operations.end()) {
		return OperType::NULL_TYPE;
	}

	// Return types PREfix POSTfix BINary
	return tmp->second->getType();
}

bool Calculator::isNumber(const string& token) {
	// Checking for number

	// Can be not a negative number but a minus
	if (token == "-") {
		return false;
	}

	// For each symbol checking
	for (char sym : token) {
		if (!isdigit(sym) && sym != '.' && sym != '-') {
			return false;
		}
	}

	return true;
}

bool Calculator::isOperation(const std::string& token) {
	// Try to find operation that operation.name == token
	return operations.find(token) != operations.end();
}

bool Calculator::isLower(const std::string& token1, const std::string& token2) {
	// Compare operations priority
	auto tmp1 = operations.find(token1);
	auto tmp2 = operations.find(token2);

	return tmp1->second->getPriority() >= tmp2->second->getPriority();
}

void Calculator::fillClosingBrackets() {
	// Try to fill bracket in string stack
	if (stack) {
		while (stack.peek() != "(") {
			notation.push_back(stack.pop());
		}
	}
	stack.pop();
}

void Calculator::fillBinaryOperation(const string& token) {
	// Filling binary operation

	// While stack that full of bracket body - try to get it for polish notation
	while (stack && isOperation(stack.peek()) &&
		(getOperationType(stack.peek()) == OperType::PRE || isLower(stack.peek(), token))) {

		notation.push_back(stack.pop());
	}

	stack.push(token);
}

string Calculator::parseToken(const string& str, int& index) {
	// Token parsing
	string token;
	// Dot flag - for correct number parsing
	bool wasDot = false;

	// If number
	if (isdigit(str[index])) {
		// While str[index] == number or dot
		while (index < str.size() && (isdigit(str[index]) || str[index] == '.')) {
			// If dot
			if (str[index] == '.') {
				// If first dot - OK
				if (!wasDot) {
					token.push_back(str[index]);
					index++;
					wasDot = true;
					// Push next digit to token
					if (isdigit(str[index])) {
						token.push_back(str[index]);
						index++;
					}
					// If next digit absent - wrong number form, example - 101.
					else {
						
						throw exception("Error: Wrong nubmer form");
					}
					continue;
				}
				// If dots in number more than 1, example - 101.10.1
				else {
					throw exception("Error: Wrong nubmer form");
				}
			}
			// Pushing next digit
			token.push_back(str[index]);
			index++;
		}
	}
	// If bracket
	else if (str[index] == '(' || str[index] == ')') {
		token.push_back(str[index]);
		index++;
	}
	// If operation or smth
	else {
		for (auto& operation : operations) {
			// Checking input str for each exist operation, from str[index] to str[index + op.length]
			auto tmp = str.substr(index, operation.first.size());
			// If true - push return token operation
			if (tmp.compare(operation.first) == 0) {
				token = tmp;
				index += int(token.size());
				return token;
			}
		}
		throw exception("Error: Unidentified symbol");
		token = str[index];
	}
	return token;
}

void Calculator::toPolishNotation() {
	for (int i = 0; i < expression.size();) {
		if (isspace(expression[i])) {
			i++;
			continue;
		}
	    
		auto token = parseToken(expression, i);
		
		if (isNumber(token) || getOperationType(token) == OperType::POST) {
			notation.push_back(token);
		}
		else if (getOperationType(token) == OperType::PRE || token == "(") {
			stack.push(token);
		}
		else if (token == ")") {
			fillClosingBrackets();
		}
		else if (getOperationType(token) == OperType::BIN) {
			fillBinaryOperation(token);
		}
	}

	while (stack) {
		notation.push_back(stack.pop());
	}
}

double Calculator::Calculate() {
	MyStack<double> calcStack;

	for (int i = 0; i < notation.size(); ++i) {
		if (isNumber(notation[i])) {
			calcStack.push(std::stod(notation[i]));
		}
		else {
			auto& op = operations.at(notation[i]);
			if (op->getType() == OperType::BIN) {
				calcStack.push(op->calculate({ calcStack.pop(), calcStack.pop()}));
			}
			else {
				calcStack.push(op->calculate({ calcStack.pop() }));
			}
		}
	}

	notation.clear();
	return calcStack.pop();
}

void Calculator::Run(const std::string& pluginsPath) {
	initOperations();

	try {
		loadOperations(pluginsPath);
	}
	catch (std::exception ex) {
		std::cout << ex.what() << std::endl;
		return;
	}

	while(readExpression()){
		try {
			toPolishNotation();
		}
		catch (exception ex) {
			std::cout << ex.what() << std::endl;
			return;
		}

		double result;
		try {
			result = Calculate();
		}
		catch (exception ex) {
			std::cout << ex.what() << std::endl;
			return;
		}
		std::cout << "Result is: " << result << std::endl;
	}
}
