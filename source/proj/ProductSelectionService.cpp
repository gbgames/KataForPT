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

#include "ProductSelectionService.h"

ProductSelectionService::ProductSelectionService() : m_dispensedItem(NO_PRODUCT)
{
}

ProductSelectionService::~ProductSelectionService()
{
}

void ProductSelectionService::select(VendingProduct product)
{
	m_dispensedItem = product;
}

VendingProduct ProductSelectionService::dispensedItem() const
{
	return m_dispensedItem;
}

void ProductSelectionService::retrieveItem()
{
	m_dispensedItem = NO_PRODUCT;
}
