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
	CoinCandidate candidate(QUARTER_WEIGHT, QUARTER_DIAMETER, QUARTER_THICKNESS);
	accepter.add(candidate);

	EXPECT_THAT(accepter.currentAmount(), Eq(25));
}
