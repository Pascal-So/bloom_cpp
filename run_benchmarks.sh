directory=`dirname $0`
mkdir $directory/build;
(cd $directory/build; cmake .. -DBUILD_BLOOMFILTER_BENCHMARK=ON; make all;)
$directory/build/benchmark/BloomFilterBenchmark $1
