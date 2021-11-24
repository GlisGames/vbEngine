#ifndef VBIMAGE_H
#define VBIMAGE_H

#include "basetypes.h"

struct ATLAS_DATA
{
	WORD width;											//!< larghezza dell'atlas
	WORD height;										//!< altezza dell'atlas
	DWORD byte_dimension;						//!< dimensione in byte dell'atlas
	WORD atlas_index;								//!< indice interno dell'atlas
	char atlas_name[20];						//!< nome dell'atlas (nome del file senza estensione dell'atlas)
	float scaleX;										//!< zoom orizzontale da applicare alla texture (se >1.0 la texture è stata ridotta)
	float scaleY;										//!< zoom verticale da applicare alla texture (se >1.0 la texture è stata ridotta)
	BYTE colorFormat;  //!< indicazione sul formato colore della texture (le texture con i font potrebbero non essere a 32bit)
};

struct IMAGE_DATA
{
	WORD atlasID;				//!< id dell'atlas caricata come texture 
	WORD x0;					//!< coordinata x rispetto alla texture
	WORD y0;					//!< coordinata y rispetto alla texture
	int offset_x;				//!< spostamento x dovuto all' ottimizzazione della texture : taglio bordo sinistra trasparente 
	int offset_y;				//!< spostamento y dovuto all' ottimizzazione della texture : taglio bordo alto trasparente 
	WORD width;					//!< larghezza della texture nell'atlas
	WORD height;				//!< altezza della texture nell'atlas
	WORD pngWidth;				//!< larghezza originale dell'immagine
	WORD pngHeight;				//!< altezza originale dell'immagine
};

struct IMAGE_SEQUENCE
{
	WORD* images;	//!< array con le id di ciascuna immagine che compone la sequenza
	WORD length;	//!< numero di immagini nella sequenza
};

#endif