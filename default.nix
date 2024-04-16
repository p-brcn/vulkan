{ pkgs ? import <nixpkgs> {} }:

let
  # Define the build inputs (dependencies)
  buildInputs = with pkgs.buildPackages; [
    glfw xorg.libXi xorg.libXxf86vm xorg.libX11
    xorg.libXrandr vulkan-tools vulkan-loader
    glm vk-bootstrap vulkan-headers vulkan-tools-lunarg
    vulkan-caps-viewer vulkan-validation-layers
    vulkan-extension-layer binutils shaderc
  ];
in
pkgs.mkShell {
  # Specify the build inputs
  buildInputs = buildInputs;
}
