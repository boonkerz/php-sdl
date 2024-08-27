<?php declare(strict_types=1);

error_reporting(E_ALL);

if (!extension_loaded('sdl')) {
    fprintf(STDERR, "The sdl extension is not loaded. Make sure it is in the system and there is a line for it on the php.ini file (eg \"extension=sdl.so\")");
    exit(1);
}


const WINDOW_WIDTH = 800;
const WINDOW_HEIGHT = 800;

SDL_Init(SDL_INIT_VIDEO);
var_dump("VIDEO");
SDL_TTF_Init();
var_dump("TTF");
$window = SDL_CreateWindow("Drawing points on screen", WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_HIGH_PIXEL_DENSITY);
$renderer = SDL_CreateRenderer($window);

// Clear screen
SDL_SetRenderDrawColor($renderer, 255, 255, 255, 100);
SDL_RenderClear($renderer);



$font = SDL_TTF_OpenFont(__DIR__ . DIRECTORY_SEPARATOR . 'segoe-ui.ttf' , 20);
var_dump($font);

$color = new SDL_Color(0,0,0,0);
var_dump($color);

$surface = SDL_TTF_RenderText_Blended($font, "Hello World", $color);
var_dump($surface);
$texture = SDL_CreateTextureFromSurface($renderer, $surface);
var_dump($texture);
//SDL_TTF_SizeText($this->font, $actWidget->getText(), \FFI::addr($rect->w), \FFI::addr($rect->h));
$rect = new SDL_FRect(40,40,$surface->w,$surface->h);
var_dump($rect);

SDL_RenderTexture($renderer, $texture, null, $rect);

SDL_SetRenderDrawColor($renderer, 128, 128, 128, 100);
SDL_RenderFillRect($renderer, $rect);
SDL_SetRenderDrawColor($renderer, 255, 128, 128, 100);
SDL_RenderRect($renderer, $rect);



SDL_RenderPresent($renderer);

// Wait for quit event
$event = new SDL_Event;
while (true) {
    if (SDL_PollEvent($event) && $event->type == SDL_EVENT_QUIT) {
        break;
    }
    if (SDL_PollEvent($event) && $event->type == SDL_EVENT_WINDOW_RESIZED) {
        var_dump($event->window);
    }
}

SDL_DestroyRenderer($renderer);
SDL_DestroyWindow($window);
SDL_Quit();
