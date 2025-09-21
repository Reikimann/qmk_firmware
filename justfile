# Hidden default. Outputs available cmds when writing "just".
_default:
  @just --list

# Compiles the `reikimann` keymap for the Piantor
compile-piantor:
    qmk compile -kb beekeeb/piantor -km reikimann

# Compiles the `reikimann` keymap for the Piantor Pro
compile-pro:
    qmk compile -kb beekeeb/piantor_pro -km reikimann

# Flashes the `reikimann` keymap for the Piantor
flash-piantor:
    qmk flash -kb beekeeb/piantor -km reikimann

# Flashes the `reikimann` keymap for the Piantor Pro
flash-pro:
    qmk flash -kb beekeeb/piantor_pro -km reikimann

# Cleans the build folder
clean:
    qmk clean -a
