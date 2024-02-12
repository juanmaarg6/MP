#!/bin/bash
# Load configuration & moves to the project root folder
if [ -d scripts ]
then
    source scripts/doConfig.sh
else
    source doConfig.sh
fi
# Runs doxygen
doxygen $DOC_FOLDER/*.doxy
# Display documentation
firefox $DOC_FOLDER/html/index.html
