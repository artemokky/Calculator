#pragma once
#include "operation.h"

class Substraction : public AbstractOperation {
public:
	Substraction() : AbstractOperation(OperationType::BIN, OperationPriority::LOW, "-") {}

	double calculate(const std::vector<double>& numbers) override {
		return numbers.at(1) - numbers.at(0);
	}

	~Substraction() = default;
};

