#include "php.h"
#include <zend_API.h>
#include <SDL3\SDL.h>
#include "php_sdl.h"
#include "rwops.h"
static zend_class_entry *php_sdl_rwops_ce;
static zend_object_handlers php_sdl_rwops_handlers;
struct php_sdl_rwops {
	zend_object   zo;
	SDL_RWops    *rwops;
	Uint32        flags;
	char         *buf;
};


/* {{{ get_php_sdl_rwops_ce */
zend_class_entry *get_php_sdl_rwops_ce(void)
{
	return php_sdl_rwops_ce;
}
/* }}} */


#define FETCH_RWOPS(__ptr, __id, __check) \
{ \
        intern = (struct php_sdl_rwops *)Z_OBJ_P(__id);\
        __ptr = intern->rwops; \
        if (__check && !__ptr) {\
                php_error_docref(NULL, E_WARNING, "Invalid %s object", ZSTR_VAL(intern->zo.ce->name));\
                RETURN_FALSE;\
        }\
}

/* {{{ sdl_rwops_to_zval */
zend_bool sdl_rwops_to_zval(SDL_RWops *rwops, zval *z_val, Uint32 flags, char *buf)
{
	if (rwops) {
		struct php_sdl_rwops *intern;

		object_init_ex(z_val, php_sdl_rwops_ce);
		intern = (struct php_sdl_rwops *)Z_OBJ_P(z_val);
		intern->rwops = rwops;
		intern->flags = flags;
		intern->buf   = buf;

		return 1;
	}
	ZVAL_NULL(z_val);
	return 0;
}
/* }}} */


/* {{{ zval_to_sdl_rwops */
SDL_RWops *zval_to_sdl_rwops(zval *z_val)
{
	struct php_sdl_rwops *intern;

	if (Z_TYPE_P(z_val) == IS_OBJECT && Z_OBJCE_P(z_val) == php_sdl_rwops_ce) {
		intern = (struct php_sdl_rwops *)Z_OBJ_P(z_val);
		return intern->rwops;
	}
	return NULL;
}
/* }}} */


/* {{{ php_sdl_rwops_free
	 */
static void php_sdl_rwops_free(zend_object *object)
{
	struct php_sdl_rwops *intern = (struct php_sdl_rwops *) object;

	if (intern->rwops) {
		if (!(intern->flags & SDL_DONTFREE)) {
			SDL_RWclose(intern->rwops);
		}
		if (intern->buf) {
			efree(intern->buf);
		}
	}

	zend_object_std_dtor(&intern->zo);
}
/* }}} */


/* {{{ php_sdl_rwops_new
 */
static zend_object* php_sdl_rwops_new(zend_class_entry *class_type)
{
	struct php_sdl_rwops *intern = NULL;

	intern = ecalloc(1, sizeof(struct php_sdl_rwops) + zend_object_properties_size(class_type));

	zend_object_std_init(&intern->zo, class_type);
	object_properties_init(&intern->zo, class_type);

	intern->rwops = NULL;
	intern->zo.handlers = (zend_object_handlers *) &php_sdl_rwops_handlers;

	return &intern->zo;
}
/* }}} */

/* {{{ proto SDL_RWops::__construct(void) */
static PHP_METHOD(SDL_RWops, __construct)
{
	struct php_sdl_rwops *intern;
	zend_error_handling error_handling;

	intern = (struct php_sdl_rwops *)Z_OBJ_P(getThis());

	zend_replace_error_handling(EH_THROW, NULL, &error_handling);
	if (FAILURE == zend_parse_parameters_none()) {
		zend_restore_error_handling(&error_handling);
		return;
	}
	zend_restore_error_handling(&error_handling);

	intern->rwops = SDL_CreateRW();
	if (intern->rwops) {
		intern->flags = 0;
	} else {
		zend_throw_exception(zend_exception_get_default(), SDL_GetError(), 0);
	}
}
/* }}} */

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_SDL_RWops___toString, 0, 0, IS_STRING, 0)
ZEND_END_ARG_INFO()

