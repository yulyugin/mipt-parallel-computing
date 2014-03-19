#!/usr/bin/python2.7
"""
Program to build graphics

Author: Evgeny Yulyugin
Year: 2014
"""

import sys
import argparse

def main():
    parser = argparse.ArgumentParser(add_help=True, version = '0.1',
                                     description="Graphics builder.")
    parser.add_argument("--mpicc", type=str, action="store", default="mpicc",
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

    return 0

if __name__ == "__main__":
    sys.exit(main())
