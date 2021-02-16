# Doxygen
Install Doxygen on your system.

To generate, build target `doxygen` through CMake.

It will output into directories:
* `docs/doxygen/html` (open `docs/doxygen/html/index.html` in browser to view)
* `docs/doxygen/xml` (used by Sphinx)

# Sphinx
Sphinx documentation looks much nicer than Doxygen.

Required Python packages:
* `sphinx`
* `sphinx_rtd_theme`
* `breathe`
* `exhale`

To generate:
* Must have generated Doxygen xml output first
* `cd` [`docs/sphinx` directory]
* Execute `make html` or `.\make.bat html` depending on platform
* Output will be in `docs/sphinx/_build/html` (open `docs/sphinx/_build/html/index.html` in browser to view)
