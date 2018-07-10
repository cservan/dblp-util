# dblp-util
Utils for interacting with the dblp computer science bibliography

## Usage

```
git clone https://github.com/yuki-koyama/dblp-util.git --recursive
```

### Download and Unarchive XML Data

```
$ python3 download.py
```

### Extract Data and Convert to Json

```
$ mkdir build
$ cd build
$ cmake ../
$ make
$ ./extract_and_convert_to_json
```

This part is under developing.
