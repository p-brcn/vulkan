{ pkgs ? import <nixpkgs> {} }:
  pkgs.mkShell {
    # nativeBuildInputs is usually what you want -- tools you need to run
    nativeBuildInputs = with pkgs.buildPackages; [
    glfw xorg.libXi xorg.libXxf86vm xorg.libX11 
    xorg.libXrandr vulkan-tools vulkan-loader 
    glm vk-bootstrap vulkan-headers vulkan-tools-lunarg
    vulkan-caps-viewer vulkan-validation-layers
    vulkan-extension-layer binutils shaderc ];
}
