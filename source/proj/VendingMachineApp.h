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
#ifndef GB_VENDING_MACHINE_APP_H
#define GB_VENDING_MACHINE_APP_H

#include "VendingProduct.h"
#include <iostream>

typedef char ButtonID;

class CoinAccepter;
class SelectionValidator;
class VendingMachineDisplay;

class VendingMachineApp
{
	public:
		VendingMachineApp(std::ostream & output, CoinAccepter & accepter, VendingMachineDisplay & display, SelectionValidator & validator);
		~VendingMachineApp();

		void run(std::istream & input);

	private:
		void process(char choice);
		void render();
		bool waitingOnInput() const;
		std::string outputReturnedCoins();
		VendingProduct getProductChoice();
		std::ostream & m_output;
		CoinAccepter & m_accepter;
		VendingMachineDisplay & m_display;
		SelectionValidator & m_validator;
		bool m_showReturnedCoins;
		ButtonID m_firstID;
		ButtonID m_secondID;
};

#endif
