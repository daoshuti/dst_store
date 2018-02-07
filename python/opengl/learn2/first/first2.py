#!/usr/bin/env python
# -*- coding=utf8 -*-
"""
# Author: wanghan
# Created Time : 2018年02月07日 星期三 22时55分44秒
# File Name: first.py
# Description:
"""
from OpenGL.GL import *
from OpenGL.GLU import *
from OpenGL.GLUT import *
 
def drawFunc():
    glClear(GL_COLOR_BUFFER_BIT)
    glRotatef(1, 0, 1, 0)
    glutWireTeapot(0.5)
    glFlush()
 
glutInit()
glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA)
glutInitWindowSize(400, 400)
glutCreateWindow("First")
glutDisplayFunc(drawFunc)
glutIdleFunc(drawFunc)
glutMainLoop()
