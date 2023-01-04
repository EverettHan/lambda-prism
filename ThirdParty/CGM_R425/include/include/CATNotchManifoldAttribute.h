/* -*-C++-*- */

#ifndef CATNotchManifoldAttribute_H
#define CATNotchManifoldAttribute_H

// COPYRIGHT DASSAULT SYSTEMES 2012

//=============================================================================
//=============================================================================
//
// CATNotchManifoldAttribute : Attribut DRep pour les Notches.
//
//=============================================================================

//=============================================================================
// Nov 2012  Creation                                                       PRL
//           Simple repompage de CATPadPocketManifoldAttribute avec modifs
// Nov 2016  Ajout methode GetLength/Width/CalculateCachedProperties        I49  
// Aug 2017  Remise au carre du travail bugge de l'ami Julian               PRL
//
// Responsible is PRL, do not modify without permission
//
//=============================================================================
//=============================================================================




#include "CATPersistentCell.h"
#include "CATCGMNewArray.h"
#include "CATExtrusionManifoldAttribute.h"
#include "CATCellManifoldNotchNavigatorInterface.h"
#include "CATMathInline.h"
#include "ListPOfCATFace.h"

class CATMathVector;
class CATExtrusionUtilities;

// tmp
#define CATNotchTypeUnknown  0
#define CATNotchTypeBlind    1
#define CATNotchTypeThrough  2
typedef CATCellManifoldNotchNavigatorInterface::EndWallType CATNotchEWType;


class ExportedByPersistentCell CATNotchManifoldAttribute : public CATExtrusionManifoldAttribute
{
public: 
//===========================================================================================================

  CATCGMDeclareAttribute (CATNotchManifoldAttribute, CATExtrusionManifoldAttribute);

  CATCGMNewClassArrayDeclare;      // Pool allocation

  CATNotchManifoldAttribute(); 
  CATNotchManifoldAttribute(CATSoftwareConfiguration* ipConfig, CATMathVector const & iExtrudeDir, ListPOfCATFace const & iExtrudeFaces, ListPOfCATFace const & iSupportFaces, ListPOfCATFace const & iEndFaces, ListPOfCATFace const & iExitFaces);
  CATNotchManifoldAttribute(CATSoftwareConfiguration* ipConfig, CATMathVector const & iExtrudeDir, ListPOfCATCellManifold const & iExtrudeCMs, ListPOfCATCellManifold const & iSupportCMs, ListPOfCATCellManifold const & iEndCMs, ListPOfCATCellManifold const & iExitCMs);
  virtual ~CATNotchManifoldAttribute();
    
  virtual CATManifoldAttribute* Clone(CATCloneManager& iCloneManager) const;
  virtual void Move3D(CATTransfoManager& iTransfoManager);

  virtual CATCellManifoldGroupNavigator* CreateGroupNavigator(CATLiveBody* iLiveBody, const CATTopData& iTopData, CATCellManifoldGroup* iGroup) const;

  virtual void Stream(CATCGMStream & ioStream) const;
  virtual void UnStream(CATCGMStream& ioStream);  
  virtual void Dump(CATCGMOutput& iWhereToWrite);

  void SetEndWallType(CATNotchEWType iEndWallType);
  CATNotchEWType GetEndWallType() const;
  virtual int  GetType() const;
  virtual void SetType(int & iType);
  double GetDepth();
  double GetLength();  // je ne vois pas l'interet de mettre du const si c'est pour mettre du mutable apres...
  double GetWidth();   // idem

  INLINE CATNotchManifoldAttribute *GetAsNotchManifoldAttribute();
protected:
  virtual CATManifoldAttribute * CreateImageAttribute(const CATLISTP(CATCellManifoldGroup) &iParentGroups, 
                                                     const CATCellManifoldGroup           &iImageCellManifoldGroup, 
                                                     CATCellManifoldsManager &iCellManifoldsManager) const;

private:
//===========================================================================================================
 
  //------------------------------------------------------------------------------
  // Donnees streamees
  //------------------------------------------------------------------------------    
  int                    _Type;
  CATNotchEWType         _EndWallType;

  //------------------------------------------------------------------------------
  // Donnees non streamees (temporaire?)
  //------------------------------------------------------------------------------    
  double                 _Length;
  double                 _Width;  
  double                 _Depth;  

  CATExtrusionUtilities* _Util;
  CATBoolean             _WiLenComputed; // calcul longueur/largeur
  CATBoolean             _DepthComputed; // calcul profondeur

  //------------------------------------------------------------------------------
  // Calcul des dimensions de la notche 
  //------------------------------------------------------------------------------    
  void ComputeWidthLength();
  //void ComputeWidthLength_v0(); // Suite discussion RR 28/08/2017: on ne conserve pas l'ancienne version, car on n'est pas dans un feature qui s'update
  void ComputeWidthLength_v1();

  //------------------------------------------------------------------------------
  // Juste pour eviter que le compilo ne definisse par lui-meme ces operateurs
  //------------------------------------------------------------------------------  
  CATNotchManifoldAttribute(CATNotchManifoldAttribute& iToCopy); 
  CATNotchManifoldAttribute& operator= (const CATNotchManifoldAttribute& iToCopy); 
};

// Methodes INLINE
//===========================================================================================================

INLINE CATNotchManifoldAttribute *CATNotchManifoldAttribute::GetAsNotchManifoldAttribute()
{
  return (CATNotchManifoldAttribute*) this;
}


#endif


// Ne rien ecrire sous cette ligne
//===========================================================================================================


