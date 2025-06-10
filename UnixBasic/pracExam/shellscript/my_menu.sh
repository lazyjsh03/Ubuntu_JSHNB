#!/bin/bash

# select 구문이 사용할 프롬프트 메시지를 PS3 변수에 설정합니다.
PS3="Input command(1~5): "

# 메뉴에 표시할 항목들을 배열 또는 공백으로 구분된 목록으로 정의합니다.
options="pwd who ps ls quit"

# select 루프를 시작합니다.
# 'options' 목록을 사용자에게 보여주고, 선택된 항목을 'cmd' 변수에 저장합니다.
echo "메뉴를 선택하세요:"
select cmd in $options
do
    # case 문으로 선택된 항목('cmd')에 따라 분기합니다.
    case $cmd in
        "pwd")
            echo "---[pwd]---"
            pwd
            ;;
        "who")
            echo "---[who]---"
            who
            ;;
        "ps")
            echo "---[ps]---"
            ps
            ;;
        "ls")
            echo "---[ls]---"
            ls
            ;;
        "quit")
            # 'quit'이 선택되면 루프를 빠져나가 스크립트를 종료합니다.
            echo "스크립트를 종료합니다."
            break # select 루프 탈출
            ;;
        *)
            # 목록에 없는 번호나 잘못된 값을 입력했을 때 실행됩니다.
            # $REPLY 변수에는 사용자가 입력한 원본 값이 저장되어 있습니다.
            echo "잘못된 입력입니다. 1~5 사이의 숫자를 선택하세요."
            ;;
    esac
done