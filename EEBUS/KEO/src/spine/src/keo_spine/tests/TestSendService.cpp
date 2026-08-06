#include "TestSendService.h"

#include <keo_spine/DeviceDefinition.h>

TestSendService::TestSendService(const std::string& name)
    : sentDatagrams()
    , deviceName(name)
{
}

TestSendService::~TestSendService()
{
}

bool TestSendService::sendDatagram(DatagramRecord& datagramRecord)
{
    sentDatagrams.push_back(datagramRecord);
    return true;
}

keo_datagram::xs_unsignedLong TestSendService::sendPendingDatagram(DatagramRecord& datagramRecord)
{
    return sendPendingDatagram(datagramRecord, DeviceDefinition::DatagramTimeoutDelay);
}

keo_datagram::xs_unsignedLong TestSendService::sendPendingDatagram(DatagramRecord& datagramRecord, long timeout)
{
    (void)timeout;
    sentDatagrams.push_back(datagramRecord);
    return datagramRecord.getDatagram().getMsgCounter();
}

bool TestSendService::removeTimeoutByMsgCounter(keo_datagram::xs_unsignedLong msgCounter)
{
    (void)msgCounter;
    return true;
}

std::string TestSendService::getDeviceName() const
{
    return deviceName;
}

bool TestSendService::isConnected(const std::string& deviceName) const
{
    (void)deviceName;
    return true;
}

const std::vector<DatagramRecord>& TestSendService::getSentDatagrams()
{
    return sentDatagrams;
}

void TestSendService::clearAll()
{
    sentDatagrams.clear();
}
