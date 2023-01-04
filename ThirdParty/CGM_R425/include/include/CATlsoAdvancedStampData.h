/* -*-C++-*- */
/**
* YSY2
*/

//============================================================================
// classe CATlsoAdvancedStampData
// WARNING  Only use for the KeepTop POC project Y2021
//============================================================================



#ifndef CATlsoAdvancedStampData_H
#define CATlsoAdvancedStampData_H

#include "CATDataType.h"
#include "ListPOfCATEdge.h"
#include "CATCGMVirtual.h"
#include "CATFaceHashTable.h"
#include "PersistentCell.h"
#include "CATCGMHashTableWithAssoc.h"
#include "CATGMAdvancedStampDefine.h"

class CATLiveBody;
class CATCGMStream;
class CATGeoFactory;
class CATBoneFillet;
class CATDraftManifold;

/**
 * @class CATlsoAdvancedStampData
 *
 * @brief 
 *	Data Structure for the AdvancedStampDetection service.
 *
 * @warning 
 *	Data structure in dev, for the KeepTop POC project.
 *
 * @author  Ysy2
 * @date  Y2021W18
 */

class ExportedByPersistentCell CATlsoAdvancedStampData : public CATCGMVirtual
{

public:



	// Constructor 
	// -----------
	CATlsoAdvancedStampData(CATLiveBody                    * iLiveBody,
													CATBoneFillet                  * iBoneFilletDM,
													CATDraftManifold               * iDraftDM,
                          CATFaceHashTable               & iTopFaceHT,
													const CATCGMHashTableWithAssoc & iEdgeToFaceListHT);


	// Destructor
	// ----------
	virtual ~CATlsoAdvancedStampData();

	/**
	 * @brief 
	 * Equality method between two given CATlsoAdvancedStampData
	 * 
	 * @param 
	 *  iData1
	 *  iData2
	 * @return 
	 *  return TRUE if iData1 and iData2 are equal, FALSE otherwise.
	 */
	static CATBoolean AreSameData(const CATlsoAdvancedStampData *iData1, 
																const CATlsoAdvancedStampData *iData2);

	//-------------------------------------------------------------------------------------------------------
	// Surcharge du new/delete
	//-------------------------------------------------------------------------------------------------------
	CATCGMNewClassArrayDeclare;

	// ===========
	// Get Methods
	// ===========
	// @nocgmitf
	INLINE CATLiveBody * GetLiveBody() const;
	// @nocgmitf
	INLINE CATBoneFillet * GetBoneFillet() const;
	// @nocgmitf
	INLINE CATDraftManifold * GetDraftManifold() const;
	// @nocgmitf
	void GetEdgeToFaceHT(CATCGMHashTableWithAssoc &oEdgeToFaceHT) const;
	// @nocgmitf
	void GetEdgeHTToKeep(CATEdgeHashTable & oToKeepEdgeHT) const;
  // @nocgmitf
  void GetAllFaceHT(CATFaceHashTable & oAllFaceHT) const;
  // @nocgmitf
  void GetTopFaceHT(CATFaceHashTable & oTopFaceHT) const;
  // @nocgmitf
  CATEdge * GetEdgeFromFaceHT(CATFaceHashTable & iFaceHT, CATAdvancedStampFaceType & oFaceType);
  // @nocgmitf
  void GetEdgeHTFromFaceHT(CATFaceHashTable & iFaceHT, CATEdgeHashTable & oEdgeHT, CATAdvancedStampFaceType & oFaceType);

	// ===========
	// Set Methods
	// ===========

	// ===========
	// Stream
	// ===========
	// @nocgmitf
	void Stream(CATCGMStream & ioStream);

	// @nocgmitf
	static CATlsoAdvancedStampData * UnStream(CATCGMStream & ioStream, CATGeoFactory * iFactory);

	// @nocgmitf
	void Dump(CATCGMOutput & Output);

  // @nocgmitf
  static void DeleteAllAssocs(CATCGMHashTableWithAssoc & HTWithAssoc);

private:

	void ResetMembers();

  //Stream/Unstream
  void EdgeToFaceListStream(CATCGMStream & ioStream);
  static void EdgeToFaceListUnstream(CATCGMStream & ioStream, CATGeoFactory * iFactory, CATCGMHashTableWithAssoc & ioEdgeToFaceListHT);


	// ============================
	// Internal Data (in CGMReplay)
	// ============================
	CATLiveBody						   * _LiveBody;
	CATBoneFillet            * _BoneFilletDM;
	CATDraftManifold         * _DraftDM;
  CATCGMHashTableWithAssoc   _EdgeToFaceHT;
  CATFaceHashTable           _TopFaceHT;

	// ============================
	// Computed Data (not recorded)
	// ============================


	// Copy-constructeur et affectation (ne compilera pas)
	CATlsoAdvancedStampData(CATlsoAdvancedStampData & iOrig);

	CATlsoAdvancedStampData & operator= (const CATlsoAdvancedStampData & iRight);

};


INLINE CATLiveBody * CATlsoAdvancedStampData::GetLiveBody() const
{
	return _LiveBody;
}

INLINE CATBoneFillet * CATlsoAdvancedStampData::GetBoneFillet() const
{
	return _BoneFilletDM;
}

INLINE CATDraftManifold * CATlsoAdvancedStampData::GetDraftManifold() const
{
	return _DraftDM;
}

#endif

