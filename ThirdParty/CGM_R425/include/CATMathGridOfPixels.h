#ifndef CATMathGridOfPixels_h
#define CATMathGridOfPixels_h

#include "MathGeo.h"
#include "CATDataType.h"

// COPYRIGHT DASSAULT SYSTEMES  2001
/**
 * Class representing a rectangular mathematical Grid of Pixels.
 * The Size is (NbPixelX x NbPixelY). A Pixel is just a CATLONG32 
 * greater than 0.
 *
 * Useful for AreaFill operation (Drafting) 07/02/2002
 */
class CATMathArrayOfIntegers;

class ExportedByMathGeo CATMathGridOfPixels {
  public:
//----------------------------------------------------------  
//- Constructors
//----------------------------------------------------------
/** 
 * Constructs an empty grid
 */ 
    CATMathGridOfPixels ();
/** 
 * Constructs a grid with iNbPixelX * iNbPixelY with value 0.
 */ 
    CATMathGridOfPixels (CATLONG32 iNbPixelX, CATLONG32 iNbPixelY);
 /**
 * Copy constructor.
 */
    CATMathGridOfPixels (const CATMathGridOfPixels & iGridToCopy);

//----------------------------------------------------------  
//  Destructor  
//----------------------------------------------------------  
    ~CATMathGridOfPixels ();

//----------------------------------------------------------  
//- Get/Set
//----------------------------------------------------------
/**
 * Get back the bounds in X and Y of the grid
 */ 
    void GetSize (CATLONG32 & oNbPixelX, CATLONG32 & oNbPixelY) const;
/**
 * Set a given Pixel 0<=iX<oNbPixelX, 0<=iY<oNbPixelY to iVal>=0
 */ 
    void SetPixel (CATLONG32 iX, CATLONG32 iY, CATLONG32 iVal);
/**
 * Set all Pixels (X, Y) with iXStart<=X<=iXEnd and Y=iY to iVal>=0
 */ 
    void SetRowOfPixels (CATLONG32 iXStart, CATLONG32 iXEnd, CATLONG32 iY, CATLONG32 iVal);
/**
 * Get the value of a given Pixel 0<=iX<oNbPixelX, 0<=iY<oNbPixelY
 */ 
    CATLONG32 GetPixel (CATLONG32 iX, CATLONG32 iY) const;
/**
 * Get the value of an empty pixel
 */ 
    CATLONG32 GetEmptyValue () const;
 /**
 * Get the value of an flooded pixel
 */ 
    CATLONG32 GetFloodValue () const;
 /**
 * Get the value of the active zone pixel
 */
    CATLONG32 GetActiveZoneValue () const;
/**
 * Do not use
 */ 
    CATLONG32 * GetGrid () const { return _Grid; }
/**
 * Map the grid of Pixels to a rectangular window of the form
 *  [iXMin, iXMax] x [iYMin, iYMax] 
 */ 
    void SetWindow (double iXMin, double iXMax, double iYMin, double iYMax);

//----------------------------------------------------------  
//- Drawing utilities
//----------------------------------------------------------
/**
 * Convert the point (iX, iY) inside the window [iXMin, iXMax] x [iYMin, iYMax] 
 * in pixels.
 */ 
    void ConvertToPixel (double iX, double iY, CATLONG32 & oX, CATLONG32 & oY) const;
 /**
 * Convert the point in pixel (iX, iY) to its position in [iXMin, iXMax] x [iYMin, iYMax] 
 * in pixels.
 */ 
    void ConvertToModel (CATLONG32 iX, CATLONG32 iY, double & oX, double & oY) const;
/**
 * Convert the length iL into the length oL in pixels. 
 */ 
    void ConvertToPixel (double iL, CATLONG32 & oL) const;
/**
 * Draw a line starting from (iX1, iY1) to (iX2, iY2).
 * It sets the good pixels of the grid to iVal>=0.
 */ 
    void DrawLine (CATLONG32 iX1, CATLONG32 iY1, CATLONG32 iX2, CATLONG32 iY2, CATLONG32 iVal);
 /**
 * Draw a polyline starting from (iX[0], iY[0]) with iNbPoint.
 * It sets the good pixels of the grid to iVal>=0.
 */ 
    void DrawPolyLine (CATLONG32 *iX, CATLONG32 *iY, CATLONG32 iNbPoint, CATLONG32 iVal);
 /**
 * Draw a complete circle with center (iX, iY) and radius iR.
 * It sets the good pixels of the grid to iVal>=0.
 */ 
   void DrawCircle (CATLONG32 iX, CATLONG32 iY, CATLONG32 iR, CATLONG32 iVal);
 /**
 * Draw an arc of circle with center (iX, iY) and radius iR.
 * The arc extremities are (iX1, iY1) and (iX2, iY2). (iXm, iYm)
 * is a point inside the arc used to chose the right portion.
 * It sets the good pixels of the grid to iVal>=0.
 */ 
   void DrawArc (CATLONG32 iX, CATLONG32 iY, CATLONG32 iR, 
                 CATLONG32 iX1, CATLONG32 iY1, CATLONG32 iX2, CATLONG32 iY2,
                 CATLONG32 iXm, CATLONG32 iYm, CATLONG32 iVal);
 /**
 * Flood fill algorithm starting from point (iX, iY).
 * The mode defines how to fill the enclosed area:
 *   FillEmpty = the default behavior; it fills empty zone by the flood
 *   DefineActive = defines the active zone
 *   FillActive = fills only active zone by the flood (should be called after a DefineActive call)
 */
	 enum FloodMode {FillEmpty, DefineActive, FillActive};
   void FloodFill (CATLONG32 iX, CATLONG32 iY, FloodMode iMode=FillEmpty); 

 
 /**
 * The flood is stopped by a non nul value of the grid. This
 * method sets to 1 the input array ioFlagVal of size the max number of
 * values (0 otherwise).
 */ 
   void GetFloodFillBoundary (CATLONG32 iNbVal, short *ioFlagVal);
/**
 * Get the pixel coordinates of the corners of the flooded zone
 */
	  void GetFloodZoneCorners (CATLONG32 & oNbVal, CATLONG32 *&oX, CATLONG32 *&oY,
			CATLONG32 & oNbDomain, CATLONG32 *&oIndexDomainBounds);
/**
 * This undo the FloodFill and reset the grid in the state
 * before this action.
 */ 
   void UndoFloodFill ();
/*
 * Boundary detection:
 *  Find the closed polyline (oX, oY) which contains the area defined by the 
 *  value iVal. iConnection is 4 or 8 according to the boundary-track strategy.
 */
	 CATLONG32 GetValueBoundary (CATLONG32 iVal, CATLONG32 iConnection, CATLONG32 &oNbPoints, CATLONG32 *&oX, CATLONG32 *&oY);
 
//----------------------------------------------------------  
//- Dump the grid : for debug purposes
//----------------------------------------------------------
/**
 * Dump the values of the grid. 
 *  iOption=0 : Dump the grid on Maple files
 *  iOption=1 : Dump the grid on the console
 */ 
    void Dump (CATLONG32 iOption=0);

