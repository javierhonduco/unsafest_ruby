#!/usr/bin/env ruby
require 'mkmf'

$CFLAGS = '-Werror -Wall'
create_makefile 'unsafest_ruby'
