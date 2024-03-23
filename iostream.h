#ifndef PHP_SRC_IOSTREAM_H
#define PHP_SRC_IOSTREAM_H

zend_class_entry *get_php_sdl_iostream_ce(void);
zend_bool  sdl_iostream_to_zval(SDL_IOStream *iostram, zval *z_val, Uint32 flags, char *buf);
SDL_IOStream *zval_to_sdl_iostream(zval *z_val);
void php_stream_to_zval_iostream(php_stream *stream, zval *return_value, int autoclose);

PHP_MINIT_FUNCTION(sdl_iostream);

#endif //PHP_SRC_IOSTREAM_H
