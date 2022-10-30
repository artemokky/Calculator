#pragma once
#include "operation.h"

class Division : public AbstractOperation {
public:
	Division() : AbstractOperation(OperationType::BIN, OperationPriority::MID, "/") {}

	double calculate(const std::vector<double>& numbers) override {
		return numbers.at(1) / numbers.at(0);
	}

	~Division() = default;
};

