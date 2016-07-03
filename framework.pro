TEMPLATE = subdirs
CONFIG += ordered

SUBDIRS = \
    framework \
    test

test.depends = framework
