#!/bin/bash
set -o xtrace
echo "(1/8) CREATE DOCKER VOLUME"
docker volume create vol
echo "(2/8) INSPECT DOCKER VOLUME"
docker volume inspect vol
echo "(3/8) CREATE DOCKER CONTAINER 1"
docker run -itd --mount source=vol,destination=/files/ --name con1 ubuntu 
docker start con1
docker ps -a
echo "(4/8) CREATE INSIDE CONTAINER FOLDER NAME 'files'"
docker exec -u root con1 mkdir files
echo "(5/8) CREATE FILE INSIDE FOLDER"
docker exec -u root con1 sh -c "echo \"Test\" > /files/temp.txt"
echo "(6/8) PRINT temp FILE"
docker exec -u root con1 sh -c "cat /files/temp.txt"
echo "(7/8) REMOVE CONTAINER AND CREATE NEW"
docker stop con1
docker rm con1
echo "(8/8) CREATE NEW CONTAINER AND CHECK FILES"
docker run -itd --mount source=vol,destination=/files/ --name con1 ubuntu
docker start con1
docker exec -u root con1 sh -c "cat /files/temp.txt"

