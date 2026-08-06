/* ****************************************************************************** *
 *  standard header files                                                         *
 * ****************************************************************************** */
#include <iostream>

/* ****************************************************************************** *
 *  project header files                                                          *
 * ****************************************************************************** */
#include <gtest/gtest.h>
#include <keo_datagram/core/Datagram.h>
#include <keo_datagram/hvac/HvacSystemFunctionSetpointRelationData.h>
#include <keo_datagram/hvac/HvacSystemFunctionSetpointRelationListData.h>
#include <keo_spine_datagramVersion.h>

/* ****************************************************************************** *
 *  defines                                                                       *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  types                                                                         *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  definition                                                                    *
 * ****************************************************************************** */

TEST(DatagramParse, ParseEmptyList)
{
    // Related to Redmine Ticket http://sl-vm-04/redmine/issues/1974
    std::vector<keo_datagram::HvacSystemFunctionSetpointRelationData> listHvacSystemFunctionSetpointRelationData;
    {
        // Heating: OperationModeId off -> no setpoint relations
        keo_datagram::HvacSystemFunctionSetpointRelationData hvacSystemFunctionSetpointRelationData;
        hvacSystemFunctionSetpointRelationData.setSystemFunctionId(1);
        hvacSystemFunctionSetpointRelationData.setOperationModeId(0);
        std::vector<keo_datagram::xs_unsignedInt> listSetpointId;
        hvacSystemFunctionSetpointRelationData.setSetpointId(listSetpointId);
        listHvacSystemFunctionSetpointRelationData.push_back(hvacSystemFunctionSetpointRelationData);
    }
    {
        // Heating: OperationModeId auto -> setpoint relations: day, setback
        keo_datagram::HvacSystemFunctionSetpointRelationData hvacSystemFunctionSetpointRelationData;
        hvacSystemFunctionSetpointRelationData.setSystemFunctionId(1);
        hvacSystemFunctionSetpointRelationData.setOperationModeId(1);
        std::vector<keo_datagram::xs_unsignedInt> listSetpointId;
        listSetpointId.push_back(1);
        listSetpointId.push_back(2);
        hvacSystemFunctionSetpointRelationData.setSetpointId(listSetpointId);
        listHvacSystemFunctionSetpointRelationData.push_back(hvacSystemFunctionSetpointRelationData);
    }
    {
        // Heating: OperationModeId on -> setpoint relations: day
        keo_datagram::HvacSystemFunctionSetpointRelationData hvacSystemFunctionSetpointRelationData;
        hvacSystemFunctionSetpointRelationData.setSystemFunctionId(1);
        hvacSystemFunctionSetpointRelationData.setOperationModeId(2);
        std::vector<keo_datagram::xs_unsignedInt> listSetpointId;
        listSetpointId.push_back(1);
        hvacSystemFunctionSetpointRelationData.setSetpointId(listSetpointId);
        listHvacSystemFunctionSetpointRelationData.push_back(hvacSystemFunctionSetpointRelationData);
    }
    {
        // Heating: OperationModeId eco -> setpoint relations: setback
        keo_datagram::HvacSystemFunctionSetpointRelationData hvacSystemFunctionSetpointRelationData;
        hvacSystemFunctionSetpointRelationData.setSystemFunctionId(1);
        hvacSystemFunctionSetpointRelationData.setOperationModeId(3);
        std::vector<keo_datagram::xs_unsignedInt> listSetpointId;
        listSetpointId.push_back(2);
        hvacSystemFunctionSetpointRelationData.setSetpointId(listSetpointId);
        listHvacSystemFunctionSetpointRelationData.push_back(hvacSystemFunctionSetpointRelationData);
    }

    keo_datagram::HvacSystemFunctionSetpointRelationListDataPtr hvacSystemFunctionSetpointRelationListDataPtr(
        new keo_datagram::HvacSystemFunctionSetpointRelationListData(listHvacSystemFunctionSetpointRelationData));

    keo_datagram::Datagram spineDatagramPtr;
    keo_datagram::Cmd cmd(hvacSystemFunctionSetpointRelationListDataPtr);
    spineDatagramPtr.setCmd(cmd);
    keo_datagram::FeatureAddress featureAddress;
    featureAddress.setDevice("device");
    std::vector<keo_datagram::xs_unsignedInt> entity;
    entity.push_back(1);
    featureAddress.setEntity(entity);
    featureAddress.setFeature(1);

    spineDatagramPtr.setCmdClassifier(keo_datagram::CmdClassifier::Value::NOTIFY);
    spineDatagramPtr.setDestinationAddress(featureAddress);
    spineDatagramPtr.setSourceAddress(featureAddress);

    std::string spineDatagramJson = spineDatagramPtr.toJson();

    spineDatagramPtr.parsePayload();

    keo_datagram::Datagram spineDatagramConvertPtr = keo_datagram::Datagram::fromJson(spineDatagramJson);
    std::string spineDatagramJsonConvert = spineDatagramConvertPtr.toJson();

    ASSERT_TRUE(spineDatagramConvertPtr.parsePayload());
    ASSERT_TRUE(spineDatagramConvertPtr.isPayloadValid());
    keo_datagram::Header header = spineDatagramConvertPtr.getHeader();
    header.setMsgCounter(1L);
    spineDatagramConvertPtr.setHeader(header);
    const std::string jsonResult = spineDatagramConvertPtr.toJson();

    std::string jsonExpected
        = "{\"datagram\":[{\"header\":[{\"specificationVersion\":\"";

    jsonExpected += SPINE_VERSION_STRING;

    jsonExpected += "\"},{\"addressSource\":[{\"device\":\"device\"}"
          ",{\"entity\":[1]},{\"feature\":1}]},{\"addressDestination\":[{\"device\":\"device\"},{\"entity\":[1]},{"
          "\"feature\":1}]},{\"msgCounter\":1},{\"cmdClassifier\":\"notify\"}]},{\"payload\":[{\"cmd\":[[{"
          "\"hvacSystemFunctionSetpointRelationListData\":[{\"hvacSystemFunctionSetpointRelationData\":[[{"
          "\"systemFunctionId\":1},{\"operationModeId\":0},{\"setpointId\":[]}],[{\"systemFunctionId\":1},{"
          "\"operationModeId\":1},{\"setpointId\":[1,2]}],[{\"systemFunctionId\":1},{\"operationModeId\":2},{"
          "\"setpointId\":[1]}],[{\"systemFunctionId\":1},{\"operationModeId\":3},{\"setpointId\":[2]}]]}]}]]}]}]}";




    ASSERT_EQ(jsonExpected, jsonResult);
}
