#ifndef CATChamferDefine_H
#define CATChamferDefine_H

//=============================================================================
// Copyright Dassault Systemes 2006-2013, all rights reserved
//=============================================================================

// --- Jan 2013 ---
// Created by SOU

// new data definitions for BoneChamferCGM

enum CATChamferType
{
  CATChamferIsUnknown = 0,
  CATChamferIsD1D2 = 1,
  CATChamferIsD1A1 = 2,
  CATChamferIsDA1 = 3,
  CATChamferIsD1D2Approx = 4,
  CATChamferIsD1A1Approx = 5
};

#endif
