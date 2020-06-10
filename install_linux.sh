#!/env/bash

# Build
make -C commandline/makemake
bash make_release_linux.sh

# Test python3
echo "Testing using python3"
cd _rel/bin-Linux-x86 && sudo python3 ../Test/test2m.py