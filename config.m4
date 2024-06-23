dnl config.m4 for the PHP SDL extension_LIBAD

PHP_ARG_ENABLE([sdl], 
    [whether to enable PHP-SDL support],
    [AS_HELP_STRING([--enable-sdl],
      [Enable SDL support])],
      [no])

AC_MSG_CHECKING([for os target])
AC_CANONICAL_HOST
build_linux=no
build_mac=no

case "${host_os}" in
  linux*)
      build_linux=yes
      ;;
  darwin*)
      build_mac=yes
      ;;
  *)
      AC_MSG_ERROR(["OS $host_os is not supported"])
      ;;
esac

if test "$build_mac" = "yes"; then
  AC_MSG_RESULT([building for MacOS])
else 
  AC_MSG_RESULT([building for Linux])
fi

if test "$PHP_SDL" != "no"; then
  AC_DEFINE(HAVE_SDL, 1, [Whether SDL support is enabled])

  SDL_SOURCE_FILES="php_sdl.c \
    version.c sdl.c \
    messagebox.c \
    window.c \
    video.c \
    glcontext.c \
    rect.c \
    mouse.c \
    surface.c \
    pixels.c \
    iostream.c \
    render.c \
    event.c \
    ttf_font.c \
    ttf.c"

  PHP_NEW_EXTENSION(sdl, $SDL_SOURCE_FILES, $ext_shared)
fi
