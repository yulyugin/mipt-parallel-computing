#!/usr/bin/python2.7
"""
Program to build graphics and test parallel programs

It builds dependancies of
* execution time to processes number
* acceleration to processes number

Author: Evgeny Yulyugin
Year: 2014
"""

''' TODO list:
    * Generate gnuplot input file
    * Make global environment
    * Build acceleration to process number graph
    * Expand process_count. Calculate in dependance on physical CPU count
'''

import sys
import argparse
import os
import re
import subprocess
import multiprocessing

graph_file      = "graph_input.tmp"
gnuplot_env     = "graph_input"
gnuplot_file    = "builder.graph"
binary          = "a.out"
process_count   = [2, 4, 8, 16, 32, 64, 128]

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
    time_one = float(single(env, 1))
    fout.write("%d %lf 0\n" % (1, time_one))
    for process in process_count:
        time = float(single(env, process))
        fout.write("%d %lf %lf\n" % (process, time, time_one/time))
    fout.close()

def build_graph(env):
    """
    Generates gnuplot file, setup appropriate environment and call gnuplot to build graphics.
    """
    generate_gnuplot_targets()
    # Setup environment
    os.putenv(gnuplot_env, graph_file)
    # Run a command
    command = list()
    command.extend([env.gnuplot, gnuplot_file])
    subprocess.call(command)

def generate_gnuplot_target(ylabel, column):
    f = open(gnuplot_file, 'w')

    header = '''#!/usr/bin/gnuplot -persist
set terminal pdfcairo solid color enhanced
set style line 1 lt 7 pt 7
set logscale x 2
set grid\n'''
    output = '''set output "%s.pdf"\n''' % ylabel
    axes = '''set xlabel "Number of Processes" font "Helvetica,18"
set ylabel "%s" font "Helvetica,18"\n''' % ylabel
    plot = '''plot "%s" using 1:%d title "%s" with linespoints linestyle 1\n''' % (graph_file, column, ylabel)

    f.write(header)
    f.write(output)
    f.write(axes)
    f.write(plot)

    f.close()

def generate_gnuplot_targets():
    generate_gnuplot_target("Time", 2)

def mkenv():
    parser = argparse.ArgumentParser(add_help=True, version = '0.5',
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
    if os.access(binary, os.F_OK):
        os.unlink(binary)
    if os.access(graph_file, os.F_OK):
        os.unlink(graph_file)
    if os.access(gnuplot_file, os.F_OK):
        os.unlink(gnuplot_file)

def main():
    env = mkenv()
    if compile(env.compiler, env.source) != 0:
        return 1

    print "Runninig on %d cores." % multiprocessing.cpu_count()

    collect(env)
    build_graph(env)

    clean()
    return 0

if __name__ == "__main__":
    sys.exit(main())
