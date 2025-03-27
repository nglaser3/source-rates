#!/bin/bash

python half-D.py 8

mv openmc_simulation* depletion_* results/

rm -f *.xml *.h5 *.out