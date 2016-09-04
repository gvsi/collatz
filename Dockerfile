FROM gcc:5.3

RUN wget -O - http://llvm.org/apt/llvm-snapshot.gpg.key | apt-key add - 
RUN echo "deb http://llvm.org/apt/trusty/ llvm-toolchain-trusty main" >> /etc/apt/sources.list

RUN apt-get update                  && \
    apt-get -y install cmake        && \
    apt-get -y install libboost-dev && \
    apt-get -y install doxygen      && \
    apt-get -y install libgtest-dev && \
    apt-get -y install valgrind     && \
    apt-get -y install clang        && \
    apt-get -y install clang-format-3.5 && \
    cd /usr/src/gtest               && \
    cmake CMakeLists.txt            && \
    make                            && \
    cp *.a /usr/lib                 && \
    cd -                            && \
    ln -s /usr/lib/llvm-3.5/bin/clang-format /usr/bin/clang-format

CMD bash
