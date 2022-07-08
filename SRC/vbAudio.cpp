#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "raylib.h"
#include "vbAudio.h"

#define FADE_IN	1	//!< Indica se la risorsa audio deve essere eseguita con un fade d'ingresso 
#define FADE_OUT 2	//!< Indica se la risorsa audio deve essere eseguita con un fade d'uscita
#define FADE_PAUSE 4	//!< Indica se la risorsa audio deve essere messa in pausa

//! @var Audio_Device
//! @brief Mantiene lo stato dei componenti necessari ad eseguire file audio
TYPE_AUDIO_DEVICE Audio_Device;
//! @var pAudio_Device
//! @brief Puntatore all'istanza di TYPE_AUDIO_DEVICE in uso
TYPE_AUDIO_DEVICE *pAudio_Device;
int _LoadSound(void* data, unsigned long size, float freq, int format);

//! @var Sounds
//! @brief Mantiene lo stato dei file audio caricati
SOUNDS Sounds;

int vbLoadSound(vbString path)
{
	Wave wave = LoadWave(path.c_str());

	int ret = _LoadSound(wave.data, (wave.frameCount * wave.channels * sizeof(short)), wave.sampleRate, AL_FORMAT_STEREO16);

	UnloadWave(wave);       // Sound is loaded, we can unload wave

	return ret;
}

//! @brief Ferma tutti i suoni in esecuzione e distrugge tutte le risorse allocate
//! @param [in] resID Indice relativo al tipo di risorse che si stanno distruggendo
//! @return void
void vbKillSound(unsigned short resID)
{
	short i;

	if (pAudio_Device == NULL)
		return;

	for(i=0; i<MAX_SOURCES; i++)
	{
		alSourceStop(pAudio_Device->source[i]);

		pAudio_Device->Sources_State[i].last_play=-1;
		pAudio_Device->Sources_State[i].looping=false;
		pAudio_Device->Sources_State[i].state=0;
	}

	alDeleteBuffers(NUM_BUFFERS, Sounds.Buffers[resID]);
	Sounds.num_sounds[resID] = 0;
	Sounds.cur_length[resID] = 0;
}

//! @brief Controlla se una data sorgente è in esecuzione
//! @param [in] source Sorgente da controllare
//! @return Risultato del controllo
bool _SourceIsPlaying(unsigned short source)
{
	ALenum state;

	bool clause = false;

	state=0;

	if (pAudio_Device->Sources_State[source].state !=0)
	{
		alGetSourcei((ALuint)source,AL_SOURCE_STATE,&state);

		if(state==AL_PLAYING)
			clause = true;
		else
		{
			if(pAudio_Device->Sources_State[source].looping)
				clause = true;
		}
	}

	return clause;
}
//! @brief Setta il volume del gioco
//! @param [in] level Livello a cui settare il volume
void vbSetMasterVolume(BYTE level)
{
	if(level<=MAX_GAIN)
		Audio_Device.volume = level;
	else
		Audio_Device.volume = MAX_GAIN;


#ifndef SIMULA_GIOCO
	ALenum state;
	float _gain;

	if (pAudio_Device == NULL)
		return;

	for(BYTE source=0;source<MAX_SOURCES;source++)
	{
		alGetSourcei((ALuint)pAudio_Device->source[source],AL_SOURCE_STATE,&state);
		if(state==AL_PLAYING || pAudio_Device->Sources_State[source].looping)
		{
			pAudio_Device->Sources_State[source].state=1;
			_gain=(float)pAudio_Device->Sources_State[source].volume*1.0f/100;
			_gain=(float)_gain*Audio_Device.volume/100;
			_gain=VBMIN(_gain, 1.0f);
			alSourcef(pAudio_Device->source[source], AL_GAIN, _gain);
		}
	}
#endif
}

