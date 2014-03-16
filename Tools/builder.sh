#/bin/sh

if [ $# == 0 ]
then
  echo "Invalid input format."
  echo "Usage: $0 [file name]"
  exit 1
fi

for i in $@
do
  if [ $i != $1 ]
  then
    params+="$i "
  fi
done

mpicc -Wall $1

output="graph_input.tmp"

echo "# process-count time" > $output

for i in 1 2 4 8 16 32 64 128
do
echo $i `mpirun -np $i a.out $params |grep Time | sed 's/[^0-9.]//g'` >> $output
done

export graph_input=$output
export x_label="x"
export y_label="y"

cat builder.graph |gnuplot

exit 0
