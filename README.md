# BIB Parser

A BibTeX parser implementation for the software engineering internship at TU Chemnitz 2020.

BIB Parser is a command line utility designed to easily translate BibTeX reference lists into other file formats like HTML, XML or PDF. The user can configure the tool using a .ini file and sort the references contained in the source file.

## Usage

The BIB Parser offers two subcommands: `convert` and `check`.

The style file is a simple key value map with one section for each output format, and a common section for scalar values. After a scalar type is issued to each field type used in the .bib file, the details for converting the field type into the specific output file must be given. This might look so:
```
author=string # Author is a string
pages=range # Pages is a range of numbers
title=string # ...

[html]
author=p # Author will be a p tag
title=h1 # Title will be a h1 tag
pages=span # Pages will be a span tag

[xml]
author=author # Author will be placed into <author>string</author>
pages=pages # Pages will be placed into <pages>range</pages>

[xml]
author=text # Author will be put into the document as text # The only type supported for PDF currently
```

For further configuration options, please see the [example .ini file](./test/data/style.ini).

### Convert

```
Convert a BibTeX file to other file formats.
Usage: ./cmd/bib-parser convert [OPTIONS]

Options:
  -h,--help                   Print this help message and exit
  -i,--input TEXT REQUIRED    Path to the input file containing BibTeX definitions.
  -o,--output TEXT REQUIRED   Path pointing to where the output file will be put.
  -c,--config TEXT REQUIRED   Path to the configuration file containing translation rules for semantic tags.
  -t,--type ENUM:value in {html->0,pdf->1,xml->2} OR {0,1,2} REQUIRED
                              XML, PDF or HTML
  -s,--sort ENUM:value in {author-asc->1,author-desc->2,key-asc->3,key-desc->4,type-asc->5,type-desc->6} OR {1,2,3,4,5,6}
                              Can be used to sort the BibTeX entries.
```

### Check

```
Check a BibTeX file for semantic errors.
Usage: ./cmd/bib-parser check [OPTIONS]

Options:
  -h,--help                   Print this help message and exit
  -i,--input TEXT REQUIRED    Path to the input file containing BibTeX definitions.
```

## Building

BIB Parser requires C++ compiler supporting the C++17 standard, and CMake installed.

```bash
git clone https://github.com/saaymeen/bib-parser.git
mkdir bib-parser/build
cd bib-parser/build
cmake -G"Unix Makefiles" .. # Pick your favourite generator
make -j4 # Number of cores
```

---

Please visit the [Wiki](https://github.com/saaymeen/bib-parser/wiki) for any additional information.