/* {{{ proto SDL_RWops::__toString() */
static PHP_METHOD(SDL_RWops, __toString)
{
	struct php_sdl_rwops *intern;
	char *buf, *t=NULL;

	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}
	intern = (struct php_sdl_rwops *)Z_OBJ_P(getThis());
	if (intern->rwops) {
		switch (intern->rwops->type) {
			case SDL_RWOPS_WINFILE:
				t="\"Win32 file\"";
				break;
			case SDL_RWOPS_STDFILE:
				t="\"Stdio file\"";
				break;
			case SDL_RWOPS_JNIFILE:
				t="\"Androit asset\"";
				break;
			case SDL_RWOPS_MEMORY:
				t="\"Memory stream\"";
				break;
			case SDL_RWOPS_MEMORY_RO:
				t="\"Read only memory stream\"";
				break;
		}
	}
	spprintf(&buf, 100, "SDL_RWops(%s)", t ? t : "");
	RETVAL_STRING(buf);
}
/* }}} */


/* {{{ proto SDL_RWops SDL_CreateRW(void)

extern DECLSPEC SDL_RWops *SDLCALL SDL_CreateRW(void);
 */
PHP_FUNCTION(SDL_CreateRW)
{
	SDL_RWops *rwops;

	if (FAILURE == zend_parse_parameters_none()) {
		return;
	}
	rwops = SDL_CreateRW();
	sdl_rwops_to_zval(rwops, return_value, 0, NULL);
}
/* }}} */


/* {{{ proto SDL_RWops SDL_RWFromFile(string path,mode)

 extern DECLSPEC SDL_RWops *SDLCALL SDL_RWFromFile(const char *file,
                                                   const char *mode);
 */
PHP_FUNCTION(SDL_RWFromFile)
{
	char *path, *mode;
	size_t path_len, mode_len;
	SDL_RWops *rwops;

	if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS(), "ss", &path, &path_len, &mode, &mode_len)) {
		return;
	}
	rwops = SDL_RWFromFile(path, mode);
	sdl_rwops_to_zval(rwops, return_value, 0, NULL);
}
/* }}} */

/* {{{ proto SDL_RWops SDL_RWFromConstMem(string buf [, int size ])

extern DECLSPEC SDL_RWops *SDLCALL SDL_RWFromConstMem(const void *mem,
                                                      int size);
 */
PHP_FUNCTION(SDL_RWFromConstMem)
{
	char *buf, *pbuf;
	size_t buf_len;
	zend_long size = 0;
	SDL_RWops *rwops;

	if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS(), "s|l", &buf, &buf_len, &size)) {
		return;
	}
	if (size<=0) {
		size=buf_len;
	} else if (buf_len < size) {
		php_error_docref(NULL, E_WARNING, "given size reduce to buffer size (%ld)", buf_len);
		size = buf_len;
	}

	pbuf=estrndup(buf, size);

	rwops = SDL_RWFromConstMem(pbuf, size);
	sdl_rwops_to_zval(rwops, return_value, 0, pbuf);
}
/* }}} */

/* {{{ proto SDL_RWops SDL_RWFromMem(string &buf, int size)

extern DECLSPEC SDL_RWops *SDLCALL SDL_RWFromMem(void *mem, int size);
 */
PHP_FUNCTION(SDL_RWFromMem)
{
	zval *z_buf;
	zend_long size = 0;
	SDL_RWops *rwops;

	if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS(), "zl", &z_buf, &size)) {
		return;
	}
	php_error_docref(NULL, E_NOTICE, "this function may raised unsupported error with PHP memory");

	Z_STRLEN_P(z_buf) = size;
//php7	Z_STRVAL_P(z_buf) = emalloc(size);
//php7	Z_TYPE_P(z_buf) = IS_STRING;
	memset(Z_STRVAL_P(z_buf), 0, size);

	rwops = SDL_RWFromMem(Z_STRVAL_P(z_buf), size);
	sdl_rwops_to_zval(rwops, return_value, 0, NULL);
}
/* }}} */


/* {{{ php_stream_to_zval_rwops */
void php_stream_to_zval_rwops(php_stream *stream, zval *return_value, int autoclose )
{
	SDL_RWops *rwops;
	FILE * fp = NULL;

	if (stream == NULL) {
		RETURN_NULL();
	}
	if (autoclose) {
		php_error_docref(NULL, E_NOTICE, "autoclose can raise unsupported error with PHP stream");
	}

	/* Can we get a FILE * */
	if (php_stream_is(stream, PHP_STREAM_IS_STDIO))	{
		if (FAILURE == php_stream_cast(stream, PHP_STREAM_AS_STDIO, (void**)&fp, REPORT_ERRORS)) {
			RETURN_NULL();
		}
// TODO
		//rwops = SDL_RWFromFP(fp, autoclose);
		sdl_rwops_to_zval(rwops, return_value, 0, NULL);
	}
}
/* }}} */

