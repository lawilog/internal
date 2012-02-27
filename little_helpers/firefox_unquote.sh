#!/bin/bash
firefox `echo $@ | sed 's/"//g'`
