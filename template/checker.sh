g++ -O2 -o std sumsumsumsum.cpp
g++ -O2 -o force sum4_force.cpp
g++ -O2 -o maker sum4_maker.cpp

while :
do
    ./maker > data.in
    echo "force time:"
    time ./force < data.in > force.out
    echo "std time:"
    time ./std < data.in > std.out
    if [[ `diff force.out std.out` != "" ]];
    then
        echo "gg"
        exit
    fi
done
