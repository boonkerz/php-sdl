#ifndef SDL_ARGINFO_H
#define SDL_ARGINFO_H

#include "version.h"
#include "sdl.h"
#include "messagebox.h"
#include "window.h"
#include "video.h"
#include "glcontext.h"
#include "surface.h"
#include "rect.h"
#include "shape.h"


static const zend_function_entry sdl_functions[] = {
    // Core
    ZEND_FE(SDL_Init,						arginfo_SDL_Init)
    ZEND_FE(SDL_InitSubSystem,				arginfo_SDL_InitSubSystem)
    ZEND_FE(SDL_Quit,						arginfo_SDL_Quit)
    ZEND_FE(SDL_QuitSubSystem,				arginfo_SDL_QuitSubSystem)
    ZEND_FE(SDL_WasInit,					arginfo_SDL_WasInit)
    ZEND_FE(SDL_SetHint,					arginfo_SDL_SetHint)

	// Window
	ZEND_FE(SDL_CreateWindow, arginfo_SDL_CreateWindow)
	ZEND_FE(SDL_CreateShapedWindow, arginfo_SDL_CreateWindow)
	ZEND_FE(SDL_DestroyWindow, arginfo_SDL_Window)
	ZEND_FE(SDL_UpdateWindowSurface, arginfo_SDL_Window)
	ZEND_FE(SDL_GetWindowTitle, arginfo_SDL_Window)
	ZEND_FE(SDL_SetWindowTitle, arginfo_SDL_SetWindowTitle)
	ZEND_FE(SDL_GetWindowDisplayIndex, arginfo_SDL_Window)
	ZEND_FE(SDL_ShowWindow, arginfo_SDL_Window)
	ZEND_FE(SDL_HideWindow, arginfo_SDL_Window)
	ZEND_FE(SDL_RaiseWindow, arginfo_SDL_Window)
	ZEND_FE(SDL_MaximizeWindow, arginfo_SDL_Window)
	ZEND_FE(SDL_MinimizeWindow, arginfo_SDL_Window)
	ZEND_FE(SDL_RestoreWindow, arginfo_SDL_Window)
	ZEND_FE(SDL_GetWindowSurface, arginfo_SDL_Window)
	ZEND_FE(SDL_SetWindowDisplayMode, arginfo_SDL_SetWindowDisplayMode)
	ZEND_FE(SDL_GetWindowDisplayMode, arginfo_SDL_GetWindowDisplayMode)
	ZEND_FE(SDL_GetWindowPixelFormat, arginfo_SDL_Window)
	ZEND_FE(SDL_GetWindowID, arginfo_SDL_Window)
	ZEND_FE(SDL_GetWindowFlags, arginfo_SDL_Window)
	ZEND_FE(SDL_SetWindowIcon, arginfo_SDL_SetWindowIcon)
	ZEND_FE(SDL_SetWindowPosition, arginfo_SDL_SetWindowPosition)
	ZEND_FE(SDL_GetWindowPosition, arginfo_SDL_GetWindowPosition)
	ZEND_FE(SDL_SetWindowSize, arginfo_SDL_SetWindowPosition)
	ZEND_FE(SDL_GetWindowSize, arginfo_SDL_GetWindowPosition)
	ZEND_FE(SDL_SetWindowMinimumSize, arginfo_SDL_SetWindowPosition)
	ZEND_FE(SDL_GetWindowMinimumSize, arginfo_SDL_GetWindowPosition)
	ZEND_FE(SDL_SetWindowMaximumSize, arginfo_SDL_SetWindowPosition)
	ZEND_FE(SDL_GetWindowMaximumSize, arginfo_SDL_GetWindowPosition)
	ZEND_FE(SDL_SetWindowBordered, arginfo_SDL_SetWindowBordered)
	ZEND_FE(SDL_SetWindowFullscreen, arginfo_SDL_SetWindowFullscreen)
	ZEND_FE(SDL_UpdateWindowSurfaceRects, arginfo_SDL_UpdateWindowSurfaceRects)
	ZEND_FE(SDL_SetWindowGrab, arginfo_SDL_SetWindowGrab)
	ZEND_FE(SDL_GetWindowGrab, arginfo_SDL_Window)
	ZEND_FE(SDL_SetWindowBrightness, arginfo_SDL_SetWindowBrightness)
	ZEND_FE(SDL_GetWindowBrightness, arginfo_SDL_Window)
	ZEND_FE(SDL_GetWindowGammaRamp, arginfo_SDL_GetWindowGammaRamp)
	ZEND_FE(SDL_IsShapedWindow, arginfo_SDL_Window)
	ZEND_FE(SDL_SetWindowShape, arginfo_SDL_SetWindowShape)
	ZEND_FE(SDL_GetShapedWindowMode, arginfo_SDL_GetShapedWindowMode)

	ZEND_FE(SDL_WINDOWPOS_UNDEFINED_DISPLAY, arginfo_SDL_WINDOWPOS_DISPLAY)
	ZEND_FE(SDL_WINDOWPOS_CENTERED_DISPLAY, arginfo_SDL_WINDOWPOS_DISPLAY)

	// Video
	ZEND_FE(SDL_GetNumVideoDrivers, arginfo_video_none)
	ZEND_FE(SDL_GetVideoDriver, arginfo_SDL_GetVideoDriver)
	ZEND_FE(SDL_VideoInit, arginfo_SDL_VideoInit)
	ZEND_FE(SDL_VideoQuit, arginfo_video_none)
	ZEND_FE(SDL_GetCurrentVideoDriver, arginfo_video_none)
	ZEND_FE(SDL_GetNumVideoDisplays, arginfo_video_none)
	ZEND_FE(SDL_GetDisplayName, arginfo_SDL_dysplayindex)
	ZEND_FE(SDL_GetDisplayBounds, arginfo_SDL_GetDisplayBounds)
	ZEND_FE(SDL_GetNumDisplayModes, arginfo_SDL_dysplayindex)
	ZEND_FE(SDL_GetDisplayMode, arginfo_SDL_GetDisplayMode)
	ZEND_FE(SDL_GetClosestDisplayMode, arginfo_SDL_GetClosestDisplayMode)
	ZEND_FE(SDL_IsScreenSaverEnabled, arginfo_video_none)
	ZEND_FE(SDL_EnableScreenSaver, arginfo_video_none)
	ZEND_FE(SDL_DisableScreenSaver, arginfo_video_none)

	// GL
	ZEND_FE(SDL_GL_ExtensionSupported, arginfo_SDL_GL_ExtensionSupported)
	ZEND_FE(SDL_GL_SetAttribute, arginfo_SDL_GL_SetAttribute)
	ZEND_FE(SDL_GL_GetAttribute, arginfo_SDL_GL_GetAttribute)
	ZEND_FE(SDL_GL_CreateContext, arginfo_SDL_GLContext__construct)
	ZEND_FE(SDL_GL_DeleteContext, arginfo_SDL_GL_DeleteContext)
	ZEND_FE(SDL_GL_MakeCurrent, arginfo_SDL_GL_MakeCurrent)
	ZEND_FE(SDL_GL_GetCurrentWindow, arginfo_none)
	ZEND_FE(SDL_GL_GetCurrentContext, arginfo_none)
	ZEND_FE(SDL_GL_GetDrawableSize, arginfo_SDL_GL_GetDrawableSize)
	ZEND_FE(SDL_GL_SwapWindow, arginfo_SDL_Window)
	ZEND_FE(SDL_GL_SetSwapInterval, arginfo_SDL_GL_SetSwapInterval)
	ZEND_FE(SDL_GL_GetSwapInterval, arginfo_none)

	// Mouse/Cursor
	ZEND_FE(SDL_CreateCursor, arginfo_SDL_Cursor__construct)
	ZEND_FE(SDL_CreateSystemCursor, arginfo_SDL_CreateSystemCursor)
	ZEND_FE(SDL_CreateColorCursor, arginfo_SDL_CreateColorCursor)
	ZEND_FE(SDL_FreeCursor, arginfo_SDL_Cursor)
	ZEND_FE(SDL_SetCursor, arginfo_SDL_Cursor)
	ZEND_FE(SDL_GetCursor, arginfo_none)
	ZEND_FE(SDL_GetDefaultCursor, arginfo_none)
	ZEND_FE(SDL_ShowCursor, arginfo_SDL_ShowCursor)
	ZEND_FE(SDL_GetMouseFocus, arginfo_none)
	ZEND_FE(SDL_GetMouseState, arginfo_SDL_GetMouseState)
	ZEND_FE(SDL_GetRelativeMouseState, arginfo_SDL_GetMouseState)
	ZEND_FE(SDL_WarpMouseInWindow, arginfo_SDL_WarpMouseInWindow)
	ZEND_FE(SDL_SetRelativeMouseMode, arginfo_SDL_SetRelativeMouseMode)
	ZEND_FE(SDL_GetRelativeMouseMode, arginfo_none)

	// Surface
	ZEND_FE(SDL_CreateRGBSurface, arginfo_SDL_CreateRGBSurface)
	ZEND_FE(SDL_FreeSurface, arginfo_SDL_Surface)
	ZEND_FE(SDL_FillRect, arginfo_SDL_FillRect)
	ZEND_FE(SDL_FillRects, arginfo_SDL_FillRects)
	ZEND_FE(SDL_MUSTLOCK, arginfo_SDL_Surface)
	ZEND_FE(SDL_LockSurface, arginfo_SDL_Surface)
	ZEND_FE(SDL_UnlockSurface, arginfo_SDL_Surface)
	ZEND_FE(SDL_LoadBMP_RW, arginfo_SDL_LoadBMP_RW)
	ZEND_FE(SDL_LoadBMP, arginfo_SDL_LoadBMP)
	ZEND_FE(SDL_UpperBlit, arginfo_SDL_UpperBlit)
	ZEND_FE(SDL_LowerBlit, arginfo_SDL_LowerBlit)
	ZEND_FE(SDL_UpperBlitScaled, arginfo_SDL_UpperBlit)
	ZEND_FE(SDL_LowerBlitScaled, arginfo_SDL_LowerBlit)
	ZEND_FE(SDL_SoftStretch, arginfo_SDL_UpperBlit)
	ZEND_FE(SDL_SaveBMP_RW, arginfo_SDL_SaveBMP_RW)
	ZEND_FE(SDL_SaveBMP, arginfo_SDL_SaveBMP)
	ZEND_FE(SDL_SetSurfaceRLE, arginfo_SDL_SetSurfaceRLE)
	ZEND_FE(SDL_SetColorKey, arginfo_SDL_SetColorKey)
	ZEND_FE(SDL_GetColorKey, arginfo_SDL_GetColorKey)
	ZEND_FE(SDL_SetSurfaceColorMod, arginfo_SDL_SetSurfaceColorMod)
	ZEND_FE(SDL_GetSurfaceColorMod, arginfo_SDL_GetSurfaceColorMod)
	ZEND_FE(SDL_SetSurfaceAlphaMod, arginfo_SDL_SetSurfaceAlphaMod)
	ZEND_FE(SDL_GetSurfaceAlphaMod, arginfo_SDL_GetSurfaceAlphaMod)
	ZEND_FE(SDL_SetSurfaceBlendMode, arginfo_SDL_SetSurfaceBlendMode)
	ZEND_FE(SDL_GetSurfaceBlendMode, arginfo_SDL_GetSurfaceBlendMode)
	ZEND_FE(SDL_SetClipRect, arginfo_SDL_SetClipRect)
	ZEND_FE(SDL_GetClipRect, arginfo_SDL_GetClipRect)
	ZEND_FE(SDL_ConvertSurface, arginfo_SDL_ConvertSurface)
	ZEND_FE(SDL_ConvertSurfaceFormat, arginfo_SDL_ConvertSurfaceFormat)
	ZEND_FE(SDL_ConvertPixels, arginfo_SDL_ConvertPixels)

	// Message box
	ZEND_FE(SDL_ShowSimpleMessageBox, arginfo_SDL_ShowSimpleMessageBox)
	ZEND_FE(SDL_ShowMessageBox, arginfo_SDL_ShowMessageBox)


    // Version
    ZEND_FE(SDL_GetVersion, arginfo_SDL_GetVersion)
    PHP_FE_END
};

#endif //SDL_ARGINFO_H
