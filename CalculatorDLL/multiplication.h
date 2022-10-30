#pragma once
#include "operation.h"

class Multiplication : public AbstractOperation {
public:
	Multiplication() : AbstractOperation(OperationType::BIN, OperationPriority::MID, "*") {}

	double calculate(const std::vector<double>& numbers) override {
		return numbers.at(0) * numbers.at(1);
	}

	~Multiplication() = default;
};

