#!/bin/bash

sigint() {
        echo "continue with script!"
}
trap sigint 2

for j in {1..1000}
do
       echo "running $j.."
          ./part2 2
          done