  private:
//----------------------------------------------------------  
//- Datas
//----------------------------------------------------------
    CATLONG32 _Nx, _Ny, _SizeGrid, *_Grid;
    double _XMin, _XMax, _YMin, _YMax;
    CATLONG32 _Flood, _Empty, _FloodActive;
	  CATMathArrayOfIntegers **_Tab;
    CATLONG32 _IndexTab, _SizeTab;
		CATLONG32 * _Stack;
		CATLONG32 _StartStack, _End;

//----------------------------------------------------------  
//- Methods
//----------------------------------------------------------
   	void Initialize ();
    CATLONG32 Adress (CATLONG32 iX, CATLONG32 iY) const;
    void UpdateSizeTab ();
		CATLONG32 AreConnected (CATLONG32 iX1, CATLONG32 iY1, CATLONG32 iX2, CATLONG32 iY2);
		CATLONG32 IsOnBoundary (CATLONG32 iX, CATLONG32 iY, CATLONG32 idX, CATLONG32 idY, CATLONG32 iVal);
		CATLONG32 IsCrossing (CATLONG32 iX1, CATLONG32 iY1, CATLONG32 iX2, CATLONG32 iY2, CATLONG32 iVal); 
		CATLONG32 FindBoundaryPoint (CATLONG32 iVal, CATLONG32 &oX, CATLONG32 &oY, CATLONG32 &odX, CATLONG32 &odY);

 /* kjd 26Febr 2008 : RI607592
 * In general, test if 2 values are equal.
 * In case of 1 or 2  multipoints, test if we can find  a similar value in the lists.
*/
 CATLONG32 AreEqual(CATLONG32 iVal1, CATLONG32 iVal2);

/* kjd 26Febr 2008 : RI607592
* This method takes into account the free diagonal points. 
* These points are added to the studied point list if they don't imply a curve crossing.
*  YES :  * 6     NO : * 6        with  * free points 
*         5 *          6 *              6 curve number 6 for instance
* It makes less strict the recursion condition used in FloodFill method.
*/
   void DiagonalFloodFill (CATLONG32 iS, CATLONG32 iE, CATLONG32 iY, CATLONG32 iColFree);

		void ResetStack();
		void NewStack();
		void FreeStack();
		void PopStack();
		void PushStack(CATLONG32 iX,CATLONG32 iY);
		CATLONG32 SizeStack();
};

#endif
