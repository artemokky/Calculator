#pragma once
#include "../CalculatorDLL/operation.h"

class Exp : public AbstractOperation{
public:
	Exp() : AbstractOperation(OperationType::PRE, OperationPriority::HIGH, "exp") {}

	double calculate(const std::vector<double>& num) override {
		return exp(num[0]);
	}

	~Exp() = default;
};

extern "C" __declspec(dllexport) AbstractOperation * LoadOperation() {
	return new Exp;
}