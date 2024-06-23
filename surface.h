#ifndef SURFACE_H
#define SURFACE_H
#include "php.h"
#include <zend_API.h>
#include <SDL3/SDL.h>

zend_class_entry *get_php_sdl_surface_ce(void);
zend_bool sdl_surface_to_zval(SDL_Surface *surface, zval *zval);
SDL_Surface *zval_to_sdl_surface(zval *z_val);


ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_CreateSurface, 0, 0, 6)
       ZEND_ARG_INFO(0, flags)
       ZEND_ARG_INFO(0, width)
       ZEND_ARG_INFO(0, height)
       ZEND_ARG_INFO(0, depth)
       ZEND_ARG_INFO(0, Rmask)
       ZEND_ARG_INFO(0, Gmask)
       ZEND_ARG_INFO(0, Bmask)
       ZEND_ARG_INFO(0, Amask)
ZEND_END_ARG_INFO()


ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_LoadBMP, 0, 0, 1)
       ZEND_ARG_INFO(0, path)
ZEND_END_ARG_INFO()


ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_SaveBMP_RW, 0, 0, 2)
       ZEND_ARG_OBJ_INFO(0, surface, SDL_Surface, 0)
       ZEND_ARG_OBJ_INFO(1, rwops, SDL_RWops, 0)
       ZEND_ARG_INFO(0, freedst)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_Surface_SaveBMP_RW, 0, 0, 1)
       ZEND_ARG_OBJ_INFO(1, rwops, SDL_RWops, 0)
       ZEND_ARG_INFO(0, freedst)
ZEND_END_ARG_INFO()


ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_SaveBMP, 0, 0, 2)
       ZEND_ARG_OBJ_INFO(0, surface, SDL_Surface, 0)
       ZEND_ARG_INFO(0, path)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_Surface_SaveBMP, 0, 0, 1)
       ZEND_ARG_INFO(0, path)
ZEND_END_ARG_INFO()


ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_FillSurfaceRect, 0, 0, 3)
       ZEND_ARG_OBJ_INFO(0, surface, SDL_Surface, 0)
       ZEND_ARG_INFO(0, rect)
       ZEND_ARG_INFO(0, color)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_Surface_FillRect, 0, 0, 2)
       ZEND_ARG_INFO(0, rect)
       ZEND_ARG_INFO(0, color)
ZEND_END_ARG_INFO()



ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_FillSurfaceRects, 0, 0, 4)
       ZEND_ARG_OBJ_INFO(0, surface, SDL_Surface, 0)
       ZEND_ARG_INFO(0, rects)
       ZEND_ARG_INFO(0, count)
       ZEND_ARG_INFO(0, color)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_Surface_FillRects, 0, 0, 3)
       ZEND_ARG_INFO(0, rects)
       ZEND_ARG_INFO(0, count)
       ZEND_ARG_INFO(0, color)
ZEND_END_ARG_INFO()


ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_BlitSurface, 0, 0, 3)
       ZEND_ARG_OBJ_INFO(0, src, SDL_Surface, 0)
       ZEND_ARG_OBJ_INFO(0, srcrect, SDL_rect, 1)
       ZEND_ARG_OBJ_INFO(0, dst, SDL_Surface, 0)
       ZEND_ARG_OBJ_INFO(1, dstrect, SDL_rect, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_Surface_UpperBlit, 0, 0, 2)
       ZEND_ARG_OBJ_INFO(0, srcrect, SDL_rect, 1)
       ZEND_ARG_OBJ_INFO(0, dst, SDL_Surface, 0)
       ZEND_ARG_OBJ_INFO(1, dstrect, SDL_rect, 1)
ZEND_END_ARG_INFO()


ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_BlitSurfaceUnchecked, 0, 0, 4)
       ZEND_ARG_OBJ_INFO(0, src, SDL_Surface, 0)
       ZEND_ARG_OBJ_INFO(1, srcrect, SDL_rect, 0)
       ZEND_ARG_OBJ_INFO(0, dst, SDL_Surface, 0)
       ZEND_ARG_OBJ_INFO(1, dstrect, SDL_rect, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_Surface_LowerBlit, 0, 0, 3)
       ZEND_ARG_OBJ_INFO(1, srcrect, SDL_rect, 0)
       ZEND_ARG_OBJ_INFO(0, dst, SDL_Surface, 0)
       ZEND_ARG_OBJ_INFO(1, dstrect, SDL_rect, 0)
