cmake_minimum_required(VERSION 3.0)
project(oslib LANGUAGES C)

set(PROJECT_VERSION 1.0)
set(PROJECT_DESCRIPTION "OldSchool Library (OSLib) MOD 2.11 written in C")

include(GNUInstallDirs)
include(FindPkgConfig)

set(SOURCE_DIR src)
set(SFONT_FILES ${SOURCE_DIR}/sfont.c ${SOURCE_DIR}/sfont.h)

set(SOURCE_FILES ${SFONT_FILES}
		 ${SOURCE_DIR}/oslib.c
		 ${SOURCE_DIR}/vfpu.c 
		 ${SOURCE_DIR}/drawing.c
		 ${SOURCE_DIR}/image.c
		 ${SOURCE_DIR}/palette.c
		 ${SOURCE_DIR}/shape.c 
		 ${SOURCE_DIR}/map.c
		 ${SOURCE_DIR}/messagebox.c
		 ${SOURCE_DIR}/oslHandleLoadNoFailError.c
		 ${SOURCE_DIR}/keys.c
		 ${SOURCE_DIR}/text.c
		 ${SOURCE_DIR}/vram_mgr.c
		 ${SOURCE_DIR}/stub.S
		 ${SOURCE_DIR}/audio/audio.c
		 ${SOURCE_DIR}/audio/bgm.c
		 ${SOURCE_DIR}/audio/mod.c
		 ${SOURCE_DIR}/audio/media.c
		 ${SOURCE_DIR}/usb.c
		 ${SOURCE_DIR}/dialog.c
		 ${SOURCE_DIR}/osk.c
		 ${SOURCE_DIR}/saveload.c
		 ${SOURCE_DIR}/net.c
		 ${SOURCE_DIR}/browser.c
		 ${SOURCE_DIR}/adhoc/pspadhoc.c
		 ${SOURCE_DIR}/vfile/VirtualFile.c
		 ${SOURCE_DIR}/vfile/vfsFile.c
		 ${SOURCE_DIR}/image/oslConvertImageTo.c
		 ${SOURCE_DIR}/image/oslSetImagePixel.c
		 ${SOURCE_DIR}/image/oslGetImagePixel.c
		 ${SOURCE_DIR}/image/oslDrawImage.c
		 ${SOURCE_DIR}/image/oslDrawImageSimple.c
		 ${SOURCE_DIR}/image/oslDrawImageBig.c
		 ${SOURCE_DIR}/image/oslLockImage.c
		 ${SOURCE_DIR}/image/oslMoveImageTo.c
		 ${SOURCE_DIR}/image/oslSwizzleImage.c
		 ${SOURCE_DIR}/image/oslUnswizzleImage.c
		 ${SOURCE_DIR}/image/oslSetDrawBuffer.c
		 ${SOURCE_DIR}/image/oslResetImageProperties.c
		 ${SOURCE_DIR}/image/oslScaleImage.c
		 ${SOURCE_DIR}/gif/dev2gif.c
		 ${SOURCE_DIR}/gif/dgif_lib.c
		 ${SOURCE_DIR}/gif/egif_lib.c
		 ${SOURCE_DIR}/gif/gif_err.c
		 ${SOURCE_DIR}/gif/gifalloc.c
		 ${SOURCE_DIR}/gif/quantize.c
		 ${SOURCE_DIR}/Special/oslLoadImageFilePNG.c
		 ${SOURCE_DIR}/Special/oslWriteImageFilePNG.c
		 ${SOURCE_DIR}/Special/oslLoadImageFileJPG.c
		 ${SOURCE_DIR}/Special/oslLoadImageFileGIF.c
		 ${SOURCE_DIR}/Special/oslLoadImageFile.c
		 ${SOURCE_DIR}/Special/oslWriteImageFile.c
		 ${SOURCE_DIR}/splash/oslShowSplashScreen1.c
		 ${SOURCE_DIR}/splash/oslShowSplashScreen2.c
		 ${SOURCE_DIR}/mem/oslGetRamStatus.c
		 ${SOURCE_DIR}/intraFont/intraFont.c
		 ${SOURCE_DIR}/intraFont/libccc.c
		 )



#----------------------------------------------------------------------------
#	Adddit.cnal libraries
#	---------------------
set(SDK_LIBS -lpspsdk
	-lpspctrl -lpsphprm
	-lpspumd
	-lpsprtc
	-lpspgu -lpspgum
	-lpspaud.clib
	-lpspaud.c -lpspaud.c.cdec
	-lpsp.cwer
	-lpspusb -lpspusbs.cr
	-lpsputility
	-lpspssl -lpsphttp -lpspwlan
	-lpspnet_ad.cc -lpspnet_ad.ccctl
	-lpspnet_ad.ccmatching)

set(EXAMPLE_SOURCE_FILES
	${SAMPLE_DIR}/adhoc
	${SAMPLE_DIR}/dialog
	${SAMPLE_DIR}/helloWorld
	${SAMPLE_DIR}/internetBrowser
	${SAMPLE_DIR}/intraFont
	${SAMPLE_DIR}/net
	${SAMPLE_DIR}/rectAndFonts
	${SAMPLE_DIR}/saveAndLoad
	${SAMPLE_DIR}/sfont
	${SAMPLE_DIR}/OSK
)
pkg_search_module(PNG REQUIRED libpng)
pkg_search_module(JPEG REQUIRED libjpeg)
pkg_search_module(ZLIB REQUIRED zlib)
#pkg_search_module(MIKMOD REQUIRED mikmod)
#pkg_search_module(LIBPSPMATH REQUIRED libpspmath)

# lib.cdfmt library
add_library( ${PROJECT_NAME} SHARED ${SOURCE_FILES} ${INCLUDE_FILES})
target_compile_options( ${PROJECT_NAME} PUBLIC ${PNG_FLAGS} ${JPEG_FLAGS} ${MIKMOD_FLAGS}
	${LIBPSPMATH_FLAGS})
target_include_directories(${PROJECT_NAME} PUBLIC ${PNG_INCLUDEDIR}
	${JPEG_INCLUDEDIR} ${MIKMOD_INCLUDEDIR}
	${SFONT_INCLUDEDIR} ${LIBPSPMATH_INCLUDEDIR}
$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/${SOURCE_DIR}>
			$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}>
			)
target_link_libraries( ${PROJECT_NAME} PUBLIC
	${SFONT_LIBRARIES} ${PNG_LIBRARIES} ${JPEG_LIBRARIES} ${MIKMOD_LIBRARIES} ${LIBPSPMATH_LIBRARIES} )

set(install_prefix "${CMAKE_INSTALL_PREFIX}")
set(install_libdir "${CMAKE_INSTALL_LIBDIR}")
set(install_includedir "${CMAKE_INSTALL_INCLUDEDIR}")

configure_file(${PROJECT_NAME}.pc.in ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.pc @ONLY)

set(ENV{PKG_CONFIG_PATH} "${PROJECT_BINARY_DIR}:$ENV{PKG_CONFIG_PATH}")

install(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME}config
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
	PUBLIC_HEADER DESTINATION
	${CMAKE_INSTALL_INCLUDEDIR}/lib${PROJECT_NAME}
	)

install(FILES ${INCLUDE_FILES} DESTINATION
	${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}/)

install(FILES ${PROJECT_NAME}.pc DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig/)
