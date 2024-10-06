#!/bin/sh

echo "Start environment configuration..."

PREFIX=/usr/local
DIR_BIN=${PREFIX}/bin
DIR_INC=${PREFIX}/include
DIR_LIB=${PREFIX}/lib

# Boost
echo "Searching boost libraries..."
BOOST_ROOT_DIR="/usr/local/include"
BOOST_CHECK_DIR=$BOOST_ROOT_DIR/boost
if [ -d $BOOST_CHECK_DIR ]
 then
     echo "Boost directory found: ${BOOST_CHECK_DIR}"
 else
	 echo ""
	 echo "Error!"
     echo "Boost directory not found! (${BOOST_CHECK_DIR})"
	 echo "Install boost-libs package!"
	 exit 1
 fi
 
 # wxWidgets
 echo "Searching wxWidgets library..."
 WX_CONFIG_FILE_NAME=`ls ${DIR_BIN} | grep wxgtk3u-...-config$ | sort -r | head -1`
 if [ -z $WX_CONFIG_FILE_NAME ]
  then
      echo ""
	  echo "Error!"
      echo "Configuration file of wxWidgets not found."
	  echo "Install wxWidgets first (wx30)."
	  exit 1
  else
	  echo "wx-config file found: ${WX_CONFIG_FILE_NAME}"
  fi
  
  WX_WIDGETS_CXX_FLAGS=`${WX_CONFIG_FILE_NAME} --cxxflags`
  WX_WIDGETS_LIBS_FLAGS=`${WX_CONFIG_FILE_NAME} --libs all`
  
  echo "WX_WIDGETS_CXX_FLAGS = ${WX_WIDGETS_CXX_FLAGS}"
  echo "WX_WIDGETS_LIBS_FLAGS = ${WX_WIDGETS_LIBS_FLAGS}"

  
# OpenCASCADE
OPENCASCADE_ROOT_DIR=${DIR_INC}/OpenCASCADE
OPENCASCADE_INCLUDE_DIRS=${DIR_INC}/OpenCASCADE
if [ -d $OPENCASCADE_INCLUDE_DIRS ]
 then
     echo "OpenCASCADE directory found: ${OPENCASCADE_INCLUDE_DIRS}"
 else
	 echo ""
	 echo "Error!"
     echo "OpenCASCADE directory not found! (${OPENCASCADE_INCLUDE_DIRS})"
	 echo "Install OpenCASCADE package!"
	 exit 1
 fi

OPENCASCADE_LIBRARIES=${DIR_LIB}
OPENCASCADE_PKG_LIBS=`pkg info -l opencascade | grep .so$ | cut -d'/' -f 5 | cut -d'.' -f 1`

for line in ${OPENCASCADE_PKG_LIBS}; do
  OPENCASCADE_LIBS_FILES="${OPENCASCADE_LIBS_FILES}-l${line##lib} "
done

 if [ -z OPENCASCADE_LIBS_FILES ]
  then
      echo ""
	  echo "Error!"
      echo "OpenCASCADE libraries not found."
	  echo "Install OpenCASCADE first."
	  exit 1
  else
	  echo "OpenCASCADE files found: ${OPENCASCADE_LIBS_FILES}"
  fi
  

cmake . -DBOOST_ROOT_DIR=$BOOST_ROOT_DIR -DOPENCASCADE_ROOT_DIR=$OPENCASCADE_ROOT_DIR -DOPENCASCADE_INCLUDE_DIRS=$OPENCASCADE_INCLUDE_DIRS -DOPENCASCADE_LIBRARIES=$OPENCASCADE_LIBRARIES -DOPENCASCADE_LIBS_FILES="${OPENCASCADE_LIBS_FILES}" -DWX_WIDGETS_CXX_FLAGS="${WX_WIDGETS_CXX_FLAGS}" -DWX_WIDGETS_LIBS_FLAGS="${WX_WIDGETS_LIBS_FLAGS}"

