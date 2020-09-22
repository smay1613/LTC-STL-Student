find . -mindepth 1 -maxdepth 2 -name student | while read -r task
do
    echo "$task"
    cd "$task" && cmake . && make -j4 && cd ..
    if [[ "$?" -ne 0 ]]; then 
      break
    fi
done