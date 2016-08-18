#/bin/bash

tempdir=$2

filename="$1.ino"
filepath="$1/$filename"
temppath="$tempdir/$filename"

version=$(cat /tmp/version)
echo "Old version: $version"
((version++))
echo "New version: $version"

echo "Generating $tempdir"
mkdir -p $tempdir && \
\
echo "Configuring $filepath with new version on $temppath" && \
#url=$(cat ./build/url.txt) && \
#url = set_api
sed -e "s/__CODEBENDER_AUTO_VERSION__/$version/g" -e "s@__CODEBENDER_UPDATE_URL__@$url@g" $filepath > $temppath && \
echo "New file at $temppath"
