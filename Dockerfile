# Builds a docker image used for building most projects in this repo. It's
# used both by contributors and CI.
#
FROM mcr.microsoft.com/dotnet/sdk:6.0

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update \
    && apt-get install --assume-yes \
    make \
    golang

WORKDIR /app

## Trigger first run experience by running arbitrary cmd to populate local package cache
RUN dotnet --list-sdks

# Install Berp (dotnet tool installs are user-global; not system global)
RUN dotnet tool install --global Berp --version 1.4.0 \
      && echo 'export PATH="$PATH:/root/.dotnet/tools"' >> ~/.bashrc

WORKDIR /app

CMD ["/bin/bash"]
