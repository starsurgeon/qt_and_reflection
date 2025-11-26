# clang-p2996 + Qt6 (Docker)

This repository builds Bloomberg's `clang-p2996` toolchain and provides a final runtime image with Qt6 development packages installed.

Quick build

```bash
cd /home/amue/projects/qt_and_reflection
DOCKER_BUILDKIT=1 docker build --progress=plain -t clang-p2996:latest .
```

Run container and verify

```bash
docker run --rm clang-p2996:latest qmake6 --version
# check headers (Debian multiarch path; symlink created at /usr/include/qt6)
docker run --rm clang-p2996:latest bash -lc "ls -l /usr/include/qt6 && ls -d /usr/include/qt6/QtCore || true"
```

Notes

- The Dockerfile builds clang and installs it into `/opt/clang-p2996`.
- Qt6 dev packages are installed in the final image. Debian places headers in the multiarch path `/usr/include/x86_64-linux-gnu/qt6`; a symlink is created at `/usr/include/qt6` for compatibility.
- If you want a minimal runtime (no Qt dev packages) adjust the final-stage `apt-get install` in `Dockerfile`.
