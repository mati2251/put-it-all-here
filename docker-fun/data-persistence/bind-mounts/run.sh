#!/bin/bash
set -o xtrace
echo "(1/7) CREATE DOCKER CONTAINER 1"
docker run -itd --mount type=bind,source="${PWD}"/files,destination=/files/ --name con1 ubuntu
docker start con1
docker ps -a
echo "(2/7) CREATE INSIDE CONTAINER FOLDER NAME 'files'"
docker exec -u root con1 mkdir files
echo "(3/7) CREATE FILE INSIDE FOLDER"
docker exec -u root con1 sh -c "echo \"Test\" > /files/temp.txt"
echo "(4/7) PRINT temp FILE"
docker exec -u root con1 sh -c "cat /files/temp.txt"
echo "(5/7) REMOVE CONTAINER AND CREATE NEW"
docker stop con1
docker rm con1
echo "(6/7) CREATE NEW CONTAINER AND CHECK FILES"
docker run -itd --mount type=bind,source="${PWD}"/files,destination=/files/ --name con1 ubuntu
docker start con1
docker exec -u root con1 sh -c "cat /files/temp.txt"
echo "(7/7) CHECK IN HOST FOLDER"
cat files/temp.txt
