#pragma once
#include "../CalculatorDLL/operation.h"

class Mod : public AbstractOperation {
public:
	Mod() : AbstractOperation(OperationType::BIN, OperationPriority::HIGH, "%") {}

	double calculate(const std::vector<double>& num) override {
		return static_cast<int>(num[1]) % static_cast<int>(num[0]);
	}

	~Mod() = default;
};

extern "C" __declspec(dllexport) AbstractOperation * LoadOperation() {
	return new Mod;
}