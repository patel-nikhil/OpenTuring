/*************/
/* miofont.h */
/*************/

#ifndef _MIOHASHMAP_H_
#define _MIOHASHMAP_H_

/*******************/
/* System includes */
/*******************/

/******************/
/* Other includes */
/******************/
#include "miotypes.h"

/**********/
/* Macros */
/**********/

/*************/
/* Constants */
/*************/

/*********/
/* Types */
/*********/

/**********************/
/* External variables */
/**********************/

/*********************************************/
/* External procedures for Turing predefines */
/*********************************************/
extern OOTint MIOHashmap_New (SRCPOS *pmSrcPos);
extern void	MIOHashmap_Free (OOTint pmFontID);

extern void	MIOHashmap_Put (OOTint pmMapID, OOTstring key,OOTint value);
extern void	MIOHashmap_PutReal(OOTint pmMapID, OOTstring key, OOTreal value);
extern void	MIOHashmap_PutString(OOTint pmMapID, OOTstring key, OOTstring value);
extern OOTint	MIOHashmap_Get (OOTint pmMapID, OOTstring key, OOTint *result);
extern OOTint	MIOHashmap_GetReal(OOTint pmMapID, OOTstring key, OOTreal *result);
extern OOTint	MIOHashmap_GetString(OOTint pmMapID, OOTstring key, char** result);
extern void	MIOHashmap_Remove (OOTint pmMapID, OOTstring key);

/***************************************/
/* External procedures for MIO library */
/***************************************/

#endif // #ifndef _MIOHASHMAP_H_
