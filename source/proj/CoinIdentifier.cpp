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
#include "CoinSpecifications.h"
#include <vector>

struct Coin
{
	Coin(CoinType type_, CoinWeight weight_, CoinDiameter diameter_, CoinThickness thickness_) : 
		type(type_), weight(weight_), diameter(diameter_), thickness(thickness_)
	{
	}

	bool isMatch(int w, int d, int t) const
	{
		return w == weight && d == diameter && t == thickness;
	}

	CoinType type;
	CoinWeight weight;
	CoinDiameter diameter;
	CoinThickness thickness;
};

CoinType CoinIdentifier::identifyCoin(int weight, int diameter, int thickness)
{
	std::vector<Coin> coins;
	coins.push_back(Coin(DIME_COIN, DIME_WEIGHT, DIME_DIAMETER, DIME_THICKNESS));
	coins.push_back(Coin(NICKEL_COIN, NICKEL_WEIGHT, NICKEL_DIAMETER, NICKEL_THICKNESS));
	coins.push_back(Coin(QUARTER_COIN, QUARTER_WEIGHT, QUARTER_DIAMETER, QUARTER_THICKNESS));

	for (std::vector<Coin>::iterator iter = coins.begin(); iter != coins.end(); ++iter)
	{
		if (iter->isMatch(weight, diameter, thickness))
		{
			return iter->type;
		}
	}

	return INVALID_COIN;
}
