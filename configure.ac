############################################################
#
#	mUPnP for C++
#
#	Copyright (C) Satoshi Konno 2003-2013
#
############################################################

AC_CONFIG_AUX_DIR(config)
AM_CONFIG_HEADER(config.h)

AC_INIT([mupnp++], [1.0])
AC_CONFIG_SRCDIR([include/mupnp/mUPnP.h])
AM_INIT_AUTOMAKE([subdir-objects])

##############################
# Constants
##############################

# GTK version.
GTK_VERSION=1.2.0
GDK_IMLIB_VERSION=1.9.0

# Xerces version.
XERCES_VERSION=2.3.0

# Expat version.
EXPAT_VERSION=1.95

# Libxml2 version.
LIBXML2_VERSION=2.6.20

##############################
# Checks for programs.
##############################

AC_PROG_CC
AC_PROG_CXX
AC_PROG_CPP
AC_PROG_INSTALL
AC_PROG_AWK
AC_PROG_RANLIB
AC_LANG_CPLUSPLUS

##############################
#Checks for CYGWIN an MinGW
##############################

#AC_CYGWIN
#if [ test $CYGWIN = yes || test $MINGW = yes ]; then
  #AC_LIBTOOL_WIN32_DLL
  #AM_DISABLE_STATIC
  #AC_PROG_LIBTOOL
  AC_CHECK_LIB([ws2_32],[main])
  #AC_CHECK_LIB([iphlpapi],[main])
#fi

##############################
# Checks for header files.
##############################

AC_HEADER_STDC
AC_CHECK_HEADERS([arpa/inet.h limits.h netdb.h netinet/in.h stdlib.h string.h sys/param.h sys/socket.h unistd.h])

##############################
# Checks for uHTTP libraries.
##############################

AC_CHECK_LIB([uhttp++],[main],,[AC_MSG_ERROR(mUPnP needs uHTTP for C++)])

##############################
# Checks for Xerces C++ libraries.
##############################

AC_ARG_ENABLE(xercescc,
	[  --enable-xercescc	enable Xerces C++ support [default=no]],
	[
		if test $enableval = yes; then
			USE_XERCESCC=yes
		else
			USE_XERCESCC=no
		fi
	],[
		USE_XERCESCC=no
	]
)

if [ test $USE_XERCESCC = yes ]; then
	AC_CHECK_HEADERS([xercesc/util/XercesVersion.hpp],,[AC_MSG_ERROR(mUPnP needs Apache Xerces C++ $XERCES_VERSION later)])
	AC_CHECK_LIB([xerces-c],[main])
fi

##############################
# Checks for Expat libraries.
##############################

AC_ARG_ENABLE(expat,
        [  --enable-expat       enable Expat support [default=no]],
        [
                if test $enableval = yes; then
                        USE_EXPAT=yes
                else
                        USE_EXPAT=no
                fi
        ],[
                USE_EXPAT=no
        ]
)

if [ test $USE_EXPAT = yes ]; then
        AC_CHECK_HEADERS([expat.h],,[AC_MSG_ERROR(mUPnP needs Expat $EXPAT_VERSION later)])
        AC_CHECK_LIB([expat],[main])
        AC_DEFINE([USE_XMLPARSER_EXPAT],1,[EXPAT])
fi

##############################
# Checks for libxml2 libraries.
##############################

AC_ARG_ENABLE(libxml2,
	[  --enable-libxml2	enable Libxml2 support [default=no]],
	[
		if test $enableval = yes; then
			USE_LIBXML2=yes
		else
			USE_LIBXML2=no
		fi
	],[
		USE_LIBXML2=no
	]
)

if [ test $USE_LIBXML2 = yes ]; then
	AC_CHECK_PROG(XML2_CONFIG, xml2-config, yes, no)
	if [ test $XML2_CONFIG = yes ]; then
		AC_DEFINE([USE_XMLPARSER_LIBXML2],1,[LIBXML2])
		XML_CFLAGS=`xml2-config --cflags`
		XML_LIBS=`xml2-config --libs`
		AC_SUBST(XML_CFLAGS)
		AC_SUBST(XML_LIBS)
	else
		AC_MSG_ERROR(mUPnP needs libxml2 $LIBXML2_VERSION later)
	fi
fi

##############################
# Checks for default XML parser
##############################

if [ test $USE_LIBXML2 != yes ]; then
if [ test $USE_EXPAT != yes ]; then
if [ test $USE_XERCESCC != yes ]; then
	AC_DEFINE([USE_XMLPARSER_LIBXML2],1,[LIBXML2])
	XML_CFLAGS=`xml2-config --cflags`
	XML_LIBS=`xml2-config --libs`
	AC_SUBST(XML_CFLAGS)
	AC_SUBST(XML_LIBS)
fi
fi
fi

##############################
# Checks for xUnit
##############################

