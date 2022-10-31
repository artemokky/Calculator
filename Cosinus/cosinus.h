#pragma once
#include "../CalculatorDLL/operation.h"

class Cosinus : public AbstractOperation {
public:
	Cosinus() : AbstractOperation(OperationType::PRE, OperationPriority::HIGH, "cos") {}

	double calculate(const std::vector<double>& num) override {
		return cos(num[0]);
	}

	~Cosinus() = default;
};

extern "C" __declspec(dllexport) AbstractOperation * LoadOperation() {
	return new Cosinus;
}