/* {{{ proto void SDL_DestroyRW(SDL_RWops area)

 extern DECLSPEC void SDLCALL SDL_DestroyRW(SDL_RWops * area);
 */
PHP_FUNCTION(SDL_DestroyRW)
{
	struct php_sdl_rwops *intern;
	zval *z_rwops;
	SDL_RWops *rwops;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "O", &z_rwops, php_sdl_rwops_ce) == FAILURE) {
		return;
	}
	FETCH_RWOPS(rwops, z_rwops, 1);

	SDL_DestroyRW(intern->rwops);
	if (intern->buf) {
		efree(intern->buf);
	}
	intern->rwops = NULL;
	intern->buf   = NULL;
}
/* }}} */


/* {{{ proto int SDL_RWsize(SDL_RWops area)

 define SDL_RWsize(ctx)         (ctx)->size(ctx)
 */
PHP_FUNCTION(SDL_RWsize)
{
	struct php_sdl_rwops *intern;
	zval *z_rwops;
	SDL_RWops *rwops;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "O", &z_rwops, php_sdl_rwops_ce) == FAILURE) {
		return;
	}
	FETCH_RWOPS(rwops, z_rwops, 1);

	RETURN_LONG(SDL_RWsize(rwops));
}
/* }}} */


/* {{{ proto int SDL_RWseek(SDL_RWops area, int offset, int whence)

 define SDL_RWseek(ctx, offset, whence) (ctx)->seek(ctx, offset, whence)
 */
PHP_FUNCTION(SDL_RWseek)
{
	struct php_sdl_rwops *intern;
	zval *z_rwops;
	SDL_RWops *rwops;
	zend_long offset, whence;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "Oll", &z_rwops, php_sdl_rwops_ce, &offset, &whence) == FAILURE) {
		return;
	}
	FETCH_RWOPS(rwops, z_rwops, 1);

	RETURN_LONG(SDL_RWseek(rwops, offset, whence));
}
/* }}} */


/* {{{ proto int SDL_RWtell(SDL_RWops area)

 define SDL_RWtell(ctx)         (ctx)->seek(ctx, 0, RW_SEEK_CUR)
 */
PHP_FUNCTION(SDL_RWtell)
{
	struct php_sdl_rwops *intern;
	zval *z_rwops;
	SDL_RWops *rwops;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "O", &z_rwops, php_sdl_rwops_ce) == FAILURE) {
		return;
	}
	FETCH_RWOPS(rwops, z_rwops, 1);

	RETURN_LONG(SDL_RWtell(rwops));
}
/* }}} */


/* {{{ proto int SDL_RWclose(SDL_RWops area)

 define SDL_RWclose(ctx)        (ctx)->close(ctx)
 */
PHP_FUNCTION(SDL_RWclose)
{
	struct php_sdl_rwops *intern;
	zval *z_rwops;
	SDL_RWops *rwops;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "O", &z_rwops, php_sdl_rwops_ce) == FAILURE) {
		return;
	}
	FETCH_RWOPS(rwops, z_rwops, 1);

	/* close method also call free */
	intern->rwops = NULL;
	intern->buf   = NULL;

	RETURN_LONG(SDL_RWclose(rwops));
}
/* }}} */


/* {{{ proto int SDL_RWread(SDL_RWops area, string, &buf, [ int size=1 ,] int n)

 define SDL_RWread(ctx, ptr, size, n)   (ctx)->read(ctx, ptr, size, n)
 */
