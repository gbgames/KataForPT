
#include "CoinAccepter.h"
#include "ProductSelectionService.h"
#include "SelectionValidator.h"
#include "VendingMachineApp.h"
#include "VendingMachineDisplay.h"
#include <iostream>

int main(int argc, char** argv)
{
	CoinAccepter accepter;
	ProductSelectionService selectionService;
	SelectionValidator validator(accepter, selectionService);
	VendingMachineDisplay display(accepter, validator);
	VendingMachineApp app(std::cout, accepter, display);
	app.run(std::cin);

	return 0;
}