//! @brief Inizializza il device audio con sorgenti e buffer
//! @param [in] adev Device già esistente
//! @param [in] resID Indice relativo al tipo di risorse da inizializzare
//! @return Controllo sulla presenza di errori
int vbInitSound(void *adev, unsigned short resID)
{
	int _err=0;
	unsigned short i;
	Audio_Device.volume = MAX_GAIN;
	if(Audio_Device.Device)
	{
		if(Sounds.num_sounds[resID]==0)
		{
			// inizializzazione di un tipo di suoni differente, genera si soli sound buffer
			Sounds.num_sounds[resID]=NUM_BUFFERS;
			Sounds.pBuffers=Sounds.Buffers[resID];
			//alGenBuffers(Sounds.num_sounds[resID], Sounds.pBuffers);
		}
		else
			printf("\n Sound device exists");
		return 0;
	}
	if (adev!=NULL)
	{
		pAudio_Device=(TYPE_AUDIO_DEVICE *)adev;
	}
	else
	{
		Audio_Device.source_idx=0;
		Audio_Device.Disabled=false;

		ALfloat sposition[] = { 0.f, 0.f, 0.f };
		ALfloat svelocity[] = { 0.f, 0.f, 0.f };
		ALfloat lposition[] = { 0.f, 0.f, 0.f };
		ALfloat lvelocity[] = { 0.f, 0.f, 0.f };
		ALfloat lorientation[]= { 0.f, 0.f, -1.f, 0.f, 1.f, 0.f };

		// reset buffer errori
		_err=alGetError();

		Audio_Device.Device=alcOpenDevice(alcGetString(NULL, ALC_DEVICE_SPECIFIER));
		if (Audio_Device.Device == NULL)
		{
			return -1;
		}

		// creo il context
		Audio_Device.Context=alcCreateContext(Audio_Device.Device,NULL);
		if (Audio_Device.Context == NULL)
		{
			return -2;
		}

		// reset buffer errori
		_err=alGetError();

		// imposto il context attivo
		alcMakeContextCurrent(Audio_Device.Context);

		// genero le sorgenti (numero massimo di suoni suonati contemporanemente)
		alGenSources(MAX_SOURCES, Audio_Device.source);

		_err=alGetError();
		if (_err!= AL_NO_ERROR)
		{
			printf("\n Errore generazione sorgenti : %d", alGetError());
			return _err;
		}

		for (i=0; i<MAX_SOURCES; i++)
		{
			Audio_Device.Sources_State[i].looping = false;
			Audio_Device.Sources_State[i].last_play= -1;
			Audio_Device.Sources_State[i].state=0;

			alSourcef(Audio_Device.source[i], AL_PITCH, 1.0f);
			alSourcef(Audio_Device.source[i], AL_GAIN, DEFAULT_GAIN);
			alSourcefv(Audio_Device.source[i], AL_POSITION, sposition);
			alSourcefv(Audio_Device.source[i], AL_VELOCITY, svelocity);
		}

		alListenerfv(AL_POSITION, lposition);
		alListenerfv(AL_VELOCITY, lvelocity);
		alListenerfv(AL_ORIENTATION, lorientation);

		pAudio_Device=&Audio_Device;
	}

	// reset errore
	_err=alGetError();
	
	// genero i buffer per i suoni
	Sounds.num_sounds[resID]=NUM_BUFFERS;
	Sounds.pBuffers=Sounds.Buffers[resID];
	alGenBuffers(Sounds.num_sounds[resID], Sounds.pBuffers);

	_err=alGetError();
	if (_err!= AL_NO_ERROR)
	{
		printf("\n Errore generazione buffer : %d", _err);
		return _err;
	}

	return 0;
}

//! @brief Carica una risorsa audio all'interno di un buffer
//! @param [in] data Risorsa audio
//! @param [in] size Grandezza della risorsa
//! @param [in] freq Frequenza della risorsa
//! @param [in] format Formato della risorsa
//! @param [in] resID Indice relativo al tipo di risorse che si sta caricando
//! @return Controllo sulla presenza di errori
int _LoadSound(void* data, unsigned long size,  float freq , int format)
{
	int _err=0;
	unsigned short resID = 0;
	if(Sounds.cur_length[resID] < Sounds.num_sounds[resID])
	{
		alBufferData(Sounds.Buffers[resID][Sounds.cur_length[resID]], (ALenum)format, data, size, (ALsizei)freq);

		_err=alGetError();

		if (_err!= AL_NO_ERROR)
			return -1;

		_err = Sounds.cur_length[resID];

		Sounds.cur_length[resID]++;
	}
	else
	{
		printf("\n Errore numero di suoni cur_length: %d num_sounds: %d", Sounds.cur_length[resID], Sounds.num_sounds[resID]);
		_err=-1;
	}

	return _err;
}

