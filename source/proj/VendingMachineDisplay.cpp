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

#include "VendingMachineDisplay.h"
#include "CoinAccepter.h"
#include <sstream>

VendingMachineDisplay::VendingMachineDisplay(CoinAccepter & accepter) : m_accepter(accepter)
{
}

VendingMachineDisplay::~VendingMachineDisplay()
{
}

std::string VendingMachineDisplay::ui() const
{
	Cents currentAmount = m_accepter.currentAmount();

	return (0 == currentAmount) ? "INSERT COIN" : amountUI(currentAmount);
}

std::string VendingMachineDisplay::amountUI(Cents amount) const
{
	std::stringstream amountText;
	amountText << amount/100 << "." << amount % 100;

	return amountText.str();
}
