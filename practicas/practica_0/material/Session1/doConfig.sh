#!/bin/bash
VERSION=1.0
# Moves to the project' root folder
function CDRootFolder() {   
    DOMOVE=false
    while [ ! -d nbproject ]
    do
        cd ..
        DOMOVE=true
        DIR=$(pwd)
        if [ $DIR == '/' ] 
        then
            echo "Ups! Something went wrong...sorry!"
            exit 1
        fi
    done 
    if [ "$DOMOVE" == true ]
    then
        echo "Moving down to project root folder "$(pwd)
    fi
}

# Check if folder exists, otherwise creates it or set it to default
# param $1 The folder to check
# param $2 The variable used to store $1 (reference)
function CheckFolder() {
    if [ ! $1 ] || [ ! $2 ]
    then
       echo "ERROR: Missing parameters to CheckFolder() "; echo
       exit 1
    fi
    FOLDER=/dev/null
    if [ ! -d $1 ]
    then
        if [ $CREATE_FOLDERS = "YES" ]
        then 
            echo "Creating folder "$1
            mkdir $1
            FOLDER=$1
        else
            echo "Folder $1 does not exist"
        fi
    else
        FOLDER=$1
    fi
    eval "$2=$FOLDER"
}


# Main
# Moves to root folder
CDRootFolder
# Reads root folder and its name
PROJECT_FOLDER=$(pwd)
PROJECT_NAME=$(basename $PROJECT_FOLDER)
# Create unexisting folders when required or not
CREATE_FOLDERS=YES
# Folder to store the zip
CheckFolder zip/ ZIP_FOLDER
# Folder to store Doxygen' data
CheckFolder doc/ DOC_FOLDER
# Folder to store test data
CheckFolder tests/ TESTS_FOLDER
# Use of memory leak detector
USE_VALGRIND=NO
# Forces the name of the ZIP. If left empty, the zip uses the name of the root foder
#ZIP_NAME=$PROJECT_NAME
ZIP_NAME="MPPractica"
# Folders not to be included in the zip. Otherwise left empty
if [ $ZIP_NAME == $PROJECT_NAME ]
then
    EXCLUDED_FOLDERS="$PROJECT_NAME/nbproject/private/**\*  $PROJECT_NAME/dist/**\* $PROJECT_NAME/build/**\* $PROJECT_NAME/doc/html/**\* $PROJECT_NAME/doc/latex/**\*"
else
    EXCLUDED_FOLDERS="nbproject/private/**\*  dist/**\* build/**\* doc/html/**\* doc/latex/**\*"
fi