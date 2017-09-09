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

TEST_F(SelectionValidatorFixture, ValidatorCanResetToNoResponse)
{
	EXPECT_THAT(validator.currentResponse(), Eq(NO_RESPONSE));
	validator.select(COLA_PRODUCT);
	ASSERT_THAT(validator.currentResponse(), Eq(NOT_ENOUGH_MONEY_RESPONSE));

	validator.reset();
	EXPECT_THAT(validator.currentResponse(), Eq(NO_RESPONSE));
}

TEST_F(SelectionValidatorFixture, GivenNoCoinsInsertedWhenColaSelectedThenRejectSelection)
{
	validator.select(COLA_PRODUCT);
	EXPECT_THAT(validator.currentResponse(), Eq(NOT_ENOUGH_MONEY_RESPONSE));
	EXPECT_THAT(selectionService.dispensedItem(), Eq(NO_PRODUCT));
	EXPECT_THAT(validator.moneyRequired(), Eq(100));
}

TEST_F(SelectionValidatorFixture, GivenNoCoinsInsertedWhenChipsSelectedThenRejectSelection)
{
	validator.select(CHIPS_PRODUCT);
	EXPECT_THAT(validator.currentResponse(), Eq(NOT_ENOUGH_MONEY_RESPONSE));
	EXPECT_THAT(selectionService.dispensedItem(), Eq(NO_PRODUCT));
	EXPECT_THAT(validator.moneyRequired(), Eq(50));
}

TEST_F(SelectionValidatorFixture, GivenNoCoinsInsertedWhenCandySelectedThenRejectSelection)
{
	validator.select(CANDY_PRODUCT);
	EXPECT_THAT(validator.currentResponse(), Eq(NOT_ENOUGH_MONEY_RESPONSE));
	EXPECT_THAT(selectionService.dispensedItem(), Eq(NO_PRODUCT));
	EXPECT_THAT(validator.moneyRequired(), Eq(65));
}

TEST_F(SelectionValidatorFixture, GivenEnoughCoinsInsertedWhenColaSelectedThenSelectCola)
{
	CoinAccepterHelper helper(accepter);
	helper.insertQuarter();
	helper.insertQuarter();
	helper.insertQuarter();
	helper.insertQuarter();
	ASSERT_THAT(accepter.currentAmount(), Eq(100));

	validator.select(COLA_PRODUCT);
	EXPECT_THAT(validator.currentResponse(), Eq(PRODUCT_DISPENSED));
	EXPECT_THAT(accepter.currentAmount(), Eq(0));
	EXPECT_THAT(selectionService.dispensedItem(), Eq(COLA_PRODUCT));
}

TEST_F(SelectionValidatorFixture, GivenEnoughCoinsInsertedWhenChipsSelectedThenSelectChips)
{
	CoinAccepterHelper helper(accepter);
	helper.insertQuarter();
	helper.insertQuarter();
	ASSERT_THAT(accepter.currentAmount(), Eq(50));

	validator.select(CHIPS_PRODUCT);
	EXPECT_THAT(validator.currentResponse(), Eq(PRODUCT_DISPENSED));
	EXPECT_THAT(accepter.currentAmount(), Eq(0));
	EXPECT_THAT(selectionService.dispensedItem(), Eq(CHIPS_PRODUCT));
}

TEST_F(SelectionValidatorFixture, GivenEnoughCoinsInsertedWhenCandySelectedThenSelectCandy)
{
	CoinAccepterHelper helper(accepter);
	helper.insertQuarter();
	helper.insertQuarter();
	helper.insertDime();
	helper.insertNickel();
	ASSERT_THAT(accepter.currentAmount(), Eq(65));

	validator.select(CANDY_PRODUCT);
	EXPECT_THAT(validator.currentResponse(), Eq(PRODUCT_DISPENSED));
	EXPECT_THAT(accepter.currentAmount(), Eq(0));
	EXPECT_THAT(selectionService.dispensedItem(), Eq(CANDY_PRODUCT));
}

TEST_F(SelectionValidatorFixture, IfNotEnoughMoneyInsertedThenRejectPurchase)
{
	CoinAccepterHelper helper(accepter);
	helper.insertQuarter();
	ASSERT_THAT(accepter.currentAmount(), Lt(50));
	
	validator.select(COLA_PRODUCT);
	EXPECT_THAT(validator.currentResponse(), Eq(NOT_ENOUGH_MONEY_RESPONSE));
	EXPECT_THAT(selectionService.dispensedItem(), Eq(NO_PRODUCT));
	EXPECT_THAT(accepter.currentAmount(), Eq(25));
}

TEST_F(SelectionValidatorFixture, PreventAskingForMoneyRequiredIfNoProductSelected)
{
	ASSERT_THAT(validator.currentResponse(), Eq(NO_RESPONSE));

	EXPECT_THROW(validator.moneyRequired(), std::runtime_error);
}

TEST_F(SelectionValidatorFixture, PreventAskingForMoneyRequiredIfProductPurchased)
{
	CoinAccepterHelper helper(accepter);
	helper.insertQuarter();
	helper.insertQuarter();
	ASSERT_THAT(accepter.currentAmount(), Eq(50));
	validator.select(CHIPS_PRODUCT);
	ASSERT_THAT(validator.currentResponse(), Eq(PRODUCT_DISPENSED));

	EXPECT_THROW(validator.moneyRequired(), std::runtime_error);
}

TEST_F(SelectionValidatorFixture, WhenSelectingNoProductThenDoNotRespond)
{
	validator.select(NO_PRODUCT);
	EXPECT_THAT(validator.currentResponse(), Eq(NO_RESPONSE));
}
