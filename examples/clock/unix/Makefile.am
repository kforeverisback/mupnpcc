noinst_PROGRAMS = upnpclock

AM_CPPFLAGS = -I$(top_srcdir)/include -I../ -I../../common @XML_CFLAGS@ @GTK_CFLAGS@ @GDK_IMLIB_CFLAGS@

noinst_HEADERS = \
	../../common/InputUtil.h

upnpclock_SOURCES = \
	ClockMain.cpp \
	../Clock.cpp \
	../ClockDevice.cpp \
	../../common/InputUtil.cpp

upnpclock_LDADD = ../../../lib/unix/libmupnp++.a @XML_LIBS@ @GTK_LIBS@ @GDK_IMLIB_LIBS@

