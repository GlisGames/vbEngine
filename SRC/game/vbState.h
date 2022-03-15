#ifndef VBSTATE_H
#define VBSTATE_H

#include "basetypes.h"
#include "vbContainer.h"
#include "vbTween.h"

enum TYPE_GAME_STATE
{
	S_NONE = 0xFF,
	S_BOOT = 0,		//!< Stato di inizializzazione del gioco
	S_DEMO,
	S_SETTINGS,
	S_START,		//!< Stato di inizio partita
	S_PLAY_EXIT,		//!< Stato di attesa tra una mano e l'altra a partita iniziata
	S_PLAY_RUN,		//!< Stato di rullata
	S_VICTORY,		//!< Stato di fine rullata
	S_GAMEOVER,		//!< Stato in cui vengono mostrate le linee vincenti
	S_CUSTOM_MAP,		//!< Stato di demo
	S_FREEGAME_PLAY,	//!< Stato che avvia le mani del Free Game
	S_FREEGAME_EXIT,	//!< Stato di fine Free Game
	S_BONUS_ENTER,	//!< Stato di inizio del Bonus
	S_BONUS_PLAY,	//!< Stato di gioco del Bonus
	S_BONUS_EXIT,	//!< Stato di fine Bonus
	S_REGISTER,	//!< Stato di registrazione della partita appena conclusa 
	S_EROGA,	//!< Stato di erogazione della vincita
	S_HELP,	//!< Stato delle regole
	S_MENU,	//!< Stato di ingresso nel menu
	S_SPINGRATIS,	//!> Stato di rigioco spin gratuiti
	S_CONTROL,	//!< Stato di valutazione delle configurazioni presenti sui rulli
	S_ENTER_HIGHSCORE,	
	S_HIGHSCORE,		
#if GAME_TYPE&AWP_GAME
	S_MISTERYWIN = 21,
	S_ARROTONDA = 22,	//!< Stato di arrotondamento della vincita
#endif
	S_LOADING = 23, 
	S_BONUS_ONE = 24,
	S_BONUS_TWO = 25
};

class vbState
{
private:
	WORD exitState = 0xFF;
protected:
	BOOL firstIn = TRUE;
	DWORD frame = 0;
	QWORD time = 0;

	virtual void init() {};
	virtual void exit() {};
	virtual void checkButton() {};
	virtual void update() {};

public:
	vbTweenMap tweens;
	vbContainer* canvas = NULL;
	WORD stateID = 0xFF;
	vbState();
	void stateExit(WORD s);
	BOOL afterAndEveryFrame(DWORD after, DWORD every);
	BOOL afterAndUntilFrame(DWORD after, DWORD until);
	BOOL afterAndEveryUntilFrame(DWORD after, DWORD until, DWORD every);

	BOOL afterAndEvery(DWORD after, DWORD every);
	BOOL afterAndUntil(DWORD after, DWORD until);
	BOOL afterAndEveryUntil(DWORD after, DWORD until, DWORD every);
	WORD run();
};

#endif // !VBSTATE_H