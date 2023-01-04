//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2002
//=============================================================================
// 
//	CATMathEvalRecord :
//		Classe Record pour stocker une evaluation de fonction d'1 variable,
//		ainsi eventuellement que la valeur de certaines derivees.
//
//    Pour gagner en memoire, on ne stocke pas la dimension: il faut donc la
//    redonner a chaque fois.
//
//=============================================================================
// Feb. 02     Creation                                   KLX
//=============================================================================

#ifndef	CATMathEvalRecord_h
#define	CATMathEvalRecord_h

#include "CATCGMVirtual.h"

class CATMathEvalRecord  : public CATCGMVirtual
{
public:
	int _order;
	double _param;
	double * _data;

	CATMathEvalRecord (int dim, double param, double * point, double * fder = 0, double * sder = 0);
	~CATMathEvalRecord ();

	void ReplaceData (int dim, double * point = 0, double * fder = 0, double * sder = 0);
		// Ne remplace que les donnees non NULL precisees a l'exception du parametre et met a jour
		// l'ordre si besoin.

private:
	CATMathEvalRecord();
	CATMathEvalRecord(const CATMathEvalRecord & rec);
	void operator = (const CATMathEvalRecord & rec);
};

#endif
