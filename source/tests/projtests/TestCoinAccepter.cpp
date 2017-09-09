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
#include "CoinCandidate.h"
#include "CoinSpecifications.h"
#include "gmock/gmock.h"

using namespace testing;

class CoinAccepterFixture : public Test
{
	public:
		CoinAccepterFixture() {}
		~CoinAccepterFixture() {}

	CoinAccepter accepter;
};

TEST_F(CoinAccepterFixture, ByDefaultHasNoCoins)
{
	EXPECT_THAT(accepter.currentAmount(), Eq(0));
}

TEST_F(CoinAccepterFixture, WhenAValidCoinIsAddedThenUpdateTheCurrentAmount)
{
	accepter.add(CoinCandidate(QUARTER_WEIGHT, QUARTER_DIAMETER, QUARTER_THICKNESS));

	EXPECT_THAT(accepter.currentAmount(), Eq(25));
}

TEST_F(CoinAccepterFixture, WhenMultipleValidCoinsAreAddedThenUpdateTheCurrentAmountWithTheTotalValue)
{
	accepter.add(CoinCandidate(DIME_WEIGHT, DIME_DIAMETER, DIME_THICKNESS));
	EXPECT_THAT(accepter.currentAmount(), Eq(10));

	accepter.add(CoinCandidate(NICKEL_WEIGHT, NICKEL_DIAMETER, NICKEL_THICKNESS));
	EXPECT_THAT(accepter.currentAmount(), Eq(15));
}

TEST_F(CoinAccepterFixture, WhenAnInvalidCoinIsAddedThenDoNotAcceptIt)
{
	ASSERT_TRUE(accepter.returnedCoins().empty());
	const Weight ARBITRARY_WEIGHT(2500);
	const Length ARBITRARY_DIAMETER(1905);
	const Length ARBITRARY_THICKNESS(152);
	CoinCandidate candidate(ARBITRARY_WEIGHT, ARBITRARY_DIAMETER, ARBITRARY_THICKNESS);
	accepter.add(candidate);

	EXPECT_THAT(accepter.returnedCoins().at(0), Eq(candidate));
}

TEST_F(CoinAccepterFixture, AcceptingPurchaseWillResetTheTotalAmountInserted)
{
	accepter.add(CoinCandidate(DIME_WEIGHT, DIME_DIAMETER, DIME_THICKNESS));
	accepter.add(CoinCandidate(NICKEL_WEIGHT, NICKEL_DIAMETER, NICKEL_THICKNESS));
	accepter.add(CoinCandidate(QUARTER_WEIGHT, QUARTER_DIAMETER, QUARTER_THICKNESS));
	ASSERT_THAT(accepter.currentAmount(), Eq(40));

	accepter.purchaseWith(40);

	EXPECT_THAT(accepter.currentAmount(), Eq(0));
}

TEST_F(CoinAccepterFixture, AddChangeToReturnToCustomer)
{
	accepter.makeChange(25);

	EXPECT_THAT(accepter.returnedCoins().at(0), Eq(CoinCandidate(QUARTER_WEIGHT, QUARTER_DIAMETER, QUARTER_THICKNESS)));
}
