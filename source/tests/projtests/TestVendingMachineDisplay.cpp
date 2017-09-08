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

#include "VendingMachineDisplay.h"
#include "CoinAccepter.h"
#include "CoinAccepterHelpers.h"
#include "gmock/gmock.h"

using namespace testing;

class VendingMachineDisplayFixture : public Test
{
	public:
		VendingMachineDisplayFixture() : helper(accepter), display(accepter) {}
		~VendingMachineDisplayFixture() {}

		CoinAccepter accepter;
		CoinAccepterHelper helper;
		VendingMachineDisplay display;
};

TEST_F(VendingMachineDisplayFixture, ShowInsertCoinWhenThereAreNoCoinsInserted)
{
	EXPECT_THAT(display.ui(), StrEq("INSERT COIN"));
}

TEST_F(VendingMachineDisplayFixture, ShowValueOfCoinsCurrentlyInserted)
{
	helper.insertQuarter();
	EXPECT_THAT(display.ui(), StrEq("0.25"));
	helper.insertQuarter();
	EXPECT_THAT(display.ui(), StrEq("0.50"));
	helper.insertDime();
	EXPECT_THAT(display.ui(), StrEq("0.60"));
	helper.insertNickel();
	EXPECT_THAT(display.ui(), StrEq("0.65"));
	helper.insertQuarter();
	EXPECT_THAT(display.ui(), StrEq("0.90"));
	helper.insertQuarter();
	EXPECT_THAT(display.ui(), StrEq("1.15"));
}

TEST_F(VendingMachineDisplayFixture, ShowValueOfCoinsLessThanTenCents)
{
	helper.insertNickel();
	EXPECT_THAT(display.ui(), StrEq("0.05"));
}
