#!/bin/bash

token=$1
artifact=$2
tag=$(cat $3)
changelog=$(cat $4)

# Create & Get The Id of the Release
id=$(curl -X POST -H "Authorization: token $token" --data "{'tag_name': 'v$3', 'name': 'v$3', 'body': '$4', 'draft': false, 'prerelease': true}" https://api.github.com/repos/ramizouari/QIPAT/releases | jq .id)

# Upload the Artifact
curl -X POST -H "Authorization:token $token" -H "Content-Type:application/octet-stream" --data-binary $artifact https://uploads.github.com/repos/ramizouari/QIPAT/releases/$id/assets?name=$artifact'
