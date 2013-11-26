#include "packets.h"


Packets::Packets()
{ 
}


Packets::Packets(packet data, int size)
{
    this->data = data;
    this->size = size;
}


void Packets::createPackets(int length)
{
    this->packet_length = length;
    this->packet_amount = this->size / length;
}


void Packets::deletePacket(int number)
{
    for(int i=0; i<this->packet_length; i++)
    {
        this->data[number*this->packet_length + i] = PLACEHOLDER;
    }
}


void Packets::replacePacket(int number, packet pk)
{
    for(int i=0; i<this->packet_length; i++)
    {
        this->data[number*this->packet_length + i] = pk[i];
    }
}


bool Packets::isDeleted(int number)
{
    int tof = 0;
    for(int i=0;i<packet_length; i++)
    {
        if(this->data[number*packet_length + i] == PLACEHOLDER)
        {
            tof++;
        }
    }
    return tof>=packet_length-1?true:false;
}


packet Packets::getPacket(int number)
{
    unsigned char * p = new unsigned char[packet_length];

    for(int i=0;i < packet_length; i++)
    {
        p[i] = this->data[number*packet_length + i];
    }
    return p;
}


int Packets::getPacketLength() const
{
    return this->packet_length;
}
