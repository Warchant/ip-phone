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
            container->data[i] = mean;
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
    int mean        = 0;
    double variance = 0;
    for(int i=0; i<sizeinpackets && container->data[i*packet_length]!=0; i++)
    {
        if(!container->isDeleted(i))
        {
            last_correct = i;

            // calculate mean and max
            mean = 0;
            for(int j=0;j<packet_length;j++)
            {
                int el = int(container->data[last_correct*packet_length + j]);
                mean+= el;
            }
            mean/=packet_length;

            // calculate variance
            variance = 0;
            for(int j=0;j<packet_length;j++)
            {
                int el = int(container->data[last_correct*packet_length + j]);
                variance+=(el-mean)*(el-mean);
            }
            variance /= (packet_length - 1);
            variance  = pow(variance, 0.5);
        }
        else
        {
            // generate randn noise
            std::default_random_engine generator;
            std::normal_distribution<double> randn(mean, variance/2);
            for(int j=0; j<packet_length; j++)
            {
                int randn_number = randn(generator);
                container->data[i*packet_length + j] = randn_number >= 2 && randn_number <=255 ?
                            randn_number : mean;
            }
        }
    }
}


//+
void RepairAlgorithm::packetRepetition()
{
    this->cleanBeforeFirst();
    int packet_length = container->getPacketLength();
    int last_correct = 0;
    for(int i=0; i<sizeinpackets && container->data[i*packet_length]!=0; i++)
    {
        if(!container->isDeleted(i))
        {
            last_correct = i;
        }
        else
        {
            container->replacePacket(i,container->getPacket(last_correct));
        }
    }
}

/* TODO
//?
void RepairAlgorithm::timeScaleModification()
{
    this->cleanBeforeFirst();
    int   packet_length = container->getPacketLength();
    int   left          = 0; // index of left correct packet
    int   right         = 1; // i+right => correct packet
    for(int i=0; i<sizeinpackets; i++)
    {
        if(!container->isDeleted(i))
        {
            // find left-sided packet
            left = i;
        }
        else
        {
            // if deleted
            // find right-sided packet
            right = 1;
            while(container->isDeleted(i+right) && i+right < sizeinpackets)
            {
                right++;
            }

            if(container->isDeleted(i+right))
            {
                // i to last packet are deleted

            }
            else
            {
                // split into 2 parts left and right packets, then concatenate them
                packet conc         = new unsigned char [packet_length];
                const packet pleft  = container->getPacket(left);
                const packet pright = container->getPacket(i+right);
                for(int j=0; j<packet_length; j++)
                {
                    // fill conc packet
                    conc[j] = (j<packet_length/2) ?
                                pleft [j + packet_length/2 + packet_length%2]:
                                pright[j - packet_length/2];
                }
                delete [] pleft;
                delete [] pright;
                // we need to scale conc packet to size = packet_length*right
                packet ins = new unsigned char [packet_length * right];
                if(right == 1)
                {
                    // one deleted packet in a row
                    memcpy(ins, conc, packet_length);
                }
                else
                {
                    // more than one deleted packet in a row
                    for(int j=0; j<packet_length; j++)
                    {
                        for(int k=0; k<right; k++)
                        {

                        }
                    }
                }
                delete [] conc;

            }
        }
    }

}

*/
