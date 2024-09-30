dnl config.m4 for the PHP SDL extension_LIBAD

PHP_ARG_ENABLE([sdl], 
    [whether to enable PHP-SDL support],
    [AS_HELP_STRING([--enable-sdl],
      [Enable SDL support])],
      [no])

PHP_ARG_WITH([sdl-dir],
  [dir of sdl],
  [AS_HELP_STRING([[--with-sdl-dir[=DIR]]],
    [Path to the sdl library directory])], [no], [no])

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

check_for_sdl() {
  for i in /usr/local /usr /opt /opt/homebrew /opt/local; do
    if test -r "$i/include/SDL3/SDL.h"; then
      SDL_DIR=$i
      return 0
    fi
  done
  return 1
}
if test "$PHP_SDL" != "no"; then
  
  AC_MSG_CHECKING([for sdl installation])

  if test "x$PHP_SDL_DIR" != "xno"; then
    if test -r "$PHP_SDL_DIR/include/SDL3/SDL.h"; then
      SDL_DIR=$PHP_SDL_DIR
    else
      check_for_sdl
    fi
  else
    check_for_sdl
  fi

  if test "x$SDL_DIR" = "x"; then
    AC_MSG_ERROR([SDL lib could not be located or build])
  fi

  AC_MSG_RESULT([found in $SDL_DIR ($PHP_LIBDIR)])

  PHP_ADD_LIBRARY_WITH_PATH(SDL3, [$SDL_DIR/lib], SDL_SHARED_LIBADD)
  PHP_ADD_LIBRARY_WITH_PATH(SDL3_ttf, [$SDL_DIR/lib], SDL_SHARED_LIBADD)
  PHP_ADD_LIBRARY_WITH_PATH(SDL3_image, [$SDL_DIR/lib], SDL_SHARED_LIBADD)

  AC_DEFINE(HAVE_SDL, 1, [Whether SDL support is enabled])
  PHP_SUBST(SDL_SHARED_LIBADD)
  SDL_SOURCE_FILES="php_sdl.c \
    version.c sdl.c window.c messagebox.c glcontext.c render.c event.c ttf.c ttf_font.c color.c surface.c rect.c iostream.c image.c"

  PHP_NEW_EXTENSION(sdl, $SDL_SOURCE_FILES, $ext_shared)
  PHP_ADD_INCLUDE([$SDL_DIR/include])
fi
