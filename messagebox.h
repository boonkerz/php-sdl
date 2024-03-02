#ifndef MESSAGEBOX_H
#define MESSAGEBOX_H
#include "php.h"
#include <zend_API.h>
#include <SDL3\SDL.h>
zend_class_entry *get_php_sdl_messageboxcolor_ce(void);
zend_bool sdl_messageboxcolor_to_zval(const SDL_MessageBoxColor *color, zval *value);
zend_bool zval_to_sdl_messageboxcolor(zval *value, SDL_MessageBoxColor *color);

zend_class_entry *get_php_sdl_messageboxbuttondata_ce(void);
zend_bool sdl_messageboxbuttondata_to_zval(const SDL_MessageBoxButtonData *data, zval *value);
zend_bool zval_to_sdl_messageboxbuttondata(zval *value, SDL_MessageBoxButtonData *data);

zend_class_entry *get_php_sdl_messageboxdata_ce(void);
zend_bool sdl_messageboxdata_to_zval(SDL_MessageBoxData *data, zval *z_val, Uint32 flags);
SDL_MessageBoxData *zval_to_sdl_messageboxdata(zval *z_val);

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_ShowMessageBox, 0, 0, 2)
       ZEND_ARG_INFO(0, messageboxdata)
       ZEND_ARG_INFO(1, buttonID)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_ShowSimpleMessageBox, 0, 0, 3)
       ZEND_ARG_INFO(0, flags)
       ZEND_ARG_INFO(0, title)
       ZEND_ARG_INFO(0, message)
       ZEND_ARG_OBJ_INFO(0, window, SDL_Window, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(SDL_ShowMessageBox);
PHP_FUNCTION(SDL_ShowSimpleMessageBox);

PHP_MINIT_FUNCTION(sdl_messagebox);


#endif //MESSAGEBOX_H
