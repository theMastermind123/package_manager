# package_manager

A simple Bash script for managing Debian packages.

## Usage

```bash
./package_manager.sh <command> <argument>
```

| Command   | Description              |
| --------- | ------------------------ |
| `info`    | Show package information |
| `install` | Install a `.deb` package |
| `remove`  | Remove a package         |
| `create`  | Create a `.deb` package  |
| `help`    | Show help                |

## Examples

```bash
./package_manager.sh info curl
./package_manager.sh install ./package.deb
./package_manager.sh remove curl
./package_manager.sh create my_package/
./package_manager.sh help
```

## Requirements

* Debian-based Linux
* Bash
* `dpkg`
* `dpkg-query`
* `dpkg-deb`
* `apt`