AC_ARG_ENABLE([tests], AC_HELP_STRING([--enable-tests], [ build tests (default = no) ]), [build_tests="yes"], [])
AM_CONDITIONAL(UNITTESTS,test "$build_tests" = yes)
if [ test "$build_tests" = yes ]; then
	AC_CHECK_LIB([boost_unit_test_framework-mt],[main],,[AC_MSG_ERROR(uHTTP unittests need boost::unit_test_framework)])
	AC_CHECK_LIB([boost_system-mt],[main],,[AC_MSG_ERROR(uHTTP unittests need boost::system)])
	AC_CHECK_LIB([boost_filesystem-mt],[main],,[AC_MSG_ERROR(uHTTP unittests need boost::filesystem)])
fi

##############################
# Checks for iconv
##############################

AC_CHECK_FUNCS([iconv])
AC_CHECK_HEADERS([iconv.h])
AC_CHECK_LIB([iconv],[main])

##############################
# Checks for pthread
##############################

AC_CHECK_HEADERS([pthread.h],,[AC_MSG_ERROR(mUPnP needs POSIX thread library)])
AC_CHECK_LIB([pthread],[main])

##############################
# Checks for GTK libraries.
##############################

AC_CHECK_PROG(GTK_CONFIG, gtk-config, yes, no)
#if [ test $GTK_CONFIG = yes ]; then
#	AM_PATH_GTK([$GTK_VERSION],[AC_DEFINE([HAVE_GTK],1,[GTK])],)
# 	AM_PATH_GDK_IMLIB($GDK_IMLIB_VERSION,[AC_DEFINE([HAVE_GDK_IMLIB],1,[GDK_IMLIB])],)
#else
	GTK_CFLAGS=
	GDK_IMLIB_CFLAGS=
	GTK_LIBS=
	GDK_IMLIB_LIBS=
	AC_SUBST(GTK_CFLAGS)
	AC_SUBST(GDK_IMLIB_CFLAGS)
	AC_SUBST(GTK_LIBS)
	AC_SUBST(GDK_IMLIB_LIBS)
#fi

##############################
# Checks for UUID
##############################

AC_CHECK_LIB([uuid],[main])
AC_CHECK_HEADERS([uuid/uuid.h])

##############################
# Checks for typedefs, structures, and compiler characteristics.
##############################

#AC_HEADER_STDBOOL
AC_C_CONST
AC_C_INLINE
AC_STRUCT_TM

##############################
# Checks for shared_ptr
##############################

AC_MSG_CHECKING(for std::shared_ptr)
AC_TRY_COMPILE([
#include <iostream>
void testFunc(){
std::shared_ptr<int> p(new int(0));
}
],
[],
[AC_MSG_RESULT(yes)
AC_DEFINE([HAVE_STD_SHRAEDPTR],1,[HAVE_STD_SHAREDPTR])],
[AC_MSG_RESULT(no)]
)

AC_MSG_CHECKING(for boost::shared_ptr)
AC_TRY_COMPILE([
#include <boost/shared_ptr.hpp>
void testFunc(){
boost::shared_ptr<int> p(new int(0));
}
],
[],
[AC_MSG_RESULT(yes)
AC_DEFINE([HAVE_BOOST_SHRAEDPTR],1,[HAVE_BOOST_SHAREDPTR])],
[AC_MSG_RESULT(no)]
)

##############################
# Checks for Network functions
##############################

AC_CHECK_FUNCS([socket])
AC_CHECK_FUNCS([inet_ntoa])
AC_CHECK_HEADERS([ifaddrs.h])
AC_CHECK_FUNCS([getifaddrs])

AC_MSG_CHECKING(for socklen_t)
AC_TRY_COMPILE([
#include <sys/types.h>
#include <sys/socket.h>
socklen_t foosocket;
],
[],
[AC_MSG_RESULT(yes)
AC_DEFINE([HAVE_SOCKLEN_T],1,[SOCKLEN_T])],
[AC_MSG_RESULT(no)]
)

##############################
# Checks for C++ stream.
##############################

AC_CHECK_HEADERS([sstream])

AC_MSG_CHECKING(for std::cout)
AC_TRY_COMPILE([
#include <iostream>
void testFunc(){
std::cout << "" << std::endl;
}
],
[],
[AC_MSG_RESULT(yes)
AC_DEFINE([HAVE_STD_COUT],1,[STD_COUT])],
[AC_MSG_RESULT(no)]
)

##############################
# Checks for other functions.
##############################

AC_CHECK_FUNCS([fopen])
AC_CHECK_FUNCS([memset])
AC_CHECK_FUNCS([realpath])
AC_CHECK_FUNCS([localtime_r])
AC_CHECK_FUNCS([gmtime_r])
AC_CHECK_FUNCS([snprintf])
AC_CHECK_FUNCS([strchr])
AC_CHECK_FUNCS([uname])

##############################
# Makefiles
##############################

AC_OUTPUT([
Makefile
include/Makefile
lib/Makefile
lib/unix/Makefile
examples/Makefile
examples/upnpdump/Makefile
examples/upnpdump/unix/Makefile
examples/clock/Makefile
examples/clock/unix/Makefile
examples/tv/Makefile
examples/tv/unix/Makefile
tests/Makefile
tests/unix/Makefile
])
