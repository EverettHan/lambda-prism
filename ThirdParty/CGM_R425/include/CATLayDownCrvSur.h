#ifndef CATLayDownCrvSur_H
#define CATLayDownCrvSur_H

// COPYRIGHT DASSAULT SYSTEMES  2000

#include "Y30E3PMG.h"
#include "CATGeoOperator.h"
#include "CATMathDef.h"
#include "CATString.h"
#include "CreateLayDownCrvSur.h"
#include "CATCreateLayDownCrvSur.h"


class CATListOfCATCurves;
class CATMultiSurface;
class CATPCurve;
class CATSurface;
class CATCrvLimits;
/**
* @nodoc
* Classe permettant le posage d'une liste de Curves sur un reseau de surfaces.
*
* Ce service est generalement utilise dans le contexte des echanges de donnees ( Interfaces standard IGES,STEP,... ou	
* interfaces directs). On part generalement d'une courbe 3D et d'une surface, et l'on cherche a obtenir la	
* representation de la courbe 3D dans l'espace parametrique de la surface. Du fait des contraintes de continuites
* C2 inherentes au modeleur V5, la courbe 3D initiale et la surface peuvent potentiellement etre decoupees
* en sous-elements. L'interface du service de posage suppose que cette decoupe a ete prealablement realisee.
* A partir des listes des courbes et surfaces obtenues a l'issue de la decoupe, le service de posage produit
* une nouvelle liste de courbes dans l'espace parametrique des differentes surfaces. Chacune des courbes fournies
* doit donner lieu a une suite de courbes posees sur le reseau de surface et une seule, le posage se fait pour
* chacun des points de la courbe 3D par recherche du point le plus proche sur la surface, cette methode
* permet d'absorber les eventuelles imprecisions au bord des differentes surfaces. De plus, a partir des imprecisions
* detectees sur la forme 3D, l'operateur produira la forme parametrique la plus compacte moyennant des approximations
* equivalentes a l'imprecision.
* 
*
*/
class ExportedByY30E3PMG CATLayDownCrvSur : public CATGeoOperator
{
  CATCGMVirtualDeclareClass(CATLayDownCrvSur);
public:
/**
* @nodoc
* Use the <tt>CreateLayDownCrvSur</tt> global method.
*
*     ListOfCurves    : Liste des courbes 3D obtenues par la decoupe de la courbe 3D initiale. Cette
*                       liste est telle que 2 courbes consecutives sont connexes, que les sens de parcours
*                       naturels (selon le parametrage) sont compatibles, que les limites courantes de chacune
*                       des courbes correspondent a la partie utile (a revoir)
*
*     ListOfSurfaces  : Liste des surfaces. Les surfaces sont supposees rangees dans la liste de maniere a
*                       former une matrice NU * NV. Deux paves contigus de la matrice sont supposes continus
*                       G0 (au sens du modeleur emetteur), les limites courantes de chaque surface correspondnt a la
*                       partie utile (a revoir).
*
*/
  
  CATLayDownCrvSur(CATGeoFactory * iFactory);
  
  /**
  * @nodoc
  * Destructor.
  */
  virtual ~CATLayDownCrvSur();
  
  /**
  * @nodoc
  */
  virtual void SetLaydownDistance(double iDistance)=0; 

  /**
  * @nodoc
  * Allows Expansion of MultiSurface Domain to the max limits of the surfaces
  * when set to TRUE
  * By default option is not set (set to FALSE)
  * Today only active in case of  multi-surface made of a single non closed Nurbs
  * in the U or V direction, ie : 
  * one single Nurbs in V => we extend domain to max limits in V
  * one single nurbs in U => we extend domain to max limits in U
  */
  virtual void SetExpandDomainMode(CATBoolean iMode)=0;

  /**
  * @nodoc
  * Activates detection of invariant Input
  * 
  * When this mode is set :
  *  if all input Curves are EdgeCurves and if each of them is containing one PCurve whose support is member of input MultiSurface the Run does nothing!
  *  The input list of curve is seen as invariant (already on Multisurface) and NextCurve will return FALSE 
  *  (input list is solution, there is no need to recreate new curves) 
  * To know wether input Curves are seen as invariant call method IsInputCurveListInvariant after Run 
  * 
  * When this mode is not set :
  *   a laydown is performed in any case, if there are solutions new curves are created
  * 
  */
  virtual void SetKeepInvariantInputCurveMode(CATBoolean iMode)=0;

  /**
  * @nodoc
  * return TRUE 
  *   -after Run 
  *   -if KeepInvariantInputCurveMode is Set to TRUE (see SetKeepInvariantInputCurveMode)
  *   and 
  *   -if InputCurves are invariant (all Curves are containing a PCurve defined on one memebr of multisurface)
  * return FALSE elsewhere 
  */
  virtual CATBoolean IsInputCurveListInvariant()=0;

  /**
  * @nodoc
  * Initializes the iterator of the solution curves of <tt>this</tt> 
  * CATLayDownCrvSur operator.
  *<br>By default, the initialization is performed once the operator runs, 
  * and this is therefore only used to read the solutions again.
  */
  virtual void BeginningCurve()=0;
  
  /**
  * @nodoc
  * Skips to the next solution curve of <tt>this</tt> CATLayDownCrvSur operator.
  *<br>After <tt>BeginningCurve</tt>, it skips to the first curve. 
  * @return
  * The existence of the next solution.
  * <br><b>Legal values</b>:
  *<dl><dt><tt>TRUE</tt> <dd>if there is a solution curve
  *    <dt><tt>FALSE</tt> <dd>no more solution curve.</dl>
  */
  virtual CATBoolean NextCurve()=0;
  
  /**
  * @nodoc
  * Creates the next solution curve of <tt>this</tt> CATLayDownCrvSur operator.
  * @oSupport
  * The surface of iMultiSurface on which the returned PCurve is defined
  * @return
  * The pointer to the created curve on surface. A new curve is created each time this method is called.
  * If you do not want to keep the created curve, use the @href CATICGMContainer#Remove method.
  */
  virtual CATPCurve * GetPCurve(CATSurface *& oSupport, CATCrvLimits & oLimits)=0;
  
  /**
  * @nodoc
  * The GetPCurve method returns a PCurve which is the projection of a curve from
  * the input list (iCurveList) with a given index k. 
  * The GetFromCurveIndex()  method returns this corresponding index k.
  */
  virtual CATLONG32 GetFromCurveIndex()=0;
  
  /**
  * @nodoc
  * Return the Maximum distance of the projected curves to the MultiSurface
  * (if -1 is returned a curve is not on the surface).
  */
  virtual double GetMaxDistanceFromSurface()=0;
  
  /**
  * @nodoc
  * Return the Maximum distance of the projected curves to the MultiSurface
  * (if -1 is returned a curve is not on the surface).
  */
  virtual double GetMaxDistanceFromSurface (CATLONG32 & oCurveIndex)=0;
  virtual double GetMaxDistanceFromSurface (CATLONG32 & oCurveIndex, CATLONG32 & oSurfaceIndex)=0;
  virtual double GetMaxDistanceFromSurface (CATLONG32 & oCurveIndex,  CATLONG32& oIndexU, CATLONG32 &oIndexV)=0;
  
};

#endif
