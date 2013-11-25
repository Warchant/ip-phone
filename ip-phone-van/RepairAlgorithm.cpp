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
void RepairAlgorithm::cleanBeforeFirst()
{
    int offset = 0;
    bool finded = false;
    for(int i=0; i<sizeinbytes; i++)
    {
        if(!finded)
        {
            while(container->data[i+offset] == PLACEHOLDER && i+offset < sizeinbytes)
            {
                offset++;
            }
            finded = true;
        }
        else
        {
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
}

// +
void RepairAlgorithm::splicing()
{
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

// +
void RepairAlgorithm::noiseSubstitution()
{
    this->cleanBeforeFirst();
    int packet_length = container->getPacketLength();
    int last_correct;
    int mean;
    int variance;
    int max;
    for(int i=0; i<sizeinpackets && container->data[i*packet_length]!=0; i++)
    {
        if(!container->isDeleted(i))
        {
            last_correct = i;

            // calculate mean and max
            mean = 0;
            max  = 0;
            for(int j=0;j<packet_length;j++)
            {
                int el = int(container->data[last_correct*packet_length + j]);
                mean+= el;
                max = max < el ? el : max;
            }
            mean/=packet_length;

            // calculate variance
            variance = (max - mean)/2;
        }
        // generate randn noise
        std::default_random_engine generator;
        std::normal_distribution<double> randn(mean, variance);

        if(container->isDeleted(i))
        {
            for(int j=0; j<packet_length; j++)
            {
                int randn_number = randn(generator);
                container->data[i*packet_length + j] = randn_number >= 2 && randn_number <=255 ?
                            randn_number : mean;
            }
        }
    }
}


void RepairAlgorithm::packetRepetition()
{
    this->cleanBeforeFirst();
    // TODO
}

