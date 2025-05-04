{
  description = "Daisy programming language";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = {
    self,
    nixpkgs,
    flake-utils,
  }:
    flake-utils.lib.eachDefaultSystem (
      system: let
        pkgs = nixpkgs.legacyPackages.${system};
        llvmVersion = pkgs.llvmPackages_19;
      in {
        devShells.default = pkgs.mkShell {
          packages = with pkgs; [
            cmake
            pkg-config
            ninja
            cppcheck
            llvmVersion.clang
          ];

          buildInputs = with pkgs; [
            cli11
            gtest
            llvmVersion.llvm
            libxml2
            libffi
          ];

          shellHook = ''
            export CXX=clang++
            export CMAKE_CXX_COMPILER=clang++
            export CMAKE_GENERATOR=Ninja
          '';
        };
      }
    );
}
