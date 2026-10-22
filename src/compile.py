from pathlib import Path
import subprocess
import argparse


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument(
        "directories",
        nargs="+",
        type=Path,
        help="One or more directories to process",
    )
    args = parser.parse_args()

    for directory in args.directories:
        for file in directory.rglob("*"):
            if file.is_file() and file.suffix in {".vert", ".frag", ".geom", ".tesc", ".tese", ".comp"}:
                output = file.with_suffix(file.suffix + ".spv")
                subprocess.run(
                    ["glslc", str(file), "-o", str(output)],
                    check=True,
                )


if __name__ == "__main__":
    main()
