/* -*-C++-*- */

#ifndef CATCGMOutputColor_H
#define CATCGMOutputColor_H

#include "ExportedByCATMathStream.h"

//--------------------------------------------------------------------------
// List of macro using color
//--------------------------------------------------------------------------

/** @brief To display text with standard color. */
#define cgmout_std      CATCGMOutputColor::SetTextColor(7)
/** @brief To display text in green. */
#define cgmout_green    CATCGMOutputColor::SetTextColor(10)
/** @brief To display text in blue. */
#define cgmout_blue     CATCGMOutputColor::SetTextColor(11)
/** @brief To display text in red. */
#define cgmout_red      CATCGMOutputColor::SetTextColor(12)
/** @brief To display text in pink. */
#define cgmout_pink     CATCGMOutputColor::SetTextColor(13)
/** @brief To display text in yellow. */
#define cgmout_yellow   CATCGMOutputColor::SetTextColor(14)
/** @brief To display text with red background. */
#define cgmout_bg_red   CATCGMOutputColor::SetTextColor(15,12)

//--------------------------------------------------------------------------
// List of macro using the graphic charter
//--------------------------------------------------------------------------

/** @brief To display text as step of algorithm, in blue. */
#define cgmout_step     CATCGMOutputColor::SetTextColor(11)
/** @brief To display text as succeeded step, in green. */
#define cgmout_S_OK     CATCGMOutputColor::SetTextColor(10)
/** @brief To display text as failed step, in red. */
#define cgmout_E_FAIL   CATCGMOutputColor::SetTextColor(12)
/** @brief To display text as error, with red background. */
#define cgmout_error    CATCGMOutputColor::SetTextColor(15,12)

/**
 @brief Display color in the console.
 @author Laurent Marini
 @date May 2017
 
 Class defining macros that change the color of text.<br>

 <H3>Graphic Charter</H3>
 <ul>
 <li> blue   : Step of the Algorithm.
 <li> yellow : Important Logical Data.
 <li> pink   : Important Numerical Data.
 <li> green  : Succeeded Internal Result.
 <li> red    : Failed Internal Result.
 <li> bg_red : High Severity Error Message. (bg for background)
 </ul>

 <H3>List of macros by color</H3>
 <ul>
 <li> cgmout_std;
 <li> cgmout_green;
 <li> cgmout_blue;
 <li> cgmout_red;
 <li> cgmout_pink;
 <li> cgmout_yellow;
 <li> cgmout_bg_red; (bg for background)
 </ul>

 <H3>List of macros by the graphic charter</H3>
 <ul>
 <li> cgmout_std;
 <li> cgmout_step;
 <li> cgmout_S_OK;
 <li> cgmout_E_FAIL;
 <li> cgmout_error;
 </ul>
 
 <H3>4 Samples of code</H3>
 @code{.cpp}
#include "CATCGMOutputColor.h"
#include "CATCGMOutput.h"

// Sample.1 : Display color with macros using color
cgmout_green;
cgmout << "cgmout_green;   - To display green text" << cgmendl;
cgmout_blue;
cgmout << "cgmout_blue;    - To display blue text" << cgmendl;
cgmout_red;
cgmout << "cgmout_red;     - To display red text" << cgmendl;
cgmout_pink;
cgmout << "cgmout_pink;    - To display pink text" << cgmendl;
cgmout_yellow;
cgmout << "cgmout_yellow;  - To display yellow text" << cgmendl;
cgmout_bg_red;
cgmout << "cgmout_bg_red;  - To display red background" << cgmendl;
cgmout_std;
cgmout << "cgmout_std;     - To return to the standard display" << cgmendl;

// Sample.2  : Display color with macros using color
// It's possible to set the color in the same line than cgmout.
cgmout << cgmout_green << "cgmout_green;   - To display green text in same line than cgmout" << cgmendl;
cgmout << cgmout_std << "cgmout_std;     - To return to the standard display in same line than cgmout" << cgmendl;

// Sample.3  : Display color with macros using color
// But for one cgmout, you can use only one color.
// If you set several colors for same cgmout, only the first color will be set.
// To have N colors in one line you have to code N cgmout;
cgmout << cgmout_green << "green"; 
cgmout << cgmout_blue << "- blue"; 
cgmout << cgmout_red << "- red"; 
cgmout << cgmout_pink << "- pink"; 
cgmout << cgmout_yellow << "- yellow"; 
cgmout << cgmout_std << "- standard";

// Sample.4  : Display color with macros using graphic charter
cgmout << "Graphic Chart" << cgmendl;
cgmout << "-------------" << cgmendl;
cgmout << cgmout_step << "-- Step1 of the Algorithm --------------------------"<< cgmendl;;
cgmout << cgmout_std << " _LogicalData1   = ";
cgmout << cgmout_yellow << "Type3" << cgmendl;
cgmout << cgmout_std << " _NumericalData1 = ";
cgmout << cgmout_pink << 5.37 << cgmendl;
cgmout << cgmout_std << " _LogicalData2   = ";
cgmout << cgmout_yellow << "TRUE " << cgmendl;
cgmout << cgmout_std << " Run Step1 : ";
cgmout << cgmout_S_OK << "Ok " << cgmendl;
cgmout << cgmout_step << "-- Step2 of the Algorithm --------------------------"<< cgmendl;; 
cgmout << cgmout_std << " ... " << cgmendl;
cgmout << cgmout_E_FAIL << " Internal Error Type 7456 " << cgmendl;
cgmout << cgmout_std << " ... " << cgmendl;
cgmout << cgmout_std << " Run Step2 : ";
cgmout << cgmout_E_FAIL << "Ko " << cgmendl;
cgmout << cgmout_step << "-- Step3 of the Algorithm --------------------------"<< cgmendl;;
cgmout << cgmout_std << " ... " << cgmendl;
cgmout << cgmout_error << " High Severity Error on Body tag4881" << cgmendl;
cgmout << cgmout_std << " ... " << cgmendl;
cgmout << cgmout_std << " Run Step3 : ";
cgmout << cgmout_E_FAIL << "Ko " << cgmendl;
cgmout_std;  // Return to the standard display
@endcode
*/

class  CATCGMOutputColor
{
public:
 /**
  * @brief To change the text color in console<br>
  * 0 - Black<br>    
  * 1 - Blue<br>       
  * 2 - Green<br>     
  * 3 - Aqua<br>     
  * 4 - Red<br>   
  * 5 - Purple<br>    
  * 6 - Yellow<br> 
  * 7 - White<br>
  * 8  - Gray<br>
  * 9  - Light Blue<br>
  * 10 - Light Green<br>
  * 11 - Light Aqua<br>
  * 12 - Light Red<br>
  * 13 - Light Purple<br>
  * 14 - Light Yellow<br>
  * 15 - Bright White<br> 
  * @param iTextColor<br>
  * @param iBackgroundColor<br>
  **/
  ExportedByCATMathStream static const char*  SetTextColor(int iTextColor,int iBackgroundColor=0);
};

#endif
