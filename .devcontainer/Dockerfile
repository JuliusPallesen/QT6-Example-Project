# [Choice] focal (20.04), jammy (22.04), lunar (23.04)
ARG VARIANT="jammy"
FROM ubuntu:${VARIANT}

# Restate the variant to use it later on in the llvm and cmake installations
ARG VARIANT

# Set the locale
#RUN sed -i '/en_US.UTF-8/s/^# //g' /etc/locale.gen && \
#    locale-gen
#ENV LANG en_US.UTF-8  
#ENV LANGUAGE en_US:en  
#ENV LC_ALL en_US.UTF-8     

# Install necessary packages available from standard repos
RUN apt-get update -qq && export DEBIAN_FRONTEND=noninteractive && \
    apt-get install -y --no-install-recommends \
    software-properties-common wget apt-utils file zip \
    openssh-client gpg-agent socat rsync \
    make ninja-build git pipx \
    python3 python3-pip python3-venv python3-setuptools

# Ensure pipx is in PATH
ENV PATH="${PATH}:/root/.local/bin"

# Install conan
RUN pipx install conan && conan --version

# By default, anything you run in Docker is done as superuser.
# Conan runs some install commands as superuser, and will prepend `sudo` to
# these commands, unless `CONAN_SYSREQUIRES_SUDO=0` is in your env variables.
ENV CONAN_SYSREQUIRES_SUDO 0
# Some packages request that Conan use the system package manager to install
# a few dependencies. This flag allows Conan to proceed with these installations;
# leaving this flag undefined can cause some installation failures.
ENV CONAN_SYSREQUIRES_MODE enabled

# User-settable versions:
# This Dockerfile should support gcc-[10, 11, 12] and clang-[10, 11, 12, 13, 14, 15]
# Earlier versions of clang will require significant modifications to the IWYU section
ARG GCC_VER="12"
# Add gcc-${GCC_VER}
RUN add-apt-repository -y ppa:ubuntu-toolchain-r/test && \
    apt-get update -qq && export DEBIAN_FRONTEND=noninteractive && \
    apt-get install -y --no-install-recommends \
    gcc-${GCC_VER} g++-${GCC_VER} gdb

# Set gcc-${GCC_VER} as default gcc
RUN update-alternatives --install /usr/bin/gcc gcc $(which gcc-${GCC_VER}) 100
RUN update-alternatives --install /usr/bin/g++ g++ $(which g++-${GCC_VER}) 100

ARG LLVM_VER="15"
# Add clang-${LLVM_VER}
ARG LLVM_URL="http://apt.llvm.org/${VARIANT}/"
ARG LLVM_PKG="llvm-toolchain-${VARIANT}-${LLVM_VER}"
RUN wget -O - https://apt.llvm.org/llvm-snapshot.gpg.key | apt-key add - 2>/dev/null && \
    add-apt-repository -y "deb ${LLVM_URL} ${LLVM_PKG} main" && \
    apt-get update -qq && export DEBIAN_FRONTEND=noninteractive && \
    apt-get install -y --no-install-recommends \
    clang-${LLVM_VER} lldb-${LLVM_VER} lld-${LLVM_VER} clangd-${LLVM_VER} \
    llvm-${LLVM_VER}-dev libclang-${LLVM_VER}-dev clang-tidy-${LLVM_VER}

# Set the default clang-tidy, so CMake can find it
RUN update-alternatives --install /usr/bin/clang-tidy clang-tidy $(which clang-tidy-${LLVM_VER}) 1

# Set clang-${LLVM_VER} as default clang
RUN update-alternatives --install /usr/bin/clang clang $(which clang-${LLVM_VER}) 100
RUN update-alternatives --install /usr/bin/clang++ clang++ $(which clang++-${LLVM_VER}) 100

# Add current cmake/ccmake, from Kitware
ARG CMAKE_URL="https://apt.kitware.com/ubuntu/"
# FALLBACK because lunar isn't support yet by kitware
ARG CMAKE_PKG=${VARIANT}
RUN wget -O - https://apt.kitware.com/keys/kitware-archive-latest.asc 2>/dev/null \
    | gpg --dearmor - | tee /etc/apt/trusted.gpg.d/kitware.gpg >/dev/null && \
    apt-add-repository -y "deb ${CMAKE_URL} ${CMAKE_PKG} main" && \
    apt-get update -qq && export DEBIAN_FRONTEND=noninteractive && \
    apt-get install -y --no-install-recommends cmake cmake-curses-gui

# Install editors
RUN apt-get update -qq && export DEBIAN_FRONTEND=noninteractive && \
    apt-get install -y --no-install-recommends \
    neovim emacs nano

# Install optional dependecies
RUN apt-get update -qq && export DEBIAN_FRONTEND=noninteractive && \
    apt-get install -y --no-install-recommends \
    doxygen graphviz ccache cppcheck xz-utils

