#ifndef PACKETS_H
#define PACKETS_H


#include <vector>

#define PLACEHOLDER 1


typedef unsigned char * packet;


class Packets
{
public:

    Packets();
    Packets(packet data, int size);

    void createPackets(int length);
    void deletePacket(int number);
    void replacePacket(int number, packet pk);
    bool isDeleted(int number);
    packet getPacket(int number);

    int getPacketLength() const;
    void setData(packet data);

    packet data;

    packet data_del;

private:

    int packet_length;
    int packet_amount;
    /**
     * @brief size in bytes.
     */
    int size;
};

#endif // PACKETS_H
