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

enum CoinWeight
{
	QUARTER_WEIGHT =  5670,
	DIME_WEIGHT = 2268
};

enum CoinDiameter
{
	QUARTER_DIAMETER = 2426,
	DIME_DIAMETER = 1791
};

enum CoinThickness
{
	QUARTER_THICKNESS = 175,
	DIME_THICKNESS = 135
};

CoinType CoinIdentifier::identifyCoin(int weight, int diameter, int thickness)
{
	if (DIME_WEIGHT == weight && DIME_DIAMETER == diameter && DIME_THICKNESS == thickness)
	{
		return DIME_COIN;
	}

	return QUARTER_COIN;
}
