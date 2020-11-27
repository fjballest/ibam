/* --------------------------------
 *
 *    File: @(#)cnsttype.h   2.4
 *    Date: 4/22/91
 *    Module: Constants and Constructors ( cnst )
 *    Programmer: Franc. J.B. Camara
 *
 *    Comments: Supports constant and constructor 
 *              tables and methods.
 * 
 *
 * --------------------- */ 



#ifndef _CNSTTYPETYPES_
#   define _CNSTTYPETYPES_

typedef char *cnst_consNameType;

typedef cnst_consNameType *cnst_constType;
typedef cnst_consNameType *cnst_constrType;

typedef
struct cnst_constTableStruct{
    int cardinal;
    cnst_constType name;
}cnst_constTableType;

typedef
struct cnst_constrTableStruct{
    int cardinal;
    cnst_constrType name;
}cnst_constrTableType;

#endif




