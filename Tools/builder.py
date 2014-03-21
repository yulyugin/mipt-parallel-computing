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
import re
import subprocess
import multiprocessing

graph_file      = "graph_input.tmp"
gnuplot_file    = "builder.graph"
binary          = "a.out"
process_count   = [1, 2, 4, 8, 16, 32, 64, 128]

def compile(compiler, source):
    """
    Compile given file with given compiler and extra options.
    Base option: -Werror -O2
    """
    compile_options = ["-Werror", "-O2"]
    command = list()
    command.append(compiler)
    command.extend(compile_options)
    command.extend([source, "-o", binary])
    return subprocess.call(command)

def single(env, size):
    command = list()
    if env.compiler == "mpicc":  # TODO: Expand check to env.eompiler contains mpicc string
        command.extend([env.mpirun, "-n", str(size), binary])
    else:
        assert(0)   # Not yet implemented

    if env.options != None:
        command.append(env.options)

    output = re.split('\n', subprocess.check_output(command))
    i = 0
    for line in output:
        if re.match('Time|time', line):
            times = re.findall('\d+\.\d+', line)
            if len(times) != 1:
                raise Exception("Invalid output format of tested program.")
            return times[0]

def collect(env):
    fout = open(graph_file, 'w')
    fout.write("# process-count time acceleration\n")
    for process in process_count:
        fout.write("%d %s\n" % (process, single(env, process))) # TODO: Add acceleration calculation
    fout.close()

def mkenv():
    parser = argparse.ArgumentParser(add_help=True, version = '0.3',
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

def clean():
    os.unlink("a.out")
    os.unlink(graph_file)

def main():
    env = mkenv()
    if compile(env.compiler, env.source) != 0:
        return 1

    print "Runninig on %d cores." % multiprocessing.cpu_count()

    collect(env)

    clean()
    return 0

if __name__ == "__main__":
    sys.exit(main())
