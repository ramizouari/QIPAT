#!/bin/bash 


# Evaluate exit code of tests

function evaluate_test() {
    if [ $? -eq 0 ]; 
    then 
        echo "- $2 **Passed**!" >> test-results 
    else 
        echo "- $2 **Failed**!" >> test-results
    fi
}

echo "## Test Results" > test-results 
echo "">> test-results

./AlgebraTest
evaluate_test $? "Algebra Test"

./DataStructuresTest
evaluate_test $? "Data Structures Test"

./PolynomialTest
evaluate_test $? "Polynomial Test"

./NumberTheoryTest
evaluate_test $? "Number Theory Test"

./LinearAlgebraTest
evaluate_test $? "Linear Algebra Test"

./TopologyTest
evaluate_test $? "Topology Test"

./ImageCoreTest
evaluate_test $? "Image Core Test"

./ImageGUITest -platform offscreen
evaluate_test $? "Image GUI Test"
