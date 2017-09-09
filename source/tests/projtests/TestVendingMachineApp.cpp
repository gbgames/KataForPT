/*
    Copyright 2017 Gianfranco Berardi. 
 	
	This file is part of the KataForPT.

    The KataForPT is free software: 
	you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    KataForPT is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with KataForPT.  If not, see <http://www.gnu.org/licenses/>.
 */ 

#include "CoinAccepter.h"
#include "VendingMachineApp.h"
#include "ProductSelectionService.h"
#include "SelectionValidator.h"
#include "VendingMachineDisplay.h"
#include "gmock/gmock.h"

using namespace testing;

class VendingMachineAppFixture : public Test
{
	public:
		VendingMachineAppFixture() : validator(accepter, selectionService), display(accepter, validator), app(output, accepter, display, validator) {}
		~VendingMachineAppFixture() {}
	
		std::string getNextOutputLine()
		{
			std::string line;
			std::getline(output, line);

			return line;
		}

		AssertionResult verifyColaMoneyAdded()
		{
			std::stringstream input;
			input << "qqqqa1." << std::endl;

			app.run(input);

			if ("INSERT COIN" != getNextOutputLine()
				|| "0.25" != getNextOutputLine()
				|| "0.50" != getNextOutputLine()
				|| "0.75" != getNextOutputLine()
				|| "1.00" != getNextOutputLine())
			{
				return AssertionFailure() << "Something went wrong when inserting money to purchase cola.";
			}

			return AssertionSuccess();
		}

		AssertionResult purchaseCola()
		{
			AssertionResult result = verifyColaMoneyAdded();

			if ("THANK YOU" != getNextOutputLine())
			{
				if (!result)
				{
					return result << " AND Customer was not thanked for purchasing cola";
				} 
				else
				{
					return AssertionFailure() << "Customer was not thanked for purchasing cola";
				}
			}
			if (COLA_PRODUCT != selectionService.dispensedItem())
			{
				if (!result)
				{
					return result << "Cola was not dispensed to customer. What was found was item # " << selectionService.dispensedItem();
				}
				else
				{
					return AssertionFailure() << "Cola was not dispensed to customer. What was found was item # " << selectionService.dispensedItem();
				}
			}

			return result;
		}

	std::stringstream output;
	CoinAccepter accepter;
	ProductSelectionService selectionService;
	SelectionValidator validator;
	VendingMachineDisplay display;
	VendingMachineApp app;
};

TEST_F(VendingMachineAppFixture, WhenUserEntersQThenAppInsertsAQuarter)
{
	std::stringstream input;
	input << 'q' << std::endl;

	app.run(input);

	std::string defaultLine(getNextOutputLine());
	EXPECT_THAT(defaultLine, StrEq("INSERT COIN"));

	std::string quarterAmount(getNextOutputLine());
	EXPECT_THAT(quarterAmount, StrEq("0.25"));
}

TEST_F(VendingMachineAppFixture, WhenUserEntersDThenAppInsertsADime)
{
	std::stringstream input;
	input << 'd' << std::endl;

	app.run(input);

	std::string defaultLine(getNextOutputLine());
	EXPECT_THAT(defaultLine, StrEq("INSERT COIN"));

	std::string dimeAmount(getNextOutputLine());
	EXPECT_THAT(dimeAmount, StrEq("0.10"));
}

TEST_F(VendingMachineAppFixture, WhenUserEntersNThenAppInsertsANickel)
{
	std::stringstream input;
	input << 'n' << std::endl;

	app.run(input);

	std::string defaultLine(getNextOutputLine());
	EXPECT_THAT(defaultLine, StrEq("INSERT COIN"));

	std::string nickelAmount(getNextOutputLine());
	EXPECT_THAT(nickelAmount, StrEq("0.05"));
}

TEST_F(VendingMachineAppFixture, WhenUserEntersPThenAppInsertsAPenny)
{
	std::stringstream input;
	input << 'p' << std::endl;

	app.run(input);

	std::string defaultLine(getNextOutputLine());
	EXPECT_THAT(defaultLine, StrEq("INSERT COIN"));

	std::string noPennyLine(getNextOutputLine());
	EXPECT_THAT(noPennyLine, StrEq("INSERT COIN"));

	EXPECT_THAT(accepter.returnedCoins().size(), Eq(1));
}

