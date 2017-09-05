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

#ifndef GB_COIN_ACCEPTER_H
#define GB_COIN_ACCEPTER_H

#include "CoinCandidate.h"
#include <vector>

typedef int Cents;

class CoinAccepter
{
	public:
		CoinAccepter();
		~CoinAccepter();
	
		Cents currentAmount() const;
		void add(const CoinCandidate & candidate);
		std::vector<CoinCandidate> returnedCoins() const;

	private:
		int m_currentAmount;
		std::vector<CoinCandidate> m_returnedCoins;
};

#endif
