#!/bin/bash
set -x
docker stop con1
docker rm con1
docker volume rm vol
