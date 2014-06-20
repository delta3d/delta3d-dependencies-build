#!/bin/bash
#CHANGE these to match your configuration
ODEDIR=$DEV/ext/src/ode-0.12
EXTDIR=$DEV/delta3d
####################################################

PLUGINDIR=$ODEDIR/lib

UNAME=`uname`

if [ $UNAME = Darwin ]; then
  SOEXT=dylib
else
  SOEXT=so
fi

if [ -f $ODEDIR/stage/lib/libode.a ]; then
  rsync -tv $ODEDIR/stage/lib/libode.a $EXTDIR/ext/lib/
fi

mkdir -p $EXTDIR/ext/inc/ode
rsync -tv $ODEDIR/stage/inc/ode/*.h $EXTDIR/ext/inc/ode
