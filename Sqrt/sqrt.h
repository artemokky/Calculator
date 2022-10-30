#pragma once
#include "../CalculatorDLL/operation.h"

class Sqrt : public AbstractOperation {
public:
	Sqrt() : AbstractOperation(OperationType::PRE, OperationPriority::HIGH, "sqrt") {}

	double calculate(const std::vector<double>& num) override {
		return sqrt(num[0]);
	}

	~Sqrt() = default;
};

extern "C" __declspec(dllexport) AbstractOperation* LoadOperation() {
	return new Sqrt;
}