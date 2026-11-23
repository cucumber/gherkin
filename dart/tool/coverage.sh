#!/usr/bin/env bash
set -euo pipefail

# Called by make with a unique output path, a Dart script, and its arguments.
output=$1
script=$2
shift 2
mkdir -p "$(dirname "$output")"
service_file="${output}.service"
rm -f "$service_file"
child=
cleanup() {
  if [[ -n "$child" ]]; then
    kill "$child" 2>/dev/null || true
    wait "$child" 2>/dev/null || true
  fi
  rm -f "$service_file" "${output}.stdout"
}
trap cleanup EXIT

# The VM writes its startup banners to stdout, even with a service-info file.
dart --disable-dart-dev --enable-vm-service=0 --pause-isolates-on-exit \
  --write-service-info="$service_file" "$script" "$@" > "${output}.stdout" &
child=$!

for ((attempt = 0; attempt < 300; attempt++)); do
  if [[ -s "$service_file" ]] && uri=$(jq -er '.uri' "$service_file" 2>/dev/null); then
    break
  fi
  if ! kill -0 "$child" 2>/dev/null; then
    wait "$child"
    echo "Dart exited without starting the VM service" >&2
    exit 1
  fi
  sleep 0.1
done
if [[ -z "${uri:-}" ]]; then
  echo "Timed out waiting for the Dart VM service" >&2
  exit 1
fi

dart pub global run coverage:collect_coverage \
  --uri="$uri" --wait-paused --resume-isolates \
  --scope-output=cucumber_gherkin --out="$output" >&2
wait "$child"
child=
sed '/^The Dart VM service is listening on /d; /^The Dart DevTools debugger and profiler is available at:/d' "${output}.stdout"
