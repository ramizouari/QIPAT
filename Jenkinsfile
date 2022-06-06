pipeline {

    environment {
        GITHUB_TOKEN = credentials('github-token')
    }

    agent { docker { 
        image 'ubuntu:22.04' 
        args '-u root:root -e QMAKE=/usr/bin/qmake6'
        }     
    }
    options {
        skipStagesAfterUnstable()
    }



    stages {

        stage('Install Dependencies') {
            steps {
                // update repositories
                sh 'apt-get -y -qq update'
                // upgrade packages
                sh 'apt-get -y upgrade'
                // Install required system dependencies
                sh 'apt-get -y -qq --no-install-recommends install \
                python3 \
                python3-pip \
                fuse \
                patchelf \
                cmake \
                extra-cmake-modules \
                build-essential \
                appstream \
                hicolor-icon-theme \
                openssl \
                curl \
                ca-certificates wget'
            }
        }

        stage('Install Qt Dependencies') {
            steps {
                // Install required dependencies for QIPAT
                sh 'apt-get -y -qq install \
                libxkbcommon-dev \
                libglu1-mesa-dev \
                freeglut3-dev \
                mesa-common-dev libboost-all-dev'

                // Build muparser
                sh 'wget https://github.com/beltoforion/muparser/archive/refs/tags/v2.3.3-1.tar.gz'
                sh 'tar -xvf v2.3.3-1.tar.gz'

                dir('muparser-2.3.3-1') {
                    sh 'cmake .'
                    sh 'make && make install'
                }
                sh 'rm -r v2.3.3-1.tar.gz'
                sh 'rm -r muparser-2.3.3-1'

                // Install Qt Specific dependencies
                sh 'apt-get -y -qq install \
                qt6-tools-dev \
                libqt6charts6-dev \
                libqt6datavisualization6-dev qt6-declarative-dev'
            }
        }

        stage('Build the Project') {
            steps {
                sh 'cmake -DCMAKE_BUILD_TYPE=Release -B buildapp .'
                sh 'ls'
                dir('buildapp') {
                    sh 'make -j4 && make install' // 4 jobs at once
                }
            }
        }

        stage('Build packaging tools') {
            steps {
                dir('bin') {
                    // Get LinuxDeploy
                    sh 'wget https://github.com/linuxdeploy/linuxdeploy/releases/download/continuous/linuxdeploy-x86_64.AppImage'
                    sh 'chmod a+x linuxdeploy-x86_64.AppImage'

                    // Get LinuxDeploy-Qt-Plugin && Extract binary
                    sh 'wget https://github.com/linuxdeploy/linuxdeploy-plugin-qt/releases/download/continuous/linuxdeploy-plugin-qt-x86_64.AppImage'
                    sh 'chmod a+x linuxdeploy-plugin-qt-x86_64.AppImage'
                    sh './linuxdeploy-plugin-qt-x86_64.AppImage --appimage-extract'
                    sh 'mv squashfs-root/usr/bin/linuxdeploy-plugin-qt .'
                    sh 'rm linuxdeploy-plugin-qt-x86_64.AppImage' // Avoid conflicts with extracted binary
                }
            }
        }

        stage("Package the Project") {
            steps {
                dir('bin') {
                    sh 'mv ../resources/* .'
                    sh 'mkdir AppDir'
                    // sh 'export QMAKE=/usr/bin/qmake6' // Needed by linux deploy
                    sh './linuxdeploy-x86_64.AppImage --appimage-extract-and-run --appdir AppDir -e ImageProcessing -i QIPAT.png -d QIPAT.desktop --plugin qt --output appimage' // appimage-extract-and-run : because we are in a docker container
                    sh 'ls'
                    sh 'mv QIPAT*.AppImage QIPAT.AppImage'
                }

            }
        }

        stage("Upload To Github") {
            dir('bin') {
                sh 'curl -X POST -H "Authorization: token $GITHUB_TOKEN" --data "{\"tag_name\": \"v0.1.0\", \"name\": \"continuous\", \"body\": \"CICD Release\", \"draft\": false, \"prerelease\": true}" https://api.github.com/repos/ramizouari/QIPAT/releases > response'
                sh 'cat response | sed -n -e \'s/"id":\ \([0-9]\+\),/\1/p\' | head -n 1 | sed \'s/[[:blank:]]//g\' | tee id'
                sh 'curl -X POST -H "Authorization:token $GITHUB_TOKEN" -H "Content-Type:application/octet-stream" --data-binary QIPAT.AppImage https://uploads.github.com/repos/ramizouari/QIPAT/releases/68737653/assets?name=QIPAT.AppImage'
            }
        }

        stage("Clean Everything") {
            steps {
                sh 'rm -rf *'
            }
        }
    }
}