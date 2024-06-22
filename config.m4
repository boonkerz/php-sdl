dnl config.m4 for the PHP SDL extension_LIBAD

PHP_ARG_ENABLE([sdl], 
    [whether to enable PHP-SDL debug support],
    [AS_HELP_STRING([--enable-sdl],
      [Enable SDL debug support])],
      [no])

if test "$PHP_SDL" != "no"; then
  AC_DEFINE(HAVE_SDL, 1, [Whether SDL support is enabled])

  SDL_SOURCE_FILES = "php_sdl.c version.c sdl.c messagebox.c window.c video.c glcontext.c rect.c mouse.c surface.c pixels.c iostream.c render.c event.c ttf_font.c ttf.c"

  PHP_NEW_EXTENSION(sdl, $SDL_SOURCE_FILES, $ext_shared)
fi
