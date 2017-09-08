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
#ifndef GB_SELECTION_VALIDATOR_H
#define GB_SELECTION_VALIDATOR_H

#include "VendingProduct.h"

enum SelectionResponse
{
	NOT_ENOUGH_MONEY_RESPONSE,
	PRODUCT_DISPENSED
};

class CoinAccepter;
class ProductSelectionService;

class SelectionValidator
{
	public:
		SelectionValidator(CoinAccepter & accepter, ProductSelectionService & service);
		~SelectionValidator();

		SelectionResponse select(VendingProduct product);
};

#endif
