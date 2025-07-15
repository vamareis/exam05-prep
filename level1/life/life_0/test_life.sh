#!/bin/bash

GREEN="\033[0;32m"
RED="\033[0;31m"
YELLOW="\033[1;33m"
NC="\033[0m"

pass() { echo -e "${GREEN}✔ $1${NC}"; }
fail() { echo -e "${RED}✘ $1${NC}"; }
warn() { echo -e "${YELLOW}⚠ $1${NC}"; }

run_test() {
    desc="$1"
    cmd="$2"
    expected="$3"

    # Temporary files
    ACTUAL_OUT=$(mktemp)
    VALGRIND_OUT=$(mktemp)

    # Run test and capture output
    eval "$cmd" | cat -e > "$ACTUAL_OUT"

    # Run test with Valgrind for leak check
    valgrind --leak-check=full --error-exitcode=42 --log-file="$VALGRIND_OUT" $cmd > /dev/null 2>&1

    # Check functional correctness
    if diff -q "$ACTUAL_OUT" <(echo "$expected") >/dev/null; then
        DIFF_RESULT=0
    else
        DIFF_RESULT=1
    fi

    # Check for leaks
    LEAK_LINE=$(grep "in use at exit" "$VALGRIND_OUT")
    if echo "$LEAK_LINE" | grep -q "0 bytes in 0 blocks"; then
        LEAK_RESULT=0
    else
        LEAK_RESULT=1
    fi

    # Print results
    if [ $DIFF_RESULT -eq 0 ] && [ $LEAK_RESULT -eq 0 ]; then
        pass "$desc ✅"
    elif [ $DIFF_RESULT -ne 0 ]; then
        fail "$desc ❌ Output mismatch"
        echo "Expected:"
        echo "$expected"
        echo "Got:"
        cat "$ACTUAL_OUT"
    elif [ $LEAK_RESULT -ne 0 ]; then
        warn "$desc ⚠ Memory leak detected"
        echo "$LEAK_LINE"
    fi

    # Cleanup
    rm "$ACTUAL_OUT" "$VALGRIND_OUT"
}

# --- Test cases (same as validated suite) ---

run_test "Diagonal draw, 2 iterations" \
"./a.out 5 5 2 <<< 'xsdxsd'" \
"00   $
00   $
     $
     $
     $"

run_test "Two parallel lines, 4 iterations" \
"./a.out 4 4 4 <<< 'xssdwdxssawd'" \
"    $
    $
    $
    $"

run_test "Staircase pattern, 3 iterations" \
"./a.out 6 6 3 <<< 'xdxsdxsdxsdd'" \
"  0   $
 0 0  $
  00  $
      $
      $
      $"

run_test "Single live cell, 5 iterations" \
"./a.out 3 3 5 <<< 'x'" \
"   $
   $
   $"

run_test "Draw multiple lines with pen toggling, 2 iterations" \
"./a.out 5 5 2 <<< 'xssdxxssddxxww'" \
"     $
00   $
00   $
00 00$
  000$"

run_test "Empty input, 1 iteration" \
"./a.out 5 5 1 <<< ''" \
"     $
     $
     $
     $
     $"

run_test "Smallest possible still life block, 3 iterations" \
"./a.out 2 2 3 <<< 'xsdw'" \
"00$
00$"

run_test "Multiple pen toggles without moving, 2 iterations" \
"./a.out 7 3 2 <<< 'xxxx'" \
"       $
       $
       $"

# --- Edge cases ---

run_test "1x1 board, toggle pen twice" \
"./a.out 1 1 3 <<< 'xx'" \
" $"

run_test "1x1 board, toggle pen once" \
"./a.out 1 1 1 <<< 'x'" \
" $"

run_test "1x5 vertical line on narrow board" \
"./a.out 1 5 1 <<< 'xssss'" \
" $
0$
0$
0$
 $"

run_test "5x1 horizontal line on narrow board" \
"./a.out 5 1 1 <<< 'xdddd'" \
" 000 $"

run_test "Rapid pen toggling while moving (forms block)" \
"./a.out 5 5 2 <<< 'xxdxsxaxdxd'" \
"00   $
00   $
     $
     $
     $"

run_test "Corner drawing (border dies after overpopulation)" \
"./a.out 5 5 3 <<< 'xddddxssssxaaaaxwwww'" \
"     $
     $
     $
     $
     $"

run_test "Blinker at border (vertical collapses to single cell)" \
"./a.out 1 3 1 <<< 'xsss'" \
" $
0$
 $"

run_test "Large empty board, no drawing" \
"./a.out 10 10 5 <<< ''" \
"          $
          $
          $
          $
          $
          $
          $
          $
          $
          $"

run_test "Overwrite cells by moving over them twice" \
"./a.out 5 3 2 <<< 'xdddaxaaax'" \
" 00  $
 00  $
     $"
