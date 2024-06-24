#ifndef VIDEO_H
#define VIDEO_H
#include "php.h"
#include <zend_API.h>
#include <SDL3/SDL.h>
#include "rect.h"
zend_class_entry *get_php_sdl_displaymode_ce(void);
zend_bool sdl_displaymode_to_zval(const SDL_DisplayMode *display, zval *value);
zend_bool zval_to_sdl_displaymode(zval *value, SDL_DisplayMode *display);

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_GetVideoDriver, 0, 0, 1)
       ZEND_ARG_INFO(0, driverIndex)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_GetDisplayBounds, 0, 0, 2)
       ZEND_ARG_INFO(0, displayIndex)
       ZEND_ARG_INFO(1, rect)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_GetClosestFullscreenDisplayMode, 0, 0, 2)
       ZEND_ARG_INFO(0, displayIndex)
       ZEND_ARG_OBJ_INFO(0, desired, SDL_DisplayMode, 0)
       ZEND_ARG_INFO(1, closest)
ZEND_END_ARG_INFO()

/* generic arginfo */
ZEND_BEGIN_ARG_INFO_EX(arginfo_video_none, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_dysplayindex, 0, 0, 1)
       ZEND_ARG_INFO(0, displayIndex)
ZEND_END_ARG_INFO()

PHP_FUNCTION(SDL_GetNumVideoDrivers);
PHP_FUNCTION(SDL_GetVideoDriver);
PHP_FUNCTION(SDL_GetCurrentVideoDriver);
PHP_FUNCTION(SDL_GetDisplays);
PHP_FUNCTION(SDL_GetDisplayName);
PHP_FUNCTION(SDL_GetDisplayBounds);
PHP_FUNCTION(SDL_GetFullscreenDisplayModes);
PHP_FUNCTION(SDL_GetClosestFullscreenDisplayMode);
PHP_FUNCTION(SDL_ScreenSaverEnabled);
PHP_FUNCTION(SDL_EnableScreenSaver);
PHP_FUNCTION(SDL_DisableScreenSaver);

PHP_MINIT_FUNCTION(sdl_video);

#endif //VIDEO_H
