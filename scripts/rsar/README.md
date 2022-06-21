# RSAR

As an attempt to understand better `procfs`, I'm building my own sar-like tool, rsar.
Feel free to use, report bugs, make suggestions and contribute.

*Disclaimer:* It's currently a work in progress.


## How to run/build

1. Clone the repo
2. Just run

   ```bash
   $ go run rsar.go <paramters ...>
   ```

3. Or build and run

   ```bash
   $ go build rsar.go
   $ ./rsar <paramters ...>
   ```

## How to use

- Usage:

  -`./rsar --<option> <number of samples> <interval between samples>` 

- Options:

  -`--help:` to get help

  -`--load:` load average statistics

  -`--mem:`  memory statistics

  -`--swap:` swap statistics

  -`--pps:`  per-process statistics


## Features

- General performance metrics
- Shows per-process performance metrics
