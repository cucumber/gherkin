# Minimal utility needed to generate parsers and distribute the
# gherking-language.json to all language implementations.
#
# See CONTRIBUTING.md
#
FROM mcr.microsoft.com/dotnet/sdk:8.0

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update \
    && apt-get install --assume-yes \
    make \
    jq


WORKDIR /app

## Trigger first run experience by running arbitrary cmd to populate local package cache
RUN dotnet --list-sdks

# Install Berp (dotnet tool installs are user-global; not system global)
RUN dotnet tool install --global Berp --version 1.5.0 \
      && echo 'export PATH="$PATH:/root/.dotnet/tools"' >> ~/.bashrc

WORKDIR /app

CMD ["/bin/bash"]
