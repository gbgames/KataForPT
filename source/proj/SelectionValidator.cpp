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

#include "SelectionValidator.h"
#include "CoinAccepter.h"
#include "ProductSelectionService.h"
#include <stdexcept>

SelectionValidator::SelectionValidator(CoinAccepter & accepter, ProductSelectionService & service) : m_accepter(accepter), m_service(service), m_response(NO_RESPONSE), m_moneyRequired(0)
{
	m_productToPriceMap.insert(std::make_pair(COLA_PRODUCT, 100));
	m_productToPriceMap.insert(std::make_pair(CHIPS_PRODUCT, 50));
	m_productToPriceMap.insert(std::make_pair(CANDY_PRODUCT, 65));
}

SelectionValidator::~SelectionValidator()
{
}

void SelectionValidator::select(VendingProduct product)
{
	m_response = (NO_PRODUCT == product) ? NO_RESPONSE : NOT_ENOUGH_MONEY_RESPONSE;
	if (m_productToPriceMap.end() != m_productToPriceMap.find(product))
	{
		m_moneyRequired = m_productToPriceMap[product];
		if (m_moneyRequired <= m_accepter.currentAmount())
		{
			m_accepter.purchaseWith(m_moneyRequired);
			m_service.select(product);
			m_response = PRODUCT_DISPENSED;
		}
	}
}

SelectionResponse SelectionValidator::currentResponse() const
{
	return m_response;
}

void SelectionValidator::reset()
{
	m_response = NO_RESPONSE;
}

Cents SelectionValidator::moneyRequired() const
{
	if (NOT_ENOUGH_MONEY_RESPONSE != m_response) 
	{
		throw std::runtime_error("moneyRequired() called when not attempting purchase.");
	}

	return m_moneyRequired;
}
