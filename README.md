# Lumons

This is a lazy pet project to:

- Make myself familiar with [Luigi](https://github.com/nakst/luigi) (and maybe migrate to Luigi2, possibly contributing along the way)
- Make myself familiar with DDC in general and [ddcutil](https://github.com/rockowitz/ddcutil) in particular
- Freshen my C skills

The idea is to have a small widget to control the overall brightness of all monitors at once (e.g., level it out, make it responsive to an external sensor or a schedule, etc.).

What cannot be done with DDC should then be done by other means.

## Installation

- **Luigi**: plug-and-play. Just add it to `/lib`.
- **ddcutil**: Please refer to the official documentation. I use `2.2.1-dev` with a dynamic lib, which comes with its own toll I’m ready to pay, but you probably won’t.


## Building

```bash
make && make run;
```

simple as that (or is it?).