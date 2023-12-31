// File: PacketMotionEX.cpp
#include "PacketMotionEX.h"
#include <inttypes.h>
#include <string.h>

const int MOTIONEX_BUFFER_SIZE = 217;

PacketMotionEXData::PacketMotionEXData()
: PHeader()
{}

PacketMotionEXData::~PacketMotionEXData()
{}

void PacketMotionEXData::push(char *receiveBuffer)
{
    memmove(PHeader::pointerToFirstElement(), receiveBuffer, MOTIONEX_BUFFER_SIZE);
}

MotionEXData PacketMotionEXData::m_carMotionEXData()
{
        return m_carMotionEXData_;

}