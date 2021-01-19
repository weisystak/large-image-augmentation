# openmp
gcc -fopenmp a.c
resA=`./a.out`
echo "$resA"
ta=`echo "$resA" | sed -n 2p |  awk '{print $2}'`
# echo $ta

# serial
gcc b.c -o b.out
resB=`./b.out`
echo "$resB"
tb=`echo "$resB" | sed -n 2p |  awk '{print $2}'`
# echo $tb

echo " "
echo speed up: `echo "scale=2; $tb / $ta" | bc`
 