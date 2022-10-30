#pragma once
#include "mystack.h"
#include "addition.h"
#include "multiplication.h"
#include "substraction.h"
#include "division.h"

#include <map>
#include <memory>
#include <stack>
#include <filesystem>
#include <windows.h>
#include <iostream>
#include <string>
#include <vector>

using AbstrOper = AbstractOperation*(void);
using Operation = std::shared_ptr<AbstractOperation>;
using OperType = AbstractOperation::OperationType;

using std::string;
using std::exception;

class Calculator {
private:
	std::map<string, Operation> operations;

	string expression;

	MyStack<string> stack;

	std::vector<string> notation;

	void initOperations();
	void loadOperations(const string& path);

	bool readExpression();

	OperType getOperationType(const string& token);

	bool isOperation(const string& token);
	bool isNumber(const string& token);
	bool isLower(const string& token1, const string& token2);

	string parseToken(const string& str, int& index);

	void fillClosingBrackets();
	void fillBinaryOperation(const string& token);

	void toPolishNotation();

	double Calculate();

public:
	void Run(const std::string& pluginsPath);
};