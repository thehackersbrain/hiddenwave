# HiddenWave
> Hide your personal Data inside Audio wav file

> Written in C++ by Gaurav Raj \[TheHackersBrain\]

![bannerImage](https://raw.githubusercontent.com/thehackersbrain/thehackersbrain.github.io/master/images/joker/hiddenwave.png)

Hiddenwave is a simple audio steganograpy tool written in **C++** for hidding your files or messages inside a `.wav` or `.mp3` audio file.
This tool is inspired by [HiddenWave](https://github.com/techchipnet/HiddenWave) created by [Techchip](https://github.com/techchipnet).

**NOTE:** This tool only supports `.mp3` and `.wav` audio file and can hide any other files inside the audio file.


## Version
**Hiddenwave 1.0.0** \(Early Release\)


## Requirement
- [libboost-all-dev](https://packages.debian.org/search?keywords=libboost-all-dev)
    ```
    sudo apt install libboost-all-dev -y
    ```
- [cmake](https://cmake.org/)
    ```
    sudo apt install cmake -y
    ```


## Installation and Uses
- Make Sure all requirements are installed
```
sudo apt install libboost-all-dev cmake -y
```
- Git clone this repo and change the directory
```
git clone https://github.com/thehackersbrain/hiddenwave.git && cd hiddenwave
```
- Now Build the package
```
mkdir build && cd build && cmake ..
```
- Now make the final binary
```
make
```
- Copy the binary in `/usr/bin/` for easy access \(optional\)
```
sudo cp hiddenwave /usr/bin/
```


## How to Use


### Hiding Data
- For hiding files inside `.wav` audio file.
    ```
    ./hiddenwave -i input.wav -f filetobehidden.txt -o output.wav
    ```
- For hiding message inside `.wav` audio file.
    ```
    ./hiddenwave -i input.wav -m 'Dummy Message' -o output.wav
    ```


### Extracting Data

```
./hiddenwave -i output.wav
```
- If the hidden data is some message, it will be printed on the terminal.
- If the hidden data is a file, it will be extracted on the current directory.


## Credits
**Inspired by:** [HiddenWave](https://github.com/techchipnet/HiddenWave) by [Techchip](https://github.com/techchipnet)

## Author

**Creator:** [Gaurav Raj](https://github.com/thehackersbrain/)
**Portfolio:** [Here](https://thehackersbrain.github.io/)
**Blog:** [TheHackersBrain Blog](https://thehackersbrain.pythonanywhere.com)
**Projects:** [Here](https://github.com/thehackersbrain?tab=repositories)
**Twitter:** [@thehackersbrain](https://twitter.com/thehackersbrain)
**TryHackMe:** [hackersbrain](https://tryhackme.com/p/hackersbrain)
