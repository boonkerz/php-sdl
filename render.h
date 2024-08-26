#ifndef RENDER_H
#define RENDER_H
#include "php.h"
#include <zend_API.h>
#include <SDL3/SDL.h>
ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_SetRenderDrawColor, 0, 0, 5)
	ZEND_ARG_INFO(0, renderer)
	ZEND_ARG_INFO(0, r)
	ZEND_ARG_INFO(0, g)
	ZEND_ARG_INFO(0, b)
	ZEND_ARG_INFO(0, a)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_RenderClear, 0, 0, 1)
	ZEND_ARG_INFO(0, renderer)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_DestroyRenderer, 0, 0, 1)
	ZEND_ARG_INFO(0, renderer)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_DestroyTexture, 0, 0, 1)
	ZEND_ARG_INFO(0, texture)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_RenderFillRect, 0, 0, 2)
	ZEND_ARG_INFO(0, renderer)
	ZEND_ARG_OBJ_INFO(0, rect, SDL_Rect, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_RenderRect, 0, 0, 2)
	ZEND_ARG_INFO(0, renderer)
	ZEND_ARG_OBJ_INFO(0, rect, SDL_Rect, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_RenderLine, 0, 0, 4)
	ZEND_ARG_INFO(0, renderer)
	ZEND_ARG_INFO(0, x1)
	ZEND_ARG_INFO(0, y1)
	ZEND_ARG_INFO(0, x2)
	ZEND_ARG_INFO(0, y2)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_RenderPresent, 0, 0, 1)
	ZEND_ARG_INFO(0, renderer)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_RenderPoint, 0, 0, 3)
	ZEND_ARG_INFO(0, renderer)
	ZEND_ARG_INFO(0, x)
	ZEND_ARG_INFO(0, y)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_CreateTextureFromSurface, 0, 0, 2)
	ZEND_ARG_INFO(0, renderer)
	ZEND_ARG_OBJ_INFO(0, surface, SDL_Surface, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_CreateTexture, 0, 0, 5)
	ZEND_ARG_INFO(0, renderer)
	ZEND_ARG_INFO(0, format)
	ZEND_ARG_INFO(0, access)
	ZEND_ARG_INFO(0, w)
	ZEND_ARG_INFO(0, h)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_GetTextureSize, 0, 0, 1)
	ZEND_ARG_OBJ_INFO(0, texture, SDL_Texture, 0)
	ZEND_ARG_TYPE_INFO(1, w, IS_LONG, 1)
	ZEND_ARG_TYPE_INFO(1, h, IS_LONG, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_SetRenderTarget, 0, 0, 2)
	ZEND_ARG_INFO(0, renderer)
	ZEND_ARG_INFO(0, texture)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_CreateRenderer, 0, 0, 1)
	ZEND_ARG_OBJ_INFO(0, window, SDL_Window, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_CreateSoftwareRenderer, 0, 0, 1)
	ZEND_ARG_OBJ_INFO(0, surface, SDL_Surface, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_RenderTexture, 0, 0, 4)
	ZEND_ARG_INFO(0, renderer)
	ZEND_ARG_INFO(0, texture)
	ZEND_ARG_OBJ_INFO(0, srcrect, SDL_FRect, 1)
	ZEND_ARG_OBJ_INFO(0, dstrect, SDL_FRect, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_RenderTextureRotated, 0, 0, 7)
	ZEND_ARG_INFO(0, renderer)
	ZEND_ARG_INFO(0, texture)
	ZEND_ARG_OBJ_INFO(0, srcrect, SDL_Rect, 1)
	ZEND_ARG_OBJ_INFO(0, dstrect, SDL_Rect, 1)
	ZEND_ARG_INFO(0, angle)
	ZEND_ARG_OBJ_INFO(0, center, SDL_Point, 1)
	ZEND_ARG_INFO(0, flip)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_SetRenderLogicalPresentation, 0, 0, 3)
	ZEND_ARG_OBJ_INFO(0, renderer, SDL_Renderer, 0)
	ZEND_ARG_TYPE_INFO(0, w, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, h, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_GetCurrentRenderOutputSize, 0, 0, 3)
	ZEND_ARG_INFO(0, renderer)
	ZEND_ARG_INFO(1, w)
	ZEND_ARG_INFO(1, h)
ZEND_END_ARG_INFO()


PHP_FUNCTION(SDL_SetRenderDrawColor);
PHP_FUNCTION(SDL_RenderClear);
PHP_FUNCTION(SDL_DestroyRenderer);
PHP_FUNCTION(SDL_DestroyTexture);
PHP_FUNCTION(SDL_RenderFillRect);
PHP_FUNCTION(SDL_RenderRect);
PHP_FUNCTION(SDL_RenderLine);
PHP_FUNCTION(SDL_RenderPresent);
PHP_FUNCTION(SDL_RenderPoint);
PHP_FUNCTION(SDL_CreateTextureFromSurface);
PHP_FUNCTION(SDL_CreateTexture);
PHP_FUNCTION(SDL_GetTextureSize);
PHP_FUNCTION(SDL_SetRenderTarget);
PHP_FUNCTION(SDL_CreateRenderer);
PHP_FUNCTION(SDL_CreateSoftwareRenderer);
PHP_FUNCTION(SDL_RenderTexture);
PHP_FUNCTION(SDL_RenderTextureRotated);
PHP_FUNCTION(SDL_SetRenderLogicalPresentation);
PHP_FUNCTION(SDL_GetCurrentRenderOutputSize);

PHP_MINIT_FUNCTION(sdl_render);

#endif //RENDERER_H
