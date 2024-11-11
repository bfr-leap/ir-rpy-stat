# ir-rpy-stat(1)
## NAME

ir-rpy-stat - display metadata information for iRacing .rpy replay files

## SYNOPSIS

```bash
Copy code
ir-rpy-stat [OPTION]... FILE...
```
## DESCRIPTION

The `ir-rpy-stat` command displays metadata for `.rpy` replay files from iRacing. This command extracts key details such as `user_id`, `session_id`, `track`, `layout`, `user_name`, and more. It supports customizable output formats using format sequences similar to the stat command.

## OPTIONS

 - `-f FORMAT, --format=FORMAT`

    Use the specified FORMAT instead of the default; output a newline after each use of FORMAT.

    **Format sequences for `FORMAT`:**

    | Sequence	| Field Description     |
    | --------- | --------------------- |
    | %c        | Car Id                |
    | %H        | Host Zone             |
    | %L        | Layout                |
    | %l        | League Id             |
    | %n        | File Name             |
    | %S        | Session Id            |
    | %s        | Subsession Id         |
    | %T        | Track                 |
    | %t        | Timestamp             |
    | %%	    | Literal `%` character |

    **Example:**
    ```bash
    ir-rpy-stat --format="User ID: %u\nTrack: %t\n" replay.rpy
    ```

 - `-c, --compact`

    Display a compact view of essential fields, typically limited to user_id, session_id, and track.

 - `--help`

    Display help information and exit.

 - `--version`

    Display version information and exit.

## EXAMPLES

 - Display all metadata for a single file:

    ```bash
    ir-rpy-stat replay.rpy
    ```
 - Show user ID and track using format sequences:

    ```bash
    ir-rpy-stat --format="%u %t" replay.rpy
    ```

 - Custom output with labels using --format:

    ```bash
    ir-rpy-stat --format="User: %U\nTrack: %t\n" replay.rpy
    ```

## FORMAT SEQUENCES DETAILS

| Sequence	| Field Description     |
| --------- | --------------------- |
| %c        | Car Id                |
| %H        | Host Zone             |
| %L        | Layout                |
| %l        | League Id             |
| %n        | File Name             |
| %S        | Session Id            |
| %s        | Subsession Id         |
| %T        | Track                 |
| %t        | Timestamp             |
| %%	    | Literal `%` character |

## EXIT STATUS

Returns 0 if successful, or a non-zero error code in case of an error.

## SEE ALSO

stat(1), ls(1)

## AUTHOR

Written by Arturo Mayorga.

## COPYRIGHT

This is free software; see the source for copying conditions. There is NO warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