//! @brief Controlla se una data risorsa audio è in pausa
//! @param [in] sound_id Indice della risorsa audio da controllare
//! @param [in] avvia Se riavviare le risorse audio in pausa
//! @return Risultato del controllo
BOOL _IsPaused(unsigned short sound_id, BOOL avvia)
{
#ifndef SIMULA_GIOCO
	ALenum state;

	if (pAudio_Device == NULL)
		return FALSE;

	for(BYTE source=0;source<MAX_SOURCES;source++)
	{
		if (pAudio_Device->Sources_State[source].last_play==(sound_id))
		{
			alGetSourcei((ALuint)pAudio_Device->source[source],AL_SOURCE_STATE,&state);

			if(state==AL_PAUSED)
			{
				if(avvia)
					alSourcePlay(pAudio_Device->source[source]);
				return TRUE;
			}
		}
	}
#endif

	return FALSE;
}

//! @brief Esegue una data risorsa audio
//! @param [in] sound_id Indice della risorsa audio
//! @param [in] loop Se ripetere o meno
//! @param [in] gain Valore del gain da impostare
//! @param [in] resID  Indice relativo al tipo di risorse che si sta eseguendo
//! @param [in] fade Se la risorsa audio va eseguita con fade
//! @param [in] time Durata della risorsa audio
void _playsound(unsigned short sound_id, unsigned char loop, unsigned char gain, unsigned short resID, WORD fade=0, WORD time=0)
{
#ifndef SIMULA_GIOCO
	BYTE _idx;
	float _gain;

	if (pAudio_Device == NULL)
		return;

	if(!Audio_Device.volume)
		fade=0;
	
	if(fade)
		_gain=0;
	else
	{
		_gain=(float)gain*1.0f/100;
		_gain=_gain*(float)Audio_Device.volume/100.0f;
		_gain=VBMIN(_gain, 1.0f);
	}

	if (pAudio_Device->Disabled || (vbSoundIsPlaying(sound_id) && loop == LOOP_NOSTOP))
		return;

	if (_IsPaused(sound_id, TRUE))
		return;
	// cerco la prima sorgente libera
	for (_idx = pAudio_Device->source_idx+1; _idx < MAX_SOURCES; _idx++)
	{
		if (!_SourceIsPlaying(_idx))
		{
			break;
		}
	}

	if (_idx==MAX_SOURCES)
	{
		for (_idx = 0; _idx < pAudio_Device->source_idx ; _idx++)
		{
			if (!_SourceIsPlaying(_idx))
			{
				break;
			}
		}
	}

	if (_idx < MAX_SOURCES)
	{
		pAudio_Device->Sources_State[_idx].state = 1;
		pAudio_Device->Sources_State[_idx].last_play = sound_id;
		pAudio_Device->Sources_State[_idx].looping = loop;
		pAudio_Device->Sources_State[_idx].fade=fade;
		pAudio_Device->Sources_State[_idx].resourceID=resID;
		pAudio_Device->Sources_State[_idx].timer=0;
		pAudio_Device->Sources_State[_idx].timeLen=time;
		pAudio_Device->Sources_State[_idx].volume=gain;

		if(loop)
			loop=true;
		alSourceStop(pAudio_Device->source[_idx]);
		alSourcei(pAudio_Device->source[_idx], AL_LOOPING, loop);
		alSourcef(pAudio_Device->source[_idx], AL_GAIN, _gain);
		alSourcei(pAudio_Device->source[_idx], AL_BUFFER, Sounds.Buffers[resID][sound_id]);
		alSourcePlay(pAudio_Device->source[_idx]);

		pAudio_Device->source_idx=_idx;
	}
#endif
}
//! @brief Mette in pausa una data risorsa audio in esecuzione
//! @param [in] sound_id Indice della risorsa audio
//! @param [in] fade fade da utilizzare
//! @param [in] time durata della risorsa audio
//! @return Controllo di errore
void vbPauseSound(unsigned short sound_id, WORD fade, WORD time)
{
	int _err=0;

	if (pAudio_Device == NULL)
		return;

	for(short i = 0;i<MAX_SOURCES;i++)
	{
		if(pAudio_Device->Sources_State[i].last_play==(sound_id))
		{
			pAudio_Device->Sources_State[i].timeLen=time;
			pAudio_Device->Sources_State[i].timer=0;
			pAudio_Device->Sources_State[i].fade=FADE_PAUSE|FADE_OUT;
		}
	}
}

//! @brief Esegue una data risorsa audio tra quelle specifiche del singolo gioco attivo
//! @param [in] pos Indice della risorsa audio
//! @param [in] loops Se ripetere o meno
//! @param [in] volume Valore del volume da impostare
//! @return Controllo di errore
int vbPlaySound(WORD pos, BOOL loops, DWORD volume)
{
	_playsound(pos, (unsigned char)loops, (unsigned char)volume, GAME_AUDIO_RESOURCE_SET_ID);
	return 0;
}

