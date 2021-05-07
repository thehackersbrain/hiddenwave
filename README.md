# HiddenWave
> Hide your personal Data inside The Audio wav file<br/>
> Written in C++ by Gaurav Raj \[TheHackersBrain\]

![bannerImage](https://raw.githubusercontent.com/thehackersbrain/thehackersbrain.github.io/master/images/joker/hiddenwave.png)

Hiddenwave is a simple audio steganography tool written in **C++** for hiding your files or messages inside a `.wav` or `.mp3` audio file. You might be wondering, In **C++** ?? You could have done it easily in **Python**. I could but we are hackers Gentleman, We love challenges :smile:
This tool is inspired by [HiddenWave](https://github.com/techchipnet/HiddenWave) created by [Techchip](https://github.com/techchipnet).

**NOTE:** This tool only supports the `.mp3` and `.wav` audio files and can hide any other files inside the audio file.

## Version
**Hiddenwave 1.2.1**

## Requirement
- [libboost-all-dev](https://packages.debian.org/search?keywords=libboost-all-dev)
    ```
    sudo apt install libboost-all-dev -y
    ```
- [cmake](https://cmake.org/)
    ```
    sudo apt install cmake -y
    ```

## Todo
- [x] Adding Support to hide files inside audio files
- [x] Adding Support to `.mp3` files
- [x] Improving UI by adding some colors

## Installation and Uses

### Automated Installation (Recommanded)
Change the directory to where you want to install this tool and run the follwing command
```
curl https://raw.githubusercontent.com/thehackersbrain/hiddenwave/main/install.sh -s | bash
```

### Manual Installation

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

**Creator:** [Gaurav Raj](https://github.com/thehackersbrain/)<br/>
**Portfolio:** [Here](https://thehackersbrain.github.io/)<br/>
**Blog:** [TheHackersBrain Blog](https://thehackersbrain.pythonanywhere.com)<br/>
**Projects:** [Here](https://github.com/thehackersbrain?tab=repositories)<br/>
**Twitter:** [@thehackersbrain](https://twitter.com/thehackersbrain)<br/>
**TryHackMe:** [hackersbrain](https://tryhackme.com/p/hackersbrain)
