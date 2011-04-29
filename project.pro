#
#  window.h
#  Gray-Scott Reaction Diffusion system.
#
#  Main window.
#
#  Created by radix on 04/29/11.
#  Copyright Mykola Konyk, <mykola@konyk.org>, 2011.
#  
#  This code is under Microsoft Reciprocal License (Ms-RL)
#  Please see http://www.opensource.org/licenses/ms-rl.html
#
#  Important points about the license (from Ms-RL):
#
#  [A] For any file you distribute that contains code from the software (in source code or binary format), you must provide 
#  recipients the source code to that file along with a copy of this license, which license will govern that file. 
#  You may license other files that are entirely your own work and do not contain code from the software under any terms 
#  you choose.
#
#  [B] No Trademark License- This license does not grant you rights to use any contributors' name, logo, or trademarks.
#
#  [C] If you bring a patent claim against any contributor over patents that you claim are infringed by the software, your 
#  patent license from such contributor to the software ends automatically.
#
#  [D] If you distribute any portion of the software, you must retain all copyright, patent, trademark, and attribution notices 
#  that are present in the software.
#
#  [E] If you distribute any portion of the software in source code form, you may do so only under this license by including a
#  complete copy of this license with your distribution. If you distribute any portion of the software in compiled or object 
#  code form, you may only do so under a license that complies with this license.
#
#  [F] The software is licensed "as-is." You bear the risk of using it. The contributors give no express warranties, guarantees 
#  or conditions. You may have additional consumer rights under your local laws which this license cannot change. To the extent 
#  permitted under your local laws, the contributors exclude the implied warranties of merchantability, fitness for a #particular 
#  purpose and non-infringement.
#
#

win32:TEMPLATE = vcapp
unix:TEMPLATE = app

CONFIG += qt debug_and_release thread

QT += gui core opengl

#QMAKE_LFLAGS += -m32 -L/usr/lib32/qt4 -L/usr/local/lib32
#QMAKE_LFLAGS += -L/usr/lib -L/usr/local/lib

unix:QMAKE_LFLAGS += -L/usr/lib -L/usr/local/lib

win32 {

	RC_FILE = project.rc


	# Fix Qt complaining about arch not found (related to adding a resource file?).
	contains(QMAKE_HOST.arch, x86):{
		QMAKE_LFLAGS *= /MACHINE:X86
	}

	contains(QMAKE_HOST.arch, x86_64):{
		QMAKE_LFLAGS *= /MACHINE:X64
	}
}
#macx {
#	ICON = core.icns
#}

win32 {

	 # [rad] We include GLEW's source files, so static linkage.
	 DEFINES += GLEW_STATIC

     CONFIG(debug, debug|release) {
          #LIBS += -lglew32d
     }
     else {
          #LIBS += -lglew32
     }
}
unix {

LIBS += -framework GLUT
      
}

INCLUDEPATH += include
SOURCEPATH = src
FORMSPATH = ui

HEADERS += \
		$${INCLUDEPATH}/window.h \
		$${INCLUDEPATH}/concentrationu.h \
		$${INCLUDEPATH}/concentrationv.h \
		$${INCLUDEPATH}/render.h \
		$${INCLUDEPATH}/framebuffer.h

SOURCES += \
		$${SOURCEPATH}/core.cpp \
		$${SOURCEPATH}/window.cpp \
		$${SOURCEPATH}/concentrationu.cpp \
		$${SOURCEPATH}/concentrationv.cpp \
		$${SOURCEPATH}/render.cpp \
		$${SOURCEPATH}/framebuffer.cpp

win32 {

HEADERS += \
		$${INCLUDEPATH}/GL/glew.h \
		$${INCLUDEPATH}/GL/wglew.h \
		$${INCLUDEPATH}/GL/glut.h

SOURCES += \
		$${SOURCEPATH}/glew.c
}


FORMS += \
		$${FORMSPATH}/concentrationu.ui \
		$${FORMSPATH}/concentrationv.ui \
		$${FORMSPATH}/render.ui

RESOURCES = project.qrc
  
TARGET = reaction_diffusion

DESTDIR = bin
