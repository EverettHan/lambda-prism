#ifndef CATSYSTSTIME_H
#define CATSYSTSTIME_H
#include "CATSysTS.h"
#include "CATSysTSDataType.h"


/* No. of days in for thses many years */
#define CATSysTSTime_d400Y	146097
#define CATSysTSTime_d100Y	36524
#define CATSysTSTime_d4Y	1461
#define CATSysTSTime_d1Y	365

/* Uptill the values for nanoSec*/
#define CATSysTSTime_power9 ((CATLONG64)1000000000)
#define CATSysTSTime_power6 ((CATLONG64)1000000)
#define CATSysTSTime_power3 ((CATLONG64)1000)

/* to hold the MAX OPERATIONAL values */ 
#define CATSysTSTime_MAX_OPERATION_YEAR         8099                                // 9999-1900 = 8099
#define CATSysTSTime_MAX_OPERATION_MONTH        97188                               // 8099*12
#define CATSysTSTime_MAX_OPERATION_DAY          2964234                             // 8099*366

#define CATSysTSTime_MAX_OPERATION_HOUR         (CATLONG64)8784                     // 366*24
#define CATSysTSTime_MAX_OPERATION_MIN          (CATLONG64)1440                     // 24*60 
#define CATSysTSTime_MAX_OPERATION_SEC          (CATLONG64)86400                    // 24*60*60
#define CATSysTSTime_MAX_OPERATION_MILLISEC     (CATLONG64)86400000                 // 24*60*60*1000
#define CATSysTSTime_MAX_OPERATION_MICROSEC     (((CATLONG64)24)*60*60*1000000)     // 24*60*60*1000*1000
#define CATSysTSTime_MAX_OPERATION_NANOSEC      (((CATLONG64)24)*60*60*1000000000)  // 24*60*60*1000*1000*1000

/* to hold the MAX values */ 
#define CATSysTSTime_MAX_DATE  2964234  // 8099*366
#define CATSysTSTime_MAX_CLOCK  (((CATLONG64)24)*60*60*1000000000)  // 24*60*60*1000*1000*1000

class ExportedByCATSysTS CATSysTSTime
{
public :

	enum CATSysTSTime_TimeZone
	{
		CATSysTSTime_TimeZone_UTC = 0
	};


	/**
	 * Constructors of instance.
	 * It will be initialized to the following date
	 * [UTC, year 1900, month 01, day 01, hour 00, minute 00, second 00, millisecond 00, microsecond 00, nanosecond 00]
	 */
	CATSysTSTime();
		
	/** 
	 * Constructors of instance copy.
	 * @param in_time
	 *   CATSysTSTime representation 
	 */
	CATSysTSTime(const CATSysTSTime& in_Time);
	
	/**
	 * destructors
	 */
	virtual ~CATSysTSTime();         

	/** 
	 * Recycles an existing instance.
	 * @param in_Time
	 *   CATSysTSTime representation 
	 * @return HRESULT
	 *   code representation for successful or failed operation  
	 */
	HRESULT SetTime( const CATSysTSTime& in_Time); 
	
	/** 
	 * Sets the Existing time (m_date, m_clock and m_timeZone). If the input 
	 * time is within the specified range the new will be set else the earlier 
	 * time will be retained
	 * @param in_TimeZone
	 *   TimeZone representation for the time zone, <b> Legal values</b>: CATSysTSTime_TimeZone_UTC
	 * @param in_Year
	 *   int representation for Year, <b> Legal values</b>: from 1900 to 9999 
	 * @param in_Month
	 *   int representation for Month, <b> Legal values</b>: from 1 to 12 
	 * @param in_Day
	 *   int representation for Day, <b> Legal values</b>: from 1 to 31 
	 * @param in_Hour
	 *   int representation for Hour, <b> Legal values</b>: from 0 to 23 
	 * @param in_Min
	 *   int representation for Minutes, <b> Legal values</b>: from 0 to 59 
	 * @param in_Sec
	 *   int representation for Seconds, <b> Legal values</b>: from 0 to 59 
	 * @param in_MilliSec 
	 *   int representation for Milli Seconds, <b> Legal values</b>: from 0 to 999 
	 * @param in_MicroSec 
	 *   int representation for Micro Seconds, <b> Legal values</b>: from 0 to 999 
	 * @param in_NanoSec 
	 *   int representation for Nano Seconds, <b> Legal values</b>: from 0 to 999 
	 * @return HRESULT
	 *   code representation for successful or failed operation  
	 */
	HRESULT SetTime(CATSysTSTime_TimeZone in_TimeZone, int in_Year, int in_Month, int in_Day, int in_Hour, int in_Min, int in_Sec, int in_MilliSec, int in_MicroSec, int in_NanoSec); 
		
	
	/*
	 * retrieve a CATSysTSTime object.
	 * @param out_Time
	 *   CATSysTSTime representation 
	 * @return HRESULT
	 *   code representation for successful or failed operation  
	 */
	HRESULT GetTime(CATSysTSTime& out_Time ) const;