PHP_FUNCTION(SDL_RWread)
{
	struct php_sdl_rwops *intern;
	zval *z_rwops, *z_buf;
	zend_long size, n=0;
	long read;
	SDL_RWops *rwops;
	char *buf;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "Ozl|l", &z_rwops, php_sdl_rwops_ce, &z_buf, &size, &n) == FAILURE) {
		return;
	}
	if (n<=0) {
		n = size;
		size = 1;
	}
	if (php_sdl_check_overflow(size, n, 0)) {
		return;
	}

	FETCH_RWOPS(rwops, z_rwops, 1);
	buf = emalloc(size * n);
	read = SDL_RWread(rwops, buf, size, n);
	if (read > 0) {
		if (read < n) {
			buf = erealloc(buf, read * size);
		}
		zval_dtor(z_buf);
		ZVAL_STRINGL(z_buf, buf, read * size);
	} else {
		efree(buf);
	}
	RETURN_LONG(read);
}
/* }}} */

/* {{{ proto int SDL_RWwrite(SDL_RWops arean string, buf [[, int size=1 ], int n])

 define SDL_RWwrite(ctx, ptr, size, n)  (ctx)->write(ctx, ptr, size, n)
 */
PHP_FUNCTION(SDL_RWwrite)
{
	struct php_sdl_rwops *intern;
	zval *z_rwops;
	zend_long size=0, n=0;
	long write;
	size_t buf_len;
	SDL_RWops *rwops;
	char *buf;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "Os|ll", &z_rwops, php_sdl_rwops_ce, &buf, &buf_len, &size, &n) == FAILURE) {
		return;
	}
	if (size<=0) { /* optional arg, default to string length */
		n = buf_len;
		size = 1;
	} else if (n<=0) { /* only length, so consider char (consistency with other php function) */
		n = size;
		size = 1;
	}
	if (php_sdl_check_overflow(size, n, 0)) {
		return;
	}
	if (buf_len < (size * n)) {
		php_error_docref(NULL, E_WARNING, "given size reduce to buffer size (%ld)", buf_len);
		size = 1;
		n = buf_len;
	}
	FETCH_RWOPS(rwops, z_rwops, 1);

	write = SDL_RWwrite(rwops, buf, size, n);
	RETURN_LONG(write);
}
/* }}} */


/* {{{ proto int SDL_ReadU8(SDL_RWops area)

 *  \name Read endian functions
 *
 *  Read an item of the specified endianness and return in native format.
 extern DECLSPEC Uint8 SDLCALL SDL_ReadU8(SDL_RWops * src);
 */
PHP_FUNCTION(SDL_ReadU8)
{
	struct php_sdl_rwops *intern;
	zval *z_rwops;
	SDL_RWops *rwops;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "O", &z_rwops, php_sdl_rwops_ce) == FAILURE) {
		return;
	}
	FETCH_RWOPS(rwops, z_rwops, 1);
	Uint8 *value;
	SDL_ReadU8(rwops, &value);
	RETURN_LONG(value);
}
/* }}} */


/* {{{ proto int SDL_ReadU16LE(SDL_RWops area)

 extern DECLSPEC Uint16 SDLCALL SDL_ReadU16LE(SDL_RWops * src);
 */
PHP_FUNCTION(SDL_ReadU16LE)
{
	struct php_sdl_rwops *intern;
	zval *z_rwops;
	SDL_RWops *rwops;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "O", &z_rwops, php_sdl_rwops_ce) == FAILURE) {
		return;
	}
	FETCH_RWOPS(rwops, z_rwops, 1);
	Uint16 *value;
	SDL_ReadU16LE(rwops, &value);
	RETURN_LONG(value);
}
/* }}} */


/* {{{ proto int SDL_ReadU16BE(SDL_RWops area)

 extern DECLSPEC Uint16 SDLCALL SDL_ReadU16BE(SDL_RWops * src);
 */
PHP_FUNCTION(SDL_ReadU16BE)
{
	struct php_sdl_rwops *intern;
	zval *z_rwops;
	SDL_RWops *rwops;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "O", &z_rwops, php_sdl_rwops_ce) == FAILURE) {
		return;
	}
	FETCH_RWOPS(rwops, z_rwops, 1);
	Uint16 *value;
	SDL_ReadU16BE(rwops, &value);
	RETURN_LONG(value);
}
/* }}} */


/* {{{ proto int SDL_ReadU32LE(SDL_RWops area)

extern DECLSPEC Uint32 SDLCALL SDL_ReadU32LE(SDL_RWops * src);
 */
