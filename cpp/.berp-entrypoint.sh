#!/bin/bash
# Entrypoint that makes berp accessible to non-root users, then drops privileges.
# Usage: docker run ... --entrypoint /workspaces/gherkin/.berp-entrypoint.sh berp-env
set -e

BERP_TOOLS=/root/.dotnet/tools

# Make berp reachable by non-root users without changing file ownership
chmod o+rx /root /root/.dotnet /root/.dotnet/tools

exec setpriv \
    --reuid="${RUNAS_UID:-1000}" \
    --regid="${RUNAS_GID:-1000}" \
    --clear-groups \
    env \
        PATH="${BERP_TOOLS}:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin" \
        HOME=/tmp \
    "${@:-bash}"
