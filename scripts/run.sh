#!/bin/bash
set -euo pipefail

ROOT_DIR=$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)
CONFIG_PATH="${1:-$ROOT_DIR/config/app_config.env}"

"$ROOT_DIR/build/build.sh"

"$ROOT_DIR/build/output/AWSMLTrainer" --config "$CONFIG_PATH"
