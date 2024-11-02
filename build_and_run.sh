#!/usr/bin/env bash
set -xe

GAME=bambam.c

EXE=$(basename $GAME .c)

cc $GAME -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -o $EXE\
   && LIBGL_ALWAYS_SOFTWARE=true ./$EXE\
   && rm -v ./$EXE
