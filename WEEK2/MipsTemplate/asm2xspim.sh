#!/bin/bash

touch debug_xspim.asm
echo " $1 to debug_xspim.asm"

sed '/.file/d' $1 | sed '/.section/d'| sed '/.previous/d' | sed '/.nan/d' | sed '/.gnu_attribute/d' | sed '/.align/d' | sed '/.size/d' | sed '/.set/d' | sed '/.ent/d' | sed '/.type/d' | sed '/.size/d' | sed '/.ident/d' | sed '/.size/d' | sed '/.ident/d' > debug_xspim.asm

echo " xspim debug_xspim.asm -font 6x10"
xspim debug_xspim.asm -font 6x10



