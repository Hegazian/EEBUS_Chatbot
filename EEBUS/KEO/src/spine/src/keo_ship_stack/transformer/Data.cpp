/**
 *  @brief Data
 *
 *  @par    This is an automatically generated class
 */

#include "keo_ship/Data.h"

using namespace keo_ship;

Payload::Payload()
{
}

Payload::~Payload()
{
}

void Payload::setPayload(std::vector<char>& p)
{
    m_payload = p;
}

std::vector<char> Payload::getPayload(void) const
{
    return m_payload;
}

Data::Data()
    : CShipDataClass()
    , m_headerIsSet(false)
    , m_extensionIsSet(false)
    , m_header(Header())
    , m_payload(Payload())
    , m_extension(Extension())
{
}

Data::Data(const Header& c_header, const Payload& c_payload, const Extension& c_extension)
    : CShipDataClass()
{
    setHeader(c_header);
    setPayload(c_payload);
    setExtension(c_extension);
}

Data::~Data()
{
}
// Implement pure virtual method //
bool Data::isSet(void) const
{
    return (m_headerIsSet /*&& m_datagram->isHeaderValid()*/); // TODO: condition for payload valid
}
// Override the base functionality //
ShipDataType Data::getDataType(void) const
{
    return DATA_TYPE;
}
// Override the base functionality //
CShipDataClass* Data::SetMemberIsSetAndReturnPointer(int c_hashKey)
{
    if (c_hashKey == 6758)
    {
        m_headerIsSet = true;
        return &m_header;
    }
    if (c_hashKey == 56141)
    {
        m_extensionIsSet = true;
        return &m_extension;
    }
    return NULL;
}
// Override the base functionality //
std::vector<int32_t> Data::getListOfSetMembers() const
{
    std::vector<int32_t> returnList;
    if (m_headerIsSet)
    {
        returnList.push_back(4);
    }
    if (m_extensionIsSet)
    {
        returnList.push_back(6);
    }
    return returnList;
}
// Override the base functionality //
ValueType Data::getSimpleMemberAsString(int c_hashKey, std::string& r_valueString)
{
    (void)c_hashKey;
    (void)r_valueString;
    return VALUE_NOT_DEFINED;
}
// Override the base functionality //
void Data::setSimpleMemberAsString(int c_hashKey, const char* c_stringValue, ValueType c_valueType)
{
    (void)c_hashKey;
    (void)c_stringValue;
    (void)c_valueType;
}
Header Data::getHeader(void) const
{
    if (m_headerIsSet)
    {
        return m_header;
    }
    return Header();
}
bool Data::getHeaderIsSet(void) const
{
    return m_headerIsSet;
}
void Data::setHeader(const Header& c_value)
{
    m_header = c_value;
    m_headerIsSet = true;
}
void Data::cleanHeader(void)
{
    m_header = Header();
    m_headerIsSet = false;
}
Payload Data::getPayload(void) const
{
    return m_payload;
}
void Data::setPayload(const Payload& c_payload)
{
    m_payload = c_payload;
}
void Data::cleanPayload(void)
{
    m_payload = Payload();
}

Extension Data::getExtension(void) const
{
    if (m_extensionIsSet)
    {
        return m_extension;
    }
    return Extension();
}
bool Data::getExtensionIsSet(void) const
{
    return m_extensionIsSet;
}

void Data::setExtension(const Extension& c_value)
{
    m_extension = c_value;
    m_extensionIsSet = true;
}
void Data::cleanExtension(void)
{
    m_extension = Extension();
    m_extensionIsSet = false;
}
