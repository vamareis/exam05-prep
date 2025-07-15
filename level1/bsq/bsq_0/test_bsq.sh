#!/bin/bash

# Clean old maps and outputs
TEST_DIR="./bsq_test_maps"
EXPECTED_DIR="./bsq_expected_outputs"
rm -rf "$TEST_DIR" "$EXPECTED_DIR"
mkdir -p "$TEST_DIR" "$EXPECTED_DIR"

# Your bsq executable
BSQ_EXEC="./a.out"

# Colors
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'

# Create test maps and expected outputs
create_tests() {
    ## --- Original Core Tests ---
    echo "5 . o x
.....
.....
..o..
.....
....." > "$TEST_DIR/map01_basic"
    echo "xx...
xx...
..o..
.....
....." > "$EXPECTED_DIR/map01_basic"

    echo "1 . o x
....." > "$TEST_DIR/map02_single_line"
    echo "x...." > "$EXPECTED_DIR/map02_single_line"

    echo "5 . o x
.
.
.
.
." > "$TEST_DIR/map03_single_column"
    echo "x
.
.
.
." > "$EXPECTED_DIR/map03_single_column"

    echo "4 . o x
oooo
oooo
oooo
oooo" > "$TEST_DIR/map04_all_obstacles"
    echo "oooo
oooo
oooo
oooo" > "$EXPECTED_DIR/map04_all_obstacles"

    echo "5 . o x
.....
..o..
.....
..o..
....." > "$TEST_DIR/map05_multiple_squares"
    echo "xx...
xxo..
.....
..o..
....." > "$EXPECTED_DIR/map05_multiple_squares"

    echo "3 . o x
.....
....
....." > "$TEST_DIR/map06_invalid_line_lengths"
    echo "map error" > "$EXPECTED_DIR/map06_invalid_line_lengths"

    echo "3 . o x
..a..
.....
....." > "$TEST_DIR/map07_invalid_characters"
    echo "map error" > "$EXPECTED_DIR/map07_invalid_characters"

    echo "1 . o x
." > "$TEST_DIR/map08_single_cell"
    echo "x" > "$EXPECTED_DIR/map08_single_cell"

    echo "5 . o x
ooooo
o...o
o.o.o
o...o
ooooo" > "$TEST_DIR/map09_obstacles_border"
    echo "ooooo
ox..o
o.o.o
o...o
ooooo" > "$EXPECTED_DIR/map09_obstacles_border"

    echo "0 . o x" > "$TEST_DIR/map10_empty_map"
    echo "map error" > "$EXPECTED_DIR/map10_empty_map"

    echo "6 . o x
......
......
......
......
......
......" > "$TEST_DIR/map11_big_square"
    echo "xxxxxx
xxxxxx
xxxxxx
xxxxxx
xxxxxx
xxxxxx" > "$EXPECTED_DIR/map11_big_square"


    ## --- NEW Edge Case Tests ---

    # Map 12: Missing characters in first line
    echo "3 . o
.....
.....
....." > "$TEST_DIR/map12_missing_char_in_first_line"
    echo "map error" > "$EXPECTED_DIR/map12_missing_char_in_first_line"

    # Map 13: Duplicate characters in first line
    echo "3 . o o
.....
.....
....." > "$TEST_DIR/map13_duplicate_char_in_first_line"
    echo "map error" > "$EXPECTED_DIR/map13_duplicate_char_in_first_line"

    # Map 14: No line break at the end
    echo -n "3 . o x
.....
.....
....." > "$TEST_DIR/map14_missing_linebreak"
    echo "map error" > "$EXPECTED_DIR/map14_missing_linebreak"

    # Map 15: Valid map using numbers as characters
    echo "3 1 2 3
111
121
111" > "$TEST_DIR/map15_numbers_as_chars"
echo "311
121
111" > "$EXPECTED_DIR/map15_numbers_as_chars"

    # Map 16: Invalid map using character not in first line
    echo "3 . o x
.....
..p..
....." > "$TEST_DIR/map16_forbidden_character"
    echo "map error" > "$EXPECTED_DIR/map16_forbidden_character"

    # Map 17: All lines not same length (trailing space)
    echo "3 . o x
.....
.... 
....." > "$TEST_DIR/map17_trailing_space_in_line"
    echo "map error" > "$EXPECTED_DIR/map17_trailing_space_in_line"

    # Map 18: Valid map with special printable characters
    echo "3 @ # $
@@@
@#@
@@@" > "$TEST_DIR/map18_special_printable_chars"

echo "\$@@
@#@
@@@" > "$EXPECTED_DIR/map18_special_printable_chars"
}

# Run tests
run_tests() {
    echo "=== Running bsq tests (with Valgrind) ==="
    for map in $(ls "$TEST_DIR" | sort); do
        base=$(basename "$map")
        echo -n ">>> Testing: $base ... "

        # Temporary files
        ACTUAL_OUT=$(mktemp)
        VALGRIND_OUT=$(mktemp)

        # Run with Valgrind
        valgrind --leak-check=full --error-exitcode=1 --log-file="$VALGRIND_OUT" $BSQ_EXEC "$TEST_DIR/$base" > "$ACTUAL_OUT" 2>&1

        # Check functional correctness
        diff -q "$ACTUAL_OUT" "$EXPECTED_DIR/$base" > /dev/null
        DIFF_RESULT=$?

        # Check for leaks
        LEAK_LINE=$(grep "in use at exit" "$VALGRIND_OUT")
        if echo "$LEAK_LINE" | grep -q "0 bytes in 0 blocks"; then
            LEAK_RESULT=0
        else
            LEAK_RESULT=1
        fi

        # Print results
        if [ $DIFF_RESULT -eq 0 ] && [ $LEAK_RESULT -eq 0 ]; then
            echo -e "${GREEN}✅ PASS${NC}"
        elif [ $DIFF_RESULT -ne 0 ]; then
            echo -e "${RED}❌ FAIL (output mismatch)${NC}"
            echo "Expected:"
            cat "$EXPECTED_DIR/$base"
            echo "Got:"
            cat "$ACTUAL_OUT"
        elif [ $LEAK_RESULT -ne 0 ]; then
            echo -e "${YELLOW}⚠️  FAIL (memory leak)${NC}"
            echo "$LEAK_LINE"
        fi

        # Cleanup
        rm "$ACTUAL_OUT" "$VALGRIND_OUT"
    done
}

# Main
create_tests
run_tests
