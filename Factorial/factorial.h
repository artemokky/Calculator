#pragma once
#include "../CalculatorDLL/operation.h"

class Factorial : public AbstractOperation {
public:
	Factorial() : AbstractOperation(OperationType::POST, OperationPriority::HIGH, "!") {}

	double calculate(const std::vector<double>& num) override {
		if (num[0] == 0 || num[0] == 1)
			return 1;

		if (num[0] < 0) {
			throw std::exception("Error: arg of factorial can't be less than 0");
			return 0;
		}

		long result = 1;
		int arg = num[0];

		for (int i = 2; i <= arg; ++i)
			result *= i;

		return result;
	}

	~Factorial() = default;
};

extern "C" __declspec(dllexport) AbstractOperation* LoadOperation() {
	return new Factorial;
}