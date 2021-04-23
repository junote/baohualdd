insmod  globalmem.ko
mknod /dev/globalmem c 230 0
echo "hello,world" > /dev/globalmemo
cat /dev/globalmem
rmmod  globalmem