	/**
	* Gets the current time from system
	* specified parameters.
	* @param oUTCtime;
	*   oUTCtime represent time in ms from OS base (1601 or 1970)
	* @param UTCbias;
	*   UTCbias represent the timezone to for the current time
	* @return HRESULT
	*   code representation for successful or failed operation
	*/
	HRESULT	GetTime(CATULONG64 *oUTCtime, CATLONG32 *UTCbias);



	/**
	 * Gets the Existing time ( from m_date, m_clock and m_timeZone) in the
	 * specified parameters. 
	 * @param out_TimeZone
	 *   TimeZone representation for the time zone
	 * @param out_Year
	 *   int representation for Year 
	 * @param out_Month
	 *   int representation for Month 
	 * @param out_Day
	 *   int representation for Day 
	 * @param out_Hour
	 *   int representation for Hour 
	 * @param out_Min
	 *   int representation for Minutes 
	 * @param out_Sec
	 *   int representation for Seconds 
	 * @param out_MilliSec 
	 *   int representation for Milli Seconds 
	 * @param out_MicroSec 
	 *   int representation for Micro Seconds 
	 * @param out_NanoSec 
	 *   int representation for Nano Seconds 
	 * @return HRESULT
	 *   code representation for successful or failed operation  
	 */
	HRESULT GetTime(CATSysTSTime_TimeZone& out_TimeZone, int& out_Year, int& out_Month, int& out_Day, int& out_Hour, int& out_Min, int& out_Sec, int& out_MilliSec, int& out_MicroSec, int& out_NanoSec ); 
		
	
		/*
	 * Return the number of day between the origine date and in_year, in_month, in_day
	 * Indicate the Number of Days Between the two dates
	 * 1901/02/02 - 1900/01/01 = 1 Year + 1 Month (Ist Month - Jan) + 1 day
	 *						   = 365 + 31 + 1
	 *						   = 397
	 * DateToNumberOfDay(1900,1,1) ->	0 = ;
	 * DateToNumberOfDay(1900,1,31) ->	30 ;
	 * DateToNumberOfDay(1900,2,28) ->	31 + 27 = 58 ;
	 * DateToNumberOfDay(1900,12,31) ->	364 ;
	 * DateToNumberOfDay(1901,1,1) ->	365  ;
	 * DateToNumberOfDay(1901,2,2) ->	365+31+1 = 397 ;
	 * @param in_year
	 *	The input year date
	 * @param in_month
	 *	The input month date
	 * @param in_day
	 *	The input day date
	 * @param out_dayNumber
	 * 	The expected number of day
	 * @return HRESULT
	 *   code representation for successful or failed operation  
	 * @return HRESULT
	 */	
	HRESULT	DateToNumberOfDay	(int in_year, int in_month, int in_day, int& out_dayNumber ) const;

