#!/bin/sh
set -x
../../../TOOL/INCLEAN/inclean --use_file_content --or_upper_case_file_name --include "../CODE//!*.hpp" --comment "// -- IMPORTS" --partial --missing --unused --sort --verbose "../CODE//*.?pp" "CODE//*.?pp"
