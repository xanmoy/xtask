# XTask

This is a simple task manager program for Linux systems that displays information about running processes.

## Requirements

- Linux-based operating system
- `gcc` compiler
- `ncurses` library



## Installation
1. **Clone The Repository**

```sh
git clone https://github.com/xanmoy/xtask.git
```
2. **Install ncurses library:**
For RHEL based systems
   ```sh
   sudo yum install ncurses-devel
   
   ```
   or
   ```sh
   sudo dnf install ncurses-devel
   
   ```
For Debian based systems
   ```sh
   sudo apt install libncurses-dev

   ```
   
For Arch based systems
   ```sh
   sudo pacman -S ncurses

   ```
For Gentoo Linux
```sh
sudo emerge --sync

```

```sh
sudo emerge --ask sys-libs/ncurses

```



3. **Compile the program:**
```sh
    gcc -o xtask xtask.c -lncurses

```

4. **Run the program:**
```sh
./xtask
```

5. **Install The Program**
```sh
sudo make install
```
The program will continuously display the list of processes with their PID, command name, state, memory usage, and CPU usage. The screen updates every 2 seconds.

## Controls
Use Ctrl+C to exit the program.

## Structure
xtask.c: Source code of the XTask.
README.md: This file providing instructions and information about the program.
Makefile: 
Contributing
Contributions are welcome! If you find any issues or have suggestions for improvements, please open an issue or submit a pull request.

## License
This project is licensed under the [MIT License](https://github.com/xanmoy/xtask/blob/main/LICENSE) - see the LICENSE file for details.