	/*
	 * Return in_year, in_month, in_day  from a number of day.
	 * Indicates the Date From the Origin(1900/01/01) plus the number of Days Specified
	 * 1900/01/01 + 397 = 1900/01/01 + 365 + 31 + 1
	 *					= 1900/01/01 + 1Yr + Ist Mn + 1 Day
	 *					= (1900/01/01 + 365) + Jan(01) + 1
	 *					= (1901/01/01 + 01 )+ 1		
	 *					= 1901/02/01 + 1 = 1901/02/02.	
	 * NumberOfDayToDate(0) -> 1900/01/01;
	 * NumberOfDayToDate(1) -> 1900/01/02;
	 * NumberOfDayToDate(2) -> 1900/01/03;
	 * NumberOfDayToDate(31) -> 1900/02/01;
	 * NumberOfDayToDate(364) -> 1900/12/31;
	 * NumberOfDayToDate(365) -> 1901/01/01;
	 * NumberOfDayToDate(366) -> 1901/01/02;
	 * NumberOfDayToDate(397) -> 1901/02/02;
	 * @param in_dayNumber
	 * 	The number of day
	 * @param out_year
	 *	The year date
	 * @param out_month
	 *	The month date
	 * @param out_day
	 *	The day date
	 * @return HRESULT
	 *   code representation for successful or failed operation  
	 * @return HRESULT
	 */	
	HRESULT	NumberOfDayToDate	(int in_dayNumber, int& out_year, int& out_month, int& out_day ) const;

	/*
	 * Sets the Current System Time. The time set is at GMT +00:00.
	 * @return HRESULT
	 *   code representation for successful or failed operation  
	 * @return HRESULT
	 */
	HRESULT SetCurrentTime() ;

	/*
	 * Adds the date & time to current date & time.
	 * After Addition the Date should be in the range
	 * 1900/01/01 <= Date <= 9999/12/31
	 * For Example - Adding Time after Default Constructor
	 * Add(0, 0, 0, 0, 0, 0, 0, 0, 1) -> 1900/01/01 00:00:00:000:000:001	
	 *
	 * Say the Date Set is  - 2000/02/02 & 16:15:00:000:000:000
	 * Add(4, 20, 30, 37, 50, 0, 0, 0, 0) -> 2005/11/6 & 06:05:00:000:000:000
	 * Add(4, 20, 30, 37, 50, 0, 0, 0, 1000)-> 2005/11/6 & 06:05:00:000:001:001
	 *
	 * @param in_Year
	 *   int representation for Year, <b> Legal values</b>: from 0 to CATSysTSTime_MAX_OPERATION_YEAR 
	 * @param in_Month
	 *   int representation for Month, <b> Legal values</b>: from 0 to CATSysTSTime_MAX_OPERATION_MONTH 
	 * @param in_Day
	 *   int representation for Day, <b> Legal values</b>: from 0 to CATSysTSTime_MAX_OPERATION_DAY 
	 * @param in_Hour
	 *   int representation for Hour, <b> Legal values</b>: from 0 to CATSysTSTime_MAX_OPERATION_HOUR 
	 * @param in_Min
	 *   int representation for Minutes, <b> Legal values</b>: from 0 to CATSysTSTime_MAX_OPERATION_MIN  
	 * @param in_Sec
	 *   int representation for Seconds, <b> Legal values</b>: from 0 to CATSysTSTime_MAX_OPERATION_SEC 
	 * @param in_MilliSec 
	 *   int representation for Milli Seconds, <b> Legal values</b>: from 0 to CATSysTSTime_MAX_OPERATION_MILLISEC 
	 * @param in_MicroSec 
	 *   int representation for Micro Seconds, <b> Legal values</b>: from 0 to CATSysTSTime_MAX_OPERATION_MICROSEC
	 * @param in_NanoSec 
	 *   int representation for Nano Seconds, <b> Legal values</b>: from 0 to CATSysTSTime_MAX_OPERATION_NANOSEC
	 * @return HRESULT
	 *   code representation for successful or failed operation   
	 */
	HRESULT Add(int in_Year, int in_Month, int in_Day, CATLONG64 in_Hour, CATLONG64 in_Min, CATLONG64 in_Sec, CATLONG64 in_MilliSec, CATLONG64 in_MicroSec, CATLONG64 in_NanoSec) ;

