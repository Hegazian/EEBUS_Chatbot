/*
 *     Copyright KEO GmbH 2013 - All rights reserved!
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
 *  standard header files                                                         *
 * ****************************************************************************** */
#include <iostream>

/* ****************************************************************************** *
 *  project header files                                                          *
 * ****************************************************************************** */
#include <gtest/gtest.h>
#include <keo_datagram/core/Datagram.h>
#include <keo_datagram/core/ScaledNumber.h>
#include <keo_datagram/measurement/Measurement_All.h>
#include <keo_datagram/smartenergymanagementps/SmartEnergyManagementPs_All.h>

/* ****************************************************************************** *
 *  defines                                                                       *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  types                                                                         *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  definition                                                                    *
 * ****************************************************************************** */

#include <gtest/gtest.h>

using namespace keo_datagram;

MeasurementListData createMeasurementListData()
{
    MeasurementData data1;
    data1.setMeasurementId(1);
    data1.setValue(ScaledNumber(3, 4));
    MeasurementData data2;
    data2.setMeasurementId(2);
    data2.setValue(ScaledNumber(5, 6));
    std::vector<MeasurementData> measurements = { data1, data2 };
    return MeasurementListData(measurements);
}

TEST(FilterTests, testMeasurementListDataSingleSelectors)
{
    auto selector = std::make_shared<MeasurementListDataSelectors>();
    selector->setMeasurementId(1);
    std::vector<std::shared_ptr<DataSelectors>> selectors = { selector };
    Filter filter;
    filter.setCmdControl(CmdControl::PARTIAL);
    filter.setSelectorsList(selectors);
    std::vector<Filter> filters = { filter };

    MeasurementListData measurementListData = createMeasurementListData();
    MeasurementListData reduced = CmdData::reduce(measurementListData, filters);

    ASSERT_EQ(1U, reduced.getMeasurementData().size());
    ASSERT_EQ(1U, reduced.getMeasurementData()[0].getMeasurementId());
    ASSERT_EQ(3, reduced.getMeasurementData()[0].getValue().getNumber());
    ASSERT_EQ(4, reduced.getMeasurementData()[0].getValue().getScale());
}

TEST(FilterTests, testMeasurementListDataMultipleSelectors)
{
    auto selector1 = std::make_shared<MeasurementListDataSelectors>();
    selector1->setMeasurementId(1);
    auto selector2 = std::make_shared<MeasurementListDataSelectors>();
    selector2->setMeasurementId(2);
    std::vector<std::shared_ptr<DataSelectors>> selectors = { selector1, selector2 };
    Filter filter;
    filter.setCmdControl(CmdControl::PARTIAL);
    filter.setSelectorsList(selectors);
    std::vector<Filter> filters = { filter };

    MeasurementListData measurementListData = createMeasurementListData();
    MeasurementListData reduced = CmdData::reduce(measurementListData, filters);

    ASSERT_EQ(2U, reduced.getMeasurementData().size());
    ASSERT_EQ(1U, reduced.getMeasurementData()[0].getMeasurementId());
    ASSERT_EQ(3, reduced.getMeasurementData()[0].getValue().getNumber());
    ASSERT_EQ(4, reduced.getMeasurementData()[0].getValue().getScale());

    ASSERT_EQ(2U, reduced.getMeasurementData()[1].getMeasurementId());
    ASSERT_EQ(5, reduced.getMeasurementData()[1].getValue().getNumber());
    ASSERT_EQ(6, reduced.getMeasurementData()[1].getValue().getScale());
}

TEST(FilterTests, testMeasurementListDataElements)
{
    auto element = std::make_shared<MeasurementDataElements>();
    ScaledNumberElements sne(false, true);
    element->setValue(sne);
    Filter filter;
    filter.setCmdControl(CmdControl::PARTIAL);
    filter.setElement(element);
    std::vector<Filter> filters = { filter };

    MeasurementListData measurementListData = createMeasurementListData();
    MeasurementListData reduced = CmdData::reduce(measurementListData, filters);

    ASSERT_EQ(2U, reduced.getMeasurementData().size());
    ASSERT_FALSE(reduced.getMeasurementData()[0].getMeasurementIdIsSet());
    ASSERT_FALSE(reduced.getMeasurementData()[1].getMeasurementIdIsSet());
    ASSERT_FALSE(reduced.getMeasurementData()[0].getValue().getNumberIsSet());
    ASSERT_FALSE(reduced.getMeasurementData()[1].getValue().getNumberIsSet());
    ASSERT_TRUE(reduced.getMeasurementData()[0].getValue().getScaleIsSet());
    ASSERT_TRUE(reduced.getMeasurementData()[1].getValue().getScaleIsSet());
    ASSERT_EQ(4, reduced.getMeasurementData()[0].getValue().getScale());
    ASSERT_EQ(6, reduced.getMeasurementData()[1].getValue().getScale());
}

TEST(FilterTests, testMeasurementListDataElementsAndSelectors)
{
    auto selector = std::make_shared<MeasurementListDataSelectors>();
    selector->setMeasurementId(1);
    std::vector<std::shared_ptr<DataSelectors>> selectors = { selector };
    auto element = std::make_shared<MeasurementDataElements>();
    element->setMeasurementId();
    Filter filter;
    filter.setElement(element);
    filter.setCmdControl(CmdControl::PARTIAL);
    filter.setSelectorsList(selectors);
    std::vector<Filter> filters = { filter };

    MeasurementListData measurementListData = createMeasurementListData();
    MeasurementListData reduced = CmdData::reduce(measurementListData, filters);

    ASSERT_EQ(1U, reduced.getMeasurementData().size());
    ASSERT_EQ(1U, reduced.getMeasurementData()[0].getMeasurementId());
    ASSERT_TRUE(reduced.getMeasurementData()[0].getMeasurementIdIsSet());
    ASSERT_FALSE(reduced.getMeasurementData()[0].getValueIsSet());
}

TEST(FilterTests, testEmptyOnWrongSelectorType)
{
    auto selector = std::make_shared<SmartEnergyManagementPsDataSelectors>();
    std::vector<std::shared_ptr<DataSelectors>> selectors = { selector };
    Filter filter;
    filter.setCmdControl(CmdControl::PARTIAL);
    filter.setSelectorsList(selectors);
    std::vector<Filter> filters = { filter };

    MeasurementListData mld = createMeasurementListData();
    ASSERT_TRUE(CmdData::reduce(mld, filters).isEmpty());
}

TEST(FilterTests, testFullCopyOnWrongCmdControl)
{
    auto selector = std::make_shared<MeasurementListDataSelectors>();
    selector->setMeasurementId(1);
    std::vector<std::shared_ptr<DataSelectors>> selectors = { selector };
    Filter filter;
    filter.setCmdControl(CmdControl::DELETE);
    filter.setSelectorsList(selectors);
    std::vector<Filter> filters = { filter };

    MeasurementListData measurementListData = createMeasurementListData();

    MeasurementListData mld = createMeasurementListData();
    ASSERT_EQ(mld, CmdData::reduce(mld, filters));
}
