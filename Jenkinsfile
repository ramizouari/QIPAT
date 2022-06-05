pipeline {
    agent { docker { image 'ubuntu:20.04' } }
    options {
        skipStagesAfterUnstable()
    }
    stages {
            // qt5-default \
            // qttools5-dev-tools \
            // qttools5-dev \
            // libqt5dbus5 \
            // libqt5network5 \
            // libqt5core5a \
            // libqt5widgets5 \
            // libqt5gui5 \
            // libqt5svg5-dev \
            // fcitx-frontend-qt5 \


        stage('Install Dependencies') {
            steps {
                sh 'apt-get -y -qq update'
                sh 'apt-get -y upgrade'
                sh 'apt-get -y --no-install-recommends install \
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
            ca-certificates \ 
            wget
            '
            }
        }
        stage('Build') {
            steps {
                echo 'Building'
		        sh 'ls'
            }
        }
    }
}