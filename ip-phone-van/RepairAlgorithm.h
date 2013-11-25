///////////////////////////////////////////////////////////
//  RepairAlgorithm.h
//  Implementation of the Class RepairAlgorithm
//  Created on:      05-Oct-2013 16:54:34
//  Original author: Bogdan Vaneev warchantua@gmail.com
///////////////////////////////////////////////////////////

#if !defined(EA_E6C96FA0_9A7D_4b53_9788_A194FBA7458F__INCLUDED_)
#define EA_E6C96FA0_9A7D_4b53_9788_A194FBA7458F__INCLUDED_

#include "packets.h"
#include <vector>
#include <algorithm>
#include <random>

/**
 * @brief The RepairAlgorithm class
 */
class RepairAlgorithm
{

public:
    RepairAlgorithm(int size);
	virtual ~RepairAlgorithm();

    void setSizeInBytes(int sib);
    void setData(unsigned char * d);
    void setPacketLength(int length);
    void setPacketsAmount(int size);

    void cleanBeforeFirst();
    /**
     * @brief splicing: 111___222 => 111222
     */
    void splicing();
    /**
     * @brief silenceSubstitution: 111___333 => 111222333
     */
    void silenceSubstitution();
    /**
     * @brief noiseSubstitution: 111___333 => 111231333
     */
    void noiseSubstitution();
    /**
     * @brief packetRepetition: 111___333 => 111111333
     */
    void packetRepetition();

    Packets* container;

private:
    int sizeinbytes;
    int sizeinpackets;
    std::vector<int> del_index;

};
#endif // !defined(EA_E6C96FA0_9A7D_4b53_9788_A194FBA7458F__INCLUDED_)
