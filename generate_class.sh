#!/bin/bash

header=""
impl=""
nspace="$3"

[ -z $space ] && nspace="FT"

(
    [ ! -z $1 ] && [ ! -z $2 ] \
    && header="\n\nnamespace $nspace {\n"\
    && header=$header"\tclass $2 {\n"\
    && header=$header"\t\tpublic:\n" \
    && header=$header"\t\t\t$2();\n" \
    && header=$header"\t\t\t~$2();\n"\
    && header=$header"\t\t\t$2 ($2 &other);\n"\
    && header=$header"\t\t\t$2& operator=(const $2 &other);\n"\
    && header=$header"\t};\n}\n" \
    && impl="\n\n#include \"$2.hpp\"\n" \
    && impl=$impl"\n$nspace::$2::$2 () {\n}\n\n" \
    && impl=$impl"$nspace::$2::~$2 () {\n}\n\n" \
    && impl=$impl"$nspace::$2::$2 ( $2 &other) {\n\t(void) other;\n\treturn;\n}\n\n"\
    && impl=$impl"$nspace::$2& $nspace::$2::operator= (const $2 & other) {\n\t(void) other;\n\treturn *this;\n}\n\n"\
    && {
            [ ! -d $1 ] && mkdir -p $1
            echo "header generated";
            echo -e $header > $1/$2.hpp;
            echo "implementation generated";
            echo -e $impl > $1/$2.cpp;
        }
) || echo "Usage ./generate_class.sh <directory> <class_name> <namespace_name(optional)>"
