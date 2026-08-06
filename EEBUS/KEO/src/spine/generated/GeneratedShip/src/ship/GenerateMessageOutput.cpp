/*
 *     Copyright KEO GmbH 2014 - All rights reserved!
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

/**
 *  @brief Ship data message creation
 *
 *  @par    Module description
 *          All generated classes are testet here by generating random objects
 *
 */

#include <QDebug>
#include <QFile>
#include <QUuid>

#include "keo_ship/GenerateRandom.h"
#include "keo_ship/JsonBuilder.h"
#include "keo_ship/GenerateMessageOutput.h"

using namespace keo_ship;
// Write the content into a file //
void GenerateMessageOutput::writeFile(const QString& c_fileName, const QString& c_fileContent) 
{
    QFile outFile(c_fileName);
    if (!outFile.open(QIODevice::ReadWrite | QIODevice::Text | QIODevice::Truncate)) 
	{
		fprintf(stderr, "Could not save outfile: %s\n", qPrintable(c_fileName));
		return;
	}

  	QTextStream in(&outFile);
    in << c_fileContent << endl;
	outFile.close();
}
// Write the xml and json message output //
void GenerateMessageOutput::writeJson(CShipDataClass* c_pMessage, const QString& c_directory, const QString& c_name) 
{
    JsonBuilder builder;

    std::vector<char> jsonArray;
    jsonArray.push_back('{');
    std::vector<char> jsonClassString = builder.getJsonFromClass(c_pMessage);
    std::copy(jsonClassString.begin(), jsonClassString.end(), std::back_inserter(jsonArray));
    jsonArray.push_back('}');
    QString outString = QString::fromLatin1( &jsonArray[0]);
    writeFile(c_directory + c_name + ".json",outString.left(jsonArray.size()));
}
// Write all generated messages //
void GenerateMessageOutput::writeAllGeneratedMessages(const QString& c_directory)
{
  GenerateRandom::initialiseBasicTypeLimits(true);
  GenerateRandom::setMaximumForInteger(10);
  writeConnectionHelloToDirectory(c_directory);
  writeMessageProtocolHandshakeToDirectory(c_directory);
  writeMessageProtocolHandshakeErrorToDirectory(c_directory);
  writeConnectionPinStateToDirectory(c_directory);
  writeConnectionPinInputToDirectory(c_directory);
  writeConnectionPinErrorToDirectory(c_directory);
  writeAccessMethodsRequestToDirectory(c_directory);
  writeAccessMethodsToDirectory(c_directory);
  writeConnectionCloseToDirectory(c_directory);
  writeDataToDirectory(c_directory);

}

void GenerateMessageOutput::writeConnectionHelloToDirectory(const QString& c_directory)
{
	ConnectionHello* pData = new (std::nothrow) ConnectionHello(GenerateRandom::generateConnectionHello());
    if(pData) {
        writeJson(pData,c_directory,"ConnectionHello");
   }     
}
void GenerateMessageOutput::writeMessageProtocolHandshakeToDirectory(const QString& c_directory)
{
	MessageProtocolHandshake* pData = new (std::nothrow) MessageProtocolHandshake(GenerateRandom::generateMessageProtocolHandshake());
    if(pData) {
        writeJson(pData,c_directory,"MessageProtocolHandshake");
   }     
}
void GenerateMessageOutput::writeMessageProtocolHandshakeErrorToDirectory(const QString& c_directory)
{
	MessageProtocolHandshakeError* pData = new (std::nothrow) MessageProtocolHandshakeError(GenerateRandom::generateMessageProtocolHandshakeError());
    if(pData) {
        writeJson(pData,c_directory,"MessageProtocolHandshakeError");
   }     
}
void GenerateMessageOutput::writeConnectionPinStateToDirectory(const QString& c_directory)
{
	ConnectionPinState* pData = new (std::nothrow) ConnectionPinState(GenerateRandom::generateConnectionPinState());
    if(pData) {
        writeJson(pData,c_directory,"ConnectionPinState");
   }     
}
void GenerateMessageOutput::writeConnectionPinInputToDirectory(const QString& c_directory)
{
	ConnectionPinInput* pData = new (std::nothrow) ConnectionPinInput(GenerateRandom::generateConnectionPinInput());
    if(pData) {
        writeJson(pData,c_directory,"ConnectionPinInput");
   }     
}
void GenerateMessageOutput::writeConnectionPinErrorToDirectory(const QString& c_directory)
{
	ConnectionPinError* pData = new (std::nothrow) ConnectionPinError(GenerateRandom::generateConnectionPinError());
    if(pData) {
        writeJson(pData,c_directory,"ConnectionPinError");
   }     
}
void GenerateMessageOutput::writeAccessMethodsToDirectory(const QString& c_directory)
{
	AccessMethods* pData = new (std::nothrow) AccessMethods(GenerateRandom::generateAccessMethods());
    if(pData) {
        writeJson(pData,c_directory,"AccessMethods");
   }     
}
void GenerateMessageOutput::writeConnectionCloseToDirectory(const QString& c_directory)
{
	ConnectionClose* pData = new (std::nothrow) ConnectionClose(GenerateRandom::generateConnectionClose());
    if(pData) {
        writeJson(pData,c_directory,"ConnectionClose");
   }     
}
void GenerateMessageOutput::writeDataToDirectory(const QString& c_directory)
{
	Data* pData = new (std::nothrow) Data(GenerateRandom::generateData());
    if(pData) {
        writeJson(pData,c_directory,"Data");
   }     
}


