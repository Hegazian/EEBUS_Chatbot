#include "GenericClientFeature.h"
#include <keo_datagram/core/SpineResultErrors.h>

GenericClientFeature::GenericClientFeature(const NetworkManagementFeatureDescriptionData& featureDescription)
    : ClientFeature(featureDescription)
{
}

GenericClientFeature::~GenericClientFeature()
{
}

GenericClientFeaturePtr GenericClientFeature::createGenericClientFeature()
{
    NetworkManagementFeatureDescriptionData featureDescription;
    featureDescription.setFeatureAddress(FeatureAddress("", 2, 1));
    featureDescription.setRole(Role::Role::Value::CLIENT);
    featureDescription.setFeatureType(FeatureType(FeatureType::Value::GENERIC));
    featureDescription.setDescription("Generic test client feature");
    return GenericClientFeaturePtr(new GenericClientFeature(featureDescription));
}

bool GenericClientFeature::handleDatagram(const DatagramRecord& datagramRecord)
{
    return sendDatagram(datagramRecord.getDatagram().createResult(SpineResultErrors::OK, "OK"));
}

bool GenericClientFeature::handlePendingDatagramResponse(const DatagramRecord& datagramRecord, const DatagramMemo& memo)
{
    (void) datagramRecord;
    (void) memo;
    return false;
}

bool GenericClientFeature::timeoutHandler(const DatagramMemo& memo)
{
    (void) memo;
    return false;
}
