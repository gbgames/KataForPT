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

#include "CoinAccepterHelpers.h"
#include "CoinAccepter.h"

CoinAccepterHelper::CoinAccepterHelper(CoinAccepter & accepter) : m_accepter(accepter)
{
}

CoinAccepterHelper::~CoinAccepterHelper()
{
}

void CoinAccepterHelper::insertQuarter()
{
	m_accepter.add(CoinCandidate(QUARTER_WEIGHT, QUARTER_DIAMETER, QUARTER_THICKNESS));
}

void CoinAccepterHelper::insertDime()
{
	m_accepter.add(CoinCandidate(DIME_WEIGHT, DIME_DIAMETER, DIME_THICKNESS));
}

void CoinAccepterHelper::insertNickel()
{
	m_accepter.add(CoinCandidate(NICKEL_WEIGHT, NICKEL_DIAMETER, NICKEL_THICKNESS));
}
