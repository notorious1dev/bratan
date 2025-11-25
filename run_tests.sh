DIR="tests_build"
TESTS_DIR="tests"
UNITY_C="unity/unity.c"

if [ ! -d "$DIR" ]; then
    mkdir "$DIR"
    echo "$DIR directory was created"
else
    echo "$DIR directory already exists"
fi

for TEST_FILE in "$TESTS_DIR"/*.c; do
    if [ -f "$TEST_FILE" ]; then
        TEST_NAME=$(basename "$TEST_FILE" .c)   
        gcc "$TEST_FILE" "$UNITY_C" -I./headers -I./headers/data_structures -I./unity -lm -o "$DIR/$TEST_NAME.out"
        if [ $? -eq 0 ]; then
            echo "Running test: $TEST_NAME"
            ./"$DIR/$TEST_NAME.out"
            echo " "
        else
            echo "Compilation failed for $TEST_NAME.out"
        fi
    fi
done
