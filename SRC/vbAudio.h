/*!
	@file ne_audio.h

	@copyright Nazionale Elettronica
	
	@brief Funzioni per la gestione delle risorse audio (libreria di interfaccia con openAL)
*/
#ifndef NE_AUDIO_H
#define NE_AUDIO_H

#include "AL/al.h"
#include "AL/alc.h"

#include "basetypes.h"

//! @def MAX_GAIN
//! @brief Massimo valore del gain
#define MAX_GAIN 100

//! @def NEA_FORMAT_STEREO16
//! @brief Valore del formato stereo 16
#define NEA_FORMAT_STEREO16    0x1103

//! @def MAX_SOURCES
//! @brief Massimo numero di sorgenti audio
#define MAX_SOURCES 15

//! @def NUM_BUFFERS
//! @brief Numero di buffer audio
#define NUM_BUFFERS 100

//! @def DEFAULT_GAIN
//! @brief Valore di default del gain
#define DEFAULT_GAIN 1.0f

//! @def NUM_MAX_AUDIO_RESOURCES_SET
//! @brief Massimo numero di tipi di risorse audio
#define NUM_MAX_AUDIO_RESOURCES_SET 2
//! @def COMMON_AUDIO_RESOURCE_SET_ID
//! @brief Indice per le risorse comuni a tutti i giochi
#define COMMON_AUDIO_RESOURCE_SET_ID 0
//! @def GAME_AUDIO_RESOURCE_SET_ID
//! @brief Indice per le risorse specifiche di gioco
#define GAME_AUDIO_RESOURCE_SET_ID 1
//! @def ALL_AUDIO_RESOURCE_SET_ID
//! @brief Indice per entrambe le risorse 
#define ALL_AUDIO_RESOURCE_SET_ID 2
//! @def LOOP_NOSTOP
//! @brief Indica se il suono deve essere eseguito in loop senza interruzioni
#define LOOP_NOSTOP 0x02
//! @struct TYPE_SOUND_SEQUENCES
//! @brief Rappresenta una lista di risorse audio
typedef struct
{
	WORD *sounds;	//!< Array di risorse audio
	WORD length;	//!< Numero di elementi dell'array
}TYPE_SOUND_SEQUENCES;

//! @brief informazioni sui file audio caricati
struct AUDIO_RESOURCE_DESCRIPTION
{
	DWORD byte_dimension;		//!< dimensione in byte del file
#ifdef EMSCRIPTEN
	char filename[MAX_PATH];	//!< nome del file audio, senza estensione
#endif
};

#ifdef EMSCRIPTEN
#define AUDIO_DESCRIPTION_LOADER(size, filename) {size, filename}	//!< macro di costruzione della struttura AUDIO_RESOURCE_DESCRIPTION
#else
#define AUDIO_DESCRIPTION_LOADER(size, filename) {size}				//!< macro di costruzione della struttura AUDIO_RESOURCE_DESCRIPTION
#endif

//! @struct SOUND_TYPE_SOURCE_STATE
//! @brief Rappresenta lo stato di una sorgente audio
typedef struct
{
	int last_play;			//!< Indice dell'ultima risorsa in esecuzione nella sorgente
	unsigned char state;	//!< Stato della sorgente: 0<=>STOPPED, 1<=>PLAYING, 2<=>PAUSED
	unsigned char looping;	//!< Se deve ripetere l'esecuzione della risorsa
	WORD fade;				//!< Se il suono deve essere eseguito con fade
	BYTE volume;			//!< Volume del suono
	WORD resourceID;		//!< id di appartenenza delle varie risorse
	WORD timeLen;			//!< Durata del suono
	WORD timer;				//!< Timer specifico per l'esecuzione della risorsa audio
}SOUND_TYPE_SOURCE_STATE;

//! @struct TYPE_AUDIO_DEVICE
//! @brief Rappresenta il device audio
typedef struct
{
	ALCcontext *Context;										//!< Puntatore al contesto
	ALCdevice *Device;											//!< Puntatore al device
	ALuint source[MAX_SOURCES];									//!< Array delle sorgenti
	SOUND_TYPE_SOURCE_STATE Sources_State[MAX_SOURCES];			//!< Array degli stati delle sorgenti
	bool Disabled;												//!< Controllo per abilitarlo o meno
	WORD source_idx;											//!< Indice dell'ultima sorgente utilizzata
	WORD volume;												//!< Volume del gioco
}TYPE_AUDIO_DEVICE;

//! @struct SOUNDS
//! @brief Rappresenta le risorse audio caricate
typedef struct
{
	ALuint Buffers[NUM_MAX_AUDIO_RESOURCES_SET][NUM_BUFFERS];	//!< Array dei buffer contenenti le risorse
	ALsizei num_sounds[NUM_MAX_AUDIO_RESOURCES_SET];			//!< Numero totale di risorse caricabili
	int cur_length[NUM_MAX_AUDIO_RESOURCES_SET];				//!< Numero di risorse caricate per ogni tipo
	ALuint* pBuffers;											//!< Puntatore ai buffer di risorse attivi
}SOUNDS;

extern SOUNDS Sounds;
extern TYPE_AUDIO_DEVICE Audio_Device;

int AU_Init(char *file_path, void *dev, WORD num_total_sound, AUDIO_RESOURCE_DESCRIPTION * S_Res_Desc, unsigned short resID);
int NEA_Init(void *adev, unsigned short resID);
int NEA_LoadSound(void* data, unsigned long size,  float freq , int format, unsigned short resID);

void NEA_PauseSound(unsigned short sound_id, WORD fade, WORD time);
int NEA_Play(WORD pos, DWORD loops=0, DWORD volume=0);
int NEA_PlayFade(WORD pos, DWORD loops, DWORD volume, WORD time);
int NEA_Common_Play(WORD pos, DWORD loops=0, DWORD volume=0);
void NEA_Stop(WORD pos, BYTE resourceID=ALL_AUDIO_RESOURCE_SET_ID);
void NEA_setVolume(BYTE level);

void NEA_StopFade(WORD pos, WORD time);
void NEA_PollSound();
void NEA_StopAll();
BOOL NEA_IsPlaying(unsigned short sound_id, BYTE resourceID=ALL_AUDIO_RESOURCE_SET_ID);
void NEA_Kill(unsigned short resID);
BOOL NEA_setSoundVolume(unsigned short sound_id, DWORD volume);

void NEA_Disable();
void NEA_Enable();

void NEA_SetCommonResources(SOUNDS *resources);

#endif
