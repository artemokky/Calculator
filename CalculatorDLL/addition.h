#pragma once
#include "operation.h"

class Addition : public AbstractOperation {
public:
	Addition() : AbstractOperation(OperationType::BIN, OperationPriority::LOW, "+") {}

	double calculate(const std::vector<double>& numbers) override {
		return numbers.at(0) + numbers.at(1);
	}

	~Addition() = default;
};