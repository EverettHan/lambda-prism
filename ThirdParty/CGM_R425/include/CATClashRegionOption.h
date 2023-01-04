//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2017
//=============================================================================
//
// CATClash2DUtils:
//    clash region option classes
//
//=============================================================================
// Usage notes:
//=============================================================================
// 06/01/17 : F1Z : Creation
// 02/04/20 : Q48 : XScale support
// DD/MM/YY
//=============================================================================
#ifndef CATClashRegionOption_H
#define CATClashRegionOption_H

// Clash
#include "Clash2D.h" // for ExportedByClash2D

// C++11
#include "CATGeoOpVirtual.h"

// System
#include "CATBoolean.h"

class CATCGMStream;
class CATCGMOutput;
class CATGeoODTScaleManager;

// ====================================================================== //
//                       CATClashRegionOption                             //
// ====================================================================== //
class ExportedByClash2D CATClashRegionOption
{
public:
   //-----------------------------------------------------------------------
   //- Object Management
   //-----------------------------------------------------------------------
   CATClashRegionOption();
   virtual ~CATClashRegionOption();
   virtual CATClashRegionOption & operator=(const CATClashRegionOption & iToCopy);

   //-----------------------------------------------------------------------
   //- Set - Interface
   //-----------------------------------------------------------------------
   void Activate();
   void Desactivate();

   //-----------------------------------------------------------------------
   //-Get - Interface
   //-----------------------------------------------------------------------
   virtual const char * GetType         ()                   const;
   virtual CATBoolean   IsATypeOf       (const char * iType) const;
           CATBoolean   IsOptionActivate()                   const;

   //-----------------------------------------------------------------------
   //-Stream
   //-----------------------------------------------------------------------
   virtual void Dump     (CATCGMOutput          & ioStream    ) const;
   virtual void Stream   (CATCGMStream          & ioStream    ) const;
   virtual void UnStream (CATCGMStream          & iStream     ,
                          CATGeoODTScaleManager * ScaleManager);

   virtual void ScaleOption(const CATGeoODTScaleManager * iScaleManager) = 0;

private:
   //-----------------------------------------------------------------------
   //-Attribute - private
   //-----------------------------------------------------------------------
   CATBoolean _OptionActivate;
};

// ====================================================================== //
//                   CATClashRegionPenetrationOption                      //
// ====================================================================== //
/**
 * This region option will launch the region penetration computation.
 */
class ExportedByClash2D CATClashRegionPenetrationOption : public CATClashRegionOption
{
public:
   //-----------------------------------------------------------------------
   //- Object Management
   //-----------------------------------------------------------------------
   CATClashRegionPenetrationOption(double iMaxDepth=0);
   virtual ~CATClashRegionPenetrationOption();
   virtual CATClashRegionPenetrationOption & operator=(const CATClashRegionPenetrationOption & iToCopy);

   //-----------------------------------------------------------------------
   //- Set - Interface
   //-----------------------------------------------------------------------
   void SetMaxDepth   (double iMaxDepth);
   void RemoveMaxDepth();

   //-----------------------------------------------------------------------
   //-Get - Interface
   //-----------------------------------------------------------------------
   virtual const char * GetType    ()                   const;
   virtual CATBoolean   IsATypeOf  (const char * iType) const;
           CATBoolean   HasMaxDepth()                   const;
           double       GetMaxDepth()                   const;

   //-----------------------------------------------------------------------
   //-Stream
   //-----------------------------------------------------------------------
   void Dump     (CATCGMOutput          & ioStream    ) const CATGEOOverride CATGEOFinal;
   void Stream   (CATCGMStream          & ioStream    ) const CATGEOOverride CATGEOFinal;
   void UnStream (CATCGMStream          & iStream     ,
                  CATGeoODTScaleManager * ScaleManager) CATGEOOverride CATGEOFinal;

   void ScaleOption(const CATGeoODTScaleManager * iScaleManager) CATGEOOverride CATGEOFinal;

private:
   //-----------------------------------------------------------------------
   //-Attribute - private
   //-----------------------------------------------------------------------
   double _MaxDepth;
};

// ====================================================================== //
//                  CATClashRegionSegmentationOption                      //
// ====================================================================== //
/**
 * This region option will launch the region segmentation based on
 * a max angle diff and max relative length information.
 */
class ExportedByClash2D CATClashRegionSegmentationOption : public CATClashRegionOption
{
public:
   //-----------------------------------------------------------------------
   //- Object Management
   //-----------------------------------------------------------------------
   CATClashRegionSegmentationOption(double iSagitta           = 0.03,
                                    double iMaxRelativeLength = 0.3 );
   virtual ~CATClashRegionSegmentationOption();
   virtual CATClashRegionSegmentationOption & operator=(const CATClashRegionSegmentationOption & iToCopy);

   //-----------------------------------------------------------------------
   //- Set - Interface
   //-----------------------------------------------------------------------
   void SetSagitta          (double iSagitta          );
   void SetMaxRelativeLength(double iMaxRelativeLength);

   //-----------------------------------------------------------------------
   //-Get - Interface
   //-----------------------------------------------------------------------
   virtual const char * GetType             ()                   const;
   virtual CATBoolean   IsATypeOf           (const char * iType) const;
           double       GetSagitta          ()                   const;
           double       GetMaxRelativeLength()                   const;

   //-----------------------------------------------------------------------
   //-Stream
   //-----------------------------------------------------------------------
   void Dump     (CATCGMOutput          & ioStream    ) const CATGEOOverride CATGEOFinal;
   void Stream   (CATCGMStream          & ioStream    ) const CATGEOOverride CATGEOFinal;
   void UnStream (CATCGMStream          & iStream     ,
                  CATGeoODTScaleManager * ScaleManager) CATGEOOverride CATGEOFinal;

   void ScaleOption(const CATGeoODTScaleManager * iScaleManager) CATGEOOverride CATGEOFinal;

private:
   //-----------------------------------------------------------------------
   //-Attribute - private
   //-----------------------------------------------------------------------
   double _Sagitta          ;
   double _MaxRelativeLength;
};

#endif
