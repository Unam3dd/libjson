FROM debian:12-slim

RUN apt-get update && \
    apt-get install git python3 python3-pip pkg-config libbsd-dev -y && \
	pip install meson==1.5.1 ninja --break-system-packages && apt-get clean

