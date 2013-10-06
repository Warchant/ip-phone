///////////////////////////////////////////////////////////
//  Channel.cpp
//  Implementation of the Class Channel
//  Created on:      05-Oct-2013 22:31:51
//  Original author: Bogdan Vaneev warchantua@gmail.com
///////////////////////////////////////////////////////////

#include "Channel.h"




Channel::Channel(){

}


Channel::~Channel(){

}


/**
 * @brief Getter for the lossPercentage.
 */
const int Channel::getLossPercentage(){

	return this->lossPercentage;
}


/**
 * @brief Setter for the lossPercentage.
 */
bool Channel::setLossPercentage(const int& lossPercentage){
	if(lossPercentage >= 0 && lossPercentage <= 100)
	{
		this->lossPercentage = lossPercentage;
        return true;
	}
    else
    {
        return false;
    }

}