ZEND_END_ARG_INFO()


ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_SetSurfaceRLE, 0, 0, 2)
       ZEND_ARG_OBJ_INFO(0, surface, SDL_Surface, 0)
       ZEND_ARG_INFO(0, flag)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_Surface_SetRLE, 0, 0, 1)
       ZEND_ARG_INFO(0, flag)
ZEND_END_ARG_INFO()


ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_SetSurfaceColorKey, 0, 0, 2)
       ZEND_ARG_OBJ_INFO(0, surface, SDL_Surface, 0)
       ZEND_ARG_INFO(0, flag)
       ZEND_ARG_INFO(0, key)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_Surface_SetColorKey, 0, 0, 1)
       ZEND_ARG_INFO(0, flag)
       ZEND_ARG_INFO(0, key)
ZEND_END_ARG_INFO()


ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_GetSurfaceColorKey, 0, 0, 2)
       ZEND_ARG_OBJ_INFO(0, surface, SDL_Surface, 0)
       ZEND_ARG_INFO(1, key)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_Surface_GetColorKey, 0, 0, 1)
       ZEND_ARG_INFO(1, key)
ZEND_END_ARG_INFO()


ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_SetSurfaceColorMod, 0, 0, 4)
       ZEND_ARG_OBJ_INFO(0, surface, SDL_Surface, 0)
       ZEND_ARG_INFO(0, red)
       ZEND_ARG_INFO(0, green)
       ZEND_ARG_INFO(0, blue)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_Surface_SetColorMod, 0, 0, 3)
       ZEND_ARG_INFO(0, red)
       ZEND_ARG_INFO(0, green)
       ZEND_ARG_INFO(0, blue)
ZEND_END_ARG_INFO()


ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_GetSurfaceColorMod, 0, 0, 4)
       ZEND_ARG_OBJ_INFO(0, surface, SDL_Surface, 0)
       ZEND_ARG_INFO(1, red)
       ZEND_ARG_INFO(1, green)
       ZEND_ARG_INFO(1, blue)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_Surface_GetColorMod, 0, 0, 3)
       ZEND_ARG_INFO(1, red)
       ZEND_ARG_INFO(1, green)
       ZEND_ARG_INFO(1, blue)
ZEND_END_ARG_INFO()


ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_SetSurfaceAlphaMod, 0, 0, 2)
       ZEND_ARG_OBJ_INFO(0, surface, SDL_Surface, 0)
       ZEND_ARG_INFO(0, alpha)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_Surface_SetAlphaMod, 0, 0, 1)
       ZEND_ARG_INFO(0, alpha)
ZEND_END_ARG_INFO()



ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_GetSurfaceAlphaMod, 0, 0, 2)
       ZEND_ARG_OBJ_INFO(0, surface, SDL_Surface, 0)
       ZEND_ARG_INFO(1, alpha)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_Surface_GetAlphaMod, 0, 0, 1)
       ZEND_ARG_INFO(1, alpha)
ZEND_END_ARG_INFO()


ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_SetSurfaceBlendMode, 0, 0, 2)
       ZEND_ARG_OBJ_INFO(0, surface, SDL_Surface, 0)
       ZEND_ARG_INFO(0, blendmmode)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_Surface_SetBlendMode, 0, 0, 1)
       ZEND_ARG_INFO(0, blendmmode)
ZEND_END_ARG_INFO()



ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_GetSurfaceBlendMode, 0, 0, 2)
       ZEND_ARG_OBJ_INFO(0, surface, SDL_Surface, 0)
       ZEND_ARG_INFO(1, blendmode)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_Surface_GetBlendMode, 0, 0, 1)
       ZEND_ARG_INFO(1, blendmode)
ZEND_END_ARG_INFO()


ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_SetSurfaceClipRect, 0, 0, 2)
       ZEND_ARG_OBJ_INFO(0, surface, SDL_Surface, 0)
       ZEND_ARG_INFO(0, cliprect)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_Surface_SetClipRect, 0, 0, 1)
       ZEND_ARG_INFO(0, cliprect)
