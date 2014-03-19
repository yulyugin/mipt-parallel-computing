#!/usr/bin/python2.7
"""
Program to build graphics and test parallel programs

It builds dependancies of
* execution time to processes number
* acceleration to processes number

Author: Evgeny Yulyugin
Year: 2014
"""

import sys
import argparse
import os
import subprocess

def compile(compiler, source):
    command = list()
    command.append(compiler)
    command.append(source)
    subprocess.call(command)

def mkenv():
    parser = argparse.ArgumentParser(add_help=True, version = '0.1',
                                     description="Graphics builder.")
    parser.add_argument("--compiler", type=str, action="store", default="mpicc",
                        help="Path to mpicc compiler.")
    parser.add_argument("--mpirun", type=str, action="store", default="mpirun",
                        help="Path to mpi starter.")
    parser.add_argument("--gnuplot", type=str, action="store", default="gnuplot",
                        help="Path to gnuplot executable file.")
    parser.add_argument("source", type=str, action="store",
                        help="Path to the source file.")
    parser.add_argument("--options", type=str, action="store",
                        help="Command line arguments for tested program.")
    args = parser.parse_args()
    return args

def main():
    env = mkenv()
    compile(env.compiler, env.source)

    return 0

if __name__ == "__main__":
    sys.exit(main())
