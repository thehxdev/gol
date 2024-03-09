{ pkgs ? import <nixpkgs> { } }:
pkgs.mkShell {
    packages = with pkgs; [
        ## compiler and cmake
        clang_17
        llvmPackages_17.bintools
        cmake
        gnumake
        ninja

        ## debugging stuff
        gdb
        valgrind
    ];

    shellHook = ''
    export CC=clang
    export CXX=clang++
    '';

}
