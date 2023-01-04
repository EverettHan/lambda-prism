#ifndef CGMVersionDebug_h
#define CGMVersionDebug_h
// COPYRIGHT DASSAULT SYSTEMES  1999
//----------------------------------------------------------------------------------------------
// Pour l'implementation de la Table de correspondance de l'affectation des Levels
//----------------------------------------------------------------------------------------------
typedef struct 
{
  const char * _VariableName;
  short        _Level;
  short        _ReferenceLevel;
}
CGMVersionCore;


typedef struct
{
  CGMVersionCore   * Tuple;
  char   * Responsable;
  char   * Date;
  char   * Comment;
}
CGMVersionDebug;

 

#endif
