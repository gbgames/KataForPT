
#include "CoinAccepter.h"
#include "VendingMachineApp.h"
#include "VendingMachineDisplay.h"
#include <iostream>

int main(int argc, char** argv)
{
	CoinAccepter accepter;
	VendingMachineDisplay display(accepter);
	VendingMachineApp app(std::cout, accepter, display);
	app.run(std::cin);

	return 0;
}
