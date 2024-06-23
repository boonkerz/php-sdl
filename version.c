#include "php.h"
#include <zend_API.h>
#include <SDL3/SDL_version.h>
#include "version.h"

PHP_FUNCTION(SDL_GetVersion)
{
	SDL_Version version;
	zval *version_array;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "z/", &version_array) == FAILURE) {
		RETURN_FALSE;
	}

	SDL_GetVersion(&version);
	if(0 == convert_sdl_version_to_php_array(&version, version_array)) {
        RETURN_FALSE;
    }

    RETURN_TRUE;
}

PHP_MINIT_FUNCTION(sdl_version)
{
	return SUCCESS;
}

zend_bool convert_sdl_version_to_php_array(SDL_Version *version, zval *version_array)
{

		if (version) {
			array_init(version_array);
			add_assoc_long(version_array, "major", version->major);
			add_assoc_long(version_array, "minor", version->minor);
			add_assoc_long(version_array, "patch", version->patch);

			return 1;
		}
		ZVAL_NULL(version_array);
		return 0;
}
