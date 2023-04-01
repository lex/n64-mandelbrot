# n64-mandelbrot

Fractals on a Nintendo 64. This project is an implementation of the Mandelbrot set fractal visualization on the Nintendo 64 using the libdragon library. Users can zoom in/out and move the view using the controller.

## Prerequisites

- Install [libdragon](https://libdragon.dev/): Follow the instructions on the libdragon website to set up the development environment.
- Install an N64 emulator like [ares](https://ares-emu.net/) or have a real Nintendo 64 console with a development cartridge.

## Building the project

To build the project, navigate to the project directory and execute the following command:

```sh
$ libdragon make
```

This will generate a `.z64` ROM file that you can run on an emulator or a real console.

## Running the project

### On an emulator

1. Open your N64 emulator (e.g., ares).
2. Load the `.z64` ROM file generated during the build process.
3. Enjoy the Mandelbrot fractal visualization.

### On a real console

1. Transfer the `.z64` ROM file to your development cartridge.
2. Insert the development cartridge into your Nintendo 64 console.
3. Power on the console and enjoy the Mandelbrot fractal visualization.

## Controls

Use the D-pad on the controller to navigate the Mandelbrot set:

- Up: Zoom in
- Down: Zoom out
- Left: Move view to the left
- Right: Move view to the right

## License

This project is licensed under the terms of the [BSD-3 License](LICENSE).
