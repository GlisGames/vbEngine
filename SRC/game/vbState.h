#ifndef VBSTATE_H
#define VBSTATE_H

#include "basetypes.h"
#include "vbContainer.h"
#include "vbTween.h"

enum TYPE_GAME_STATE
{
	S_NONE = 0xFF,
	S_BOOT = 0,		//!< Stato di inizializzazione del gioco
	S_START = 1,		//!< Stato di inizio partita
	S_START_DEMO = 2,		//!< Stato di inizio del demo
	S_CHANGE = 3,		//!< Stato di attesa tra una mano e l'altra a partita iniziata
	S_CLOSEMANO = 4,		//!< Stato di fine della mano corrente
	S_PLAY_RUN = 5,		//!< Stato di rullata
	S_PLAY_EXIT = 6,		//!< Stato di fine rullata
	S_SHOW_WIN = 7,		//!< Stato in cui vengono mostrate le linee vincenti
	S_DEMO = 8,		//!< Stato di demo
	S_FREEGAME_ENTER = 9,		//!< Stato di inizio del Free Game
	S_FREEGAME_PLAY = 10,	//!< Stato che avvia le mani del Free Game
	S_FREEGAME_EXIT = 11,	//!< Stato di fine Free Game
	S_BONUS_ENTER = 12,	//!< Stato di inizio del Bonus
	S_BONUS_PLAY = 13,	//!< Stato di gioco del Bonus
	S_BONUS_EXIT = 14,	//!< Stato di fine Bonus
	S_REGISTER = 15,	//!< Stato di registrazione della partita appena conclusa 
	S_EROGA = 16,	//!< Stato di erogazione della vincita
	S_HELP = 17,	//!< Stato delle regole
	S_MENU = 18,	//!< Stato di ingresso nel menu
	S_SPINGRATIS = 19,	//!> Stato di rigioco spin gratuiti
	S_CONTROL = 20,	//!< Stato di valutazione delle configurazioni presenti sui rulli
#if GAME_TYPE&AWP_GAME
	S_MISTERYWIN = 21,
	S_ARROTONDA = 22,	//!< Stato di arrotondamento della vincita
#endif
	S_LOADING = 23
};

class vbState
{
private:
	WORD exitState = 0xFF;
protected:
	BOOL firstIn = TRUE;
	DWORD frame = 0;

	virtual void init() {};
	virtual void exit() {};
	virtual void checkButton() {};
	virtual void update() {};

public:
	vbTweenMap tweens;
	vbContainer* canvas;
	WORD stateID = 0xFF;
	vbState();
	void stateExit(WORD s);
	BOOL afterAndEvery(DWORD after, DWORD every);
	BOOL afterAndUntil(DWORD after, DWORD until);
	BOOL afterAndEveryUntil(DWORD after, DWORD until, DWORD every);
	WORD run();
};

#endif // !VBSTATE_H