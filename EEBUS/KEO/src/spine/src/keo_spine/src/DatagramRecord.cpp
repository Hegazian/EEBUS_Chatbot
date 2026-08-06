/*
 *     Copyright KEO GmbH 2016 - All rights reserved!
 *
 *     This software is protected by the inclusion of the above copyright notice.
 *     This software may not be provided or otherwise made available to, or used
 *     by, any other person. No title to or ownership of the software is hereby
 *     transferred. The information contained in this document is considered the
 *     @b confidential and @b proprietary information of KEO GmbH
 *     and may not be disclosed or discussed with anyone who is not employed by
 *     KEO GmbH, unless the individual or company
 *     - has an express need to know such information, and
 *     - disclosure of information is subject to the terms of a duly
 *     executed "Confidentiality and Non-Disclosure Agreement" between
 *     KEO GmbH and the individual or company.
 */

/* ****************************************************************************** *
 *  project header files                                                          *
 * ****************************************************************************** */

#include <keo_spine/DatagramRecord.h>

/* ****************************************************************************** *
 *  KEO header files                                                          *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  standard header files                                                         *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  defines                                                                       *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  types                                                                         *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  definition                                                                    *
 * ****************************************************************************** */

namespace keo_spine
{

DatagramRecord::DatagramRecord()
{
}

DatagramRecord::DatagramRecord(const keo_datagram::DatagramPtr datagram)
    : datagram(*(datagram.get()))
{
}

DatagramRecord::DatagramRecord(const keo_datagram::Datagram& datagram)
    : datagram(datagram)
{
}

DatagramRecord::DatagramRecord(const keo_datagram::DatagramPtr datagram, const TransportId& transportId)
    : datagram(*(datagram.get()))
    , transportId(transportId)
{
}

DatagramRecord::DatagramRecord(const keo_datagram::Datagram& datagram, const TransportId& transportId)
    : datagram(datagram)
    , transportId(transportId)
{
}

void DatagramRecord::setTransportId(const TransportId& transportId)
{
    this->transportId = transportId;
}

const TransportId& DatagramRecord::getTransportId() const
{
    return transportId;
}

void DatagramRecord::setDatagram(const keo_datagram::Datagram& datagram)
{
    this->datagram = datagram;
}

const keo_datagram::Datagram& DatagramRecord::getDatagram() const
{
    return datagram;
}

keo_datagram::Datagram& DatagramRecord::getDatagram()
{
    return datagram;
}

std::string DatagramRecord::getDestinationDevice() const
{
    if (datagram.getHeaderIsSet() && datagram.getHeader().getAddressDestinationIsSet())
    {
        return datagram.getDestinationAddress().getDevice();
    }
    else
    {
        return std::string();
    }
}

std::string DatagramRecord::getSourceDevice() const
{
    if (datagram.getHeaderIsSet() && datagram.getHeader().getAddressSourceIsSet())
    {
        return datagram.getSourceAddress().getDevice();
    }
    else
    {
        return std::string();
    }
}

std::string DatagramRecord::toJson() const
{
    return datagram.toJson();
}

} /* namespace keo_spine */
