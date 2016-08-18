#/bin/bash
version=$(cat /tmp/version)
echo "Old version: $version"
((version++))
echo "New version: $version" && \
echo $version > /tmp/version$version > /tmp/version && \
echo "Successfuly set new version to $version"