	/*
	 * Subtract the date & time from the current date & time.
	 * After Subtraction the Date should be in the range
	 * 1900/01/01 <= Date <= 9999/12/31
	 * 
	 * For Example - Substracting Time after Default Constructor
	 * Sub(0, 0, 0, 0, 0, 0, 0, 0, 9) -> 1900/01/01 & 23:59:59:999:999:991	
	 *
	 * Say the Date Set is  - 2000/03/02 & 00:00:00:000:000:000
	 * Sub(0, 0, 02, 0, 0, 0, 0, 0, 0) -> 2000/02/29 & 00:00:00:000:000:000
	 * Sub(0, 0, 0, 48, 0, 0, 0, 0, 0)-> 2000/02/29 & 00:00:00:000:000:000
	 *
	 * @param in_Year
	 *   int representation for Year, <b> Legal values</b>: from 0 to CATSysTSTime_MAX_OPERATION_YEAR 
	 * @param in_Month
	 *   int representation for Month, <b> Legal values</b>: from 0 to CATSysTSTime_MAX_OPERATION_MONTH 
	 * @param in_Day
	 *   int representation for Day, <b> Legal values</b>: from 0 to CATSysTSTime_MAX_OPERATION_DAY 
	 * @param in_Hour
	 *   int representation for Hour, <b> Legal values</b>: from 0 to CATSysTSTime_MAX_OPERATION_HOUR 
	 * @param in_Min
	 *   int representation for Minutes, <b> Legal values</b>: from 0 to CATSysTSTime_MAX_OPERATION_MIN  
	 * @param in_Sec
	 *   int representation for Seconds, <b> Legal values</b>: from 0 to CATSysTSTime_MAX_OPERATION_SEC 
	 * @param in_MilliSec 
	 *   int representation for Milli Seconds, <b> Legal values</b>: from 0 to CATSysTSTime_MAX_OPERATION_MILLISEC 
	 * @param in_MicroSec 
	 *   int representation for Micro Seconds, <b> Legal values</b>: from 0 to CATSysTSTime_MAX_OPERATION_MICROSEC
	 * @param in_NanoSec 
	 *   int representation for Nano Seconds, <b> Legal values</b>: from 0 to CATSysTSTime_MAX_OPERATION_NANOSEC
	 * @return HRESULT
	 *   code representation for successful or failed operation     
	*/
	HRESULT Sub(int in_Year, int in_Month, int in_Day, CATLONG64 in_Hour, CATLONG64 in_Min, CATLONG64 in_Sec, CATLONG64 in_MilliSec, CATLONG64 in_MicroSec, CATLONG64 in_NanoSec);


	/*
	 * Assignment operator from long int.
	 * @param in_TimeToCopy
	 *   CATSysTSTime representation to be copied 
	 * @return CATSysTSTime
	 *   CATSysTSTime return reference on the current object  
	 */
	CATSysTSTime& operator =  ( const CATSysTSTime &in_TimeToCopy);
	
	/*
	 * Equality operator.
	 * @param in_TimeToCompare
	 *   CATSysTSTime representation to be compared 
	 * @return CATBoolean
	 *    True : if compared objects are equals
	 *    False : if compared objects are different
	 */
	CATBoolean    operator == ( const CATSysTSTime &in_TimeToCompare ) const;
	
	/*
	 * Inequality operator.
	 * @param in_TimeToCompare
	 *   CATSysTSTime representation to be compared 
	 * @return CATBoolean
	 *    True : if compared objects are different
	 *    False : if compared objects are equals
	 */
	CATBoolean    operator != ( const CATSysTSTime &in_TimeToCompare ) const;
	
	/*
	 * Strictly less-than operator.
	 * @param in_TimeToCompare
	 *   CATSysTSTime representation to be compared 
	 * @return CATBoolean
	 *    True : if compared objects is strictly inferior
	 *    False : if compared objects is higher or equal 
	 */
	CATBoolean    operator <  ( const CATSysTSTime &in_TimeToCompare ) const;
	
	/*
	 * Striclty higher-than operator.
	 * @param in_TimeToCompare
	 *   CATSysTSTime representation to be compared 
	 * @return CATBoolean
	 *    True : if compared objects is strictly higher
	 *    False : if compared objects is inferior or equal 
	 */
	CATBoolean    operator >  ( const CATSysTSTime &in_TimeToCompare ) const;
	
	/*
	 * Less-than equal operator.
	 * @param in_TimeToCompare
	 *   CATSysTSTime representation to be compared 
	 * @return CATBoolean
	 *    True : if compared objects is equal inferior
	 *    False : if compared objects is strictly higher
	 */
	CATBoolean    operator <= ( const CATSysTSTime &in_TimeToCompare ) const;
	
