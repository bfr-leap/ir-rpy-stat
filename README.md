# ir-rpy-stat

**`ir-rpy-stat`** is a command-line tool that extracts and displays metadata from iRacing replay files (`.rpy`). This tool provides essential details such as the user ID, session ID, track, layout, and other metadata related to replay files, making it easier for users to analyze race data.

## Features

- Display detailed metadata about `.rpy` replay files
- Supports custom output formats using format sequences (like `stat`)
- Filter output to show only specific metadata fields
- Compact view mode for essential fields

## Usage Documentation
For usage details, visit the [manpage](man.md).

## Installation

 - **Clone the repository**:

   ```bash
   git clone https://github.com/yourusername/ir-rpy-stat.git
   cd ir-rpy-stat
   ```
 - **Dependencies**:
    ```bash
    sudo apt-get install libcxxopts-dev
    sudo apt-get install lcov
    ```
