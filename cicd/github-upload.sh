#!/bin/bash

token=$1
artifact=$2
tag=$(cat $3)
changelog=$(cat $4)

changelog_cleaned="${changelog//$'\n'/'\n'}" # Transform Line Break to \n ( otherwise not valid JSON )

# Data Used to Create the release
function release_data() {
cat <<EOF
{
  "tag_name": "v$tag",
  "name": "v$tag",
  "body": "$changelog_cleaned",
  "draft": false,
  "prerelease": true
}
EOF
}

# Create & Get The Id of the Release
curl -X POST -H "Authorization: token $token" --data "$(release_data)" https://api.github.com/repos/ramizouari/QIPAT/releases


# Upload the Artifact
curl -X POST -H "Authorization:token $token" -H "Content-Type:application/octet-stream" --data-binary $artifact https://uploads.github.com/repos/ramizouari/QIPAT/releases/$id/assets?name=$artifact
