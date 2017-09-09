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

CoinAccepter::CoinAccepter() : m_currentAmount(0)
{
}

CoinAccepter::~CoinAccepter()
{
}

Cents CoinAccepter::currentAmount() const
{
	return m_currentAmount;
}

void CoinAccepter::add(const CoinCandidate & candidate)
{
	switch (CoinIdentifier::identifyCoin(candidate.weight, candidate.diameter, candidate.thickness))
	{
		case QUARTER_COIN:
			m_currentAmount += 25;
			break;

		case DIME_COIN:
			m_currentAmount += 10;
			break;

		case NICKEL_COIN:
			m_currentAmount += 5;
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
	m_currentAmount = 0;
}

void CoinAccepter::makeChange(Cents amount)
{
	m_returnedCoins.push_back(CoinCandidate(QUARTER_WEIGHT, QUARTER_DIAMETER, QUARTER_THICKNESS));
}
