<?php declare(strict_types=1);

error_reporting(E_ALL);

if (!extension_loaded('sdl')) {
    fprintf(STDERR, "The sdl extension is not loaded. Make sure it is in the system and there is a line for it on the php.ini file (eg \"extension=sdl.so\")");
    exit(1);
}

function initSDLOrExit() {
    \SDL_Init(\SDL_INIT_VIDEO);
}

function printSdlErrorAndExit() {
    fprintf(STDERR, "ERROR: %s\n", SDL_GetError());
    exit(1);
}

initSDLOrExit();

$window = SDL_CreateWindow("Drawing points on screen", 800, 600, SDL_WINDOW_HIGH_PIXEL_DENSITY);
$renderer = SDL_CreateRenderer($window);
// Clear screen
SDL_SetRenderDrawColor($renderer, 255, 255, 255, 100);
SDL_RenderClear($renderer);
SDL_SetRenderDrawColor($renderer, 255, 0, 0, 255);
for ($i = 0; $i < 800; ++$i) {
     SDL_RenderPoint($renderer, $i, $i);
}
SDL_RenderPresent($renderer);
$event = new SDL_Event;

$windowSec = SDL_CreateWindow("secounds", 800, 600, SDL_WINDOW_HIGH_PIXEL_DENSITY);
$rendererSec = SDL_CreateRenderer($windowSec);
SDL_SetRenderDrawColor($rendererSec, 255, 123, 255, 100);
SDL_RenderClear($rendererSec);
SDL_SetRenderDrawColor($rendererSec, 255, 12, 0, 255);
for ($i = 0; $i < 800; ++$i) {
    SDL_RenderPoint($rendererSec, $i, $i);
}
SDL_RenderPresent($rendererSec);

while (true) {
    if (SDL_PollEvent($event) && $event->type == SDL_EVENT_QUIT) {
        echo "Ende";
        break;
    }
    if (SDL_PollEvent($event)) {
        var_dump($event);
    }
}

SDL_DestroyRenderer($rendererSec);
SDL_DestroyWindow($windowSec);

SDL_DestroyRenderer($renderer);
SDL_DestroyWindow($window);
SDL_Quit();
