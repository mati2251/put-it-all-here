#!/bin/bash
set -x
docker build -t www-example .
minikube start --nodes 4 -p demo
kubectl apply -f deployment.yaml
kubectl apply -f load-balancer.yaml
