#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <php.h>
#include <zend_API.h>
#include <ext/standard/info.h>

#include "php_sdl.h"
#include "sdl_arginfo.h"
#include "version.h"

zend_module_entry sdl_module_entry = {
	STANDARD_MODULE_HEADER,
	"sdl",
	sdl_functions,
	NULL,		/* Replace with NULL if there is nothing to do at php startup   */
	NULL, /* Replace with NULL if there is nothing to do at php shutdown  */
	PHP_RINIT(sdl),				/* RINIT */
	NULL,				/* RSHUTDOWN */
	PHP_MINFO(sdl),
	PHP_SDL_VERSION,
	STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_SDL
# ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
# endif
ZEND_GET_MODULE(sdl)
#endif /* COMPILE_DL_SDL */



PHP_RINIT_FUNCTION(sdl)
{
#if defined(ZTS) && defined(COMPILE_DL_SDL)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif

	return SUCCESS;
}

PHP_MINFO_FUNCTION(sdl)
{
	php_info_print_table_start();
	php_info_print_table_row(2, "SDL support", "enabled");
}