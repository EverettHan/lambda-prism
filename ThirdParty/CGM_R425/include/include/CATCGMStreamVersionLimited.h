#ifndef CATCGMStreamVersionLimited_h
#define CATCGMStreamVersionLimited_h

// COPYRIGHT DASSAULT SYSTEMES  2009
#include "CATIACGMLevel.h"
#include "CATMathStreamVersionDef.h"
#include "ExportedByCATMathStream.h"
#include "CATBoolean.h"


/**
 *
 *  GM Persistency Change Management
 *
 *  Declaration of forecoming Data Version Format of CGM Persistency  
 *
 *  Last news about current working Level 
 *
 *     Internal Calendar (2013 year) is now managed by 
 *
 *           file:\\techno\HOME\CGM\Tech_Internal_Express\Tech_Internal_Express.html
 *
 *          Current Format under development is CatCGMStream_2012Winter  label
 *
 * 
 *     2012 season expectations are one single common version for the full year.
 *
 *             (so same weather conditions as 2009 Year with one single common version (V6=V5)
 *                    following 2011 with two new V5 versions
 *		                following 2010 without new V5 version)
 *         Due to Global warming with 2011 heat wawe on spring , climate disturbance and so on ..
 *
 *           So according to master schedules and V5 management reducing environment footprint , http://plmexecreview/ 
 *              Associated master target Release of V5-6R2013 may be V6R2013x/R214  (Be carefull NOT V6R2013/R213)
 *              Contact Release Implement Leader in case another change of timeframe occured
 *           Drop 2012Spring frozen and activated in CGMOFF-CGMPRJ made Friday 06 July 2012 (delivery 2012.week 27)
 *                 available in associated co-existence V5-V6 BSF rel release of saturday 14 th July 
 *
 *      Scope (contents, shedule, formats, maturity) of  forecoming 2013 innovations and iterations have not yet be closed  
 *        to relimit impact from convergent deliveries which may reached a suffisient quality level 
 *           for an association with for instance of  2013 development label "2012Winter" GM persistent data structures.
 *        Industrialisation of innovations is a continuous process.
 *
 *      Currently, on 31 august 2012, BSF Build,ODT,ODTIMPACT of Version Six (R216 R215) and Version Five (CXR24) are already available 
 *           you consult master schedule of  V6R2014 (R215)  V6R2014x (R216) and V6R2014 (R215) for more appropriate planning.
 *
 * For implement coding, current internal rules are still about :
 *
 *        + Mandatory for any core geometrical object data format change
 *        - Optionnal technic for applicative/external attributes 
 *
 *   About data and code management of this underlying dedicated persistency services (IsStreamable, Stream, Unstream, ...)
 *
 *      Before activation :
 *         Preventive tests can and should be perfomed with 
 *           - generated data persisted only in temporary output 
 *           - with persistency lifespan limited to working process
 *        and only under the control of following non commercial variable, for instance :
 *           CATCGMVersion=2012Winter   and  CATDevelopmentStage=TRUE
 *
 *      After activation :
 *         No local change should be made according to level of Data Version Format
 *         Forward compatibility must be maintained against any new changes.
 *
 */  
//


//---------------------------------------------------------------------------------
//  FORECASTING
//---------------------------------------------------------------------------------
// 2023Fall   Global GM Data Format  V5-6R2024-CXR34 & V6R2023x-R426   activation on June 2023
#define    CatCGMStream_2023Fall  CATCGMStreamVersion(+1722)

//---------------------------------------------------------------------------------
//  PAST Activation done 
//---------------------------------------------------------------------------------
// 2022Fall   Global GM Data Format  V5-6R2023-CXR33 & V6R2023x-R425   activation on June 2022
#define    CatCGMStream_2022Fall  CATCGMStreamVersion(+1720)

