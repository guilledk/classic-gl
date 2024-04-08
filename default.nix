{ pkgs ? import <nixpkgs> {} }:
pkgs.mkShell {
  nativeBuildInputs = with pkgs; [
    gcc
    cmake
    gnumake
    pkg-config

    glfw
    glew

    libGL
    libGL.dev
    libglvnd
    libglvnd.dev
    mesa
    libxkbcommon
    wayland
    xorg.libX11
    xorg.libXcursor
    xorg.libXi
    xorg.libXrandr
    xorg.libXinerama
  ];
  buildInputs = with pkgs; [
    glfw
    glew

    libGL
    libglvnd
    mesa
    libxkbcommon
    wayland
    xorg.libX11
    xorg.libXcursor
    xorg.libXi
    xorg.libXrandr
    xorg.libXinerama
  ];
}
