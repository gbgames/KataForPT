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

#include "ProductSelectionService.h"
#include "gmock/gmock.h"

using namespace testing;

class ProductSelectionServiceFixture : public Test
{
	public:
		ProductSelectionServiceFixture() {}
		~ProductSelectionServiceFixture() {}

		ProductSelectionService service;
};

TEST_F(ProductSelectionServiceFixture, WhenColaSelectedThenDispenseCola)
{
	ASSERT_THAT(service.dispensedItem(), Eq(NO_PRODUCT));

	service.select(COLA_PRODUCT);

	EXPECT_THAT(service.dispensedItem(), Eq(COLA_PRODUCT));
}

TEST_F(ProductSelectionServiceFixture, WhenChipsSelectedThenDispenseChips)
{
	ASSERT_THAT(service.dispensedItem(), Eq(NO_PRODUCT));

	service.select(CHIPS_PRODUCT);

	EXPECT_THAT(service.dispensedItem(), Eq(CHIPS_PRODUCT));
}

TEST_F(ProductSelectionServiceFixture, WhenCandySelectedThenDispenseCandy)
{
	ASSERT_THAT(service.dispensedItem(), Eq(NO_PRODUCT));

	service.select(CANDY_PRODUCT);

	EXPECT_THAT(service.dispensedItem(), Eq(CANDY_PRODUCT));
}

TEST_F(ProductSelectionServiceFixture, AllCustomerToRetrieveItem)
{
	service.select(COLA_PRODUCT);
	ASSERT_THAT(service.dispensedItem(), Eq(COLA_PRODUCT));

	service.retrieveItem();

	EXPECT_THAT(service.dispensedItem(), Eq(NO_PRODUCT));
}
