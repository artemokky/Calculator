#pragma once
#include "../CalculatorDLL/operation.h"

class Sinus : public AbstractOperation {
public:
	Sinus() : AbstractOperation(OperationType::PRE, OperationPriority::HIGH, "sin") {}

	double calculate(const std::vector<double>& num) override {
		return sin(num[0]);
	}

	~Sinus() = default;
};

extern "C" __declspec(dllexport) AbstractOperation * LoadOperation() {
	return new Sinus;
}