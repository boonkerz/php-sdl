<?php

declare(strict_types=1);

require 'bootstrap.php';

const WINDOW_WIDTH = 800;
const WINDOW_HEIGHT = 800;

SDL_Init(SDL_INIT_VIDEO);
$window = SDL_CreateWindow("Drawing points on screen", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
$renderer = SDL_CreateRenderer($window, 0, SDL_RENDERER_ACCELERATED);

// Clear screen
SDL_SetRenderDrawColor($renderer, 100, 0, 0, 0);
SDL_RenderClear($renderer);

// Draw line
SDL_SetRenderDrawColor($renderer, 255, 0, 0, 255);
for ($i = 0; $i < WINDOW_WIDTH; ++$i) {
    SDL_RenderDrawPoint($renderer, $i, $i);
}
SDL_RenderPresent($renderer);

// Wait for quit event
$event = new SDL_Event;

$font = __DIR__ . "/DroidSans.ttf";
var_dump($font);
$f = SDL_TTF_OpenFont($font, 40);
var_dump($f);
$r = new \SDL_Color(1,63,127,255);
var_dump($r);
$d = SDL_TTF_RenderText_Solid($f, "test", $r);
var_dump($d);
//$texture = SDL_CreateTextureFromSurface($renderer, $d);

while (true) {
    if (SDL_PollEvent($event) && $event->type == SDL_QUIT) {
        break;
    }
}

SDL_DestroyRenderer($renderer);
SDL_DestroyWindow($window);
SDL_Quit();