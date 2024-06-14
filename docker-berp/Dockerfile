# Builds a docker image used for building most projects in this repo. It's
# used both by contributors and CI.
#
FROM mcr.microsoft.com/dotnet/sdk:6.0

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
