#ifndef CATGlobalDRepModification_H
#define CATGlobalDRepModification_H

//VB7
//===========================================================================
// Output of VariationalManager
// Input of SingleModifyFace operators
// carries data about DRep in order to edit it (by Parameter creation)
//CAN BE STREAMED
//===========================================================================

#include "CATPersistentCell.h"
#include "CATCGMVirtual.h"
#include "ListPOfCATManifold.h"
#include "CATManifoldParameter.h"
#include "ListPOfCATOneDRepModification.h"
#include "ListPOfCATFace.h"

class CATManifold;
class CATBody;
class CATMathVector;
class CATPersistentCellInfra;
class CATOneDRepModification;
class CATSoftwareConfiguration;
class CATMathTransformation;

// Prevoir HashTalbe pour les DRepModif
// Hashage basé sur TagManifold + Key
// --------------------------------------

class ExportedByPersistentCell CATGlobalDRepModification : public CATCGMVirtual
{
public:

  // Constructor
  CATGlobalDRepModification(CATSoftwareConfiguration *iConfig); 
  // Destructor
  virtual ~CATGlobalDRepModification();


  // @nocgmitf
  void GetManifoldToModify(ListPOfCATManifold & oManifoldToModif) const;
  // @nocgmitf
  // GetModification throught body filter
  int RetrieveModifications(ListPOfCATOneDRepModification &oListOfDRepModification, CATBody *ipBody=NULL , const ListPOfCATFace *ipListFace=NULL) const;
  // nocgmitf
  int RetrieveModifications(CATManifold *ipManifold, ListPOfCATOneDRepModification &oListOfDRepModification) const;
  // nocgmitf
  int RetrieveModifications(const ListPOfCATFace &iInputFaceList, ListPOfCATOneDRepModification *oListOfDRepModification=NULL) const;

  // @nocgmitf 
  HRESULT AppendTransfo(CATManifold * iManifold, CATBody * iBody, int iKey, const CATMathTransformation &iTransfo);
  // @nocgmitf
  HRESULT AppendVector(CATManifold * iManifold, CATBody * iBody, int iKey, const CATMathVector & iVector);
  // @nocgmitf 
  HRESULT AppendDouble(CATManifold * iManifold, CATBody * iBody, int iKey, double iDouble);
  // @nocgmitf
  // -1 = fail, 0 = updated, 1 = new
  int AppendModification(CATOneDRepModification *ipOneDRepModif);
  // @return nb added elements
  int AppendGlobalModification(const CATGlobalDRepModification *ipGlobalModif);

  // @nocgmitf
  void GenerateParameters(CATPersistentCellInfra & iInfra, int iNumOperatorId) const;

  // @nocgmitf - boucle en N2. A optimiser avec HashTable.
  CATBoolean Compare(const CATGlobalDRepModification & iGlobalModifToCompare) const;
  
  // @nocgmitf
  int                      Size() const;
  // @nocgmitf
  CATOneDRepModification * Get(unsigned int iNum) const;

  // @nocgmitf
  void Dump(CATCGMOutput& Output) const;
  // @nocgmitf
  void Stream(CATCGMStream & ioStream) const ;
  // @nocgmitf
  void UnStream(CATCGMStream & ioStream, CATGeoFactory * iFactory);

private :
  
  INLINE CATSoftwareConfiguration * GetSoftwareConfiguration() const;
  INLINE const ListPOfCATOneDRepModification & GetModifications() const; 


  CATOneDRepModification * FindOneDRepModification(CATManifold * iManifold, CATBody * iBody, CATLONG32 iKey) const;
   
  // Copy constructor - forbidden
  CATGlobalDRepModification(const CATGlobalDRepModification & iGlobalDRepModification);
  CATGlobalDRepModification & operator =(const CATGlobalDRepModification & iGlobalDRepModification);

private :

  CATSoftwareConfiguration          * _Config;
  ListPOfCATOneDRepModification       _DRepModificationList;

};

// ----------------------------------------------------------------------------------------------
INLINE CATSoftwareConfiguration * CATGlobalDRepModification::GetSoftwareConfiguration() const {
// ----------------------------------------------------------------------------------------------
  return _Config ; }

// ----------------------------------------------------------------------------------------------
INLINE const ListPOfCATOneDRepModification & CATGlobalDRepModification::GetModifications() const {
// ----------------------------------------------------------------------------------------------
  return _DRepModificationList; }

#endif
