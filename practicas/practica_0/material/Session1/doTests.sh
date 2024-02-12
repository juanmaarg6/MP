#!/bin/bash
VERSION=1.0
# Load configuration & moves to the project root folder
if [ -d scripts ]
then
    source scripts/doConfig.sh
else
    source doConfig.sh
fi
echo "Generating fresh binaries"
make build
echo "Press [RETURN] to continue"
read
if [ $USE_VALGRIND == "YES" ]
then 
    VALGRIND="valgrind --leak-check=full "
else
    VALGRIND=""
fi
DIST=dist/Debug/GNU-Linux/
BINARY=$(ls $DIST)
FULL_BINARY=$VALGRIND$PROJECT_FOLDER/$DIST/$BINARY
CALL_MARK="%%%CALL"
OUTPUT_MARK="%%%OUTPUT"
rm $TESTS_FOLDER/.out*
k=1
for test in $TESTS_FOLDER/*.test
do
    MYCALL=$(grep $CALL_MARK $test | sed s/$CALL_MARK//)
    DUE_OUTPUT=$(sed -n /$OUTPUT_MARK/,\$p $test)
    echo "Test #$k ($BINARY $MYCALL)"
    if [ $USE_VALGRIND == "YES" ]
    then 
        eval "$FULL_BINARY $MYCALL "
        echo ""
        echo ""
        echo "Test #$k ($BINARY $MYCALL)"
        echo "DUE) $DUE_OUTPUT"
    else
        eval "$FULL_BINARY $MYCALL &> $TESTS_FOLDER/.out$k"
        if  grep $OUTPUT_MARK $TESTS_FOLDER/.out$k; 
        then
            REAL_OUTPUT=$(sed -n /$OUTPUT_MARK/,\$p $TESTS_FOLDER/.out$k)
        else
            REAL_OUTPUT=$(echo $OUTPUT_MARK; cat $TESTS_FOLDER/.out$k)
            #REAL_OUTPUT=eval "echo $OUTPUT_MARK; cat $TESTS_FOLDER/.out$k"
        fi
        if [ ! "$DUE_OUTPUT" == "$REAL_OUTPUT" ]
        then
            echo ""
            echo ""
            echo "DUE) $DUE_OUTPUT"
            echo "REAL) $REAL_OUTPUT"
            echo "Test #$k ($BINARY $MYCALL)"
            echo "Test #$k FAILED"
        else
            cat $TESTS_FOLDER/.out$k
            echo ""
            echo ""
            echo "Test #$k ($BINARY $MYCALL)"
            echo "Test #$k OK"
        fi
    fi
    echo "Press [RETURN] to continue"
    read
    clear
    k=$[k + 1]
done 