	/*
	 * Higher-than equal operator.
	 * @param in_TimeToCompare
	 *   CATSysTSTime representation to be compared 
	 * @return CATBoolean
	 *    True : if compared objects is equal higher
	 *    False : if compared objects is strictly inferior
	 */
	CATBoolean    operator >= ( const CATSysTSTime &in_TimeToCompare ) const;

private:
	/*
	 * Return the number of day from the origine date to the last day of the specified year
	 * the number of day from [1900/01/01 to x/12/31]
	 * YearToNumberOfDay(1900) -> 365 = 1900/01/01 - 1900/12/31
	 * YearToNumberOfDay(1901) -> 365*2 = 1900/01/01 - 1901/12/31
	 * YearToNumberOfDay(1902) -> 365*3 = 1900/01/01 - 1902/12/31
	 * YearToNumberOfDay(1903) -> 365*4 = 1900/01/01 - 1903/12/31
	 * YearToNumberOfDay(1904) -> 365*5 + 1 = 1900/01/01 - 1904/12/31 (being Leap year)
	 * YearToNumberOfDay(2000) -> 365*101 + 24 = 1900/01/01 - 2001/12/31(being Leap year)
	 * @param in_year
	 *	The year date
	 * @param out_dayNumber
	 * 	The number of day
	 * @return HRESULT
	 *   code representation for successful or failed operation  
	 * @return HRESULT
	 */	
	HRESULT	YearToNumberOfDay	(int in_year, int& out_dayNumber) const;

	/*
	 * Return the number of days from the first day of the specified year to the last day of the specified month
	 * the number of day between [01/01/1900; Date/mon/yr]
	 * MonthToNumberOfDay(1900, 0) -> 0 = 1 = [1900/01/01 ; 1900/01/01]
	 * MonthToNumberOfDay(1900, 1) -> 31 = 31 =  [1900/01/01 ; 1900/01/31]
	 * MonthToNumberOfDay(1900, 2) -> 59 = 31+28 = [1900/01/01 ; 1900/02/28]
	 * MonthToNumberOfDay(1900, 12) -> 365 = 31+28+31+.....30+31 = [1900/01/01 ; 1900/12/31]
	 * MonthToNumberOfDay(1904, 2) -> 60 = 31+29 =  [1904/01/01 ; 1904/02/29]
	 * MonthToNumberOfDay(1904, 12) -> 366 = 31+29+31...+30+31 = [1904/01/01 ; 1904/12/31] (being leap year)
	 * MonthToNumberOfDay(2001, 03) -> 90 = 31+28+31 = [2001/01/01; 2001/03/31]
	 * MonthToNumberOfDay(2004, 02) -> 60 = [2004/01/01; 2004/02/29] (being leap Year)
	 * @param in_year
	 *	The year date
	 * @param in_year
	 *	The month date
	 * @param out_dayNumber
	 * 	The number of day
	 * @return HRESULT
	 *   code representation for successful or failed operation  
	 * @return HRESULT
	 */	
	HRESULT	MonthToNumberOfDay (int in_year, int in_month, int& out_dayNumber) const;

	/*
	 * Return the number of Year from a number of day. It also returns the remaining days.
	 * It indicates the Year from 1900 (origin) and extra Days after that year(Year/01/01).
	 * Indicates the year of the day (1900/01/01 + xdays)
	 * NumberOfDayToYear (0) -> (1900, 0) = (1900/01/01)
	 * NumberOfDayToYear (1) -> (1900, 1) = (1900/01/01)
	 * NumberOfDayToYear (364) -> (1900, 364) = (1900/12/31)
	 * NumberOfDayToYear (365) -> (1901, 0) = (1901/01/01)
	 * NumberOfDayToYear (366) -> (1901, 1) = (1901/01/02)
	 * @param in_dayNumber
	 * 	The number of day
	 * @param out_year
	 *	The year date
	 * @param out_dayNumber
	 *	The remaining days
	 * @return HRESULT
	 *   code representation for successful or failed operation  
	 * @return HRESULT
	 */	
	HRESULT	NumberOfDayToYear (int in_dayNumber, int& out_year, int& out_dayNumber) const;

