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

#include "VendingMachineApp.h"
#include "CoinCandidate.h"
#include "CoinAccepter.h"
#include "SelectionValidator.h"
#include "VendingMachineDisplay.h"
#include <sstream>

namespace VendingMachineAppConstants
{
	const char NO_ID('_');
}

VendingMachineApp::VendingMachineApp(std::ostream & output, CoinAccepter & accepter, VendingMachineDisplay & display, SelectionValidator & validator) : m_output(output), m_accepter(accepter), m_display(display), m_validator(validator), m_showReturnedCoins(false), m_firstID(VendingMachineAppConstants::NO_ID), m_secondID(VendingMachineAppConstants::NO_ID)
{
}

VendingMachineApp::~VendingMachineApp()
{
}

void VendingMachineApp::run(std::istream & input)
{
	char choice;
	do 
	{
		process(choice);
		render();
	} while (input >> choice);
}

void VendingMachineApp::process(char choice)
{
	switch (choice)
	{
		case 'q':
			m_accepter.add(CoinCandidate(QUARTER_WEIGHT, QUARTER_DIAMETER, QUARTER_THICKNESS));
			break;

		case 'd':
			m_accepter.add(CoinCandidate(DIME_WEIGHT, DIME_DIAMETER, DIME_THICKNESS));
			break;

		case 'n':
			m_accepter.add(CoinCandidate(NICKEL_WEIGHT, NICKEL_DIAMETER, NICKEL_THICKNESS));
			break;

		case 'p':
			m_accepter.add(CoinCandidate(2500, 1905, 152));
			break;

		case 'r':
			m_showReturnedCoins = true;
			break;

		case 'a':
		case 'b':
		case 'c':
			m_firstID = choice;
			m_secondID = VendingMachineAppConstants::NO_ID;
			break;

		case '1':
		case '2':
		case '3':
			m_secondID = choice;
			m_validator.select(getProductChoice());
			m_secondID = VendingMachineAppConstants::NO_ID;
			m_firstID = VendingMachineAppConstants::NO_ID;
			break;
	}
}

void VendingMachineApp::render()
{
	if (m_showReturnedCoins)
	{
		m_output << outputReturnedCoins() << std::endl;
		m_showReturnedCoins = false;
	}
	else if (!waitingOnInput())
	{
		m_output << m_display.ui() << std::endl;
	}
}

bool VendingMachineApp::waitingOnInput() const
{
	return VendingMachineAppConstants::NO_ID != m_firstID && VendingMachineAppConstants::NO_ID == m_secondID;
}

std::string VendingMachineApp::outputReturnedCoins()
{
	std::stringstream coinText;
	coinText << "Returned: ";
	for (int i = 0; i < m_accepter.returnedCoins().size(); ++i)
	{
		coinText << "rejected coin";
		if (i + 1 < m_accepter.returnedCoins().size())
		{
			coinText << ", ";
		}
	}

	return coinText.str();
}

VendingProduct VendingMachineApp::getProductChoice()
{
	if ('a' == m_firstID && '1' == m_secondID)
	{
		return COLA_PRODUCT;
	}
	else if ('b' == m_firstID && '2' == m_secondID)
	{
		return CHIPS_PRODUCT;
	}
	else if ('c' == m_firstID && '3' == m_secondID)
	{
		return CANDY_PRODUCT;
	}
	
	return NO_PRODUCT;
}
