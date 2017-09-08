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

#include "SelectionValidator.h"
#include "CoinAccepter.h"
#include "ProductSelectionService.h"
#include "CoinAccepterHelpers.h"
#include "gmock/gmock.h"

using namespace testing;

class SelectionValidatorFixture : public Test
{
	public:
		SelectionValidatorFixture() : validator(accepter, selectionService) {}
		~SelectionValidatorFixture() {}

		CoinAccepter accepter;
		ProductSelectionService selectionService;
		SelectionValidator validator;
};

TEST_F(SelectionValidatorFixture, GivenNoCoinsInsertedWhenColaSelectedThenRejectSelection)
{
	EXPECT_THAT(validator.select(COLA_PRODUCT), Eq(NOT_ENOUGH_MONEY_RESPONSE));
	EXPECT_THAT(selectionService.dispensedItem(), Eq(NO_PRODUCT));
}

TEST_F(SelectionValidatorFixture, GivenEnoughCoinsInsertedWhenColaSelectedThenSelectCola)
{
	CoinAccepterHelper helper(accepter);
	helper.insertQuarter();
	helper.insertQuarter();
	helper.insertQuarter();
	helper.insertQuarter();
	ASSERT_THAT(accepter.currentAmount(), Eq(100));

	EXPECT_THAT(validator.select(COLA_PRODUCT), Eq(PRODUCT_DISPENSED));
	EXPECT_THAT(accepter.currentAmount(), Eq(0));
	EXPECT_THAT(selectionService.dispensedItem(), Eq(COLA_PRODUCT));
}

TEST_F(SelectionValidatorFixture, GivenEnoughCoinsInsertedWhenChipsSelectedThenSelectChips)
{
	CoinAccepterHelper helper(accepter);
	helper.insertQuarter();
	helper.insertQuarter();
	ASSERT_THAT(accepter.currentAmount(), Eq(50));

	EXPECT_THAT(validator.select(CHIPS_PRODUCT), Eq(PRODUCT_DISPENSED));
	EXPECT_THAT(accepter.currentAmount(), Eq(0));
	EXPECT_THAT(selectionService.dispensedItem(), Eq(CHIPS_PRODUCT));

}
