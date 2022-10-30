#pragma once
#include "../CalculatorDLL/operation.h"

class Pow : public AbstractOperation {
public:
	Pow() : AbstractOperation(OperationType::BIN, OperationPriority::HIGH, "^") {}

	double calculate(const std::vector<double>& num) override {
		return pow(num[1], num[0]);
	}

	~Pow() = default;
};

extern "C" __declspec(dllexport) AbstractOperation * LoadOperation() {
	return new Pow;
}