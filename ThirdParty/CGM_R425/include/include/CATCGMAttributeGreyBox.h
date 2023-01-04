/* -*-c++-*- */
#ifndef CATCGMAttributeGreyBox_H
#define CATCGMAttributeGreyBox_H

#include "YP0LOGRP.h"  
#include "CATCGMStream.h"
#include "CATCGMStreamControl.h"
#include "CATCGMOutput.h" 
#include "CATCGMNewArray.h"
#include "CATDataType.h"


extern const char CATCGMAttributeGreyBox_Head_2012March[]; 

class CATCGMAttributeGreyBox  
{

public:
  CATCGMAttributeGreyBox();
  ~CATCGMAttributeGreyBox();

  void Stream(CATCGMStream &);
  void UnStream(CATCGMStream &);

  void SetGreyBoxStrControl(CATCGMStreamControl& iStrControl);
  CATCGMStreamControl& GetGreyBoxStrControl();

	CATBoolean VerifyVersionDefinition();

private:

  CATCGMStreamControl _GBStrControl;
	char *              _VersionString;

};



#endif
