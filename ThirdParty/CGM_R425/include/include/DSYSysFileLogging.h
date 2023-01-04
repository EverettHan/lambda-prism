#ifndef DSYSYSFILELOGGING_H
#define DSYSYSFILELOGGING_H

#include "DSYString.h"
#include "JS0HTTP.h"

#define DSYSysFileLoggingGlobalCounter 0x0000000000000001L

class CATSysTSUnicodeString;    // TODO RM

//DSYSysFileLogging create log file in this format:
// E:\temp\                                       2014_02_28__16_10_28__21564
// iRootPath (argument of InitPath method)        a subdirectory of iRootPath named like this YYYY_MM_DD__HH_MIN_SEC__PID
//-rw-rw-rw-   1 DSONE\SIP       DSONE\Domain+Users      170 Feb 28 17:10 2014_02_28__16_10_29__0000000001CATComSidlStreamProcessorTest.txt
//-rw-rw-rw-   1 DSONE\SIP       DSONE\Domain+Users      162 Feb 28 17:10 2014_02_28__16_10_29__0000000001SidlAnswer.txt
//-rw-rw-rw-   1 DSONE\SIP       DSONE\Domain+Users  5242807 Feb 28 17:10 2014_02_28__16_10_29__0000000002CATComSidlStreamProcessorTest.txt
//-rw-rw-rw-   1 DSONE\SIP       DSONE\Domain+Users  5242807 Feb 28 17:10 2014_02_28__16_10_30__0000000002CATComSidlStreamProcessorTest.txt
//-rw-rw-rw-   1 DSONE\SIP       DSONE\Domain+Users  5242807 Feb 28 17:10 2014_02_28__16_10_32__0000000002CATComSidlStreamProcessorTest.txt
//-rw-rw-rw-   1 DSONE\SIP       DSONE\Domain+Users  5242807 Feb 28 17:10 2014_02_28__16_10_33__0000000002CATComSidlStreamProcessorTest.txt
//...
//-rw-rw-rw-   1 DSONE\SIP       DSONE\Domain+Users 10485614 Feb 28 17:10 2014_02_28__16_10_43__0000000002CATComSidlStreamProcessorTest.txt
//-rw-rw-rw-   1 DSONE\SIP       DSONE\Domain+Users 10485614 Feb 28 17:10 2014_02_28__16_10_44__0000000002CATComSidlStreamProcessorTest.txt
//-rw-rw-rw-   1 DSONE\SIP       DSONE\Domain+Users 10485614 Feb 28 17:10 2014_02_28__16_10_45__0000000002CATComSidlStreamProcessorTest.txt
//-rw-rw-rw-   1 DSONE\SIP       DSONE\Domain+Users 15728421 Feb 28 17:10 2014_02_28__16_10_46__0000000002CATComSidlStreamProcessorTest.txt
//                                                                        YYYY_MM_DD__HH_MIN_S__{sequence num}{iFileName arg from Write methode}.{iFileExtention arg from Write methode}
//...
//When file name doesn't change one file is writen by second. So if multiple write happends during a second the file is appened.


class ExportedByJS0HTTP DSYSysFileLogging
{
public:
	DSYSysFileLogging(unsigned int iMode = 0);
	~DSYSysFileLogging();

    HRESULT		InitPath(const CATUnicodeString &iRootPath);
    // @deprecated R417
	HRESULT		InitPath(CATSysTSUnicodeString &iRootPath);

	//Methode to check if iRootPath exists and that also create a directory YYYY_MM_DD__HH_MIN_SEC__PID under iRootPath
	//Return code:
	// - S_OK: if iRootPath exists and if it successfully create the directory YYYY_MM_DD__HH_MIN_SEC__PID
	// - Otherwise: E_FAIL or Directory creation error, if iRootPath doesn't exist or if current process doesn't have right to create a directory in iRootPath
	HRESULT		Write(const char *iFileName, unsigned int iSeqNum, const char *iBuffer, unsigned int iBufferSize);
	HRESULT		Write(const char *iFileName, const char *iBuffer, unsigned int iBufferSize);
	HRESULT		Write(const CATUnicodeString &iFileName, unsigned int iSeqNum, const char *iBuffer, unsigned int iBufferSize);
    HRESULT		Write(const CATUnicodeString &iFileName, const char *iBuffer, unsigned int iBufferSize);
    // @deprecated R417
	HRESULT		Write(CATSysTSUnicodeString &iFileName, const char *iBuffer, unsigned int iBufferSize);

	//Methode to reset to 1 the sequence number in the file name. Sequence number is usefull to be able to identify request and responce in http communication (for exemple)
	void ResetSequenceNumber();

	//Methode to increase sequence number by 1. So next call to Write methode will concerne another request/responce sequence in http communication (for exemple)
	void NextSequenceNumber();
protected:
	HRESULT		ComposePathAndFileName(CATUnicodeString &oFullFilePath, const CATUnicodeString &iFileName);
	HRESULT		ComposeDate(CATUnicodeString &oStringDate, unsigned int iMode);
private:
	unsigned int		_FileNumber;
	unsigned int		_Mode;
	CATUnicodeString	_TraceFilePath;
};

#endif // DSYSYSFILELOGGING_H
