#! /usr/bin/env python
# coding=utf-8
class node:
    def __init__(self, data):
        if isinstance(data,node):
            self._data = data._data
            self._children = data._children
            return

        self._data = data
        self._children = []

    def getdata(self):
        return self._data

    def getchildren(self):
        return self._children

    def add(self, node):
        self._children.append(node)

    def print_node(self, prefix=0):
        print('  ' * prefix, '-', self._data)
        for child in self._children:
            child.print_node(prefix + 1)

# a = node()
# a.print_node()
