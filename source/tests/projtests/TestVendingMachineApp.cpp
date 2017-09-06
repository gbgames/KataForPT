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
#include "VendingMachineDisplay.h"
#include "gmock/gmock.h"

using namespace testing;

class VendingMachineAppFixture : public Test
{
	public:
		VendingMachineAppFixture() : display(accepter), app(output, accepter, display) {}
		~VendingMachineAppFixture() {}

	std::stringstream output;
	CoinAccepter accepter;
	VendingMachineDisplay display;
	VendingMachineApp app;
};

TEST_F(VendingMachineAppFixture, WhenUserEntersQThenAppInsertsAQuarter)
{
	std::stringstream input;
	input << 'q' << std::endl;

	app.run(input);

	std::string defaultLine;
	std::getline(output, defaultLine);
	EXPECT_THAT(defaultLine, StrEq("INSERT COIN"));

	std::string quarterAmount;
	std::getline(output, quarterAmount);
	EXPECT_THAT(quarterAmount, StrEq("0.25"));
}

TEST_F(VendingMachineAppFixture, WhenUserEntersDThenAppInsertsADime)
{
	std::stringstream input;
	input << 'd' << std::endl;

	app.run(input);

	std::string defaultLine;
	std::getline(output, defaultLine);
	EXPECT_THAT(defaultLine, StrEq("INSERT COIN"));

	std::string quarterAmount;
	std::getline(output, quarterAmount);
	EXPECT_THAT(quarterAmount, StrEq("0.10"));
}
