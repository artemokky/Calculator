#include "calculator.h"

int main() {
	string path = ("../DLLS"); // Path to DLLs

	Calculator calculator; // Init calculator
	calculator.Run(path);  // Run calculator

	return 0;
}