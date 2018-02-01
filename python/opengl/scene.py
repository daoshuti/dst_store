#!/usr/bin/env python
# -*- coding=utf8 -*-
"""
# Author: wanghan
# Created Time : 2018年02月01日 星期四 12时29分39秒
# File Name: scene.py
# Description:
"""

class Scene(object):

    #放置节点的深度，放置的节点距离摄像机15个单位
    PLACE_DEPTH = 15.0

    def __init__(self):
        #场景下的节点队列
        self.node_list = list()

    def add_node(self, node):
        """ 在场景中加入一个新节点 """
        self.node_list.append(node)

    def render(self):
        """ 遍历场景下所有节点并渲染 """
        for node in self.node_list:
            node.render() 
