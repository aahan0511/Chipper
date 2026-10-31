# CHIP-8 Emulator

This project is a CHIP-8 emulator for [Hack Club's Chipper](https://chipper.hackclub.com/).

## Running

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
just execute
```

Direct:
```bash
./build/Chipper
```

---

### Other just commands:

```bash
just run
```
> Compiles and runs the code

```bash
just run-with-build
```
> Builds, compiles and then runs the codes
