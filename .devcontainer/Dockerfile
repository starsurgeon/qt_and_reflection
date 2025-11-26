FROM clang-p2996:latest

# Install build tools for developing inside the container
ARG DEBIAN_FRONTEND=noninteractive
RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake ninja-build build-essential pkg-config \ 
    && rm -rf /var/lib/apt/lists/*

WORKDIR /workspace
