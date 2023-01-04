/* -*-C++-*- */

#ifndef CATSlotManifoldAttribute_H
#define CATSlotManifoldAttribute_H

// COPYRIGHT DASSAULT SYSTEMES 2012

//=============================================================================
//=============================================================================
//
// CATSlotManifoldAttribute : Attribut DRep pour les Slots.
//
//=============================================================================

//=============================================================================
// Sep 2012  Creation                                                       PRL
//           Simple repompage de CATPadPocketManifoldAttribute avec modifs
// 2013      Ajout de const un peu partout                               Spa US
// Nov 2014  Ajout methode Set/Get/Width/Length/Blind/Declarative           PRL
// Nov 2016  Ajout methode GetDepth                                         I49  
//
// Responsible is PRL, do not modify without permission
//
//=============================================================================
//=============================================================================

#include "CATPersistentCell.h"
#include "CATCGMNewArray.h"
#include "CATExtrusionManifoldAttribute.h"
#include "CATMathInline.h"
#include "ListPOfCATFace.h"
#include "CATDeclarativeType.h"

class CATMathVector;
class CATExtrusionUtilities;

// tmp
#define CATSlotTypeUnknown  0
#define CATSlotTypeBlind    1
#define CATSlotTypeThrough  2


class ExportedByPersistentCell CATSlotManifoldAttribute : public CATExtrusionManifoldAttribute
{
public: 
//===========================================================================================================

  CATCGMDeclareAttribute (CATSlotManifoldAttribute, CATExtrusionManifoldAttribute);

  CATSlotManifoldAttribute(); 
  CATSlotManifoldAttribute(CATSoftwareConfiguration* ipConfig, CATMathVector const & iExtrudeDir, ListPOfCATFace const & iExtrudeFaces, ListPOfCATFace const & iSupportFaces, ListPOfCATFace const & iEndFaces, ListPOfCATFace const & iExitFaces);
  CATSlotManifoldAttribute(CATSoftwareConfiguration* ipConfig, CATMathVector const & iExtrudeDir, ListPOfCATCellManifold const & iExtrudeCMs, ListPOfCATCellManifold const & iSupportCMs, ListPOfCATCellManifold const & iEndCMs, ListPOfCATCellManifold const & iExitCMs);
  virtual ~CATSlotManifoldAttribute();

  //CATSlotManifoldAttribute(CATSlotManifoldAttribute& iToCopy); // Forbidden  Il ne suffit pas de l'ecrire...
  //CATSlotManifoldAttribute& operator= (const CATSlotManifoldAttribute& iToCopy); // Forbidden  Il ne suffit pas de l'ecrire...
  virtual CATManifoldAttribute* Clone(CATCloneManager& iCloneManager) const;
  virtual void Move3D(CATTransfoManager& iTransfoManager);

  CATCGMNewClassArrayDeclare;      // Pool allocation

  virtual CATCellManifoldGroupNavigator* CreateGroupNavigator(CATLiveBody* iLiveBody, const CATTopData& iTopData, CATCellManifoldGroup* iGroup) const;

  virtual void Stream(CATCGMStream & ioStream) const;
  virtual void UnStream(CATCGMStream& ioStream);  
  virtual void Dump(CATCGMOutput& iWhereToWrite) const;

  // Specifique Slot... pas completement vrai, mais bon...
  virtual void        SetBlindType(short iType);
  virtual CATBoolean  IsBlind();  

  virtual void        SetDeclarativeType(CATDeclarativeType  iType);
  virtual void        GetDeclarativeType(CATDeclarativeType &oType);

  virtual void        SetWidth (double   iWidth);
  virtual void        SetLength(double   iLength);
  virtual void        GetWidth (double  &oWidth);
  virtual void        GetLength(double  &oLength);
  virtual double      GetDepth() const; // Bel effort pour respecter les signatures existantes :-(

  INLINE CATSlotManifoldAttribute *GetAsSlotManifoldAttribute();
  
protected:
  virtual CATManifoldAttribute * CreateImageAttribute(const CATLISTP(CATCellManifoldGroup) &iParentGroups, 
                                                      const CATCellManifoldGroup           &iImageCellManifoldGroup, 
                                                      CATCellManifoldsManager &iCellManifoldsManager) const;

private:
//===========================================================================================================
  
  //------------------------------------------------------------------------------
  // Donnees membre
  //------------------------------------------------------------------------------  
  short                  _BlindType; // cf. CATSlotTypeBlindCyl/CATSlotTypeThrough
  short                  _DeclaType; // cf. CATDeclarativeType
  double                 _Width;     // Largeur  = diametre slot si round slot (et largeur du rectangle sinon)
  double                 _Length;    // Longueur = distance entre les axes des cylindres si round (et longueur du rectangle sinon)

  CATExtrusionUtilities* _Util;      // Utilitaire [pour calcul de la profondeur]

  //------------------------------------------------------------------------------
  // Juste pour eviter que le compilo ne definisse par lui-meme ces operateurs
  //------------------------------------------------------------------------------  
  //CATSlotManifoldAttribute();
  CATSlotManifoldAttribute(CATSlotManifoldAttribute& iObj);
  CATSlotManifoldAttribute& operator=(const CATSlotManifoldAttribute & iObj);
};

// Methodes INLINE
//===========================================================================================================

INLINE CATSlotManifoldAttribute *CATSlotManifoldAttribute::GetAsSlotManifoldAttribute()
{
  return (CATSlotManifoldAttribute *) this;
}

#endif


// Ne rien ecrire sous cette ligne
//===========================================================================================================



