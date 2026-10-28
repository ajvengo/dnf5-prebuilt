# Bazel Central Registry

Templates used by `.github/workflows/publish.yaml`
([publish-to-bcr](https://github.com/bazel-contrib/publish-to-bcr)) to open a
pull request against the Bazel Central Registry for every release. See
<https://github.com/bazel-contrib/publish-to-bcr/blob/main/templates/README.md>.

The source archive referenced by `source.template.json` is created by
`.github/workflows/release_prep.sh`: unlike the git tag, it contains the
integrity of the prebuilt dnf5 archives in `dnf5-prebuilt/private/versions.bzl`.
