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

#include "CoinIdentifier.h"
#include "gmock/gmock.h"

using namespace testing;

TEST(CoinIdentifierTest, IdentifiesQuarters)
{
	const int QUARTER_WEIGHT(5670);
	const int QUARTER_DIAMETER(2426);
	const int QUARTER_THICKNESS(175);

	EXPECT_THAT(CoinIdentifier::identifyCoin(QUARTER_WEIGHT, QUARTER_DIAMETER, QUARTER_THICKNESS), Eq(QUARTER_COIN));
}
