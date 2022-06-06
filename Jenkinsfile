pipeline {
    agent { docker { image 'ubuntu:22.04' } }
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
                ca-certificates wget
                '
            }
        }

        stage('Install Qt Dependencies') {
            steps {
                // Install required dependencies for QIPAT
                sh 'apt-get -y -qq install \
                libxkbcommon-dev \
                libglu1-mesa-dev \
                freeglut3-dev \
                mesa-common-dev libboost-all-dev
                '

                // Build muparser
                sh 'wget https://github.com/beltoforion/muparser/archive/refs/tags/v2.3.3-1.tar.gz'
                sh 'tar -xvf v2.3.3-1.tar.gz'
                sh 'pushd muparser-2.3.3-1'
                sh 'cmake .'
                sh 'make && make install'
                sh 'popd'

                // Install Qt Specific dependencies
                sh 'apt-get -y -qq install \
                qt6-tools-dev \
                libqt6charts6-dev \
                libqt6datavisualization6-dev qt6-declarative-dev 
                '
            }
        }

        stage('Build the Project') {
            sh 'cmake -DCMAKE_BUILD_TYPE=Release -B build .'
            sh 'pushd build'
            sh 'make -j4 && make install' // 4 jobs at once
            sh 'popd'
        }

        stage('Build packaging tools') {
            steps {
                sh 'pushd bin'

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

        stage("Package the Project") {
            steps {
                sh 'mv ../resources/* .'
                sh 'mkdir AppDir'
                sh 'export QMAKE=/usr/bin/qmake6' // Needed by linux deploy
                sh './linuxdeploy-x86_64.AppImage --appimage-extract-and-run --appdir AppDir -e ImageProcessing -i QIPAT.png -d QIPAT.desktop --plugin qt --output appimage' // appimage-extract-and-run : because we are in a docker container
                sh 'ls'
                sh 'mv QIPAT*.AppImage QIPAT.AppImage'
                sh 'popd'
            }
        }
    }
}