sysbench fileio --file-num=1 --threads=1 --file-total-size=3G \
         --file-test-mode=seqrd --file-io-mode=async prepare

sysbench fileio --file-num=1 --threads=1 --file-total-size=3G \
         --file-test-mode=seqrd --file-io-mode=async run

sysbench fileio --file-num=1 --threads=1 --file-total-size=3G \
         --file-test-mode=seqrd --file-io-mode=async cleanup

