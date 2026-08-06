#ifndef GENERATE_MESSAGE_OUTPUT__H__
#define GENERATE_MESSAGE_OUTPUT__H__


#include <QString>
#include "keo_ship/CShipDataClass.h"

namespace keo_ship  {

/** @addtogroup ShipDataClass
 * @{
 */

class GenerateMessageOutput
{

public:

    /** bool writeFile()
     *
     * Write the content into a file.
     * @param c_fileName name of file
     * @param c_fileContent content of file
     */
static void writeFile(const QString& c_fileName, const QString& c_fileContent);

    /** bool writeJson()
     *
     * Write the content to a json file.
     * @param c_pMessage message pointer
     * @param c_directory name of directory
     * @param c_name classifier plus name of cmd type
     */
static void writeJson(CShipDataClass* c_pMessage, const QString& c_directory, const QString& c_name);

    /** bool writeAllGeneratedMessages()
     *
     * Write all generated messages.
     */
static void writeAllGeneratedMessages(const QString& c_directory);

    /** writeConnectionHelloToDirectory
     *
     * Random generation of the CONNECTIONHELLO MESSAGE and save it to the directory 
     * @param c_directory output directory
     */
static void writeConnectionHelloToDirectory(const QString& c_directory);

    /** writeMessageProtocolHandshakeToDirectory
     *
     * Random generation of the MESSAGEPROTOCOLHANDSHAKE MESSAGE and save it to the directory 
     * @param c_directory output directory
     */
static void writeMessageProtocolHandshakeToDirectory(const QString& c_directory);

    /** writeMessageProtocolHandshakeErrorToDirectory
     *
     * Random generation of the MESSAGEPROTOCOLHANDSHAKEERROR MESSAGE and save it to the directory 
     * @param c_directory output directory
     */
static void writeMessageProtocolHandshakeErrorToDirectory(const QString& c_directory);

    /** writeConnectionPinStateToDirectory
     *
     * Random generation of the CONNECTIONPINSTATE MESSAGE and save it to the directory 
     * @param c_directory output directory
     */
static void writeConnectionPinStateToDirectory(const QString& c_directory);

    /** writeConnectionPinInputToDirectory
     *
     * Random generation of the CONNECTIONPININPUT MESSAGE and save it to the directory 
     * @param c_directory output directory
     */
static void writeConnectionPinInputToDirectory(const QString& c_directory);

    /** writeConnectionPinErrorToDirectory
     *
     * Random generation of the CONNECTIONPINERROR MESSAGE and save it to the directory 
     * @param c_directory output directory
     */
static void writeConnectionPinErrorToDirectory(const QString& c_directory);

    /** writeAccessMethodsRequestToDirectory
     *
     * Random generation of the ACCESSMETHODSREQUEST MESSAGE and save it to the directory 
     * @param c_directory output directory
     */
static void writeAccessMethodsRequestToDirectory(const QString& c_directory);

    /** writeAccessMethodsToDirectory
     *
     * Random generation of the ACCESSMETHODS MESSAGE and save it to the directory 
     * @param c_directory output directory
     */
static void writeAccessMethodsToDirectory(const QString& c_directory);

    /** writeConnectionCloseToDirectory
     *
     * Random generation of the CONNECTIONCLOSE MESSAGE and save it to the directory 
     * @param c_directory output directory
     */
static void writeConnectionCloseToDirectory(const QString& c_directory);

    /** writeDataToDirectory
     *
     * Random generation of the DATA MESSAGE and save it to the directory 
     * @param c_directory output directory
     */
static void writeDataToDirectory(const QString& c_directory);



private:

    // Empty Constructor //
    GenerateMessageOutput();
    // Empty Destructor //
    ~GenerateMessageOutput();
    	
};
/** @}
 */
} // end namespace keo_ship
#endif