//! @brief Esegue una data risorsa audio tra quelle specifiche del singolo gioco attivo ma con un determinato Fade di ingresso
//! @param [in] pos Indice della risorsa audio
//! @param [in] loops Se ripetere o meno
//! @param [in] volume Valore del volume da impostare
//! @param [in] time Durata della risorsa audio  
//! @return Controllo di errore
int vbPlaySoundFade(WORD pos, BOOL loops, DWORD volume, WORD time)
{
	_playsound(pos, (unsigned char)loops, (unsigned char)volume, GAME_AUDIO_RESOURCE_SET_ID, FADE_IN, time);
	return 0;
}

//! @brief Ferma l'esecuzione di una data risorsa audio
//! @param [in] pos Indice della risorsa audio
//! @param [in] time Durata della risorsa audio
void vbStopSoundFade(WORD pos, WORD time)
{
	int _err=0;

	if (pAudio_Device == NULL)
		return;

	if(!Audio_Device.volume)
	{
		vbStopSound(pos);
		return;
	}


	for(short i = 0;i<MAX_SOURCES;i++)
	{
		if(pAudio_Device->Sources_State[i].last_play==(pos))
		{
			//pAudio_Device->Sources_State[i].looping=0;
			pAudio_Device->Sources_State[i].timeLen=time;
			pAudio_Device->Sources_State[i].timer=0;
			pAudio_Device->Sources_State[i].fade=FADE_OUT;
		}
	}
}

//! @brief Ferma l'esecuzione di una data risorsa audio
//! @param [in] pos Indice della risorsa audio
void vbStopSound(WORD pos,BYTE resourceID)
{
#ifndef SIMULA_GIOCO
	int _err=0;

	if (pAudio_Device == NULL)
		return;

	for(short i = 0;i<MAX_SOURCES;i++)
	{
		if(pAudio_Device->Sources_State[i].last_play==(pos) && (pAudio_Device->Sources_State[i].resourceID == resourceID || resourceID == ALL_AUDIO_RESOURCE_SET_ID))
		{
			alSourceStop(pAudio_Device->source[i]);
			pAudio_Device->Sources_State[i].last_play=-1;
			pAudio_Device->Sources_State[i].looping=false;
			pAudio_Device->Sources_State[i].state=0;
			pAudio_Device->Sources_State[i].timer=0;
			pAudio_Device->Sources_State[i].timeLen=0;
			pAudio_Device->Sources_State[i].fade=0;
			//_err=alGetError();
			//if (_err)
			//{
			//	return;
			//}
		}
	}
#endif
}

//! @brief Ferma l'esecuzione di tutte le risorse audio
//! @return void
#ifdef ARM_RAINBOW
void vbStopSoundAll(BOOL del_loops)
#else
void vbStopSoundAll()
#endif
{
#ifndef SIMULA_GIOCO
	if (pAudio_Device == NULL)
		return;

	for(short i = 0;i<MAX_SOURCES;i++)
	{
		if(pAudio_Device->Sources_State[i].looping != LOOP_NOSTOP)
		{
		
			alSourceStop(pAudio_Device->source[i]);

			pAudio_Device->Sources_State[i].last_play=-1;
			pAudio_Device->Sources_State[i].looping =false;
			pAudio_Device->Sources_State[i].state=0;
			pAudio_Device->Sources_State[i].timer=0;
			pAudio_Device->Sources_State[i].timeLen=0;
			pAudio_Device->Sources_State[i].fade=0;
		}
	}
#endif
}

//! @brief Controlla se una data risorsa audio è in esecuzione
//! @param [in] sound_id Indice della risorsa audio da controllare
//! @param [in] resourceID Specifica se si tratta di un indice appartenente alle risorse di progetto o a quelle comuni
//! @return Risultato del controllo
BOOL vbSoundIsPlaying(unsigned short sound_id,BYTE resourceID)
{
#ifndef SIMULA_GIOCO
	ALenum state;

	if (pAudio_Device == NULL)
		return FALSE;

	for(BYTE source=0;source<MAX_SOURCES;source++)
	{
		if (pAudio_Device->Sources_State[source].last_play==(sound_id) && (resourceID == pAudio_Device->Sources_State[source].resourceID || resourceID == ALL_AUDIO_RESOURCE_SET_ID))
		{
			alGetSourcei((ALuint)pAudio_Device->source[source],AL_SOURCE_STATE,&state);

			if(state==AL_PLAYING || pAudio_Device->Sources_State[source].looping)
			{
				pAudio_Device->Sources_State[source].state=1;
				return TRUE;
			}
		}
	}
#endif

	return FALSE;
}