PHP_FUNCTION(SDL_ReadU32LE)
{
	struct php_sdl_rwops *intern;
	zval *z_rwops;
	SDL_RWops *rwops;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "O", &z_rwops, php_sdl_rwops_ce) == FAILURE) {
		return;
	}
	FETCH_RWOPS(rwops, z_rwops, 1);
	Uint16 *value;
	SDL_ReadU16BE(rwops, &value);
	RETURN_LONG(value);
}
/* }}} */


/* {{{ proto int SDL_ReadU32BE(SDL_RWops area)

extern DECLSPEC Uint32 SDLCALL SDL_ReadU32BE(SDL_RWops * src);
 */
PHP_FUNCTION(SDL_ReadU32BE)
{
	struct php_sdl_rwops *intern;
	zval *z_rwops;
	SDL_RWops *rwops;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "O", &z_rwops, php_sdl_rwops_ce) == FAILURE) {
		return;
	}
	FETCH_RWOPS(rwops, z_rwops, 1);
	Uint32 *value;
	SDL_ReadU32BE(rwops, &value);
	RETURN_LONG(value);
}
/* }}} */


#if SIZEOF_LONG > 4
/* {{{ proto int SDL_ReadLE64(SDL_RWops area)

extern DECLSPEC Uint64 SDLCALL SDL_ReadLE64(SDL_RWops * src);
 */
PHP_FUNCTION(SDL_ReadLE64)
{
	struct php_sdl_rwops *intern;
	zval *z_rwops;
	SDL_RWops *rwops;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "O", &z_rwops, php_sdl_rwops_ce) == FAILURE) {
		return;
	}
	FETCH_RWOPS(rwops, z_rwops, 1);

	RETURN_LONG(SDL_ReadLE64(rwops));
}
/* }}} */


/* {{{ proto int SDL_ReadBE64(SDL_RWops area)

 extern DECLSPEC Uint64 SDLCALL SDL_ReadBE64(SDL_RWops * src);
 */
PHP_FUNCTION(SDL_ReadBE64)
{
	struct php_sdl_rwops *intern;
	zval *z_rwops;
	SDL_RWops *rwops;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "O", &z_rwops, php_sdl_rwops_ce) == FAILURE) {
		return;
	}
	FETCH_RWOPS(rwops, z_rwops, 1);

	RETURN_LONG(SDL_ReadBE64(rwops));
}
/* }}} */
#endif

/* {{{ proto int SDL_WriteU8(SDL_RWops area, int value)

 *  \name Write endian functions
 *
 *  Write an item of native format to the specified endianness.
 extern DECLSPEC size_t SDLCALL SDL_WriteU8(SDL_RWops * dst, Uint8 value);
 */
PHP_FUNCTION(SDL_WriteU8)
{
	struct php_sdl_rwops *intern;
	zend_long value;
	zval *z_rwops;
	SDL_RWops *rwops;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "Ol", &z_rwops, php_sdl_rwops_ce, &value) == FAILURE) {
		return;
	}
	FETCH_RWOPS(rwops, z_rwops, 1);

	RETURN_LONG(SDL_WriteU8(rwops, (Uint8)value));
}
/* }}} */


/* {{{ proto int SDL_WriteU16LE(SDL_RWops area, int value)

 extern DECLSPEC size_t SDLCALL SDL_WriteU16LE(SDL_RWops * dst, Uint16 value);
 */
PHP_FUNCTION(SDL_WriteU16LE)
{
	struct php_sdl_rwops *intern;
	zend_long value;
	zval *z_rwops;
	SDL_RWops *rwops;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "Ol", &z_rwops, php_sdl_rwops_ce, &value) == FAILURE) {
		return;
	}
	FETCH_RWOPS(rwops, z_rwops, 1);

	RETURN_LONG(SDL_WriteU16LE(rwops, (Uint16)value));
}
/* }}} */



/* {{{ proto int SDL_WriteU16BE(SDL_RWops area, int value)

 extern DECLSPEC size_t SDLCALL SDL_WriteU16BE(SDL_RWops * dst, Uint16 value);
 */
PHP_FUNCTION(SDL_WriteU16BE)
{
	struct php_sdl_rwops *intern;
	zend_long value;
	zval *z_rwops;
	SDL_RWops *rwops;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "Ol", &z_rwops, php_sdl_rwops_ce, &value) == FAILURE) {
		return;
	}
	FETCH_RWOPS(rwops, z_rwops, 1);

	RETURN_LONG(SDL_WriteU16BE(rwops, (Uint16)value));
}
/* }}} */


