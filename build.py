import subprocess
import sys
from pathlib import Path

binary_name = "lsj"

Path("build").mkdir(parents=True, exist_ok=True)

subprocess.run(
    [
        "clear",
    ],
    stdout=open("/dev/tty", "w")
)

result = subprocess.run(
    [
        "clang",
        "-g",
        "main.c",
        "third_party/cjson/cJSON.c",
        "-o",
        "build/" + binary_name,
        *sys.argv[1:],
    ],
)

try:
    if result.returncode != 0:
        raise subprocess.CalledProcessError(result.returncode, "clang")
    subprocess.run(
        [
            "./build/" + binary_name,
            *sys.argv[1:]
        ],
    )
except subprocess.CalledProcessError as e:
    print(f"Compile failed with exit code {e.returncode}", file=sys.stderr)
    sys.exit(e.returncode)

