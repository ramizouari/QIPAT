pipeline {
    agent { docker { image 'ubuntu:20.04' } }
    options {
        skipStagesAfterUnstable()
    }
    stages {
        stage('Build') {
            steps {
                echo 'Building'
		sh 'ls'
            }
        }
    }
}