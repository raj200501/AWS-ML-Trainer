#!/bin/bash
set -euo pipefail

ROOT_DIR=$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)
CONFIG_PATH="$ROOT_DIR/config/app_config.env"

"$ROOT_DIR/build/build.sh"

"$ROOT_DIR/build/output/AWSMLTrainer" --config "$CONFIG_PATH"

MODEL_PATH="$ROOT_DIR/output/model.json"
if [[ ! -f "$MODEL_PATH" ]]; then
  echo "Expected model artifact at $MODEL_PATH" >&2
  exit 1
fi

if ! grep -q '"model"' "$MODEL_PATH"; then
  echo "Model artifact missing expected content" >&2
  exit 1
fi

if ! grep -q '"metrics"' "$MODEL_PATH"; then
  echo "Model metrics missing expected content" >&2
  exit 1
fi

echo "Verification completed successfully."
