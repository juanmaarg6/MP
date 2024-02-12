#!/bin/bash
VERSION=1.0
# Load configuration & moves to the project root folder
if [ -d scripts ]
then
    source scripts/doConfig.sh
else
    source doConfig.sh
fi
# Remove older copies
rm $ZIP_FOLDER/*.zip
# Zips the project	
echo "Zipping project"
if [ $ZIP_NAME == $PROJECT_NAME ]
then
    cd ..
    eval "zip -r $PROJECT_NAME/$ZIP_FOLDER/$ZIP_NAME.zip $PROJECT_NAME/* -x $EXCLUDED_FOLDERS"
    cd -
else
    eval "zip -r $ZIP_FOLDER/$ZIP_NAME.zip * -x $EXCLUDED_FOLDERS"
fi