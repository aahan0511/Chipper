# CHIP-8 Emulator

This project is a CHIP-8 emulator for [Hack Club's Chipper](https://chipper.hackclub.com/) written in C++ and raylib.
The emulator implements the base CHIP-8 instructions with quirks aligned to the original COSMIC VIP.

## Running

You can change the settings and quirks inside `./settings.hpp`.

### Build

If you have [`just`](https://github.com/casey/just):
```bash
just build
```

otherwise you can use the command directly:
```bash
cmake -B build
```

### Compile

With `just`:
```bash
just compile
```

Direct:
```bash
cmake --build build
```

### Execute

With `just`:
```bash
just execute <file>
```

Direct:
```bash
./build/Chipper <file>
```

---

### Other just commands:

```bash
just run <file>
```
> Compiles and runs the code

```bash
just run-with-build <file>
```
> Builds, compiles and then runs the code

```bash
just test <chip8-test-suite directory>
```
> Goes through test one to seven in the CHIP-8 Test Suite and runs them one by one.

## To-do

- [x] Make the base CHIP-8 emulator
- [ ] Make a frontend around the emulator
- [ ] Add SUPER-CHIP support (maybe)
- [ ] Add XO-CHIP support (maybe)

## Credits

Most of my work is based on [Guide to making a CHIP-8 emulator](https://tobiasvl.github.io/blog/write-a-chip-8-emulator/) by [Tobias V. I. Langhoff](https://github.com/tobiasvl), he really has written an amazing guide.

And without [Timendus' CHIP-8 test suite](https://github.com/Timendus/chip8-test-suite), I would not have been able to work out any of the bugs and quirks.

Huge thanks to both of them!
