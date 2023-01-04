// COPYRIGHT DASSAULT SYSTEMES 2015, ALL RIGHTS RESERVED.
//===================================================================
//
// CATBSVLink.h
//
//===================================================================
//
// Link between 2 CATBSVNode in CATBodyToShape
//
//===================================================================
//
// October 2015 Creation: rr
//===================================================================
#ifndef CATBSVLink_h
#define CATBSVLink_h

#include "CATVLink.h"
#include "CATMathematics.h"
#include "CATErrorDef.h"
#include "CATCGMNewArray.h"

class CATSoftwareConfiguration;
class CATBSVNode;

class ExportedByCATMathematics CATBSVLink : public CATVLink
{
public:
  //-----------------------------------------------------------------------------
  // Object Management
  //-----------------------------------------------------------------------------
  CATBSVLink(CATSoftwareConfiguration *iConfig, CATBSVNode* iNode1, CATBSVNode* iNode2, const short iAngle, const short iSide1, const short iSide2);
  CATCGMNewClassArrayDeclare;        // Pool allocation
  ~CATBSVLink();

  //-----------------------------------------------------------------------------
  // Data access 
  //-----------------------------------------------------------------------------
  short GetSide(const CATBSVNode* iNode) const; // Side of the linked node versus iNode 
  void InvertSide(const CATBSVNode* iNode);
  HRESULT Check() const;

  //-----------------------------------------------------------------------------
  // Customisation
  //-----------------------------------------------------------------------------
  virtual void DumpValue(ostream& ioOS) const;
  virtual HRESULT HasSameValue(const CATVLink& iLink, const int Orn) const;

  //-----------------------------------------------------------------------------
  // Compact Stream 
  //-----------------------------------------------------------------------------
  static int GetMaxCode(); 
  unsigned char GetCode() const; 
  CATBSVLink(CATSoftwareConfiguration *iConfig, CATBSVNode* iNode1, CATBSVNode* iNode2, const int iIndex);

private:
  //-----------------------------------------------------------------------------
  // Object Management
  //-----------------------------------------------------------------------------
  void Set(CATBSVNode* iNode1, CATBSVNode* iNode2, const short iAngle, const short iSide1, const short iSide2);

  //-----------------------------------------------------------------------------
  // Data
  //-----------------------------------------------------------------------------
  short      _Side[2]; // Side[i]: Side of _Wall[1-i] vs _Wall[i]
  short      _Angle;   // -1: opposite, 1: aligned,  0: angle!=0 
  //-----------------------------------------------------------------------------
};

#endif
