# Flux Language

Flux is a modern programming language designed for simplicity and efficiency, compiling directly into assembly code. This README provides an overview of the language, its features, and instructions for getting started.

## Features

- **Compilation to Assembly**: Flux compiles high-level code into low-level assembly, allowing for optimized performance.
- **Executable Generation**: The compiler generates `.o` files and produces executable binaries that can be run on various platforms.
- **Easy to Use**: With a straightforward syntax, Flux is designed to be accessible for both beginners and experienced programmers.
- **Package Management**: Flux includes a built-in package manager for easy installation and management of libraries and dependencies.

## Getting Started

### Installation

To install Flux, follow these steps:

1. Clone the repository:
   ```
   git clone https://github.com/yourusername/fluxlang.git
   cd fluxlang
   ```

2. Build the project using the provided Makefile:
   ```
   make
   ```

3. Ensure that the `fluxl` command is available in your PATH.

### Compiling a Flux Program

To compile a Flux source file, use the following command:

```
fluxl <source_file.flx>
```

This will generate an executable from the specified Flux source file.

### Running a Flux Program

After compiling, you can run the generated executable directly from the command line.

### Using the Package Manager

The Flux package manager (`fluxpkg`) allows you to install and manage packages easily. To install a package, use:

```
fluxpkg install <package_name>
```

## Example

Here is a simple example of a Flux program:

```flux
mod <"stdio">

int main() {
    stdio::out("Welcome to the Flux Language!");
    return 0;
}
```

Save this code in a file named `example.flx` and compile it using:

```
fluxl example.flx
```

## Contributing

Contributions are welcome! Please submit a pull request or open an issue for any suggestions or improvements.

## License

This project is licensed under the MIT License. See the LICENSE file for more details.