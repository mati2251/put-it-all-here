set -o xtrace
mkdir files
docker run -itd --mount type=tmpfs,destination=/files --name con1 ubuntu
docker start con1
docker ps -a
docker exec con1 sh -c "echo hello >  files/test.txt"
docker exec con1 sh -c "cat /files/test.txt"
docker stop con1
docker start con1
docker exec con1 sh -c "cat /files/test.txt"
