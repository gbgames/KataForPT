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
#include "VendingMachineDisplay.h"

VendingMachineApp::VendingMachineApp(std::ostream & output, CoinAccepter & accepter, VendingMachineDisplay & display) : m_output(output), m_accepter(accepter), m_display(display)
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
		m_output << m_display.ui() << std::endl;
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
	}
}
