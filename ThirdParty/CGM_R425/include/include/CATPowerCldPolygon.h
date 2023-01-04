/* COPYRIGHT DASSAULT SYSTEMES PROVENCE 2003
 * --------------------------------------------------------
 *=========================================================
 *   PROJET:............Polygon2Surface                             
 *   FRAMEWORK:.........SurfacicGeoOperators       
 *   DATE:..............fev 2003
 *   Purpose : 
 *=========================================================
 * HISTORY:
 * 22.07.2019 : RAQ : Ajout boundary vertices services
 * fev 2003 : ktu definition
 *=========================================================
 */

#ifndef CATPowerCldPolygon_h
#define CATPowerCldPolygon_h

#include "CATBaseUnknown.h"
#include "CATGMOperatorsInterfaces.h"
#include "CATBoolean.h"

class CATMathPoint ;
class CATCldPolygon;


class ExportedByCATGMOperatorsInterfaces CATPowerCldPolygon : public CATBaseUnknown   
{
public :   
          CATPowerCldPolygon();
          virtual ~CATPowerCldPolygon();

	virtual int GetNumberOfPoints() const = 0;
	//
	virtual int SetTolerancesG0( int iIndex, double iTolG0 ) = 0;
	virtual int ToleranceG0( int iIndex, double  & oTol ) const = 0;
	//
	virtual int  GetPoint( int iIndex, CATMathPoint * oPoint ) const  = 0;
	virtual int  GetPoint( int iIndex, double & oX, double & oY, double & oZ ) const =0;
	virtual int  SetPoint( int iIndex, double  oX, double  oY, double  oZ ) = 0;
	//
	virtual int  SetIsFilterable( int iIdx, const CATBoolean iIsFilterable )= 0;
	virtual int  GetIsFilterable( int iIdx, CATBoolean & oIsFilterable  ) const = 0;
	//
	virtual int  SetIsFiltered( int iIdx, const CATBoolean  iIsFiltered ) = 0;
	virtual int  GetIsFiltered(  int iIdx, CATBoolean & oIsFiltered ) const = 0;
	//
	virtual int   SetUV( int Index, double iU, double iV )= 0;
	virtual int   GetUV( int iIndex, double & oU, double & oV, CATBoolean & oIsDefined  ) const= 0;
   
	virtual int SetIsNotFree( int Index, const CATBoolean iIsNotFree )= 0;
	virtual CATBoolean IsFree( int iIndex) const= 0;

  //Flag boundary vertices (0 <= iIndex < nb points), currently only used in P2S
#ifndef _AIX_SOURCE
  virtual int SetIsOnBoundary(const int iIndex, const CATBoolean iIsOnBoundary) = 0;
  virtual CATBoolean IsOnBoundary(const int iIndex) const = 0;
#endif  //!_AIX_SOURCE

private:
  CATPowerCldPolygon(const CATPowerCldPolygon &iObject); // Prohibited
  CATPowerCldPolygon &operator=(const CATPowerCldPolygon &iObject); // Prohibited
};
   

#endif
