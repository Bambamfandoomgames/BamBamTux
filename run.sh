#!/usr/bin/env bash
set -xe

GAME=bambam

if [ -f $GAME ]; then
    LIBGL_ALWAYS_SOFTWARE=true ./$GAME
else
    echo "ERROR: game not found!"
fi
