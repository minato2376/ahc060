FROM gcc:15.2.0 AS gcc-source

FROM mcr.microsoft.com/devcontainers/base:trixie

RUN apt-get update && apt-get install -y --no-install-recommends \
        libc6-dev \
        binutils \
        make \
        gdb \
        curl \
        ca-certificates \
        zlib1g-dev \
        unzip \
        clang-format \
        python3 \
        python3-venv \
    && rm -rf /var/lib/apt/lists/*

COPY --from=gcc-source /usr/local/ /usr/local/

ENV PATH="/usr/local/bin:${PATH}"

RUN echo '/usr/local/lib64' > /etc/ld.so.conf.d/000-local-lib.conf \
    && echo '/usr/local/lib' >> /etc/ld.so.conf.d/000-local-lib.conf \
    && ldconfig

RUN update-alternatives --install /usr/bin/cc  cc  /usr/local/bin/gcc 999 \
    && update-alternatives --install /usr/bin/gcc gcc /usr/local/bin/gcc 999 \
    && update-alternatives --install /usr/bin/g++ g++ /usr/local/bin/g++ 999 \
    && update-alternatives --install /usr/bin/c++ c++ /usr/local/bin/g++ 999

RUN gcc --version && g++ --version \
    && gcc -print-search-dirs \
    && echo '#include <iostream>\nint main(){ std::cout<<"C++23 ready\\n"; }' > /tmp/test.cpp \
    && g++ -std=c++23 -O2 -pipe -o /tmp/test /tmp/test.cpp \
    && /tmp/test \
    && rm /tmp/test.cpp /tmp/test

ENV VIRTUAL_ENV=/opt/venv
COPY requirements.txt /tmp/requirements.txt
RUN curl -LsSf https://astral.sh/uv/install.sh | sh \
    && . $HOME/.local/bin/env \
    && uv venv $VIRTUAL_ENV \
    && uv pip install -p $VIRTUAL_ENV -r /tmp/requirements.txt \
    && rm /tmp/requirements.txt
ENV PATH="$VIRTUAL_ENV/bin:${PATH}"

ENV RUSTUP_HOME=/usr/local/rustup \
    CARGO_HOME=/usr/local/cargo \
    PATH="/usr/local/cargo/bin:${PATH}"
RUN curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh -s -- -y --default-toolchain stable \
    && rustc --version && cargo --version

RUN curl -fsSL https://claude.ai/install.sh | bash