	/*
	 * Return the month number from a number of day after the first day of the specified year. It also returns the remaining days.
	 * Indicates the Months of the Year and the remaining Days of that Month
	 * NumberOfDayToMonth (1900, 0) -> (1, 0) = (1900/01/01)
	 * NumberOfDayToMonth (1900, 1) -> (1, 1) = (1900/01/02)
	 * NumberOfDayToMonth (1900, 2) -> (1, 2) = (1900/01/03)
	 * NumberOfDayToMonth (1900, 364) -> (12, 30) (1900/12/31)
	 * NumberOfDayToMonth (1904, 31) -> (2, 0) = (1904/02/01) at the end
	 * NumberOfDayToMonth (1904, 32) -> (2, 1) = (1904/02/02)
	 * NumberOfDayToMonth (1904, 57) -> (2, 26) = (1904/02/27)
	 * NumberOfDayToMonth (1904, 58) -> (2, 27) = (1904/02/28)
	 * NumberOfDayToMonth (1904, 59) -> (3, 0) = (1904/03/01)
	 * NumberOfDayToMonth (1904, 60) -> (3, 1) = (1904/03/02)
	 * NumberOfDayToMonth (1904, 61) -> (3, 2) = (1904/03/03)
	 * @param in_year
	 *	The year date
	 * @param in_year
	 *	The month date
	 * @param out_dayNumber
	 * 	The number of day
	 * @return HRESULT
	 *   code representation for successful or failed operation  
	 * @return HRESULT
	 */	
	HRESULT	NumberOfDayToMonth	(int in_year, int in_dayNumber, int& out_month, int& out_dayNumber) const;

	/*
	 * Return the True if the specified year is a leap year, false otherwise
	 * @param in_year
	 *	The year date
	 * @param out_isLeap
	 * 	True if it's a leap year, false otherwise
	 * @return HRESULT
	 *   code representation for successful or failed operation  
	 * @return HRESULT
	 */	
	HRESULT	IsLeapYear		(int in_year, CATBoolean& out_isLeap) const;
	
	/*
	 * Gets the Maximum number of days for the month.
	 * @param month
	 *   int representation for month
	 * @param isLeap
	 *   CATBoolean tells if the Year is Leap. 
	 * @return int
	 *   Number of days for the month.
	 */
	int MaximumDays(int month,CATBoolean isLeap) const;

	/*
	 * Validates the Date. The date should be between 1900/01/01 to 9999/12/31
	 * @param in_Year
	 *   int representation for Year
	 * @param in_Month
	 *   int representation for Month
	 * @param in_Day
	 *   int representation for day
	 * @return CATBoolean
	 *   TRUE if the Year(1900 - 9999) Month(1 -12) and Date(1 - 31)
	 *	are in the range. FALSE otherwise
	 */
	CATBoolean IsValidDate(int in_Year = 1900, int in_Month = 1, int in_Day = 1) const;

	/*
	 * Validates the Time. The Time should be between 0 to 24hrs
	 * @param in_Hour
	 *   int representation for Hour
	 * @param in_Min
	 *   int representation for Minute
	 * @param in_Sec
	 *   int representation for Second
	 * @param in_mSec
	 *   int representation for milliSecon
	 * @param in_uSec
	 *   int representation for microSecond
	 * @param in_nSec
	 *   int representation for nanoSecond
	 * @return CATBoolean
	 *   TRUE if the Hour(0 - 23), Min(0-59),Sec (0-59), mSec(0-999)
	 * uSec(0-999) and nSec(0-999) are in the range. FALSE otherwise
	 */
	CATBoolean IsValidClock(int in_Hour = 0, int in_Min = 0, int in_Sec = 0, int in_mSec = 0, int in_uSec = 0, int in_nSec = 0) const;

	/*
	 * Validates the Date and Time. The date should be between 1900/01/01 to 9999/12/31
	 * And time should be in between 0 -24 hrs
	 * @param in_Clock
	 *   int representation for time
	 * @param in_Date
	 *   int representation for date
	 * @return CATBoolean
	 *   TRUE if the Date should not exceed CATSysTSTime_MAX_OPERATION_DAY
	 * and Clock should not exceed CATSysTSTime_MAX_OPERATION_NANOSEC.
	 * FALSE otherwise
	 */
	CATBoolean IsExceedingMAXTime(CATLONG64 in_Clock = 0, CATLONG32 in_Date = 0) const;

	
	CATLONG32	m_date; // hold date in terms of days
	CATLONG64	m_clock; // hold time in terms of nanosecs
	CATSysTSTime_TimeZone		m_timeZone;

};
#endif
