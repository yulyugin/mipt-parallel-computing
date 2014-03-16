#/bin/sh

if [ $# != 1 ]
then
  echo "Invalid input format."
  echo "Usage: $0 [file name]"
  exit 1
fi

mpicc -Wall $1

output="graph_input.tmp"

echo "# process-count time" > $output

for i in 1 2 4 8 16 32
do
echo $i `mpirun -np $i a.out $N |grep Time | sed 's/[^0-9.]//g'` >> $output
done

exit 0
