#!/usr/bin/env python
# encoding: utf-8
# waf script for builduing project
# author: Anton Feldmann 
# Copyright 2016 anton.feldmann@gmail.com
# license: MIT

import os, sys
from waflib import Build, TaskGen

name = 'flogger'

major  = 0
minor  = 1
bugfix = 0

name_version = '%s-%d.%d.%d' % (name, major, minor, bugfix)

application = name
version     = '%d.%d.%d' % (major, minor, bugfix)

top = '.'
out = 'build'

def options(opt):
    opt.load('compiler_cxx')


def configure(conf):
    conf.load('compiler_cxx')

def build(bld):
    # flogger compile
    bld(features     = 'cxx cxxshlib',
	source       = 'src/flogger.cc',
	cxxflags     = ['-Wall','-std=c++11'],
        includes     = ['include'],
        install_path = '${PREFIX}/lib',
	target       = name)
    
    
    # flogger headerfile install
    bld.install_files('${PREFIX}/include/flogger/', bld.path.ant_glob(['include/flogger/*.hpp'], remove=False))

    from waflib import Options
# process flogger.pc.in -> flogger.pc - by default it use the task "env" attribute
    pcf = bld(
        features = 'subst',
        source = '%s.pc.in' % name,
        target = '%s.pc' % name,
        install_path = '${PREFIX}/lib/pkgconfig/'
        )

    pcf.env.table.update(
        {'LIBS':' -l%s'  % 'flogger', 
         'VERSION': version,
         'NAME': name,
         'PREFIX': '%s' % Options.options.prefix,
         'INCLUDEDIR': 'include/%s' % name}
        )
