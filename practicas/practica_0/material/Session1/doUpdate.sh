#!/bin/bash
VERSION=1.0
# Load configuration & moves to the project root folder
if [ -d scripts ]
then
    source scripts/doConfig.sh
else
    source doConfig.sh
fi
BASE=$(pwd)
echo "Exploring for other NetBeans project in the same subfolder ..."
cd ..
for folder in $(ls)
do
    if [ -d $folder/nbproject ] && [ -d $folder/scripts ] && [ ! $folder == $PROJECT_NAME ]
    then
        echo "Found Netbeans folder with scripts at "$folder" ... Updating scripts"
        cp $BASE/scripts/*.sh $folder/scripts
    fi
done 
cd $BASE
