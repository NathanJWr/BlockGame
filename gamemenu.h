#ifndef GAMEMENU_H
#define GAMEMENU_H
#include <SDL2/SDL.h>
int handleGameMenuEvents(SDL_Event*);
void setupGameMenu();
void drawGameMenu();
void updateGameMenu();
void cleanupGameMenu();
#endif
