#! /bin/bash

if [ $# -eq 0 ]; then
    echo "Usage: $0 <file>*"
    exit 1
fi

echo -e "사용 권한\t파일"

for file in "$@"
do 
    perm=$(ls -ld "$file" | cut -d ' ' -f 1)
    echo -e "$perm\t$file"
done