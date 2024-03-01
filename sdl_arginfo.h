#ifndef SDL_ARGINFO_H
#define SDL_ARGINFO_H

ZEND_BEGIN_ARG_INFO_EX(arginfo_SDL_GetVersion, 0, 0, 1)
    ZEND_ARG_INFO(1, version)
ZEND_END_ARG_INFO()

PHP_FUNCTION(SDL_GetVersion);


static const zend_function_entry sdl_functions[] = {
    ZEND_FE(SDL_GetVersion, arginfo_SDL_GetVersion)
    PHP_FE_END
};

#endif //SDL_ARGINFO_H
