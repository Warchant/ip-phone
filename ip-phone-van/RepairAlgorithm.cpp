///////////////////////////////////////////////////////////
//  RepairAlgorithm.cpp
//  Implementation of the Class RepairAlgorithm
//  Created on:      05-Oct-2013 16:54:34
//  Original author: Bogdan Vaneev warchantua@gmail.com
///////////////////////////////////////////////////////////

#include "RepairAlgorithm.h"


RepairAlgorithm::RepairAlgorithm(int size){
    this->container = new Packets();
    this->sizeinbytes = size;
}


RepairAlgorithm::~RepairAlgorithm(){
    delete container;
}


void RepairAlgorithm::setSizeInBytes(int sib)
{
    this->sizeinbytes = sib;
}


void RepairAlgorithm::setData(unsigned char * d)
{
    delete this->container;
    this->container = new Packets(d, this->sizeinbytes);
}


void RepairAlgorithm::setPacketLength(int length)
{
    this->container->createPackets(length);
}


void RepairAlgorithm::setPacketsAmount(int size)
{
    this->sizeinpackets = size;
}

// +
void RepairAlgorithm::splicing()
{
    /* NOT COMPLETED ALGO
    int packet_length = container->getPacketLength();
    unsigned char * zero_packet = new unsigned char [packet_length];

    for(int i=0; i<packet_length;i++)
    {
        zero_packet[i] = 0;
    }

    int offset = 1;
    for(int i=0; i < this->sizeinpackets; i++)
    {
        if(container->isDeleted(i))
        {
            while(container->isDeleted(i+offset) && (i+offset) < this->sizeinpackets)
            {
                offset++;
            }
            container->replacePacket(i,container->getPacket(i+offset));
            container->replacePacket(i+offset,zero_packet);
        }
        else
        {
            continue;
        }
    }

    delete zero_packet;
    */

    // COMPLETED ALGO
    int offset = 0;
    for(int i=0; i<this->sizeinbytes; i++)
    {
        while(container->data[i+offset] == PLACEHOLDER && i+offset < sizeinbytes)
        {
            offset++;
        }
        if(i+offset < sizeinbytes)
        {
            container->data[i] = container->data[i+offset];
        }
        else
        {
            container->data[i] = 0;
        }
    }
}

// +
void RepairAlgorithm::silenceSubstitution()
{
    double mean = 0;
    int amount  = 0;
    for(int i=0;i<sizeinbytes;i++)
    {
        if(container->data[i] != PLACEHOLDER)
        {
            amount++;
            mean+=double(container->data[i]);
        }
    }
    mean/=amount;
    for(int i=0;i<sizeinbytes;i++)
    {
        if(container->data[i] == PLACEHOLDER)
        {
            container->data[i] = mean;
        }
    }
}
