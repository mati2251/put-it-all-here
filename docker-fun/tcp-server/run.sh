set -x
mkdir files
echo "Hello :)))" > files/hello.txt
docker build -t tcp-server .
docker run -it -p 80:80 --rm tcp-server
