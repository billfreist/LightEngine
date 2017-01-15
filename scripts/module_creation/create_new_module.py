
import os
import sys
import argparse
import shutil

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--name', help='foo help')
    args = parser.parse_args()

    moduleDir = os.path.join('../../engine/modules/', args.name)
    if os.path.exists(moduleDir):
        raise

    # Copy directory tree
    shutil.copytree('template', moduleDir)

    # Recursively rename files and replace symbols
    for base, dirs, files in os.walk(moduleDir, topdown=False):
        # Files first
        for f in files:
            # Rename file names
            prev = os.path.join(base, f)
            split = os.path.split(prev)
            new = os.path.join(split[0], split[1].replace('template_proj', args.name))
            os.rename(prev, new)

            # Replace symbols in code
            with open(new, "r+") as fContents:
                fileData = str(fContents.read()).replace('template_proj', args.name)
                fContents.seek(0)
                fContents.write(fileData)
                fContents.truncate()

        # Now directories
        for d in dirs:
            prev = os.path.join(base, d)
            split = os.path.split(prev)
            new = os.path.join(split[0], split[1].replace('template_proj', args.name))
            os.rename(prev, new)

if __name__ == "__main__":
   main()
