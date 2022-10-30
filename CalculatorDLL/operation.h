#pragma once
#include <string>
#include <vector>
#include <cmath>

// Base class for operations
class AbstractOperation {
public:

	/*
	* BIN - if binary, example - a + b
	* POST - if postfix, example - a!
	* PRE - if prefix, example sin(a)
	* NULL_TYPE - exception
	*/
	enum class OperationType {
		BIN,
		POST,
		PRE,
		NULL_TYPE
	};

	/*
	* LOW < MID < HIGH
	* example:
	* a+b < a/b < a^b
	*/
	enum class OperationPriority {
		LOW,
		MID,
		HIGH
	};

private:
	OperationType type;
	OperationPriority priority;
	// Name - that is the way it will be written in the expression
	std::string name;

public:
	
	AbstractOperation(OperationType type, OperationPriority priority, std::string name) {
		this->type = type;
		this->priority = priority;
		this->name = name;
	}

	virtual double calculate(const std::vector<double>&) = 0;


	OperationPriority getPriority() {
		return priority;
	}

	OperationType getType() {
		return type;
	}

	std::string toString() {
		return name;
	}

	virtual ~AbstractOperation() = default;

};