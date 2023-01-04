#ifndef CATMathLocalVersioning_h
#define CATMathLocalVersioning_h

// ExportedBy macros 
#include "ExportedByCATMathStream.h"

// Utilities
#include "CATMathInline.h"

// DS Data types
#include "CATBoolean.h"
#include "CATUnicodeString.h"

// C++11
#include "CATMathCpp11.h"

// ----------------------------------------------------------------------------------------------
// The main macro access point (to be used in source files)
// ----------------------------------------------------------------------------------------------

#ifndef MATH_CPP11
#define IsCGMVersioningActive(CGMLevel, flagData) (CGMLevel >= flagData)
#else
#define IsCGMVersioningActive(CGMLevel, flagData) ManualVersioningStore::IsVersioningFlagActive(CGMLevel, flagData)
#endif
// ----------------------------------------------------------------------------------------------

#ifdef MATH_CPP11
// std data types (for C++11)
#include <vector>

// ----------------------------------------------------------------------------------------------
// The parent class for storing versioning flag information
// ----------------------------------------------------------------------------------------------
class ManualVersioningData
{
public:

  ManualVersioningData(const short iFlagLevel, const CATUnicodeString & iFlagName);
  virtual ~ManualVersioningData();

  CATBoolean Matches(const ManualVersioningData & iFlag) const;

protected:
  const   CATUnicodeString _FlagName;
  mutable short            _FlagLevel;
};

// ----------------------------------------------------------------------------------------------
// Derived class to store flag information from the environment
// ----------------------------------------------------------------------------------------------
class /*ExportedByCATMathStream*/ ManualVersioningData_Env : public ManualVersioningData
{
public:
  ManualVersioningData_Env(const short iFlagLevel, const CATUnicodeString & iFlagName);
  virtual ~ManualVersioningData_Env();

  INLINE short GetLevel() const;
};

// ----------------------------------------------------------------------------------------------
// Derived class to store flag information of local (manual) flags
// ----------------------------------------------------------------------------------------------
class /*ExportedByCATMathStream*/ ManualVersioningData_Flag : public ManualVersioningData
{
public:
  ManualVersioningData_Flag(const short iFlagLevel, const CATUnicodeString & iFlagName);
  virtual ~ManualVersioningData_Flag();

  CATBoolean IsActive(const short iCGMLevel) const;

  void Update(const ManualVersioningData_Env & iEnvFlag) const;
  void SetUpdated() const;

private:

  void UpdateFromEnv() const;

private:

  mutable CATBoolean _UpdatedFromEnv;
};

// ----------------------------------------------------------------------------------------------
// Simple class to manage stored flag information
// ----------------------------------------------------------------------------------------------
class ExportedByCATMathStream ManualVersioningStore
{
public:

  static ManualVersioningStore* GetManualVersioning();

  virtual ~ManualVersioningStore();
  
  static const ManualVersioningData_Flag* AddManualFlag(const short              iFlagLevel,
                                                        const CATUnicodeString & iFlagFullName);

  void UpdateFlagFromEnv(const ManualVersioningData_Flag & iFlag) const;

  // The "standard" versioning method
  INLINE static CATBoolean IsVersioningFlagActive(const short iCGMLevel,
                                                  const short iFlagLevel);

  // The "local" versioning method
  static CATBoolean IsVersioningFlagActive(const short                       iCGMLevel,
                                           const ManualVersioningData_Flag * iFlag);


protected:

  // Protected constructor
  ManualVersioningStore(); // protected constuctor - only access via singleton get-method

  // Internal methods
  const ManualVersioningData_Flag* AddManualFlag_Int(const short              iFlagLevel,
                                                                            const CATUnicodeString & iFlagName);

  CATBoolean IsVersioningFlagActive_Int(const short                       iCGMLevel,
                                        const ManualVersioningData_Flag * iFlag) const;

  void ReadEnvFlags();

  // Internal data
  static ManualVersioningStore* _TheManualVersioningStore;

  std::vector<ManualVersioningData_Flag*> _CacheFlags;

  CATBoolean _ProcessedEnvFlags;
  std::vector<ManualVersioningData_Env*>  _CacheEnv;
};

INLINE CATBoolean ManualVersioningStore::IsVersioningFlagActive(const short iCGMLevel, const short iFlagLevel)
{
  return (iCGMLevel >= iFlagLevel);
}

INLINE short ManualVersioningData_Env::GetLevel() const { return _FlagLevel; }
#endif // MATH_CPP11
#endif // CATMathLocalVersioning_h