TEST_F(VendingMachineAppFixture, WhenUserEntersRThenAppDisplaysReturnedCoins)
{
	std::stringstream input;
	input << 'p' << std::endl;
	input << 'p' << std::endl;
	input << 'p' << std::endl;
	input << 'r' << std::endl;

	app.run(input);

	EXPECT_THAT(getNextOutputLine(), StrEq("INSERT COIN"));
	EXPECT_THAT(getNextOutputLine(), StrEq("INSERT COIN"));
	EXPECT_THAT(getNextOutputLine(), StrEq("INSERT COIN"));
	EXPECT_THAT(getNextOutputLine(), StrEq("INSERT COIN"));

	std::string noPennyLine(getNextOutputLine());
	EXPECT_THAT(noPennyLine, StrEq("Returned: rejected coin, rejected coin, rejected coin"));
}

TEST_F(VendingMachineAppFixture, WhenCustomerSelectsProductThenDisplayPrice)
{
	std::stringstream input;
	input << "a1" << std::endl;
	input << "b2" << std::endl;
	input << "c3" << std::endl;

	app.run(input);

	EXPECT_THAT(getNextOutputLine(), StrEq("INSERT COIN"));
	EXPECT_THAT(getNextOutputLine(), StrEq("PRICE: 1.00"));
	EXPECT_THAT(getNextOutputLine(), StrEq("PRICE: 0.50"));
	EXPECT_THAT(getNextOutputLine(), StrEq("PRICE: 0.65"));
}

TEST_F(VendingMachineAppFixture, WhenCustomerSelectsProductWithSecondButtonFirstThenIgnore)
{
	std::stringstream input;
	input << "1" << std::endl;

	app.run(input);

	EXPECT_THAT(getNextOutputLine(), StrEq("INSERT COIN"));
	EXPECT_THAT(getNextOutputLine(), StrEq("INSERT COIN"));
}

TEST_F(VendingMachineAppFixture, WhenCustomerSelectsWrongButtonCombinationThenIgnore)
{
	std::stringstream input;
	input << "a3" << std::endl;

	app.run(input);

	EXPECT_THAT(getNextOutputLine(), StrEq("INSERT COIN"));
	EXPECT_THAT(getNextOutputLine(), StrEq("INSERT COIN"));
}

TEST_F(VendingMachineAppFixture, GivenCustomerAddsEnoughMoneyWhenSelectingProductThenDispenseAndThankCustomer)
{
	verifyColaMoneyAdded();

	EXPECT_THAT(getNextOutputLine(), StrEq("THANK YOU"));
	EXPECT_THAT(selectionService.dispensedItem(), Eq(COLA_PRODUCT));
}

TEST_F(VendingMachineAppFixture, WhenCustomerHasBeenThankedThenResetMachine)
{
	ASSERT_TRUE(purchaseCola());
	EXPECT_THAT(getNextOutputLine(), StrEq("INSERT COIN"));
}

TEST_F(VendingMachineAppFixture, WhenPriceDisplayedThenResetMachine)
{
	std::stringstream input;
	input << "a1." << std::endl;

	app.run(input);

	ASSERT_THAT(getNextOutputLine(), StrEq("INSERT COIN"));
	ASSERT_THAT(getNextOutputLine(), StrEq("PRICE: 1.00"));
	EXPECT_THAT(getNextOutputLine(), StrEq("INSERT COIN"));
}

TEST_F(VendingMachineAppFixture, GivenSomeMoneyInsertedWhenPriceDisplayedThenResetMachineAndDisplayAmountInserted)
{
	std::stringstream input;
	input << "qqa1." << std::endl;

	app.run(input);

	ASSERT_THAT(getNextOutputLine(), StrEq("INSERT COIN"));
	ASSERT_THAT(getNextOutputLine(), StrEq("0.25"));
	ASSERT_THAT(getNextOutputLine(), StrEq("0.50"));
	ASSERT_THAT(getNextOutputLine(), StrEq("PRICE: 1.00"));
	EXPECT_THAT(getNextOutputLine(), StrEq("0.50"));
}

TEST_F(VendingMachineAppFixture, GivenValidChangeWhenUserEntersRThenAppDisplaysReturnedCoins)
{
	std::stringstream input;
	input << "qqqdnb2r" << std::endl;

	app.run(input);

	EXPECT_THAT(getNextOutputLine(), StrEq("INSERT COIN"));
	ASSERT_THAT(getNextOutputLine(), StrEq("0.25"));
	ASSERT_THAT(getNextOutputLine(), StrEq("0.50"));
	ASSERT_THAT(getNextOutputLine(), StrEq("0.75"));
	ASSERT_THAT(getNextOutputLine(), StrEq("0.85"));
	ASSERT_THAT(getNextOutputLine(), StrEq("0.90"));
	ASSERT_THAT(getNextOutputLine(), StrEq("THANK YOU"));
	ASSERT_THAT(selectionService.dispensedItem(), Eq(CHIPS_PRODUCT));

	EXPECT_THAT(getNextOutputLine(), StrEq("Returned: quarter, dime, nickel"));
}