// 2021Fall   Global GM Data Format  V5-6R2022-CXR32 & V6R2022x-R424   activation on June 2021
#define    CatCGMStream_2021Fall  CATCGMStreamVersion(+1718)

// 2020Fall   Global GM Data Format  V5-6R2021-CXR31 & V6R2021x-R423   activation on December 2019
#define    CatCGMStream_2020Fall  CATCGMStreamVersion(+1715)

// 2019Fall   Global GM Data Format  V5-6R2020-CXR30 & V6R2020x-R422   activation on July 2019
#define    CatCGMStream_2019Fall  CATCGMStreamVersion(+1712)

// 2018Fall   Global GM Data Format  V5-6R2019-CXR29 & V6R2019x-R421   activation on July 2018
#define    CatCGMStream_2018Fall  CATCGMStreamVersion(+1710)

// 2017Fall   Global GM Data Format  V5-6R2018-CXR28 & V6R2018x-R420   activation on July 2017
#define    CatCGMStream_2017Fall  CATCGMStreamVersion(+1708)

// 2016Fall   Global GM Data Format  V5-6R2017-CXR27 & V6R2017x-R419   activation on July 2016
#define    CatCGMStream_2016Fall  CATCGMStreamVersion(+1704)

// 2015Fall   Global GM Data Format  V5-6R2016-CXR26 & V6R2016x-R418   activation on July 2015
#define    CatCGMStream_2015Fall  CATCGMStreamVersion(+1700)

// 2014Fall   Global GM Data Format  V5-6R2015-CXR25 & V6R2015x-R417   activation on July 2014
#define    CatCGMStream_2014Fall  CATCGMStreamVersion(+1696)

// 2013 Fall   Global GM Data Format  V5-6R2014-CXR24  V6R2014x-R216   activation DONE  25 October 2013
#define    CatCGMStream_2013Fall  CATCGMStreamVersion(+1694)

// 2013 Spring  CGMReplay dedicated activation DONE  25 October 2013
#define    CatCGMStream_2013Spring  CATCGMStreamVersion(+1689)


//---------------------------------------------------------------------------------
// 2012 Winter  V6R2014-R215 activation possible 11 January July 2012   
//---------------------------------------------------------------------------------
//              CURRENTLY UNDER DEVELOPMENT 
//---------------------------------------------------------------------------------

#define    CatCGMStream_2012Winter  CATCGMStreamVersion(+1686)



// 2012 Spring  Global GM Data Format  V5-6R2013-CXR23 V6R2013x-R214   activation DONE  14 July 2012   
#define    CatCGMStream_2012Spring  CATCGMStreamVersion(+1680)


// For 2011 Fall common Ph.I/Ph II  Geometrical Native Data Format 
//               V6R2012x/R212 and V5-6R2012 
#define    CatCGMStream_2011Fall  CATCGMStreamVersion(+1675)

//
// For 2011  common Ph.I/Ph II Geometrical Native Data Format 
//               V5R21 and  V6R2012/R211
#define    CatCGMStream_2011Spring  CATCGMStreamVersion(+1672)

//
// For 2010  common Ph.I/Ph II Geometrical Native Data Format 
//               V6R2011x / R210
#define    CatCGMStream_2010Fall  CATCGMStreamVersion(+1670)

//
// For begin of 2010  R209_V6R2011 
//
#define    CatCGMStream_R209_V6R2011  CATCGMStreamVersion(+1669)
#define    CatCGMStream_2010Spring    CatCGMStream_R209_V6R2011

//
// For 2009  Best So Far Geometrical Native Data Format 
//   (FROZEN CXR20 and R208 levels)
//
#define    CatCGMStream_2009Fall  CATCGMStreamVersion(+1668)
 
 

//
// For Debug Only
//
#define    CatCGMStream_NeverActivated  CATCGMStreamVersion(+9999)
#define    CatCGMStream_Volatile        CATCGMStreamVersion(+6666)


#endif /* CATCGMStreamVersionLimited_h */
