///////////////////////////////////////////////////////////
//  Channel.h
//  Implementation of the Class Channel
//  Created on:      05-окт-2013 22:31:51
//  Original author: Bogdan Vaneev warchantua@gmail.com
///////////////////////////////////////////////////////////

#if !defined(EA_CE516535_49EA_4af3_95FE_5F5D4B06EE00__INCLUDED_)
#define EA_CE516535_49EA_4af3_95FE_5F5D4B06EE00__INCLUDED_

#include "AudioIO.h"

/**
 * @class Channel
 * @brief Spits WAV into packets.
 */
class Channel : public AudioIO
{

public:
	Channel();
	virtual ~Channel();
	const int getLossPercentage();
	void setLossPercentage(const int& lossPercentage);

private:
	int lossPercentage;

};
#endif // !defined(EA_CE516535_49EA_4af3_95FE_5F5D4B06EE00__INCLUDED_)
