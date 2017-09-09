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
#ifndef GB_VENDING_MACHINE_DISPLAY_H
#define GB_VENDING_MACHINE_DISPLAY_H

#include "Cents.h"
#include <string>

class CoinAccepter;
class SelectionValidator;

class VendingMachineDisplay
{
	public:
		VendingMachineDisplay(CoinAccepter & accepter, SelectionValidator & validator);
		~VendingMachineDisplay();

		std::string ui() const;
	
	private:
		std::string amountUI(Cents amount) const;
		CoinAccepter & m_accepter;
		SelectionValidator & m_validator;
};

#endif

