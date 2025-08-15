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
YELLOW='\033[1;33m'
NC='\033[0m'

# Create test maps and expected outputs
create_tests() {
    ## --- Core Tests ---
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

    echo "3 . o
.....
.....
....." > "$TEST_DIR/map12_missing_char_in_first_line"
    echo "map error" > "$EXPECTED_DIR/map12_missing_char_in_first_line"

    echo "3 . o o
.....
.....
....." > "$TEST_DIR/map13_duplicate_char_in_first_line"
    echo "map error" > "$EXPECTED_DIR/map13_duplicate_char_in_first_line"

    echo -n "3 . o x
.....
.....
....." > "$TEST_DIR/map14_missing_linebreak"
    echo "map error" > "$EXPECTED_DIR/map14_missing_linebreak"

    echo "3 1 2 3
111
121
111" > "$TEST_DIR/map15_numbers_as_chars"
    echo "311
121
111" > "$EXPECTED_DIR/map15_numbers_as_chars"

    echo "3 . o x
.....
..p..
....." > "$TEST_DIR/map16_forbidden_character"
    echo "map error" > "$EXPECTED_DIR/map16_forbidden_character"

    echo "3 . o x
.....
....
....." > "$TEST_DIR/map17_trailing_space_in_line"
    echo "map error" > "$EXPECTED_DIR/map17_trailing_space_in_line"

    echo "3 @ # $
@@@
@#@
@@@" > "$TEST_DIR/map18_special_printable_chars"
    echo "\$@@
@#@
@@@" > "$EXPECTED_DIR/map18_special_printable_chars"

    echo "9 . o x
...........................
....o......................
............o..............
.........................o.
....o....o........o........
......o....o...o...........
...........................
......o..............o.....
..o.......o................" > "$TEST_DIR/map19_full_integration"
    echo "...................xxxxxx..
....o..............xxxxxx..
............o......xxxxxx..
...................xxxxxxo.
....o....o........oxxxxxx..
......o....o...o...xxxxxx..
...........................
......o..............o.....
..o.......o................" > "$EXPECTED_DIR/map19_full_integration"

    echo "9 . o x
...........................
....o......................
............o..............
...........................
....o......................
.........o.....o...........
...........................
......o..............o.....
..o.......o................" > "$TEST_DIR/map20_full_integration_2"
    echo "................xxxxxxx....
....o...........xxxxxxx....
............o...xxxxxxx....
................xxxxxxx....
....o...........xxxxxxx....
.........o.....oxxxxxxx....
................xxxxxxx....
......o..............o.....
..o.......o................" > "$EXPECTED_DIR/map20_full_integration_2"
}

run_tests() {
    echo "=== Running bsq tests (with Valgrind) ==="
    for map in $(ls "$TEST_DIR" | sort); do
        base=$(basename "$map")
        echo -n ">>> Testing: $base ... "

        ACTUAL_OUT=$(mktemp)
        VALGRIND_OUT=$(mktemp)

        valgrind --leak-check=full --error-exitcode=1 --log-file="$VALGRIND_OUT" $BSQ_EXEC "$TEST_DIR/$base" > "$ACTUAL_OUT" 2>&1

        diff -q "$ACTUAL_OUT" "$EXPECTED_DIR/$base" > /dev/null
        DIFF_RESULT=$?

        LEAK_LINE=$(grep "in use at exit" "$VALGRIND_OUT")
        if echo "$LEAK_LINE" | grep -q "0 bytes in 0 blocks"; then
            LEAK_RESULT=0
        else
            LEAK_RESULT=1
        fi

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

        rm "$ACTUAL_OUT" "$VALGRIND_OUT"
    done
}

create_tests
run_tests
