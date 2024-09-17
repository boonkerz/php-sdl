<?php declare(strict_types=1);

error_reporting(E_ALL);

if (!extension_loaded('sdl')) {
    fprintf(STDERR, "The sdl extension is not loaded. Make sure it is in the system and there is a line for it on the php.ini file (eg \"extension=sdl.so\")");
    exit(1);
}


const WINDOW_WIDTH = 800;
const WINDOW_HEIGHT = 800;

SDL_Init(SDL_INIT_VIDEO);
SDL_TTF_Init();
$window = SDL_CreateWindow("Drawing points on screen", WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_HIGH_PIXEL_DENSITY);
$renderer = SDL_CreateRenderer($window);

// Clear screen
SDL_SetRenderDrawColor($renderer, 255, 255, 255, 100);
SDL_RenderClear($renderer);

$font = SDL_TTF_OpenFont(__DIR__ . DIRECTORY_SEPARATOR . 'segoe-ui.ttf' , 30);

$color = new SDL_Color(0,0,0,0);

$surface = SDL_TTF_RenderText_Blended($font, "Hello World", $color);
$width = 0;
$height = 0;
SDL_TTF_SizeText($font, "Hello World", $width, $height);
var_dump($surface->w);
$rect = new SDL_FRect(10,10,$surface->w,$surface->h);
$texture = SDL_CreateTextureFromSurface($renderer, $surface);



SDL_SetRenderDrawColor($renderer, 255, 100, 128, 100);
SDL_RenderFillRect($renderer, $rect);
SDL_SetRenderDrawColor($renderer, 255, 128, 128, 100);
SDL_RenderRect($renderer, $rect);
SDL_RenderTexture($renderer, $texture, null, $rect);
SDL_RenderPresent($renderer);

// Wait for quit event
$event = new SDL_Event;
while (true) {
    if (SDL_PollEvent($event) && $event->type == SDL_EVENT_QUIT) {
        break;
    }
    if (SDL_PollEvent($event) && $event->type == SDL_EVENT_WINDOW_RESIZED) {
        SDL_SetRenderDrawColor($renderer, 255, 255, 255, 100);
        SDL_RenderClear($renderer);
        SDL_RenderPresent($renderer);
    }
}

SDL_DestroyRenderer($renderer);
SDL_DestroyWindow($window);
SDL_Quit();
