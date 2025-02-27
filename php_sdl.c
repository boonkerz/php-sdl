#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <php.h>
#include <zend_API.h>
#include <ext/standard/info.h>

#include "php_sdl.h"
#include "sdl_arginfo.h"


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
		SUCCESS == PHP_MINIT_CALL(sdl_render) &&
		SUCCESS == PHP_MINIT_CALL(sdl_event) &&
		SUCCESS == PHP_MINIT_CALL(sdl_ttf) &&
		SUCCESS == PHP_MINIT_CALL(sdl_color) &&
		SUCCESS == PHP_MINIT_CALL(sdl_surface) &&
		SUCCESS == PHP_MINIT_CALL(sdl_rect) &&
		SUCCESS == PHP_MINIT_CALL(sdl_iostream) &&
		SUCCESS == PHP_MINIT_CALL(sdl_image) &&
		SUCCESS == PHP_MINIT_CALL(systray) &&
		SUCCESS == PHP_MINIT_CALL(sdl_glcontext)/* &&
		SUCCESS == PHP_MINIT_CALL(sdl_mouse) &&
		SUCCESS == PHP_MINIT_CALL(sdl_video)*/
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
    int sdl_linked = SDL_GetVersion();
	int img_linked = IMG_Version();
	int ttf_linked = TTF_Version();
    char buff[32];

    php_info_print_table_start();
	
    php_info_print_table_header(2, "SDL support", "enabled");

    php_info_print_table_row(2, "SDL module version", PHP_SDL_VERSION);

    snprintf(buff, sizeof(buff), "%d.%d.%d",
             SDL_VERSIONNUM_MAJOR(sdl_linked), SDL_VERSIONNUM_MINOR(sdl_linked), SDL_VERSIONNUM_MICRO(sdl_linked));
    php_info_print_table_row(2, "SDL library version", buff);
	
    snprintf(buff, sizeof(buff), "%d.%d.%d",
             SDL_VERSIONNUM_MAJOR(img_linked), SDL_VERSIONNUM_MINOR(img_linked), SDL_VERSIONNUM_MICRO(img_linked));
    php_info_print_table_row(2, "SDL_image library version", buff);
	
    snprintf(buff, sizeof(buff), "%d.%d.%d",
             SDL_VERSIONNUM_MAJOR(ttf_linked), SDL_VERSIONNUM_MINOR(ttf_linked), SDL_VERSIONNUM_MICRO(ttf_linked));
    php_info_print_table_row(2, "SDL_ttf library version", buff);

    php_info_print_table_end();
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
