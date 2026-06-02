{
  description = "sch-core - implementation and computation algorithms for the convex hulls";

  inputs.mc-rtc-nix.url = "github:mc-rtc/nixpkgs";

  outputs =
    inputs:
    inputs.mc-rtc-nix.lib.mkFlakoboros inputs (
      { lib, ... }:
      {
        overrideAttrs.sch-core = {
          src = lib.cleanSource ./.;
        };
      }
    );
}