//! @brief Disabilita il device
//! @return void
void vbDisableSounds()
{
	if (pAudio_Device == NULL)
		return;

	pAudio_Device->Disabled=true;
	vbStopSoundAll();
}

//! @brief Abilita il device
//! @return void
void vbEnableSounds()
{
	if (pAudio_Device == NULL)
		return;

	pAudio_Device->Disabled=false;
}

//! @brief  Permette di impostare il volume dei suoni
BOOL vbSetSoundVolume(unsigned short sound_id, DWORD volume)
{
#ifndef SIMULA_GIOCO
	ALenum state;
	float _gain;

	_gain=(float)volume* 1.0f/100;
	_gain=VBMIN(_gain, 1.0f);

	if (pAudio_Device == NULL)
		return FALSE;

	for(BYTE source=0;source<MAX_SOURCES;source++)
	{
		if (pAudio_Device->Sources_State[source].last_play==(sound_id))
		{
			alGetSourcei((ALuint)pAudio_Device->source[source],AL_SOURCE_STATE,&state);

			if(state==AL_PLAYING || pAudio_Device->Sources_State[source].looping)
			{
				pAudio_Device->Sources_State[source].state=1;
				alSourcef(pAudio_Device->source[source], AL_GAIN, _gain);

				return TRUE;
			}
		}
	}
#endif

	return FALSE;
}
//! @brief Interpolazione dei valori compresi nell'intervallo definito
//! @param [in] Start_p Primo valore dell'intervallo
//! @param [in] Stop_p Ultimo valore dell'intervallo
//! @param [in] currentStep Punto da interpolare
//! @param [in] TOTsteps Numero di valori dell'insieme
//! @return Valore interpolato del punto
FLOAT doTween(FLOAT Start_p, FLOAT Stop_p, WORD currentStep, WORD TOTsteps)
{
	if(currentStep >= TOTsteps)
		currentStep=TOTsteps;
	return (Stop_p - Start_p)*((FLOAT)currentStep / (FLOAT)TOTsteps) + Start_p;
}

//! @brief Esegue il polling a libreria audio, permette di ottenere un FADE_IN o FADE_OUT dei suoni in ingresso o in uscita 
//! @return void
void vbPollSound()
{
	BYTE _idx;
	for(_idx=0; _idx<MAX_SOURCES; _idx++)
	{
		if(_SourceIsPlaying(_idx) && pAudio_Device->Sources_State[_idx].fade)
		{
			if(pAudio_Device->Sources_State[_idx].fade==FADE_IN)
				vbSetSoundVolume(pAudio_Device->Sources_State[_idx].last_play, (DWORD)doTween(0.0f, (FLOAT)VBMIN(pAudio_Device->Sources_State[_idx].volume,Audio_Device.volume), pAudio_Device->Sources_State[_idx].timer, pAudio_Device->Sources_State[_idx].timeLen)); 
			else if(pAudio_Device->Sources_State[_idx].fade==FADE_OUT)
				vbSetSoundVolume(pAudio_Device->Sources_State[_idx].last_play, (DWORD)doTween((FLOAT)VBMIN(pAudio_Device->Sources_State[_idx].volume,Audio_Device.volume), 0.0f, pAudio_Device->Sources_State[_idx].timer, pAudio_Device->Sources_State[_idx].timeLen));
				
			
			if(pAudio_Device->Sources_State[_idx].timer==pAudio_Device->Sources_State[_idx].timeLen)
			{	if(pAudio_Device->Sources_State[_idx].fade&FADE_OUT)
				{	
					if(pAudio_Device->Sources_State[_idx].fade&FADE_PAUSE)
						alSourcePause(pAudio_Device->source[_idx]);
					else
						vbStopSound(pAudio_Device->Sources_State[_idx].last_play);
					pAudio_Device->Sources_State[_idx].looping=0;
				}
				if(pAudio_Device->Sources_State[_idx].fade&FADE_PAUSE)
					pAudio_Device->Sources_State[_idx].fade=FADE_PAUSE;
				else
					pAudio_Device->Sources_State[_idx].fade=0;
			}
			pAudio_Device->Sources_State[_idx].timer++;
		}
	}
}