/* {{{ proto int SDL_WriteU32LE(SDL_RWops area, int value)

 extern DECLSPEC size_t SDLCALL SDL_WriteU32LE(SDL_RWops * dst, Uint32 value);
 */
PHP_FUNCTION(SDL_WriteU32LE)
{
	struct php_sdl_rwops *intern;
	zend_long value;
	zval *z_rwops;
	SDL_RWops *rwops;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "Ol", &z_rwops, php_sdl_rwops_ce, &value) == FAILURE) {
		return;
	}
	FETCH_RWOPS(rwops, z_rwops, 1);

	RETURN_LONG(SDL_WriteU32LE(rwops, (Uint32)value));
}
/* }}} */


/* {{{ proto int SDL_WriteU32BE(SDL_RWops area, int value)

 extern DECLSPEC size_t SDLCALL SDL_WriteU32BE(SDL_RWops * dst, Uint32 value);
 */
PHP_FUNCTION(SDL_WriteU32BE)
{
	struct php_sdl_rwops *intern;
	zend_long value;
	zval *z_rwops;
	SDL_RWops *rwops;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "Ol", &z_rwops, php_sdl_rwops_ce, &value) == FAILURE) {
		return;
	}
	FETCH_RWOPS(rwops, z_rwops, 1);

	RETURN_LONG(SDL_WriteU32BE(rwops, (Uint32)value));
}
/* }}} */


#if SIZEOF_LONG > 4
/* {{{ proto int SDL_WriteLE64(SDL_RWops area, int value)

 extern DECLSPEC size_t SDLCALL SDL_WriteLE64(SDL_RWops * dst, Uint64 value);
 */
PHP_FUNCTION(SDL_WriteLE64)
{
	struct php_sdl_rwops *intern;
	zend_long value;
	zval *z_rwops;
	SDL_RWops *rwops;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "Ol", &z_rwops, php_sdl_rwops_ce, &value) == FAILURE) {
		return;
	}
	FETCH_RWOPS(rwops, z_rwops, 1);

	RETURN_LONG(SDL_WriteLE64(rwops, (Uint64)value));
}
/* }}} */


/* {{{ proto int SDL_WriteBE64(SDL_RWops area, int value)

 extern DECLSPEC size_t SDLCALL SDL_WriteBE64(SDL_RWops * dst, Uint64 value);
 */
PHP_FUNCTION(SDL_WriteBE64)
{
	struct php_sdl_rwops *intern;
	zend_long value;
	zval *z_rwops;
	SDL_RWops *rwops;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "Ol", &z_rwops, php_sdl_rwops_ce, &value) == FAILURE) {
		return;
	}
	FETCH_RWOPS(rwops, z_rwops, 1);

	RETURN_LONG(SDL_WriteBE64(rwops, (Uint64)value));
}
/* }}} */
#endif


/* generic arginfo */
ZEND_BEGIN_ARG_INFO_EX(arginfo_rwops_none, 0, 0, 0)
ZEND_END_ARG_INFO()


