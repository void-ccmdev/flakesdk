{
  description = "A FlakeSDK Nix Flake for development environments for developers.";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = { nixpkgs, flake-utils, ... }:
    flake-utils.lib.eachDefaultSystem (system:
      let
        pkgs = nixpkgs.legacyPackages.${system};
      in
      {
        devShells.default = pkgs.mkShell {
          packages = with pkgs; [
            cmake
            gcc
            gnumake
            glfw3
            glfw
            libGL
	    python3
	    pkg-config
	    glm
	    mesa
	    git
          ];
	  shellHook = ''
	  	export LIBGL_DRIVERS_PATH="${pkgs.mesa}/lib/dri"
		  export __EGL_VENDOR_LIBRARY_FILENAMES="${pkgs.mesa}/share/glvnd/egl_vendor.d/50_mesa.json"
		  export LD_LIBRARY_PATH="${pkgs.lib.makeLibraryPath [pkgs.libGL pkgs.mesa ]}:$LD_LIBRARY_PATH"
	  '';
        };
    });
}
