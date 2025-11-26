FROM ubuntu:24.04 AS builder

ARG DEBIAN_FRONTEND=noninteractive
ARG LLVM_SRC_DIR=/opt/src/clang-p2996
ARG LLVM_BUILD_DIR=/opt/build/clang-p2996
ARG LLVM_INSTALL_PREFIX=/opt/clang-p2996
ARG LLVM_BRANCH=p2996

RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential git ninja-build cmake python3 ca-certificates pkg-config \
    zlib1g-dev libtinfo-dev libxml2-dev libedit-dev libncurses-dev libzstd-dev \
    liblzma-dev libcurl4-openssl-dev libssl-dev \
    qt6-base-dev qt6-base-dev-tools qmake6 qt6-tools-dev qt6-tools-dev-tools \
    && rm -rf /var/lib/apt/lists/*

RUN mkdir -p $(dirname ${LLVM_SRC_DIR}) && \
    git clone --depth 1 --branch ${LLVM_BRANCH} \
      https://github.com/bloomberg/clang-p2996.git \
      ${LLVM_SRC_DIR}

WORKDIR ${LLVM_SRC_DIR}

# Configure, build, install, then remove build tree & source in the same stage.
RUN mkdir -p ${LLVM_BUILD_DIR} && \
    cmake -G Ninja \
      -S llvm \
      -B ${LLVM_BUILD_DIR} \
      -DCMAKE_BUILD_TYPE=Release \
    -DLLVM_ENABLE_PROJECTS="clang;clang-tools-extra;lld;compiler-rt" \
    -DLLVM_ENABLE_RUNTIMES="libcxx;libcxxabi;libunwind" \
      -DLLVM_TARGETS_TO_BUILD="X86" \
      -DLLVM_INCLUDE_TESTS=OFF \
      -DLLVM_INCLUDE_EXAMPLES=OFF \
      -DLLVM_INCLUDE_BENCHMARKS=OFF \
      -DCMAKE_INSTALL_PREFIX=${LLVM_INSTALL_PREFIX} && \
    ninja -C ${LLVM_BUILD_DIR} install && \
    rm -rf ${LLVM_BUILD_DIR} ${LLVM_SRC_DIR}

# Final slimmer image with only the installed toolchain
FROM ubuntu:24.04

ARG LLVM_INSTALL_PREFIX=/opt/clang-p2996

# Install any minimal runtime dependencies you need (example: ca-certificates)
RUN apt-get update && apt-get install -y --no-install-recommends ca-certificates \
  libqt6core6 libqt6gui6 libqt6widgets6 \
  qt6-base-dev qt6-base-dev-tools qmake6 qt6-tools-dev qt6-tools-dev-tools \
  && rm -rf /var/lib/apt/lists/*
COPY --from=builder ${LLVM_INSTALL_PREFIX} ${LLVM_INSTALL_PREFIX}

# Provide a convenient include path for tools that expect `/usr/include/qt6`
RUN ln -s /usr/include/x86_64-linux-gnu/qt6 /usr/include/qt6 || true

COPY --from=builder ${LLVM_INSTALL_PREFIX} ${LLVM_INSTALL_PREFIX}

ENV PATH="${LLVM_INSTALL_PREFIX}/bin:${PATH}" \
    CC="${LLVM_INSTALL_PREFIX}/bin/clang" \
    CXX="${LLVM_INSTALL_PREFIX}/bin/clang++"

WORKDIR /workspace
CMD ["/bin/bash"]