# Install include-what-you-use
ENV IWYU /home/iwyu
ENV IWYU_BUILD ${IWYU}/build
ENV IWYU_SRC ${IWYU}/include-what-you-use
RUN mkdir -p ${IWYU_BUILD} && \
    git clone --branch clang_${LLVM_VER} \
    https://github.com/include-what-you-use/include-what-you-use.git \
    ${IWYU_SRC}
RUN CC=clang-${LLVM_VER} CXX=clang++-${LLVM_VER} cmake -S ${IWYU_SRC} \
    -B ${IWYU_BUILD} \
    -G "Unix Makefiles" -DCMAKE_PREFIX_PATH=/usr/lib/llvm-${LLVM_VER} && \
    cmake --build ${IWYU_BUILD} -j && \
    cmake --install ${IWYU_BUILD}

# Per https://github.com/include-what-you-use/include-what-you-use#how-to-install:
# `You need to copy the Clang include directory to the expected location before
#  running (similarly, use include-what-you-use -print-resource-dir to learn
#  exactly where IWYU wants the headers).`
RUN mkdir -p $(include-what-you-use -print-resource-dir 2>/dev/null)
RUN ln -s $(readlink -f /usr/lib/clang/${LLVM_VER}/include) \
    $(include-what-you-use -print-resource-dir 2>/dev/null)/include


# Build QT6
# Per https://doc.qt.io/qt-6/linux-requirements.html
RUN apt-get update -qq && export DEBIAN_FRONTEND=noninteractive && \
    apt-get install -y --no-install-recommends \
    libfontconfig1-dev libfreetype6-dev libx11-dev \
    libx11-xcb-dev libxext-dev libxfixes-dev libxi-dev \
    libxrender-dev libxcb1-dev libxcb-cursor-dev \
    libxcb-glx0-dev libxcb-keysyms1-dev \
    libxcb-image0-dev libxcb-shm0-dev libxcb-icccm4-dev \
    libxcb-sync-dev libxcb-xfixes0-dev libxcb-shape0-dev \
    libxcb-randr0-dev libxcb-render-util0-dev libxcb-util-dev \
    libxcb-xinerama0-dev libxcb-xkb-dev libxkbcommon-dev \
    libxkbcommon-x11-dev


RUN wget -O qt-archive.tar.xz "https://download.qt.io/official_releases/qt/6.6/6.6.1/single/qt-everywhere-src-6.6.1.tar.xz" && \
    openssl md5 qt-archive.tar.xz | awk '{print $2}' > /tmp/qt-archive.md5
RUN wget -O /tmp/qt-checksum.md5.txt "https://download.qt.io/official_releases/qt/6.6/6.6.1/single/md5sums.txt" && \ 
    cat /tmp/qt-checksum.md5.txt | awk 'NR==1{print $1}' > /tmp/qt-checksum.md5 && \
    cmp /tmp/qt-checksum.md5 /tmp/qt-archive.md5 && \
    tar xf qt-archive.tar.xz -C /tmp

RUN export QT_QPA_PLATFORM=xcb

WORKDIR /tmp/qt-everywhere-src-6.6.1
RUN ./configure --no-opengl && cmake --build . --parallel && cmake --install .
ENV PATH=${PATH}:/usr/local/Qt-6.6.1/bin
WORKDIR /

#RUN apt install qtwayland5

## Cleanup cached apt data we don't need anymore
RUN apt-get autoremove -y && apt-get clean && \
    rm -rf /var/lib/apt/lists/*

## Install ARM GCC toolchain
# RUN wget -O archive.tar.xz "https://developer.arm.com/-/media/Files/downloads/gnu/12.2.rel1/binrel/arm-gnu-toolchain-12.2.rel1-x86_64-arm-none-eabi.tar.xz?rev=7bd049b7a3034e64885fa1a71c12f91d&hash=732D909FA8F68C0E1D0D17D08E057619" && \
#     echo 84be93d0f9e96a15addd490b6e237f588c641c8afdf90e7610a628007fc96867 archive.tar.xz > /tmp/archive.sha256 && sha256sum -c /tmp/archive.sha256 && rm /tmp/archive.sha256 && \
#     tar xf archive.tar.xz -C /opt

# Allow the user to set compiler defaults
ARG USE_CLANG
# if --build-arg USE_CLANG=1, set CC to 'clang' or set to null otherwise.
ENV CC=${USE_CLANG:+"clang"}
ENV CXX=${USE_CLANG:+"clang++"}
# if CC is null, set it to 'gcc' (or leave as is otherwise).
ENV CC=${CC:-"gcc"}
ENV CXX=${CXX:-"g++"}

# Include project
#ADD . /workspaces/cpp_project
#WORKDIR /workspaces/cpp_project

CMD ["/bin/bash"]
