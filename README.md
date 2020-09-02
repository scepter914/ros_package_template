# ros_package_template

My ROS package template

## Prerequisite

```sh
brew install fd sd rename
```

## Usage

```sh
cd YOUR_ROS_WORKSPACE
git clone git@github.com:kenji-miyake/ros_package_template.git YOUR_PACKAGE_NAME
cd YOUR_PACKAGE_NAME

# case1. If you'd like to cleanup manually
./setup.fish
mv PACKAGE_README.md README.md
rm -rf .git
rm setup.fish

# case2. If you'd like to cleanup automatically
./setup.fish --clean
```