ZEND_END_ARG_INFO()


ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_GetSurfaceClipRect, 0, 0, 2)
       ZEND_ARG_OBJ_INFO(0, surface, SDL_Surface, 0)
       ZEND_ARG_INFO(1, cliprect)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_Surface_GetClipRect, 0, 0, 1)
       ZEND_ARG_INFO(1, cliprect)
ZEND_END_ARG_INFO()


ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_ConvertSurface, 0, 0, 2)
       ZEND_ARG_OBJ_INFO(0, surface, SDL_Surface, 0)
       ZEND_ARG_OBJ_INFO(0, format, SDL_PixelFormat, 0)
       ZEND_ARG_INFO(0, flags)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_Surface_Convert, 0, 0, 1)
       ZEND_ARG_OBJ_INFO(0, format, SDL_PixelFormat, 0)
       ZEND_ARG_INFO(0, flags)
ZEND_END_ARG_INFO()


ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_ConvertSurfaceFormat, 0, 0, 2)
       ZEND_ARG_OBJ_INFO(0, surface, SDL_Surface, 0)
       ZEND_ARG_INFO(0, format)
       ZEND_ARG_INFO(0, flags)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_Surface_ConvertFormat, 0, 0, 1)
       ZEND_ARG_INFO(0, format)
       ZEND_ARG_INFO(0, flags)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_ConvertPixels, 0, 0, 8)
       ZEND_ARG_INFO(0, height)
       ZEND_ARG_INFO(0, width)
       ZEND_ARG_INFO(0, src_format)
       ZEND_ARG_OBJ_INFO(0, src, SDL_Pixels, 0)
       ZEND_ARG_INFO(0, src_pitch)
       ZEND_ARG_INFO(0, dst_format)
       ZEND_ARG_OBJ_INFO(0, dst, SDL_Pixels, 0)
       ZEND_ARG_INFO(0, dst_pitch)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_surface_none, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_Surface, 0, 0, 1)
       ZEND_ARG_OBJ_INFO(0, surface, SDL_Surface, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_LoadBMP_RW, 0, 0, 2)
       ZEND_ARG_OBJ_INFO(1, RWops, SDL_RWops, 0)
       ZEND_ARG_INFO(0, freesrc)
ZEND_END_ARG_INFO()

PHP_FUNCTION(SDL_CreateSurface);
PHP_FUNCTION(SDL_LoadBMP_RW);
PHP_FUNCTION(SDL_LoadBMP);
PHP_FUNCTION(SDL_SaveBMP_RW);
PHP_FUNCTION(SDL_SaveBMP);
PHP_FUNCTION(SDL_DestroySurface);
PHP_FUNCTION(SDL_FillSurfaceRect);
PHP_FUNCTION(SDL_FillSurfaceRects);
PHP_FUNCTION(SDL_MUSTLOCK);
PHP_FUNCTION(SDL_LockSurface);
PHP_FUNCTION(SDL_UnlockSurface);
PHP_FUNCTION(SDL_BlitSurface);
PHP_FUNCTION(SDL_BlitSurfaceUnchecked);
PHP_FUNCTION(SDL_BlitSurfaceScaled);
PHP_FUNCTION(SDL_BlitSurfaceUncheckedScaled);
PHP_FUNCTION(SDL_SoftStretch);
PHP_FUNCTION(SDL_SetSurfaceRLE);
PHP_FUNCTION(SDL_SetSurfaceColorKey);
PHP_FUNCTION(SDL_GetSurfaceColorKey);
PHP_FUNCTION(SDL_SetSurfaceColorMod);
PHP_FUNCTION(SDL_GetSurfaceColorMod);
PHP_FUNCTION(SDL_SetSurfaceAlphaMod);
PHP_FUNCTION(SDL_GetSurfaceAlphaMod);
PHP_FUNCTION(SDL_SetSurfaceBlendMode);
PHP_FUNCTION(SDL_GetSurfaceBlendMode);
PHP_FUNCTION(SDL_SetSurfaceClipRect);
PHP_FUNCTION(SDL_GetSurfaceClipRect);
PHP_FUNCTION(SDL_ConvertSurface);
PHP_FUNCTION(SDL_ConvertSurfaceFormat);
PHP_FUNCTION(SDL_ConvertPixels);

PHP_MINIT_FUNCTION(sdl_surface);

#endif //SURFACE_H
