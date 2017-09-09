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
#include "CoinIdentifier.h"

CoinAccepter::CoinAccepter() 
{
}

CoinAccepter::~CoinAccepter()
{
}

Cents CoinAccepter::currentAmount() const
{
	Cents total(0);
	for (std::vector<CoinCandidate>::const_iterator iter = m_insertedCoins.begin(); iter != m_insertedCoins.end(); ++iter)
	{
		switch (CoinIdentifier::identifyCoin(iter->weight, iter->diameter, iter->thickness))
		{
			case QUARTER_COIN:
				total += 25;
				break;
			case DIME_COIN:
				total += 10;
				break;
			case NICKEL_COIN:
				total += 5;
				break;
		}
	}

	return total;
}

void CoinAccepter::add(const CoinCandidate & candidate)
{
	switch (CoinIdentifier::identifyCoin(candidate.weight, candidate.diameter, candidate.thickness))
	{
		case QUARTER_COIN:
		case DIME_COIN:
		case NICKEL_COIN:
			m_insertedCoins.push_back(candidate);
			break;

		default:
			m_returnedCoins.push_back(candidate);
			break;
	}
}

std::vector<CoinCandidate> CoinAccepter::returnedCoins() const
{
	return m_returnedCoins;
}

void CoinAccepter::purchaseWith(Cents amount)
{
	Cents change = currentAmount() - amount;
	makeChange(change);
	m_insertedCoins.clear();
}

void CoinAccepter::returnMoney()
{
	for(std::vector<CoinCandidate>::iterator iter = m_insertedCoins.begin(); iter != m_insertedCoins.end(); ++iter)
	{
		m_returnedCoins.push_back(*iter);
	}
	m_insertedCoins.clear();
}

void CoinAccepter::makeChange(Cents amount)
{
	while (amount >= 25)
	{
		m_returnedCoins.push_back(CoinCandidate(QUARTER_WEIGHT, QUARTER_DIAMETER, QUARTER_THICKNESS));
		amount -= 25;
	}

	while (amount >= 10)
	{
		m_returnedCoins.push_back(CoinCandidate(DIME_WEIGHT, DIME_DIAMETER, DIME_THICKNESS));
		amount -= 10;
	}

	if (5 == amount)
	{
		m_returnedCoins.push_back(CoinCandidate(NICKEL_WEIGHT, NICKEL_DIAMETER, NICKEL_THICKNESS));
	}
}