/* {{{ sdl_rwops_methods[] */
static const zend_function_entry php_sdl_rwops_methods[] = {
	PHP_ME(SDL_RWops,        __construct,       arginfo_rwops_none,    ZEND_ACC_CTOR|ZEND_ACC_PUBLIC)
	PHP_ME(SDL_RWops,        __toString,        arginfo_class_SDL_RWops___toString,    ZEND_ACC_PUBLIC)

	/* non-static methods */
	PHP_FALIAS(Free,         SDL_DestroyRW,        arginfo_rwops_none)
	PHP_FALIAS(Size,         SDL_RWsize,        arginfo_rwops_none)
	PHP_FALIAS(Seek,         SDL_RWseek,        arginfo_SDL_RWops_seek)
	PHP_FALIAS(Tell,         SDL_RWtell,        arginfo_rwops_none)
	PHP_FALIAS(Read,         SDL_RWread,        arginfo_SDL_RWops_read)
	PHP_FALIAS(Write,        SDL_RWwrite,       arginfo_SDL_RWops_write)
	PHP_FALIAS(Close,        SDL_RWclose,       arginfo_rwops_none)
	PHP_FALIAS(ReadU8,       SDL_ReadU8,        arginfo_rwops_none)
	PHP_FALIAS(ReadLE16,     SDL_ReadU16LE,      arginfo_rwops_none)
	PHP_FALIAS(ReadBE16,     SDL_ReadU16BE,      arginfo_rwops_none)
	PHP_FALIAS(ReadLE32,     SDL_ReadU32LE,      arginfo_rwops_none)
	PHP_FALIAS(ReadBE32,     SDL_ReadU32BE,      arginfo_rwops_none)
#if SIZEOF_LONG > 4
	PHP_FALIAS(ReadLE64,     SDL_ReadLE64,      arginfo_rwops_none)
	PHP_FALIAS(ReadBE64,     SDL_ReadBE64,      arginfo_rwops_none)
#endif
	PHP_FALIAS(WriteU8,      SDL_WriteU8,       arginfo_SDL_RWops_writeint)
	PHP_FALIAS(WriteLE16,    SDL_WriteU16LE,     arginfo_SDL_RWops_writeint)
	PHP_FALIAS(WriteBE16,    SDL_WriteU16BE,     arginfo_SDL_RWops_writeint)
	PHP_FALIAS(WriteLE32,    SDL_WriteU32LE,     arginfo_SDL_RWops_writeint)
	PHP_FALIAS(WriteBE32,    SDL_WriteU32BE,     arginfo_SDL_RWops_writeint)
#if SIZEOF_LONG > 4
	PHP_FALIAS(WriteLE64,    SDL_WriteU32LE,     arginfo_SDL_RWops_writeint)
	PHP_FALIAS(WriteBE64,    SDL_WriteU32BE,     arginfo_SDL_RWops_writeint)
#endif

	/* static methods */
	ZEND_FENTRY(FromFile,      ZEND_FN(SDL_RWFromFile),      arginfo_SDL_RWFromFile,      ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_FENTRY(FromMem,       ZEND_FN(SDL_RWFromMem),       arginfo_SDL_RWFromMem,       ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_FENTRY(FromConstMem,  ZEND_FN(SDL_RWFromConstMem),  arginfo_SDL_RWFromConstMem,  ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)

	PHP_FE_END
};
/* }}} */

#define REGISTER_RWOPS_CLASS_CONST_LONG(const_name, value) \
	REGISTER_LONG_CONSTANT("SDL_" const_name, value, CONST_CS | CONST_PERSISTENT); \
	zend_declare_class_constant_long(php_sdl_rwops_ce, ZEND_STRL(const_name), value)


/* {{{ MINIT */
PHP_MINIT_FUNCTION(sdl_rwops)
{
	zend_class_entry ce_rwops;

	INIT_CLASS_ENTRY(ce_rwops, "SDL_RWops", php_sdl_rwops_methods);
	ce_rwops.create_object = php_sdl_rwops_new;
	php_sdl_rwops_ce = zend_register_internal_class(&ce_rwops);
	memcpy(&php_sdl_rwops_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
	php_sdl_rwops_handlers.free_obj = php_sdl_rwops_free;

	zend_declare_property_long(php_sdl_rwops_ce, ZEND_STRL("type"), 0, ZEND_ACC_PUBLIC);

	/* RWops Types */
	REGISTER_RWOPS_CLASS_CONST_LONG("UNKNOWN",        SDL_RWOPS_UNKNOWN);
	REGISTER_RWOPS_CLASS_CONST_LONG("WINFILE",        SDL_RWOPS_WINFILE);
	REGISTER_RWOPS_CLASS_CONST_LONG("STDFILE",        SDL_RWOPS_STDFILE);
	REGISTER_RWOPS_CLASS_CONST_LONG("JNIFILE",        SDL_RWOPS_JNIFILE);
	REGISTER_RWOPS_CLASS_CONST_LONG("MEMORY",         SDL_RWOPS_MEMORY);
	REGISTER_RWOPS_CLASS_CONST_LONG("MEMORY_RO",      SDL_RWOPS_MEMORY_RO);

	REGISTER_LONG_CONSTANT("RW_SEEK_SET",    SDL_RW_SEEK_SET, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("RW_SEEK_CUR",    SDL_RW_SEEK_CUR, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("RW_SEEK_END",    SDL_RW_SEEK_END, CONST_CS | CONST_PERSISTENT);

	return SUCCESS;
}
/* }}} */