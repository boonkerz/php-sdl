<?php declare(strict_types=1);

error_reporting(E_ALL);

if (!extension_loaded('sdl')) {
    fprintf(STDERR, "The sdl extension is not loaded. Make sure it is in the system and there is a line for it on the php.ini file (eg \"extension=sdl.so\")");
    exit(1);
}


const WINDOW_WIDTH = 800;
const WINDOW_HEIGHT = 800;

SDL_Init(SDL_INIT_VIDEO);
$window = SDL_CreateWindow("Drawing points on screen", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE);
$renderer = SDL_CreateRenderer($window, 0, SDL_RENDERER_ACCELERATED);

// Clear screen
SDL_SetRenderDrawColor($renderer, 100, 0, 0, 0);
SDL_RenderClear($renderer);

// Draw line
SDL_SetRenderDrawColor($renderer, 255, 0, 0, 255);
for ($i = 0; $i < WINDOW_WIDTH; ++$i) {
    SDL_RenderPoint($renderer, $i, $i);
}
SDL_RenderPresent($renderer);

// Wait for quit event
$event = new SDL_Event;
while (true) {
    if (SDL_PollEvent($event) && $event->type == SDL_EVENT_QUIT) {
        break;
    }
    if (SDL_PollEvent($event) && $event->type == SDL_EVENT_QUIT) {

    }
}

SDL_DestroyRenderer($renderer);
SDL_DestroyWindow($window);
SDL_Quit();