# Text separation library
### From [SeveraTheDuck](https://github.com/SeveraTheDuck)

## Contents
1. [Short description](#short-description)
2. [Install guide](#install-guide)
3. [Usage](#usage)

## Short description
The [repository](https://github.com/SeveraTheDuck/TextSeparationLibrary) contains library which reads text from file and separates it into strings by a separation symbol.

## Install guide
1. Download the [repository](https://github.com/SeveraTheDuck/TextSeparationLibrary) from github or use
`git clone https://github.com/SeveraTheDuck/TextSeparationLibrary`.
2. Copy `include` and `source` folders to your project.

## Usage
The lib has following interface:
1. `SeparateTextFile (filename, separator)` function gets name of file and separation symbol.
It returns a structure with buffer, array of strings separated by separator and their number.
2. `DestroySeparation (text_separation)` function gets the structure and destroys it.
