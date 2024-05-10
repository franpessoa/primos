format: _h _cc

alias f:=format
_h:
    find ./include/*/*.h | xargs clang-format -i
_cc:
    find src/**/*.cc | xargs clang-format -i