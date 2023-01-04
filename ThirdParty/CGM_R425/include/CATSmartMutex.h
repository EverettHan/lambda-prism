#ifndef CATSmartMutex_h
#define CATSmartMutex_h

// COPYRIGHT DASSAULT SYSTEMES 2004

#include "CATConstantsForThreads.h"
#include "CATMutex.h"

/**
 * Class used to avoid a thread block when doing several Lock on the same CATMutex 
 * in the same thread.
 */
class ExportedByJS0MT CATSmartMutex : public CATMutex {

	public:
	
		/**
		 * Constructor
		 */
		CATSmartMutex(int iLazyCreation = 0);
		
		/**
		 * Destructor
		 */
		~CATSmartMutex();
		
	private:

		/**
		 * Copy Constructor.
		 */
		CATSmartMutex(const CATSmartMutex&);

};

#endif // CATSmartMutex_h

