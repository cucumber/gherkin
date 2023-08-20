# Builds a docker image used for building most projects in this repo. It's
# used both by contributors and CI.
#
FROM ubuntu:22.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update \
    && apt-get install --assume-yes \
    locales

RUN locale-gen en_US.UTF-8
ENV LANG en_US.UTF-8
ENV LANGUAGE en_US:en
ENV LC_ALL en_US.UTF-8

WORKDIR /app

RUN apt-get update && apt-get --assume-yes upgrade

# Create a cukebot user. Some tools (Bundler, npm publish) don't work properly
# when run as root
ENV USER=cukebot
ENV UID=1000
ENV GID=2000

RUN addgroup --gid "$GID" "$USER" \
    && adduser \
    --disabled-password \
    --gecos "" \
    --ingroup "$USER" \
    --uid "$UID" \
    --shell /bin/bash \
    "$USER"

# Install .NET Core
# https://github.com/dotnet/dotnet-docker/blob/5c25dd2ed863dfd73edb1a6381dd9635734d0e5f/2.2/sdk/bionic/amd64/Dockerfile
ENV DOTNET_CLI_TELEMETRY_OPTOUT=true
## Install .NET CLI dependencies
RUN apt-get update \
    && apt-get install --assume-yes --no-install-recommends \
    curl \
    ca-certificates \
    libicu-dev \
    && rm -rf /var/lib/apt/lists/*

## Install .NET Core SDK
ENV DOTNET_SDK_VERSION 6.0

COPY scripts/install-dotnet.sh .
RUN ./install-dotnet.sh -c $DOTNET_SDK_VERSION --install-dir /usr/share/dotnet \
    && ln -s /usr/share/dotnet/dotnet /usr/bin/dotnet
RUN rm install-dotnet.sh

## Trigger first run experience by running arbitrary cmd to populate local package cache
RUN dotnet --list-sdks

USER $USER

## As a user install node and npm via node version-manager
WORKDIR /home/$USER

# Install Berp (dotnet tool installs are user-global; not system global)
RUN dotnet tool install --global Berp --version 1.4.0 \
      && echo 'export PATH="$PATH:/home/cukebot/.dotnet/tools"' >> ~/.bashrc

WORKDIR /app


CMD ["/bin/bash"]
