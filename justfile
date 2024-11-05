# Hidden default. Outputs available cmds when writing "just".
_default:
  @just --list

# Compiles the `reikimann` keymap for the Piantor
compile:
    qmk compile -kb beekeeb/piantor/weact -km reikimann

# Cleans the build folder
clean:
    qmk clean -a
