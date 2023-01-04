// COPYRIGHT DASSAULT SYSTEMES 2012

#ifndef CGMVswpKeyframesCache_H
#define CGMVswpKeyframesCache_H

#include "CATBoolean.h"
#include "CATCurve.h"
class CATGeoFactory;
class VswpKeyframeDef;
class VswpKeyframesCache;

class VswpKeyframesCacheIter
{
public :
	VswpKeyframesCacheIter();
	VswpKeyframesCacheIter( VswpKeyframesCacheIter const & iKeyframesIter );
	~VswpKeyframesCacheIter();
	void Reset();
	VswpKeyframeDef* Next();
	VswpKeyframeDef* FindSpan( double iTime, CATBoolean iEvalBelow );



private :
	friend class VswpKeyframesCache;

	VswpKeyframesCacheIter( VswpKeyframesCache const* iKeyframes );

	CATBoolean WithinSpan( double iTime, CATBoolean iEvalBelow) const;

	CATBoolean _IsReset;
	VswpKeyframeDef * _CurrentFrame;
	VswpKeyframesCache const * _KeyframesCache;  // assumes lifetime of iterator is shorter
};

class VswpKeyframesCache
{
public :
	VswpKeyframesCache();
	~VswpKeyframesCache();


	int Size() const;
	void SetFrames( VswpKeyframeDef* iFrames );
    void SetInternalFactory( CATGeoFactory * ipFactory );
    CATGeoFactory* GetInternalFactory() const;
    void SetTolerance( double iTol );
	CATBoolean IsSet() const;
	//void AddFrame( VswpKeyframeDef * iFrame);  
	VswpKeyframesCacheIter GetIterator() const;
  void AddCurve(CATCurve *ipCurve) {if (!_Curves.Locate(ipCurve)) _Curves.Append(ipCurve);};
	void Cleanup();
	void CleanupInternalFactory();

private :
	friend class VswpKeyframesCacheIter;

	VswpKeyframesCache(VswpKeyframesCache const & iOther);
	VswpKeyframesCache & operator=(VswpKeyframesCache const & iOther);

	VswpKeyframeDef * _Frames;
	VswpKeyframeDef * _LastFrame;

    // Owns the factory
    CATGeoFactory* _pInternalFactory;
    double _Tol;
    CATListPV _Curves;
};




#endif 
