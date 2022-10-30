#pragma once
#include "../CalculatorDLL/operation.h"

class Ln : public AbstractOperation {
public:
	Ln() : AbstractOperation(OperationType::PRE, OperationPriority::HIGH, "ln") {}

	double calculate(const std::vector<double>& num) override {
		return log(num[0]);
	}

	~Ln() = default;
};

extern "C" __declspec(dllexport) AbstractOperation * LoadOperation() {
	return new Ln;
}