/*
 *     Copyright KEO GmbH 2017 - All rights reserved!
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
#include "AppConfiguration.h"
#include <keo_util/KEIniReader.h>
#include <keo_util/KELogging.h>

/* ****************************************************************************** *
 *  standard header files                                                         *
 * ****************************************************************************** */

#include <fstream>
#include <sys/stat.h>

/* ****************************************************************************** *
 *  defines                                                                       *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  types                                                                         *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  definition                                                                    *
 * ****************************************************************************** */

namespace keo_spine_example_client
{

const char* SECTION = "DeviceConfiguration";

static void fillConfiguration(AppConfiguration& cfg, const keo_util::KEIniReader& ini)
{
    DEBUG_FUNC();
    cfg.setSpineDevice(ini.get(SECTION, "SpineDevice", "d:_i:47859_KEO-SimpleDeviceClient"));
    cfg.setSHIPHostAddress(ini.get(SECTION, "ConnectionHost", "localhost"));
    cfg.setSHIPHostPort(ini.get<std::int32_t>(SECTION, "ConnectionPort", 0));
    cfg.setCertificateFullFilename(ini.get(SECTION, "CertificateFullFilename", "prime256v1CertDER.bin"));
    cfg.setPrivateKeyFullFilename(ini.get(SECTION, "PrivateKeyFullFilename", "prime256v1KeyDER.bin"));
    cfg.setTruststoreFullFilename(ini.get(SECTION, "TruststoreFullFilename", "truststore.json"));
    cfg.setShipId(ini.get(SECTION, "ShipId", "ShipId"));
    cfg.setShipPin(ini.get(SECTION, "ShipPin", ""));
    cfg.setShipPinRequirement(ini.get(SECTION, "ShipPinRequirement", ""));
    cfg.setBrand(ini.get(SECTION, "DeviceBrand", "devicebrand"));
    cfg.setType(ini.get(SECTION, "DeviceType", "devicetype"));
    cfg.setModel(ini.get(SECTION, "DeviceModel", "devicemodel"));
    cfg.setInstanceName(ini.get(SECTION, "InstanceName", "instancename"));
}

bool AppConfiguration::readConfiguration(AppConfiguration& config, const std::string& filename)
{
    DEBUG_FUNC();
    bool retval = false;

    struct stat buffer;
    if (stat(filename.c_str(), &buffer) == 0)
    {
        keo_util::KEIniReader ini;

        if (ini.parse(filename))
        {
            if (ini.hasSection(SECTION))
            {
                fillConfiguration(config, ini);
                retval = true;
            }
            else
            {
                LOG_WARNING() << "Configuration '" << filename << "' contains no 'DeviceConfiguration' section";
            }
        }
        else
        {
            LOG_ERROR() << "Configuration '" << filename << "' parse error " << ini.getLastError();
        }
    }
    else
    {
        LOG_ERROR() << "File not found '" << filename << "'";
    }
    return retval;
}

keo_ship::ShipStackConfiguration AppConfiguration::getShipConfiguration() const
{
    DEBUG_FUNC();
    keo_ship::ShipStackConfiguration shipStackConfiguration;
    shipStackConfiguration.setShipId(shipId);
    if (pinRequirement.empty())
    {
        shipStackConfiguration.setPinRequirement(keo_ship::PinRequirement::PIN_NONE);
    }
    else
    {
        keo_ship::PinRequirement requirement(keo_ship::PinRequirement::PIN_REQUIRED);
        if (pinRequirement.compare("none") == 0)
        {
            requirement = keo_ship::PinRequirement::PIN_NONE;
        }
        else if (pinRequirement.compare("ok") == 0)
        {
            requirement = keo_ship::PinRequirement::PIN_OK;
        }
        else if (pinRequirement.compare("optional") == 0)
        {
            requirement = keo_ship::PinRequirement::PIN_OPTIONAL;
        }
        shipStackConfiguration.setPinRequirement(requirement);
    }
    return shipStackConfiguration;
}

} /* namespace keo_spine_example_client */
