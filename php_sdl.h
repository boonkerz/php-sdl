#ifndef	_INCLUDED_SDL_H
#define	_INCLUDED_SDL_H

# define PHP_SDL_VERSION "0.1.0"

extern zend_module_entry sdl_module_entry;
# define phpext_sdl_ptr &sdl_module_entry

PHP_RINIT_FUNCTION(sdl);
PHP_MINIT_FUNCTION(sdl);
PHP_MINFO_FUNCTION(sdl);

zend_bool php_sdl_check_overflow(int a, int b, int silent);

# if defined(ZTS) && defined(COMPILE_DL_SDL)
ZEND_TSRMLS_CACHE_EXTERN()
# endif

#endif
