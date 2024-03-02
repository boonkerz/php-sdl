#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <php.h>
#include <zend_API.h>
#include <ext/standard/info.h>

#include "php_sdl.h"
#include "sdl_arginfo.h"
#include "version.h"
#include "sdl.h"
#include "messagebox.h"
#include "window.h"
#include "video.h"
#include "glcontext.h"
#include "mouse.h"
#include "rect.h"
#include "rwops.h"

zend_module_entry sdl_module_entry = {
	STANDARD_MODULE_HEADER,
	"sdl",
	sdl_functions,
	PHP_MINIT(sdl),		/* Replace with NULL if there is nothing to do at php startup   */
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

#define PHP_MINIT_CALL(func) PHP_MINIT(func)(INIT_FUNC_ARGS_PASSTHRU)

PHP_MINIT_FUNCTION(sdl)
{
	if (SUCCESS == PHP_MINIT_CALL(sdl_sdl) &&
		SUCCESS == PHP_MINIT_CALL(sdl_version) &&
		SUCCESS == PHP_MINIT_CALL(sdl_messagebox) &&
		SUCCESS == PHP_MINIT_CALL(sdl_window) &&
		SUCCESS == PHP_MINIT_CALL(sdl_glcontext) &&
		SUCCESS == PHP_MINIT_CALL(sdl_rect) &&
		SUCCESS == PHP_MINIT_CALL(sdl_mouse) &&
		SUCCESS == PHP_MINIT_CALL(sdl_pixels) &&
		SUCCESS == PHP_MINIT_CALL(sdl_rwops) &&
		SUCCESS == PHP_MINIT_CALL(sdl_video)
)
	{
		return SUCCESS;
	}

	return FAILURE;
}

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

/* {{{ php_sdl_check_overflow */
zend_bool php_sdl_check_overflow(int a, int b, int silent)
{
	if (a <= 0 || b <= 0)
	{
		if (!silent)
		{
			php_error_docref(NULL, E_WARNING, "one parameter to a memory allocation multiplication is negative or zero, failing operation gracefully");
		}
		return 1;
	}
	if (a > INT_MAX / b)
	{
		if (!silent)
		{
			php_error_docref(NULL, E_WARNING, "product of memory allocation multiplication would exceed INT_MAX, failing operation gracefully");
		}
		return 1;
	}
	return 0;
}
/* }}} */