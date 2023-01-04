// COPYRIGHT DASSAULT SYSTEMES 2013
#ifndef OpIGraph_HPP
#define OpIGraph_HPP
/* 
*  Ligth Interfaces (For scalable and simple generic purpose)
*
*   For ZERO FootPrint (excluding live infrastructure prerequisite such as Fw System !! )
*      -> a kind of design ready for Fw SpecialAPI embedded :-)
*
*   and on demand Monitoring (some similary with V5PCSToolsPrivate )
*       but for more oriented for explicit applied domains indicators 
*       (rather than external Operating System capacity and scalability indicators) 
*/
#include "CATOpDataItf.hpp"

/* -*-c++-for common purpose - */
#if ! defined ( INLINE ) 
#if defined(_WINDOWS_SOURCE) && defined(_MSC_VER) && _MSC_VER>1300
#define  INLINE     __forceinline
#else
#define  INLINE     inline
#endif
#endif


#define CATOpDataItfCommon(Interface) \
  private: \
      unsigned int _Counter; \
      Interface (const Interface &); \
      Interface& operator=(const Interface&);  \
   protected : \
      INLINE Interface()  : _Counter(1) {}   \
      INLINE ~Interface()   { _Counter=0; } \
  public: \
    INLINE unsigned int AddRef()  \
       { return ++_Counter; }    \
    INLINE unsigned int Release() \
    { \
       if ( _Counter <= 0  )  OpDataInterfaces::OpIError::Signal(66); \
       unsigned int  result = --_Counter; \
       if ( 0 == result ) \
         delete this; \
       return result; \
    } \
  public: \


namespace OpDataInterfaces
{
  class OpIError;

  class OpIFactory;
 
  class OpINode;

  class OpIGraph;
  class OpIArc;
  class OpINode;

  class OpINodesIterator;
  class OpINodeNeighbours;
  
  
  
  
  //------------------------------------------------------------------------
  // OpIError (signaling error management)
  //------------------------------------------------------------------------
  class  ExportedByCATOpDataItf OpIError  
  {
  public:
    /**
    * Signal 
    */
    static void Signal(unsigned int iIndex);

  private:
    OpIError (const OpIError &);          
    OpIError& operator=(const OpIError&);  
  };







  //------------------------------------------------------------------------
  // OpIFactory : getting initial root elements  
  //------------------------------------------------------------------------
  class  ExportedByCATOpDataItf OpIFactory   
  {
    CATOpDataItfCommon(OpIFactory)

    /**
    * Reader : origin or request
    */
    virtual OpIGraph * CreateGraph()  = 0;
 
  };

  

  //------------------------------------------------------------------------
  // OpIKey   
  //------------------------------------------------------------------------
  class  ExportedByCATOpDataItf OpIKey  
  {
    CATOpDataItfCommon(OpIKey)
 
   /**
    * Comparison 
    */
    virtual void IsEqual(OpIKey *iKey) const = 0;

   /**
    * For hash tables  
    */
    virtual unsigned int ComputeHashKey() const = 0;

  };



  //------------------------------------------------------------------------
  // OpIGraph   
  //------------------------------------------------------------------------
  class  ExportedByCATOpDataItf OpIGraph  
  {
    CATOpDataItfCommon(OpIGraph)

    /**
    * Reader :  (? with filtered or indexed properties) 
    */
    virtual OpINodesIterator * CreateNodesIterator() = 0;

    /**
    * Writer : Factory of elementary structure : OpIArc 
    */
    virtual OpINode * CreateNode() = 0;

    virtual OpIArc  * CreateArc(OpINode *iStart, OpINode * iEnd) = 0;


    /**
    * LifeCycle management
    */
    virtual void Empty() = 0;
  };




  //------------------------------------------------------------------------
  // OpINode  
  //------------------------------------------------------------------------
  class  ExportedByCATOpDataItf OpINode
  {
     CATOpDataItfCommon(OpINode)

   /**
    * Reader : neighborhood management  
    */
    virtual OpINodeNeighbours * Successors() const = 0;

   /**
    * Reader : neighborhood management  
    */
    virtual OpINodeNeighbours * Predecessors() const = 0;

  };

  
  //------------------------------------------------------------------------
  // OpIArc   
  //------------------------------------------------------------------------
  class  ExportedByCATOpDataItf OpIArc 
  {
     CATOpDataItfCommon(OpIArc)

   /**
    * Reader : neighborhood management  
    */
    virtual void GetNodes(OpINode *& iStart, OpINode * & iEnd) = 0; 
  };

   




 //------------------------------------------------------------------------
  // OpINodeNeighbours (specialised Iterator)
  //------------------------------------------------------------------------
  class  ExportedByCATOpDataItf OpINodeNeighbours 
  {
     CATOpDataItfCommon(OpINodeNeighbours)

    /**
    * Reader : origin or request
    */
    virtual OpINode * GetContext() const = 0;

    /**
    * Writer : Factory of elementary structure : OpIArc 
    */
    virtual OpINode * NextNode(OpINode *iPrevious) = 0;

    /**
    * NextArc 
    */
    virtual OpIArc  * NextArc(OpIArc *iPrevious) = 0;
 
  };

  //------------------------------------------------------------------------
  // OpINodesIterator   (or array)
  //------------------------------------------------------------------------
  class  ExportedByCATOpDataItf OpINodesIterator 
  {
    CATOpDataItfCommon(OpINodesIterator)

   /**
    * Scan (0 as input value to begin, 0 as output value for end of iteration)  
    */
    virtual OpINode * Next(OpINode *iPrevious)  = 0;
 
  };





} ;


 
#endif
