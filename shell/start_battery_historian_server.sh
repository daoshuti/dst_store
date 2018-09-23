#!/bin/bash
# Author: wanghan
# Created Time : 2018年09月21日 21:55:45
# File Name: start_battery_historian_server.sh
# Description:  start the battery historian server

echo Change work path to battery-historian path ...
cd /d/codes/Go/src/github.com/google/battery-historian/

echo Run server ... 
go run cmd/battery-historian/battery-historian.go

echo Done.
